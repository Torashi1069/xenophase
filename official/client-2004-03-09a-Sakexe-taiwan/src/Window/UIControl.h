#pragma once
#include "Window/UIWindow.h"
#include "Window/UISys.h"


class UIStaticText : public UIWindow
{
	struct vtable_t // const UIStaticText::`vftable'
	{
		void* (UIStaticText::* scalar_deleting_destructor)(unsigned int flags);
		void (UIWindow::* Invalidate)(void);
		void (UIWindow::* InvalidateWallPaper)(void);
		void (UIWindow::* Resize)(int cx, int cy);
		bool (UIWindow::* IsFrameWnd)(void);
		bool (UIWindow::* IsUpdateNeed)(void);
		void (UIWindow::* Move)(int x, int y);
		bool (UIWindow::* CanGetFocus)(void);
		bool (UIWindow::* GetTransBoxInfo)(BOXINFO* boxInfo);
		bool (UIWindow::* IsTransmitMouseInput)(void);

		bool (UIWindow::* ShouldDoHitTest)(void);
		void (UIWindow::* DragAndDrop)(int x, int y, const DRAG_INFO* const dragInfo);
		void (UIWindow::* StoreInfo)(void);
		void (UIWindow::* SaveOriginalPos)(void);
		void (UIWindow::* MoveDelta)(int deltaDragX, int deltaDragY);
		unsigned long (UIWindow::* GetColor)(void);
		void (UIWindow::* SetShow)(int visible);
		void (UIWindow::* OnCreate)(int cx, int cy);
		void (UIWindow::* OnDestroy)(void);
		void (UIWindow::* OnProcess)(void);

		void (UIStaticText::* OnDraw)(void);
		void (UIWindow::* OnDraw2)(void);
		void (UIWindow::* OnRun)(void);
		void (UIWindow::* OnSize)(int cx, int cy);
		void (UIWindow::* OnBeginEdit)(void);
		void (UIWindow::* OnFinishEdit)(void);
		void (UIStaticText::* OnLBtnDown)(int x, int y);
		void (UIStaticText::* OnLBtnDblClk)(int x, int y);
		void (UIStaticText::* OnMouseMove)(int x, int y);
		void (UIStaticText::* OnMouseHover)(int x, int y);

		void (UIStaticText::* OnMouseShape)(int x, int y);
		void (UIStaticText::* OnLBtnUp)(int x, int y);
		void (UIStaticText::* OnRBtnDown)(int x, int y);
		void (UIStaticText::* OnRBtnUp)(int x, int y);
		void (UIWindow::* OnRBtnDblClk)(int x, int y);
		void (UIStaticText::* OnWheel)(int wheel);
		void (UIWindow::* RefreshSnap)(void);
		int (UIWindow::* SendMsg)(UIWindow* sender, int message, int val1, int val2, int val3);
	};

	/* this+  0 */ public: //UIWindow baseclass_0;
	/* this+ 72 */ public: int m_drawBackGround;
	/* this+ 76 */ public: int m_backR;
	/* this+ 80 */ public: int m_backG;
	/* this+ 84 */ public: int m_backB;
	/* this+ 88 */ public: int m_drawTwice;
	/* this+ 92 */ public: int m_drawBold;
	/* this+ 96 */ protected: int m_fontHeight;
	/* this+100 */ protected: int m_fontType;
	/* this+104 */ protected: int m_isShorten;
	/* this+108 */ protected: mystd::string m_text;
	/* this+124 */ protected: mystd::string m_fullText;

