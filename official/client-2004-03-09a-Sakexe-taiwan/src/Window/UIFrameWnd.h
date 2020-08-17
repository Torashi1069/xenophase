#pragma once
#include "ItemInfo.h"
#include "Struct.h"
#include "Window/UIControl.h"
#include "Window/UIControl2.h"
#include "Window/UIRectInfo.h"
#include "Window/UISys.h"
class UIBitmapEditCtrl;
class UIChatEditCtrl;
class UIChatHisBox;
class UIChatHisBox2;
class UIEditCtrl;
class UINoneVisibleButton;
class UIResizer;
class UISlotBitmap;


class UIFrameWnd : public UIWindow
{
	struct vtable_t // const UIFrameWnd::`vftable'
	{
		void* (UIFrameWnd::* scalar_deleting_destructor)(unsigned int flags);
		void (UIWindow::* Invalidate)(void);
		void (UIWindow::* InvalidateWallPaper)(void);
		void (UIWindow::* Resize)(int cx, int cy);
		bool (UIFrameWnd::* IsFrameWnd)(void);
		bool (UIWindow::* IsUpdateNeed)(void);
		void (UIFrameWnd::* Move)(int x, int y);
		bool (UIWindow::* CanGetFocus)(void);
		bool (UIWindow::* GetTransBoxInfo)(BOXINFO* boxInfo);
		bool (UIWindow::* IsTransmitMouseInput)(void);

		bool (UIWindow::* ShouldDoHitTest)(void);
		void (UIWindow::* DragAndDrop)(int x, int y, const DRAG_INFO* const dragInfo);
		void (UIWindow::* StoreInfo)(void);
		void (UIFrameWnd::* SaveOriginalPos)(void);
		void (UIFrameWnd::* MoveDelta)(int deltaDragX, int deltaDragY);
		unsigned long (UIWindow::* GetColor)(void);
		void (UIWindow::* SetShow)(int visible);
		void (UIWindow::* OnCreate)(int cx, int cy);
		void (UIWindow::* OnDestroy)(void);
		void (UIWindow::* OnProcess)(void);

		void (UIWindow::* OnDraw)(void);
		void (UIWindow::* OnDraw2)(void);
		void (UIWindow::* OnRun)(void);
		void (UIWindow::* OnSize)(int cx, int cy);
		void (UIWindow::* OnBeginEdit)(void);
		void (UIWindow::* OnFinishEdit)(void);
		void (UIFrameWnd::* OnLBtnDown)(int x, int y);
		void (UIWindow::* OnLBtnDblClk)(int x, int y);
		void (UIFrameWnd::* OnMouseMove)(int x, int y);
		void (UIFrameWnd::* OnMouseHover)(int x, int y);

		void (UIWindow::* OnMouseShape)(int x, int y);
		void (UIFrameWnd::* OnLBtnUp)(int x, int y);
		void (UIWindow::* OnRBtnDown)(int x, int y);
		void (UIWindow::* OnRBtnUp)(int x, int y);
		void (UIWindow::* OnRBtnDblClk)(int x, int y);
		void (UIWindow::* OnWheel)(int wheel);
		void (UIFrameWnd::* RefreshSnap)(void);
		int (UIFrameWnd::* SendMsg)(UIWindow* sender, int message, int val1, int val2, int val3);
	};

	/* this+ 0 */ public: //UIWindow baseclass_0;
	/* this+72 */ protected: int m_startGlobalX;
	/* this+76 */ protected: int m_startGlobalY;
	/* this+80 */ protected: int m_orgX;
	/* this+84 */ protected: int m_orgY;
	/* this+88 */ protected: int m_defPushId;
	/* this+92 */ protected: int m_defCancelPushId;

	public: UIFrameWnd::UIFrameWnd(void);
	public: virtual UIFrameWnd::~UIFrameWnd(void);
	public: virtual void UIFrameWnd::OnLBtnDown(int x, int y);
	public: virtual void UIFrameWnd::OnMouseMove(int x, int y);
	public: virtual void UIFrameWnd::OnMouseHover(int x, int y);
	public: virtual void UIFrameWnd::OnLBtnUp(int x, int y);
	public: virtual int UIFrameWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3);
	public: virtual void UIFrameWnd::Move(int x, int y);
	public: virtual bool UIFrameWnd::IsFrameWnd(void);
	public: virtual void UIFrameWnd::SaveOriginalPos(void);
	public: virtual void UIFrameWnd::MoveDelta(int deltaDragX, int deltaDragY);
	public: virtual void UIFrameWnd::RefreshSnap(void);
	protected: void UIFrameWnd::DrawItem(int x, int y, const ITEM_INFO& iteminfo, bool forceidentified);
	protected: void UIFrameWnd::DrawItem(int x, int y, const char* itemName, bool identified);
	protected: void UIFrameWnd::DrawItemWithCount(int x, int y, const ITEM_INFO& iteminfo, bool forceidentified, bool boldtext);
	protected: void UIFrameWnd::DrawItemFrame(int x, int y);
	protected: void UIFrameWnd::DrawLatticeFrame(int x, int y, int width, int height);
	protected: int UIFrameWnd::DrawItemText(int x, int y, const ITEM_INFO& iteminfo, unsigned long color, int fontType, int fontHeight);
	protected: int UIFrameWnd::DrawItemTextRect(int x, int y, int width, const ITEM_INFO& iteminfo, unsigned long color, int fontType, int fontHeight);
	protected: int UIFrameWnd::DrawItemObtainTextRect(int x, int y, int width, const ITEM_INFO& iteminfo, unsigned long color, int fontType, int fontHeight);

