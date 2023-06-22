#ifndef __USB_POWER_H_
#define __USB_POWER_H_

#include "utils.h"
#include "controller.h"

/**
* USB Power Management Related Functions
* with pm prefix
*/

void usb_pm_resume(void);
void usb_pm_reset(void);
void usb_pm_suspend(void);

#endif