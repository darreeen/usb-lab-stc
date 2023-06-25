#include "./transaction.h"

void control_in() {

    usb_write_reg(INDEX, 0);
    unsigned char csr0 = usb_read_reg(CSR0);
    if(csr0 & CSR0_IPRDY) return; // return if there's a packet pending

    unsigned char send_counter = (gEp0.wSize > EPS_0) ? EPS_0 : gEp0.wSize;
    usb_write_fifo(FIFO0, gEp0.pData, send_counter);
    gEp0.wSize -= send_counter;
    gEp0.pData += send_counter;
    if(gEp0.wSize == 0) {
        usb_write_reg(CSR0, CSR0_IPRDY | CSR0_DATEND);
        gEp0.bState = EP_STATE_IDLE;
    } else {
        usb_write_reg(CSR0, CSR0_IPRDY);
    }
}

void control_out() {
    usb_write_reg(INDEX, 0);
    unsigned char csr0 = usb_read_reg(CSR0);
    if(!(csr0 & CSR0_OPRDY)) return; // return if there's no out packet to receive

    unsigned char receive_counter = usb_read_fifo(FIFO0, gEp0.pData);
    gEp0.wSize -= receive_counter;
    // this might not working
    gEp0.wSize -= receive_counter;
    gEp0.pData += receive_counter;
    if(gEp0.wSize == 0) {
        usb_write_reg(CSR0, CSR0_SOPRDY | CSR0_DATEND);
        gEp0.bState = EP_STATE_IDLE;
    } else {
        usb_write_reg(CSR0, CSR0_SOPRDY);
    }
}

void control_stall() {
    gEp0.bState = EP_STATE_STALL;
    usb_write_reg(CSR0, CSR0_SOPRDY | CSR0_SDSTL);
}
