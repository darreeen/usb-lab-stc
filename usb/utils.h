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
// bmRequestType
	// types
#define R_BMRT_REQ_TYPE_MASK 				0x60	// bit 5-6 indicates request type
#define R_BMRT_REQ_TYPE_STD					0x00
#define R_BMRT_REQ_TYPE_CLASS				0x20
#define R_BMRT_REQ_TYPE_VENDOR				0x40
	// recipient
#define R_BMRT_REQ_RECIPIENT_MASK			0x0f
#define R_BMRT_REQ_RECIPIENT_DEVICE			0x00
#define R_BMRT_REQ_RECIPIENT_INTERFACE		0x01
#define R_BMRT_REQ_RECIPIENT_ENDPOINT		0x02
	// data direction
#define R_BMRT_REQ_DIRECTION_MASK			0x80
#define R_BMRT_REQ_DIRECTION_OUT			0x00
#define R_BMRT_REQ_DIRECTION_IN				0x80
// bRequest: request nunmber
#define R_BR_GET_STATUS						0x00
#define R_BR_CLEAR_FEATURE					0x01
#define R_BR_SET_FEATURE					0x03
#define R_BR_SET_ADDRESS					0x05
#define R_BR_GET_DESCRIPTOR					0x06
#define R_BR_SET_DESCRIPTOR					0x07
#define R_BR_GET_CONFIGURATION				0x08
#define R_BR_SET_CONFIGURATION				0x09
#define R_BR_GET_INTERFACE					0x0a
#define R_BR_SET_INTERFACE					0x0b
#define R_BR_SYNCH_FRAME					0x0c
// wIndexL: endpoint number and direction
#define R_WI_EP1_IN 						0x81
#define R_WI_EP1_OUT						0x01
#define R_WI_EP_NUM_MASK					0x0f

/**
* 5. USB Busy Indicator
*/
extern unsigned char gUsbBusy;


/**
* 6. Endpoint maxium package bits
*/
#define EPS_IN_1							64
#define EPS_OUT_1							64

#endif
