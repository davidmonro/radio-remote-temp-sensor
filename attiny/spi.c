#include "spi.h"
#include <avr/io.h>
void SPIInit(void) {
  // Switch off the pullups
  DDRA |= _BV(PINA4) | _BV(PINA5) | _BV(PINA6);
  PORTA &= ~(_BV(PINA4) | _BV(PINA5) | _BV(PINA6));
  // Enable DO and USCK as outputs
  DDRA |= (_BV(PINA4) | _BV(PINA5));
  // DI as input
  DDRA &= ~_BV(PINA6);
}

uint8_t SPITransfer(uint8_t data) {
  USIDR = data;
  USISR = (1<<USIOIF);
  do {
    USICR = (1<<USIWM0)|(1<<USICS1)|(1<<USICLK)|(1<<USITC);
  } while ((USISR & (1<<USIOIF)) == 0);
  return USIDR;
}

void SPIWriteBlock(uint8_t* data, uint8_t len)
{
  uint8_t i;
  for (i = 0; i < len; i++) {
    SPITransfer(data[i]);
  }
}

void SPITransferBlock(uint8_t* data, uint8_t* buffer, uint8_t len)
{
  uint8_t i;
  for (i = 0; i < len; i++) {
    buffer[i] = SPITransfer(data[i]);
  }
}
