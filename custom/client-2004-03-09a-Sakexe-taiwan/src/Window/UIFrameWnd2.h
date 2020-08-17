#pragma once
#include "Struct.h"
#include "Window/UIControl.h"
#include "Window/UIFrameWnd.h"
class UIBarGraph4;
class UIBarGraphPlayerHp;
class UIBarGraphPlayerSp;
class UIBitmapButton;
class UICheckBox;
class UIEditCtrl;
class UIRadioBtn;
class UIStaticText;
class UITextViewer;
struct BasicInfoWndInfo;


class UIWaitWnd : public UIFrameWnd
{
	struct vtable_t
	{
//		UIWaitWnd::`scalar deleting destructor'(uint)
//		UIWindow::Invalidate(void)
//		UIWindow::InvalidateWallPaper(void)
//		UIWindow::Resize(int,int)
//		UIFrameWnd::IsFrameWnd(void)
		bool (UIWindow::* IsUpdateNeed)(void);
//		UIFrameWnd::Move(int,int)
//		UIWindow::CanGetFocus(void)
//		UIWindow::GetTransBoxInfo(BOXINFO* boxInfo)
//		UIWindow::IsTransmitMouseInput(void)

//		UIWindow::ShouldDoHitTest(void)
		void (UIWindow::* DragAndDrop)(int x, int y, const DRAG_INFO* const dragInfo);
		void (UIWindow::* StoreInfo)(void);
//		UIFrameWnd::SaveOriginalPos(void)
//		UIFrameWnd::MoveDelta(int,int)
//		UIWindow::GetColor(void)
//		UIWindow::SetShow(int visible)
//		UIWaitWnd::OnCreate(int cx, int cy)
//		UIWindow::OnDestroy(void)
//		UIWindow::OnProcess(void)

		void (UIWaitWnd::* OnDraw)(void);
//		UIWindow::OnDraw2(void)
//		UIWindow::OnRun(void)
//		UIWindow::OnSize(int,int)
//		UIWindow::OnBeginEdit(void)
//		UIWindow::OnFinishEdit(void)
//		UIFrameWnd::OnLBtnDown(int x, int y)
//		UIWindow::OnLBtnDblClk(int x, int y)
//		UIFrameWnd::OnMouseMove(int,int)
//		UIFrameWnd::OnMouseHover(int x, int y)

//		UIWindow::OnMouseShape(int,int)
//		UIFrameWnd::OnLBtnUp(int,int)
//		UIWindow::OnRBtnDown(int x, int y)
//		UIWindow::OnRBtnUp(int,int)
//		UIWindow::OnRBtnDblClk(int,int)
//		UIWindow::OnWheel(int)
//		UIFrameWnd::RefreshSnap(void)
//		UIWaitWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3)
	};

	/* this+ 0 */ public: //UIFrameWnd baseclass_0;
	/* this+96 */ protected: UITextViewer* m_textViewer;

	public: UIWaitWnd::UIWaitWnd(void);
	public: virtual UIWaitWnd::~UIWaitWnd(void);
	public: virtual void UIWaitWnd::OnCreate(int cx, int cy);
	public: virtual void UIWaitWnd::OnDraw(void);
	public: virtual int UIWaitWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3);
	public: void UIWaitWnd::SetMsg(const char* waitMsg, int fontHeight, int fontType);

private:
	static hook_method<void (UIWaitWnd::*)(int cx, int cy)> UIWaitWnd::_OnCreate;
	static hook_method<void (UIWaitWnd::*)(void)> UIWaitWnd::_OnDraw;
	static hook_method<int (UIWaitWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UIWaitWnd::_SendMsg;
	static hook_method<void (UIWaitWnd::*)(const char* waitMsg, int fontHeight, int fontType)> UIWaitWnd::_SetMsg;
};


class UILoadingWnd : public UIFrameWnd
{
	struct vtable_t
	{
		//TODO
	};

	/* this+  0 */ public: //UIFrameWnd baseclass_0;
	/* this+ 96 */ protected: UIStaticText* m_waitMsg;
	/* this+100 */ protected: UIBarGraph2* m_barGraph;

	public: UILoadingWnd::UILoadingWnd(void);
	public: virtual UILoadingWnd::~UILoadingWnd(void);
	public: virtual void UILoadingWnd::OnCreate(int cx, int cy);
	public: virtual void UILoadingWnd::OnDraw(void);
	public: virtual int UILoadingWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3);
	public: void UILoadingWnd::SetMsg(const char* waitMsg, int fontHeight, int fontType);

private:
	static hook_method<void (UILoadingWnd::*)(int cx, int cy)> UILoadingWnd::_OnCreate;
	static hook_method<void (UILoadingWnd::*)(void)> UILoadingWnd::_OnDraw;
	static hook_method<int (UILoadingWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UILoadingWnd::_SendMsg;
	static hook_method<void (UILoadingWnd::*)(const char* waitMsg, int fontHeight, int fontType)> UILoadingWnd::_SetMsg;
};


