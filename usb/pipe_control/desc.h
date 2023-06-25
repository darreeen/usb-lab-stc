/**
*	descriptors used during device setup
*	- device descriptor
*	- configure descriptor
*		- interface descriptor
*		- endpoint descriptor
*	- vendor string descriptor
*/

#ifndef __CTRL_TRANS_DESC_
#define __CTRL_TRANS_DESC_

#include "../../compatible.h"

// device
__CODE extern char desc_device[18];

// configure and others
__CODE extern char desc_conf[41];
__CODE extern char desc_lang[4];
__CODE extern char desc_manufacturer[12];
__CODE extern char desc_product[30];

// class specific
__CODE extern char desc_hid_report[43];
__CODE extern char packet0[2];
__CODE extern char packet1[2];



#endif
