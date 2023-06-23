#include "./transaction.h"

void control_in();

void control_out();

void control_stall();

/**
*	three stages during control transfer:
*	1. setup stage		 SETUP transaction
*	2. data stage	 	 IN/OUT transaction
*	3. status stage		 IN/OUT transactions
*/