private:
	static hook_method<void (UIFrameWnd::*)(int x, int y)> UIFrameWnd::_OnLBtnDown;
	static hook_method<void (UIFrameWnd::*)(int x, int y)> UIFrameWnd::_OnMouseMove;
	static hook_method<void (UIFrameWnd::*)(int x, int y)> UIFrameWnd::_OnMouseHover;
	static hook_method<void (UIFrameWnd::*)(int x, int y)> UIFrameWnd::_OnLBtnUp;
	static hook_method<int (UIFrameWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UIFrameWnd::_SendMsg;
	static hook_method<void (UIFrameWnd::*)(int x, int y)> UIFrameWnd::_Move;
	static hook_method<bool (UIFrameWnd::*)(void)> UIFrameWnd::_IsFrameWnd;
	static hook_method<void (UIFrameWnd::*)(void)> UIFrameWnd::_SaveOriginalPos;
	static hook_method<void (UIFrameWnd::*)(int deltaDragX, int deltaDragY)> UIFrameWnd::_MoveDelta;
	static hook_method<void (UIFrameWnd::*)(void)> UIFrameWnd::_RefreshSnap;
	static hook_method<void (UIFrameWnd::*)(int x, int y, const ITEM_INFO& iteminfo, bool forceidentified)> UIFrameWnd::_DrawItem;
	static hook_method<void (UIFrameWnd::*)(int x, int y, const char* itemName, bool identified)> UIFrameWnd::_DrawItem2;
	static hook_method<void (UIFrameWnd::*)(int x, int y, const ITEM_INFO& iteminfo, bool forceidentified, bool boldtext)> UIFrameWnd::_DrawItemWithCount;
	static hook_method<void (UIFrameWnd::*)(int x, int y)> UIFrameWnd::_DrawItemFrame;
	static hook_method<void (UIFrameWnd::*)(int x, int y, int width, int height)> UIFrameWnd::_DrawLatticeFrame;
	static hook_method<int (UIFrameWnd::*)(int x, int y, const ITEM_INFO& iteminfo, unsigned long color, int fontType, int fontHeight)> UIFrameWnd::_DrawItemText;
	static hook_method<int (UIFrameWnd::*)(int x, int y, int width, const ITEM_INFO& iteminfo, unsigned long color, int fontType, int fontHeight)> UIFrameWnd::_DrawItemTextRect;
	static hook_method<int (UIFrameWnd::*)(int x, int y, int width, const ITEM_INFO& iteminfo, unsigned long color, int fontType, int fontHeight)> UIFrameWnd::_DrawItemObtainTextRect;
};


class UISelectServerWnd : public UIFrameWnd
{
	struct vtable_t
	{
		void* (UISelectServerWnd::* scalar_deleting_destructor)(unsigned int flags);
		void (UIWindow::* Invalidate)(void);
		void (UIWindow::* InvalidateWallPaper)(void);
		void (UIWindow::* Resize)(int cx, int cy);
		bool (UIFrameWnd::* IsFrameWnd)(void);
		bool (UIWindow::* IsUpdateNeed)(void);
		void (UIFrameWnd::* Move)(int x, int y);
		bool (UIWindow::* CanGetFocus)(void);
		bool (UIWindow::* GetTransBoxInfo)(BOXINFO* boxInfo);
		bool (UIWindow::* IsTransmitMouseInput)(void);

		bool (UIWindow::* ShouldDoHitTest)(void);
		void (UIWindow::* DragAndDrop)(int x, int y, const DRAG_INFO* const dragInfo);
		void (UIWindow::* StoreInfo)(void);
		void (UIFrameWnd::* SaveOriginalPos)(void);
		void (UIFrameWnd::* MoveDelta)(int deltaDragX, int deltaDragY);
		unsigned long (UIWindow::* GetColor)(void);
		void (UIWindow::* SetShow)(int);
		void (UISelectServerWnd::* OnCreate)(int cx, int cy);
		void (UISelectServerWnd::* OnDestroy)(void);
		void (UIWindow::* OnProcess)(void);

