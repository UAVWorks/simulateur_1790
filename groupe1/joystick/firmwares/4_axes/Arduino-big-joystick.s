	.file	"Arduino-big-joystick.c"
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__SREG__ = 0x3f
__tmp_reg__ = 0
__zero_reg__ = 1
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.section	.text.SetupHardware,"ax",@progbits
.global	SetupHardware
	.type	SetupHardware, @function
SetupHardware:
.LFB87:
	.file 1 "Arduino-big-joystick.c"
	.loc 1 63 0
	.cfi_startproc
	push r28
.LCFI0:
	.cfi_def_cfa_offset 3
	.cfi_offset 28, -2
	push r29
.LCFI1:
	.cfi_def_cfa_offset 4
	.cfi_offset 29, -3
/* prologue: function */
/* frame size = 0 */
/* stack size = 2 */
.L__stack_usage = 2
	.loc 1 65 0
	in r24,0x34
	andi r24,lo8(-9)
	out 0x34,r24
	.loc 1 66 0
	ldi r24,lo8(24)
/* #APP */
 ;  66 "Arduino-big-joystick.c" 1
	in __tmp_reg__, __SREG__
	cli
	sts 96, r24
	sts 96, __zero_reg__
	out __SREG__,__tmp_reg__
	
 ;  0 "" 2
.LVL0:
/* #NOAPP */
.LBB50:
.LBB51:
	.file 2 "../../LUFA/Drivers/Peripheral/Serial.h"
	.loc 2 102 0
	ldi r24,lo8(16)
	ldi r25,0
	sts 204+1,r25
	sts 204,r24
	.loc 2 104 0
	ldi r24,lo8(6)
	sts 202,r24
	.loc 2 105 0
	ldi r24,lo8(2)
	sts 200,r24
	.loc 2 106 0
	ldi r28,lo8(-55)
	ldi r29,0
	ldi r24,lo8(24)
	st Y,r24
	.loc 2 108 0
	sbi 0xa,3
	.loc 2 109 0
	sbi 0xb,2
.LBE51:
.LBE50:
.LBB52:
.LBB53:
	.file 3 "./Board/LEDs.h"
	.loc 3 69 0
	in r24,0xa
	ori r24,lo8(48)
	out 0xa,r24
	.loc 3 70 0
	in r24,0xb
	ori r24,lo8(48)
	out 0xb,r24
.LBE53:
.LBE52:
	.loc 1 71 0
	call USB_Init
.LVL1:
	.loc 1 73 0
	ldi r24,lo8(-104)
	st Y,r24
/* epilogue start */
	.loc 1 74 0
	pop r29
	pop r28
	ret
	.cfi_endproc
.LFE87:
	.size	SetupHardware, .-SetupHardware
	.section	.text.startup.main,"ax",@progbits
.global	main
	.type	main, @function
main:
.LFB86:
	.loc 1 40 0
	.cfi_startproc
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	.loc 1 41 0
	call SetupHardware
.LVL2:
.LBB63:
.LBB64:
	.file 4 "Lib/LightweightRingBuff.h"
	.loc 4 87 0
	in r18,__SREG__
.LVL3:
.LBB65:
.LBB66:
	.file 5 "/usr/lib/avr/include/util/atomic.h"
	.loc 5 50 0
/* #APP */
 ;  50 "/usr/lib/avr/include/util/atomic.h" 1
	cli
 ;  0 "" 2
.LVL4:
/* #NOAPP */
.LBE66:
.LBE65:
	.loc 4 89 0
	ldi r24,lo8(USARTtoUSB_Buffer)
	ldi r25,hi8(USARTtoUSB_Buffer)
	sts USARTtoUSB_Buffer+126+1,r25
	sts USARTtoUSB_Buffer+126,r24
	.loc 4 90 0
	sts USARTtoUSB_Buffer+128+1,r25
	sts USARTtoUSB_Buffer+128,r24
.LVL5:
.LBB67:
.LBB68:
	.loc 5 70 0
	out __SREG__,r18
	.loc 5 71 0
.LBE68:
.LBE67:
.LBE64:
.LBE63:
	.loc 1 45 0
/* #APP */
 ;  45 "Arduino-big-joystick.c" 1
	sei
 ;  0 "" 2
.LVL6:
/* #NOAPP */
.L4:
	.loc 1 48 0
	ldi r24,lo8(Joystick_HID_Interface)
	ldi r25,hi8(Joystick_HID_Interface)
	call HID_Device_USBTask
.LVL7:
	.loc 1 49 0
	call USB_USBTask
.LVL8:
	.loc 1 52 0
	lds r24,led1_ticks
	lds r25,led1_ticks+1
	or r24,r25
	breq .L4
	.loc 1 53 0
	lds r24,led1_ticks
	lds r25,led1_ticks+1
	sbiw r24,1
	sts led1_ticks+1,r25
	sts led1_ticks,r24
	.loc 1 54 0
	lds r24,led1_ticks
	lds r25,led1_ticks+1
	or r24,r25
	brne .L4
.LVL9:
.LBB69:
.LBB70:
	.loc 3 80 0
	sbi 0xb,5
	rjmp .L4
.LBE70:
.LBE69:
	.cfi_endproc
.LFE86:
	.size	main, .-main
	.section	.text.EVENT_USB_Device_Connect,"ax",@progbits
.global	EVENT_USB_Device_Connect
	.type	EVENT_USB_Device_Connect, @function
EVENT_USB_Device_Connect:
.LFB88:
	.loc 1 78 0
	.cfi_startproc
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	ret
	.cfi_endproc
.LFE88:
	.size	EVENT_USB_Device_Connect, .-EVENT_USB_Device_Connect
	.section	.text.EVENT_USB_Device_Disconnect,"ax",@progbits
.global	EVENT_USB_Device_Disconnect
	.type	EVENT_USB_Device_Disconnect, @function
EVENT_USB_Device_Disconnect:
.LFB89:
	.loc 1 84 0
	.cfi_startproc
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	ret
	.cfi_endproc
.LFE89:
	.size	EVENT_USB_Device_Disconnect, .-EVENT_USB_Device_Disconnect
	.section	.text.EVENT_USB_Device_ConfigurationChanged,"ax",@progbits
.global	EVENT_USB_Device_ConfigurationChanged
	.type	EVENT_USB_Device_ConfigurationChanged, @function
EVENT_USB_Device_ConfigurationChanged:
.LFB90:
	.loc 1 89 0
	.cfi_startproc
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	.loc 1 90 0
	ldi r24,lo8(Joystick_HID_Interface)
	ldi r25,hi8(Joystick_HID_Interface)
	call HID_Device_ConfigureEndpoints
.LVL10:
.LBB71:
.LBB72:
	.file 6 "../../LUFA/Drivers/USB/HighLevel/../LowLevel/Device.h"
	.loc 6 150 0
	ldi r30,lo8(-30)
	ldi r31,0
	ld r24,Z
	ori r24,lo8(4)
	st Z,r24
	ret
.LBE72:
.LBE71:
	.cfi_endproc
.LFE90:
	.size	EVENT_USB_Device_ConfigurationChanged, .-EVENT_USB_Device_ConfigurationChanged
	.section	.text.EVENT_USB_Device_UnhandledControlRequest,"ax",@progbits
.global	EVENT_USB_Device_UnhandledControlRequest
	.type	EVENT_USB_Device_UnhandledControlRequest, @function
EVENT_USB_Device_UnhandledControlRequest:
.LFB91:
	.loc 1 97 0
	.cfi_startproc
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	.loc 1 98 0
	ldi r24,lo8(Joystick_HID_Interface)
	ldi r25,hi8(Joystick_HID_Interface)
	jmp HID_Device_ProcessControlRequest
