#include "GameMode.h"
#include "Globals.h"
#include "ModeMgr.h"
#include "MsgStrings.h"
#include "Base/ResMgr.h"
#include "Base/Util.h" // GetNumberText()
#include "Window/UIFrameWnd2.h"
#include "Window/UITextViewer.h"


////////////////////////////////////////


UIWaitWnd::UIWaitWnd(void) // line 486
{
}


UIWaitWnd::~UIWaitWnd(void) // line ???
{
}


hook_method<void (UIWaitWnd::*)(int cx, int cy)> UIWaitWnd::_OnCreate(SAKEXE, "UIWaitWnd::OnCreate");
void UIWaitWnd::OnCreate(int cx, int cy) // line 500
{
	return (this->*_OnCreate)(cx, cy);

	//TODO
}


hook_method<void (UIWaitWnd::*)(void)> UIWaitWnd::_OnDraw(SAKEXE, "UIWaitWnd::OnDraw");
void UIWaitWnd::OnDraw(void) // line 514
{
	return (this->*_OnDraw)();

	//TODO
}


hook_method<int (UIWaitWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UIWaitWnd::_SendMsg(SAKEXE, "UIWaitWnd::SendMsg");
int UIWaitWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3) // line 521
{
	return (this->*_SendMsg)(sender, message, val1, val2, val3);

	//TODO
}


hook_method<void (UIWaitWnd::*)(const char* waitMsg, int fontHeight, int fontType)> UIWaitWnd::_SetMsg(SAKEXE, "UIWaitWnd::SetMsg");
void UIWaitWnd::SetMsg(const char* waitMsg, int fontHeight, int fontType) // line 494
{
	return (this->*_SetMsg)(waitMsg, fontHeight, fontType);

	//TODO
}


////////////////////////////////////////


UILoadingWnd::UILoadingWnd(void) // line 528
{
	m_barGraph = NULL;
}


UILoadingWnd::~UILoadingWnd(void) // line 533
{
}


hook_method<void (UILoadingWnd::*)(int cx, int cy)> UILoadingWnd::_OnCreate(SAKEXE, "UILoadingWnd::OnCreate");
void UILoadingWnd::OnCreate(int cx, int cy) // line 537
{
	return (this->*_OnCreate)(cx, cy);

	//TODO
}


hook_method<void (UILoadingWnd::*)(void)> UILoadingWnd::_OnDraw(SAKEXE, "UILoadingWnd::OnDraw");
void UILoadingWnd::OnDraw(void) // line 599
{
	return (this->*_OnDraw)();

	//TODO
}


hook_method<int (UILoadingWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UILoadingWnd::_SendMsg(SAKEXE, "UILoadingWnd::SendMsg");
int UILoadingWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3) // line 614
{
	return (this->*_SendMsg)(sender, message, val1, val2, val3);

	//TODO
}


hook_method<void (UILoadingWnd::*)(const char* waitMsg, int fontHeight, int fontType)> UILoadingWnd::_SetMsg(SAKEXE, "UILoadingWnd::SetMsg");
void UILoadingWnd::SetMsg(const char* waitMsg, int fontHeight, int fontType) // line 606
{
	return (this->*_SetMsg)(waitMsg, fontHeight, fontType);

	//TODO
}


////////////////////////////////////////


UIBasicInfoWnd::UIBasicInfoWnd(void) // line 636
{
	m_info = 0;
}


UIBasicInfoWnd::~UIBasicInfoWnd(void) // line 641
{
}


hook_method<bool (UIBasicInfoWnd::*)(void)> UIBasicInfoWnd::_IsUpdateNeed(SAKEXE, "UIBasicInfoWnd::IsUpdateNeed");
bool UIBasicInfoWnd::IsUpdateNeed(void) // line 334 (UIFrameWnd.h)
{
	return (this->*_IsUpdateNeed)();

	return true;
}


hook_method<void (UIBasicInfoWnd::*)(int cx, int cy)> UIBasicInfoWnd::_OnCreate(SAKEXE, "UIBasicInfoWnd::OnCreate");
void UIBasicInfoWnd::OnCreate(int cx, int cy) // line 645
{
	return (this->*_OnCreate)(cx, cy);

	//TODO
}


hook_method<void (UIBasicInfoWnd::*)(void)> UIBasicInfoWnd::_OnDraw(SAKEXE, "UIBasicInfoWnd::OnDraw");
void UIBasicInfoWnd::OnDraw(void) // line 766
{
	return (this->*_OnDraw)();

	//TODO
}


hook_method<void (UIBasicInfoWnd::*)(int x, int y)> UIBasicInfoWnd::_OnLBtnDblClk(SAKEXE, "UIBasicInfoWnd::OnLBtnDblClk");
void UIBasicInfoWnd::OnLBtnDblClk(int x, int y) // line 854
{
	return (this->*_OnLBtnDblClk)(x, y);

	//TODO
}


hook_method<void (UIBasicInfoWnd::*)(int x, int y)> UIBasicInfoWnd::_OnMouseHover(SAKEXE, "UIBasicInfoWnd::OnMouseHover");
void UIBasicInfoWnd::OnMouseHover(int x, int y) // line 859
{
	return (this->*_OnMouseHover)(x, y);

	//TODO
}


hook_method<int (UIBasicInfoWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UIBasicInfoWnd::_SendMsg(SAKEXE, "UIBasicInfoWnd::SendMsg");
int UIBasicInfoWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3) // line 885
{
	return (this->*_SendMsg)(sender, message, val1, val2, val3);

	//TODO
}


hook_method<void (UIBasicInfoWnd::*)(void)> UIBasicInfoWnd::_StoreInfo(SAKEXE, "UIBasicInfoWnd::StoreInfo");
void UIBasicInfoWnd::StoreInfo(void) // line 876
{
	return (this->*_StoreInfo)();

	//TODO
}


hook_method<void (UIBasicInfoWnd::*)(int newHeight)> UIBasicInfoWnd::_NewHeight(SAKEXE, "UIBasicInfoWnd::NewHeight");
void UIBasicInfoWnd::NewHeight(int newHeight) // line 720
{
	return (this->*_NewHeight)(newHeight);

	//TODO
}


////////////////////////////////////////


UIToolTipWnd::UIToolTipWnd(void) // line 1010
{
}


UIToolTipWnd::~UIToolTipWnd(void) // line 1014
{
}


hook_method<void (UIToolTipWnd::*)(int cx, int cy)> UIToolTipWnd::_OnCreate(SAKEXE, "UIToolTipWnd::OnCreate");
void UIToolTipWnd::OnCreate(int cx, int cy) // line 1018
{
	return (this->*_OnCreate)(cx, cy);

	//TODO
}


