#pragma once
#include "Window/UIFrameWnd.h"
class UIBarGraph4;
class UIBarGraphPlayerHp;
class UIBarGraphPlayerSp;
class UIBitmapButton;
class UIStaticText;


struct BasicInfoWndInfo
{
	/* this+ 0 */ int x;
	/* this+ 4 */ int y;
	/* this+ 8 */ int w;
	/* this+12 */ int h;
};


class UIBasicInfoWnd : public UIFrameWnd
{
	/* this+  0 */ public: //UIFrameWnd baseclass_0;
	/* this+ 96 */ protected: int field_60_height1; //TODO
	/* this+100 */ protected: int field_64_height2; //TODO
	/* this+104 */ protected: bool bAreButtonsDisplayed;
	/* this+108 */ protected: UIStaticText* m_name;
	/* this+112 */ protected: BasicInfoWndInfo* m_info;
	/* this+116 */ protected: UIBitmapButton* m_buttons[8];
	/* this+148 */ protected: UIBarGraphPlayerHp* m_hpGraph;
	/* this+152 */ protected: UIBarGraphPlayerSp* m_spGraph;
	/* this+156 */ protected: UIBarGraph4* m_expGraph;
	/* this+160 */ protected: UIBarGraph4* m_jobexpGraph;
	/* this+164 */ protected: int field_A4; //TODO

	public: UIBasicInfoWnd::UIBasicInfoWnd(void);
	public: virtual UIBasicInfoWnd::~UIBasicInfoWnd(void);

public:
	static hook_func<UIBasicInfoWnd* (UIBasicInfoWnd::*)(void)> UIBasicInfoWnd::_cUIBasicInfoWnd;
	static hook_func<void (UIBasicInfoWnd::*)(void)> UIBasicInfoWnd::_dUIBasicInfoWnd;
};
C_ASSERT( sizeof UIBasicInfoWnd == 168 );
