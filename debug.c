#include "debug.h"
void d_init() {
    P0M0 = 0;
    P0M1 = 0;
}
void d_led(unsigned char num) {
    P0 |= (1 << num);
}
