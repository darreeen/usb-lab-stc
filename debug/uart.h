#ifndef _D_UART_
#define _D_UART_

void uart_init(void);
char putchar(char c);
int puts(char * s);
void putHex8(volatile unsigned char number);

#endif
