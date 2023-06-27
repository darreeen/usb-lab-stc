#include "handler.h"

uint16_t reverse2uint16(uint16_t data) {
    uint16_t result;
    ((unsigned char * )&result)[0] = ((unsigned char * )&data)[1];
    ((unsigned char * )&result)[1] = ((unsigned char * )&data)[0];
    return result;
}

void control_request(void) {
    usb_write_reg(INDEX, 0);
	unsigned char csr = usb_read_reg(CSR0);

    // fix previous stall
    if (csr & CSR0_STSTL) {
        usb_write_reg(CSR0, csr & ~CSR0_STSTL);
        gEp0.bState = EP_STATE_IDLE;
    }
    // fix setup end bit
    if (csr & CSR0_SUEND) {
        usb_write_reg(CSR0, csr | CSR0_SSUEND);
    }
	switch (gEp0.bState) {
        case EP_STATE_IDLE:
            // if the OUT packet from host is ready, we send the data.
            if(csr & CSR0_OPRDY) {
                usb_read_fifo(FIFO0, (unsigned char *) & gRequest);

                // i have no idea why the heck STC demo code reverse bytes of wLength
                // but i gotta follow since there's no efficent way to debug
                // i think maybe it's a endianness issue:
                // for sdcc, it store integers in little endian
                // but keil compiler store intergers in BIG endian
                // and the usb protocol tranfer multi bytes data in little endian format
                // so for our sdcc project, maybe there's no need to reverse bytes.
                // https://stackoverflow.com/questions/2477379/does-8-bit-processor-have-to-face-endianness-problem

                #if defined __CX51__
                    gRequest.wLength = reverse2uint16(gRequest.wLength);
                #endif

                switch (gRequest.bmRequestType & R_BMRT_REQ_TYPE_MASK)
                {
                case R_BMRT_REQ_TYPE_STD:
                    req_std();
                    break;
                case R_BMRT_REQ_TYPE_CLASS:
                    req_class();
                    break;
                case R_BMRT_REQ_TYPE_VENDOR:
                    req_vendor();
                    break;
                default:
                    control_stall();
                    break;
                }
            }
        break;
        case EP_STATE_DATAIN: // if there's unfinished transaction
            control_in();
        break;
        case EP_STATE_DATAOUT:  // if there's unfinished transaction
            control_out();
        break;
        default:
            control_stall();
        break;
    }
}

void ep1_out() {
    unsigned char outcsr1;
    usb_write_reg(INDEX, 1);
    outcsr1 = usb_read_reg(OUTCSR1);
    if(outcsr1 & OUTCSR1_STSTL) {
        usb_write_reg(OUTCSR1, OUTCSR1_CLRDT);
    }
    if(outcsr1 & OUTCSR1_OPRDY) {
        class_out();
    }
}
void ep1_in() {
    unsigned char incsr1;
    usb_write_reg(INDEX, 1);
    incsr1 = usb_read_reg(INCSR1);
    if(incsr1 & INCSR1_STSTL) {
        usb_write_reg(INCSR1, INCSR1_CLRDT);
    }
    if(incsr1 & INCSR1_UNDRUN) {
        usb_write_reg(INCSR1, 0);
    }
    gUsbBusy = 0;
}