hook_method<void (UIToolTipWnd::*)(void)> UIToolTipWnd::_OnDraw(SAKEXE, "UIToolTipWnd::OnDraw");
void UIToolTipWnd::OnDraw(void) // line 705 (UIFrameWnd.h)
{
	return (this->*_OnDraw)();

	//TODO
}


hook_method<int (UIToolTipWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UIToolTipWnd::_SendMsg(SAKEXE, "UIToolTipWnd::SendMsg");
int UIToolTipWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3) // line 1057
{
	return (this->*_SendMsg)(sender, message, val1, val2, val3);

	//TODO
}


////////////////////////////////////////


UIShortCutWnd::UIShortCutWnd(void) // line 1083
{
	m_slot = -1;
}


UIShortCutWnd::~UIShortCutWnd(void) // line 1088
{
}


hook_method<bool (UIShortCutWnd::*)(void)> UIShortCutWnd::_IsUpdateNeed(SAKEXE, "UIShortCutWnd::IsUpdateNeed");
bool UIShortCutWnd::IsUpdateNeed(void) // line 717 (UIFrameWnd.h)
{
	return (this->*_IsUpdateNeed)();

	return true;
}


hook_method<void (UIShortCutWnd::*)(int cx, int cy)> UIShortCutWnd::_OnCreate(SAKEXE, "UIShortCutWnd::OnCreate");
void UIShortCutWnd::OnCreate(int cx, int cy) // line 1092
{
	return (this->*_OnCreate)(cx, cy);

	int posX[3];
	posX[0] = m_w - 14;
	posX[1] = 0;
	posX[2] = 0;

	const char* buttonName2[8];
	memset(buttonName2, 0, sizeof(buttonName2));
	buttonName2[0] = "close";

	const char* toolTip[8];
	memset(toolTip, 0, sizeof(toolTip));
	toolTip[0] = "F12";

	mystd::string base = "유저인터페이스\\basic_interface\\sys_";
	UIBitmapButton* button = new UIBitmapButton();
	button->UIBitmapButton::SetBitmapName((base + buttonName2[0] + "_off.bmp").c_str(), 0);
	button->UIBitmapButton::SetBitmapName((base + buttonName2[0] + "_on.bmp").c_str(), 1);
	button->UIBitmapButton::SetBitmapName((base + buttonName2[0] + "_on.bmp").c_str(), 2);

	button->UIWindow::Create(button->UIBitmapButton::GetBitmapWidth(), button->UIBitmapButton::GetBitmapHeight());
	button->Move(posX[0], 3);
	button->UIWindow::SetId(111);
	button->UIButton::SetToolTip(toolTip[0]);
	this->UIWindow::AddChild(button);

	for( int i = 0; i < 3 * 9; ++i )
	{
		m_itemIndexOrSkillId[i] = 0;
		m_isSkill[i] = 0;
	}

	this->SendMsg(NULL, UM_REFRESHITEM, 0, 0, 0);
}


hook_method<void (UIShortCutWnd::*)(void)> UIShortCutWnd::_OnDraw(SAKEXE, "UIShortCutWnd::OnDraw");
void UIShortCutWnd::OnDraw(void) // line 1127
{
	return (this->*_OnDraw)();

	CBitmapRes* bmp = (CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp("유저인터페이스\\basic_interface\\shortitem_bg.bmp"));
	this->UIWindow::DrawBitmap(0, 0, bmp, false);

	if( m_slot != -1 )
		this->UIWindow::DrawBox(29 * m_slot + 5, 5, 24, 24, 0x00B4FFB4); // highlight box under cursor (light-green)

	for( int i = 0; i < 9; ++i )
	{
		int slot = i + 9 * g_session.m_shortcutSlotCnt;
	
		if( m_itemIndexOrSkillId[slot] != 0 )
		{
			if( m_isSkill[slot] )
			{
				SKILL_INFO sInfo = g_session.CSession::GetSkillItemInfoBySkillId(m_itemIndexOrSkillId[slot]);

				if( sInfo.m_isValid != 0 )
				{
					char text[1024];
					g_session.CSession::GetSkillBitmapFileName(sInfo.skillName, text);
					CBitmapRes* bmp = (CBitmapRes*)g_resMgr().CResMgr::Get(text);
					this->UIWindow::DrawBitmap(i * 29 + 5, 4, bmp, 1);

					if( m_skillUseLevel[slot] != 0 )
					{// display selected skill level
						sprintf(text, "%d", m_skillUseLevel[slot]);
						this->UIWindow::TextOutA(i * 29 + 20, 19, text, 0, 0, 11, 0x00FFFFFF);
						this->UIWindow::TextOutA(i * 29 + 18, 19, text, 0, 0, 11, 0x00FFFFFF);
						this->UIWindow::TextOutA(i * 29 + 19, 20, text, 0, 0, 11, 0x00FFFFFF);
						this->UIWindow::TextOutA(i * 29 + 19, 18, text, 0, 0, 11, 0x00FFFFFF);
						this->UIWindow::TextOutA(i * 29 + 19, 19, text, 0, 0, 11, 0x00000000);
					}
				}
			}
			else
			{
				ITEM_INFO itemInfo = g_session.CSession::GetItemInfoByIndex(m_itemIndexOrSkillId[slot]);

				if( itemInfo.m_itemIndex != 0 )
					this->UIFrameWnd::DrawItemWithCount(i * 29 + 4, 3, itemInfo, itemInfo.m_isIdentified, true);
			}
		}

		char msg[20];
		sprintf(msg, "%d", g_session.m_shortcutSlotCnt + 1);
		this->UIWindow::TextOutA(m_w - 13, m_h - 16, msg, 0, 0, 12, 0);
	}
}


hook_method<void (UIShortCutWnd::*)(void)> UIShortCutWnd::_OnProcess(SAKEXE, "UIShortCutWnd::OnProcess");
void UIShortCutWnd::OnProcess(void) // line 1280
{
	return (this->*_OnProcess)();

	int slot = this->UIShortCutWnd::GetSlot(g_mouse.CMouse::GetXPos() - m_x, g_mouse.CMouse::GetYPos() - m_y);
	if( slot != m_slot )
	{
		m_slot = slot;
		this->Invalidate();
	}
}


hook_method<void (UIShortCutWnd::*)(int x, int y)> UIShortCutWnd::_OnLBtnDown(SAKEXE, "UIShortCutWnd::OnLBtnDown");
void UIShortCutWnd::OnLBtnDown(int x, int y) // line 1369
{
	return (this->*_OnLBtnDown)(x, y);

	//TODO
}


