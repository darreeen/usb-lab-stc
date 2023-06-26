#include "usb.h"


void usb_init() {
	usb_write_reg(FADDR, 0x00); 	// reset to default usb address
	usb_write_reg(POWER, 0x09); 	// enable sop to sync timing, and enable suspend detection
	usb_write_reg(INTRIN1E, 0x3f); 	// enable interrupt for all IN endpoint
	usb_write_reg(INTROUT1E, 0x3f);	// enable interrupt for all OUT endpoint
	usb_write_reg(INTRUSBE, 0x07); 	// enable all interrupt except SOF
	usb_write_reg(POWER, 0x01);		// disable sop sync, not sure why.

	// initial value for device and endpoints
	gDeviceState = DEVICE_DEFAULT;
	gEp0.bState  = EP_STATE_IDLE;
	gInEpHalt	 = 0x00;
	gOutEpHalt	 = 0x00;
	gUsbBusy	 = 0;

	// enable usb interrupt in mcs51 core
	IE2 |= 0x80;
}
