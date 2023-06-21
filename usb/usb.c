#include "usb.h"
// interrupt service routine 
void usb_isr(void) __interrupt (25) __using (2) {
	// intrusb register indicate power interruption
	unsigned char intrusb; 
	
}


