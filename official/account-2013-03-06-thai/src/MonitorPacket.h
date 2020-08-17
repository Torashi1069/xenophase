#pragma once


enum
{
	HEADER_MA_REQ_HASH             = 0,
	HEADER_AM_RES_HASH             = 1,
	HEADER_MA_ENTER                = 2,
	HEADER_AM_ACCEPT_ENTER         = 3,
	HEADER_AM_REFUSE_ENTER         = 4,
	HEADER_AM_SERVER_STATE         = 5,
	HEADER_MA_CTRL_USER_CONNECTION = 6,
};


void InitMonitorPktLenMap();
