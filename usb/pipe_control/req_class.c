#include "req_class.h"

#define GET_REPORT              0x01
#define GET_IDLE                0x02
#define GET_PROTOCOL            0x03
#define SET_REPORT              0x09
#define SET_IDLE                0x0A
#define SET_PROTOCOL            0x0B

#define DESC_HIDREPORT          0x22

void class_in();
void class_out();

void get_report();
void set_report();

void get_idle();
void set_idle();
unsigned char bHidIdle;

void get_protocol();
void set_procotol();


void req_class() {
    switch (gRequest.bRequest)
    {
    case GET_REPORT:
        get_report();
        break;
    case SET_REPORT:
        set_report();
        break;
    case GET_IDLE:
        get_idle();
        break;
    case SET_IDLE:
        set_idle();
        break;
    case GET_PROTOCOL:
        get_protocol();
        break;
    case SET_PROTOCOL:
        set_procotol();
        break;
    default:
        control_stall();
        return;
    }
}


void class_in(unsigned char report_key_code) {
    unsigned char keys_report[8] = {0};
    // byte 1 for report id
    // byte 2 reserved
    keys_report[2] = report_key_code;

    IE2 &= ~0x80; // disable usb interrupt
    gUsbBusy = 1;
    usb_write_reg(INDEX, 1);
    usb_write_fifo(FIFO1, keys_report, 8);
    usb_write_reg(INCSR1, INCSR1_IPRDY);
    IE2 |= 0x80;   // enable usb interrupt

}
void class_out() { // class out for led support
    control_stall(); // no led support for this project
}

void get_report() {
    if((gDeviceState != DEVICE_CONFIGURED) ||
        (gRequest.bmRequestType != (R_BMRT_REQ_DIRECTION_IN | R_BMRT_REQ_TYPE_CLASS | R_BMRT_REQ_RECIPIENT_INTERFACE))) {
            control_stall();
            return;
    }

    gEp0.pData = gUsbBuffer;
    gEp0.wSize = gRequest.wLength;

    gEp0.bState = EP_STATE_DATAIN;
    usb_write_reg(CSR0, CSR0_SOPRDY);
    control_in();
}
void set_report() {
    if((gDeviceState != DEVICE_CONFIGURED) ||
        (gRequest.bmRequestType != (R_BMRT_REQ_DIRECTION_OUT | R_BMRT_REQ_TYPE_CLASS | R_BMRT_REQ_RECIPIENT_INTERFACE))) {
            control_stall();
            return;
    }
    gEp0.pData = gUsbBuffer;
    gEp0.wSize = gRequest.wLength;

    gEp0.bState = EP_STATE_DATAOUT;
    usb_write_reg(CSR0, CSR0_SOPRDY);
}

void get_idle() {
    if((gDeviceState != DEVICE_CONFIGURED) ||
        (gRequest.bmRequestType != (R_BMRT_REQ_DIRECTION_IN | R_BMRT_REQ_TYPE_CLASS | R_BMRT_REQ_RECIPIENT_INTERFACE))) {
            control_stall();
            return;
    }
    gEp0.pData = &bHidIdle;
    gEp0.wSize = 1;

    gEp0.bState = EP_STATE_DATAIN;
    usb_write_reg(CSR0, CSR0_SOPRDY);
    control_in();
}
void set_idle() {
    if((gDeviceState != DEVICE_CONFIGURED) ||
        (gRequest.bmRequestType != (R_BMRT_REQ_DIRECTION_OUT | R_BMRT_REQ_TYPE_CLASS | R_BMRT_REQ_RECIPIENT_INTERFACE))) {
            control_stall();
            return;
    }
    bHidIdle = gRequest.wValueH;

    gEp0.bState = EP_STATE_IDLE;
    usb_write_reg(CSR0, CSR0_SOPRDY | CSR0_DATEND);
}

void get_protocol() {
    control_stall();    // not supported yet
}
void set_procotol() {
    control_stall();    // not supported yet
}
