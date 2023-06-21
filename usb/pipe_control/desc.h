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

// device
__code extern char desc_device[18];

// configure and others
__code extern char desc_conf[41];
__code extern char desc_lang[4];
__code extern char desc_manufacturer[12];
__code extern char desc_product[30];

// class specific
__code extern char desc_hid_report[23];
__code extern char packet0[2];
__code extern char packet1[2];



#endif