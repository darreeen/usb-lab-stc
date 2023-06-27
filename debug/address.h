// all constants here with _D_ prefix
// to easily remove from main projects
#ifndef _D_ADDRESS_
#define _D_ADDRESS_
#include "../compatible.h"



// Device registers
SFR(_D_P0, 0x80);
SFR(_D_P0M0, 0x94);
SFR(_D_P0M1, 0x93);
// essential
SFR(_D_P4M0, 0xb4);
SFR(_D_P4M1, 0xb3);

SFR(_D_P_SW2, 0xba);
SFR(_D_S2CON, 0x9a);
SFR(_D_S2BUF, 0x9b);

SFR(_D_T2L, 0xd7);  // timer as baud generator
SFR(_D_T2H, 0xd6);

SFR(_D_AUXR, 0x8e);

// registers in code

#endif
