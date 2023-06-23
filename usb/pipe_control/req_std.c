#include "./req_std.h"

void get_status();

void clear_feature();
void set_feature();

void set_address();
void get_descriptor();
void set_descriptor();

void get_configuration();
void set_configuration();

void get_interface();
void set_interface();

void synch_frame(); // unsupported yet

void req_std() {
	switch (gRequest.bRequest)
	{
	case BR_GET_STATUS:
		get_status();
		break;
	case BR_CLEAR_FEATURE:
		clear_feature();
		break;
	case BR_SET_FEATURE:
		set_feature();
		break;
	case BR_SET_ADDRESS:
		set_address();
		break;
	case BR_GET_DESCRIPTOR:
		get_descriptor();
		break;
	case BR_SET_DESCRIPTOR:
		set_descriptor();
		break;
	case BR_GET_CONFIGURATION:
		get_configuration();
		break;
	case BR_SET_CONFIGURATION:
		set_configuration();
		break;
	case BR_GET_INTERFACE:
		set_interface();
		break;
	case BR_SET_INTERFACE:
		set_interface();
		break;
	case BR_SYNCH_FRAME:
		synch_frame();
		break;
	default:
		control_stall();
		break;
	}
}