class UIBasicInfoWnd : public UIFrameWnd
{
	struct vtable_t
	{
//		UIBasicInfoWnd::`scalar deleting destructor'(uint)
//		UIWindow::Invalidate(void)
//		UIWindow::InvalidateWallPaper(void)
//		UIWindow::Resize(int,int)
//		UIFrameWnd::IsFrameWnd(void)
		bool (UIBasicInfoWnd::* IsUpdateNeed)(void);
//		UIFrameWnd::Move(int,int)
//		UIWindow::CanGetFocus(void)
//		UIWindow::GetTransBoxInfo(BOXINFO* boxInfo)
//		UIWindow::IsTransmitMouseInput(void)
//		UIWindow::ShouldDoHitTest(void)
		void (UIWindow::* DragAndDrop)(int x, int y, const DRAG_INFO* const dragInfo);
		void (UIBasicInfoWnd::* StoreInfo)(void);
//		UIFrameWnd::SaveOriginalPos(void)
//		UIFrameWnd::MoveDelta(int,int)
//		UIWindow::GetColor(void)
//		UIWindow::SetShow(int visible)
//		UIBasicInfoWnd::OnCreate(int cx, int cy)
//		UIWindow::OnDestroy(void)
//		UIWindow::OnProcess(void)
		void (UIBasicInfoWnd::* OnDraw)(void);
//		UIWindow::OnDraw2(void)
//		UIWindow::OnRun(void)
//		UIWindow::OnSize(int,int)
//		UIWindow::OnBeginEdit(void)
//		UIWindow::OnFinishEdit(void)
//		UIFrameWnd::OnLBtnDown(int x, int y)
//		UIBasicInfoWnd::OnLBtnDblClk(int x, int y)
//		UIFrameWnd::OnMouseMove(int,int)
//		UIBasicInfoWnd::OnMouseHover(int x, int y)
//		UIWindow::OnMouseShape(int,int)
//		UIFrameWnd::OnLBtnUp(int,int)
//		UIWindow::OnRBtnDown(int x, int y)
//		UIWindow::OnRBtnUp(int,int)
//		UIWindow::OnRBtnDblClk(int,int)
//		UIWindow::OnWheel(int)
//		UIFrameWnd::RefreshSnap(void)
//		UIBasicInfoWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3)
	};

	/* this+  0 */ public: //UIFrameWnd baseclass_0;
	/* this+ 96 */ protected: BasicInfoWndInfo* m_info;
	/* this+100 */ protected: UIBitmapButton* m_buttons[8];
	/* this+132 */ protected: UIBarGraphPlayerHp* m_hpGraph;
	/* this+136 */ protected: UIBarGraphPlayerSp* m_spGraph;
	/* this+140 */ protected: UIBarGraph4* m_expGraph;
	/* this+144 */ protected: UIBarGraph4* m_jobexpGraph;
	/* this+148 */ protected: UIStaticText* m_name;

	enum HEIGHT_TYPE
	{
		MINI_SIZE = 34,
		FULL_SIZE = 120,
	};

	public: UIBasicInfoWnd::UIBasicInfoWnd(void);
	public: virtual UIBasicInfoWnd::~UIBasicInfoWnd(void);
	public: virtual bool UIBasicInfoWnd::IsUpdateNeed(void);
	public: virtual void UIBasicInfoWnd::OnCreate(int cx, int cy);
	public: virtual void UIBasicInfoWnd::OnDraw(void);
	public: virtual void UIBasicInfoWnd::OnLBtnDblClk(int x, int y);
	public: virtual void UIBasicInfoWnd::OnMouseHover(int x, int y);
	public: virtual int UIBasicInfoWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3);
	public: void UIBasicInfoWnd::StoreInfo(void);
	public: void UIBasicInfoWnd::NewHeight(int newHeight);

private:
	static hook_method<bool (UIBasicInfoWnd::*)(void)> UIBasicInfoWnd::_IsUpdateNeed;
	static hook_method<void (UIBasicInfoWnd::*)(int cx, int cy)> UIBasicInfoWnd::_OnCreate;
	static hook_method<void (UIBasicInfoWnd::*)(void)> UIBasicInfoWnd::_OnDraw;
	static hook_method<void (UIBasicInfoWnd::*)(int x, int y)> UIBasicInfoWnd::_OnLBtnDblClk;
	static hook_method<void (UIBasicInfoWnd::*)(int x, int y)> UIBasicInfoWnd::_OnMouseHover;
	static hook_method<int (UIBasicInfoWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UIBasicInfoWnd::_SendMsg;
	static hook_method<void (UIBasicInfoWnd::*)(void)> UIBasicInfoWnd::_StoreInfo;
	static hook_method<void (UIBasicInfoWnd::*)(int newHeight)> UIBasicInfoWnd::_NewHeight;
};


class UIToolTipWnd : public UIFrameWnd
{
	struct vtable_t
	{
		//TODO
	};

	/* this+ 0 */ public: //UIFrameWnd baseclass_0;
	/* this+96 */ protected: UIListBox* m_toolTipList;

