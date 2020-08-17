#pragma once
#include "Window/UIWindow.h"


class UIScrollBar : public UIWindow
{
	struct vtable_t // const UIScrollBar::`vftable'
	{
		void* (UIScrollBar::* scalar_deleting_destructor)(unsigned int flags);
		void (UIScrollBar::* Resize)(int cx, int cy);
		bool (UIScrollBar::* IsTransmitMouseInput)(void);
		void (UIScrollBar::* OnDraw)(void);
		void (UIScrollBar::* OnLBtnDown)(int x, int y);
		void (UIScrollBar::* OnLBtnDblClk)(int x, int y);
		void (UIScrollBar::* OnMouseMove)(int x, int y);
		void (UIScrollBar::* OnMouseShape)(int x, int y);
		void (UIScrollBar::* OnLBtnUp)(int x, int y);
		void (UIScrollBar::* OnRBtnUp)(int x, int y);
		void (UIScrollBar::* OnWheel)(int wheel);
	};

	/* this+  0 */ public: //UIWindow baseclass_0;
	/* this+ 72 */ protected: int m_drawMode;
	/* this+ 76 */ protected: int m_maxPos;
	/* this+ 80 */ protected: int m_curPos;
	/* this+ 84 */ protected: int m_isVert;
	/* this+ 88 */ protected: int m_startDragX;
	/* this+ 92 */ protected: int m_startDragY;
	/* this+ 96 */ protected: int m_deltaDrag;
	/* this+100 */ protected: int m_parentNumItem;
	/* this+104 */ protected: int m_parentnumCanDisplayItem;
	/* this+108 */ protected: int m_scrollBtnSize;

	public: UIScrollBar::UIScrollBar(void);
	public: virtual UIScrollBar::~UIScrollBar(void);
	public: void UIScrollBar::Create(int x, int y, int type, int size);
	public: virtual void UIScrollBar::OnLBtnDown(int x, int y);
	public: virtual void UIScrollBar::OnLBtnDblClk(int x, int y);
	public: virtual void UIScrollBar::OnMouseMove(int x, int y);
	public: virtual void UIScrollBar::OnMouseShape(int x, int y);
	public: virtual void UIScrollBar::OnLBtnUp(int x, int y);
	public: virtual void UIScrollBar::OnRBtnUp(int x, int y);
	public: virtual void UIScrollBar::OnWheel(int wheel);
	public: virtual void UIScrollBar::OnDraw(void);
	public: virtual void UIScrollBar::Resize(int cx, int cy);
	public: virtual bool UIScrollBar::IsTransmitMouseInput(void);
	public: void UIScrollBar::SetRange(int range, int parentnumCanDisplayItem, int parentNumItem);
	public: void UIScrollBar::SetPos(int pos);
	public: int UIScrollBar::GetPos(void);
	protected: int UIScrollBar::HitTest(int x, int y);
	protected: int UIScrollBar::GetThumbSize(void);
	protected: int UIScrollBar::GetScrollRange(void);
	protected: int UIScrollBar::GetThumbOffset(void);

private:
	static hook_method<void (UIScrollBar::*)(int x, int y, int type, int size)> UIScrollBar::_Create;
	static hook_method<void (UIScrollBar::*)(int x, int y)> UIScrollBar::_OnLBtnDown;
	static hook_method<void (UIScrollBar::*)(int x, int y)> UIScrollBar::_OnLBtnDblClk;
	static hook_method<void (UIScrollBar::*)(int x, int y)> UIScrollBar::_OnMouseMove;
	static hook_method<void (UIScrollBar::*)(int x, int y)> UIScrollBar::_OnMouseShape;
	static hook_method<void (UIScrollBar::*)(int x, int y)> UIScrollBar::_OnLBtnUp;
	static hook_method<void (UIScrollBar::*)(int x, int y)> UIScrollBar::_OnRBtnUp;
	static hook_method<void (UIScrollBar::*)(int wheel)> UIScrollBar::_OnWheel;
	static hook_method<void (UIScrollBar::*)(void)> UIScrollBar::_OnDraw;
	static hook_method<void (UIScrollBar::*)(int cx, int cy)> UIScrollBar::_Resize;
	static hook_method<bool (UIScrollBar::*)(void)> UIScrollBar::_IsTransmitMouseInput;
	static hook_method<void (UIScrollBar::*)(int range, int parentnumCanDisplayItem, int parentNumItem)> UIScrollBar::_SetRange;
	static hook_method<int (UIScrollBar::*)(void)> UIScrollBar::_GetPos;
	static hook_method<int (UIScrollBar::*)(int x, int y)> UIScrollBar::_HitTest;
	static hook_method<int (UIScrollBar::*)(void)> UIScrollBar::_GetThumbSize;
	static hook_method<int (UIScrollBar::*)(void)> UIScrollBar::_GetScrollRange;
	static hook_method<int (UIScrollBar::*)(void)> UIScrollBar::_GetThumbOffset;
};