.LVL11:
	.cfi_endproc
.LFE91:
	.size	EVENT_USB_Device_UnhandledControlRequest, .-EVENT_USB_Device_UnhandledControlRequest
	.section	.text.EVENT_USB_Device_StartOfFrame,"ax",@progbits
.global	EVENT_USB_Device_StartOfFrame
	.type	EVENT_USB_Device_StartOfFrame, @function
EVENT_USB_Device_StartOfFrame:
.LFB92:
	.loc 1 103 0
	.cfi_startproc
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
.LVL12:
.LBB73:
.LBB74:
	.file 7 "../../LUFA/Drivers/USB/Class/Device/HID.h"
	.loc 7 201 0
	lds r24,Joystick_HID_Interface+11
	lds r25,Joystick_HID_Interface+11+1
	sbiw r24,0
	breq .L13
	.loc 7 202 0
	sbiw r24,1
	sts Joystick_HID_Interface+11+1,r25
	sts Joystick_HID_Interface+11,r24
.L13:
	ret
.LBE74:
.LBE73:
	.cfi_endproc
.LFE92:
	.size	EVENT_USB_Device_StartOfFrame, .-EVENT_USB_Device_StartOfFrame
	.section	.text.CALLBACK_HID_Device_CreateHIDReport,"ax",@progbits
.global	CALLBACK_HID_Device_CreateHIDReport
	.type	CALLBACK_HID_Device_CreateHIDReport, @function
CALLBACK_HID_Device_CreateHIDReport:
.LFB93:
	.loc 1 123 0
	.cfi_startproc
.LVL13:
	push r16
.LCFI2:
	.cfi_def_cfa_offset 3
	.cfi_offset 16, -2
	push r17
.LCFI3:
	.cfi_def_cfa_offset 4
	.cfi_offset 17, -3
	push r28
.LCFI4:
	.cfi_def_cfa_offset 5
	.cfi_offset 28, -4
	push r29
.LCFI5:
	.cfi_def_cfa_offset 6
	.cfi_offset 29, -5
/* prologue: function */
/* frame size = 0 */
/* stack size = 4 */
.L__stack_usage = 4
.LVL14:
.LBB92:
.LBB93:
.LBB94:
	.loc 4 111 0
	in r25,__SREG__
.LVL15:
.LBB95:
.LBB96:
	.loc 5 50 0
/* #APP */
 ;  50 "/usr/lib/avr/include/util/atomic.h" 1
	cli
 ;  0 "" 2
.LVL16:
/* #NOAPP */
.LBE96:
.LBE95:
	.loc 4 113 0
	lds r24,USARTtoUSB_Buffer+130
.LVL17:
.LBB97:
.LBB98:
	.loc 5 70 0
	out __SREG__,r25
	.loc 5 71 0
.LBE98:
.LBE97:
.LBE94:
.LBE93:
.LBE92:
	.loc 1 131 0
	cpi r24,lo8(8)
	brlo .L19
	ldi r28,lo8(joyReport)
	ldi r29,hi8(joyReport)
.LBB99:
.LBB100:
.LBB101:
	.loc 4 187 0
	ldi r24,lo8(USARTtoUSB_Buffer)
	ldi r25,hi8(USARTtoUSB_Buffer)
.LVL18:
.L22:
	.loc 4 184 0 discriminator 2
	lds r30,USARTtoUSB_Buffer+128
	lds r31,USARTtoUSB_Buffer+128+1
	ld r21,Z+
.LVL19:
	.loc 4 186 0 discriminator 2
	sts USARTtoUSB_Buffer+128+1,r31
	sts USARTtoUSB_Buffer+128,r30
	subi r30,lo8(USARTtoUSB_Buffer+126)
	sbci r31,hi8(USARTtoUSB_Buffer+126)
	brne .L20
	.loc 4 187 0
	sts USARTtoUSB_Buffer+128+1,r25
	sts USARTtoUSB_Buffer+128,r24
.L20:
.LBB102:
	.loc 4 189 0
	in r22,__SREG__
.LVL20:
.LBB103:
.LBB104:
	.loc 5 50 0
/* #APP */
 ;  50 "/usr/lib/avr/include/util/atomic.h" 1
	cli
 ;  0 "" 2
.LVL21:
/* #NOAPP */
.LBE104:
.LBE103:
	.loc 4 191 0
	lds r20,USARTtoUSB_Buffer+130
	subi r20,lo8(-(-1))
	sts USARTtoUSB_Buffer+130,r20
.LVL22:
.LBB105:
.LBB106:
	.loc 5 70 0
	out __SREG__,r22
	.loc 5 71 0
.LBE106:
.LBE105:
.LBE102:
.LBE101:
.LBE100:
	.loc 1 134 0
	st Y+,r21
.LVL23:
	.loc 1 133 0
	ldi r30,hi8(joyReport+8)
	cpi r28,lo8(joyReport+8)
	cpc r29,r30
	brne .L22
.LVL24:
.LBB107:
.LBB108:
	.loc 3 75 0
	cbi 0xb,5
.LBE108:
.LBE107:
	.loc 1 138 0
	ldi r24,lo8(-48)
	ldi r25,lo8(7)
	sts led1_ticks+1,r25
	sts led1_ticks,r24
.LVL25:
.L19:
.LBE99:
	.loc 1 141 0
	ldi r24,lo8(8)
	ldi r30,lo8(joyReport)
	ldi r31,hi8(joyReport)
	movw r26,r18
	0:
	ld r0,Z+
	st X+,r0
	dec r24
	brne 0b
	.loc 1 143 0
	ldi r24,lo8(8)
	ldi r25,0
	movw r30,r16
	std Z+1,r25
	st Z,r24
	.loc 1 145 0
	ldi r24,0
/* epilogue start */
	pop r29
	pop r28
	pop r17
	pop r16
.LVL26:
	ret
	.cfi_endproc
.LFE93:
	.size	CALLBACK_HID_Device_CreateHIDReport, .-CALLBACK_HID_Device_CreateHIDReport
	.section	.text.CALLBACK_HID_Device_ProcessHIDReport,"ax",@progbits
.global	CALLBACK_HID_Device_ProcessHIDReport
	.type	CALLBACK_HID_Device_ProcessHIDReport, @function
CALLBACK_HID_Device_ProcessHIDReport:
.LFB94:
	.loc 1 160 0
	.cfi_startproc
.LVL27:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	ret
	.cfi_endproc
.LFE94:
	.size	CALLBACK_HID_Device_ProcessHIDReport, .-CALLBACK_HID_Device_ProcessHIDReport
	.section	.text.__vector_23,"ax",@progbits
.global	__vector_23
	.type	__vector_23, @function
__vector_23:
.LFB95:
	.loc 1 168 0
	.cfi_startproc
	.loc 1 168 0
	push r1
.LCFI6:
	.cfi_def_cfa_offset 3
	.cfi_offset 1, -2
	push r0
.LCFI7:
	.cfi_def_cfa_offset 4
	.cfi_offset 0, -3
	in r0,__SREG__
	push r0
	clr __zero_reg__
	push r18
.LCFI8:
	.cfi_def_cfa_offset 5
	.cfi_offset 18, -4
	push r24
.LCFI9:
	.cfi_def_cfa_offset 6
	.cfi_offset 24, -5
	push r25
.LCFI10:
	.cfi_def_cfa_offset 7
	.cfi_offset 25, -6
	push r30
.LCFI11:
	.cfi_def_cfa_offset 8
	.cfi_offset 30, -7
	push r31
.LCFI12:
	.cfi_def_cfa_offset 9
	.cfi_offset 31, -8
