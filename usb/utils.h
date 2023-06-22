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
extern unsigned char gInEpState;		// used for getStatus request
extern unsigned char gOutEpState;

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
} Request;
// general request structure
extern Request gRequest;

/**
* 5. USB Busy Indicator
*/
extern unsigned char gUsbBusy;
#endif
