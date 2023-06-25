#ifndef __ADDRESS_
#define __ADDRESS_

#include "compatible.h"

// STC extend registers
// P_SW2 peripheral switch 2
// b7 eaxfr enable external sfr

SFR(P_SW2, 0xba);  // use this to access external sfr

// INTERRUPT related registers
SFR(IE2, 0xaf);

// STC IO port configuration registers
// combine PxM0 with PxM1 to set register modes
SFR(P3M0, 0xb2);
SFR(P3M1, 0xb1);

// usb controller related registers
SFR(USBCON, 0xf4);
SFR(USBCLK, 0xdc);
SFR(USBADR, 0xfc);
SFR(USBDAT, 0xec);

// timer related regs
SFR(AUXR, 0x8e);
SFR(TMOD, 0x89);
SFR(TL0, 0x8a);
SFR(TH0, 0x8c);
// TMOD bit 4
SBIT(TR0, 0x89, 4);
// ET0 bit 1
SBIT(ET0, 0xa8, 1);

// interrupt related


// external sfr
#define     IRC48MCR                (*(unsigned char volatile __XDATA *)0xfe07)

#endif