		void (UISelectServerWnd::* OnDraw)(void);
		void (UIWindow::* OnDraw2)(void);
		void (UIWindow::* OnRun)(void);
		void (UIWindow::* OnSize)(int cx, int cy);
		void (UIWindow::* OnBeginEdit)(void);
		void (UIWindow::* OnFinishEdit)(void);
		void (UIFrameWnd::* OnLBtnDown)(int x, int y);
		void (UIWindow::* OnLBtnDblClk)(int x, int y);
		void (UIFrameWnd::* OnMouseMove)(int x, int y);
		void (UIFrameWnd::* OnMouseHover)(int x, int y);

		void (UIWindow::* OnMouseShape)(int x, int y);
		void (UIFrameWnd::* OnLBtnUp)(int x, int y);
		void (UIWindow::* OnRBtnDown)(int x, int y);
		void (UIWindow::* OnRBtnUp)(int x, int y);
		void (UIWindow::* OnRBtnDblClk)(int x, int y);
		void (UIWindow::* OnWheel)(int wheel);
		void (UIFrameWnd::* RefreshSnap)(void);
		int (UISelectServerWnd::* SendMsg)(UIWindow* sender, int message, int val1, int val2, int val3);
	};

	/* this+  0 */ public: //UIFrameWnd baseclass_0;
	/* this+ 96 */ public: UIListBox* m_serverList;
	/* this+100 */ private: mystd::string m_regKey;
	/* this+116 */ private: int m_defaultCurItem;
	/* this+120 */ private: int m_target;
	/* this+124 */ private: UIBitmapButton* m_exitButton;

	public: UISelectServerWnd::UISelectServerWnd(void);
	public: virtual UISelectServerWnd::~UISelectServerWnd(void);
	public: virtual void UISelectServerWnd::OnCreate(int cx, int cy);
	public: virtual void UISelectServerWnd::OnDestroy(void);
	public: virtual void UISelectServerWnd::OnDraw(void);
	public: virtual int UISelectServerWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3);
	public: void UISelectServerWnd::InitDefaultCurItemFromReg(const char* regkey);
	public: void UISelectServerWnd::SaveCurItemToReg(const char* regkey);

private:
	static hook_method<void (UISelectServerWnd::*)(int cx, int cy)> UISelectServerWnd::_OnCreate;
	static hook_method<void (UISelectServerWnd::*)(void)> UISelectServerWnd::_OnDestroy;
	static hook_method<void (UISelectServerWnd::*)(void)> UISelectServerWnd::_OnDraw;
	static hook_method<int (UISelectServerWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UISelectServerWnd::_SendMsg;
	static hook_method<void (UISelectServerWnd::*)(const char* regkey)> UISelectServerWnd::_InitDefaultCurItemFromReg;
	static hook_method<void (UISelectServerWnd::*)(const char* regkey)> UISelectServerWnd::_SaveCurItemToReg;
};


class UILoginWnd : public UIFrameWnd
{
	struct vtable_t
	{
		void* (UILoginWnd::* scalar_deleting_destructor)(unsigned int flags);
		void (UIWindow::* Invalidate)(void);
		void (UIWindow::* InvalidateWallPaper)(void);
		void (UIWindow::* Resize)(int cx, int cy);
		bool (UIFrameWnd::* IsFrameWnd)(void);
		bool (UIWindow::* IsUpdateNeed)(void);
		void (UIFrameWnd::* Move)(int x, int y);
		bool (UIWindow::* CanGetFocus)(void);
		bool (UIWindow::* GetTransBoxInfo)(BOXINFO* boxInfo);
		bool (UIWindow::* IsTransmitMouseInput)(void);

		bool (UIWindow::* ShouldDoHitTest)(void);
		void (UIWindow::* DragAndDrop)(int x, int y, const DRAG_INFO* const dragInfo);
		void (UIWindow::* StoreInfo)(void);
		void (UIFrameWnd::* SaveOriginalPos)(void);
		void (UIFrameWnd::* MoveDelta)(int deltaDragX, int deltaDragY);
		unsigned long (UIWindow::* GetColor)(void);
		void (UIWindow::* SetShow)(int);
		void (UILoginWnd::* OnCreate)(int cx, int cy);
		void (UILoginWnd::* OnDestroy)(void);
		void (UIWindow::* OnProcess)(void);

