#ifndef __DEBUG_

void d_init();
void d_puts(char * s);
void d_put_hex_8(unsigned char num);
void d_led();

// stages specific functions

void d_intr(char *s);
void d_std_req(char *s);
void d_class_req(char *s);
void d_vendor_req(char *s);

void d_stall_info(char *s, unsigned char v);
void d_req_detail(char *s);

#endif
