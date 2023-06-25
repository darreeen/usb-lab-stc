#include "./transaction.h"
unsigned char interrupt_out(unsigned char *pData, unsigned char endpoint) {
    unsigned char receive_counter = usb_read_fifo((unsigned char)(FIFO0 + endpoint), pData);
    usb_write_reg(OUTCSR1, 0);

    return receive_counter;
}