	public: UIToolTipWnd::UIToolTipWnd(void);
	public: virtual UIToolTipWnd::~UIToolTipWnd(void);
	public: void UIToolTipWnd::OnCreate(int cx, int cy);
	public: void UIToolTipWnd::OnDraw(void);
	public: int UIToolTipWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3);

private:
	static hook_method<void (UIToolTipWnd::*)(int cx, int cy)> UIToolTipWnd::_OnCreate;
	static hook_method<void (UIToolTipWnd::*)(void)> UIToolTipWnd::_OnDraw;
	static hook_method<int (UIToolTipWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UIToolTipWnd::_SendMsg;
};


class UIShortCutWnd : public UIFrameWnd
{
	struct vtable_t
	{
		void* (UIShortCutWnd::* scalar_deleting_destructor)(unsigned int flags);
		void (UIWindow::* Invalidate)(void);
		void (UIWindow::* InvalidateWallPaper)(void);
		void (UIWindow::* Resize)(int cx, int cy);
		bool (UIFrameWnd::* IsFrameWnd)(void);
		bool (UIShortCutWnd::* IsUpdateNeed)(void);
		void (UIFrameWnd::* Move)(int x, int y);
		bool (UIWindow::* CanGetFocus)(void);
		bool (UIWindow::* GetTransBoxInfo)(BOXINFO* boxInfo);
		bool (UIWindow::* IsTransmitMouseInput)(void);

		bool (UIWindow::* ShouldDoHitTest)(void);
		void (UIShortCutWnd::* DragAndDrop)(int x, int y, const DRAG_INFO* const dragInfo);
		void (UIShortCutWnd::* StoreInfo)(void);
		void (UIFrameWnd::* SaveOriginalPos)(void);
		void (UIFrameWnd::* MoveDelta)(int deltaDragX, int deltaDragY);
		unsigned long (UIWindow::* GetColor)(void);
		void (UIShortCutWnd::* SetShow)(int visible);
		void (UIShortCutWnd::* OnCreate)(int cx, int cy);
		void (UIWindow::* OnDestroy)(void);
		void (UIShortCutWnd::* OnProcess)(void);

		void (UIShortCutWnd::* OnDraw)(void);
		void (UIWindow::* OnDraw2)(void);
		void (UIWindow::* OnRun)(void);
		void (UIWindow::* OnSize)(int cx, int cy);
		void (UIWindow::* OnBeginEdit)(void);
		void (UIWindow::* OnFinishEdit)(void);
		void (UIShortCutWnd::* OnLBtnDown)(int x, int y);
		void (UIShortCutWnd::* OnLBtnDblClk)(int x, int y);
		void (UIFrameWnd::* OnMouseMove)(int x, int y);
		void (UIShortCutWnd::* OnMouseHover)(int x, int y);

		void (UIWindow::* OnMouseShape)(int x, int y);
		void (UIFrameWnd::* OnLBtnUp)(int x, int y);
		void (UIShortCutWnd::* OnRBtnDown)(int x, int y);
		void (UIWindow::* OnRBtnUp)(int x, int y);
		void (UIWindow::* OnRBtnDblClk)(int x, int y);
		void (UIWindow::* OnWheel)(int wheel);
		void (UIFrameWnd::* RefreshSnap)(void);
		int (UIShortCutWnd::* SendMsg)(UIWindow* sender, int message, int val1, int val2, int val3);
	};

	/* this+  0 */ public: //UIFrameWnd baseclass_0;
	/* this+ 96 */ protected: ShortCutWndInfo* m_info;
	/* this+100 */ protected: int m_itemIndexOrSkillId[27];
	/* this+208 */ protected: int m_isSkill[27];
	/* this+316 */ protected: int m_skillUseLevel[27];
	/* this+424 */ protected: int m_slot;

	public: UIShortCutWnd::UIShortCutWnd(void);
	public: virtual UIShortCutWnd::~UIShortCutWnd(void);
	public: virtual bool UIShortCutWnd::IsUpdateNeed(void);
	public: virtual void UIShortCutWnd::OnCreate(int cx, int cy);
	public: virtual void UIShortCutWnd::OnDraw(void);
	public: virtual void UIShortCutWnd::OnProcess(void);
	public: virtual void UIShortCutWnd::OnLBtnDown(int x, int y);
	public: virtual void UIShortCutWnd::OnRBtnDown(int x, int y);
	public: virtual void UIShortCutWnd::OnLBtnDblClk(int x, int y);
	public: virtual void UIShortCutWnd::OnMouseHover(int x, int y);
	public: virtual int UIShortCutWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3);
	public: virtual void UIShortCutWnd::DragAndDrop(int x, int y, const DRAG_INFO* const dragInfo);
	public: virtual void UIShortCutWnd::StoreInfo(void);
	public: virtual void UIShortCutWnd::SetShow(int visible);
	public: int UIShortCutWnd::GetSlot(int x, int y);

