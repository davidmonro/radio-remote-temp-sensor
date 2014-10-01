	.file	"spi.c"
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__SREG__ = 0x3f
__tmp_reg__ = 0
__zero_reg__ = 1
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.section	.text.SPIInit,"ax",@progbits
.global	SPIInit
	.type	SPIInit, @function
SPIInit:
.LFB0:
	.file 1 "spi.c"
	.loc 1 3 0
	.cfi_startproc
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	.loc 1 4 0
	in r24,0x1a
	ori r24,lo8(48)
	out 0x1a,r24
	ret
	.cfi_endproc
.LFE0:
	.size	SPIInit, .-SPIInit
	.section	.text.SPITransfer,"ax",@progbits
.global	SPITransfer
	.type	SPITransfer, @function
SPITransfer:
.LFB1:
	.loc 1 7 0
	.cfi_startproc
.LVL0:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	.loc 1 8 0
	out 0xf,r24
	.loc 1 9 0
	ldi r24,lo8(64)
.LVL1:
	out 0xe,r24
.LVL2:
	.loc 1 11 0
	ldi r24,lo8(27)
.L4:
	.loc 1 11 0 is_stmt 0 discriminator 1
	out 0xd,r24
	.loc 1 12 0 is_stmt 1 discriminator 1
	sbis 0xe,6
	rjmp .L4
	.loc 1 13 0
	in r24,0xf
	.loc 1 14 0
	ret
	.cfi_endproc
.LFE1:
	.size	SPITransfer, .-SPITransfer
	.section	.text.SPIWriteBlock,"ax",@progbits
.global	SPIWriteBlock
	.type	SPIWriteBlock, @function
SPIWriteBlock:
.LFB2:
	.loc 1 17 0
	.cfi_startproc
.LVL3:
	push r14
.LCFI0:
	.cfi_def_cfa_offset 3
	.cfi_offset 14, -2
	push r15
.LCFI1:
	.cfi_def_cfa_offset 4
	.cfi_offset 15, -3
	push r17
.LCFI2:
	.cfi_def_cfa_offset 5
	.cfi_offset 17, -4
	push r28
.LCFI3:
	.cfi_def_cfa_offset 6
	.cfi_offset 28, -5
	push r29
.LCFI4:
	.cfi_def_cfa_offset 7
	.cfi_offset 29, -6
	push __zero_reg__
.LCFI5:
	.cfi_def_cfa_offset 8
	in r28,__SP_L__
	in r29,__SP_H__
.LCFI6:
	.cfi_def_cfa_register 28
/* prologue: function */
/* frame size = 1 */
/* stack size = 6 */
.L__stack_usage = 6
.LVL4:
	mov r17,r24
	.loc 1 19 0
	movw r14,r24
.LVL5:
.L7:
	mov r24,r14
	sub r24,r17
	.loc 1 19 0 is_stmt 0 discriminator 1
	cp r24,r22
	brsh .L9
	.loc 1 20 0 is_stmt 1 discriminator 2
	movw r30,r14
	ld r24,Z+
	movw r14,r30
.LVL6:
	std Y+1,r22
	rcall SPITransfer
.LVL7:
	ldd r22,Y+1
	rjmp .L7
.L9:
/* epilogue start */
	.loc 1 22 0
	pop __tmp_reg__
	pop r29
	pop r28
	pop r17
	pop r15
	pop r14
.LVL8:
	ret
	.cfi_endproc
.LFE2:
	.size	SPIWriteBlock, .-SPIWriteBlock
	.section	.text.SPITransferBlock,"ax",@progbits
.global	SPITransferBlock
	.type	SPITransferBlock, @function
SPITransferBlock:
.LFB3:
	.loc 1 25 0
	.cfi_startproc
.LVL9:
	push r12
.LCFI7:
	.cfi_def_cfa_offset 3
	.cfi_offset 12, -2
	push r13
.LCFI8:
	.cfi_def_cfa_offset 4
	.cfi_offset 13, -3
	push r15