/* prologue: Signal */
/* frame size = 0 */
/* stack size = 8 */
.L__stack_usage = 8
	.loc 1 169 0
	lds r24,206
.LVL28:
	.loc 1 171 0
	in r25,0x1e
	cpi r25,lo8(4)
	brne .L24
.LVL29:
.LBB125:
.LBB126:
.LBB127:
.LBB128:
	.loc 4 111 0
	in r18,__SREG__
.LVL30:
.LBB129:
.LBB130:
	.loc 5 50 0
/* #APP */
 ;  50 "/usr/lib/avr/include/util/atomic.h" 1
	cli
 ;  0 "" 2
.LVL31:
/* #NOAPP */
.LBE130:
.LBE129:
	.loc 4 113 0
	lds r25,USARTtoUSB_Buffer+130
.LVL32:
.LBB131:
.LBB132:
	.loc 5 70 0
	out __SREG__,r18
	.loc 5 71 0
.LBE132:
.LBE131:
.LBE128:
.LBE127:
.LBE126:
.LBE125:
	.loc 1 171 0
	cpi r25,lo8(126)
	breq .L24
.LVL33:
.LBB133:
.LBB134:
	.loc 4 161 0
	lds r30,USARTtoUSB_Buffer+126
	lds r31,USARTtoUSB_Buffer+126+1
	st Z,r24
	.loc 4 163 0
	lds r30,USARTtoUSB_Buffer+126
	lds r31,USARTtoUSB_Buffer+126+1
	movw r24,r30
.LVL34:
	adiw r24,1
	sts USARTtoUSB_Buffer+126+1,r25
	sts USARTtoUSB_Buffer+126,r24
	subi r24,lo8(USARTtoUSB_Buffer+126)
	sbci r25,hi8(USARTtoUSB_Buffer+126)
.LVL35:
	brne .L28
	.loc 4 164 0
	ldi r24,lo8(USARTtoUSB_Buffer)
	ldi r25,hi8(USARTtoUSB_Buffer)
	std Z+2,r25
	std Z+1,r24
.L28:
.LBB135:
	.loc 4 166 0
	in r25,__SREG__
.LVL36:
.LBB136:
.LBB137:
	.loc 5 50 0
/* #APP */
 ;  50 "/usr/lib/avr/include/util/atomic.h" 1
	cli
 ;  0 "" 2
.LVL37:
/* #NOAPP */
.LBE137:
.LBE136:
	.loc 4 168 0
	lds r24,USARTtoUSB_Buffer+130
	subi r24,lo8(-(1))
	sts USARTtoUSB_Buffer+130,r24
.LVL38:
.LBB138:
.LBB139:
	.loc 5 70 0
	out __SREG__,r25
	.loc 5 71 0
.LVL39:
.L24:
/* epilogue start */
.LBE139:
.LBE138:
.LBE135:
.LBE134:
.LBE133:
	.loc 1 175 0
	pop r31
	pop r30
	pop r25
	pop r24
	pop r18
	pop r0
	out __SREG__,r0
	pop r0
	pop r1
	reti
	.cfi_endproc
.LFE95:
	.size	__vector_23, .-__vector_23
.global	led1_ticks
	.section .bss
	.type	led1_ticks, @object
	.size	led1_ticks, 2
led1_ticks:
	.zero	2
.global	joyReport
	.type	joyReport, @object
	.size	joyReport, 8
joyReport:
	.zero	8
	.comm	USARTtoUSB_Buffer,131,1
.global	Joystick_HID_Interface
	.data
	.type	Joystick_HID_Interface, @object
	.size	Joystick_HID_Interface, 13
Joystick_HID_Interface:
	.byte	0
	.byte	1
	.word	8
	.byte	0
	.word	PrevJoystickHIDReportBuffer
	.byte	8
	.zero	5
	.comm	PrevJoystickHIDReportBuffer,8,1
	.text
