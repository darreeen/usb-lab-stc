#include "debug.h"
void d_init() {
    P0M0 = 0;
    P0M1 = 0;

    // P3M0 = 0;
    // P3M1 = 0;

    P2M0 = 0;
    P2M1 = 0;

    d_led(0, 1);
}
void d_led(unsigned char num, unsigned char value) {
    if(num <= 7) {
        P0 &= ~(value << num);
    } else if (num <= 0xf) {
        P2 &= ~(value << (num - 8));
    }
}

// void d_byte(unsigned char)