	public: UIStaticText::UIStaticText(void);
	public: virtual UIStaticText::~UIStaticText(void);
	public: virtual void UIStaticText::OnDraw(void);
	public: virtual void UIStaticText::OnLBtnDown(int x, int y);
	public: virtual void UIStaticText::OnLBtnDblClk(int x, int y);
	public: virtual void UIStaticText::OnMouseMove(int x, int y);
	public: virtual void UIStaticText::OnLBtnUp(int x, int y);
	public: virtual void UIStaticText::OnMouseHover(int x, int y);
	public: virtual void UIStaticText::OnMouseShape(int x, int y);
	public: virtual void UIStaticText::OnWheel(int wheel);
	public: virtual void UIStaticText::OnRBtnDown(int x, int y);
	public: virtual void UIStaticText::OnRBtnUp(int x, int y);
	public: void UIStaticText::SetText(const char* txt, int drawBold);
	public: void UIStaticText::SetTextWithNumber(int number);
	public: void UIStaticText::SetTextWithShorten(const char* txt);
	public: void UIStaticText::SetTextWithNewWidth(const char* txt);
	//public: void UIStaticText::SetFont(int, int);
	//public: const char * GetFullText();

private:
	static hook_method<void (UIStaticText::*)(void)> UIStaticText::_OnDraw;
	static hook_method<void (UIStaticText::*)(int x, int y)> UIStaticText::_OnLBtnDown;
	static hook_method<void (UIStaticText::*)(int x, int y)> UIStaticText::_OnLBtnDblClk;
	static hook_method<void (UIStaticText::*)(int x, int y)> UIStaticText::_OnMouseMove;
	static hook_method<void (UIStaticText::*)(int x, int y)> UIStaticText::_OnLBtnUp;
	static hook_method<void (UIStaticText::*)(int x, int y)> UIStaticText::_OnMouseHover;
	static hook_method<void (UIStaticText::*)(int x, int y)> UIStaticText::_OnMouseShape;
	static hook_method<void (UIStaticText::*)(int wheel)> UIStaticText::_OnWheel;
	static hook_method<void (UIStaticText::*)(int x, int y)> UIStaticText::_OnRBtnDown;
	static hook_method<void (UIStaticText::*)(int x, int y)> UIStaticText::_OnRBtnUp;
	static hook_method<void (UIStaticText::*)(const char* txt, int drawBold)> UIStaticText::_SetText;
	static hook_method<void (UIStaticText::*)(int number)> UIStaticText::_SetTextWithNumber;
	static hook_method<void (UIStaticText::*)(const char* txt)> UIStaticText::_SetTextWithShorten;
	static hook_method<void (UIStaticText::*)(const char* txt)> UIStaticText::_SetTextWithNewWidth;
};


class UICheckBox : public UIWindow
{
public:
	UICheckBox();
	virtual ~UICheckBox();
	virtual void OnLBtnDown(int x, int y);
	virtual void OnDraw();
	virtual void OnMouseShape(int x, int y);
	void SetBitmap(const char* onBitmapName, const char* offBitmapName);
	void SetBitmap2(const char* onBitmapName, const char* offBitmapName, const char* checkMsg);
	void SetCheck(int check);
//	void SetCheck2(int check);

public:
	/* this+  0 */ //UIWindow baseclass_0;
	/* this+ 72 */ BOOL m_isDisabled;
private:
	/* this+ 76 */ mystd::string m_onBitmapName;
	/* this+ 92 */ mystd::string m_offBitmapName;
	/* this+108 */ mystd::string m_checkMsg;
};


class UIButton : public UIWindow
{
	struct vtable_t // const UIButton::`vftable'
	{
		void* (UIButton::* scalar_deleting_destructor)(unsigned int flags);
		void (UIWindow::* Invalidate)(void);
		void (UIWindow::* InvalidateWallPaper)(void);
		void (UIWindow::* Resize)(int cx, int cy);
		bool (UIWindow::* IsFrameWnd)(void);
		bool (UIWindow::* IsUpdateNeed)(void);
		void (UIWindow::* Move)(int x, int y);
		bool (UIWindow::* CanGetFocus)(void);
		bool (UIWindow::* GetTransBoxInfo)(BOXINFO* boxInfo);
		bool (UIWindow::* IsTransmitMouseInput)(void);

		bool (UIWindow::* ShouldDoHitTest)(void);
		void (UIWindow::* DragAndDrop)(int x, int y, const DRAG_INFO* const dragInfo);
		void (UIWindow::* StoreInfo)(void);
		void (UIWindow::* SaveOriginalPos)(void);
		void (UIWindow::* MoveDelta)(int deltaDragX, int deltaDragY);
		unsigned long (UIWindow::* GetColor)(void);
		void (UIWindow::* SetShow)(int visible);
		void (UIWindow::* OnCreate)(int cx, int cy);
		void (UIWindow::* OnDestroy)(void);
		void (UIWindow::* OnProcess)(void);

