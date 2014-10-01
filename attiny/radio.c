#include "spi.h"
#include "radio.h"
#include "nRF24L01.h"
#include <avr/io.h>
#include <avr/sleep.h>
#include <stddef.h>
#include <util/delay.h>
#include "serial-helpers.h"

// non-public constants and macros

#define CHANNEL 76
#define ADDRESS_LENGTH 5

// Pin definitions for chip select and chip enable on the radio module

#define CE_DDR          DDRA
#define CSN_DDR         DDRB
#define CE_PORT         PORTA
#define CSN_PORT        PORTB
#define CE_PIN          PA7
#define CSN_PIN         PB2

// Definitions for selecting and enabling the radio
#define CSN_HIGH()      CSN_PORT |=  _BV(CSN_PIN);
#define CSN_LOW()       CSN_PORT &= ~_BV(CSN_PIN);
#define CE_HIGH()       CE_PORT |=  _BV(CE_PIN);
#define CE_LOW()        CE_PORT &= ~_BV(CE_PIN);

// Misc stuff
#define min(a,b) ((a)<(b)?(a):(b))

// Static variables
static uint8_t wide_band = 1; /* 2Mbs data rate in use? */
static uint8_t p_variant = 0; /* False for RF24L01 and true for RF24L01P */
static uint8_t payload_size = 32; /**< Fixed size of payloads */
static uint8_t ack_payload_available = 0; /**< Whether there is an ack payload waiting */
static uint8_t dynamic_payloads_enabled = 0; /**< Whether dynamic payloads are enabled. */ 
static uint8_t ack_payload_length; /**< Dynamic size of pending ack payload. */
static uint64_t pipe0_reading_address = 0; /**< Last address set on pipe 0 for reading. */

static uint8_t read_register2(uint8_t reg, uint8_t* buffer, uint8_t len)
{
  uint8_t status;
  CSN_LOW();
  status = SPITransfer(R_REGISTER | (REGISTER_MASK & reg));
  while( len-- ) {
    *buffer++ = SPITransfer(NOP);
  }
  CSN_HIGH();
  return status;
}

static uint8_t read_register(uint8_t reg)
{
  CSN_LOW();
  SPITransfer( R_REGISTER | ( REGISTER_MASK & reg ) );
  uint8_t result = SPITransfer(NOP);
  CSN_HIGH();
  return result;
}

static uint8_t write_register2(uint8_t reg, const uint8_t* buf, uint8_t len)
{
  uint8_t status;

  CSN_LOW();
  status = SPITransfer( W_REGISTER | ( REGISTER_MASK & reg ) );
  while ( len-- )
    SPITransfer(*buf++);
  CSN_HIGH();

  return status;
}

static uint8_t write_register(uint8_t reg, uint8_t value)
{
  uint8_t status;

  CSN_LOW();
  status = SPITransfer( W_REGISTER | ( REGISTER_MASK & reg ) );
  SPITransfer(value);
  CSN_HIGH();

  return status;
}

static uint8_t write_payload(const void* buf, uint8_t len)
{
  uint8_t status;

  const uint8_t* current = buf;

  uint8_t data_len = min(len,payload_size);
  uint8_t blank_len = dynamic_payloads_enabled ? 0 : payload_size - data_len;
  
  CSN_LOW();
  status = SPITransfer( W_TX_PAYLOAD );
  while ( data_len-- )
    SPITransfer(*current++);
  while ( blank_len-- )
    SPITransfer(0);
  CSN_HIGH();

  return status;
}

static uint8_t read_payload(void* buf, uint8_t len)
{
  uint8_t status;
  uint8_t* current = buf;

  uint8_t data_len = min(len,payload_size);
  uint8_t blank_len = dynamic_payloads_enabled ? 0 : payload_size - data_len;
  
  CSN_LOW();
  status = SPITransfer( R_RX_PAYLOAD );
  while ( data_len-- )
    *current++ = SPITransfer(0xff);
  while ( blank_len-- )
    SPITransfer(0xff);
  CSN_HIGH();

  return status;
}

uint8_t radioFlushRX(void)
{
  uint8_t status;

  CSN_LOW();
  status = SPITransfer( FLUSH_RX );
  CSN_HIGH();

  return status;
}

