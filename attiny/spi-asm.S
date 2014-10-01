#include <avr/io.h>
.global SPITransfer

SPITransfer:
	out USIDR,r24
//	ldi r24,(1<<USIOIF)
	ldi r24,64
	out USISR,r24
//	ldi r18,((1<<USIWM0)|(1<<USICS1)|(1<<USICLK)|(1<<USITC))
	ldi r18,27
SPITransfer_loop:
	out USICR,r18
	in r24, USISR
	sbrs r24, USIOIF
	rjmp SPITransfer_loop
	in r24,USIDR
	ret