.LCFI9:
	.cfi_def_cfa_offset 5
	.cfi_offset 15, -4
	push r16
.LCFI10:
	.cfi_def_cfa_offset 6
	.cfi_offset 16, -5
	push r17
.LCFI11:
	.cfi_def_cfa_offset 7
	.cfi_offset 17, -6
	push r28
.LCFI12:
	.cfi_def_cfa_offset 8
	.cfi_offset 28, -7
	push r29
.LCFI13:
	.cfi_def_cfa_offset 9
	.cfi_offset 29, -8
	push __zero_reg__
.LCFI14:
	.cfi_def_cfa_offset 10
	in r28,__SP_L__
	in r29,__SP_H__
.LCFI15:
	.cfi_def_cfa_register 28
/* prologue: function */
/* frame size = 1 */
/* stack size = 8 */
.L__stack_usage = 8
.LVL10:
	mov r15,r24
	movw r16,r22
	.loc 1 27 0
	movw r12,r24
.LVL11:
.L11:
	mov r24,r12
	sub r24,r15
	.loc 1 27 0 is_stmt 0 discriminator 1
	cp r24,r20
	brsh .L13
	.loc 1 28 0 is_stmt 1 discriminator 2
	movw r30,r12
	ld r24,Z+
	movw r12,r30
.LVL12:
	std Y+1,r20
	rcall SPITransfer
.LVL13:
	movw r30,r16
	st Z+,r24
	movw r16,r30
.LVL14:
	ldd r20,Y+1
	rjmp .L11
.L13:
/* epilogue start */
	.loc 1 30 0
	pop __tmp_reg__
	pop r29
	pop r28
	pop r17
	pop r16
	pop r15
	pop r13
	pop r12
.LVL15:
	ret
	.cfi_endproc
.LFE3:
	.size	SPITransferBlock, .-SPITransferBlock
	.text
.Letext0:
	.file 2 "/usr/lib/avr/include/stdint.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0x15c
	.word	0x2
	.long	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.long	.LASF9
	.byte	0x1
	.long	.LASF10
	.long	.LASF11
	.long	.Ldebug_ranges0+0
	.long	0
	.long	0
	.long	.Ldebug_line0
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.long	.LASF0
	.uleb128 0x3
	.long	.LASF12
	.byte	0x2
	.byte	0x7a
	.long	0x3b
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.long	.LASF1
	.uleb128 0x4
	.byte	0x2
	.byte	0x5
	.string	"int"
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.long	.LASF2
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.long	.LASF3
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.long	.LASF4
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.long	.LASF5
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.long	.LASF6
	.uleb128 0x5
	.byte	0x1
	.long	.LASF13
	.byte	0x1
	.byte	0x3
	.byte	0x1
	.long	.LFB0
	.long	.LFE0
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.byte	0x1
	.uleb128 0x6
	.byte	0x1
	.long	.LASF14
	.byte	0x1
	.byte	0x7
	.byte	0x1
	.long	0x30
	.long	.LFB1
	.long	.LFE1
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.byte	0x1
	.long	0xb0
	.uleb128 0x7
	.long	.LASF7
	.byte	0x1
	.byte	0x7
	.long	0x30
	.long	.LLST0
	.byte	0
	.uleb128 0x8
	.byte	0x1
	.long	.LASF15
	.byte	0x1
	.byte	0x10
	.byte	0x1
	.long	.LFB2
	.long	.LFE2
	.long	.LLST1
	.byte	0x1
	.long	0xff
	.uleb128 0x7
	.long	.LASF7
	.byte	0x1
	.byte	0x10
	.long	0xff
	.long	.LLST2
	.uleb128 0x9
	.string	"len"
	.byte	0x1
	.byte	0x10
	.long	0x30
	.long	.LLST3
	.uleb128 0xa
	.string	"i"
	.byte	0x1
	.byte	0x12
	.long	0x30
	.long	.LLST4
	.uleb128 0xb
	.long	.LVL7
	.long	0x82
	.byte	0
	.uleb128 0xc
	.byte	0x2
	.long	0x30
	.uleb128 0xd
	.byte	0x1
	.long	.LASF16
	.byte	0x1
	.byte	0x18
	.byte	0x1
	.long	.LFB3
	.long	.LFE3
	.long	.LLST5
	.byte	0x1
	.uleb128 0x7
	.long	.LASF7
	.byte	0x1
	.byte	0x18
	.long	0xff
	.long	.LLST6
	.uleb128 0x7
	.long	.LASF8
	.byte	0x1
	.byte	0x18
	.long	0xff
	.long	.LLST7
	.uleb128 0x9
	.string	"len"
	.byte	0x1
	.byte	0x18
	.long	0x30
	.long	.LLST8
	.uleb128 0xa
	.string	"i"
	.byte	0x1
	.byte	0x1a
	.long	0x30
	.long	.LLST9
	.uleb128 0xb
	.long	.LVL13
	.long	0x82
	.byte	0
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x55
	.uleb128 0x6
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x52
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.uleb128 0x2117
	.uleb128 0xc
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x4109
	.byte	0
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x2117
	.uleb128 0xc
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_loc,"",@progbits
.Ldebug_loc0:
.LLST0:
	.long	.LVL0
	.long	.LVL1
	.word	0x1
	.byte	0x68
	.long	.LVL1
	.long	.LVL2
	.word	0x2
	.byte	0x8
	.byte	0x2f
	.long	.LVL2
	.long	.LFE1
	.word	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x68
	.byte	0x9f
	.long	0
	.long	0