hook_method<void (UIShortCutWnd::*)(int x, int y)> UIShortCutWnd::_OnRBtnDown(SAKEXE, "UIShortCutWnd::OnRBtnDown");
void UIShortCutWnd::OnRBtnDown(int x, int y) // line 1398
{
	return (this->*_OnRBtnDown)(x, y);

	//TODO
}


hook_method<void (UIShortCutWnd::*)(int x, int y)> UIShortCutWnd::_OnLBtnDblClk(SAKEXE, "UIShortCutWnd::OnLBtnDblClk");
void UIShortCutWnd::OnLBtnDblClk(int x, int y) // line 1434
{
	return (this->*_OnLBtnDblClk)(x, y);

	//TODO
}


hook_method<void (UIShortCutWnd::*)(int x, int y)> UIShortCutWnd::_OnMouseHover(SAKEXE, "UIShortCutWnd::OnMouseHover");
void UIShortCutWnd::OnMouseHover(int x, int y) // line 1230
{
	return (this->*_OnMouseHover)(x, y);

	//TODO
}


hook_method<int (UIShortCutWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UIShortCutWnd::_SendMsg(SAKEXE, "UIShortCutWnd::SendMsg");
int UIShortCutWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3) // line 1441
{
	return (this->*_SendMsg)(sender, message, val1, val2, val3);

	switch( message )
	{
	case UM_USE_SHORTEN_ITEM:
	{
		int col = val1;
		int row = g_session.m_shortcutSlotCnt;
		if( g_session.m_isBattle && val2 != 0 )
			row = val2;
		int pos = col + 9 * row;

		if( !m_isSkill[pos] )
		{// item
			if( m_itemIndexOrSkillId[pos] == 0 )
				break;

			ITEM_INFO itemInfo = g_session.CSession::GetItemInfoByIndex(m_itemIndexOrSkillId[pos]);
			if( itemInfo.m_itemIndex == 0 )
				break;

			CGameMode* mode = g_modeMgr.CModeMgr::GetGameMode();
			if( itemInfo.m_itemType >= 0 )
			{
				if( itemInfo.m_itemType <= 2 )
				{
					mode->SendMsg(29, itemInfo.m_itemIndex, 0, 0);
					break;
				}

				if( itemInfo.m_itemType == 10 )
				{
					if ( itemInfo.m_wearLocation == 0x8000 )
					{
						mode->SendMsg(21, 15, 0, 0);
						mode->SendMsg(100, itemInfo.m_itemIndex, itemInfo.m_location, 0);
					}
					break;
				}
			}

			if( itemInfo.m_location != 0 && itemInfo.m_wearLocation == 0 && itemInfo.m_isIdentified )
				mode->SendMsg(20, itemInfo.m_itemIndex, itemInfo.m_location, 0);
		}
		else
		{// skill
			SKILL_INFO skillInfo = g_session.CSession::GetSkillItemInfoBySkillId(m_itemIndexOrSkillId[pos]);
			if( skillInfo.level != 0 && skillInfo.m_isValid )
				g_modeMgr.CModeMgr::GetCurMode()->SendMsg(MM_USING_SKILL, (int)&skillInfo, m_skillUseLevel[pos], 0);
		}
	}
	break;
	case UM_SETINFO:
	{
		m_info = (ShortCutWndInfo*)val1;
		if( !m_info->ShortCutWndInfo::IsValidInfo() )
			m_info->ShortCutWndInfo::MakeDefault();
		this->SendMsg(NULL, UM_REFRESHITEM, 0, 0, 0);
		this->Move(m_info->x, m_info->y);
	}
	break;
	case UM_REFRESHITEM:
	{
		for( int i = 0; i < 3 * 9; ++i )
		{
			m_itemIndexOrSkillId[i] = 0;
			m_isSkill[i] = 0;
			m_skillUseLevel[i] = 0;
		}

		int numItem = g_session.CSession::GetNumItem();
		for( int g = 0; g < 3 * 9; ++g )
		{
			mystd::string sItemName = g_session.CSession::GetShortenItemName(g);
			if( sItemName == "nothing" )
				continue;

			int i;
			for( i = 0; i < numItem; ++i )
			{// try item
				ITEM_INFO itemInfo = g_session.CSession::GetItemInfoBySequence(i);
				if( itemInfo.m_itemIndex != 0 && itemInfo.m_itemName == sItemName && itemInfo.m_isIdentified )
				{
					m_itemIndexOrSkillId[g] = itemInfo.m_itemIndex;
//					m_isSkill[g] = 0;
//					m_skillUseLevel[g] = 0;
					break; // found
				}
			}

			if( i == numItem && sItemName.size() > 3 && sItemName[0] == '#' && sItemName[1] == '#' )
			{// try skill
				SKILL_INFO sInfo = g_session.CSession::GetSkillItemInfoByName(sItemName.c_str() + 2);
				if( sInfo.m_isValid != 0 && sInfo.level != 0 && sInfo.spcost != 0 )
				{
					m_itemIndexOrSkillId[g] = sInfo.SKID;
					m_isSkill[g] = 1;
					m_skillUseLevel[g] = g_session.CSession::GetShortenSkillUseLevel(g);
				}
			}
		}

		this->Invalidate();
	}
	break;
	case UM_COMMAND:
	{
		if( val1 == 111 )
			g_windowMgr.UIWindowMgr::ShowWindow(WID_SHORTCUTWND, 0);
	}
	break;
	default:
		return this->UIFrameWnd::SendMsg(sender, message, val1, val2, val3);
	}

	return 0;
}


hook_method<void (UIShortCutWnd::*)(int x, int y, const DRAG_INFO* const dragInfo)> UIShortCutWnd::_DragAndDrop(SAKEXE, "UIShortCutWnd::DragAndDrop");
void UIShortCutWnd::DragAndDrop(int x, int y, const DRAG_INFO* const dragInfo) // line 1291
{
	return (this->*_DragAndDrop)(x, y, dragInfo);

	//TODO
}


hook_method<void (UIShortCutWnd::*)(void)> UIShortCutWnd::_StoreInfo(SAKEXE, "UIShortCutWnd::StoreInfo");
void UIShortCutWnd::StoreInfo(void) // line 1425
{
	return (this->*_StoreInfo)();

	if( m_info != NULL )
	{
		m_info->x = m_x;
		m_info->y = m_y;
		m_info->w = m_w;
		m_info->h = m_h;
	}
}


