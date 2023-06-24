/**
* utility functions for genreal usb controller manipulation
*/

#ifndef __USB_UTILS_
#define __USB_UTILS_

#include <stdint.h>
#include "../address.h"
#include "controller.h"
/**
* 1. Utility Functions
*/
// read from usb controller registers
unsigned char usb_read_reg(unsigned char usb_reg_addr);
// write to usb controller registers
unsigned char usb_write_reg(unsigned char usb_reg_addr, unsigned char reg_data);
// read from usb controller fifo registers
unsigned char usb_read_fifo(unsigned char fifo, unsigned char *pdat);
// write to usb controller fifo registers
unsigned char usb_write_fifo(unsigned char fifo, unsigned char *pdat, unsigned char count);


/**
* 2. Endpoint State Structure
*/
typedef struct {
	unsigned char bState; 	// Endpoint state indicator
	uint16_t wSize;			// Data remains to write
	unsigned char *pData;  	// Data pointer.
} EndpointState;

// bState Codes:
#define EP_STATE_IDLE            0
#define EP_STATE_HALT            1
#define EP_STATE_STATUS          2
#define EP_STATE_DATAIN          3
#define EP_STATE_DATAOUT         4
#define EP_STATE_STALL           5
// state structure for endpoint 0
extern EndpointState gEp0;
// other endpoint state variable
extern unsigned char gInEpHalt;		// endpoint halt indicator
extern unsigned char gOutEpHalt;

/**
* 3. Device State
*/
extern unsigned char gDeviceState;
// DeviceState codes
#define DEVICE_ATTACHED       0
#define DEVICE_POWERED        1
#define DEVICE_DEFAULT        2
#define DEVICE_ADDRESS        3
#define DEVICE_CONFIGURED     4
#define DEVICE_SUSPENDED      5


/**
* 4. Request Structure
*/
typedef struct {
	unsigned char bmRequestType;
	unsigned char bRequest;
	unsigned char wValueL;
	unsigned char wValueH;
	unsigned char wIndexL;
	unsigned char wIndexH;
	uint16_t wLength;
} Request;
// general request structure
extern Request gRequest;
// constants for bmRequestType
#define BMRT_REQ_TYPE_MASK 		0x60	// bit 5-6 indicates request type
#define BMRT_REQ_TYPE_STD		0x00
#define BMRT_REQ_TYPE_CLASS		0x20
#define BMRT_REQ_TYPE_VENDOR	0x40
// constants for bRequest
#define BR_GET_STATUS			0x00
#define BR_CLEAR_FEATURE		0x01
#define BR_SET_FEATURE			0x03
#define BR_SET_ADDRESS			0x05
#define BR_GET_DESCRIPTOR		0x06
#define BR_SET_DESCRIPTOR		0x07
#define BR_GET_CONFIGURATION	0x08
#define BR_SET_CONFIGURATION	0x09
#define BR_GET_INTERFACE		0x0a
#define BR_SET_INTERFACE		0x0b
#define BR_SYNCH_FRAME			0x0c

/**
* 5. USB Busy Indicator
*/
extern unsigned char gUsbBusy;
#endif