.Letext0:
	.file 8 "/usr/lib/avr/include/stdint.h"
	.file 9 "Arduino-joystick.h"
	.file 10 "../../LUFA/Drivers/USB/HighLevel/../LowLevel/USBController.h"
	.file 11 "../../LUFA/Drivers/USB/HighLevel/USBTask.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0xa04
	.word	0x2
	.long	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.long	.LASF80
	.byte	0x1
	.long	.LASF81
	.long	.LASF82
	.long	.Ldebug_ranges0+0
	.long	0
	.long	0
	.long	.Ldebug_line0
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.long	.LASF0
	.uleb128 0x3
	.long	.LASF2
	.byte	0x8
	.byte	0x7a
	.long	0x3b
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.long	.LASF1
	.uleb128 0x3
	.long	.LASF3
	.byte	0x8
	.byte	0x7b
	.long	0x4d
	.uleb128 0x4
	.byte	0x2
	.byte	0x5
	.string	"int"
	.uleb128 0x3
	.long	.LASF4
	.byte	0x8
	.byte	0x7c
	.long	0x5f
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.long	.LASF5
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.long	.LASF6
	.uleb128 0x3
	.long	.LASF7
	.byte	0x8
	.byte	0x7e
	.long	0x78
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.long	.LASF8
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.long	.LASF9
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.long	.LASF10
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.long	.LASF11
	.uleb128 0x5
	.long	.LASF83
	.byte	0x1
	.byte	0x6
	.byte	0x72
	.long	0xc5
	.uleb128 0x6
	.long	.LASF12
	.sleb128 0
	.uleb128 0x6
	.long	.LASF13
	.sleb128 1
	.uleb128 0x6
	.long	.LASF14
	.sleb128 2
	.uleb128 0x6
	.long	.LASF15
	.sleb128 3
	.uleb128 0x6
	.long	.LASF16
	.sleb128 4
	.uleb128 0x6
	.long	.LASF17
	.sleb128 5
	.byte	0
	.uleb128 0x7
	.byte	0x2
	.uleb128 0x8
	.byte	0x8
	.byte	0x7
	.byte	0x56
	.long	0x124
	.uleb128 0x9
	.long	.LASF18
	.byte	0x7
	.byte	0x58
	.long	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x9
	.long	.LASF19
	.byte	0x7
	.byte	0x5a
	.long	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0x1
	.uleb128 0x9
	.long	.LASF20
	.byte	0x7
	.byte	0x5b
	.long	0x54
	.byte	0x2
	.byte	0x23
	.uleb128 0x2
	.uleb128 0x9
	.long	.LASF21
	.byte	0x7
	.byte	0x5c
	.long	0x124
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0x9
	.long	.LASF22
	.byte	0x7
	.byte	0x5e
	.long	0xc5
	.byte	0x2
	.byte	0x23
	.uleb128 0x5
	.uleb128 0x9
	.long	.LASF23
	.byte	0x7
	.byte	0x6a
	.long	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0x7
	.byte	0
	.uleb128 0x2
	.byte	0x1
	.byte	0x2
	.long	.LASF24
	.uleb128 0x8
	.byte	0x5
	.byte	0x7
	.byte	0x73
	.long	0x15e
	.uleb128 0x9
	.long	.LASF25
	.byte	0x7
	.byte	0x75
	.long	0x124
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x9
	.long	.LASF26
	.byte	0x7
	.byte	0x76
	.long	0x54
	.byte	0x2
	.byte	0x23
	.uleb128 0x1
	.uleb128 0x9
	.long	.LASF27
	.byte	0x7
	.byte	0x77
	.long	0x54
	.byte	0x2
	.byte	0x23
	.uleb128 0x3
	.byte	0
	.uleb128 0x8
	.byte	0xd
	.byte	0x7
	.byte	0x54
	.long	0x183
	.uleb128 0x9
	.long	.LASF28
	.byte	0x7
	.byte	0x70
	.long	0x183
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x9
	.long	.LASF29
	.byte	0x7
	.byte	0x79
	.long	0x12b
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.byte	0
	.uleb128 0xa
	.long	0xc7
	.uleb128 0x3
	.long	.LASF30
	.byte	0x7
	.byte	0x7c
	.long	0x15e
	.uleb128 0x8
	.byte	0x83
	.byte	0x4
	.byte	0x46
	.long	0x1d5
	.uleb128 0x9
	.long	.LASF31
	.byte	0x4
	.byte	0x48
	.long	0x1d5
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0xb
	.string	"In"
	.byte	0x4
	.byte	0x49
	.long	0x1e5
	.byte	0x2
	.byte	0x23
	.uleb128 0x7e
	.uleb128 0xb
	.string	"Out"
	.byte	0x4
	.byte	0x4a
	.long	0x1e5
	.byte	0x3
	.byte	0x23
	.uleb128 0x80
	.uleb128 0x9
	.long	.LASF32
	.byte	0x4
	.byte	0x4b
	.long	0x30
	.byte	0x3
	.byte	0x23
	.uleb128 0x82
	.byte	0
	.uleb128 0xc
	.long	0x30
	.long	0x1e5
	.uleb128 0xd
	.long	0x8d
	.byte	0x7d
	.byte	0
	.uleb128 0xe
	.byte	0x2
	.long	0x30
	.uleb128 0x3
	.long	.LASF33
	.byte	0x4
	.byte	0x4c
	.long	0x193
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.long	.LASF34
	.uleb128 0x8
	.byte	0x8
	.byte	0x9
	.byte	0x17
	.long	0x214
	.uleb128 0x9
	.long	.LASF35
	.byte	0x9
	.byte	0x18
	.long	0x214
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.byte	0
	.uleb128 0xc
	.long	0x42
	.long	0x224
	.uleb128 0xd
	.long	0x8d
	.byte	0x3
	.byte	0
	.uleb128 0x3
	.long	.LASF36
	.byte	0x9
	.byte	0x19
	.long	0x1fd
	.uleb128 0xf
	.long	.LASF39
	.byte	0x5
	.byte	0x44
	.byte	0x1
	.byte	0x3
	.long	0x248
	.uleb128 0x10
	.string	"__s"
	.byte	0x5
	.byte	0x44
	.long	0x248
	.byte	0
	.uleb128 0xe
	.byte	0x2
	.long	0x24e
	.uleb128 0xa
	.long	0x30
	.uleb128 0x11
	.long	.LASF84
	.byte	0x5
	.byte	0x30
	.byte	0x1
	.long	0x30
	.byte	0x3
	.uleb128 0x12
	.long	.LASF43
	.byte	0x4
	.byte	0x6b
	.byte	0x1
	.long	0x30
	.byte	0x3
	.long	0x2a0
	.uleb128 0x13
	.long	.LASF31
	.byte	0x4
	.byte	0x6b
	.long	0x2a0
	.uleb128 0x14
	.long	.LASF32
	.byte	0x4
	.byte	0x6d
	.long	0x30
	.uleb128 0x15
	.uleb128 0x14
	.long	.LASF37
	.byte	0x4
	.byte	0x6f
	.long	0x30
	.uleb128 0x14
	.long	.LASF38
	.byte	0x4
	.byte	0x6f
	.long	0x30
	.byte	0
	.byte	0
	.uleb128 0xa
	.long	0x2a5
	.uleb128 0xe
	.byte	0x2
	.long	0x1eb
	.uleb128 0x16
	.long	.LASF54
	.byte	0x6
	.byte	0x94
	.byte	0x1
	.byte	0x3
	.uleb128 0xf
	.long	.LASF40
	.byte	0x7
	.byte	0xc7
	.byte	0x1
	.byte	0x3
	.long	0x2cd
	.uleb128 0x13
	.long	.LASF41
	.byte	0x7
	.byte	0xc7
	.long	0x2cd
	.byte	0
	.uleb128 0xa
	.long	0x2d2
	.uleb128 0xe
	.byte	0x2
	.long	0x188
	.uleb128 0xf
	.long	.LASF42
	.byte	0x4
	.byte	0x55
	.byte	0x1
	.byte	0x3
	.long	0x309
	.uleb128 0x13
	.long	.LASF31
	.byte	0x4
	.byte	0x55
	.long	0x2a0
	.uleb128 0x15
	.uleb128 0x14
	.long	.LASF37
	.byte	0x4
	.byte	0x57
	.long	0x30
	.uleb128 0x14
	.long	.LASF38
	.byte	0x4
	.byte	0x57
	.long	0x30
	.byte	0
	.byte	0
	.uleb128 0x12
	.long	.LASF44
	.byte	0x4
	.byte	0x7f
	.byte	0x1
	.long	0x124
	.byte	0x3
	.long	0x326
	.uleb128 0x13
	.long	.LASF31
	.byte	0x4
	.byte	0x7f
	.long	0x2a0
	.byte	0
	.uleb128 0xf
	.long	.LASF45
	.byte	0x4
	.byte	0x9e
	.byte	0x1
	.byte	0x3
	.long	0x362
	.uleb128 0x13
	.long	.LASF31
	.byte	0x4
	.byte	0x9e
	.long	0x2a0
	.uleb128 0x13
	.long	.LASF46
	.byte	0x4
	.byte	0x9f
	.long	0x24e
	.uleb128 0x15
	.uleb128 0x14
	.long	.LASF37
	.byte	0x4
	.byte	0xa6
	.long	0x30
	.uleb128 0x14
	.long	.LASF38
	.byte	0x4
	.byte	0xa6
	.long	0x30
	.byte	0
	.byte	0
	.uleb128 0x12
	.long	.LASF47
	.byte	0x4
	.byte	0xb6
	.byte	0x1
	.long	0x30
	.byte	0x3
	.long	0x3a2
	.uleb128 0x13
	.long	.LASF31
	.byte	0x4
	.byte	0xb6
	.long	0x2a0
	.uleb128 0x14
	.long	.LASF46
	.byte	0x4
	.byte	0xb8
	.long	0x30
	.uleb128 0x15
	.uleb128 0x14
	.long	.LASF37
	.byte	0x4
	.byte	0xbd
	.long	0x30
	.uleb128 0x14
	.long	.LASF38
	.byte	0x4
	.byte	0xbd
	.long	0x30
	.byte	0
	.byte	0
	.uleb128 0xf
	.long	.LASF48
	.byte	0x3
	.byte	0x49
	.byte	0x1
	.byte	0x3
	.long	0x3bb
	.uleb128 0x13
	.long	.LASF49
	.byte	0x3
	.byte	0x49
	.long	0x24e
	.byte	0
	.uleb128 0xf
	.long	.LASF50
	.byte	0x3
	.byte	0x4e
	.byte	0x1
	.byte	0x3
	.long	0x3d4
	.uleb128 0x13
	.long	.LASF49
	.byte	0x3
	.byte	0x4e
	.long	0x24e
	.byte	0
	.uleb128 0xf
	.long	.LASF51
	.byte	0x2
	.byte	0x63
	.byte	0x1
	.byte	0x3
	.long	0x3f8
	.uleb128 0x13
	.long	.LASF52
	.byte	0x2
	.byte	0x63
	.long	0x3f8
	.uleb128 0x13
	.long	.LASF53
	.byte	0x2
	.byte	0x64
	.long	0x3fd
	.byte	0
	.uleb128 0xa
	.long	0x6d
	.uleb128 0xa
	.long	0x124
	.uleb128 0x16
	.long	.LASF55
	.byte	0x3
	.byte	0x43
	.byte	0x1
	.byte	0x3
	.uleb128 0x17
	.byte	0x1
	.long	.LASF58
	.byte	0x1
	.byte	0x3e
	.byte	0x1
	.long	.LFB87
	.long	.LFE87
	.long	.LLST0
	.byte	0x1
	.long	0x461
	.uleb128 0x18
	.long	0x3d4
	.long	.LBB50
	.long	.LBE50
	.byte	0x1
	.byte	0x45
	.long	0x448
	.uleb128 0x19
	.long	0x3e1
	.long	0x1c200
	.uleb128 0x1a
	.long	0x3ec
	.byte	0x1
	.byte	0
	.uleb128 0x1b
	.long	0x402
	.long	.LBB52
	.long	.LBE52
	.byte	0x1
	.byte	0x46
	.uleb128 0x1c
	.long	.LVL1
	.long	0x9b6
	.byte	0
	.uleb128 0x1d
	.byte	0x1
	.long	.LASF62
	.byte	0x1
	.byte	0x27
	.byte	0x1
	.long	0x4d
	.long	.LFB86
	.long	.LFE86
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.byte	0x1
	.long	0x52f
	.uleb128 0x18
	.long	0x2d8
	.long	.LBB63
	.long	.LBE63
	.byte	0x1
	.byte	0x2b
	.long	0x4e6
	.uleb128 0x1e
	.long	0x2e5
	.byte	0x6
	.byte	0x3
	.long	USARTtoUSB_Buffer
	.byte	0x9f
	.uleb128 0x1f
	.long	.LBB64
	.long	.LBE64
	.uleb128 0x20
	.long	0x2f1
	.long	.LLST1
	.uleb128 0x20
	.long	0x2fc
	.long	.LLST2
	.uleb128 0x1b
	.long	0x253
	.long	.LBB65
	.long	.LBE65
	.byte	0x4
	.byte	0x57
	.uleb128 0x21
	.long	0x22f
	.long	.LBB67
	.long	.LBE67
	.byte	0x4
	.byte	0x57
	.uleb128 0x1e
	.long	0x23c
	.byte	0x6
	.byte	0xf2
	.long	.Ldebug_info0+1191
	.sleb128 0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x18
	.long	0x3bb
	.long	.LBB69
	.long	.LBE69
	.byte	0x1
	.byte	0x37
	.long	0x500
	.uleb128 0x1a
	.long	0x3c8
	.byte	0x20
	.byte	0
	.uleb128 0x1c
	.long	.LVL2
	.long	0x40b
	.uleb128 0x22
	.long	.LVL7
	.long	0x9c1
	.long	0x525
	.uleb128 0x23
	.byte	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.byte	0x5
	.byte	0x3
	.long	Joystick_HID_Interface
	.byte	0
	.uleb128 0x1c
	.long	.LVL8
	.long	0x9d5
	.byte	0
	.uleb128 0x24
	.byte	0x1
	.long	.LASF56
	.byte	0x1
	.byte	0x4d
	.byte	0x1
	.long	.LFB88
	.long	.LFE88
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.byte	0x1
	.uleb128 0x24
	.byte	0x1
	.long	.LASF57
	.byte	0x1
	.byte	0x53
	.byte	0x1
	.long	.LFB89
	.long	.LFE89
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.byte	0x1
	.uleb128 0x25
	.byte	0x1
	.long	.LASF59
	.byte	0x1
	.byte	0x58
	.byte	0x1
	.long	.LFB90
	.long	.LFE90
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.byte	0x1
	.long	0x59d
	.uleb128 0x1b
	.long	0x2ab
	.long	.LBB71
	.long	.LBE71
	.byte	0x1
	.byte	0x5c
	.uleb128 0x26
	.long	.LVL10
	.long	0x9df
	.uleb128 0x23
	.byte	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.byte	0x5
	.byte	0x3
	.long	Joystick_HID_Interface
	.byte	0
	.byte	0
	.uleb128 0x25
	.byte	0x1
	.long	.LASF60
	.byte	0x1
	.byte	0x60
	.byte	0x1
	.long	.LFB91
	.long	.LFE91
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.byte	0x1
	.long	0x5d1
	.uleb128 0x27
	.long	.LVL11
	.byte	0x1
	.long	0x9f7
	.uleb128 0x23
	.byte	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.byte	0x5
	.byte	0x3
	.long	Joystick_HID_Interface
	.byte	0
	.byte	0
	.uleb128 0x25
	.byte	0x1
	.long	.LASF61
	.byte	0x1
	.byte	0x66
	.byte	0x1
	.long	.LFB92
	.long	.LFE92
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.byte	0x1
	.long	0x608
	.uleb128 0x21
	.long	0x2b4
	.long	.LBB73
	.long	.LBE73
	.byte	0x1
	.byte	0x68
	.uleb128 0x1e
	.long	0x2c1
	.byte	0x6
	.byte	0x3
	.long	Joystick_HID_Interface
	.byte	0x9f
	.byte	0
	.byte	0
	.uleb128 0x28
	.byte	0x1
	.long	.LASF63
	.byte	0x1
	.byte	0x75
	.byte	0x1
	.long	0x124
	.long	.LFB93
	.long	.LFE93
	.long	.LLST3
	.byte	0x1
	.long	0x7a9
	.uleb128 0x29
	.long	.LASF41
	.byte	0x1
	.byte	0x76
	.long	0x2cd
	.long	.LLST4
	.uleb128 0x29
	.long	.LASF64
	.byte	0x1
	.byte	0x77
	.long	0x7a9
	.long	.LLST5
	.uleb128 0x29
	.long	.LASF65
	.byte	0x1
	.byte	0x78
	.long	0x24e
	.long	.LLST6
	.uleb128 0x2a
	.long	.LASF66
	.byte	0x1
	.byte	0x79
	.long	0xc5
	.byte	0x6
	.byte	0x62
	.byte	0x93
	.uleb128 0x1
	.byte	0x63
	.byte	0x93
	.uleb128 0x1
	.uleb128 0x29
	.long	.LASF67
	.byte	0x1
	.byte	0x7a
	.long	0x7ae
	.long	.LLST7
	.uleb128 0x2b
	.long	.LASF69
	.byte	0x1
	.byte	0x7c
	.long	0x7b9
	.byte	0x6
	.byte	0x62
	.byte	0x93
	.uleb128 0x1
	.byte	0x63
	.byte	0x93
	.uleb128 0x1
	.uleb128 0x14
	.long	.LASF68
	.byte	0x1
	.byte	0x7e
	.long	0x30
	.uleb128 0x18
	.long	0x260
	.long	.LBB92
	.long	.LBE92
	.byte	0x1
	.byte	0x7e
	.long	0x706
	.uleb128 0x1e
	.long	0x271
	.byte	0x6
	.byte	0x3
	.long	USARTtoUSB_Buffer
	.byte	0x9f
	.uleb128 0x1f
	.long	.LBB93
	.long	.LBE93
	.uleb128 0x20
	.long	0x27c
	.long	.LLST8
	.uleb128 0x1f
	.long	.LBB94
	.long	.LBE94
	.uleb128 0x2c
	.long	0x288
	.byte	0x1
	.byte	0x69
	.uleb128 0x20
	.long	0x293
	.long	.LLST9
	.uleb128 0x1b
	.long	0x253
	.long	.LBB95
	.long	.LBE95
	.byte	0x4
	.byte	0x6f
	.uleb128 0x21
	.long	0x22f
	.long	.LBB97
	.long	.LBE97
	.byte	0x4
	.byte	0x6f
	.uleb128 0x2d
	.long	0x23c
	.long	.LLST10
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x1f
	.long	.LBB99
	.long	.LBE99
	.uleb128 0x2e
	.string	"ind"
	.byte	0x1
	.byte	0x84
	.long	0x30
	.long	.LLST11
	.uleb128 0x18
	.long	0x362
	.long	.LBB100
	.long	.LBE100
	.byte	0x1
	.byte	0x86
	.long	0x78e
	.uleb128 0x2f
	.long	0x373
	.uleb128 0x1f
	.long	.LBB101
	.long	.LBE101
	.uleb128 0x20
	.long	0x37e
	.long	.LLST12
	.uleb128 0x1f
	.long	.LBB102
	.long	.LBE102
	.uleb128 0x20
	.long	0x38a
	.long	.LLST13
	.uleb128 0x20
	.long	0x395
	.long	.LLST14
	.uleb128 0x1b
	.long	0x253
	.long	.LBB103
	.long	.LBE103
	.byte	0x4
	.byte	0xbd
	.uleb128 0x21
	.long	0x22f
	.long	.LBB105
	.long	.LBE105
	.byte	0x4
	.byte	0xbd
	.uleb128 0x2d
	.long	0x23c
	.long	.LLST15
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x21
	.long	0x3a2
	.long	.LBB107
	.long	.LBE107
	.byte	0x1
	.byte	0x89
	.uleb128 0x2d
	.long	0x3af
	.long	.LLST16
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0xa
	.long	0x1e5
	.uleb128 0xa
	.long	0x7b3
	.uleb128 0xe
	.byte	0x2
	.long	0x54
	.uleb128 0xe
	.byte	0x2
	.long	0x224
	.uleb128 0x25
	.byte	0x1
	.long	.LASF70
	.byte	0x1
	.byte	0x9b
	.byte	0x1
	.long	.LFB94
	.long	.LFE94
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.byte	0x1
	.long	0x82a
	.uleb128 0x2a
	.long	.LASF41
	.byte	0x1
	.byte	0x9b
	.long	0x2cd
	.byte	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.uleb128 0x2a
	.long	.LASF64
	.byte	0x1
	.byte	0x9c
	.long	0x24e
	.byte	0x1
	.byte	0x66
	.uleb128 0x2a
	.long	.LASF65
	.byte	0x1
	.byte	0x9d
	.long	0x24e
	.byte	0x1
	.byte	0x64
	.uleb128 0x2a
	.long	.LASF66
	.byte	0x1
	.byte	0x9e
	.long	0x82a
	.byte	0x6
	.byte	0x62
	.byte	0x93
	.uleb128 0x1
	.byte	0x63
	.byte	0x93
	.uleb128 0x1
	.uleb128 0x2a
	.long	.LASF67
	.byte	0x1
	.byte	0x9f
	.long	0x831
	.byte	0x6
	.byte	0x60
	.byte	0x93
	.uleb128 0x1
	.byte	0x61
	.byte	0x93
	.uleb128 0x1
	.byte	0
	.uleb128 0xe
	.byte	0x2
	.long	0x830
	.uleb128 0x30
	.uleb128 0xa
	.long	0x54
	.uleb128 0x17
	.byte	0x1
	.long	.LASF71
	.byte	0x1
	.byte	0xa7
	.byte	0x1
	.long	.LFB95
	.long	.LFE95
	.long	.LLST17
	.byte	0x1
	.long	0x947
	.uleb128 0x31
	.long	.LASF72
	.byte	0x1
	.byte	0xa9
	.long	0x30
	.long	.LLST18
	.uleb128 0x18
	.long	0x309
	.long	.LBB125
	.long	.LBE125
	.byte	0x1
	.byte	0xac
	.long	0x8e4
	.uleb128 0x2f
	.long	0x31a
	.uleb128 0x21
	.long	0x260
	.long	.LBB126
	.long	.LBE126
	.byte	0x4
	.byte	0x81
	.uleb128 0x2f
	.long	0x271
	.uleb128 0x1f
	.long	.LBB127
	.long	.LBE127
	.uleb128 0x20
	.long	0x27c
	.long	.LLST19
	.uleb128 0x1f
	.long	.LBB128
	.long	.LBE128
	.uleb128 0x20
	.long	0x288
	.long	.LLST20
	.uleb128 0x20
	.long	0x293
	.long	.LLST21
	.uleb128 0x1b
	.long	0x253
	.long	.LBB129
	.long	.LBE129
	.byte	0x4
	.byte	0x6f
	.uleb128 0x21
	.long	0x22f
	.long	.LBB131
	.long	.LBE131
	.byte	0x4
	.byte	0x6f
	.uleb128 0x2d
	.long	0x23c
	.long	.LLST22
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x21
	.long	0x326
	.long	.LBB133
	.long	.LBE133
	.byte	0x1
	.byte	0xad
	.uleb128 0x2f
	.long	0x333
	.uleb128 0x2d
	.long	0x33e
	.long	.LLST23
	.uleb128 0x1f
	.long	.LBB135
	.long	.LBE135
	.uleb128 0x20
	.long	0x34a
	.long	.LLST24
	.uleb128 0x20
	.long	0x355
	.long	.LLST25
	.uleb128 0x1b
	.long	0x253
	.long	.LBB136
	.long	.LBE136
	.byte	0x4
	.byte	0xa6
	.uleb128 0x21
	.long	0x22f
	.long	.LBB138
	.long	.LBE138
	.byte	0x4
	.byte	0xa6
	.uleb128 0x2d
	.long	0x23c
	.long	.LLST26
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0xc
	.long	0x30
	.long	0x957
	.uleb128 0xd
	.long	0x8d
	.byte	0x7
	.byte	0
	.uleb128 0x32
	.long	.LASF73
	.byte	0x1
	.byte	0x4
	.long	0x947
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.long	PrevJoystickHIDReportBuffer
	.uleb128 0x32
	.long	.LASF74
	.byte	0x1
	.byte	0xa
	.long	0x188
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.long	Joystick_HID_Interface
	.uleb128 0x32
	.long	.LASF75
	.byte	0x1
	.byte	0x1d
	.long	0x1eb
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.long	USARTtoUSB_Buffer
	.uleb128 0x32
	.long	.LASF76
	.byte	0x1
	.byte	0x1f
	.long	0x224
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.long	joyReport
	.uleb128 0x32
	.long	.LASF77
	.byte	0x1
	.byte	0x22
	.long	0x9b1
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.long	led1_ticks
	.uleb128 0x33
	.long	0x4d
	.uleb128 0x34
	.byte	0x1
	.long	.LASF78
	.byte	0xa
	.word	0x123
	.byte	0x1
	.byte	0x1
	.uleb128 0x35
	.byte	0x1
	.long	.LASF85
	.byte	0x7
	.byte	0x95
	.byte	0x1
	.byte	0x1
	.long	0x9d5
	.uleb128 0x36
	.long	0x2cd
	.byte	0
	.uleb128 0x37
	.byte	0x1
	.long	.LASF79
	.byte	0xb
	.byte	0xb2
	.byte	0x1
	.byte	0x1
	.uleb128 0x38
	.byte	0x1
	.long	.LASF86
	.byte	0x7
	.byte	0x87
	.byte	0x1
	.long	0x124
	.byte	0x1
	.long	0x9f7
	.uleb128 0x36
	.long	0x2cd
	.byte	0
	.uleb128 0x39
	.byte	0x1
	.long	.LASF87
	.byte	0x7
	.byte	0x8e
	.byte	0x1
	.byte	0x1
	.uleb128 0x36
	.long	0x2cd
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
	.uleb128 0x4
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xd
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x13
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x20
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x10
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
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x2e
	.byte	0
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
	.uleb128 0x20
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0x2e
	.byte	0x1
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
	.uleb128 0x20
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x13
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
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0x34
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
	.uleb128 0x15
	.uleb128 0xb
	.byte	0x1
	.byte	0
	.byte	0
	.uleb128 0x16
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x20
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x17
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
	.uleb128 0x18
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x19
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x1c
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x1a
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x1b
	.uleb128 0x1d
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x1c
	.uleb128 0x4109
	.byte	0
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1d
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
	.uleb128 0x1e
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x1f
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.byte	0
	.byte	0
	.uleb128 0x20
	.uleb128 0x34
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x21
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x22
	.uleb128 0x4109
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x23
	.uleb128 0x410a
	.byte	0
	.uleb128 0x2
	.uleb128 0xa
	.uleb128 0x2111
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x24
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
	.uleb128 0x25
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
	.uleb128 0xa
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x26
	.uleb128 0x4109
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x27
	.uleb128 0x4109
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x2115
	.uleb128 0xc
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x28
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
	.uleb128 0x6
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x29
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
	.uleb128 0x2a
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
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x2b
	.uleb128 0x34
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
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x2c
	.uleb128 0x34
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x2d
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x2e
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
	.uleb128 0x2f
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x30
	.uleb128 0x26
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x31
	.uleb128 0x34
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
	.uleb128 0x32
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x33
	.uleb128 0x35
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x34
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
	.byte	0
	.byte	0
	.uleb128 0x35
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
	.uleb128 0x3c
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x36
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x37
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
	.uleb128 0x3c
	.uleb128 0xc
	.byte	0
	.byte	0
	.uleb128 0x38
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
	.uleb128 0x3c
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x39
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
	.uleb128 0x3c
	.uleb128 0xc
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_loc,"",@progbits
.Ldebug_loc0:
.LLST0:
	.long	.LFB87
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
	.long	.LFE87
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 4
	.long	0
	.long	0