hook_method<void (UIShortCutWnd::*)(int visible)> UIShortCutWnd::_SetShow(SAKEXE, "UIShortCutWnd::SetShow");
void UIShortCutWnd::SetShow(int visible) // line 1653
{
	return (this->*_SetShow)(visible);

	//TODO
}


hook_method<int (UIShortCutWnd::*)(int x, int y)> UIShortCutWnd::_GetSlot(SAKEXE, "UIShortCutWnd::GetSlot");
int UIShortCutWnd::GetSlot(int x, int y) // line 1665
{
	return (this->*_GetSlot)(x, y);

	//TODO
}


////////////////////////////////////////


UIStatusWnd::UIStatusWnd(void) // line 2381
{
	m_state = 0;
	m_info = NULL;
}


UIStatusWnd::~UIStatusWnd(void) // line 2387
{
}


hook_method<bool (UIStatusWnd::*)(void)> UIStatusWnd::_IsUpdateNeed(SAKEXE, "UIStatusWnd::IsUpdateNeed");
bool UIStatusWnd::IsUpdateNeed(void) // line 913 (UIFrameWnd.h)
{
	return (this->*_IsUpdateNeed)();

	//TODO
}


hook_method<void (UIStatusWnd::*)(int cx, int cy)> UIStatusWnd::_OnCreate(SAKEXE, "UIStatusWnd::OnCreate");
void UIStatusWnd::OnCreate(int cx, int cy) // line 2391
{
	return (this->*_OnCreate)(cx, cy);

	//TODO
}


hook_method<void (UIStatusWnd::*)(void)> UIStatusWnd::_OnDraw(SAKEXE, "UIStatusWnd::OnDraw");
void UIStatusWnd::OnDraw(void) // line 2518
{
	return (this->*_OnDraw)();

	//TODO
}


hook_method<void (UIStatusWnd::*)(int x, int y)> UIStatusWnd::_OnLBtnDblClk(SAKEXE, "UIStatusWnd::OnLBtnDblClk");
void UIStatusWnd::OnLBtnDblClk(int x, int y) // line 2444
{
	return (this->*_OnLBtnDblClk)(x, y);

	//TODO
}


hook_method<void (UIStatusWnd::*)(int x, int y)> UIStatusWnd::_OnLBtnDown(SAKEXE, "UIStatusWnd::OnLBtnDown");
void UIStatusWnd::OnLBtnDown(int x, int y) // line 2450
{
	return (this->*_OnLBtnDown)(x, y);

	//TODO
}


hook_method<void (UIStatusWnd::*)(int x, int y)> UIStatusWnd::_OnMouseHover(SAKEXE, "UIStatusWnd::OnMouseHover");
void UIStatusWnd::OnMouseHover(int x, int y) // line 2465
{
	return (this->*_OnMouseHover)(x, y);

	//TODO
}


hook_method<int (UIStatusWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UIStatusWnd::_SendMsg(SAKEXE, "UIStatusWnd::SendMsg");
int UIStatusWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3) // line 2620
{
	return (this->*_SendMsg)(sender, message, val1, val2, val3);

	//TODO
}


hook_method<void (UIStatusWnd::*)(void)> UIStatusWnd::_StoreInfo(SAKEXE, "UIStatusWnd::StoreInfo");
void UIStatusWnd::StoreInfo(void) // line 2610
{
	return (this->*_StoreInfo)();

	//TODO
}


hook_method<void (UIStatusWnd::*)(int state)> UIStatusWnd::_ChangeState(SAKEXE, "UIStatusWnd::ChangeState");
void UIStatusWnd::ChangeState(int state) // line 2426
{
	return (this->*_ChangeState)(state);

	//TODO
}


////////////////////////////////////////


UIOptionWnd::UIOptionWnd(void) // line 3029
{
	m_info = NULL;
}


UIOptionWnd::~UIOptionWnd(void) // line 3034
{
}


hook_method<void (UIOptionWnd::*)(int cx, int cy)> UIOptionWnd::_OnCreate(SAKEXE, "UIOptionWnd::OnCreate");
void UIOptionWnd::OnCreate(int cx, int cy) // line 3038
{
	return (this->*_OnCreate)(cx, cy);

	//TODO
}


hook_method<void (UIOptionWnd::*)(void)> UIOptionWnd::_OnDraw(SAKEXE, "UIOptionWnd::OnDraw");
void UIOptionWnd::OnDraw(void) // line 3174
{
	return (this->*_OnDraw)();

	//TODO
}


hook_method<void (UIOptionWnd::*)(int x, int y)> UIOptionWnd::_OnLBtnDblClk(SAKEXE, "UIOptionWnd::OnLBtnDblClk");
void UIOptionWnd::OnLBtnDblClk(int x, int y) // line 3142
{
	return (this->*_OnLBtnDblClk)(x, y);

	//TODO
}


hook_method<void (UIOptionWnd::*)(int x, int y)> UIOptionWnd::_OnLBtnDown(SAKEXE, "UIOptionWnd::OnLBtnDown");
void UIOptionWnd::OnLBtnDown(int x, int y) // line 3148
{
	return (this->*_OnLBtnDown)(x, y);

	//TODO
}


hook_method<int (UIOptionWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UIOptionWnd::_SendMsg(SAKEXE, "UIOptionWnd::SendMsg");
int UIOptionWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3) // line 3208
{
	return (this->*_SendMsg)(sender, message, val1, val2, val3);

	//TODO
}


hook_method<void (UIOptionWnd::*)(void)> UIOptionWnd::_StoreInfo(SAKEXE, "UIOptionWnd::StoreInfo");
void UIOptionWnd::StoreInfo(void) // line 3198
{
	return (this->*_StoreInfo)();

	//TODO
}


////////////////////////////////////////


UINotifyItemObtainWnd::UINotifyItemObtainWnd(void) // line 3599
{
	m_isIdentified = false;
}


UINotifyItemObtainWnd::~UINotifyItemObtainWnd(void) // line 3604
{
}


hook_method<void (UINotifyItemObtainWnd::*)(int cx, int cy)> UINotifyItemObtainWnd::_OnCreate(SAKEXE, "UINotifyItemObtainWnd::OnCreate");
void UINotifyItemObtainWnd::OnCreate(int cx, int cy) // line 3609
{
	return (this->*_OnCreate)(cx, cy);

	;
}


hook_method<void (UINotifyItemObtainWnd::*)(void)> UINotifyItemObtainWnd::_OnDraw(SAKEXE, "UINotifyItemObtainWnd::OnDraw");
void UINotifyItemObtainWnd::OnDraw(void) // line 3618
{
	return (this->*_OnDraw)();

	//TODO
}


