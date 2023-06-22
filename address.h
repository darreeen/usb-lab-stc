#ifndef __ADDRESS_
#define __ADDRESS_

// SDCC C IntelliSense Compatible
// https://sourceforge.net/p/sdcc/discussion/1864/thread/e049b17c55/
// https://sourceforge.net/p/sdcc/code/HEAD/tree/trunk/sdcc/device/include/mcs51/compiler.h
#ifndef __SDCC__
#define __SFRDEF(a,b) volatile unsigned char a;
#else
#define __SFRDEF(reg,addr) __sfr __at addr reg;
#endif

// STC extend registers
// P_SW2 peripheral switch 2
// b7 eaxfr enable external sfr
__SFRDEF()
__sfr __at (0xba) P_SW2;  // use this to access external sfr

// INTERRUPT related registers
__sfr __at (0xaf) IE2;

// STC IO port configuration registers
// combine PxM0 with PxM1 to set register modes
__sfr __at (0xb2) P3M0;
__sfr __at (0xb1) P3M1;


// usb controller related registers
__sfr __at (0xf4) USBCON;
__sfr __at (0xdc) USBCLK;
__sfr __at (0xfc) USBADR;
__sfr __at (0xec) USBDAT;


#endif
