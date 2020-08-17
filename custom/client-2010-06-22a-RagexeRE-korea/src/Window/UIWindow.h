#pragma once
#include "std/list"
class CBitmapRes;
class CDC;
struct BOXINFO;
struct DRAG_INFO;


class UIWindow
{
public:
	UIWindow();
	virtual ~UIWindow();
	void Create(int cx, int cy);
	void Destroy();
	void AddChild(UIWindow* window);
	void RemoveChild(UIWindow* window);
	void RemoveAllChildren();
	void ClearAllChildrenState();
	void InvalidateChildren();
	void SetId(int id);
	int GetId();
	BOOL IsFamily(UIWindow* window);
	virtual void Invalidate();
	virtual void InvalidateWallPaper();
	UIWindow* HitTest(int x, int y);
	void DoDraw(BOOL blitToParent);
	virtual void Resize(int cx, int cy);
	virtual bool IsFrameWnd();
	virtual bool IsUpdateNeed();
	virtual void Move(int x, int y);
	virtual bool CanGetFocus();
	virtual bool GetTransBoxInfo(BOXINFO* boxInfo);
	virtual bool IsTransmitMouseInput();
	virtual bool ShouldDoHitTest();
	virtual void DragAndDrop(int x, int y, const DRAG_INFO* const dragInfo);
	virtual void StoreInfo();
	virtual void SaveOriginalPos();
	virtual void MoveDelta(int deltaDragX, int deltaDragY);
	bool IsChildOf(UIWindow* win);
	UIWindow* GetNextSiblingOf(UIWindow* wnd);
	UIWindow* GetPrevSiblingOf(UIWindow* wnd);
	UIWindow* GetAncestor();
	void GetGlobalCoor(int& x, int& y);
	BOOL IsShow();
	virtual COLORREF GetColor();
	virtual void SetShow(BOOL visible);
	virtual void OnCreate(int cx, int cy);
	virtual void OnDestroy();
	virtual void OnProcess();
	virtual void OnDraw();
	virtual void OnRun();
	virtual void OnSize(int cx, int cy);
	virtual void OnBeginEdit();
	virtual void OnFinishEdit();
	virtual void OnLBtnDown(int x, int y);
	virtual void OnLBtnDblClk(int x, int y);
	virtual void OnMouseMove(int x, int y);
	virtual void OnMouseHover(int x, int y);
	virtual void OnMouseShape(int x, int y);
	virtual void OnLBtnUp(int x, int y);
	virtual void OnRBtnDown(int x, int y);
	virtual void OnRBtnUp(int x, int y);
	virtual void OnRBtnDblClk(int x, int y);
	virtual void OnWheel(int wheel);
	virtual void RefreshSnap();
	virtual int UIWindow::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3, int val4);
	virtual bool GetTransBoxInfo2(BOXINFO* boxInfo);
	virtual void DrawBoxScreen2();
	int GetX();
	int GetY();
	int GetHeight();
	int GetWidth();

protected:
	void DrawBitmap(int x, int y, CBitmapRes* bitmap, bool drawOnlyNoTrans);
	void DrawBitmap_2(int a2, int x, int y, CBitmapRes* bitmap, bool a6, bool a7); //TODO
	void TextOutA(int x, int y, const char* text, int textLen, int fontType, int fontHeight, COLORREF colorRef);
	void TextOutWithRightAlign(int x, int y, const char* text, int textLen, int fontType, int fontHeight, COLORREF colorRef);
//	void TextOutWithDecoration(int x, int y, const char* text, int textLen, COLORREF* colorRef, int fontType, int fontHeight);
	void TextOutWithShadow(int x, int y, const char* text, int textLen, COLORREF colorText, COLORREF colorShadow, int fontType, int fontHeight);
	void TextOutWithOutline(int x, int y, const char* text, int textLen, COLORREF colorText, COLORREF colorOutline, int fontType, int fontHeight, bool bold);
//	void TextOutWithDecoOutline(int x, int y, const char* text, int textLen, COLORREF* colorText, COLORREF colorOutline, int fontType, int fontHeight, bool bold);
//	void TextOutVertical(int x, int y, const char* text, int textLen, int fontType, int fontHeight, COLORREF colorRef);
	void TextOutWithOutlineVertical(int x, int y, const char* text, int textLen, COLORREF colorText, COLORREF colorOutline, int fontType, int fontHeight, bool bold);
	void TextOutWithTwoColors(int x, int y, const char* text, COLORREF colorRef, COLORREF colorRef2, int textLen, int fontType, int fontHeight);
	int GetTextWidth(const char* text, int textLen, int fontType, int fontHeight, bool bold);
	int GetTextHeight(const char* text, int textLen, int fontType, int fontHeight, bool bold);
