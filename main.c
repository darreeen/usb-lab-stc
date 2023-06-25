#include "address.h"
#include "usb.h"

void sys_init();

void main() {

}



void sys_init() {
    P_SW2 |= 0x80;  //扩展寄存器(XFR)访问使能

    P3M0 &= ~0x03;
    P3M1 |= 0x03;

    IRC48MCR = 0x80;
    while (!(IRC48MCR & 0x01));

    USBCLK = 0x00;
    USBCON = 0x90;
}