		void (UILoginWnd::* OnDraw)(void);
		void (UIWindow::* OnDraw2)(void);
		void (UIWindow::* OnRun)(void);
		void (UIWindow::* OnSize)(int cx, int cy);
		void (UIWindow::* OnBeginEdit)(void);
		void (UIWindow::* OnFinishEdit)(void);
		void (UIFrameWnd::* OnLBtnDown)(int x, int y);
		void (UIWindow::* OnLBtnDblClk)(int x, int y);
		void (UIFrameWnd::* OnMouseMove)(int x, int y);
		void (UIFrameWnd::* OnMouseHover)(int x, int y);

		void (UIWindow::* OnMouseShape)(int x, int y);
		void (UIFrameWnd::* OnLBtnUp)(int x, int y);
		void (UIWindow::* OnRBtnDown)(int x, int y);
		void (UIWindow::* OnRBtnUp)(int x, int y);
		void (UIWindow::* OnRBtnDblClk)(int x, int y);
		void (UIWindow::* OnWheel)(int wheel);
		void (UIFrameWnd::* RefreshSnap)(void);
		int (UILoginWnd::* SendMsg)(UIWindow* sender, int message, int val1, int val2, int val3);
	};

	/* this+  0 */ public: //UIFrameWnd baseclass_0;
	/* this+ 96 */ public: UIEditCtrl* m_login;
	/* this+100 */ public: UIEditCtrl* m_password;
	/* this+104 */ public: int m_isCheckOn;
	/* this+108 */ public: UIBitmapButton* m_cancelButton;

	public: UILoginWnd::UILoginWnd(void);
	public: virtual UILoginWnd::~UILoginWnd(void);
	public: virtual void UILoginWnd::OnCreate(int cx, int cy);
	public: virtual void UILoginWnd::OnDestroy(void);
	public: virtual void UILoginWnd::OnDraw(void);
	public: virtual int UILoginWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3);
	public: void UILoginWnd::StoreInfo(void);
	public: void UILoginWnd::InitFromReg(void);
	public: void UILoginWnd::WriteToReg(void);
	public: void UILoginWnd::OpenRegistPage(void);

private:
	static hook_method<void (UILoginWnd::*)(int cx, int cy)> UILoginWnd::_OnCreate;
	static hook_method<void (UILoginWnd::*)(void)> UILoginWnd::_OnDestroy;
	static hook_method<void (UILoginWnd::*)(void)> UILoginWnd::_OnDraw;
	static hook_method<int  (UILoginWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UILoginWnd::_SendMsg;
	static hook_method<void (UILoginWnd::*)(void)> UILoginWnd::_StoreInfo;
	static hook_method<void (UILoginWnd::*)(void)> UILoginWnd::_InitFromReg;
	static hook_method<void (UILoginWnd::*)(void)> UILoginWnd::_WriteToReg;
	static hook_method<void (UILoginWnd::*)(void)> UILoginWnd::_OpenRegistPage;
};


class UINoticeWnd : public UIFrameWnd
{
	struct vtable_t
	{
		void* (UINoticeWnd::* scalar_deleting_destructor)(unsigned int flags);
		void (UIWindow::* Invalidate)(void);
		void (UIWindow::* InvalidateWallPaper)(void);
		void (UIWindow::* Resize)(int cx, int cy);
		bool (UIFrameWnd::* IsFrameWnd)(void);
		bool (UIWindow::* IsUpdateNeed)(void);
		void (UIFrameWnd::* Move)(int x, int y);
		bool (UIWindow::* CanGetFocus)(void);
		bool (UIWindow::* GetTransBoxInfo)(BOXINFO* boxInfo);
		bool (UIWindow::* IsTransmitMouseInput)(void);

		bool (UIWindow::* ShouldDoHitTest)(void);
		void (UIWindow::* DragAndDrop)(int x, int y, const DRAG_INFO* const dragInfo);
		void (UIWindow::* StoreInfo)(void);
		void (UIFrameWnd::* SaveOriginalPos)(void);
		void (UIFrameWnd::* MoveDelta)(int deltaDragX, int deltaDragY);
		unsigned long (UIWindow::* GetColor)(void);
		void (UIWindow::* SetShow)(int visible);
		void (UINoticeWnd::* OnCreate)(int cx, int cy);
		void (UINoticeWnd::* OnDestroy)(void);
		void (UIWindow::* OnProcess)(void);

		void (UINoticeWnd::* OnDraw)(void);
		void (UIWindow::* OnDraw2)(void);
		void (UIWindow::* OnRun)(void);
		void (UIWindow::* OnSize)(int cx, int cy);
		void (UIWindow::* OnBeginEdit)(void);
		void (UIWindow::* OnFinishEdit)(void);
		void (UIFrameWnd::* OnLBtnDown)(int x, int y);
		void (UIWindow::* OnLBtnDblClk)(int x, int y);
		void (UIFrameWnd::* OnMouseMove)(int x, int y);
		void (UINoticeWnd::* OnMouseHover)(int x, int y);

