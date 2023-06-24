/**
*	IN/OUT/SETUP transactions handler for control transfer
*/

#ifndef __CTRL_TRANS_TRANSACTION_
#define __CTRL_TRANS_TRANSACTION_

void control_in();

void control_out();

// not a specific transfer type but for send stall packet
void control_stall();

#endif
