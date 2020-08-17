#pragma once
#include "Window/UIFrameWnd.h"
class UIBitmapButton;
class UITextViewer;


class UIWaitWnd : public UIFrameWnd
{
	/* this+  0 */ public: //UIFrameWnd baseclass_0;
	/* this+ 96 */ protected: UITextViewer* m_textViewer;
	/* this+100 */ protected: UIBitmapButton* m_pctrCancel;

	public: void UIWaitWnd::SetMsg(const char* waitMsg, int fontHeight, int fontType);
	//TODO

public:
	static hook_func<void (UIWaitWnd::*)(const char* waitMsg, int fontHeight, int fontType)> UIWaitWnd::_SetMsg;
};
