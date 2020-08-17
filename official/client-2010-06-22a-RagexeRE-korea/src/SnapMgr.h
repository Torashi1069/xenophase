#pragma once
class UIWindow;


class CSnapMgr
{
public:
	void BeginMove(UIWindow* masterWindow);
	bool IsRegisteredToSnap(UIWindow* window);
	void GetDeltaDrag(UIWindow* masterWindow, int& deltaDragX, int& deltaDragY);
	void MoveDelta(UIWindow* masterWindow, int deltaDragX, int deltaDragY);
	void EndMove(UIWindow* moveWindow);

private:
	//TODO

private:
	static hook_func<void (CSnapMgr::*)(UIWindow* masterWindow)> CSnapMgr::_BeginMove;
	static hook_func<bool (CSnapMgr::*)(UIWindow* window)> CSnapMgr::_IsRegisteredToSnap;
	static hook_func<void (CSnapMgr::*)(UIWindow* masterWindow, int& deltaDragX, int& deltaDragY)> CSnapMgr::_GetDeltaDrag;
	static hook_func<void (CSnapMgr::*)(UIWindow* masterWindow, int deltaDragX, int deltaDragY)> CSnapMgr::_MoveDelta;
	static hook_func<void (CSnapMgr::*)(UIWindow* moveWindow)> CSnapMgr::_EndMove;
};


extern CSnapMgr& g_snapMgr;
