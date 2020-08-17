#pragma once
#include "Window/UIControl2.h"


class UIChatHisBox : public UIListBox
{
public:
	UIChatHisBox();
	virtual ~UIChatHisBox();
	virtual void Create2(int x, int y, int cx, int cy, bool trans);
	virtual void OnCreate(int cx, int cy);
	virtual void OnLBtnDown(int x, int y);
	virtual void OnLBtnDblClk(int x, int y);
	virtual void OnLBtnUp(int x, int y);
	virtual void OnDraw();
	virtual int SendMsg(UIWindow* sender, int message, int val1, int val2, int val3);
	virtual bool IsTransmitMouseInput();
	virtual void AddItem(const char* txt, COLORREF itemRGB);
	virtual void ClearAllItems();
	virtual void Resize(int cx, int cy);
	virtual void SetShow(BOOL visible);
	void DeleteFirstHalfItem();
//	COLORREF GetItemColor(int);
	BOOL WriteChatToFile(const char* fileName);

protected:
	/* this+  0 */ //UIListBox baseclass_0;
	/* this+144 */ mystd::vector<COLORREF> m_itemColors;
	/* this+160 */ int m_maxItem;

private:
	static hook_func<void (UIChatHisBox::*)(const char* txt, COLORREF itemRGB)> UIChatHisBox::_AddItem;
	static hook_func<void (UIChatHisBox::*)()> UIChatHisBox::_DeleteFirstHalfItem;
	static hook_func<BOOL (UIChatHisBox::*)(const char* fileName)> UIChatHisBox::_WriteChatToFile;
};