private:
	static hook_method<bool (UIShortCutWnd::*)(void)> UIShortCutWnd::_IsUpdateNeed;
	static hook_method<void (UIShortCutWnd::*)(int cx, int cy)> UIShortCutWnd::_OnCreate;
	static hook_method<void (UIShortCutWnd::*)(void)> UIShortCutWnd::_OnDraw;
	static hook_method<void (UIShortCutWnd::*)(void)> UIShortCutWnd::_OnProcess;
	static hook_method<void (UIShortCutWnd::*)(int x, int y)> UIShortCutWnd::_OnLBtnDown;
	static hook_method<void (UIShortCutWnd::*)(int x, int y)> UIShortCutWnd::_OnRBtnDown;
	static hook_method<void (UIShortCutWnd::*)(int x, int y)> UIShortCutWnd::_OnLBtnDblClk;
	static hook_method<void (UIShortCutWnd::*)(int x, int y)> UIShortCutWnd::_OnMouseHover;
	static hook_method<int (UIShortCutWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UIShortCutWnd::_SendMsg;
	static hook_method<void (UIShortCutWnd::*)(int x, int y, const DRAG_INFO* const dragInfo)> UIShortCutWnd::_DragAndDrop;
	static hook_method<void (UIShortCutWnd::*)(void)> UIShortCutWnd::_StoreInfo;
	static hook_method<void (UIShortCutWnd::*)(int visible)> UIShortCutWnd::_SetShow;
	static hook_method<int (UIShortCutWnd::*)(int x, int y)> UIShortCutWnd::_GetSlot;
};


class UIStatusWnd : public UIFrameWnd
{
	struct vtable_t
	{
		//TODO
	};

	/* this+  0 */ public: //UIFrameWnd baseclass_0;
	/* this+ 96 */ protected: UIBitmapButton* m_incArrowButton[6];
	/* this+120 */ protected: int m_orgHeight;
	/* this+124 */ protected: StatusWndInfo* m_info;

	public: UIStatusWnd::UIStatusWnd(void);
	public: virtual UIStatusWnd::~UIStatusWnd(void);
	public: virtual bool UIStatusWnd::IsUpdateNeed(void);
	public: virtual void UIStatusWnd::OnCreate(int cx, int cy);
	public: virtual void UIStatusWnd::OnDraw(void);
	public: virtual void UIStatusWnd::OnLBtnDblClk(int x, int y);
	public: virtual void UIStatusWnd::OnLBtnDown(int x, int y);
	public: virtual void UIStatusWnd::OnMouseHover(int x, int y);
	public: virtual int UIStatusWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3);
	public: virtual void UIStatusWnd::StoreInfo(void);
	public: void UIStatusWnd::ChangeState(int state);

private:
	static hook_method<bool (UIStatusWnd::*)(void)> UIStatusWnd::_IsUpdateNeed;
	static hook_method<void (UIStatusWnd::*)(int cx, int cy)> UIStatusWnd::_OnCreate;
	static hook_method<void (UIStatusWnd::*)(void)> UIStatusWnd::_OnDraw;
	static hook_method<void (UIStatusWnd::*)(int x, int y)> UIStatusWnd::_OnLBtnDblClk;
	static hook_method<void (UIStatusWnd::*)(int x, int y)> UIStatusWnd::_OnLBtnDown;
	static hook_method<void (UIStatusWnd::*)(int x, int y)> UIStatusWnd::_OnMouseHover;
	static hook_method<int (UIStatusWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UIStatusWnd::_SendMsg;
	static hook_method<void (UIStatusWnd::*)(void)> UIStatusWnd::_StoreInfo;
	static hook_method<void (UIStatusWnd::*)(int state)> UIStatusWnd::_ChangeState;
};


class UIOptionWnd : public UIFrameWnd
{
	struct vtable_t
	{
		//TODO
	};

	/* this+  0 */ public: //UIFrameWnd baseclass_0;
	/* this+ 96 */ protected: int m_orgHeight;
	/* this+100 */ protected: OptionWndInfo* m_info;
	/* this+104 */ protected: UIScrollBar* m_bgmVolumescrBar;
	/* this+108 */ protected: UIScrollBar* m_soundVolumescrBar;
	/* this+112 */ protected: int m_soundVolume;
	/* this+116 */ protected: int m_bgmVolume;
	/* this+120 */ protected: UICheckBox* m_soundOncheckBox;
	/* this+124 */ protected: UICheckBox* m_bgmOncheckBox;
	/* this+128 */ protected: UICheckBox* m_attackSnapCheckBox;
	/* this+132 */ protected: UICheckBox* m_skillSnapCheckBox;
	/* this+136 */ protected: UICheckBox* m_itemSnapCheckBox;
	/* this+140 */ protected: UICheckBox* m_opaqueCheckBox;
	/* this+144 */ protected: UINoneVisibleButton* m_skinSelectButton;

