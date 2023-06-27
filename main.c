#include "address.h"
#include "usb/usb.h"
#include "usb/pipe_control/req_class.h"


// interrupt service routine
// void usb_isr(void) __interrupt (25) __using (2) {
INTERRUPT_USING(usb_isr, 25, 2) {
	// intrusb register indicate power interruption
	unsigned char intrusb	= usb_read_reg(INTRUSB);
	unsigned char intrin	= usb_read_reg(INTRIN1);
	unsigned char introut	= usb_read_reg(INTROUT1);
	// process power management interrupts
	if(intrusb & INTRUSB_RSUIF)	{
		d_intr("PowerManagement: Resume");
		usb_pm_resume();
	}
	if(intrusb & INTRUSB_RSTIF)	{
		d_intr("PowerManagement: Reset");
		usb_pm_reset();
	}
	// process control pipe request
	if(intrin & INTRIN1_EP0IF) {
		d_intr("Control Endpoint");
		control_request();
	}
	// process in transaction
	if(intrin & INTRIN1_EP1INIF) {
		d_intr("Endpoint 1 IN");
		ep1_in();
	}
	// process out transaction
	if(introut & INTROUT1_EP1OUTIF) {
		d_intr("Endpoint 1 OUT");
		ep1_out();
	}
	if(intrusb & INTRUSB_SUSIF) {
		d_intr("PowerManagement: Suspend");
		usb_pm_suspend();
	}
}

void sys_init();

void main() {
    sys_init();
	d_init();
	d_puts("\n\r \n\r Debug Facility Start Successfully \n\r \n\r");
    usb_init();
    timer_init();



    // EA = 1;
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

    IE |= (1 << 7);
}