uint8_t radioFlushTX(void)
{
  uint8_t status;

  CSN_LOW();
  status = SPITransfer( FLUSH_TX );
  CSN_HIGH();

  return status;
}



/**
 * Retrieve the status register.
 */
static uint8_t get_status(void)
{
  uint8_t status = 0;
  CSN_LOW();

  status = SPITransfer(NOP);

  CSN_HIGH();

  return status;
}


static void print_byte_register(const char* name, uint8_t reg, uint8_t qty)
{
  uint8_t regval;
  myPutStr(name);
  myPutStr(" =");
  while (qty--) {
    myPutStr(" 0x");
    regval = read_register(reg++);
    myPutUint8(regval);
  }
  myPutStr("\r\n");
}

static void print_address_register(const char* name, uint8_t reg, uint8_t qty) {
  myPutStr(name);
  myPutStr(" =");
  while (qty--) {
    uint8_t buffer[5];
    read_register2(reg++,buffer,sizeof buffer);
    myPutStr(" 0x");
    uint8_t* bufptr = buffer + sizeof buffer;
    while(--bufptr >= buffer) {
      myPutUint8(*bufptr);
    }
  }
  myPutStr("\r\n");
}

static void print_status(uint8_t status)
{
  myPutStr("STATUS = 0x");
  myPutUint8(status);
  myPutStr("\r\n");
}

void radioPrintDetails(void) {
  print_status(get_status());
  print_address_register("RX_ADDR_P0-1",RX_ADDR_P0,2);
  print_byte_register("RX_ADDR_P2-5",RX_ADDR_P2,4);
  print_address_register("TX_ADDR",TX_ADDR,1);

  print_byte_register("RX_PW_P0-6",RX_PW_P0,6);
  print_byte_register("EN_AA",EN_AA,1);
  print_byte_register("EN_RXADDR",EN_RXADDR,1);
  print_byte_register("RF_CH",RF_CH,1);
  print_byte_register("RF_SETUP",RF_SETUP,1);
  print_byte_register("CONFIG",CONFIG,1);
  print_byte_register("DYNPD/FEATURE",DYNPD,2);

}

void radioSetChannel(uint8_t channel)
{
  // TODO: This method could take advantage of the 'wide_band' calculation
  // done in radioSetChannel() to require certain channel spacing.

  const uint8_t max_channel = 127;
  write_register(RF_CH,min(channel,max_channel));
}

void radioSetPayloadSize(uint8_t size)
{
  const uint8_t max_payload_size = 32;
  payload_size = min(size,max_payload_size);
}

uint8_t radioGetPayloadSize(void)
{
  return payload_size;
}

void radioSetPALevel(rf24_pa_dbm_e level)
{
  uint8_t setup = read_register(RF_SETUP) ;
  setup &= ~(_BV(RF_PWR_LOW) | _BV(RF_PWR_HIGH)) ;

  // switch uses RAM (evil!)
  if ( level == RF24_PA_MAX )
  {
    setup |= (_BV(RF_PWR_LOW) | _BV(RF_PWR_HIGH)) ;
  }
  else if ( level == RF24_PA_HIGH )
  {
    setup |= _BV(RF_PWR_HIGH) ;
  }
  else if ( level == RF24_PA_LOW )
  {
    setup |= _BV(RF_PWR_LOW);
  }
  else if ( level == RF24_PA_MIN )
  {
    // nothing
  }
  else if ( level == RF24_PA_ERROR )
  {
    // On error, go to maximum PA
    setup |= (_BV(RF_PWR_LOW) | _BV(RF_PWR_HIGH)) ;
  }

  write_register( RF_SETUP, setup ) ;
}

rf24_pa_dbm_e radioGetPALevel(void)
{
  rf24_pa_dbm_e result = RF24_PA_ERROR ;
  uint8_t power = read_register(RF_SETUP) & (_BV(RF_PWR_LOW) | _BV(RF_PWR_HIGH)) ;

  // switch uses RAM (evil!)
  if ( power == (_BV(RF_PWR_LOW) | _BV(RF_PWR_HIGH)) )
  {
    result = RF24_PA_MAX ;
  }
  else if ( power == _BV(RF_PWR_HIGH) )
  {
    result = RF24_PA_HIGH ;
  }
  else if ( power == _BV(RF_PWR_LOW) )
  {
    result = RF24_PA_LOW ;
  }
  else
  {
    result = RF24_PA_MIN ;
  }

  return result ;
}

