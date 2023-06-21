/**
* utility functions for genreal usb controller manipulation
*/

#ifndef __USB_UTILS_
#define __USB_UTILS_


// read from usb controller registers
unsigned char usb_read_reg(unsigned char usb_reg_addr);
// write to usb controller registers
unsigned char usb_write_reg(unsigned char usb_reg_addr, unsigned char reg_data);
// read from usb controller fifo registers
unsigned char usb_read_fifo(unsigned char fifo, unsigned char *pdat);
// write to usb controller fifo registers
unsigned char usb_write_fifo(unsigned char fifo, unsigned char *pdat, unsigned char count);

unsigned char 

#endif