		void (UIWindow::* OnMouseShape)(int x, int y);
		void (UIFrameWnd::* OnLBtnUp)(int x, int y);
		void (UIWindow::* OnRBtnDown)(int x, int y);
		void (UIWindow::* OnRBtnUp)(int x, int y);
		void (UIWindow::* OnRBtnDblClk)(int x, int y);
		void (UINoticeWnd::* OnWheel)(int wheel);
		void (UIFrameWnd::* RefreshSnap)(void);
		int (UINoticeWnd::* SendMsg)(UIWindow* sender, int message, int val1, int val2, int val3);
	};

	/* this+  0 */ public: //UIFrameWnd baseclass_0;
	/* this+ 96 */ public: UIStaticText* m_NoticeMessage[21];
	/* this+180 */ public: int m_NoticeTotalLine;
	/* this+184 */ public: int m_NoticeDisplayLine;
	/* this+188 */ public: char* m_NoticeFileName;
	/* this+192 */ public: int m_TotalPage;
	/* this+196 */ public: int m_PresentPage;
	/* this+200 */ public: int m_PageStartLine[10];
	/* this+240 */ public: int m_PageLastLine[10];
	/* this+280 */ public: int m_PagePresentLine;
	/* this+284 */ protected: UIScrollBar* m_scrollBar;

	public: UINoticeWnd::UINoticeWnd(void);
	public: virtual UINoticeWnd::~UINoticeWnd(void);
	public: virtual void UINoticeWnd::OnCreate(int cx, int cy);
	public: virtual void UINoticeWnd::OnDestroy(void);
	public: virtual void UINoticeWnd::OnDraw(void);
	public: virtual void UINoticeWnd::OnWheel(int wheel);
	public: virtual void UINoticeWnd::OnMouseHover(int x, int y);
	public: virtual int UINoticeWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3);
	public: void UINoticeWnd::PrintNotice(void);

private:
	static hook_method<void (UINoticeWnd::*)(int cx, int cy)> UINoticeWnd::_OnCreate;
	static hook_method<void (UINoticeWnd::*)(void)> UINoticeWnd::_OnDestroy;
	static hook_method<void (UINoticeWnd::*)(void)> UINoticeWnd::_OnDraw;
	static hook_method<void (UINoticeWnd::*)(int wheel)> UINoticeWnd::_OnWheel;
	static hook_method<void (UINoticeWnd::*)(int x, int y)> UINoticeWnd::_OnMouseHover;
	static hook_method<int (UINoticeWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UINoticeWnd::_SendMsg;
	static hook_method<void (UINoticeWnd::*)(void)> UINoticeWnd::_PrintNotice;
};


class UIMakeCharWnd : public UIFrameWnd
{
	struct vtable_t
	{
		void* (UIMakeCharWnd::* scalar_deleting_destructor)(unsigned int flags);
		void (UIWindow::* Invalidate)(void);
		void (UIWindow::* InvalidateWallPaper)(void);
		void (UIWindow::* Resize)(int cx, int cy);
		bool (UIFrameWnd::* IsFrameWnd)(void);
		bool (UIWindow::* IsUpdateNeed)(void);
		void (UIFrameWnd::* Move)(int x, int y);
		bool (UIWindow::* CanGetFocus)(void);
		bool (UIWindow::* GetTransBoxInfo)(BOXINFO* boxInfo);
		bool (UIWindow::* IsTransmitMouseInput)(void);

		bool (UIWindow::* ShouldDoHitTest)(void);
		void (UIWindow::* DragAndDrop)(int x, int y, const DRAG_INFO* const dragInfo);
		void (UIWindow::* StoreInfo)(void);
		void (UIFrameWnd::* SaveOriginalPos)(void);
		void (UIFrameWnd::* MoveDelta)(int deltaDragX, int deltaDragY);
		unsigned long (UIWindow::* GetColor)(void);
		void (UIWindow::* SetShow)(int visible);
		void (UIMakeCharWnd::* OnCreate)(int cx, int cy);
		void (UIMakeCharWnd::* OnDestroy)(void);
		void (UIMakeCharWnd::* OnProcess)(void);

		void (UIMakeCharWnd::* OnDraw)(void);
		void (UIWindow::* OnDraw2)(void);
		void (UIWindow::* OnRun)(void);
		void (UIWindow::* OnSize)(int cx, int cy);
		void (UIWindow::* OnBeginEdit)(void);
		void (UIWindow::* OnFinishEdit)(void);
		void (UIFrameWnd::* OnLBtnDown)(int x, int y);
		void (UIWindow::* OnLBtnDblClk)(int x, int y);
		void (UIFrameWnd::* OnMouseMove)(int x, int y);
		void (UIFrameWnd::* OnMouseHover)(int x, int y);

