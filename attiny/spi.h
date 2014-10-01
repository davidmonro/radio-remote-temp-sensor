#include <stdint.h>
extern void SPIInit(void);
extern uint8_t SPITransfer(uint8_t data);
extern void SPIWriteBlock(uint8_t* data, uint8_t len);
extern void SPITransferBlock(uint8_t* data, uint8_t* buffer, uint8_t len);
