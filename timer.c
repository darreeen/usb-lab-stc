#include "timer.h"
#define FOSC                    24000000UL
#define TM_1MS      (65536 - FOSC/1000)

unsigned char g1msFlg;

INTERRUPT_USING(timer_isr, 1, 3) {
    g1msFlg = 0;
    AUXR |= 0x80;
    TMOD &= ~0x0f;
    TL0 = TM_1MS;
    TH0 = TM_1MS >> 8;
    TR0 = 1;
    ET0 = 1;
}
