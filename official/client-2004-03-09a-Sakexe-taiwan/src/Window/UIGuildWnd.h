#pragma once
#include "Struct.h"
#include "Window/UIFrameWnd.h"
class UIBitmapButton;
class UIStaticText;


class UIGuildWnd : public UIFrameWnd
{
public:
	UIGuildWnd();
	virtual ~UIGuildWnd();
	virtual void OnCreate(int cx, int cy) = 0;
	virtual void OnLBtnDown(int x, int y);
	virtual int GetTab() = 0;
	virtual int SendMsg(UIWindow* sender, int message, int val1, int val2, int val3);
	virtual void OnDraw();
	virtual void StoreInfo();
	void DrawTab(int curTab);
	void InitTabText();

protected:
	/* this+  0 */ //UIFrameWnd baseclass_0;
	/* this+ 96 */ GuildWndInfo* m_info;
	/* this+100 */ UIStaticText* m_tabText[6];
};


class UIGuildMemberManageWnd : public UIGuildWnd
{
public:
//	UIGuildMemberManageWnd();
//	~UIGuildMemberManageWnd();
//	void OnCreate(int, int);
//	void OnDraw();
//	void OnLBtnDown(int, int);
//	void OnRBtnDown(int, int);
//	int SendMsg(class UIWindow *, int, int, int, int);
//	int GetTab();
//	void OnWheel(int);
//	void OnRBtnUp(int, int);
//	void RecalcScrbarPos();
//	int GetCurItem(int, int);
//	unsigned char GetMemberInfo(int, struct GUILD_MEMBER_INFORMATION *);

protected:
	/* this+  0 */ //UIGuildWnd baseclass_0;
	/* this+124 */ UIStaticText* m_memberName[5];
	/* this+144 */ UIStaticText* m_positionName[5];
	/* this+164 */ UIStaticText* m_jobName[5];
	/* this+184 */ UIStaticText* m_memo[5];
	/* this+204 */ UIBitmapButton* m_posComboButton[5];
	/* this+224 */ UIScrollBar* m_scrollBar;
	/* this+228 */ UIBitmapButton* m_applyButton;
	/* this+232 */ mystd::vector<StringId> m_menuItems;
	/* this+248 */ int m_viewOffset;
	/* this+252 */ int m_curItem;
	/* this+256 */ int m_itemHorzNum;
	/* this+260 */ int m_itemVertNum;
	/* this+264 */ int m_vertScrEnabled;
	/* this+268 */ int m_posComboSeq;
	/* this+272 */ mystd::list<GUILD_MEMBER_INFORMATION> m_memberInfoList;
	/* this+284 */ mystd::map<int,MEMBER_POSITION_INFORMATION> m_memberPositionInfoListForChange;
};