		void (UIWindow::* OnMouseShape)(int x, int y);
		void (UIFrameWnd::* OnLBtnUp)(int x, int y);
		void (UIWindow::* OnRBtnDown)(int x, int y);
		void (UIWindow::* OnRBtnUp)(int x, int y);
		void (UIWindow::* OnRBtnDblClk)(int x, int y);
		void (UIWindow::* OnWheel)(int wheel);
		void (UIFrameWnd::* RefreshSnap)(void);
		int (UIMakeCharWnd::* SendMsg)(UIWindow* sender, int message, int val1, int val2, int val3);
	};

	/* this+  0 */ public: //UIFrameWnd baseclass_0;
	/* this+ 96 */ public: UIBitmapEditCtrl* m_nameEditCtrl;
	/* this+100 */ public: CHARACTER_INFO m_charInfo;
	/* this+208 */ private: viewSprite m_viewChar;
	/* this+444 */ private: UIStaticText* m_text[6];

	public: UIMakeCharWnd::UIMakeCharWnd(void);
	public: virtual UIMakeCharWnd::~UIMakeCharWnd(void);
	public: virtual void UIMakeCharWnd::OnCreate(int cx, int cy);
	public: virtual void UIMakeCharWnd::OnProcess(void);
	public: virtual void UIMakeCharWnd::OnDestroy(void);
	public: virtual void UIMakeCharWnd::OnDraw(void);
	public: virtual int UIMakeCharWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3);
	public: void UIMakeCharWnd::DrawHexagon(void);
	public: void UIMakeCharWnd::MakeButton(void);
	public: void UIMakeCharWnd::InitTextControls(void);

private:
	static hook_method<void (UIMakeCharWnd::*)(int cx, int cy)> UIMakeCharWnd::_OnCreate;
	static hook_method<void (UIMakeCharWnd::*)(void)> UIMakeCharWnd::_OnProcess;
	static hook_method<void (UIMakeCharWnd::*)(void)> UIMakeCharWnd::_OnDestroy;
	static hook_method<void (UIMakeCharWnd::*)(void)> UIMakeCharWnd::_OnDraw;
	static hook_method<int (UIMakeCharWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UIMakeCharWnd::_SendMsg;
	static hook_method<void (UIMakeCharWnd::*)(void)> UIMakeCharWnd::_DrawHexagon;
	static hook_method<void (UIMakeCharWnd::*)(void)> UIMakeCharWnd::_MakeButton;
	static hook_method<void (UIMakeCharWnd::*)(void)> UIMakeCharWnd::_InitTextControls;
};


class UIChatWnd : public UIFrameWnd
{
	struct vtable_t
	{
		void* (UIChatWnd::* scalar_deleting_destructor)(unsigned int flags);
		void (UIWindow::* Invalidate)(void);
		void (UIWindow::* InvalidateWallPaper)(void);
		void (UIChatWnd::* Resize)(int cx, int cy);
		bool (UIFrameWnd::* IsFrameWnd)(void);
		bool (UIWindow::* IsUpdateNeed)(void);
		void (UIChatWnd::* Move)(int x, int y);
		bool (UIWindow::* CanGetFocus)(void);
		bool (UIChatWnd::* GetTransBoxInfo)(BOXINFO* boxInfo);
		bool (UIWindow::* IsTransmitMouseInput)(void);

		bool (UIWindow::* ShouldDoHitTest)(void);
		void (UIWindow::* DragAndDrop)(int x, int y, const DRAG_INFO* const dragInfo);
		void (UIChatWnd::* StoreInfo)(void);
		void (UIFrameWnd::* SaveOriginalPos)(void);
		void (UIFrameWnd::* MoveDelta)(int deltaDragX, int deltaDragY);
		unsigned long (UIWindow::* GetColor)(void);
		void (UIChatWnd::* SetShow)(int visible);
		void (UIChatWnd::* OnCreate)(int cx, int cy);
		void (UIWindow::* OnDestroy)(void);
		void (UIWindow::* OnProcess)(void);

		void (UIChatWnd::* OnDraw)(void);
		void (UIChatWnd::* OnDraw2)(void);
		void (UIWindow::* OnRun)(void);
		void (UIWindow::* OnSize)(int cx, int cy);
		void (UIWindow::* OnBeginEdit)(void);
		void (UIWindow::* OnFinishEdit)(void);
		void (UIChatWnd::* OnLBtnDown)(int x, int y);
		void (UIWindow::* OnLBtnDblClk)(int x, int y);
		void (UIChatWnd::* OnMouseMove)(int x, int y);
		void (UIFrameWnd::* OnMouseHover)(int x, int y);

