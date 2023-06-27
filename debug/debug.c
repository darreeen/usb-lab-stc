#include "debug.h"
#include "uart.h"

void d_init() {
    uart_init();
}

void d_puts(char * s) {
    puts(s);
}

void d_put_hex_8(unsigned char num) {
    putHex8(num);
}

// stage specific

void d_intr(char *s) {
    d_puts("[INTERRUPT] ");
    d_puts(s);
    d_puts("\n\r");
}

void d_std_req(char *s) {
    d_puts("[REQ_STD] ");
    d_puts("\t");
    d_puts(s);
    d_puts("\n\r");
}

void d_class_req(char *s) {
    d_puts("[REQ_CLASS] ");
    d_puts("\t");
    d_puts(s);
    d_puts("\n\r");
}

void d_vendor_req(char *s) {
    d_puts("[REQ_VENDOR] ");
    d_puts("\t");
    d_puts(s);
    d_puts("\n\r");
}

void d_req_detail(char *s) {
    d_puts("[REQ INFO] ");
    d_puts("\t\t");
    d_puts(s);
    d_puts("\n\r");
}

void d_stall_info(char *s, unsigned char v) {
    d_puts("[STALLED!!!]: ");
    d_puts(s);
    d_puts(" value = ");
    d_put_hex_8(v);
    d_puts("\n\r");
}

#ifdef DEBUG_WITH_LEDs
void d_led() {

}
#endif
