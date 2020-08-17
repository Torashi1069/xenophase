#pragma once
#include "Window/UIWindow.h"
#include "Window/UISys.h"
class UIScrollBar;


class UIBarGraph : public UIWindow
{
	struct vtable_t
	{
		//TODO
	};

	/* this+ 0 */ public: //UIWindow baseclass_0;
	/* this+72 */ public: float m_percent;

	public: UIBarGraph::UIBarGraph(void);
	public: virtual UIBarGraph::~UIBarGraph(void);
	public: virtual void UIBarGraph::OnDraw(void);
	public: void UIBarGraph::SetAmount(float percent);

private:
	static hook_method<void (UIBarGraph::*)(void)> UIBarGraph::_OnDraw;
	static hook_method<void (UIBarGraph::*)(float percent)> UIBarGraph::_SetAmount;
};


class UIBarGraph2 : public UIBarGraph
{
	struct vtable_t
	{
		//TODO
	};

	/* this+  0 */ public: //UIBarGraph baseclass_0;
	/* this+ 76 */ public: int m_isVertical;
	/* this+ 80 */ public: int m_backR;
	/* this+ 84 */ public: int m_backG;
	/* this+ 88 */ public: int m_backB;
	/* this+ 92 */ public: int m_r;
	/* this+ 96 */ public: int m_g;
	/* this+100 */ public: int m_b;

	public: UIBarGraph2::UIBarGraph2(void);
	public: virtual UIBarGraph2::~UIBarGraph2(void);
	public: virtual void UIBarGraph2::OnDraw(void);

private:
	static hook_method<void (UIBarGraph2::*)(void)> UIBarGraph2::_OnDraw;
};


class UIListBox : public UIWindow
{
public:
	UIListBox();
	virtual ~UIListBox();
	virtual void Create2(int x, int y, int cx, int cy, bool trans);
	virtual void OnCreate(int cx, int cy);
	virtual void OnLBtnDown(int x, int y);
	virtual void OnLBtnDblClk(int x, int y);
	virtual void OnWheel(int wheel);
	virtual void OnDraw();
	virtual int SendMsg(UIWindow* sender, int message, int val1, int val2, int val3);
	virtual void AddItem(const char* txt);
	virtual void ClearAllItems();
	virtual void Resize(int cx, int cy);
	virtual void RecalcScrbarPos();
	int IsVertScrEnabled();
	int GetSelected();
	//int GetNumItem();
	//mystd::string& GetItem(int);
protected:
	//int HitTest(int, int);

public:
	/* this+  0 */ //UIWindow baseclass_0;
	/* this+ 72 */ int m_bR;
	/* this+ 76 */ int m_bG;
	/* this+ 80 */ int m_bB;
protected:
	/* this+ 84 */ mystd::vector<mystd::string> m_items;
	/* this+100 */ int m_curItem;
	/* this+104 */ int m_vertViewOffset;
	/* this+108 */ int m_horzViewOffset;
	/* this+112 */ int m_maxTextWidth;
	/* this+116 */ int m_vertScrEnabled;
	/* this+120 */ int m_horzScrEnabled;
	/* this+124 */ UIScrollBar* m_vertScrollBar;
	/* this+128 */ UIScrollBar* m_horzScrollBar;
	/* this+132 */ BOOL m_isTransParent;
	/* this+136 */ int m_itemSpacing;
	/* this+140 */ bool m_noColor;

private:
	static hook_method<void (UIListBox::*)(int cx, int cy)> UIListBox::_OnCreate;
	static hook_method<void (UIListBox::*)(int x, int y)> UIListBox::_OnLBtnDown;
	static hook_method<void (UIListBox::*)(int x, int y)> UIListBox::_OnLBtnDblClk;
	static hook_method<void (UIListBox::*)(int wheel)> UIListBox::_OnWheel;
	static hook_method<void (UIListBox::*)(void)> UIListBox::_OnDraw;
	static hook_method<int (UIListBox::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UIListBox::_SendMsg;
	static hook_method<void (UIListBox::*)(const char* txt)> UIListBox::_AddItem;
	static hook_method<void (UIListBox::*)(void)> UIListBox::_RecalcScrbarPos;
	static hook_method<int (UIListBox::*)(void)> UIListBox::_IsVertScrEnabled;
	static hook_method<int (UIListBox::*)(void)> UIListBox::_GetSelected;
};
