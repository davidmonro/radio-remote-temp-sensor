// Copyright 2013 David Monro davidm@davidmonro.net

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/power.h>
#include <avr/sleep.h>
#include <util/atomic.h>
#include <util/delay.h>
#include <stdio.h>
#include "serial-helpers.h"
#include "onewire.h"
#include "ds18x20.h"
#include "radio.h"


typedef struct {
  unsigned long tstamp;
  uint8_t sensid[8];
  int32_t tenthousandths;
} myRadioBuf_t;

// Globals
volatile unsigned long millis = 0;

/** The sensor stuff */
#define MAXSENSORS 8
uint8_t gSensorIDs[MAXSENSORS][OW_ROMCODE_SIZE];

// Statics
static const uint64_t pipe = 0xE8E8F0F0E1LL;

// Interrupt service routines

// Fires once per millisecond
ISR(TIM0_COMPA_vect)
{
  millis++;
}

// Fires on watchdog timeout
ISR(WDT_vect)
{
  //myPutStr("WATCHDOG FIRED\r\n");
}

void initInterrupts(void)
{
  sei();
}

volatile unsigned long int getMillis(void)
{
  unsigned long int localcopy;
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
  {
          localcopy = millis;
  }
  return localcopy;
}

void timerInit(void)
{
  // Use OCR0A for count (wg mode 2), use a /8 prescaler
  TCCR0A = _BV(WGM01);
  TCCR0B = _BV(CS01);
  // Set the ICR1 reg for 1ms count
  OCR0A = 125;
  // Set the top interrupt enable
  TIMSK0 = _BV(OCIE0A);
}

void debugLedToggle(uint8_t led) {
  PORTA ^= 0x01;
}

static uint8_t search_sensors(void)
{
  uint8_t i;
  uint8_t id[OW_ROMCODE_SIZE];
  uint8_t diff, nSensors;

  ow_reset();

  nSensors = 0;

  diff = OW_SEARCH_FIRST;
  while ( diff != OW_LAST_DEVICE && nSensors < MAXSENSORS ) {
    DS18X20_find_sensor( &diff, &id[0] );

    if( diff == OW_PRESENCE_ERR ) {
      break;
    }

    if( diff == OW_DATA_ERR ) {
      break;
    }

    for ( i=0; i < OW_ROMCODE_SIZE; i++ ) {
      gSensorIDs[nSensors][i] = id[i];
    }

    nSensors++;
  }

  return nSensors;
}

void wdtInit(void) {
  // We enable it as an interrupt source only
  // Set to 8s period
  WDTCSR = _BV(WDIE) | _BV(WDP3) | _BV(WDP0);
}