		void (UIWindow::* OnMouseShape)(int x, int y);
		void (UIChatWnd::* OnLBtnUp)(int x,int y);
		void (UIWindow::* OnRBtnDown)(int x, int y);
		void (UIWindow::* OnRBtnUp)(int x, int y);
		void (UIWindow::* OnRBtnDblClk)(int x, int y);
		void (UIWindow::* OnWheel)(int wheel);
		void (UIFrameWnd::* RefreshSnap)(void);
		int (UIChatWnd::* SendMsg)(UIWindow* sender, int message, int val1, int val2, int val3);
	};

	/* this+  0 */ public: //UIFrameWnd baseclass_0;
	/* this+ 96 */ public: UIEditCtrl* m_lastFocusChat;
	/* this+100 */ public: UIResizer* m_resizer;
	/* this+104 */ public: UIChatEditCtrl* m_commonChat;
	/* this+108 */ public: UIWhisperEditCtrl* m_whisperChat;
	/* this+112 */ public: UIChatHisBox* m_listBox;
	/* this+116 */ public: BOXINFO m_boxInfo;
	/* this+144 */ public: UIBitmapButton* m_buttons[3];
	/* this+156 */ public: int m_comboMode;

	public: UIChatWnd::UIChatWnd(void);
	public: virtual UIChatWnd::~UIChatWnd(void);
	public: virtual void UIChatWnd::OnCreate(int cx, int cy);
	public: virtual void UIChatWnd::OnDraw(void);
	public: virtual void UIChatWnd::OnDraw2(void);
	public: virtual void UIChatWnd::OnLBtnDown(int x, int y);
	public: virtual void UIChatWnd::OnMouseMove(int x, int y);
	public: virtual void UIChatWnd::OnLBtnUp(int x,int y);
	public: virtual int UIChatWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3);
	public: virtual bool UIChatWnd::GetTransBoxInfo(BOXINFO* boxInfo);
	public: virtual void UIChatWnd::Move(int x, int y);
	public: virtual void UIChatWnd::Resize(int cx, int cy);
	public: virtual void UIChatWnd::StoreInfo(void);
	public: virtual void UIChatWnd::SetShow(int visible);
	public: void UIChatWnd::SetState(int state);
	//public: int GetState(void);
	public: void UIChatWnd::WriteChatToFile(void);
	//public: void WriteChatToReportFile(void);

private:
	static hook_method<void (UIChatWnd::*)(int cx, int cy)> UIChatWnd::_OnCreate;
	static hook_method<void (UIChatWnd::*)(void)> UIChatWnd::_OnDraw;
	static hook_method<void (UIChatWnd::*)(void)> UIChatWnd::_OnDraw2;
	static hook_method<void (UIChatWnd::*)(int x, int y)> UIChatWnd::_OnLBtnDown;
	static hook_method<void (UIChatWnd::*)(int x, int y)> UIChatWnd::_OnMouseMove;
	static hook_method<void (UIChatWnd::*)(int x,int y)> UIChatWnd::_OnLBtnUp;
	static hook_method<int (UIChatWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UIChatWnd::_SendMsg;
	static hook_method<bool (UIChatWnd::*)(BOXINFO* boxInfo)> UIChatWnd::_GetTransBoxInfo;
	static hook_method<void (UIChatWnd::*)(int x, int y)> UIChatWnd::_Move;
	static hook_method<void (UIChatWnd::*)(int cx, int cy)> UIChatWnd::_Resize;
	static hook_method<void (UIChatWnd::*)(void)> UIChatWnd::_StoreInfo;
	static hook_method<void (UIChatWnd::*)(int visible)> UIChatWnd::_SetShow;
	static hook_method<void (UIChatWnd::*)(int state)> UIChatWnd::_SetState;
	static hook_method<void (UIChatWnd::*)(void)> UIChatWnd::_WriteChatToFile;
};


class UIChatRoomWnd : public UIFrameWnd
{
	struct vtable_t
	{
		//TODO
	};

	/* this+  0 */ public: //UIFrameWnd baseclass_0;
	/* this+ 96 */ public: ChatRoomInfo m_roomInfo;
	/* this+144 */ protected: UIResizer* m_resizer;
	/* this+148 */ protected: UIChatEditCtrl* m_chatEdit;
	/* this+152 */ protected: UIChatHisBox2* m_listBox;
	/* this+156 */ protected: UIChatHisBox2* m_memberListBox;
	/* this+160 */ protected: UIBitmapButton* m_sysButton;
	/* this+164 */ protected: UIStaticText* m_title;
	/* this+168 */ protected: mystd::map<mystd::string,unsigned long> m_memberList;
	/* this+184 */ protected: mystd::vector<StringId> m_menuItems;
	/* this+200 */ protected: ChatRoomWndInfo* m_info;

