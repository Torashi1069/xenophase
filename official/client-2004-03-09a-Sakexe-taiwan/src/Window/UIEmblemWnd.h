#pragma once
#include "Window/UIFrameWnd.h"


class UIEmblemWnd : public UIFrameWnd
{
public:
	//UIEmblemWnd();
	//~UIEmblemWnd();
	//void OnCreate(int, int);
	//void OnDraw();
	//int SendMsg(UIWindow*, int, int, int, int);
	//void OnProcess();

public:
	/* this+  0 */ //UIFrameWnd baseclass_0;
	/* this+ 96 */ int m_posx;
	/* this+100 */ int m_posy;
	/* this+104 */ mystd::string m_fileName;
	/* this+120 */ unsigned long m_masterAid;
};