.LLST1:
	.long	.LVL3
	.long	.LVL6
	.word	0x1
	.byte	0x62
	.long	0
	.long	0
.LLST2:
	.long	.LVL4
	.long	.LVL5
	.word	0x2
	.byte	0x31
	.byte	0x9f
	.long	.LVL5
	.long	.LFE86
	.word	0x2
	.byte	0x30
	.byte	0x9f
	.long	0
	.long	0
.LLST3:
	.long	.LFB93
	.long	.LCFI2
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.long	.LCFI2
	.long	.LCFI3
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 3
	.long	.LCFI3
	.long	.LCFI4
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 4
	.long	.LCFI4
	.long	.LCFI5
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 5
	.long	.LCFI5
	.long	.LFE93
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 6
	.long	0
	.long	0
.LLST4:
	.long	.LVL13
	.long	.LVL17
	.word	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.long	.LVL17
	.long	.LFE93
	.word	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x68
	.byte	0x9f
	.long	0
	.long	0
.LLST5:
	.long	.LVL13
	.long	.LVL18
	.word	0x6
	.byte	0x66
	.byte	0x93
	.uleb128 0x1
	.byte	0x67
	.byte	0x93
	.uleb128 0x1
	.long	.LVL18
	.long	.LFE93
	.word	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x66
	.byte	0x9f
	.long	0
	.long	0