		void (UIButton::* OnDraw)(void);
		void (UIWindow::* OnDraw2)(void);
		void (UIWindow::* OnRun)(void);
		void (UIWindow::* OnSize)(int, int);
		void (UIWindow::* OnBeginEdit)(void);
		void (UIWindow::* OnFinishEdit)(void);
		void (UIButton::* OnLBtnDown)(int x, int y);
		void (UIButton::* OnLBtnDblClk)(int x, int y);
		void (UIButton::* OnMouseMove)(int x, int y);
		void (UIButton::* OnMouseHover)(int x, int y);

		void (UIButton::* OnMouseShape)(int x, int y);
		void (UIButton::* OnLBtnUp)(int x, int y);
		void (UIWindow::* OnRBtnDown)(int x, int y);
		void (UIWindow::* OnRBtnUp)(int x, int y);
		void (UIWindow::* OnRBtnDblClk)(int x, int y);
		void (UIWindow::* OnWheel)(int wheel);
		void (UIWindow::* RefreshSnap)(void);
		int (UIWindow::* SendMsg)(UIWindow* sender, int message, int val1, int val2, int val3);
	};

	/* this+  0 */ public: //UIWindow baseclass_0;
	/* this+ 72 */ protected: mystd::string m_text;
	/* this+ 88 */ protected: mystd::string m_toolTip;
	/* this+104 */ protected: int m_isDisabled;

	public: UIButton::UIButton(void);
	public: virtual UIButton::~UIButton(void);
	public: virtual void UIButton::OnLBtnDblClk(int x, int y);
	public: virtual void UIButton::OnLBtnDown(int x, int y);
	public: virtual void UIButton::OnMouseMove(int x, int y);
	public: virtual void UIButton::OnLBtnUp(int x, int y);
	public: virtual void UIButton::OnMouseShape(int x, int y);
	public: virtual void UIButton::OnDraw(void);
	public: virtual void UIButton::OnMouseHover(int x, int y);
	public: void UIButton::SetToolTip(const char* toolTip);
	public: void UIButton::SetText(mystd::string text);
	public: void UIButton::SetDiabled(int isDisabled); //TYPO

private:
	static hook_method<void (UIButton::*)(int x, int y)> UIButton::_OnLBtnDblClk;
	static hook_method<void (UIButton::*)(int x, int y)> UIButton::_OnLBtnDown;
	static hook_method<void (UIButton::*)(int x, int y)> UIButton::_OnMouseMove;
	static hook_method<void (UIButton::*)(int x, int y)> UIButton::_OnLBtnUp;
	static hook_method<void (UIButton::*)(int x, int y)> UIButton::_OnMouseShape;
	static hook_method<void (UIButton::*)(void)> UIButton::_OnDraw;
	static hook_method<void (UIButton::*)(int x, int y)> UIButton::_OnMouseHover;
	static hook_method<void (UIButton::*)(const char* toolTip)> UIButton::_SetToolTip;
	static hook_method<void (UIButton::*)(mystd::string text)> UIButton::_SetText;
	static hook_method<void (UIButton::*)(int isDisabled)> UIButton::_SetDiabled;
};


class UIBitmapButton : public UIButton
{
public:
	UIBitmapButton();
	virtual ~UIBitmapButton();
	virtual void OnDraw();
	void SetBitmapName(const char* bitmapName, int buttonState);
	int GetBitmapWidth();
	int GetBitmapHeight();

private:
	/* this+  0 */ //UIButton baseclass_0;
	/* this+108 */ int m_bitmapWidth;
	/* this+112 */ int m_bitmapHeight;
	/* this+116 */ mystd::string m_normalBitmapName;
	/* this+132 */ mystd::string m_mouseonBitmapName;
	/* this+148 */ mystd::string m_pressedBitmapName;
};


class UIEditCtrl : public UIWindow
{
	struct vtable_t
	{
		void* (UIEditCtrl::* scalar_deleting_destructor)(unsigned int flags);
		void (UIWindow::* Invalidate)(void);
		void (UIWindow::* InvalidateWallPaper)(void);
		void (UIWindow::* Resize)(int cx, int cy);
		bool (UIWindow::* IsFrameWnd)(void);
		bool (UIWindow::* IsUpdateNeed)(void);
		void (UIWindow::* Move)(int x, int y);
		bool (UIEditCtrl::* CanGetFocus)(void);
		bool (UIWindow::* GetTransBoxInfo)(BOXINFO* boxInfo);
		bool (UIWindow::* IsTransmitMouseInput)(void);

