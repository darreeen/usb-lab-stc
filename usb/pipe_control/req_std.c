#include "./req_std.h"


// requests
void get_status();

void clear_feature();
void set_feature();

void set_address();
void get_descriptor();
void set_descriptor();

void get_configuration();
void set_configuration();

void get_interface();
void set_interface();

void synch_frame(); // unsupported yet


void req_std() {
	switch (gRequest.bRequest)
	{
	case BR_GET_STATUS:
		get_status();
		break;
	case BR_CLEAR_FEATURE:
		clear_feature();
		break;
	case BR_SET_FEATURE:
		set_feature();
		break;
	case BR_SET_ADDRESS:
		set_address();
		break;
	case BR_GET_DESCRIPTOR:
		get_descriptor();
		break;
	case BR_SET_DESCRIPTOR:
		set_descriptor();
		break;
	case BR_GET_CONFIGURATION:
		get_configuration();
		break;
	case BR_SET_CONFIGURATION:
		set_configuration();
		break;
	case BR_GET_INTERFACE:
		set_interface();
		break;
	case BR_SET_INTERFACE:
		set_interface();
		break;
	case BR_SYNCH_FRAME:
		synch_frame();
		break;
	default:
		control_stall();
		break;
	}
}

void get_status() {
	const unsigned char RECIPIENT_MASK		= 0x0f;
	const unsigned char RECIPIENT_DEVICE	= 0x00;
	const unsigned char RECIPIENT_INTERFACE	= 0x01;
	const unsigned char RECIPIENT_ENDPOINT	= 0x02;

	switch (gRequest.bmRequestType & RECIPIENT_MASK)
	{
	case RECIPIENT_DEVICE:
		// for device recipient, wIndex should = 0x0000,
		if(gRequest.wIndexH != 0 || gRequest.wIndexL != 0) {
			control_stall();
			return;
		}
		// could be improved
		gEp0.pData = packet0; // host powered and no remote wakeup
		gEp0.wSize = 2;
		break;
	case RECIPIENT_INTERFACE:
		// device needs to be configured and only interface 0 is provided. so index must equal to 0
		if(gDeviceState != DEVICE_CONFIGURED || gRequest.wIndexH !=0 || gRequest.wIndexL !=0) {
			control_stall();
			return;
		}
		// could be improved
		gEp0.pData = packet0; // reserved bit pattern with all bits 0
		gEp0.wSize = 2;
		break;
	case RECIPIENT_ENDPOINT:
		// device needs to be configured and only endpoint 0-5 supported by the chip.
		if(gDeviceState != DEVICE_CONFIGURED || gRequest.wIndexH != 0) {
			control_stall();
			return;
		}
		unsigned char endpointNumber = gRequest.wIndexL & 0x0f; // endpoint number without direction bit
		gEp0.wSize = 2;
		gEp0.pData = packet0; // not halt by default
		switch (gRequest.wIndexL)
		{
		case 0x81:	// endpoint 1 IN
			if(gInEpHalt & (1 << endpointNumber)) { // check if halted
				gEp0.pData = packet1;
			}
			break;
		case 0x01: // endpoint 1 out
			if(gOutEpHalt & (1 << endpointNumber)) {
				gEp0.pData = packet1;	// return halt info
			}
			break;
		default:
			control_stall();
			return;
		}
		break;
	default:
		control_stall();
		return;
	}

	gEp0.bState = EP_STATE_DATAIN;		// make endpoint from idle to data in mode
	usb_write_reg(CSR0, CSR0_SOPRDY); 	// clear OPRDY
	control_in();						// start in transaction
}

void clear_feature() {}
void set_feature() {}

void set_address() {}
void get_descriptor() {}
void set_descriptor() {}

void get_configuration() {}
void set_configuration() {}

void get_interface() {}
void set_interface() {}

void synch_frame() {
	control_stall();
}