.LLST6:
	.long	.LVL13
	.long	.LVL18
	.word	0x1
	.byte	0x64
	.long	.LVL18
	.long	.LFE93
	.word	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x64
	.byte	0x9f
	.long	0
	.long	0
.LLST7:
	.long	.LVL13
	.long	.LVL26
	.word	0x6
	.byte	0x60
	.byte	0x93
	.uleb128 0x1
	.byte	0x61
	.byte	0x93
	.uleb128 0x1
	.long	.LVL26
	.long	.LFE93
	.word	0x6
	.byte	0x6e
	.byte	0x93
	.uleb128 0x1
	.byte	0x6f
	.byte	0x93
	.uleb128 0x1
	.long	0
	.long	0
.LLST8:
	.long	.LVL17
	.long	.LVL18
	.word	0x1
	.byte	0x68
	.long	0
	.long	0
.LLST9:
	.long	.LVL16
	.long	.LVL17
	.word	0x2
	.byte	0x31
	.byte	0x9f
	.long	.LVL17
	.long	.LFE93
	.word	0x2
	.byte	0x30
	.byte	0x9f
	.long	0
	.long	0
.LLST10:
	.long	.LVL17
	.long	.LVL18
	.word	0x6
	.byte	0xf2
	.long	.Ldebug_info0+1739
	.sleb128 0
	.long	.LVL22
	.long	.LVL25
	.word	0x6
	.byte	0xf2
	.long	.Ldebug_info0+1873
	.sleb128 0
	.long	0
	.long	0