int main(void) {

  uint8_t numSensors = 0, i;
  // unsigned long nextflash = 0;

  // Configure all pins as inputs with pullups initially
  DDRA = 0x00;
  PORTA = 0xff;
  DDRB = 0x00;
  PORTB = 0xff;

  // Serial output line
  DDRB |= _BV(PINB0);
  PORTB |= _BV(PINB0);

  // LED
  // DDRA |= _BV(PINA0);

  // Radio power is PA1
  PORTA &= ~_BV(PINA1);
  DDRA |= _BV(PINA1);

  // Onewire power is PA2
  PORTA &= ~_BV(PINA2);
  DDRA |= _BV(PINA2);

  myPutStr("Hello world\r\n");

  // Various power-saving things

  // Disable BOD while sleeping. I hope.
  MCUCR |= (_BV(BODS) | _BV(BODSE));
  MCUCR &= ~_BV(BODSE);
  MCUCR |= (_BV(BODS));
 
  // Disable the ADC
  ADCSRA &= ~_BV(ADEN);

  // Disable the Analog Comparator
  ACSR |= _BV(ACD);

  // Disable clocking of timer1 and ADC
  PRR |= (_BV(PRTIM1)|_BV(PRADC));

  timerInit();
  wdtInit();
  initInterrupts();


  // Power up the Onewire bus
  PORTA |= _BV(PINA2);
  while(numSensors == 0) {
    myPutStr("Scanning for sensors\r\n");
    numSensors = search_sensors();
    myPutStr("Found ");
    myPutUint8(numSensors);
    myPutStr(" sensors\r\n");

    for (i=0;i<numSensors;i++) {
      uint8_t j;
      myPutStr("Sensor ");
      myPutUint8(i);
      myPutStr(" address ");
      for (j=0;j<OW_ROMCODE_SIZE;j++) {
	myPutUint8(gSensorIDs[i][j]);
      }
      if (gSensorIDs[i][0] == DS18S20_FAMILY_CODE ) {
	myPutStr(" DS18S20/DS1820");
      } else if ( gSensorIDs[i][0] == DS1822_FAMILY_CODE ) {
	myPutStr(" DS1822");
      } else {
	myPutStr(" DS18B20");
      }
      if ( DS18X20_get_power_status( &gSensorIDs[i][0] ) == DS18X20_POWER_PARASITE ) {
	myPutStr(" parasite\r\n");
      } else {
	myPutStr(" external\r\n");
      }

      // Enable 12 bit mode (won't do anything on DS18S20)
      DS18X20_write_scratchpad(&gSensorIDs[i][0], 0, 0, DS18B20_12_BIT);
      DS18X20_scratchpad_to_eeprom(DS18X20_get_power_status( &gSensorIDs[i][0] ),&gSensorIDs[i][0]);
	
    }
      

  }
  while(1) {
    unsigned long wakepoint;
    myRadioBuf_t radiobuf;
    //char debugbuf[10];

    // if ((signed long)now - (signed long)nextflash >= 0) {
    //   debugLedToggle(0);
    //   nextflash = now + 1000;
    // }

    // Power up the Onewire bus
    PORTA |= _BV(PINA2);
    // Let is stabilize for a few ms
    wakepoint = getMillis() + 15;
    numSensors = search_sensors();
    while (! ((signed long)getMillis() - (signed long)wakepoint >= 0)) {
      set_sleep_mode(SLEEP_MODE_IDLE);
      sleep_mode();
    }
    if ( DS18X20_start_meas( DS18X20_POWER_PARASITE, NULL ) == DS18X20_OK) {
      wakepoint = getMillis() + DS18B20_TCONV_12BIT;
      while (! ((signed long)getMillis() - (signed long)wakepoint >= 0)) {
	set_sleep_mode(SLEEP_MODE_IDLE);
	sleep_mode();
      }
      // Power the radio up
      PORTA |= _BV(PINA1);
      // Wakepoint set to now +100ms to allow radio to wake
      wakepoint = getMillis() + 100;

      for ( i = 0; i < numSensors; i++ ) {
        radiobuf.tenthousandths = -9999999L;
	if (DS18X20_read_maxres( &gSensorIDs[i][0], &(radiobuf.tenthousandths) ) != DS18X20_OK) {
	  radiobuf.tenthousandths = -9999999L;
	}

	//myPutStr("Sensor ");
	uint8_t j;
	for (j=0;j<OW_ROMCODE_SIZE;j++) {
            radiobuf.sensid[j] = gSensorIDs[i][j];
	    //myPutUint8(gSensorIDs[i][j]);
        }
	//myPutStr(" = ");
	//sprintf(debugbuf, "%d.%d\r\n", (int)(radiobuf.tenthousandths/10000), (int)(radiobuf.tenthousandths % 10000));
	//myPutStr(debugbuf);
        if (0 == i) {
	  // First time around, radio not initialized
	  while (! ((signed long)getMillis() - (signed long)wakepoint >= 0)) {
            set_sleep_mode(SLEEP_MODE_IDLE);
            sleep_mode();
          }
	  radioInit();
	  // No auto ack
	  radioSetAutoAck(0);
	  radioOpenWritingPipe(pipe);
        }
	radiobuf.tstamp = getMillis();
	//myPutStr("about to radioWrite, i=");
	//myPutUint8(i);
	//myPutStr("...");
	radioWrite(&radiobuf,sizeof(radiobuf));
	//myPutStr("Done\r\n");
      }
      // Power the radio down
      PORTA &= ~_BV(PINA1);
      // Plus the CE and CSN pins
      PORTA &= ~_BV(PINA7);
      PORTB &= ~_BV(PINB2);
      // And the onewire bus
      PORTA &= ~_BV(PINA2);
    } else {
      myPutStr("Error measuring sensors\n");
    }
    //tmp = getMillis();
    //radioWrite(&tmp , sizeof(unsigned long) );
    // Sleep hard until WDT fires
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_mode();
  }
}

