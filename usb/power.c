#include "power.h"

void usb_pm_resume(void) {
	// not implemented yet
	// since STC demo code not implemented this either.
}
void usb_pm_reset(void) {
	usb_write_reg(FADDR, 0x00); 	// reset device address
	gDeviceState = DEVICE_DEFAULT;	
	gEp0.bState = EP_STATE_IDLE;
	
	// reset endpoint 1
	usb_write_reg(INDEX, 1);
	usb_write_reg(INCSR1, INCSR1_CLRDT | INCSR1_FLUSH);
	
	usb_write_reg(INDEX, 1);
	usb_write_reg(OUTCSR1, OUTCSR1_CLRDT | OUTCSR1_FLUSH);
	
	usb_write_reg(INDEX, 0);
}
void usb_pm_suspend(void) {
	// not implemented yet
	// since STC demo code not implemented this either.
}