		bool (UIWindow::* ShouldDoHitTest)(void);
		void (UIWindow::* DragAndDrop)(int x, int y, const DRAG_INFO* const dragInfo);
		void (UIWindow::* StoreInfo)(void);
		void (UIWindow::* SaveOriginalPos)(void);
		void (UIWindow::* MoveDelta)(int deltaDragX, int deltaDragY);
		unsigned long (UIWindow::* GetColor)(void);
		void (UIWindow::* SetShow)(int visible);
		void (UIWindow::* OnCreate)(int cx, int cy);
		void (UIWindow::* OnDestroy)(void);
		void (UIWindow::* OnProcess)(void);

		void (UIEditCtrl::* OnDraw)(void);
		void (UIWindow::* OnDraw2)(void);
		void (UIWindow::* OnRun)(void);
		void (UIWindow::* OnSize)(int cx, int cy);
		void (UIEditCtrl::* OnBeginEdit)(void);
		void (UIEditCtrl::* OnFinishEdit)(void);
		void (UIEditCtrl::* OnLBtnDown)(int x, int y);
		void (UIWindow::* OnLBtnDblClk)(int x, int y);
		void (UIWindow::* OnMouseMove)(int x, int y);
		void (UIWindow::* OnMouseHover)(int x, int y);

		void (UIWindow::* OnMouseShape)(int x, int y);
		void (UIWindow::* OnLBtnUp)(int x, int y);
		void (UIWindow::* OnRBtnDown)(int x, int y);
		void (UIWindow::* OnRBtnUp)(int x, int y);
		void (UIWindow::* OnRBtnDblClk)(int x, int y);
		void (UIWindow::* OnWheel)(int wheel);
		void (UIWindow::* RefreshSnap)(void);
		int (UIEditCtrl::* SendMsg)(UIWindow* sender, int message, int val1, int val2, int val3);
		void (UIEditCtrl::* SetText)(const char* txt);
	};

	/* this+  0 */ public: //UIWindow baseclass_0;
	/* this+ 72 */ protected: int m_selectionOrigin;
	/* this+ 76 */ protected: int m_selectionCursor;
	/* this+ 80 */ protected: int m_maskchar;
	/* this+ 84 */ protected: int m_maxchar;
	/* this+ 88 */ protected: int m_isSingColorFrame;
	/* this+ 92 */ protected: int m_r;
	/* this+ 96 */ protected: int m_g;
	/* this+100 */ protected: int m_b;
	/* this+104 */ protected: int m_textR;
	/* this+108 */ protected: int m_textG;
	/* this+112 */ protected: int m_textB;
	/* this+116 */ protected: int m_xOffset;
	/* this+120 */ protected: int m_yOffset;
	/* this+124 */ private: mystd::string m_text;

	public: UIEditCtrl::UIEditCtrl(void);
	public: virtual UIEditCtrl::~UIEditCtrl(void);
	public: virtual void UIEditCtrl::OnLBtnDown(int x, int y);
	public: virtual void UIEditCtrl::OnDraw(void);
	public: virtual void UIEditCtrl::OnBeginEdit(void);
	public: virtual void UIEditCtrl::OnFinishEdit(void);
	public: virtual void UIEditCtrl::SetText(const char* txt);
	public: virtual bool UIEditCtrl::CanGetFocus(void);
	public: virtual int UIEditCtrl::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3);
	//public: void SetMaskChar(char);
	public: void UIEditCtrl::SetTextLimit(int limit);
	public: void UIEditCtrl::SetFrameColor(int r, int g, int b);
	public: void UIEditCtrl::SetTextColor(int r, int g, int b);
	public: void UIEditCtrl::MakeSelect(void);
	//public: void UIEditCtrl::DisableSelect(int);
	public: const char* UIEditCtrl::GetText(void);
	public: int UIEditCtrl::GetTextSize(void);
	//protected: void UIEditCtrl::RefreshText();
	//protected: void UIEditCtrl::DrawEditText();
	//protected: void UIEditCtrl::DrawSelectionBox(int, int);
	//protected: void UIEditCtrl::UpdateKeyStroke(int);
	//protected: void UIEditCtrl::UpdateCandidate(int);
	protected: void UIEditCtrl::SetTextByMaxChar(void);

