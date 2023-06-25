/**
*	control pipe request handler
*/

#ifndef __CTRL_TRANS_HANDLER_
#define __CTRL_TRANS_HANDLER_

#include "../controller.h"
#include "../utils.h"
#include "transaction.h"
#include "req_std.h"
#include "req_class.h"
#include "req_vendor.h"

void control_request();

// holy blob, it's getting messy.
void ep1_out();
void ep1_in();

#endif
