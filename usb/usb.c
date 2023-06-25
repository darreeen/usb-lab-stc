#include "usb.h"
// interrupt service routine
// void usb_isr(void) __interrupt (25) __using (2) {
INTERRUPT_USING(usb_isr, 25, 2) {
	// intrusb register indicate power interruption
	unsigned char intrusb	= usb_read_reg(INTRUSB);
	unsigned char intrin	= usb_read_reg(INTRIN1);
	unsigned char introut	= usb_read_reg(INTROUT1);

	// process power management interrupts
	if(intrusb & INTRUSB_RSUIF)	usb_pm_resume();
	if(intrusb & INTRUSB_RSTIF)	usb_pm_reset();

	// process control pipe in

	// process in transaction

	// process out transaction

}

void usb_init() {
	usb_write_reg(FADDR, 0x00); 	// reset to default usb address
	usb_write_reg(POWER, 0x01); 	// enable sop to sync timing, and enable suspend detection
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