.LLST11:
	.long	.LVL18
	.long	.LVL25
	.word	0x9
	.byte	0x8c
	.sleb128 0
	.byte	0x3
	.long	joyReport
	.byte	0x1c
	.byte	0x9f
	.long	0
	.long	0
.LLST12:
	.long	.LVL19
	.long	.LVL25
	.word	0x1
	.byte	0x65
	.long	0
	.long	0
.LLST13:
	.long	.LVL20
	.long	.LVL25
	.word	0x1
	.byte	0x66
	.long	0
	.long	0
.LLST14:
	.long	.LVL21
	.long	.LVL22
	.word	0x2
	.byte	0x31
	.byte	0x9f
	.long	.LVL22
	.long	.LVL25
	.word	0x2
	.byte	0x30
	.byte	0x9f
	.long	0
	.long	0
.LLST15:
	.long	.LVL22
	.long	.LVL25
	.word	0x6
	.byte	0xf2
	.long	.Ldebug_info0+1873
	.sleb128 0
	.long	0
	.long	0
.LLST16:
	.long	.LVL24
	.long	.LVL25
	.word	0x3
	.byte	0x8
	.byte	0x20
	.byte	0x9f
	.long	0
	.long	0
.LLST17:
	.long	.LFB95
	.long	.LCFI6
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.long	.LCFI6
	.long	.LCFI7
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 3
	.long	.LCFI7
	.long	.LCFI8
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 4
	.long	.LCFI8
	.long	.LCFI9
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 5
	.long	.LCFI9
	.long	.LCFI10
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 6
	.long	.LCFI10
	.long	.LCFI11
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 7
	.long	.LCFI11
	.long	.LCFI12
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 8
	.long	.LCFI12
	.long	.LFE95
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 9
	.long	0
	.long	0
.LLST18:
	.long	.LVL28
	.long	.LVL34
	.word	0x1
	.byte	0x68
	.long	0
	.long	0
.LLST19:
	.long	.LVL32
	.long	.LVL36
	.word	0x1
	.byte	0x69
	.long	0
	.long	0
.LLST20:
	.long	.LVL30
	.long	.LVL35
	.word	0x1
	.byte	0x62
	.long	0
	.long	0
.LLST21:
	.long	.LVL31
	.long	.LVL32
	.word	0x2
	.byte	0x31
	.byte	0x9f
	.long	.LVL32
	.long	.LVL39
	.word	0x2
	.byte	0x30
	.byte	0x9f
	.long	0
	.long	0
.LLST22:
	.long	.LVL32
	.long	.LVL38
	.word	0x6
	.byte	0xf2
	.long	.Ldebug_info0+2214
	.sleb128 0
	.long	.LVL38
	.long	.LVL39
	.word	0x6
	.byte	0xf2
	.long	.Ldebug_info0+2314
	.sleb128 0
	.long	0
	.long	0
