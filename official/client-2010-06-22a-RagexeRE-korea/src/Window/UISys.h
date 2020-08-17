#pragma once
#include "std/string"
#include "std/vector"


/// @see UIWindow::m_id
enum UIID
{
	ID_NOTHING = 121,
};


/// @see UIWindow::SendMsg()
enum UIMESSAGE
{
	UM_DEFPUSH                    = 0,
	UM_CANCELPUSH                 = 1,
	UM_COMMAND                    = 6,
	UM_RESIZE                     = 14,
	UM_SETINFO                    = 34,
	UM_ADDCHAT                    = 37,
};


void __cdecl CutString(const char* msg, mystd::vector<mystd::string>& strings, int maxNumCharLine);