	public: UIOptionWnd::UIOptionWnd(void);
	public: virtual UIOptionWnd::~UIOptionWnd(void);
	public: virtual void UIOptionWnd::OnCreate(int cx, int cy);
	public: virtual void UIOptionWnd::OnDraw(void);
	public: virtual void UIOptionWnd::OnLBtnDblClk(int x, int y);
	public: virtual void UIOptionWnd::OnLBtnDown(int x, int y);
	public: virtual int UIOptionWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3);
	public: virtual void UIOptionWnd::StoreInfo(void);

private:
	static hook_method<void (UIOptionWnd::*)(int cx, int cy)> UIOptionWnd::_OnCreate;
	static hook_method<void (UIOptionWnd::*)(void)> UIOptionWnd::_OnDraw;
	static hook_method<void (UIOptionWnd::*)(int x, int y)> UIOptionWnd::_OnLBtnDblClk;
	static hook_method<void (UIOptionWnd::*)(int x, int y)> UIOptionWnd::_OnLBtnDown;
	static hook_method<int (UIOptionWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UIOptionWnd::_SendMsg;
	static hook_method<void (UIOptionWnd::*)(void)> UIOptionWnd::_StoreInfo;
};


class UINotifyItemObtainWnd : public UIFrameWnd
{
	struct vtable_t
	{
		//TODO
	};

	/* this+  0 */ public: //UIFrameWnd baseclass_0;
	/* this+ 96 */ protected: mystd::string m_itemName;
	/* this+112 */ protected: mystd::string m_message;
	/* this+128 */ protected: DWORD m_madeTick;
	/* this+132 */ protected: int m_isMoney;
	/* this+136 */ protected: ITEM_INFO m_itemInfo;
	/* this+204 */ protected: bool m_isIdentified;

	public: UINotifyItemObtainWnd::UINotifyItemObtainWnd(void);
	public: UINotifyItemObtainWnd::~UINotifyItemObtainWnd(void);
	public: virtual void UINotifyItemObtainWnd::OnCreate(int cx, int cy);
	public: virtual void UINotifyItemObtainWnd::OnDraw(void);
	public: virtual int UINotifyItemObtainWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3);
	public: virtual void UINotifyItemObtainWnd::OnProcess(void);
	public: virtual bool UINotifyItemObtainWnd::ShouldDoHitTest(void);

private:
	static hook_method<void (UINotifyItemObtainWnd::*)(int cx, int cy)> UINotifyItemObtainWnd::_OnCreate;
	static hook_method<void (UINotifyItemObtainWnd::*)(void)> UINotifyItemObtainWnd::_OnDraw;
	static hook_method<int (UINotifyItemObtainWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UINotifyItemObtainWnd::_SendMsg;
	static hook_method<void (UINotifyItemObtainWnd::*)(void)> UINotifyItemObtainWnd::_OnProcess;
	static hook_method<bool (UINotifyItemObtainWnd::*)(void)> UINotifyItemObtainWnd::_ShouldDoHitTest;
};


class UISayDialogWnd : public UIFrameWnd
{
	struct vtable_t
	{
//		UISayDialogWnd::`scalar deleting destructor'(uint)
//		UIWindow::Invalidate(void)
//		UIWindow::InvalidateWallPaper(void)
//		UISayDialogWnd::Resize(int,int)
//		UIFrameWnd::IsFrameWnd(void)
//		UIWindow::IsUpdateNeed(void)
//		UIFrameWnd::Move(int,int)
//		UIWindow::CanGetFocus(void)
//		UIWindow::GetTransBoxInfo(BOXINFO* boxInfo)
//		UIWindow::IsTransmitMouseInput(void)
//		UIWindow::ShouldDoHitTest(void)
		void (UIWindow::* DragAndDrop)(int x, int y, const DRAG_INFO* const dragInfo);
//		UISayDialogWnd::StoreInfo(void)
//		UIFrameWnd::SaveOriginalPos(void)
//		UIFrameWnd::MoveDelta(int,int)
//		UIWindow::GetColor(void)
//		UIWindow::SetShow(int visible)
//		UISayDialogWnd::OnCreate(int cx, int cy)
//		UIWindow::OnDestroy(void)
//		UIWindow::OnProcess(void)
//		UISayDialogWnd::OnDraw(void)
//		UIWindow::OnDraw2(void)
//		UIWindow::OnRun(void)
//		UIWindow::OnSize(int,int)
//		UIWindow::OnBeginEdit(void)
//		UIWindow::OnFinishEdit(void)
//		UIFrameWnd::OnLBtnDown(int x, int y)
//		UIWindow::OnLBtnDblClk(int x, int y)
//		UIFrameWnd::OnMouseMove(int,int)
//		UIFrameWnd::OnMouseHover(int x, int y)
//		UIWindow::OnMouseShape(int,int)
//		UIFrameWnd::OnLBtnUp(int,int)
//		UIWindow::OnRBtnDown(int x, int y)
//		UIWindow::OnRBtnUp(int,int)
//		UIWindow::OnRBtnDblClk(int,int)
//		UIWindow::OnWheel(int)
//		UIFrameWnd::RefreshSnap(void)
//		UISayDialogWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3)
	};

