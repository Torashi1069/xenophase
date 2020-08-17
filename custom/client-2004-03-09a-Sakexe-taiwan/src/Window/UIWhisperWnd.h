#pragma once
#include "Struct.h"
#include "Window/UIFrameWnd.h"
class UIBitmapButton;
class UIChatHisBox2;
class UIChatEditCtrl;
struct WhisperWndInfo;


class UIWhisperWnd : public UIFrameWnd
{
public:
	UIWhisperWnd();
	virtual ~UIWhisperWnd();
	virtual void OnCreate(int cx, int cy);
	virtual void OnDraw();
	virtual void OnRBtnUp(int x, int y);
	virtual int SendMsg(UIWindow* sender, int message, int val1, int val2, int val3);
	virtual void StoreInfo();
	virtual void Move(int x, int y);
	void WriteChatToFile();
//	void WriteChatToReportFile();

public:
	/* this+  0 */ //UIFrameWnd baseclass_0;
	/* this+ 96 */ mystd::string m_whisperName;
protected:
	/* this+112 */ UIResizer* m_resizer;
	/* this+116 */ UIChatEditCtrl* m_chatEdit;
	/* this+120 */ UIChatHisBox2* m_listBox;
	/* this+124 */ UIBitmapButton* m_sysButton;
	/* this+128 */ mystd::vector<StringId> m_menuItems;
	/* this+144 */ WhisperWndInfo* m_info;
};