private:
	static hook_method<void (UIEditCtrl::*)(int x, int y)> UIEditCtrl::_OnLBtnDown;
	static hook_method<void (UIEditCtrl::*)(void)> UIEditCtrl::_OnDraw;
	static hook_method<void (UIEditCtrl::*)(void)> UIEditCtrl::_OnBeginEdit;
	static hook_method<void (UIEditCtrl::*)(void)> UIEditCtrl::_OnFinishEdit;
	static hook_method<void (UIEditCtrl::*)(const char* txt)> UIEditCtrl::_SetText;
	static hook_method<bool (UIEditCtrl::*)(void)> UIEditCtrl::_CanGetFocus;
	static hook_method<int (UIEditCtrl::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UIEditCtrl::_SendMsg;
	static hook_method<void (UIEditCtrl::*)(int limit)> UIEditCtrl::_SetTextLimit;
	static hook_method<void (UIEditCtrl::*)(int r, int g, int b)> UIEditCtrl::_SetFrameColor;
	static hook_method<void (UIEditCtrl::*)(int r, int g, int b)> UIEditCtrl::_SetTextColor;
	static hook_method<void (UIEditCtrl::*)(void)> UIEditCtrl::_MakeSelect;
	static hook_method<const char* (UIEditCtrl::*)(void)> UIEditCtrl::_GetText;
	static hook_method<int (UIEditCtrl::*)(void)> UIEditCtrl::_GetTextSize;
	static hook_method<void (UIEditCtrl::*)(void)> UIEditCtrl::_SetTextByMaxChar;
};


class UIEditCtrl2 : public UIEditCtrl
{
	struct vtable_t
	{
		void* (UIEditCtrl2::* scalar_deleting_destructor)(unsigned int flags);
//		UIWindow::Invalidate(void)
//		UIWindow::InvalidateWallPaper(void)
//		UIWindow::Resize(int,int)
//		UIWindow::IsFrameWnd(void)
//		UIWindow::IsUpdateNeed(void)
//		UIWindow::Move(int,int)
//		UIEditCtrl::CanGetFocus(void)
//		UIWindow::GetTransBoxInfo(BOXINFO* boxInfo)
//		UIWindow::IsTransmitMouseInput(void)

//		UIWindow::ShouldDoHitTest(void)
		void (UIWindow::* DragAndDrop)(int x, int y, const DRAG_INFO* const dragInfo);
//		UIWindow::StoreInfo(void)
//		UIWindow::SaveOriginalPos(void)
//		UIWindow::MoveDelta(int,int)
//		UIWindow::GetColor(void)
//		UIWindow::SetShow(int)
//		UIWindow::OnCreate(int,int)
//		UIWindow::OnDestroy(void)
//		UIWindow::OnProcess(void)

//		UIEditCtrl::OnDraw(void)
//		UIWindow::OnDraw2(void)
//		UIWindow::OnRun(void)
//		UIWindow::OnSize(int,int)
//		UIEditCtrl::OnBeginEdit(void)
//		UIEditCtrl::OnFinishEdit(void)
//		UIEditCtrl::OnLBtnDown(int,int)
//		UIWindow::OnLBtnDblClk(int,int)
//		UIWindow::OnMouseMove(int,int)
//		UIWindow::OnMouseHover(int,int)

//		UIWindow::OnMouseShape(int,int)
//		UIWindow::OnLBtnUp(int,int)
//		UIWindow::OnRBtnDown(int,int)
//		UIWindow::OnRBtnUp(int,int)
//		UIWindow::OnRBtnDblClk(int,int)
//		UIWindow::OnWheel(int)
//		UIWindow::RefreshSnap(void)
//		UIEditCtrl2::SendMsg(UIWindow *,int,int,int,int)
//		UIEditCtrl::SetText(char const *)
	};

	/* this+0 */ public: //UIEditCtrl baseclass_0;

	public: UIEditCtrl2::UIEditCtrl2(void);
	public: virtual UIEditCtrl2::~UIEditCtrl2(void);
	//public: int UIEditCtrl2::SendMsg(class UIWindow *, int, int, int, int);
};