//	int GetTextHeightVertical(const char* text, int textLen, int fontType, int fontHeight, bool bold);
//	int GetColorTextWidth(const char* text, int textLen, int fontType, int fontHeight, bool bold);
//	char* PolishText(const char* text, int drawWidth, int fontType, int fontHeight, bool bold);
//	char* PolishText2(const char* text, int maxNumCharLine);
//	void PolishText3(const char* text, mystd::vector<mystd::string>& strings, mystd::vector<bool>& enters, int width);
//	void PolishText4(const char* text, mystd::vector<mystd::string>& strings, int width);
	void ClearDC(COLORREF color);
	void ClearDCRect(COLORREF color, RECT& rect);
	void DrawBox(int x, int y, int cx, int cy, COLORREF color);
	void DrawBorderLine(int x, int y, int w, int h, COLORREF color);
	void DrawBorderLine_1px(int x, int y, int w, int h, COLORREF color); //TODO
	void DrawTriangleDC(int x1, int y1, int x2, int y2, int x3, int y3, COLORREF color);
	const char* InterpretColor(const char* color_text, COLORREF* colorRef);
	const char* FindColorMark(const char* text, const char* text_end);

protected:
	/* this+ 0 */ //const UIWindow::`vftable';
	/* this+ 4 */ UIWindow* m_parent;
	/* this+ 8 */ mystd::list<UIWindow*> m_children;
	/* this+20 */ int m_x;
	/* this+24 */ int m_y;
	/* this+28 */ int m_w;
	/* this+32 */ int m_h;
	/* this+36 */ BOOL m_isDirty;
	/* this+40 */ CDC* m_dc;
	/* this+44 */ int m_id; // enum UIID
	/* this+48 */ int m_state;
	/* this+52 */ int m_stateCnt;
	/* this+56 */ BOOL m_show;
	/* this+60 */ DWORD m_trans;
	/* this+64 */ DWORD m_transTarget;
	/* this+68 */ DWORD m_transTime;
};
C_ASSERT( sizeof UIWindow == 72 );


struct UIWindowVtbl
{
	void* (UIWindow::* scalar_deleting_destructor)(unsigned int flags);
	void (UIWindow::* Invalidate)();
	void (UIWindow::* InvalidateWallPaper)();
	void (UIWindow::* Resize)(int cx, int cy);
	bool (UIWindow::* IsFrameWnd)();
	bool (UIWindow::* IsUpdateNeed)();
	void (UIWindow::* Move)(int x, int y);
	bool (UIWindow::* CanGetFocus)();
	bool (UIWindow::* GetTransBoxInfo)(BOXINFO* boxInfo);
	bool (UIWindow::* IsTransmitMouseInput)();
	bool (UIWindow::* ShouldDoHitTest)();
	void (UIWindow::* DragAndDrop)(int x, int y, const DRAG_INFO* const dragInfo);
	void (UIWindow::* StoreInfo)();
	void (UIWindow::* SaveOriginalPos)();
	void (UIWindow::* MoveDelta)(int deltaDragX, int deltaDragY);
	COLORREF (UIWindow::* GetColor)();
	void (UIWindow::* SetShow)(BOOL visible);
	void (UIWindow::* OnCreate)(int cx, int cy);
	void (UIWindow::* OnDestroy)();
	void (UIWindow::* OnProcess)();
	void (UIWindow::* OnDraw)();
	void (UIWindow::* OnRun)();
	void (UIWindow::* OnSize)(int cx, int cy);
	void (UIWindow::* OnBeginEdit)();
	void (UIWindow::* OnFinishEdit)();
	void (UIWindow::* OnLBtnDown)(int x, int y);
	void (UIWindow::* OnLBtnDblClk)(int x, int y);
	void (UIWindow::* OnMouseMove)(int x, int y);
	void (UIWindow::* OnMouseHover)(int x, int y);
	void (UIWindow::* OnMouseShape)(int x, int y);
	void (UIWindow::* OnLBtnUp)(int x, int y);
	void (UIWindow::* OnRBtnDown)(int x, int y);
	void (UIWindow::* OnRBtnUp)(int x, int y);
	void (UIWindow::* OnRBtnDblClk)(int x, int y);
	void (UIWindow::* OnWheel)(int wheel);
	void (UIWindow::* RefreshSnap)();
	int (UIWindow::* SendMsg)(UIWindow* sender, int message, int val1, int val2, int val3, int val4);
	bool (UIWindow::* GetTransBoxInfo2)(BOXINFO* boxInfo);
	void (UIWindow::* DrawBoxScreen2)();
};
