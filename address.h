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
// P0
SFR(P0, 0x80);
SFR(P0M0, 0x94);
SFR(P0M1, 0x93);

// P2
SFR(P2, 0xa0);
SFR(P2M0, 0x96);
SFR(P2M1, 0x95);

// P3
SFR(P3, 0xb0);
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
// IE0 bit 0
SBIT(EA, 0xa8, 0);
// IE0 bit 1
SBIT(ET0, 0xa8, 1);

SFR(IE, 0xa8);

// interrupt related

// parallel port 0
SFR(P0, 0x80);

SFR(P0M0, 0x94);
SFR(P0M1, 0x93);

// external sfr
#define     IRC48MCR                (*(unsigned char volatile __XDATA *)0xfe07)

#endif
