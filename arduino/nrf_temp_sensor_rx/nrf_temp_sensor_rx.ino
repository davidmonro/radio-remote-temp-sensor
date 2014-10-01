/*
 Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

/**
 * Example of using interrupts
 *
 * This is an example of how to user interrupts to interact with the radio.
 * It builds on the pingpair_pl example, and uses ack payloads.
 */

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

//
// On-wire datastructure
//
typedef struct {
  unsigned long tstamp;
  uint8_t sensid[8];
  int32_t tenthousandths;
} myRadioBuf_t;

//
// Hardware configuration
//

// Set up nRF24L01 radio on SPI bus plus pins 9 & 10

RF24 radio(9,8);

//
// Topology
//

// Single radio pipe address for the nodes to communicate.
const uint64_t pipe = 0xE8E8F0F0E1LL;

// Interrupt handler, check the radio because we got an IRQ
void check_radio(void);
   
#define DS18X20_DECIMAL_CHAR      '.'
#define DS18X20_OK                0x00
#define DS18X20_ERROR             0x01

uint8_t DS18X20_format_from_maxres( int32_t temperaturevalue, char str[], uint8_t n)
{
        uint8_t sign = 0;
        char temp[10];
        int8_t temp_loc = 0;
        uint8_t str_loc = 0;
        ldiv_t ldt;
        uint8_t ret;

        // range from -550000:-55.0000°C to 1250000:+125.0000°C -> min. 9+1 chars
        if ( n >= (9+1) && temperaturevalue > -1000000L && temperaturevalue < 10000000L ) {

                if ( temperaturevalue < 0) {
                        sign = 1;
                        temperaturevalue = -temperaturevalue;
                }

                do {
                        ldt = ldiv( temperaturevalue, 10 );
                        temp[temp_loc++] = ldt.rem + '0';
                        temperaturevalue = ldt.quot;
                } while ( temperaturevalue > 0 );

                // mk 20110209
                if ((temp_loc < 4)&&(temp_loc > 1)) {
                        temp[temp_loc++] = '0';
                } // mk end

                if ( sign ) {
                        temp[temp_loc] = '-';
                } else {
                        temp[temp_loc] = '+';
                }

                while ( temp_loc >= 0 ) {
                        str[str_loc++] = temp[(uint8_t)temp_loc--];
                        if ( temp_loc == 3 ) {
                                str[str_loc++] = DS18X20_DECIMAL_CHAR;
                        }
                }
                str[str_loc] = '\0';

                ret = DS18X20_OK;
        } else {
                ret = DS18X20_ERROR;
        }
        
        return ret;
}

void setup(void)
{
  //
  // Print preamble
  //

  Serial.begin(57600);
  printf_begin();
  printf("Hello World\n\r");

  //
  // Setup and configure rf radio
  //

  radio.begin();

  // No AA in use
  radio.setAutoAck(false);

  //
  // Open pipes to other nodes for communication
  //

  radio.openReadingPipe(1,pipe);
  
  //
  // Start listening
  //
  
  radio.startListening();

  //
  // Dump the configuration of the rf unit for debugging
  //

  radio.printDetails();

  //
  // Attach interrupt handler to interrupt #0 (using pin 2)
  //

  attachInterrupt(0, check_radio, FALLING);
}

void loop(void)
{
  
  //
  // Receiver role: Does nothing!  All the work is in IRQ
  //

}

void check_radio(void)
{
  // What happened?
  bool tx,fail,rx;
  radio.whatHappened(tx,fail,rx);

  // Did we receive a message?
  if ( rx )
  {
    // Get this payload and dump it
    myRadioBuf_t payload;
    bool done = false;
    while (!done)
    {
      char s[10];
      done = radio.read( &payload, sizeof(payload) );
      DS18X20_format_from_maxres(payload.tenthousandths,s,10);
      printf("Sensor %02X%02X%02X%02X%02X%02X%02X%02X = %s\r\n",
        payload.sensid[0], payload.sensid[1], payload.sensid[2], payload.sensid[3],
        payload.sensid[4], payload.sensid[5], payload.sensid[6], payload.sensid[7], s);
    }
  }
}

// vim:ai:cin:sts=2 sw=2 ft=cpp
