#ifndf __ADDRESS_
#define __ADDRESS_

// STC extend registers
// P_SW2 peripheral switch 2 
// b7 eaxfr enable external sfr  
__sfr _at (0xba) P_SW2;  // use this to access external sfr


// STC IO port configuration registers
// combine PxM0 with PxM1 to set register modes
__sfr _at (0xb2) P3M0;
__sfr _at (0xb1) P3M1;


// usb controller related registers
__sfr _at (0xf4) USBCON;
__sfr _at (0xdc) USBCLK;
__sfr _at (0xfc) USBADR;
__sfr _at (0xec) USBDAT;


#endif