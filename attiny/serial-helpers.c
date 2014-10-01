#include "serial-helpers.h"

void myPutStr(const char *str) {
  while (*str != 0) {
    myPutChar(*str);
    str++;
  }
}

void myPutUint8(uint8_t num) {
  uint8_t tmp = (num >> 4);
  if (tmp < 10) {
    myPutChar(tmp+'0');
  } else {
    myPutChar(tmp-10+'A');
  }
  num &= 0xf;
  if (num < 10) {
    myPutChar(num+'0');
  } else {
    myPutChar(num-10+'A');
  }
}

