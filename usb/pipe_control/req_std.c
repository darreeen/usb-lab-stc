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
	case R_BR_GET_STATUS:
		get_status();
		break;
	case R_BR_CLEAR_FEATURE:
		clear_feature();
		break;
	case R_BR_SET_FEATURE:
		set_feature();
		break;
	case R_BR_SET_ADDRESS:
		set_address();
		break;
	case R_BR_GET_DESCRIPTOR:
		get_descriptor();
		break;
	case R_BR_SET_DESCRIPTOR:
		set_descriptor();
		break;
	case R_BR_GET_CONFIGURATION:
		get_configuration();
		break;
	case R_BR_SET_CONFIGURATION:
		set_configuration();
		break;
	case R_BR_GET_INTERFACE:
		set_interface();
		break;
	case R_BR_SET_INTERFACE:
		set_interface();
		break;
	case R_BR_SYNCH_FRAME:
		synch_frame();
		break;
	default:
		control_stall();
		break;
	}
}

void get_status() {
	if(((gRequest.bmRequestType & R_BMRT_REQ_DIRECTION_MASK) != R_BMRT_REQ_DIRECTION_IN) ||
		(gRequest.wValueH != 0) || (gRequest.wValueL != 0) || (gRequest.wLength != 2)) {
			control_stall();
			return;
		}
	switch (gRequest.bmRequestType & R_BMRT_REQ_RECIPIENT_MASK)
	{
	case R_BMRT_REQ_RECIPIENT_DEVICE:
		// for device recipient, wIndex should = 0x0000,
		if(gRequest.wIndexH != 0 || gRequest.wIndexL != 0) {
			control_stall();
			return;
		}
		// could be improved
		gEp0.pData = packet0; // host powered and no remote wakeup
		gEp0.wSize = 2;
		break;
	case R_BMRT_REQ_RECIPIENT_INTERFACE:
		// device needs to be configured and only interface 0 is provided. so index must equal to 0
		if((gDeviceState != DEVICE_CONFIGURED) || (gRequest.wIndexH != 0) || (gRequest.wIndexL != 0)) {
			control_stall();
			return;
		}
		// could be improved
		gEp0.pData = packet0; // reserved bit pattern with all bits 0
		gEp0.wSize = 2;
		break;
	case R_BMRT_REQ_RECIPIENT_ENDPOINT:
		// device needs to be configured and only endpoint 0-5 supported by the chip.
		if((gDeviceState != DEVICE_CONFIGURED) || (gRequest.wIndexH != 0)) {
			control_stall();
			return;
		}
		unsigned char endpointNumber = gRequest.wIndexL & R_WI_EP_NUM_MASK; // endpoint number without direction bit
		gEp0.wSize = 2;
		gEp0.pData = packet0; // not halt by default
		switch (gRequest.wIndexL)
		{
		case R_WI_EP1_IN:	// endpoint 1 IN
			if(gInEpHalt & (1 << endpointNumber)) { // check if halted // this might be problematic
				gEp0.pData = packet1;
			}
			break;
		case R_WI_EP1_OUT: // endpoint 1 out
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

// The host requests to enable a feature on a device, interface, or endpoint.
void clear_feature() {
	if((gDeviceState != DEVICE_CONFIGURED) || (gRequest.bmRequestType != (R_BMRT_REQ_TYPE_STD | R_BMRT_REQ_DIRECTION_OUT | R_BMRT_REQ_RECIPIENT_ENDPOINT)) ||
	(gRequest.wIndexH != 0) || (gRequest.wValueH != 0) || (gRequest.wValueL != 0x00) || (gRequest.wLength != 0)) { // wValueL indicate endpoint halt
		control_stall();
		return;
	}
	unsigned char endpointNumber = gRequest.wIndexL & R_WI_EP_NUM_MASK;
	switch (gRequest.wIndexL)
	{
	case R_WI_EP1_IN:
		gInEpHalt &= ~(1 << endpointNumber);  // reset endpoint if halted
		usb_write_reg(INDEX, endpointNumber);
		usb_write_reg(INCSR1, INCSR1_CLRDT);
		usb_write_reg(INDEX, 0);
		break;
	case R_WI_EP1_OUT:
		gOutEpHalt &= ~(1 << endpointNumber);
		usb_write_reg(INDEX, endpointNumber);
		usb_write_reg(OUTCSR1, OUTCSR1_CLRDT);
		usb_write_reg(INDEX, 0);
	default:
		control_stall();
		return;
	}
}

void set_feature() {
	if((gDeviceState != DEVICE_CONFIGURED) ||
		(gRequest.bmRequestType != (R_BMRT_REQ_DIRECTION_OUT | R_BMRT_REQ_TYPE_STD | R_BMRT_REQ_RECIPIENT_ENDPOINT)) ||
		(gRequest.wIndexH != 0) || (gRequest.wValueH != 0) || (gRequest.wValueL != 0x00) || (gRequest.wLength != 0)) { // wValueL indicates endpoint halt
			control_stall();
			return;
	}
	unsigned char endpointNumber = gRequest.wIndexL & R_WI_EP_NUM_MASK;
	switch (gRequest.wIndexL)
	{
	case R_WI_EP1_IN:
		gInEpHalt |= (1 << endpointNumber);
		usb_write_reg(INDEX, endpointNumber);
		usb_write_reg(INCSR1, INCSR1_SDSTL);
		usb_write_reg(INDEX, 0);
		break;
	case R_WI_EP1_OUT:
		gOutEpHalt |= (1 << endpointNumber);
		usb_write_reg(INDEX, endpointNumber);
		usb_write_reg(OUTCSR1, OUTCSR1_SDSTL);
		usb_write_reg(INDEX, 0);
		break;

	default:
		control_stall();
		return;
	}
}

void set_address() {
	if((gRequest.bmRequestType != (R_BMRT_REQ_DIRECTION_OUT | R_BMRT_REQ_TYPE_STD | R_BMRT_REQ_RECIPIENT_DEVICE)) ||
		(gRequest.wIndexH != 0) ||
		(gRequest.wIndexL != 0) ||
		(gRequest.wValueH != 0) ||
		(gRequest.wValueL >= 0x80) ||
		(gRequest.wLength != 0)) {
			control_stall();
	}
	unsigned char addr = gRequest.wValueL;
	usb_write_reg(FADDR, addr);
	if(addr != 0) {
		gDeviceState = DEVICE_ADDRESS;
	} else {
		gDeviceState = DEVICE_DEFAULT;
	}
	// set endpoint status
	gEp0.bState - EP_STATE_IDLE;
	usb_write_reg(CSR0, CSR0_SOPRDY | CSR0_DATEND);
}
void get_descriptor() {
	if((gRequest.bmRequestType & R_BMRT_REQ_DIRECTION_MASK) != R_BMRT_REQ_DIRECTION_IN) {
		control_stall();
		return;
	}
	switch(gRequest.wValueH) {
		case 0x01: // device descriptor
			gEp0.pData = desc_device;
			gEp0.wSize = sizeof(desc_device);
			break;
		case 0x02: // configuration descriptor
			gEp0.pData = desc_conf;
			gEp0.wSize = sizeof(desc_conf);
			break;
		case 0x03: // string descriptor
			switch (gRequest.wValueL)
			{
			case 0:		// language id descriptor
				gEp0.pData = desc_lang;
				gEp0.wSize = sizeof(desc_lang);
				break;
			case 1:		// manufacturer descriptor
				gEp0.pData = desc_manufacturer;
				gEp0.wSize = sizeof(desc_manufacturer);
				break;
			case 2:		// product descriptor
				gEp0.pData = desc_product;
				gEp0.wSize = sizeof(desc_product);
				break;
			default:
				control_stall();
				break;
			}
			break;
		case 0x22:	// hid class descriptor, aka report descriptor
			gEp0.pData = desc_hid_report;
			gEp0.wSize = sizeof(desc_hid_report);
			break;
		default:
			control_stall();
			return;
	}
	// in case of over host request size:
	if(gEp0.wSize > gRequest.wLength) {
		gEp0.wSize = gRequest.wLength;
	}
}

void set_descriptor() {
	control_stall();
}

// get current using configuratin descriptor index, bConfigurationValue
void get_configuration() {
	if((gRequest.bmRequestType != (R_BMRT_REQ_DIRECTION_IN | R_BMRT_REQ_TYPE_STD | R_BMRT_REQ_RECIPIENT_DEVICE)) ||
		(gRequest.wValueH != 0) ||
		(gRequest.wValueL != 0) ||
		(gRequest.wIndexH != 0) ||
		(gRequest.wIndexL != 0) ||
		(gRequest.wLength != 1))
	{
		control_stall();
		return;
	}
	if(gDeviceState == DEVICE_CONFIGURED) {
		gEp0.pData = packet1;
		gEp0.wSize = 1;
	} else {
		gEp0.pData = packet0;
		gEp0.wSize = 1;
	}
	gEp0.bState = EP_STATE_DATAIN;
	usb_write_reg(CSR0, CSR0_SOPRDY);
	control_in();
}
void set_configuration() {
	if((gDeviceState == DEVICE_DEFAULT) ||
		(gRequest.bmRequestType != (R_BMRT_REQ_DIRECTION_OUT | R_BMRT_REQ_TYPE_STD | R_BMRT_REQ_RECIPIENT_DEVICE)) ||
		(gRequest.wValueH != 0) ||
		(gRequest.wIndexH != 0) ||
		(gRequest.wIndexL != 0) ||
		(gRequest.wLength != 0)) {
			control_stall();
			return;
	}
	if(gRequest.wValueL == 1) {
		gDeviceState = DEVICE_CONFIGURED;
		gInEpHalt = 0x00;
		gOutEpHalt = 0x00;
		usb_write_reg(INDEX, 1);
		usb_write_reg(INCSR2, INCSR2_MODE_IN);
		usb_write_reg(INMAXP, EPS_IN_1 / 8);

		usb_write_reg(INDEX, 1);
		usb_write_reg(INCSR2, INCSR2_MODE_OUT);
		usb_write_reg(OUTMAXP, EPS_OUT_1 / 8);

		usb_write_reg(INDEX, 0);
	} else {
		gDeviceState = DEVICE_ADDRESS;
		gInEpHalt = 0xff;
		gOutEpHalt = 0xff;
	}

	gEp0.bState = EP_STATE_IDLE;
	usb_write_reg(CSR0, CSR0_SOPRDY | CSR0_DATEND);
}

void get_interface() {
	if((gDeviceState != DEVICE_CONFIGURED) ||
		(gRequest.bmRequestType != (R_BMRT_REQ_DIRECTION_IN | R_BMRT_REQ_TYPE_STD | R_BMRT_REQ_RECIPIENT_INTERFACE)) ||
		(gRequest.wValueH != 0) ||
		(gRequest.wIndexH != 0) ||
		(gRequest.wLength != 1)) {
			control_stall();
			return;
	}
	gEp0.pData = packet0;
	gEp0.wSize = 1;

	gEp0.bState = EP_STATE_DATAIN;
	usb_write_reg(CSR0, CSR0_SOPRDY);
	control_in();
}
void set_interface() {
	if((gDeviceState != DEVICE_CONFIGURED) ||
		(gRequest.bmRequestType != (R_BMRT_REQ_DIRECTION_OUT | R_BMRT_REQ_TYPE_STD | R_BMRT_REQ_RECIPIENT_INTERFACE)) ||
		(gRequest.wValueH != 0) ||
		(gRequest.wIndexH != 0) ||
		(gRequest.wLength != 0)) {
			control_stall();
			return;
	}

	gEp0.bState = EP_STATE_IDLE;
	usb_write_reg(CSR0, CSR0_SOPRDY | CSR0_DATEND);
}

void synch_frame() {
	control_stall();
}