.LLST1:
	.long	.LFB2
	.long	.LCFI0
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.long	.LCFI0
	.long	.LCFI1
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 3
	.long	.LCFI1
	.long	.LCFI2
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 4
	.long	.LCFI2
	.long	.LCFI3
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 5
	.long	.LCFI3
	.long	.LCFI4
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 6
	.long	.LCFI4
	.long	.LCFI5
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 7
	.long	.LCFI5
	.long	.LCFI6
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 8
	.long	.LCFI6
	.long	.LFE2
	.word	0x2
	.byte	0x8c
	.sleb128 8
	.long	0
	.long	0
.LLST2:
	.long	.LVL3
	.long	.LVL5
	.word	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.long	.LVL5
	.long	.LFE2
	.word	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x68
	.byte	0x9f
	.long	0
	.long	0
.LLST3:
	.long	.LVL3
	.long	.LVL5
	.word	0x1
	.byte	0x66
	.long	.LVL5
	.long	.LFE2
	.word	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x66
	.byte	0x9f
	.long	0
	.long	0
.LLST4:
	.long	.LVL4
	.long	.LVL5
	.word	0x2
	.byte	0x30
	.byte	0x9f
	.long	.LVL5
	.long	.LVL6
	.word	0x7
	.byte	0x7e
	.sleb128 0
	.byte	0xf3
	.uleb128 0x1
	.byte	0x68
	.byte	0x1c
	.byte	0x9f
	.long	.LVL6
	.long	.LVL7
	.word	0x8
	.byte	0xf3
	.uleb128 0x1
	.byte	0x68
	.byte	0x20
	.byte	0x7e
	.sleb128 0
	.byte	0x22
	.byte	0x9f
	.long	.LVL7
	.long	.LVL8
	.word	0x7
	.byte	0x7e
	.sleb128 0
	.byte	0xf3
	.uleb128 0x1
	.byte	0x68
	.byte	0x1c
	.byte	0x9f
	.long	0
	.long	0
.LLST5:
	.long	.LFB3
	.long	.LCFI7
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.long	.LCFI7
	.long	.LCFI8
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 3
	.long	.LCFI8
	.long	.LCFI9
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 4
	.long	.LCFI9
	.long	.LCFI10
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 5
	.long	.LCFI10
	.long	.LCFI11
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 6
	.long	.LCFI11
	.long	.LCFI12
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 7
	.long	.LCFI12
	.long	.LCFI13
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 8
	.long	.LCFI13
	.long	.LCFI14
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 9
	.long	.LCFI14
	.long	.LCFI15
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 10
	.long	.LCFI15
	.long	.LFE3
	.word	0x2
	.byte	0x8c
	.sleb128 10
	.long	0
	.long	0
