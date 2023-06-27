#include "uart.h"
#include "address.h"

#define _D_U_MAIN_F_OSC     22118400L  // set main clock
#define _D_U_BAUD_RATE      115200L
#define _D_U_TM            (65536 -(_D_U_MAIN_F_OSC/_D_U_BAUD_RATE/4))

#define _D_U_SERIAL_CON     _D_S2CON
#define _D_U_PM0		    _D_P4M0
#define _D_U_PM1		    _D_P4M1
#define _D_U_SERIAL_BUF     _D_S2BUF
#define _D_U_TIMER_L        _D_T2L
#define _D_U_TIMER_H        _D_T2H


void uart_putc(unsigned char dat);
static unsigned char conv2hex_ascii(unsigned char num);


void uart_init(void) {

	_D_P_SW2 |= 1;         			// UART2 switch to P4.6 P4.7
	_D_U_PM0 = 0x00;  _D_U_PM1 = 0x00;
	_D_U_SERIAL_CON &= ~(1<<7);   	// 8n1. 8 bit data,  1 start bit, 1 stop bit, no crc.
	_D_U_TIMER_L  = _D_U_TM;
	_D_U_TIMER_H  = _D_U_TM>>8;
	_D_AUXR |= 0x14;	    		// 1T mode timer 2, auto reload, start running

}

void uart_putc(unsigned char dat) {
	_D_U_SERIAL_BUF  = dat;
	while((_D_U_SERIAL_CON & 2) == 0) {};
	_D_U_SERIAL_CON &= ~2;    // Clear Tx flag
}

char putchar(char c) {
	uart_putc(c);
	return c;
}

int puts(char * s) {
    int length = 0;
    while(*s) {
        putchar(*s);
        s++;
		length++;
    }
    return length;
}

void putHex8(volatile unsigned char number) {
    volatile unsigned char *cp = &number;
    puts("0x");
        unsigned char lower4bit = 0x0F & *(cp);
        unsigned char upper4bit = *(cp) >> 4;
        putchar(conv2hex_ascii(upper4bit));
        putchar(conv2hex_ascii(lower4bit));
}
static unsigned char conv2hex_ascii(unsigned char num) {
    if(num < 0xA) {
        return num+48;
    }
    return num+65-10;
}
