#include "debug.h"
#include "uart.h"

void debug_init() {
    uart_init();
}

void d_puts(char * s) {
    puts(s);
}

void d_put_hex_8(unsigned char num) {
    putHex8(num);
}
#ifdef DEBUG_WITH_LEDs
void d_led() {

}
#endif