hook_method<int (UINotifyItemObtainWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UINotifyItemObtainWnd::_SendMsg(SAKEXE, "UINotifyItemObtainWnd::SendMsg");
int UINotifyItemObtainWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3) // line 3631
{
	return (this->*_SendMsg)(sender, message, val1, val2, val3);

	switch( message )
	{
	case 34:
		m_itemInfo = *(ITEM_INFO*)val1;
		return 0;

	case 36:
	{
		int ismoney = (int)val1;
		int number = (int)val2;
		const char* name = (const char*)val3;

		m_isMoney = ismoney;
		if( ismoney )
		{
			char buf[24];
			GetNumberText(number, buf);

			char Dest[128];
			sprintf(Dest, MsgStr(MSI_GET_ZENY), buf);

			m_message = Dest;
			m_itemName = "";
		}
		else
		{
			ITEM_INFO iteminfo;
			iteminfo.m_itemName = name;
			iteminfo.m_isIdentified = m_isIdentified;
			iteminfo.m_refiningLevel = 0;
			
			char itemName[128];
			iteminfo.ITEM_INFO::GetItemName(itemName);

			char Dest[128];
			sprintf(Dest, MsgStr(MSI_GET_ITEM), itemName, number);

			m_message = Dest;
			m_itemName = name;
		}

		int textwidth = this->UIWindow::GetTextWidth(m_message.c_str(), 0, 0, 12, 0);
		int w = ((textwidth + 54) % 28 != 0 ? 28 : 0) + 28 * (textwidth + 54) / 28;
		if( w < 34 )
			w = 34;

		if( w != m_w )
			this->Resize(w, m_h);

		this->Invalidate();
		m_madeTick = timeGetTime();
		return 0;
	}

	case 76:
		m_isIdentified = ( val1 != 0 );
		return 0;

	default:
		return this->UIFrameWnd::SendMsg(sender, message, val1, val2, val3);
	}
}


hook_method<void (UINotifyItemObtainWnd::*)(void)> UINotifyItemObtainWnd::_OnProcess(SAKEXE, "UINotifyItemObtainWnd::OnProcess");
void UINotifyItemObtainWnd::OnProcess(void) // line 3612
{
	return (this->*_OnProcess)();

	if( timeGetTime() > m_madeTick + 5000 )
		g_windowMgr.UIWindowMgr::DeleteWindow(WID_NOTIFYITEMOBTAINWND);
}


hook_method<bool (UINotifyItemObtainWnd::*)(void)> UINotifyItemObtainWnd::_ShouldDoHitTest(SAKEXE, "UINotifyItemObtainWnd::ShouldDoHitTest");
bool UINotifyItemObtainWnd::ShouldDoHitTest(void) // line 875 (UIFrameWnd.h)
{
	return (this->*_ShouldDoHitTest)();

	return false;
}


////////////////////////////////////////


UISayDialogWnd::UISayDialogWnd(void) // line 4125
{
	m_textViewer = NULL;
	m_info = NULL;
}


UISayDialogWnd::~UISayDialogWnd(void) // line 4131
{
}


hook_method<void (UISayDialogWnd::*)(int cx, int cy)> UISayDialogWnd::_OnCreate(SAKEXE, "UISayDialogWnd::OnCreate");
void UISayDialogWnd::OnCreate(int cx, int cy) // line 4135
{
	return (this->*_OnCreate)(cx, cy);

	//TODO
}


hook_method<void (UISayDialogWnd::*)(void)> UISayDialogWnd::_OnDraw(SAKEXE, "UISayDialogWnd::OnDraw");
void UISayDialogWnd::OnDraw(void) // line 1068 (UIFrameWnd.h)
{
	return (this->*_OnDraw)();

	//TODO
}


hook_method<int (UISayDialogWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UISayDialogWnd::_SendMsg(SAKEXE, "UISayDialogWnd::SendMsg");
int UISayDialogWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3) // line 4163
{
	return (this->*_SendMsg)(sender, message, val1, val2, val3);

	//TODO
}


hook_method<void (UISayDialogWnd::*)(void)> UISayDialogWnd::_StoreInfo(SAKEXE, "UISayDialogWnd::StoreInfo");
void UISayDialogWnd::StoreInfo(void) // line 4147
{
	return (this->*_StoreInfo)();

	//TODO
}


hook_method<void (UISayDialogWnd::*)(int cx, int cy)> UISayDialogWnd::_Resize(SAKEXE, "UISayDialogWnd::Resize");
void UISayDialogWnd::Resize(int cx, int cy) // line 4155
{
	return (this->*_Resize)(cx, cy);

	//TODO
}


hook_method<int (UISayDialogWnd::*)(int buttonSize)> UISayDialogWnd::_GetButtonOffset(SAKEXE, "UISayDialogWnd::GetButtonOffset");
int UISayDialogWnd::GetButtonOffset(int buttonSize) // line 4274
{
	return (this->*_GetButtonOffset)(buttonSize);

	//TODO
}


////////////////////////////////////////


UIItemCollectionWnd::UIItemCollectionWnd() // line 4289-4299
{
	m_info = NULL;
	memset(&m_itemInfo, 0, sizeof(m_itemInfo));
	m_petLevel = -1;
	m_petFullness = -1;
	m_petRelationship = -1;
	m_petITID = -1;
	m_isPetNameModified = 0;
}


UIItemCollectionWnd::~UIItemCollectionWnd() // line 4302-4303
{
}


