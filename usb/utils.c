#include "./utils.h"
// global variables
unsigned char gDeviceState;
EndpointState gEp0;
unsigned char gInEpHalt;
unsigned char gOutEpHalt;
Request gRequest;
unsigned char gUsbBusy;
unsigned char __XDATA gUsbBuffer[256];

unsigned char usb_read_reg(unsigned char usb_reg_addr) {
	unsigned char data;
	// wait if usb controller if busy
	while(USBADR & 0x80);
	USBADR = usb_reg_addr | 0x80;
	while(USBADR & 0x80);
	data = USBDAT;

	return data;
}

unsigned char usb_write_reg(unsigned char usb_reg_addr, unsigned char data) {
	// wait if usb controller if busy
	while(USBADR & 0x80);
	USBADR = usb_reg_addr;
	USBDAT = data&0x7f;
	return 0;
}

unsigned char usb_write_fifo(unsigned char usb_fifo_reg_addr, unsigned char * pdata, unsigned char count) {
	while(count--) {
		usb_write_reg(usb_fifo_reg_addr, *pdata);
		pdata++;
	}
	return count;
}

unsigned char usb_read_fifo(unsigned char usb_fifo_reg_addr, unsigned char *pdata) {
	unsigned char count = usb_read_reg(COUNT0);
	unsigned char return_vale = count;

	// keep reading till all data are read.
	while(count--) {
		*pdata = usb_read_reg(usb_fifo_reg_addr);
		pdata++;
	}
	return return_vale;
}