uint8_t radioSetDataRate(rf24_datarate_e speed)
{
  uint8_t result = 0;
  uint8_t setup = read_register(RF_SETUP) ;

  // HIGH and LOW '00' is 1Mbs - our default
  wide_band = 0 ;
  setup &= ~(_BV(RF_DR_LOW) | _BV(RF_DR_HIGH)) ;
  if( speed == RF24_250KBPS )
  {
    // Must set the RF_DR_LOW to 1; RF_DR_HIGH (used to be RF_DR) is already 0
    // Making it '10'.
    wide_band = 0 ;
    setup |= _BV( RF_DR_LOW ) ;
  }
  else
  {
    // Set 2Mbs, RF_DR (RF_DR_HIGH) is set 1
    // Making it '01'
    if ( speed == RF24_2MBPS )
    {
      wide_band = 1 ;
      setup |= _BV(RF_DR_HIGH);
    }
    else
    {
      // 1Mbs
      wide_band = 0 ;
    }
  }
  write_register(RF_SETUP,setup);

  // Verify our result
  if ( read_register(RF_SETUP) == setup )
  {
    result = 1;
  }
  else
  {
    wide_band = 0;
  }

  return result;
}

rf24_datarate_e radioGetDataRate( void )
{
  rf24_datarate_e result ;
  uint8_t dr = read_register(RF_SETUP) & (_BV(RF_DR_LOW) | _BV(RF_DR_HIGH));
  
  // switch uses RAM (evil!)
  // Order matters in our case below
  if ( dr == _BV(RF_DR_LOW) )
  {
    // '10' = 250KBPS
    result = RF24_250KBPS ;
  }
  else if ( dr == _BV(RF_DR_HIGH) )
  {
    // '01' = 2MBPS
    result = RF24_2MBPS ;
  }
  else
  {
    // '00' = 1MBPS
    result = RF24_1MBPS ;
  }
  return result ;
}

void radioSetCRCLength(rf24_crclength_e length)
{
  uint8_t config = read_register(CONFIG) & ~( _BV(CRCO) | _BV(EN_CRC)) ;
  
  // switch uses RAM (evil!)
  if ( length == RF24_CRC_DISABLED )
  {
    // Do nothing, we turned it off above. 
  }
  else if ( length == RF24_CRC_8 )
  {
    config |= _BV(EN_CRC);
  }
  else
  {
    config |= _BV(EN_CRC);
    config |= _BV( CRCO );
  }
  write_register( CONFIG, config ) ;
}

rf24_crclength_e radioGetCRCLength(void)
{
  rf24_crclength_e result = RF24_CRC_DISABLED;
  uint8_t config = read_register(CONFIG) & ( _BV(CRCO) | _BV(EN_CRC)) ;

  if ( config & _BV(EN_CRC ) )
  {
    if ( config & _BV(CRCO) )
      result = RF24_CRC_16;
    else
      result = RF24_CRC_8;
  }

  return result;
}

void radioDisableCRC( void )
{
  uint8_t disable = read_register(CONFIG) & ~_BV(EN_CRC) ;
  write_register( CONFIG, disable ) ;
}

void radioSetRetries(uint8_t delay, uint8_t count)
{
 write_register(SETUP_RETR,(delay&0xf)<<ARD | (count&0xf)<<ARC);
}