void UIItemCollectionWnd::OnCreate(int cx, int cy) // line 4306-4350
{
	m_windowId = WID_ITEMCOLLECTIONWND;
	int posX[3] = { m_w - 14, 0, 0 };
//	int ids2[3];

	m_textViewer = new UITextViewer();
	m_textViewer->Create2(91, 31, cx - 98, cy - 40, false);
	unsigned long rr, gg, bb;
	g_skinMgr.CSkinMgr::GetColorChipColor(2, 2, rr, gg, bb);
	m_textViewer->m_bgR = rr;
	m_textViewer->m_bgG = gg;
	m_textViewer->m_bgB = bb;
	this->UIWindow::AddChild(m_textViewer);

	mystd::string preBmpName2 = "유저인터페이스\\basic_interface\\sys_";
	UIBitmapButton* closeButton = new UIBitmapButton();
	closeButton->UIBitmapButton::SetBitmapName((preBmpName2 + "close" + "_off.bmp").c_str(), 0);
	closeButton->UIBitmapButton::SetBitmapName((preBmpName2 + "close" + "_on.bmp").c_str(), 1);
	closeButton->UIBitmapButton::SetBitmapName((preBmpName2 + "close" + "_on.bmp").c_str(), 2);
	closeButton->UIWindow::Create(closeButton->UIBitmapButton::GetBitmapWidth(), closeButton->UIBitmapButton::GetBitmapHeight());
	closeButton->Move(posX[0], 3);
	closeButton->UIWindow::SetId(ID_CLOSE);
	closeButton->UIButton::SetToolTip("ESC");
	this->UIWindow::AddChild(closeButton);

	mystd::string pathName = "유저인터페이스\\";
	m_cardItemButton = new UIBitmapButton();
	m_cardItemButton->UIBitmapButton::SetBitmapName((pathName + "btn_view" + ".bmp").c_str(), 0);
	m_cardItemButton->UIBitmapButton::SetBitmapName((pathName + "btn_view_a" + ".bmp").c_str(), 1);
	m_cardItemButton->UIBitmapButton::SetBitmapName((pathName + "btn_view_b" + ".bmp").c_str(), 2);
	m_cardItemButton->UIWindow::Create(m_cardItemButton->UIBitmapButton::GetBitmapWidth(), m_cardItemButton->UIBitmapButton::GetBitmapHeight());
	m_cardItemButton->Move(6, 6);
	m_cardItemButton->UIWindow::SetId(ID_CARDITEM);
	this->UIWindow::AddChild(m_cardItemButton);
}


void UIItemCollectionWnd::OnDraw(void) // line 4353-4390
{
	this->UIWindow::ClearDC(0xFFFF00FF);

	CBitmapRes* bgBitmapRes = (CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp("유저인터페이스\\basic_interface\\collection_bg.bmp"));
	this->UIWindow::DrawBitmap(0, 0, bgBitmapRes, true);

	if( m_itemBmp.size() != 0 )
	{
		CBitmapRes* itemBitmapRes = (CBitmapRes*)g_resMgr().CResMgr::Get(m_itemBmp.c_str());
		this->UIWindow::DrawBitmap(10, 11, itemBitmapRes, true);
	}

	COLORREF textColor = ( m_itemInfo.m_isIdentified ) ? 0x000000 : 0x808080;
	this->UIFrameWnd::DrawItemText(90, 10, m_itemInfo, textColor, 0, 12);

	if( m_h <= 120 )
		return; // done.

	// optional card slot section

	this->UIFrameWnd::DrawLatticeFrame(0, 120, m_w, 29);

	if( m_itemInfo.m_slot[0] == 0 || ITEM_INFO::IsCardItem(m_itemInfo.m_slot[0]) )
	{
		for( int i = 0; i < m_itemInfo.ITEM_INFO::GetSlotCount(); ++i )
		{
			if( m_itemInfo.m_slot[i] != 0 )
			{
				char itemName[16];
				itoa(m_itemInfo.m_slot[i], itemName, 10);
				this->UIFrameWnd::DrawItem(4 + 25 * i, m_h - 26, itemName, false);
			}
			else
			{
				CBitmapRes* slotBitmapRes = (CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp("유저인터페이스\\empty_card_slot.bmp"));
				this->UIWindow::DrawBitmap(4 + 25 * i, m_h - 26, slotBitmapRes, true);
			}
		}
	}
}


hook_method<void (UIItemCollectionWnd::*)(int x, int y)> UIItemCollectionWnd::_OnMouseHover(SAKEXE, "UIItemCollectionWnd::OnMouseHover");
void UIItemCollectionWnd::OnMouseHover(int x, int y) // line 4435
{
	return (this->*_OnMouseHover)(x, y);

	//TODO
}


hook_method<void (UIItemCollectionWnd::*)(int x, int y)> UIItemCollectionWnd::_OnRBtnDown(SAKEXE, "UIItemCollectionWnd::OnRBtnDown");
void UIItemCollectionWnd::OnRBtnDown(int x, int y) // line 4415
{
	return (this->*_OnRBtnDown)(x, y);

	//TODO
}


hook_method<int (UIItemCollectionWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UIItemCollectionWnd::_SendMsg(SAKEXE, "UIItemCollectionWnd::SendMsg");
int UIItemCollectionWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3) // line 4462
{
	return (this->*_SendMsg)(sender, message, val1, val2, val3);

	//TODO
}


hook_method<void (UIItemCollectionWnd::*)(void)> UIItemCollectionWnd::_StoreInfo(SAKEXE, "UIItemCollectionWnd::StoreInfo");
void UIItemCollectionWnd::StoreInfo(void) // line 4453
{
	return (this->*_StoreInfo)();

	//TODO
}


hook_method<int (UIItemCollectionWnd::*)(int x, int y, int& gx, int& gy)> UIItemCollectionWnd::_GetCardSlotNum(SAKEXE, "UIItemCollectionWnd::GetCardSlotNum");
int UIItemCollectionWnd::GetCardSlotNum(int x, int y, int& gx, int& gy) // line 4393
{
	return (this->*_GetCardSlotNum)(x, y, gx, gy);

	//TODO
}


hook_method<bool (UIItemCollectionWnd::*)(const ITEM_INFO& item_info)> UIItemCollectionWnd::_IsSameCollectionDisplayParameters(SAKEXE, "UIItemCollectionWnd::IsSameCollectionDisplayParameters");
bool UIItemCollectionWnd::IsSameCollectionDisplayParameters(const ITEM_INFO& item_info) // line 4602
{
	return (this->*_IsSameCollectionDisplayParameters)(item_info);

	//TODO
}


////////////////////////////////////////


UIChooseWarpWnd::UIChooseWarpWnd(void) // line 4875
{
	m_mapNameList.reserve(3);
}


UIChooseWarpWnd::~UIChooseWarpWnd(void) // line 4880
{
}


hook_method<void (UIChooseWarpWnd::*)(int cx, int cy)> UIChooseWarpWnd::_OnCreate(SAKEXE, "UIChooseWarpWnd::OnCreate");
void UIChooseWarpWnd::OnCreate(int cx, int cy) // line 4884
{
	return (this->*_OnCreate)(cx, cy);

	//TODO
}


hook_method<void (UIChooseWarpWnd::*)(void)> UIChooseWarpWnd::_OnDraw(SAKEXE, "UIChooseWarpWnd::OnDraw");
void UIChooseWarpWnd::OnDraw(void) // line 1110 (UIFrameWnd.h)
{
	return (this->*_OnDraw)();

	this->UIFrameWnd::DrawLatticeFrame(0, 0, 0, 0);
}