	/* this+  0 */ public: //UIFrameWnd baseclass_0;
	/* this+ 96 */ protected: UITextViewer* m_textViewer;
	/* this+100 */ protected: mystd::list<UIBitmapButton*> m_buttonList;
	/* this+112 */ protected: mystd::list<UIBitmapButton*> m_buttonListDeleted;
	/* this+124 */ protected: int m_target;
	/* this+128 */ protected: unsigned long m_naid;
	/* this+132 */ protected: SayDialogWndInfo* m_info;
	/* this+136 */ protected: int m_bClearTextViewer;

	public: UISayDialogWnd::UISayDialogWnd(void);
	public: virtual UISayDialogWnd::~UISayDialogWnd(void);
	public: virtual void UISayDialogWnd::OnCreate(int cx, int cy);
	public: virtual void UISayDialogWnd::OnDraw(void);
	public: virtual int UISayDialogWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3);
	public: virtual void UISayDialogWnd::StoreInfo(void);
	public: virtual void UISayDialogWnd::Resize(int cx, int cy);
	protected: int UISayDialogWnd::GetButtonOffset(int buttonSize);

private:
	static hook_method<void (UISayDialogWnd::*)(int cx, int cy)> UISayDialogWnd::_OnCreate;
	static hook_method<void (UISayDialogWnd::*)(void)> UISayDialogWnd::_OnDraw;
	static hook_method<int (UISayDialogWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UISayDialogWnd::_SendMsg;
	static hook_method<void (UISayDialogWnd::*)(void)> UISayDialogWnd::_StoreInfo;
	static hook_method<void (UISayDialogWnd::*)(int cx, int cy)> UISayDialogWnd::_Resize;
	static hook_method<int (UISayDialogWnd::*)(int buttonSize)> UISayDialogWnd::_GetButtonOffset;
};


class UIItemCollectionWnd : public UIFrameWnd
{
public:
	UIItemCollectionWnd();
	virtual ~UIItemCollectionWnd();
	virtual void UIItemCollectionWnd::OnCreate(int cx, int cy);
	virtual void UIItemCollectionWnd::OnDraw();
	virtual void UIItemCollectionWnd::OnMouseHover(int x, int y);
	virtual void UIItemCollectionWnd::OnRBtnDown(int x, int y);
	virtual int UIItemCollectionWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3);
	virtual void UIItemCollectionWnd::StoreInfo(void);
	int UIItemCollectionWnd::GetCardSlotNum(int x, int y, int& gx, int& gy);
protected:
	bool UIItemCollectionWnd::IsSameCollectionDisplayParameters(const ITEM_INFO& item_info);

protected:
	/* this+  0 */ //UIFrameWnd baseclass_0;
	/* this+ 96 */ ITEM_INFO m_itemInfo;
	/* this+164 */ UITextViewer* m_textViewer;
	/* this+168 */ UIBitmapButton* m_cardItemButton;
	/* this+172 */ mystd::string m_itemBmp;
	/* this+188 */ mystd::string m_itemName;
	/* this+204 */ bool m_isIdentified;
	/* this+205 */ bool m_hasSlot;
	/* this+208 */ enum WINDOWID m_windowId;
private:
	/* this+212 */ ItemCollectionWndInfo* m_info;
public:
	/* this+216 */ short m_petLevel;
	/* this+218 */ short m_petFullness;
	/* this+220 */ short m_petRelationship;
	/* this+222 */ char m_petName[24];
	/* this+246 */ unsigned short m_petITID;
	/* this+248 */ int m_isPetNameModified;

private:
	static hook_method<void (UIItemCollectionWnd::*)(int x, int y)> UIItemCollectionWnd::_OnMouseHover;
	static hook_method<void (UIItemCollectionWnd::*)(int x, int y)> UIItemCollectionWnd::_OnRBtnDown;
	static hook_method<int (UIItemCollectionWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UIItemCollectionWnd::_SendMsg;
	static hook_method<void (UIItemCollectionWnd::*)(void)> UIItemCollectionWnd::_StoreInfo;
	static hook_method<int (UIItemCollectionWnd::*)(int x, int y, int& gx, int& gy)> UIItemCollectionWnd::_GetCardSlotNum;
	static hook_method<bool (UIItemCollectionWnd::*)(const ITEM_INFO& item_info)> UIItemCollectionWnd::_IsSameCollectionDisplayParameters;
};


class UIChooseWarpWnd : public UIFrameWnd
{
	struct vtable_t
	{
		void* (UIChooseWarpWnd::* scalar_deleting_destructor)(unsigned int flags);
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
		void (UIChooseWarpWnd::* OnCreate)(int cx, int cy);
		void (UIWindow::* OnDestroy)(void);
		void (UIWindow::* OnProcess)(void);

		void (UIChooseWarpWnd::* OnDraw)(void);
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
		int (UIChooseWarpWnd::* SendMsg)(UIWindow* sender, int message, int val1, int val2, int val3);
	};

