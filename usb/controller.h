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
		
#define INTROUT1			0x04	// Out endpoints
		
#define INTRUSB				0x06	// Power Management
#define INTRUSB_RSUIF		0x02	
#define INTRUSB_RSTIF		0x04	

// length count of endpoints OUT and IN
#define COUNT0 				0x16 		// endpoint0 IN and out

// Endpoint registers
#define INDEX  				0x0e			// endpoint index register

#define INCSR1 				0x11			// in endpoint controll register 1
#define INCSR1_CLRDT 		0x40	// constants for INCSR1
#define INCSR1_FLUSH 		0x08

#define OUTCSR1 			0x14		// out endpoint control register 2
#define OUTCSR1_CLRDT 		0x80	// constants for INCSR1
#define OUTCSR1_FLUSH 		0x18

#define FIFO0  				0x20
#define FIFO1  				0x21
// length count of endpoints 


/**
* 3. constants for INCSR1
*/



#endif