hook_method<int (UIChooseWarpWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UIChooseWarpWnd::_SendMsg(SAKEXE, "UIChooseWarpWnd::SendMsg");
int UIChooseWarpWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3) // line 4933
{
	return (this->*_SendMsg)(sender, message, val1, val2, val3);

	switch( message )
	{
	case 18:
		m_choostList->SendMsg(NULL, 18, 0, 0, 0);
	break;
	case 19:
		m_choostList->SendMsg(NULL, 19, 0, 0, 0);
	break;
	case 6:
		if( val1 == 94 )
		{
			if( m_choostList->UIListBox::GetSelected() == -1 )
				break;
			g_modeMgr.CModeMgr::GetGameMode()->SendMsg(82, (int)m_mapNameList[m_choostList->UIListBox::GetSelected()].c_str(), m_skid, 0);
			g_windowMgr.UIWindowMgr::DeleteWindow(WID_CHOOSEWARPWND);
		}
		else
		if( val1 == 95 )
		{
			g_modeMgr.CModeMgr::GetGameMode()->SendMsg(82, (int)"cancel", m_skid, 0);
			g_windowMgr.UIWindowMgr::DeleteWindow(WID_CHOOSEWARPWND);
		}
	break;
	case 27:
	{
		const char* mapname = (const char*)val1;
		if( mapname == NULL )
			break;

		const char* text = ( mystd::string(mapname) == "Random" ) ? MsgStr(MSI_RANDOM_POS)
		                 : ( mystd::string(mapname) == "cancel" ) ? MsgStr(MSI_CANCEL)
		                 : g_session.CSession::GetMapName(g_session.CSession::GatName2RswName(mapname));

		m_choostList->AddItem(text);
		m_mapNameList.push_back(mapname);
	}
	break;
	case 59:
		m_skid = val1;
		break;
	default:
		return this->UIFrameWnd::SendMsg(sender, message, val1, val2, val3);
	}

	return 0;
}


////////////////////////////////////////


UIQuitWnd::UIQuitWnd(void) // line 5618
{
}


UIQuitWnd::~UIQuitWnd(void) // line 5622
{
}


hook_method<void (UIQuitWnd::*)(int cx, int cy)> UIQuitWnd::_OnCreate(SAKEXE, "UIQuitWnd::OnCreate");
void UIQuitWnd::OnCreate(int cx, int cy) // line 5626
{
	return (this->*_OnCreate)(cx, cy);

	//TODO
}


hook_method<void (UIQuitWnd::*)(void)> UIQuitWnd::_OnDraw(SAKEXE, "UIQuitWnd::OnDraw");
void UIQuitWnd::OnDraw(void) // line 5654
{
	return (this->*_OnDraw)();

	//TODO
}


hook_method<int (UIQuitWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UIQuitWnd::_SendMsg(SAKEXE, "UIQuitWnd::SendMsg");
int UIQuitWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3) // line 5660
{
	return (this->*_SendMsg)(sender, message, val1, val2, val3);

	//TODO
}


////////////////////////////////////////


UIExchangeWnd::UIExchangeWnd(void) // line 7063
{
}


////////////////////////////////////////


UIMinimapZoomWnd::UIMinimapZoomWnd(void) // line 1568 (Window/UIFrameWnd.h)
{
}


UIMinimapZoomWnd::~UIMinimapZoomWnd(void) // line 1569 (Window/UIFrameWnd.h)
{
}


hook_method<void (UIMinimapZoomWnd::*)(int cx, int cy)> UIMinimapZoomWnd::_OnCreate(SAKEXE, "UIMinimapZoomWnd::OnCreate");
void UIMinimapZoomWnd::OnCreate(int cx, int cy) // line 8236
{
	return (this->*_OnCreate)(cx, cy);

	//TODO
}


hook_method<void (UIMinimapZoomWnd::*)(void)> UIMinimapZoomWnd::_OnDraw(SAKEXE, "UIMinimapZoomWnd::OnDraw");
void UIMinimapZoomWnd::OnDraw(void) // line 8255
{
	return (this->*_OnDraw)();

	;
}


hook_method<int (UIMinimapZoomWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UIMinimapZoomWnd::_SendMsg(SAKEXE, "UIMinimapZoomWnd::SendMsg");
int UIMinimapZoomWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3) // line 8258
{
	return (this->*_SendMsg)(sender, message, val1, val2, val3);

	//TODO
}


////////////////////////////////////////


UIPartySettingWnd::UIPartySettingWnd(void) // line 7537
{
	m_nYOffset = 0;
	m_info = NULL;
}


UIPartySettingWnd::~UIPartySettingWnd(void) // line 7543
{
}


hook_method<void (UIPartySettingWnd::*)(int cx, int cy)> UIPartySettingWnd::_OnCreate(SAKEXE, "UIPartySettingWnd::OnCreate");
void UIPartySettingWnd::OnCreate(int cx, int cy) // line 7547
{
	return (this->*_OnCreate)(cx, cy);

	//TODO
}


hook_method<void (UIPartySettingWnd::*)(void)> UIPartySettingWnd::_OnDraw(SAKEXE, "UIPartySettingWnd::OnDraw");
void UIPartySettingWnd::OnDraw(void) // line 7686
{
	return (this->*_OnDraw)();

	//TODO
}


hook_method<void (UIPartySettingWnd::*)(int x, int y)> UIPartySettingWnd::_OnLBtnDown(SAKEXE, "UIPartySettingWnd::OnLBtnDown");
void UIPartySettingWnd::OnLBtnDown(int x, int y) // line 7754
{
	return (this->*_OnLBtnDown)(x, y);

	//TODO
}


hook_method<int (UIPartySettingWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UIPartySettingWnd::_SendMsg(SAKEXE, "UIPartySettingWnd::SendMsg");
int UIPartySettingWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3) // line 7772
{
	return (this->*_SendMsg)(sender, message, val1, val2, val3);

	//TODO
}


hook_method<void (UIPartySettingWnd::*)(void)> UIPartySettingWnd::_StoreInfo(SAKEXE, "UIPartySettingWnd::StoreInfo");
void UIPartySettingWnd::StoreInfo(void) // line 7763
{
	return (this->*_StoreInfo)();

	//TODO
}


hook_val< const bool > UIPartySettingWnd::s_bUseNewPacket(SAKEXE, "UIPartySettingWnd::s_bUseNewPacket"); // = false;


////////////////////////////////////////