.LLST23:
	.long	.LVL33
	.long	.LVL34
	.word	0x1
	.byte	0x68
	.long	0
	.long	0
.LLST24:
	.long	.LVL36
	.long	.LVL39
	.word	0x1
	.byte	0x69
	.long	0
	.long	0
.LLST25:
	.long	.LVL37
	.long	.LVL38
	.word	0x2
	.byte	0x31
	.byte	0x9f
	.long	.LVL38
	.long	.LVL39
	.word	0x2
	.byte	0x30
	.byte	0x9f
	.long	0
	.long	0
.LLST26:
	.long	.LVL38
	.long	.LVL39
	.word	0x6
	.byte	0xf2
	.long	.Ldebug_info0+2314
	.sleb128 0
	.long	0
	.long	0
	.section	.debug_aranges,"",@progbits
	.long	0x64
	.word	0x2
	.long	.Ldebug_info0
	.byte	0x4
	.byte	0
	.word	0
	.word	0
	.long	.LFB87
	.long	.LFE87-.LFB87
	.long	.LFB86
	.long	.LFE86-.LFB86
	.long	.LFB88
	.long	.LFE88-.LFB88
	.long	.LFB89
	.long	.LFE89-.LFB89
	.long	.LFB90
	.long	.LFE90-.LFB90
	.long	.LFB91
	.long	.LFE91-.LFB91
	.long	.LFB92
	.long	.LFE92-.LFB92
	.long	.LFB93
	.long	.LFE93-.LFB93
	.long	.LFB94
	.long	.LFE94-.LFB94
	.long	.LFB95
	.long	.LFE95-.LFB95
	.long	0
	.long	0
	.section	.debug_ranges,"",@progbits
.Ldebug_ranges0:
	.long	.LFB87
	.long	.LFE87
	.long	.LFB86
	.long	.LFE86
	.long	.LFB88
	.long	.LFE88
	.long	.LFB89
	.long	.LFE89
	.long	.LFB90
	.long	.LFE90
	.long	.LFB91
	.long	.LFE91
	.long	.LFB92
	.long	.LFE92
	.long	.LFB93
	.long	.LFE93
	.long	.LFB94
	.long	.LFE94
	.long	.LFB95
	.long	.LFE95
	.long	0
	.long	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF47:
	.string	"RingBuffer_Remove"
.LASF55:
	.string	"LEDs_Init"
.LASF84:
	.string	"__iCliRetVal"
.LASF30:
	.string	"USB_ClassInfo_HID_Device_t"
.LASF71:
	.string	"__vector_23"
.LASF36:
	.string	"USB_JoystickReport_Data_t"
.LASF23:
	.string	"PrevReportINBufferSize"
.LASF10:
	.string	"long long unsigned int"
.LASF21:
	.string	"ReportINEndpointDoubleBank"
.LASF12:
	.string	"DEVICE_STATE_Unattached"
.LASF14:
	.string	"DEVICE_STATE_Default"
.LASF40:
	.string	"HID_Device_MillisecondElapsed"
.LASF3:
	.string	"int16_t"
.LASF9:
	.string	"long long int"
.LASF0:
	.string	"signed char"
.LASF52:
	.string	"BaudRate"
.LASF77:
	.string	"led1_ticks"
.LASF66:
	.string	"ReportData"
.LASF51:
	.string	"Serial_Init"
.LASF54:
	.string	"USB_Device_EnableSOFEvents"
.LASF6:
	.string	"long int"
.LASF60:
	.string	"EVENT_USB_Device_UnhandledControlRequest"
.LASF4:
	.string	"uint16_t"
.LASF83:
	.string	"USB_Device_States_t"
.LASF81:
	.string	"Arduino-big-joystick.c"
.LASF61:
	.string	"EVENT_USB_Device_StartOfFrame"
.LASF86:
	.string	"HID_Device_ConfigureEndpoints"
.LASF49:
	.string	"LEDMask"
.LASF18:
	.string	"InterfaceNumber"
.LASF26:
	.string	"IdleCount"
.LASF38:
	.string	"__ToDo"
.LASF64:
	.string	"ReportID"
.LASF22:
	.string	"PrevReportINBuffer"
.LASF73:
	.string	"PrevJoystickHIDReportBuffer"
.LASF5:
	.string	"unsigned int"
.LASF75:
	.string	"USARTtoUSB_Buffer"
.LASF8:
	.string	"long unsigned int"
.LASF37:
	.string	"sreg_save"
.LASF20:
	.string	"ReportINEndpointSize"
.LASF16:
	.string	"DEVICE_STATE_Configured"
.LASF87:
	.string	"HID_Device_ProcessControlRequest"
.LASF35:
	.string	"axis"
.LASF79:
	.string	"USB_USBTask"
.LASF45:
	.string	"RingBuffer_Insert"
.LASF57:
	.string	"EVENT_USB_Device_Disconnect"
.LASF17:
	.string	"DEVICE_STATE_Suspended"
.LASF11:
	.string	"sizetype"
.LASF70:
	.string	"CALLBACK_HID_Device_ProcessHIDReport"
.LASF78:
	.string	"USB_Init"
.LASF65:
	.string	"ReportType"
.LASF15:
	.string	"DEVICE_STATE_Addressed"
.LASF13:
	.string	"DEVICE_STATE_Powered"
.LASF72:
	.string	"ReceivedByte"
.LASF74:
	.string	"Joystick_HID_Interface"
.LASF58:
	.string	"SetupHardware"
.LASF68:
	.string	"BufferCount"
.LASF24:
	.string	"_Bool"
.LASF1:
	.string	"unsigned char"
.LASF69:
	.string	"reportp"
.LASF82:
	.string	"/home/baptiste/Bureau/github/simulateur_1790/groupe1/joystick/firmwares/4_axes"
.LASF56:
	.string	"EVENT_USB_Device_Connect"
.LASF53:
	.string	"DoubleSpeed"
.LASF19:
	.string	"ReportINEndpointNumber"
.LASF43:
	.string	"RingBuffer_GetCount"
.LASF50:
	.string	"LEDs_TurnOffLEDs"
.LASF7:
	.string	"uint32_t"
.LASF34:
	.string	"char"
.LASF29:
	.string	"State"
.LASF27:
	.string	"IdleMSRemaining"
.LASF80:
	.string	"GNU C 4.8.1 -mmcu=atmega8u2 -gdwarf-2 -Os -std=gnu99 -funsigned-char -funsigned-bitfields -ffunction-sections -fno-inline-small-functions -fpack-struct -fshort-enums -fno-strict-aliasing"
.LASF25:
	.string	"UsingReportProtocol"
.LASF63:
	.string	"CALLBACK_HID_Device_CreateHIDReport"
.LASF39:
	.string	"__iRestore"
.LASF42:
	.string	"RingBuffer_InitBuffer"
.LASF33:
	.string	"RingBuff_t"
.LASF85:
	.string	"HID_Device_USBTask"
.LASF44:
	.string	"RingBuffer_IsFull"
.LASF28:
	.string	"Config"
.LASF41:
	.string	"HIDInterfaceInfo"
.LASF31:
	.string	"Buffer"
.LASF67:
	.string	"ReportSize"
.LASF32:
	.string	"Count"
.LASF2:
	.string	"uint8_t"
.LASF46:
	.string	"Data"
.LASF59:
	.string	"EVENT_USB_Device_ConfigurationChanged"
.LASF48:
	.string	"LEDs_TurnOnLEDs"
.LASF76:
	.string	"joyReport"
.LASF62:
	.string	"main"
	.ident	"GCC: (GNU) 4.8.1"
.global __do_copy_data
.global __do_clear_bss
