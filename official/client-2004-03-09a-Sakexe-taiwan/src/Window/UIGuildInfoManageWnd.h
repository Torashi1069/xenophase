#pragma once
#include "Window/UIGuildWnd.h"


class UIGuildInfoManageWnd : public UIGuildWnd
{
public:
	UIGuildInfoManageWnd();
	virtual ~UIGuildInfoManageWnd();
	virtual void OnCreate(int cx, int cy);
	virtual void OnDraw();
	virtual void OnLBtnDown(int x, int y);
	virtual void OnRBtnUp(int x, int y);
	virtual int SendMsg(UIWindow* sender, int message, int val1, int val2, int val3);
	virtual int GetTab();
	void RefreshEmblemList();
	void DeleteCompressedEmblemBitmapFileImage();
	void RefreshCompressedEmblemFileImage(const char* emblemBitmapFileName);
	void SetEmblemResName();

protected:
	/* this+  0 */ //UIGuildWnd baseclass_0;
	/* this+124 */ UIBitmapButton* m_emblemChangeButton;
	/* this+128 */ mystd::list<mystd::string> m_emblemList;
	/* this+140 */ char* m_compressedEmblemBitmapFileImage;
	/* this+144 */ unsigned long m_compressedEmblemBitmapFileImageSize;
	/* this+148 */ int m_gdid;
	/* this+152 */ int m_emblemVersion;
	/* this+156 */ mystd::string m_emblemResName;
	/* this+172 */ int m_curAllyGuild;
	/* this+176 */ int m_curHostileGuild;
	/* this+180 */ mystd::vector<StringId> m_menuItems;
};
