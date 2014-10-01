//**** A P P L I C A T I O N   N O T E   A V R 3 0 5 ************************
//*
//* Title		: Half Duplex Interrupt Driven Software UART
//* Version		: rev. 1.2 (24-04-2002), reset vector added
//*			: rev. 1.1 (27.08.1997)
//* Last updated		: 24-04-2002
//* Target		: AT90Sxxxx (All AVR Device)
//*
//* Support email	: avr@atmel.com
//*
//* Code Size		: 32 Words
//* Low Register Usage	: 0
//* High Register Usage	: 4
//* Interrupt Usage	: None
//*
//* DESCRIPTION
//* This Application note contains a very code efficient software UART.
//* The example program receives one character and echoes it back.
//***************************************************************************
#include <avr/io.h>

// Declare symbols
.global	myPutChar

//***** Pin definitions

//Transmit pin is PB0
#define	TxPin	0
#define TxPort PORTB

//***** Global register variables
#define	bitcnt	R16			//bit counter
#define	temp	R17			//temporary storage register

#define	Txbyte	R24			//Data to be transmitted, 1st arg

//***************************************************************************
//*
//* "putchar"
//*
//* This subroutine transmits the byte stored in the "Txbyte" register
//* The number of stop bits used is set with the sb constant
//*
//* Number of words	:14 including return
//* Number of cycles	:Depens on bit rate
//* Low registers used	:None
//* High registers used	:2 (bitcnt,Txbyte)
//* Pointers used	:None
//*
//***************************************************************************
.equ		sb,	1		//Number of stop bits (1, 2, ...)

myPutChar:	push	r16
		push	r17
		ldi	bitcnt,9+sb	//1+8+sb (sb is # of stop bits)
		com	Txbyte		//Inverte everything
		sec			//Start bit
		cli

putchar0:	brcc	putchar1	//If carry set
		cbi	_SFR_IO_ADDR(TxPort),TxPin	//    send a '0'
		rjmp	putchar2	//else	

putchar1:	sbi	_SFR_IO_ADDR(TxPort),TxPin	//    send a '1'
		nop

putchar2:	rcall UART_delay	//One bit delay
		rcall UART_delay

		lsr	Txbyte		//Get next bit
		dec	bitcnt		//If not all bit sent
		brne	putchar0	//   send next
					//else
		sei
		pop	r17
		pop	r16
		ret			//   return


//***************************************************************************
//*
//* "UART_delay"
//*
//* This delay subroutine generates the required delay between the bits when
//* transmitting and receiving bytes. The total execution time is set by the
//* constant "b":
//*
//*	3·b + 7 cycles (including rcall and ret)
//*
//* Number of words	:4 including return
//* Low registers used	:None
//* High registers used	:1 (temp)
//* Pointers used	:None
//*
//***************************************************************************
// Some b values: 	(See also table in Appnote documentation)
//
// 1 MHz crystal:
//   9600 bps - b=14
//  19200 bps - b=5
//  28800 bps - b=2
//
// 2 MHz crystal:
//  19200 bps - b=14
//  28800 bps - b=8
//  57600 bps - b=2

// 4 MHz crystal:
//  19200 bps - b=31
//  28800 bps - b=19
//  57600 bps - b=8
// 115200 bps - b=2

.equ	b,	5	//19200 bps @ 1 MHz crystal


UART_delay:	ldi	temp,b
UART_delay1:	dec	temp
		brne	UART_delay1

		ret