	public: UIChatRoomWnd::UIChatRoomWnd(void);
	public: virtual UIChatRoomWnd::~UIChatRoomWnd(void);
	//public: void UIChatRoomWnd::OnCreate(int, int);
	//public: void UIChatRoomWnd::OnDraw(void);
	//public: int UIChatRoomWnd::SendMsg(class UIWindow *, int, int, int, int);
	//public: void UIChatRoomWnd::StoreInfo(void);
	//public: void UIChatRoomWnd::Move(int, int);
	//public: int GetRoomId(void);
	public: void UIChatRoomWnd::WriteChatToFile(void);
	//public: void WriteChatToReportFile(void);

private:
	static hook_method<void (UIChatRoomWnd::*)(void)> UIChatRoomWnd::_WriteChatToFile;
};


class UIPetInfoWnd : public UIFrameWnd
{
	struct vtable_t
	{
		void* (UIFrameWnd::* scalar_deleting_destructor)(unsigned int flags);
//		UIWindow::Invalidate(void);
//		UIWindow::InvalidateWallPaper(void);
//		UIWindow::Resize(int,int);
//		UIFrameWnd::IsFrameWnd(void);
//		UIWindow::IsUpdateNeed(void);
//		UIFrameWnd::Move(int,int);
//		UIWindow::CanGetFocus(void);
//		UIWindow::GetTransBoxInfo(BOXINFO* boxInfo);
//		UIWindow::IsTransmitMouseInput(void);

//		UIWindow::ShouldDoHitTest(void);
		void (UIWindow::* DragAndDrop)(int x, int y, const DRAG_INFO* const dragInfo);
//		UIWindow::StoreInfo(void);
//		UIFrameWnd::SaveOriginalPos(void);
//		UIFrameWnd::MoveDelta(int,int);
//		UIWindow::GetColor(void);
//		UIWindow::SetShow(int);
//		UIWindow::OnCreate(int,int);
//		UIWindow::OnDestroy(void);
//		UIWindow::OnProcess(void);

//		UIWindow::OnDraw(void);
//		UIWindow::OnDraw2(void);
//		UIWindow::OnRun(void);
//		UIWindow::OnSize(int,int);
//		UIWindow::OnBeginEdit(void);
//		UIWindow::OnFinishEdit(void);
//		UIFrameWnd::OnLBtnDown(int,int);
//		UIWindow::OnLBtnDblClk(int,int);
//		UIFrameWnd::OnMouseMove(int,int);
//		UIFrameWnd::OnMouseHover(int,int);

//		UIWindow::OnMouseShape(int,int);
//		UIFrameWnd::OnLBtnUp(int,int);
//		UIWindow::OnRBtnDown(int,int);
//		UIWindow::OnRBtnUp(int,int);
//		UIWindow::OnRBtnDblClk(int,int);
//		UIWindow::OnWheel(int);
//		UIFrameWnd::RefreshSnap(void);
//		UIFrameWnd::SendMsg(UIWindow *,int,int,int,int);
	};

	/* this+  0 */ public: //UIFrameWnd baseclass_0;
	/* this+ 96 */ public: UIEditCtrl2* m_newName;
	/* this+100 */ public: PetInfoWndInfo* m_info;
	/* this+104 */ public: UIBitmapButton* m_button;
	/* this+108 */ public: UINoneVisibleButton* m_skinSelectButton;

	public: UIPetInfoWnd::UIPetInfoWnd(void);
	public: virtual UIPetInfoWnd::~UIPetInfoWnd(void);
	//public: void UIPetInfoWnd::OnCreate(int, int);
	//public: void UIPetInfoWnd::OnDraw(void);
	//public: void UIPetInfoWnd::StoreInfo(void);
	//public: int UIPetInfoWnd::SendMsg(UIWindow *, int, int, int, int);
};


class UICntWnd : public UIFrameWnd
{
	/* this+  0 */ public: //UIFrameWnd baseclass_0;
	/* this+ 96 */ int m_target;
	/* this+100 */ UIEditCtrl* m_editCtrl;
	/* this+104 */ UIStaticText* m_newText;

	public: UICntWnd::UICntWnd(void);
	public: virtual UICntWnd::~UICntWnd(void);
	public: virtual void UICntWnd::OnCreate(int cx, int cy);
	public: virtual void UICntWnd::OnDraw(void);
	public: virtual int UICntWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3);

private:
	static hook_method<void (UICntWnd::*)(int cx, int cy)> UICntWnd::_OnCreate;
	static hook_method<void (UICntWnd::*)(void)> UICntWnd::_OnDraw;
	static hook_method<int (UICntWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UICntWnd::_SendMsg;
};
