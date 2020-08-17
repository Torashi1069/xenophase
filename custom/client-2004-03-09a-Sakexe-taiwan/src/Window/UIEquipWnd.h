#pragma once
#include "ItemInfo.h" // ITEM_INFO
#include "Window/UIFrameWnd.h"
struct DRAG_INFO; // #include "Struct.h"
struct EquipWndInfo; // #include "Window/UIRectInfo.h"
class UIBitmapButton; // #include "Window/UIControl.h"


class UIEquipWnd : public UIFrameWnd
{
public:
	UIEquipWnd();
	virtual ~UIEquipWnd();

public:
	virtual bool IsUpdateNeed();
	virtual void OnCreate(int cx, int cy);
	virtual void OnDraw();
	virtual int SendMsg(UIWindow* sender, int message, int val1, int val2, int val3);
	virtual void DragAndDrop(int x, int y, const DRAG_INFO* const dragInfo);
	virtual void OnMouseHover(int x, int y);
	virtual void OnMouseMove(int x, int y);
	virtual void OnLBtnDblClk(int x, int y);
	virtual void OnLBtnDown(int x, int y);
	virtual void OnRBtnDown(int x, int y);
	virtual void StoreInfo();
	ITEM_INFO GetItemInfo(int x, int y);

protected:
	bool HasOptionOffButton();
	bool HasOptionOpenButton();
	const char* GetOptionOffToolTipText();
	const char* GetOptionOpenToolTipText();
	void SendOptionOffToMode();

protected:
	/* this+  0 */ //UIFrameWnd baseclass_0;
	/* this+ 96 */ int m_highlightMode[3];
	/* this+108 */ int m_orgHeight;
	/* this+112 */ EquipWndInfo* m_info;
	/* this+116 */ UIBitmapButton* m_optionOffButton;
	/* this+120 */ UIBitmapButton* m_optionOpenButton;
};