class UIBitmapEditCtrl : public UIEditCtrl
{
	struct vtable_t
	{
		void* (UIBitmapEditCtrl::* scalar_deleting_destructor)(unsigned int flags);
		void (UIWindow::* Invalidate)(void);
		void (UIWindow::* InvalidateWallPaper)(void);
		void (UIWindow::* Resize)(int cx, int cy);
		bool (UIWindow::* IsFrameWnd)(void);
		bool (UIWindow::* IsUpdateNeed)(void);
		void (UIWindow::* Move)(int x, int y);
		bool (UIEditCtrl::* CanGetFocus)(void);
		bool (UIWindow::* GetTransBoxInfo)(BOXINFO* boxInfo);
		bool (UIWindow::* IsTransmitMouseInput)(void);

		bool (UIWindow::* ShouldDoHitTest)(void);
		void (UIWindow::* DragAndDrop)(int x, int y, const DRAG_INFO* const dragInfo);
		void (UIWindow::* StoreInfo)(void);
		void (UIWindow::* SaveOriginalPos)(void);
		void (UIWindow::* MoveDelta)(int deltaDragX, int deltaDragY);
		unsigned long (UIWindow::* GetColor)(void);
		void (UIWindow::* SetShow)(int visible);
		void (UIWindow::* OnCreate)(int cx, int cy);
		void (UIWindow::* OnDestroy)(void);
		void (UIWindow::* OnProcess)(void);

		void (UIBitmapEditCtrl::* OnDraw)(void);
		void (UIWindow::* OnDraw2)(void);
		void (UIWindow::* OnRun)(void);
		void (UIWindow::* OnSize)(int cx, int cy);
		void (UIEditCtrl::* OnBeginEdit)(void);
		void (UIEditCtrl::* OnFinishEdit)(void);
		void (UIEditCtrl::* OnLBtnDown)(int x, int y);
		void (UIWindow::* OnLBtnDblClk)(int x, int y);
		void (UIWindow::* OnMouseMove)(int x, int y);
		void (UIWindow::* OnMouseHover)(int x, int y);

		void (UIWindow::* OnMouseShape)(int x, int y);
		void (UIWindow::* OnLBtnUp)(int x, int y);
		void (UIWindow::* OnRBtnDown)(int x, int y);
		void (UIWindow::* OnRBtnUp)(int x, int y);
		void (UIWindow::* OnRBtnDblClk)(int x, int y);
		void (UIWindow::* OnWheel)(int wheel);
		void (UIWindow::* RefreshSnap)(void);
		int (UIEditCtrl::* SendMsg)(UIWindow* sender, int message, int val1, int val2, int val3);
		void (UIEditCtrl::* SetText)(const char* txt);
	};

	/* this+  0 */ public: //UIEditCtrl baseclass_0;
	/* this+140 */ protected: mystd::string m_bitmapName;

	public: UIBitmapEditCtrl::UIBitmapEditCtrl(void);
	public: virtual UIBitmapEditCtrl::~UIBitmapEditCtrl(void);
	public: virtual void UIBitmapEditCtrl::OnDraw(void);
	public: void UIBitmapEditCtrl::SetBitmap(const char* bitmapName);

private:
	static hook_method<void (UIBitmapEditCtrl::*)(void)> UIBitmapEditCtrl::_OnDraw;
	static hook_method<void (UIBitmapEditCtrl::*)(const char* bitmapName)> UIBitmapEditCtrl::_SetBitmap;
};


class UIChatEditCtrl : public UIEditCtrl
{
	struct vtable_t
	{
		//TODO
	};

	/* this+  0 */ public: //UIEditCtrl baseclass_0;
	/* this+140 */ public: mystd::vector<mystd::string> m_hisChat;
	/* this+156 */ public: mystd::string m_lastEditText;
	/* this+172 */ public: int m_curHis;

	//public: void UIChatEditCtrl::UIChatEditCtrl();
	//public: int UIChatEditCtrl::SendMsg(class UIWindow *, int, int, int, int);
	//public: void UIChatEditCtrl::OnLBtnDown(int, int);
	public: void UIChatEditCtrl::StoreInHistory(void);

private:
	static hook_method<void (UIChatEditCtrl::*)(void)> UIChatEditCtrl::_StoreInHistory;
};


class UIWhisperEditCtrl : public UIEditCtrl
{
	struct vtable_t
	{
		//TODO
	};

	/* this+  0 */ public: //UIEditCtrl baseclass_0;
	/* this+140 */ public: mystd::vector<mystd::string> m_hisChat;
	/* this+156 */ public: int m_curHis;

