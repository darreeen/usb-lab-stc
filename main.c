#include "address.h"
#include "usb/usb.h"
#include "usb/pipe_control/req_class.h"
#include "timer.h"

#include "debug.h"

void sys_init();

void main() {
    sys_init();
    usb_init();
    timer_init();

    d_init();

    EA = 1;
    while (1)
    {
        // don't make key press for now
        // class_in(0x1e);
    }

}

void sys_init() {
    P_SW2 |= 0x80;  // external sfr enable

    P3M0 &= ~0x03;
    P3M1 |= 0x03;

    IRC48MCR = 0x80;
    while (!(IRC48MCR & 0x01));

    USBCLK = 0x00;
    USBCON = 0x90;
}