void radioInit(void)
{
  // Initialize pins
  CE_PORT &= ~_BV(CE_PIN);
  CE_DDR |= _BV(CE_PIN);
  CSN_PORT &= ~_BV(CSN_PIN);
  CSN_DDR |= _BV(CSN_PIN);

  // Initialize SPI bus
  SPIInit();

  CE_LOW();
  CSN_HIGH();

  // Must allow the radio time to settle else configuration bits will not necessarily stick.
  // This is actually only required following power up but some settling time also appears to
  // be required after resets too. For full coverage, we'll always assume the worst.
  // Enabling 16b CRC is by far the most obvious case if the wrong timing is used - or skipped.
  // Technically we require 4.5ms + 14us as a worst case. We'll just call it 5ms for good measure.
  // WARNING: Delay is based on P-variant whereby non-P *may* require different timing.
  _delay_ms( 5 ) ;

  // Set 1500uS (minimum for 32B payload in ESB@250KBPS) timeouts, to make testing a little easier
  // WARNING: If this is ever lowered, either 250KBS mode with AA is broken or maximum packet
  // sizes must never be used. See documentation for a more complete explanation.
  write_register(SETUP_RETR,(0x04 << ARD) | (0x0f << ARC));

  // Restore our default PA level
  radioSetPALevel( RF24_PA_MAX ) ;

  // Determine if this is a p or non-p RF24 module and then
  // reset our data rate back to default value. This works
  // because a non-P variant won't allow the data rate to
  // be set to 250Kbps.
  if( radioSetDataRate( RF24_250KBPS ) )
  {
    p_variant = 1;
  }

  // Then set the data rate to the slowest (and most reliable) speed supported by all
  // hardware.
  radioSetDataRate( RF24_1MBPS ) ;

  // Initialize CRC and request 2-byte (16bit) CRC
  radioSetCRCLength( RF24_CRC_16 ) ;
  
  // Disable dynamic payloads, to match dynamic_payloads_enabled setting
  write_register(DYNPD,0);

  // Reset current status
  // Notice reset and flush is the last thing we do
  write_register(STATUS,_BV(RX_DR) | _BV(TX_DS) | _BV(MAX_RT) );

  // Set up default configuration.  Callers can always change it later.
  // This channel should be universally safe and not bleed over into adjacent
  // spectrum.
  radioSetChannel(76);

  // Flush buffers
  radioFlushRX();
  radioFlushTX();
}

void radioStartListening(void)
{
  write_register(CONFIG, read_register(CONFIG) | _BV(PWR_UP) | _BV(PRIM_RX));
  write_register(STATUS, _BV(RX_DR) | _BV(TX_DS) | _BV(MAX_RT) );

  // Restore the pipe0 adddress, if exists
  if (pipe0_reading_address)
    write_register2(RX_ADDR_P0, (const uint8_t *)(&pipe0_reading_address), 5);

  // Flush buffers
  radioFlushRX();
  radioFlushTX();

  // Go!
  CE_HIGH();

  // wait for the radio to come up (130us actually only needed)
  _delay_us(130);
}

void radioStopListening(void)
{
  CE_LOW();
  radioFlushTX();
  radioFlushRX();
}

void radioPowerDown(void)
{
  write_register(CONFIG,read_register(CONFIG) & ~_BV(PWR_UP));
}

void radioPowerUp(void)
{
  write_register(CONFIG,read_register(CONFIG) | _BV(PWR_UP));
}

static uint8_t radioGetDynamicPayloadSize(void)
{
  uint8_t result = 0;

  CSN_LOW();
  SPITransfer( R_RX_PL_WID );
  result = SPITransfer(0xff);
  CSN_HIGH();

  return result;
}

void radioStartWrite( const void* buf, uint8_t len )
{
  // Transmitter power-up
  write_register(CONFIG, ( read_register(CONFIG) | _BV(PWR_UP) ) & ~_BV(PRIM_RX) );
  _delay_us(1500);

  // Now we should be in Standby-I

  // Send the payload
  write_payload( buf, len );

  // Allons!
  CE_HIGH();
  _delay_us(15);
  CE_LOW();
}

void radioWhatHappened(uint8_t* tx_ok,uint8_t* tx_fail,uint8_t* rx_ready)
{
  // Read the status & reset the status in one easy call
  // Or is that such a good idea?
  uint8_t status = write_register(STATUS,_BV(RX_DR) | _BV(TX_DS) | _BV(MAX_RT) );

  // Report to the user what happened
  *tx_ok = status & _BV(TX_DS);
  *tx_fail = status & _BV(MAX_RT);
  *rx_ready = status & _BV(RX_DR);
}