	public: UIWhisperEditCtrl::UIWhisperEditCtrl(void);
	public: virtual void UIWhisperEditCtrl::OnBeginEdit(void);
	public: virtual void UIWhisperEditCtrl::OnFinishEdit(void);
	public: virtual void UIWhisperEditCtrl::SetText(const char* txt);
	public: virtual int UIWhisperEditCtrl::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3);
	public: void UIWhisperEditCtrl::StoreInHistory(void);

private:
	static hook_method<void (UIWhisperEditCtrl::*)(void)> UIWhisperEditCtrl::_OnBeginEdit;
	static hook_method<void (UIWhisperEditCtrl::*)(void)> UIWhisperEditCtrl::_OnFinishEdit;
	static hook_method<void (UIWhisperEditCtrl::*)(const char* txt)> UIWhisperEditCtrl::_SetText;
	static hook_method<int (UIWhisperEditCtrl::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UIWhisperEditCtrl::_SendMsg;
	static hook_method<void (UIWhisperEditCtrl::*)(void)> UIWhisperEditCtrl::_StoreInHistory;
};


class UIResizer : public UIWindow
{
	struct vtable_t
	{
		void* (UIResizer::* scalar_deleting_destructor)(unsigned int flags);
		void (UIWindow::* Invalidate)(void);
		void (UIWindow::* InvalidateWallPaper)(void);
		void (UIWindow::* Resize)(int cx, int cy);
		bool (UIWindow::* IsFrameWnd)(void);
		bool (UIWindow::* IsUpdateNeed)(void);
		void (UIWindow::* Move)(int x, int y);
		bool (UIWindow::* CanGetFocus)(void);
		bool (UIWindow::* GetTransBoxInfo)(BOXINFO* boxInfo);
		bool (UIWindow::* IsTransmitMouseInput)(void);

		bool (UIWindow::* ShouldDoHitTest)(void);
		void (UIWindow::* DragAndDrop)(int x, int y, const DRAG_INFO* const dragInfo);
		void (UIWindow::* StoreInfo)(void);
		void (UIWindow::* SaveOriginalPos)(void);
		void (UIWindow::* MoveDelta)(int deltaDragX, int deltaDragY);
		unsigned long (UIWindow::* GetColor)(void);
		void (UIWindow::* SetShow)(int visible);
		void (UIWindow::* OnCreate)(int cx, int cy);
		void (UIWindow::* OnDestroy)(void);
		void (UIWindow::* OnProcess)(void);

		void (UIResizer::* OnDraw)(void);
		void (UIWindow::* OnDraw2)(void);
		void (UIWindow::* OnRun)(void);
		void (UIWindow::* OnSize)(int cx, int cy);
		void (UIWindow::* OnBeginEdit)(void);
		void (UIWindow::* OnFinishEdit)(void);
		void (UIResizer::* OnLBtnDown)(int x, int y);
		void (UIWindow::* OnLBtnDblClk)(int x, int y);
		void (UIResizer::* OnMouseMove)(int x, int y);
		void (UIResizer::* OnMouseHover)(int x, int y);

		void (UIResizer::* OnMouseShape)(int x, int y);
		void (UIResizer::* OnLBtnUp)(int x, int y);
		void (UIWindow::* OnRBtnDown)(int x, int y);
		void (UIWindow::* OnRBtnUp)(int x, int y);
		void (UIWindow::* OnRBtnDblClk)(int x, int y);
		void (UIWindow::* OnWheel)(int wheel);
		void (UIWindow::* RefreshSnap)(void);
		int (UIWindow::* SendMsg)(UIWindow* sender, int message, int val1, int val2, int val3);
	};

	/* this+  0 */ public: //UIWindow baseclass_0;
	/* this+ 72 */ protected: mystd::string m_bitmapName;
	/* this+ 88 */ protected: int m_startX;
	/* this+ 92 */ protected: int m_startY;
	/* this+ 96 */ protected: RESIZERTYPE m_type;
	/* this+100 */ protected: int m_parentWidth;
	/* this+104 */ protected: int m_parentHeight;
	/* this+108 */ protected: unsigned long m_color;
	/* this+112 */ protected: unsigned long m_backColor;

