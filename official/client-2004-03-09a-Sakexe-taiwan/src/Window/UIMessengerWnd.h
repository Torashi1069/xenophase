#pragma once
#include "Struct.h"
#include "Window/UIControl.h"
#include "Window/UIFrameWnd.h"


class UIMessengerGroupWnd : public UIFrameWnd
{
public:
	UIMessengerGroupWnd();
	virtual ~UIMessengerGroupWnd();
	virtual void OnCreate(int cx, int cy);
	virtual void OnDraw();
	virtual int SendMsg(UIWindow* sender, int message, int val1, int val2, int val3);
	virtual void StoreInfo();
	virtual void OnWheel(int wheel);
	virtual void OnLBtnDown(int x, int y);
	virtual void OnRBtnUp(int x, int y);
	virtual void OnLBtnDblClk(int x, int y);
	FRIEND_INFO GetItemInfo(int x, int y);
	FRIEND_INFO GetItemInfoBySequence(int sequence);
	void RecalcScrbarPos();

protected:
	/* this+  0 */ //UIFrameWnd baseclass_0;
	/* this+ 96 */ MessengerGroupWndInfo* m_info;
	/* this+100 */ UIScrollBar* m_scrollBar;
	/* this+104 */ UIRadioBtn* m_radioBtns[2];
	/* this+112 */ UIBitmapButton* m_sysButton;
	/* this+116 */ UIBitmapButton* m_button[5];
	/* this+136 */ UIResizer* m_resizer;
	/* this+140 */ UIStaticText* m_titleText;
	/* this+144 */ int m_viewOffset;
	/* this+148 */ int m_itemHorzNum;
	/* this+152 */ int m_itemVertNum;
	/* this+156 */ BOOL m_vertScrEnabled;
	/* this+160 */ mystd::list<FRIEND_INFO> m_itemList;
	/* this+172 */ int m_curRadioBtn;
	/* this+176 */ int m_curItem;
	/* this+180 */ mystd::vector<StringId> m_menuItems;

private:
	static hook_method<void (UIMessengerGroupWnd::*)(void)> UIMessengerGroupWnd::_OnDraw;
	static hook_method<int (UIMessengerGroupWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UIMessengerGroupWnd::_SendMsg;
	static hook_method<void (UIMessengerGroupWnd::*)(int x, int y)> UIMessengerGroupWnd::_OnLBtnDown;
	static hook_method<void (UIMessengerGroupWnd::*)(void)> UIMessengerGroupWnd::_RecalcScrbarPos;
};


class UIWhisperListWnd : public UIFrameWnd
{
public:
	UIWhisperListWnd();
	virtual ~UIWhisperListWnd();
	virtual void OnCreate(int cx, int cy);
	virtual void OnDraw();
	virtual void OnLBtnDblClk(int x, int y);
	virtual void OnLBtnDown(int x, int y);
	virtual void OnRBtnUp(int x, int y);
	virtual int SendMsg(UIWindow* sender, int message, int val1, int val2, int val3);
	virtual void StoreInfo();
	virtual void OnWheel(int wheel);
	void RecalcScrbarPos();
	int GetCurItem(int x, int y);
	void DeleteCurWhisperName();

protected:
	/* this+  0 */ //UIFrameWnd baseclass_0;
	/* this+ 96 */ MessengerGroupWndInfo* m_info;
	/* this+100 */ UIScrollBar* m_scrollBar;
	/* this+104 */ UIRadioBtn* m_radioBtns[2];
	/* this+112 */ UIBitmapButton* m_sysButton;
	/* this+116 */ UIBitmapButton* m_button[5];
	/* this+136 */ UIResizer* m_resizer;
	/* this+140 */ int m_viewOffset;
	/* this+144 */ int m_curItem;
	/* this+148 */ int m_itemHorzNum;
	/* this+152 */ int m_itemVertNum;
	/* this+156 */ int m_vertScrEnabled;
	/* this+160 */ int m_curRadioBtn;
	/* this+164 */ mystd::vector<StringId> m_menuItems;
	/* this+180 */ mystd::list<mystd::string> m_whisperNameList;

private:
	static hook_method<void (UIWhisperListWnd::*)(int cx, int cy)> UIWhisperListWnd::_OnCreate;
	static hook_method<void (UIWhisperListWnd::*)(void)> UIWhisperListWnd::_OnDraw;
	static hook_method<int (UIWhisperListWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UIWhisperListWnd::_SendMsg;
	static hook_method<void (UIWhisperListWnd::*)(int wheel)> UIWhisperListWnd::_OnWheel;
	static hook_method<void (UIWhisperListWnd::*)(void)> UIWhisperListWnd::_RecalcScrbarPos;
	static hook_method<int (UIWhisperListWnd::*)(int x, int y)> UIWhisperListWnd::_GetCurItem;
	static hook_method<void (UIWhisperListWnd::*)(void)> UIWhisperListWnd::_DeleteCurWhisperName;
};


class UIFriendOptionWnd : public UIFrameWnd
{
public:
	UIFriendOptionWnd();
	virtual ~UIFriendOptionWnd();
	virtual void OnCreate(int cx, int cy);
	virtual void OnDraw();
	virtual int SendMsg(UIWindow* sender, int message, int val1, int val2, int val3);
	virtual void StoreInfo();

protected:
	/* this+  0 */ //UIFrameWnd baseclass_0;
	/* this+ 96 */ FriendOptionWndInfo* m_info;
	/* this+100 */ UICheckBox* m_showWhisperWndCheckBox;
	/* this+104 */ UICheckBox* m_showFriendWhisperWndCheckBox;
	/* this+108 */ UICheckBox* m_playWhisperOpenSoundCheckBox;
	/* this+112 */ UIBitmapButton* m_sysButton;
};