uint8_t radioWrite( const void* buf, uint8_t len )
{
  uint8_t result = 0;

  // Begin the write
  radioStartWrite(buf,len);

  // ------------
  // At this point we could return from a non-blocking write, and then call
  // the rest after an interrupt

  // Instead, we are going to block here until we get TX_DS (transmission completed and ack'd)
  // or MAX_RT (maximum retries, transmission failed).  Also, we'll timeout in case the radio
  // is flaky and we get neither.

  // IN the end, the send should be blocking.  It comes back in 60ms worst case, or much faster
  // if I tighted up the retry logic.  (Default settings will be 1500us.
  // Monitor the send

  uint8_t observe_tx;
  uint8_t status;
  unsigned long sent_at = getMillis();
  unsigned long timeout = sent_at + 500; //ms to wait for timeout
  do {
    status = read_register2(OBSERVE_TX,&observe_tx,1);
    //IF_SERIAL_DEBUG(Serial.print(observe_tx,HEX));
    set_sleep_mode(SLEEP_MODE_IDLE);
    sleep_mode();
  } while( ! ( status & ( _BV(TX_DS) | _BV(MAX_RT) ) ) && (! ((signed long)getMillis() - (signed long)timeout >= 0)  ) );

  // The part above is what you could recreate with your own interrupt handler,
  // and then call this when you got an interrupt
  // ------------

  // Call this when you get an interrupt
  // The status tells us three things
  // * The send was successful (TX_DS)
  // * The send failed, too many retries (MAX_RT)
  // * There is an ack packet waiting (RX_DR)
  uint8_t tx_ok, tx_fail;
  radioWhatHappened(&tx_ok,&tx_fail,&ack_payload_available);

  //printf("%u%u%u\r\n",tx_ok,tx_fail,ack_payload_available);

  result = tx_ok;
  //IF_SERIAL_DEBUG(Serial.print(result?"...OK.":"...Failed"));

  // Handle the ack packet
  if ( ack_payload_available )
  {
    ack_payload_length = radioGetDynamicPayloadSize();
    //IF_SERIAL_DEBUG(Serial.print("[AckPacket]/"));
    //IF_SERIAL_DEBUG(Serial.println(ack_payload_length,DEC));
  }

  // Yay, we are done.

  // Power down
  radioPowerDown();

  // Flush buffers (Is this a relic of past experimentation, and not needed anymore??)
  radioFlushTX();

  return result;
}

uint8_t radioDataAvailable(uint8_t* pipe_num)
{
  uint8_t status = get_status();

  // Too noisy, enable if you really want lots o data!!
  //IF_SERIAL_DEBUG(print_status(status));

  uint8_t result = ( status & _BV(RX_DR) );

  if (result)
  {
    // If the caller wants the pipe number, include that
    if ( pipe_num )
      *pipe_num = ( status >> RX_P_NO ) & 0x07;

    // Clear the status bit

    // ??? Should this REALLY be cleared now?  Or wait until we
    // actually READ the payload?

    write_register(STATUS,_BV(RX_DR) );

    // Handle ack payload receipt
    if ( status & _BV(TX_DS) )
    {
      write_register(STATUS,_BV(TX_DS));
    }
  }

  return result;
}

uint8_t radioRead( void* buf, uint8_t len )
{
  // Fetch the payload
  read_payload( buf, len );

  // was this the last of the data available?
  return read_register(FIFO_STATUS) & _BV(RX_EMPTY);
}

void radioOpenWritingPipe(uint64_t value)
{
  // Note that AVR 8-bit uC's store this LSB first, and the NRF24L01(+)
  // expects it LSB first too, so we're good.

  write_register2(RX_ADDR_P0, (const uint8_t*)(&value), 5);
  write_register2(TX_ADDR, (const uint8_t*)(&value), 5);

  const uint8_t max_payload_size = 32;
  write_register(RX_PW_P0,min(payload_size,max_payload_size));
}

static const uint8_t child_pipe[] =
{
  RX_ADDR_P0, RX_ADDR_P1, RX_ADDR_P2, RX_ADDR_P3, RX_ADDR_P4, RX_ADDR_P5
};
static const uint8_t child_payload_size[] =
{
  RX_PW_P0, RX_PW_P1, RX_PW_P2, RX_PW_P3, RX_PW_P4, RX_PW_P5
};
static const uint8_t child_pipe_enable[] =
{
  ERX_P0, ERX_P1, ERX_P2, ERX_P3, ERX_P4, ERX_P5
};

