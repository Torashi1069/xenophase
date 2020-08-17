#pragma once


extern class CZSAcceptHandler& g_zsAcceptHandler;
extern class CGlobalVarDB& g_globalVarDB;
extern HINSTANCE& g_hInst;
extern HWND& g_hWnd;
extern BOOL& g_isPacketLog;
extern DWORD& g_curTime;
extern BOOL& g_storePasswordCheck;
extern const char g_infFile[];


struct WARP_POSITION
{
	WARP_POSITION()
	{
		this->xPos = 0;
		this->yPos = 0;
		memset(this->mapName, '\0', sizeof(this->mapName));
	}

	WARP_POSITION(const WARP_POSITION& in_rhs)
	{
		this->xPos = in_rhs.xPos;
		this->yPos = in_rhs.yPos;
		strcpy_s(this->mapName, countof(this->mapName), in_rhs.mapName);
	}

	/* this+0 */ short xPos;
	/* this+2 */ short yPos;
	/* this+4 */ char mapName[16];
};
