#pragma once
#include "Window/UIFrameWnd.h"
#include "Struct.h"
class UIBitmapButton;


enum NMSGTYPE
{// new chat window message type
	NMSG_NONE                = 0,
	NMSG_CHAT                = 1,
	NMSG_WHISPER             = 2,
	NMSG_PARTY               = 3,
	NMSG_GUILD               = 4,
	NMSG_GET_ITEM            = 5,
	NMSG_EQUIP               = 6,
	NMSG_CHANGE_STATUS       = 7,
	NMSG_GET_ITEM_PARTY      = 8,
	NMSG_CHANGE_STATUS_PARTY = 9,
	NMSG_FAIL_SKILL          = 10,
	NEW_PARTY_SETUP          = 11,
	NMSG_DAMAGED_EQUIP       = 12,
	NMSG_SEIGE_INFO          = 13,
	NMSG_14                  = 14,
	NMSG_15                  = 15,
	NMSG_16                  = 16,
	//TODO
};


class UINewChatWnd : public UIFrameWnd
{
	UINewChatWnd();
	virtual ~UINewChatWnd();
	virtual void OnCreate(int cx, int cy);
	virtual void OnDraw();
	virtual void OnLBtnDown(int x, int y);
	virtual void OnMouseMove(int x, int y);
	virtual void OnLBtnUp(int x, int y);
	virtual int SendMsg(UIWindow* sender, int message, int val1, int val2, int val3, int val4);
	virtual bool GetTransBoxInfo2(BOXINFO* boxInfo);
	virtual void DrawBoxScreen2();
	virtual void Move(int x, int y);
	virtual void Resize(int cx, int cy);
	virtual void StoreInfo();
	virtual void SetShow(BOOL visible);
	void SetState(int state);
	void WriteChatToFile();
	void StickOnOff(bool stickOn);

public:
	/* this+  0 */ //UIFrameWnd baseclass_0;
	/* this+ 96 */ UIWindow* m_lastFocusChat_TODO; // UIEditCtrl
	/* this+100 */ UIWindow* m_resizer_TODO; // UIResizer
	/* this+104 */ UIWindow* m_commonChat_TODO; // UIChatEditCtrl
	/* this+108 */ UIWindow* m_whisperChat_TODO; // UIWhisperEditCtrl
	/* this+112 */ BOXINFO m_boxInfo;
	/* this+140 */ UIBitmapButton* m_buttons[4];
	/* this+156 */ int m_comboMode;
	/* this+160 */ mystd::vector<UIWindow*> field_A0_wndvec;
	/* this+176 */ UIBitmapButton* field_B0_btn;
	/* this+180 */ int field_B4;
	/* this+184 */ int field_B8;
	/* this+188 */ int field_BC;
	/* this+192 */ int field_C0;
	/* this+196 */ int m_tab;
	/* this+200 */ int m_saveState;
	/* this+204 */ int m_titleHeight;
	/* this+208 */ int m_titleWidth;
	/* this+212 */ int m_chatEditHeight;
	/* this+216 */ UIBitmapButton* m_btnStickOff;
	/* this+220 */ UIBitmapButton* m_btnOption;
	/* this+224 */ int field_E0;
	/* this+228 */ int field_E4;
	/* this+232 */ int field_E8;

private:
	static hook_func<void (UINewChatWnd::*)()> UINewChatWnd::_dtor;
	static hook_func<void (UINewChatWnd::*)(int cx, int cy)> UINewChatWnd::_OnCreate;
	static hook_func<void (UINewChatWnd::*)()> UINewChatWnd::_OnDraw;
	static hook_func<void (UINewChatWnd::*)(int x, int y)> UINewChatWnd::_OnLBtnDown;
	static hook_func<void (UINewChatWnd::*)(int x, int y)> UINewChatWnd::_OnMouseMove;
	static hook_func<void (UINewChatWnd::*)(int x, int y)> UINewChatWnd::_OnLBtnUp;
	static hook_func<int (UINewChatWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3, int val4)> UINewChatWnd::_SendMsg;
	static hook_func<bool (UINewChatWnd::*)(BOXINFO* boxInfo)> UINewChatWnd::_GetTransBoxInfo2;
	static hook_func<void (UINewChatWnd::*)()> UINewChatWnd::_DrawBoxScreen2;
	static hook_func<void (UINewChatWnd::*)(int x, int y)> UINewChatWnd::_Move;
	static hook_func<void (UINewChatWnd::*)(int cx, int cy)> UINewChatWnd::_Resize;
	static hook_func<void (UINewChatWnd::*)()> UINewChatWnd::_StoreInfo;
	static hook_func<void (UINewChatWnd::*)(BOOL visible)> UINewChatWnd::_SetShow;
	static hook_func<void (UINewChatWnd::*)(int state)> UINewChatWnd::_SetState;
	static hook_func<void (UINewChatWnd::*)()> UINewChatWnd::_WriteChatToFile;
};
C_ASSERT( sizeof UINewChatWnd == 236 );


struct UINewChatWndVtbl
{
	void* (UINewChatWnd::* scalar_deleting_destructor)(unsigned int flags);
	void (UIWindow::* Invalidate)();
	void (UIWindow::* InvalidateWallPaper)();
	void (UINewChatWnd::* Resize)(int cx, int cy);
	bool (UIFrameWnd::* IsFrameWnd)();
	bool (UIWindow::* IsUpdateNeed)();
	void (UINewChatWnd::* Move)(int x, int y);
	bool (UIWindow::* CanGetFocus)();
	bool (UIWindow::* GetTransBoxInfo)(BOXINFO* boxInfo);
	bool (UIWindow::* IsTransmitMouseInput)();
	bool (UIWindow::* ShouldDoHitTest)();
	void (UIWindow::* DragAndDrop)(int x, int y, const DRAG_INFO* const dragInfo);
	void (UINewChatWnd::* StoreInfo)();
	void (UIFrameWnd::* SaveOriginalPos)();
	void (UIFrameWnd::* MoveDelta)(int deltaDragX, int deltaDragY);
	COLORREF (UIWindow::* GetColor)();
	void (UINewChatWnd::* SetShow)(BOOL visible);
	void (UINewChatWnd::* OnCreate)(int cx, int cy);
	void (UIWindow::* OnDestroy)();
	void (UIWindow::* OnProcess)();
	void (UINewChatWnd::* OnDraw)();
	void (UIWindow::* OnRun)();
	void (UIWindow::* OnSize)(int cx, int cy);
	void (UIWindow::* OnBeginEdit)();
	void (UIWindow::* OnFinishEdit)();
	void (UINewChatWnd::* OnLBtnDown)(int x, int y);
	void (UIWindow::* OnLBtnDblClk)(int x, int y);
	void (UINewChatWnd::* OnMouseMove)(int x, int y);
	void (UIFrameWnd::* OnMouseHover)(int x, int y);
	void (UIWindow::* OnMouseShape)(int x, int y);
	void (UINewChatWnd::* OnLBtnUp)(int x, int y);
	void (UIWindow::* OnRBtnDown)(int x, int y);
	void (UIWindow::* OnRBtnUp)(int x, int y);
	void (UIWindow::* OnRBtnDblClk)(int x, int y);
	void (UIWindow::* OnWheel)(int wheel);
	void (UIFrameWnd::* RefreshSnap)();
	int (UINewChatWnd::* SendMsg)(UIWindow* sender, int message, int val1, int val2, int val3, int val4);
	bool (UINewChatWnd::* GetTransBoxInfo2)(BOXINFO* boxInfo);
	void (UINewChatWnd::* DrawBoxScreen2)();
};