void radioOpenReadingPipe(uint8_t child, uint64_t address)
{
  // If this is pipe 0, cache the address.  This is needed because
  // radioOpenWritingPipe() will overwrite the pipe 0 address, so
  // radioStartListening() will have to restore it.
  if (child == 0)
    pipe0_reading_address = address;

  if (child <= 6)
  {
    // For pipes 2-5, only write the LSB
    if ( child < 2 )
      write_register2(child_pipe[child], (const uint8_t *)(&address), 5);
    else
      write_register2(child_pipe[child], (const uint8_t *)(&address), 1);

    write_register(child_payload_size[child],payload_size);

    // Note it would be more efficient to set all of the bits for all open
    // pipes at once.  However, I thought it would make the calling code
    // more simple to do it this way.
    write_register(EN_RXADDR,read_register(EN_RXADDR) | _BV(child_pipe_enable[child]));
  }
}

static void toggle_features(void)
{
  CSN_LOW();
  SPITransfer( ACTIVATE );
  SPITransfer( 0x73 );
  CSN_HIGH();
}

void radioEnableDynamicPayloads(void)
{
  // Enable dynamic payload throughout the system
  write_register(FEATURE,read_register(FEATURE) | _BV(EN_DPL) );

  // If it didn't work, the features are not enabled
  if ( ! read_register(FEATURE) )
  {
    // So enable them and try again
    toggle_features();
    write_register(FEATURE,read_register(FEATURE) | _BV(EN_DPL) );
  }

  // IF_SERIAL_DEBUG(printf("FEATURE=%i\r\n",read_register(FEATURE)));

  // Enable dynamic payload on all pipes
  //
  // Not sure the use case of only having dynamic payload on certain
  // pipes, so the library does not support it.
  write_register(DYNPD,read_register(DYNPD) | _BV(DPL_P5) | _BV(DPL_P4) | _BV(DPL_P3) | _BV(DPL_P2) | _BV(DPL_P1) | _BV(DPL_P0));

  dynamic_payloads_enabled = 1;
}

void radioEnableAckPayload(void)
{
  //
  // enable ack payload and dynamic payload features
  //

  write_register(FEATURE,read_register(FEATURE) | _BV(EN_ACK_PAY) | _BV(EN_DPL) );

  // If it didn't work, the features are not enabled
  if ( ! read_register(FEATURE) )
  {
    // So enable them and try again
    toggle_features();
    write_register(FEATURE,read_register(FEATURE) | _BV(EN_ACK_PAY) | _BV(EN_DPL) );
  }

  // IF_SERIAL_DEBUG(printf("FEATURE=%i\r\n",read_register(FEATURE)));

  //
  // Enable dynamic payload on pipes 0 & 1
  //

  write_register(DYNPD,read_register(DYNPD) | _BV(DPL_P1) | _BV(DPL_P0));
}

void radioWriteAckPayload(uint8_t pipe, const void* buf, uint8_t len)
{
  const uint8_t* current = buf;

  CSN_LOW();
  SPITransfer( W_ACK_PAYLOAD | ( pipe & 0x07 ) );
  const uint8_t max_payload_size = 32;
  uint8_t data_len = min(len,max_payload_size);
  while ( data_len-- )
    SPITransfer(*current++);

  CSN_HIGH();
}

uint8_t radioIsAckPayloadAvailable(void)
{
  uint8_t result = ack_payload_available;
  ack_payload_available = 0;
  return result;
}

uint8_t radioIsPVariant(void)
{
  return p_variant ;
}

void radioSetAutoAck(uint8_t enable)
{
  if ( enable )
    write_register(EN_AA, 0x3f);
  else
    write_register(EN_AA, 0);
}

void radioSetAutoAck2( uint8_t pipe, uint8_t enable )
{
  if ( pipe <= 6 )
  {
    uint8_t en_aa = read_register( EN_AA ) ;
    if( enable )
    {
      en_aa |= _BV(pipe) ;
    }
    else
    {
      en_aa &= ~_BV(pipe) ;
    }
    write_register( EN_AA, en_aa ) ;
  }
}

uint8_t radioTestCarrier(void)
{
  return ( read_register(CD) & 1 );
}

uint8_t radioTestRPD(void)
{
  return ( read_register(RPD) & 1 ) ;
}