	public: UIResizer::UIResizer(void);
	public: virtual void UIResizer::OnDraw(void);
	public: virtual void UIResizer::OnLBtnDown(int x, int y);
	public: virtual void UIResizer::OnMouseMove(int x, int y);
	public: virtual void UIResizer::OnLBtnUp(int x, int y);
	public: virtual void UIResizer::OnMouseHover(int x, int y);
	public: virtual void UIResizer::OnMouseShape(int x, int y);
	public: void UIResizer::SetBitmap(const char* bitmapName);
	public: void UIResizer::SetType(RESIZERTYPE type);
	public: void UIResizer::SetColor(unsigned long color, unsigned long backColor);
	//public: void SetColor(unsigned long);

private:
	static hook_method<void (UIResizer::*)(void)> UIResizer::_OnDraw;
	static hook_method<void (UIResizer::*)(int x, int y)> UIResizer::_OnLBtnDown;
	static hook_method<void (UIResizer::*)(int x, int y)> UIResizer::_OnMouseMove;
	static hook_method<void (UIResizer::*)(int x, int y)> UIResizer::_OnLBtnUp;
	static hook_method<void (UIResizer::*)(int x, int y)> UIResizer::_OnMouseHover;
	static hook_method<void (UIResizer::*)(int x, int y)> UIResizer::_OnMouseShape;
	static hook_method<void (UIResizer::*)(const char* bitmapName)> UIResizer::_SetBitmap;
	static hook_method<void (UIResizer::*)(RESIZERTYPE type)> UIResizer::_SetType;
	static hook_method<void (UIResizer::*)(unsigned long color, unsigned long backColor)> UIResizer::_SetColor;
};


class UIRadioBtn : public UIWindow
{
	/* this+ 0 */ public: //UIWindow baseclass_0;
	/* this+72 */ public: mystd::string m_text;
	/* this+88 */ public: int m_isEnabled;

	public: UIRadioBtn::UIRadioBtn(void);
	public: virtual UIRadioBtn::~UIRadioBtn(void);
	public: virtual void UIRadioBtn::OnDraw(void);
	public: virtual void UIRadioBtn::OnLBtnDown(int x, int y);
	public: virtual int UIRadioBtn::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3);
	public: void UIRadioBtn::SetText(const char* text);

private:
	static hook_method<void (UIRadioBtn::*)(void)> UIRadioBtn::_OnDraw;
	static hook_method<void (UIRadioBtn::*)(int x, int y)> UIRadioBtn::_OnLBtnDown;
	static hook_method<int (UIRadioBtn::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UIRadioBtn::_SendMsg;
	static hook_method<void (UIRadioBtn::*)(const char* text)> UIRadioBtn::_SetText;
};


class UIChatRoomTitle : public UIWindow
{
	struct vtable_t
	{
		//TODO
	};

	/* this+ 0 */ public: //UIWindow baseclass_0;
	/* this+72 */ public: UIStaticText* m_title;
	/* this+76 */ public: ChatRoomInfo m_roomInfo;

	public: UIChatRoomTitle::UIChatRoomTitle(void);
	public: virtual UIChatRoomTitle::~UIChatRoomTitle(void);
	//public: void UIChatRoomTitle::OnCreate(int, int);
	//public: void UIChatRoomTitle::OnDraw();
	//public: void UIChatRoomTitle::OnLBtnDblClk(int, int);
	//public: int UIChatRoomTitle::SendMsg(class UIWindow *, int, int, int, int);
	//public: void UIChatRoomTitle::OnMouseShape(int, int);
	//public: int GetRoomId();
};


class UIMerchantShopTitle : public UIWindow
{
	/* this+ 0 */ public: //UIWindow baseclass_0;
	/* this+72 */ public: UIStaticText* m_title;
	/* this+76 */ public: unsigned long m_shopOwnerAid;

	public: UIMerchantShopTitle::UIMerchantShopTitle(void);
	public: virtual UIMerchantShopTitle::~UIMerchantShopTitle(void);
	//public: void UIMerchantShopTitle::OnCreate(int, int);
	//public: void UIMerchantShopTitle::OnDraw(void);
	//public: void UIMerchantShopTitle::OnLBtnDblClk(int, int);
	//public: int UIMerchantShopTitle::SendMsg(class UIWindow *, int, int, int, int);
	//public: void UIMerchantShopTitle::OnMouseShape(int, int);
	//public: int GetShopOwnerAid(void);
};
