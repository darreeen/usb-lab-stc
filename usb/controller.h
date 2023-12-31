#ifndef __USB_CONTROLLER_H_
#define __USB_CONTROLLER_H_


/**
* 1. USB Controller Register Address
*/

#define FADDR 				0x00	// USB Function Address Register:
									// holds the current usb0 function address. software should write the host-assigned 7-bit function address to this with setAddress request.
#define POWER 				0x01	// USB Power Control Register:

// USB Controller Interrupt related registers
// interrupt enable registers
#define INTRIN1E 			0x07	// IN endpoints
#define INTROUT1E			0x09	// OUT endpoints
#define INTRUSBE 			0X0b	// Power Management
// interrupt sign
#define INTRIN1				0x02	// In endpoints
#define INTRIN1_EP0IF		0x01
#define INTRIN1_EP1INIF		0x02

#define INTROUT1			0x04	// Out endpoints
#define INTROUT1_EP1OUTIF	0x02

#define INTRUSB				0x06	// Power Management
#define INTRUSB_RSUIF		0x02
#define INTRUSB_RSTIF		0x04
#define INTRUSB_SUSIF		0x01

// length count of endpoints OUT and IN
#define COUNT0 				0x16 	// endpoint0 IN and out

// Endpoint registers
#define INDEX  				0x0e	// endpoint index register

#define CSR0				0x11
#define CSR0_STSTL			0x04
#define CSR0_SUEND			0x10
#define CSR0_SSUEND			0x80
#define CSR0_OPRDY			0x01	// received an output transaction
#define CSR0_SOPRDY			0x40	// clear output indicator
#define CSR0_DATEND			0x08
#define CSR0_IPRDY			0x02
#define CSR0_SDSTL			0x20


#define INCSR1 				0x11	// in endpoint controll register 1
#define INCSR1_CLRDT 		0x40	// constants for INCSR1
#define INCSR1_FLUSH 		0x08
#define INCSR1_SDSTL 		0x10
#define INCSR1_IPRDY 		0x01
#define INCSR1_STSTL 		0x20
#define INCSR1_UNDRUN 		0x04

#define INCSR2 				0x12	// in endpoint controll register 2
#define INCSR2_MODE_IN		0x20
#define INCSR2_MODE_OUT		0x00

#define INMAXP				0x10
#define OUTMAXP				0x13

#define OUTCSR1 			0x14	// out endpoint control register 2
#define OUTCSR1_CLRDT 		0x80	// constants for INCSR1
#define OUTCSR1_FLUSH 		0x18
#define OUTCSR1_SDSTL 		0x20
#define OUTCSR1_STSTL 		0x40
#define OUTCSR1_OPRDY 		0x01

#define FIFO0  				0x20
#define FIFO1  				0x21
// length count of endpoints


/**
* 3. constants for INCSR1
*/



#endif