.LLST6:
	.long	.LVL9
	.long	.LVL11
	.word	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.long	.LVL11
	.long	.LFE3
	.word	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x68
	.byte	0x9f
	.long	0
	.long	0
.LLST7:
	.long	.LVL9
	.long	.LVL11
	.word	0x6
	.byte	0x66
	.byte	0x93
	.uleb128 0x1
	.byte	0x67
	.byte	0x93
	.uleb128 0x1
	.long	.LVL11
	.long	.LFE3
	.word	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x66
	.byte	0x9f
	.long	0
	.long	0
.LLST8:
	.long	.LVL9
	.long	.LVL11
	.word	0x1
	.byte	0x64
	.long	.LVL11
	.long	.LFE3
	.word	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x64
	.byte	0x9f
	.long	0
	.long	0
.LLST9:
	.long	.LVL10
	.long	.LVL11
	.word	0x2
	.byte	0x30
	.byte	0x9f
	.long	.LVL11
	.long	.LVL12
	.word	0x7
	.byte	0x7c
	.sleb128 0
	.byte	0xf3
	.uleb128 0x1
	.byte	0x68
	.byte	0x1c
	.byte	0x9f
	.long	.LVL12
	.long	.LVL14
	.word	0x8
	.byte	0xf3
	.uleb128 0x1
	.byte	0x68
	.byte	0x20
	.byte	0x7c
	.sleb128 0
	.byte	0x22
	.byte	0x9f
	.long	.LVL14
	.long	.LVL15
	.word	0x7
	.byte	0x7c
	.sleb128 0
	.byte	0xf3
	.uleb128 0x1
	.byte	0x68
	.byte	0x1c
	.byte	0x9f
	.long	0
	.long	0
	.section	.debug_aranges,"",@progbits
	.long	0x34
	.word	0x2
	.long	.Ldebug_info0
	.byte	0x4
	.byte	0
	.word	0
	.word	0
	.long	.LFB0
	.long	.LFE0-.LFB0
	.long	.LFB1
	.long	.LFE1-.LFB1
	.long	.LFB2
	.long	.LFE2-.LFB2
	.long	.LFB3
	.long	.LFE3-.LFB3
	.long	0
	.long	0
	.section	.debug_ranges,"",@progbits
.Ldebug_ranges0:
	.long	.LFB0
	.long	.LFE0
	.long	.LFB1
	.long	.LFE1
	.long	.LFB2
	.long	.LFE2
	.long	.LFB3
	.long	.LFE3
	.long	0
	.long	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF16:
	.string	"SPITransferBlock"
.LASF10:
	.string	"spi.c"
.LASF7:
	.string	"data"
.LASF1:
	.string	"unsigned char"
.LASF4:
	.string	"long unsigned int"
.LASF9:
	.string	"GNU C 4.8.2 -mmcu=attiny84 -mrelax -gdwarf-2 -g2 -Os -std=gnu99 -fshort-enums -fno-inline-small-functions -fpack-struct -fno-strict-aliasing -funsigned-char -funsigned-bitfields -ffunction-sections"
.LASF14:
	.string	"SPITransfer"
.LASF13:
	.string	"SPIInit"
.LASF11:
	.string	"/u5/home/davidm/radio-temp-sensor/src/attiny84"
.LASF2:
	.string	"unsigned int"
.LASF6:
	.string	"long long unsigned int"
.LASF12:
	.string	"uint8_t"
.LASF15:
	.string	"SPIWriteBlock"
.LASF5:
	.string	"long long int"
.LASF8:
	.string	"buffer"
.LASF3:
	.string	"long int"
.LASF0:
	.string	"signed char"
	.ident	"GCC: (GNU) 4.8.2"