UIMenuWnd::UIMenuWnd(void) // line 8371
{
	m_callerWid = WID_LAST;
	m_menuItemSpacing = 14;
	m_curMenuIndex = -1;
}


UIMenuWnd::~UIMenuWnd(void) // line 8378
{
}


hook_method<void (UIMenuWnd::*)(int cx, int cy)> UIMenuWnd::_OnCreate(SAKEXE, "UIMenuWnd::OnCreate");
void UIMenuWnd::OnCreate(int cx, int cy) // line 8383
{
	return (this->*_OnCreate)(cx, cy);

	;
}


hook_method<void (UIMenuWnd::*)(int x, int y)> UIMenuWnd::_OnLBtnUp(SAKEXE, "UIMenuWnd::OnLBtnUp");
void UIMenuWnd::OnLBtnUp(int x, int y) // line 8386
{
	return (this->*_OnLBtnUp)(x, y);

	//TODO
}


hook_method<void (UIMenuWnd::*)(void)> UIMenuWnd::_OnDraw(SAKEXE, "UIMenuWnd::OnDraw");
void UIMenuWnd::OnDraw(void) // line 8449
{
	return (this->*_OnDraw)();

	//TODO
}


hook_method<void (UIMenuWnd::*)(int x, int y)> UIMenuWnd::_OnMouseMove(SAKEXE, "UIMenuWnd::OnMouseMove");
void UIMenuWnd::OnMouseMove(int x, int y) // line 8513
{
	return (this->*_OnMouseMove)(x, y);

	//TODO
}


hook_method<void (UIMenuWnd::*)(int x, int y)> UIMenuWnd::_OnMouseHover(SAKEXE, "UIMenuWnd::OnMouseHover");
void UIMenuWnd::OnMouseHover(int x, int y) // line 8518
{
	return (this->*_OnMouseHover)(x, y);

	//TODO
}


hook_method<int (UIMenuWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UIMenuWnd::_SendMsg(SAKEXE, "UIMenuWnd::SendMsg");
int UIMenuWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3) // line 8540
{
	return (this->*_SendMsg)(sender, message, val1, val2, val3);

	switch( message )
	{
	case 72:
		this->UIMenuWnd::AddMenu(boundaryText);
		this->Invalidate();
	break;
	case 31:
	{
		const char* menuString = (const char*)val1;

		this->UIMenuWnd::AddMenu(menuString);
		this->UIMenuWnd::AddMenu(menuString);
		this->Invalidate();
	}
	break;
	case 83:
	{
		enum WINDOWID wid = (enum WINDOWID)val1;

		m_callerWid = wid;
	}
	break;
	case 30:
	{
		size_t count = m_menuItems.size();
		int width = 20;

		for( size_t i = 0; i < count; ++i )
			if( width <= this->UIWindow::GetTextWidth(m_menuItems[i].c_str(), 0, 0, 12, false) )
				width = this->UIWindow::GetTextWidth(m_menuItems[i].c_str(), 0, 0, 12, false);

		this->Resize(6 + width, count * m_menuItemSpacing / 2);
		this->Invalidate();
	}
	break;
	default:
		return this->UIWindow::SendMsg(sender, message, val1, val2, val3);
	}

	return 0;
}


hook_method<void (UIMenuWnd::*)(int x, int y)> UIMenuWnd::_Move(SAKEXE, "UIMenuWnd::Move");
void UIMenuWnd::Move(int x, int y) // line 8526
{
	return (this->*_Move)(x, y);

	//TODO
}


hook_method<void (UIMenuWnd::*)(const char* menuString)> UIMenuWnd::_AddMenu(SAKEXE, "UIMenuWnd::AddMenu");
void UIMenuWnd::AddMenu(const char* menuString) // line 8535
{
	return (this->*_AddMenu)(menuString);

	m_menuItems.push_back(menuString);
}


hook_method<int (UIMenuWnd::*)(int x, int y)> UIMenuWnd::_GetMenuIndex(SAKEXE, "UIMenuWnd::GetMenuIndex");
int UIMenuWnd::GetMenuIndex(int x, int y) // line 8411
{
	return (this->*_GetMenuIndex)(x, y);

	if( x < 0 || x >= m_w || y < 0 || y >= m_h )
		return -1;

	int index = y / (m_menuItemSpacing / 2);

	if( index < 0 )
		index = 0;

	if( index > (int)m_menuItems.size() - 1 )
		index = (int)m_menuItems.size() - 1;

	return index;
}


hook_method<int (UIMenuWnd::*)(int seq)> UIMenuWnd::_GetNumBoundary(SAKEXE, "UIMenuWnd::GetNumBoundary");
int UIMenuWnd::GetNumBoundary(int seq) // line 8424
{
	return (this->*_GetNumBoundary)(seq);

	//TODO
}


hook_method<int (UIMenuWnd::*)(int curItem)> UIMenuWnd::_IsBoundary(SAKEXE, "UIMenuWnd::IsBoundary");
int UIMenuWnd::IsBoundary(int curItem) // line 8442
{
	return (this->*_IsBoundary)(curItem);

	//TODO
}


////////////////////////////////////////


UIProhibitListWnd::UIProhibitListWnd(void) // line 9793
{
	m_oldLogCnt = 0;
}


UIProhibitListWnd::~UIProhibitListWnd(void) // line 9798
{
}


hook_method<void (UIProhibitListWnd::*)(int cx, int cy)> UIProhibitListWnd::_OnCreate(SAKEXE, "UIProhibitListWnd::OnCreate");
void UIProhibitListWnd::OnCreate(int cx, int cy) // line 9802
{
	return (this->*_OnCreate)(cx, cy);

	//TODO
}


hook_method<void (UIProhibitListWnd::*)(void)> UIProhibitListWnd::_OnDraw(SAKEXE, "UIProhibitListWnd::OnDraw");
void UIProhibitListWnd::OnDraw(void) // line 9852
{
	return (this->*_OnDraw)();

	//TODO
}


hook_method<void (UIProhibitListWnd::*)(void)> UIProhibitListWnd::_OnProcess(SAKEXE, "UIProhibitListWnd::OnProcess");
void UIProhibitListWnd::OnProcess(void) // line 9844
{
	return (this->*_OnProcess)();

	//TODO
}


hook_method<int (UIProhibitListWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UIProhibitListWnd::_SendMsg(SAKEXE, "UIProhibitListWnd::SendMsg");
int UIProhibitListWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3) // line 9922
{
	return (this->*_SendMsg)(sender, message, val1, val2, val3);

	//TODO
}


////////////////////////////////////////