	/* this+  0 */ public: //UIFrameWnd baseclass_0;
	/* this+ 96 */ protected: UIListBox* m_choostList;
	/* this+100 */ protected: unsigned long m_skid;
	/* this+104 */ protected: mystd::vector<mystd::string> m_mapNameList;

	public: UIChooseWarpWnd::UIChooseWarpWnd(void);
	public: virtual UIChooseWarpWnd::~UIChooseWarpWnd(void);
	public: virtual void UIChooseWarpWnd::OnCreate(int cx, int cy);
	public: virtual void UIChooseWarpWnd::OnDraw(void);
	public: virtual int UIChooseWarpWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3);

private:
	static hook_method<void (UIChooseWarpWnd::*)(int cx, int cy)> UIChooseWarpWnd::_OnCreate;
	static hook_method<void (UIChooseWarpWnd::*)(void)> UIChooseWarpWnd::_OnDraw;
	static hook_method<int (UIChooseWarpWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UIChooseWarpWnd::_SendMsg;
};


class UIQuitWnd : public UIFrameWnd
{
	struct vtable_t
	{
		//TODO
	};

	/* this+0 */ public: //UIFrameWnd baseclass_0;

	public: UIQuitWnd::UIQuitWnd(void);
	public: virtual UIQuitWnd::~UIQuitWnd(void);
	public: virtual void UIQuitWnd::OnCreate(int cx, int cy);
	public: virtual void UIQuitWnd::OnDraw(void);
	public: virtual int UIQuitWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3);

private:
	static hook_method<void (UIQuitWnd::*)(int cx, int cy)> UIQuitWnd::_OnCreate;
	static hook_method<void (UIQuitWnd::*)(void)> UIQuitWnd::_OnDraw;
	static hook_method<int (UIQuitWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UIQuitWnd::_SendMsg;
};


class UIExchangeWnd : public UIFrameWnd
{
	struct vtable_t
	{
		//TODO
	};

	/* this+  0 */ public: //UIFrameWnd baseclass_0;
	/* this+ 96 */ protected: UIBitmapButton* m_buttons[3];
	/* this+108 */ protected: UIEditCtrl* m_editCtrl;
	/* this+112 */ protected: int m_IsMyDragClosed;
	/* this+116 */ protected: int m_IsOtherDragClosed;
	/* this+120 */ protected: int m_okPushed;
	/* this+124 */ protected: int m_exchangePushed;
	/* this+128 */ protected: int m_cancelPushed;
	/* this+132 */ protected: mystd::list<ITEM_INFO> m_myItemList;
	/* this+144 */ protected: mystd::list<ITEM_INFO> m_otherItemList;
	/* this+156 */ protected: mystd::string m_exchangeCharacterName;
	/* this+172 */ protected: int m_exchangeCharacterID;
	/* this+176 */ protected: short m_exchangeCharacterLV;

	public: UIExchangeWnd::UIExchangeWnd(void);
	//public: UIExchangeWnd::~UIExchangeWnd(void);
	//public: void UIExchangeWnd::OnCreate(int cx, int cy);
	//public: void UIExchangeWnd::OnDraw();
	//public: int UIExchangeWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3);
	//public: void UIExchangeWnd::OnMouseHover(int x, int y);
	//public: void UIExchangeWnd::OnRBtnDown(int x, int y);
	//public: void UIExchangeWnd::DragAndDrop(int x, int y, const DRAG_INFO* const dragInfo);
	//public: struct ITEM_INFO UIExchangeWnd::GetItemInfo(int, int);
	//public: void UIExchangeWnd::InvalidateButton();
	//public: void UIExchangeWnd::RemoveMoneyCtrls();
};


class UIMinimapZoomWnd : public UIFrameWnd
{
	/* this+0 */ public: //UIFrameWnd baseclass_0;

	public: UIMinimapZoomWnd::UIMinimapZoomWnd(void);
	public: virtual UIMinimapZoomWnd::~UIMinimapZoomWnd(void);
	public: virtual void UIMinimapZoomWnd::OnCreate(int cx, int cy);
	public: virtual void UIMinimapZoomWnd::OnDraw(void);
	public: virtual int UIMinimapZoomWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3);

private:
	static hook_method<void (UIMinimapZoomWnd::*)(int cx, int cy)> UIMinimapZoomWnd::_OnCreate;
	static hook_method<void (UIMinimapZoomWnd::*)(void)> UIMinimapZoomWnd::_OnDraw;
	static hook_method<int (UIMinimapZoomWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UIMinimapZoomWnd::_SendMsg;
};


class UIPartySettingWnd : public UIFrameWnd
{
	/* this+  0 */ public: //UIFrameWnd baseclass_0;
	/* this+ 96 */ protected: UIRadioBtn* m_radioExpDiv[2];
	/* this+104 */ protected: int m_curExpDivBtn;
	/* this+108 */ protected: UIRadioBtn* m_radioItemCollect[2];
	/* this+116 */ protected: int m_curItemCollectBtn;
	/* this+120 */ protected: UIRadioBtn* m_radioItemDiv[2];
	/* this+128 */ protected: int m_curItemDivBtn;
	/* this+132 */ protected: PartySettingWndInfo* m_info;
	/* this+136 */ private: int m_nYOffset;
	/* static   */ private: static hook_val< const bool > s_bUseNewPacket;

	public: UIPartySettingWnd::UIPartySettingWnd(void);
	public: virtual UIPartySettingWnd::~UIPartySettingWnd(void);
	public: virtual void UIPartySettingWnd::OnCreate(int cx, int cy);
	public: virtual void UIPartySettingWnd::OnDraw(void);
	public: virtual void UIPartySettingWnd::OnLBtnDown(int x, int y);
	public: virtual int UIPartySettingWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3);
	public: virtual void UIPartySettingWnd::StoreInfo(void);

private:
	static hook_method<void (UIPartySettingWnd::*)(int cx, int cy)> UIPartySettingWnd::_OnCreate;
	static hook_method<void (UIPartySettingWnd::*)(void)> UIPartySettingWnd::_OnDraw;
	static hook_method<void (UIPartySettingWnd::*)(int x, int y)> UIPartySettingWnd::_OnLBtnDown;
	static hook_method<int (UIPartySettingWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UIPartySettingWnd::_SendMsg;
	static hook_method<void (UIPartySettingWnd::*)(void)> UIPartySettingWnd::_StoreInfo;
};


class UIMenuWnd : public UIFrameWnd
{
	/* this+  0 */ public: //UIFrameWnd baseclass_0;
	/* this+ 96 */ protected: enum WINDOWID m_callerWid;
	/* this+100 */ protected: int m_curMenuIndex;
	/* this+104 */ protected: int m_menuItemSpacing;
	/* this+108 */ protected: mystd::vector<mystd::string> m_menuItems;

	public: UIMenuWnd::UIMenuWnd(void);
	public: virtual UIMenuWnd::~UIMenuWnd(void);
	public: virtual void UIMenuWnd::OnCreate(int cx, int cy);
	public: virtual void UIMenuWnd::OnLBtnUp(int x, int y);
	public: virtual void UIMenuWnd::OnDraw(void);
	public: virtual void UIMenuWnd::OnMouseMove(int x, int y);
	public: virtual void UIMenuWnd::OnMouseHover(int x, int y);
	public: virtual int UIMenuWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3);
	public: virtual void UIMenuWnd::Move(int x, int y);
	public: void UIMenuWnd::AddMenu(const char* menuString);
	public: int UIMenuWnd::GetMenuIndex(int x, int y);
	public: int UIMenuWnd::GetNumBoundary(int seq);
	public: int UIMenuWnd::IsBoundary(int curItem);

private:
	static hook_method<void (UIMenuWnd::*)(int cx, int cy)> UIMenuWnd::_OnCreate;
	static hook_method<void (UIMenuWnd::*)(int x, int y)> UIMenuWnd::_OnLBtnUp;
	static hook_method<void (UIMenuWnd::*)(void)> UIMenuWnd::_OnDraw;
	static hook_method<void (UIMenuWnd::*)(int x, int y)> UIMenuWnd::_OnMouseMove;
	static hook_method<void (UIMenuWnd::*)(int x, int y)> UIMenuWnd::_OnMouseHover;
	static hook_method<int (UIMenuWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UIMenuWnd::_SendMsg;
	static hook_method<void (UIMenuWnd::*)(int x, int y)> UIMenuWnd::_Move;
	static hook_method<void (UIMenuWnd::*)(const char* menuString)> UIMenuWnd::_AddMenu;
	static hook_method<int (UIMenuWnd::*)(int x, int y)> UIMenuWnd::_GetMenuIndex;
	static hook_method<int (UIMenuWnd::*)(int seq)> UIMenuWnd::_GetNumBoundary;
	static hook_method<int (UIMenuWnd::*)(int curItem)> UIMenuWnd::_IsBoundary;
};


class UIProhibitListWnd : public UIFrameWnd
{
	struct vtable_t
	{
		//TODO
	};

	/* this+  0 */ public: //UIFrameWnd baseclass_0;
	/* this+ 96 */ protected: int m_oldLogCnt;
	/* this+100 */ protected: unsigned long m_AID;

	public: UIProhibitListWnd::UIProhibitListWnd(void);
	public: virtual UIProhibitListWnd::~UIProhibitListWnd(void);
	public: virtual void UIProhibitListWnd::OnCreate(int cx, int cy);
	public: virtual void UIProhibitListWnd::OnDraw(void);
	public: virtual void UIProhibitListWnd::OnProcess(void);
	public: virtual int UIProhibitListWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3);

private:
	static hook_method<void (UIProhibitListWnd::*)(int cx, int cy)> UIProhibitListWnd::_OnCreate;
	static hook_method<void (UIProhibitListWnd::*)(void)> UIProhibitListWnd::_OnDraw;
	static hook_method<void (UIProhibitListWnd::*)(void)> UIProhibitListWnd::_OnProcess;
	static hook_method<int (UIProhibitListWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UIProhibitListWnd::_SendMsg;
};
