#include "GameMode.h"
#include "Globals.h" // g_session
#include "Mode.h"
#include "ModeMgr.h"
#include "MsgStrings.h"
#include "Session.h"
#include "SnapMgr.h"
#include "Base/ResMgr.h"
#include "Resource/Action.h"
#include "Resource/ImfRes.h"
#include "Resource/PaletteRes.h"
#include "Resource/Sprite.h"
#include "Window/UIControl.h" // UIBitmapButton
#include "Window/UIEquipWnd.h"
#include "Window/UIRectInfo.h" // EquipWndInfo


UIEquipWnd::UIEquipWnd() // line 1695-1697 (UIFrameWnd2.cpp)
{
//	m_highlightMode[0] = m_highlightMode[1] = m_highlightMode[2] = 0;
//	m_orgHeight = 0;
	m_info = NULL;
//	m_optionOffButton = NULL;
//	m_optionOpenButton = NULL;

}


UIEquipWnd::~UIEquipWnd() // line 1700-1701 (UIFrameWnd2.cpp)
{
}


bool UIEquipWnd::IsUpdateNeed() // line 743 (UIFrameWnd.h)
{
	return true;
}


void UIEquipWnd::OnCreate(int cx, int cy) // line 1704-1770 (UIFrameWnd2.cpp)
{
	int posX[3] = {};
	int ids2[3] = {};
	char* toolTip[8] = {};
	char* buttonName2[8] = {};

	posX[0] = 3;
	posX[1] = 252;
	posX[2] = 266;
	ids2[0] = ID_BASE;
	ids2[1] = ID_MINI;
	ids2[2] = ID_CLOSE;
	buttonName2[0] = "base";
	buttonName2[1] = "mini";
	buttonName2[2] = "close";
	toolTip[0] = "";
	toolTip[1] = "Ctrl+Q";
	toolTip[2] = "Alt+Q";

	mystd::string preBmpName2 = "유저인터페이스\\basic_interface\\sys_";

	for( size_t i = 0; i < 3; ++i )
	{
		UIBitmapButton* button = new UIBitmapButton();
		button->UIBitmapButton::SetBitmapName((preBmpName2 + buttonName2[i] + "_off.bmp").c_str(), 0);
		button->UIBitmapButton::SetBitmapName((preBmpName2 + buttonName2[i] + "_on.bmp").c_str(), 1);
		button->UIBitmapButton::SetBitmapName((preBmpName2 + buttonName2[i] + "_on.bmp").c_str(), 2);
		button->UIWindow::Create(button->UIBitmapButton::GetBitmapWidth(), button->UIBitmapButton::GetBitmapHeight());
		button->Move(posX[i], 3);
		button->UIButton::SetId(ids2[i]);
		button->UIButton::SetToolTip(toolTip[i]);
		this->UIWindow::AddChild(button);
	}

	{
	std::string pathName = "유저인터페이스\\basic_interface\\";

	m_optionOffButton = new UIBitmapButton();
	m_optionOffButton->UIBitmapButton::SetBitmapName((pathName + "btn_off" + ".bmp").c_str(), 0);
	m_optionOffButton->UIBitmapButton::SetBitmapName((pathName + "btn_off" + ".bmp").c_str(), 1);
	m_optionOffButton->UIBitmapButton::SetBitmapName((pathName + "btn_off" + ".bmp").c_str(), 2);
	m_optionOffButton->UIWindow::Create(m_optionOffButton->UIBitmapButton::GetBitmapWidth(), m_optionOffButton->UIBitmapButton::GetBitmapHeight());
	m_optionOffButton->Move(m_w / 2 - 18, m_h - 40 + 230 * this->UIEquipWnd::HasOptionOffButton());
	m_optionOffButton->UIButton::SetId(ID_EQUIP_OPTION_OFF);
	m_optionOffButton->UIButton::SetToolTip(this->UIEquipWnd::GetOptionOffToolTipText());
	this->UIWindow::AddChild(m_optionOffButton);
	}

	{
	std::string pathName = "유저인터페이스\\basic_interface\\";

	m_optionOpenButton = new UIBitmapButton();
	m_optionOpenButton->UIBitmapButton::SetBitmapName((pathName + "btn_items_off" + ".bmp").c_str(), 0);
	m_optionOpenButton->UIBitmapButton::SetBitmapName((pathName + "btn_items_on" + ".bmp").c_str(), 1);
	m_optionOpenButton->UIBitmapButton::SetBitmapName((pathName + "btn_items_on" + ".bmp").c_str(), 2);
	m_optionOpenButton->UIWindow::Create(m_optionOpenButton->UIBitmapButton::GetBitmapWidth(), m_optionOpenButton->UIBitmapButton::GetBitmapHeight());
	m_optionOpenButton->Move(m_w / 2 - 14, m_h - 60 + 230 * this->UIEquipWnd::HasOptionOpenButton());
	m_optionOpenButton->UIButton::SetId(ID_EQUIP_OPTION_OPEN);
	m_optionOpenButton->UIButton::SetToolTip(this->UIEquipWnd::GetOptionOpenToolTipText());
	this->UIWindow::AddChild(m_optionOpenButton);
	}

	m_highlightMode[0] = -1;
	m_highlightMode[1] = -1;
	m_highlightMode[2] = -1;

	m_orgHeight = m_h;
}


void UIEquipWnd::DragAndDrop(int x, int y, const DRAG_INFO* const dragInfo) // line 1773-1826 (UIFrameWnd2.cpp)
{
	if( g_windowMgr.UIWindowMgr::GetExchangeWnd() != NULL )
	{
		this->UIWindow::DragAndDrop(x, y, dragInfo);
		return;
	}

	if( dragInfo->m_dragType == DT_FROM_ITEMWND )
	{
		Trace("x == %d, y == %d", x, y);
		Trace("dragInfo->m_numDragItem == %d, dragInfo->m_dragItemIndex == %d", dragInfo->m_numDragItem, dragInfo->m_dragItemIndex);

		CGameMode* gameMode = g_modeMgr.CModeMgr::GetGameMode();

		ITEM_INFO itemInfo = g_session.CSession::GetItemInfoByIndex(dragInfo->m_dragItemIndex);
		Trace("dragitemInfo.m_itemType==%d", itemInfo.m_itemType);

		if( itemInfo.m_itemIndex != 0 )
		{
			if( itemInfo.m_itemType == TYPE_ARROW )
				gameMode->SendMsg(MM_WEAR_EQUIP_ARROW, dragInfo->m_dragItemIndex, itemInfo.m_location, 0);
			else
			if( itemInfo.m_location != 0 && itemInfo.m_wearLocation != 0 && itemInfo.m_isIdentified )
				gameMode->SendMsg(MM_WEAR_EQUIP, dragInfo->m_dragItemIndex, itemInfo.m_location, 0);
		}
	}

	g_modeMgr.CModeMgr::GetCurMode()->SendMsg(UM_DOWNPUSH, 0, 0, 0);
}


void UIEquipWnd::OnLBtnDblClk(int x, int y) // line 1829-1845 (UIFrameWnd2.cpp)
{
	if( y < 17 )
		this->SendMsg(this, UM_COMMAND, ID_MINI, 0, 0);

	ITEM_INFO itemInfo = this->UIEquipWnd::GetItemInfo(x, y);
	if( itemInfo.m_itemIndex != 0 && itemInfo.m_num > 0 )
	{
		int slotNum[3];
		g_session.CSession::BitMaskToSlotNum(itemInfo.m_wearLocation, slotNum);
		g_modeMgr.CModeMgr::GetCurMode()->SendMsg(MM_TAKE_OFF_EQUIP, slotNum[0], 0, 0);
	}
}


void UIEquipWnd::OnLBtnDown(int x, int y) // line 1848-1861 (UIFrameWnd2.cpp)
{
	if( y < 17 )
		this->UIFrameWnd::OnLBtnDown(x, y);

	ITEM_INFO itemInfo = this->UIEquipWnd::GetItemInfo(x, y);
	if( itemInfo.m_itemIndex != 0 && itemInfo.m_num > 0 )
	{
		g_modeMgr.CModeMgr::GetCurMode()->SendMsg(MM_BEGIN_DRAG_FROM_EQUIPMWND, itemInfo.m_wearLocation, 0, 0);
	}
}


void UIEquipWnd::OnRBtnDown(int x, int y) // line 1864-1870 (UIFrameWnd2.cpp)
{
	ITEM_INFO itemInfo = this->UIEquipWnd::GetItemInfo(x, y);
	if( itemInfo.m_itemIndex != 0 )
	{
		UIFrameWnd* wnd = g_windowMgr.UIWindowMgr::MakeWindow(WID_ITEMCOLLECTIONWND);
		wnd->SendMsg(NULL, UM_ITEMEXPLANATION, (int)&itemInfo, 0, 0);
	}
}


ITEM_INFO UIEquipWnd::GetItemInfo(int x, int y) // line 1873-1904 (UIFrameWnd2.cpp)
{
	int wearLocation = -1;

	if( x >= 6 && x < 30 )
	{
		if( y >= 17 && y < 41 )
			wearLocation = WEARLOCATION_HEAD2;
		else
		if( y >= 43 && y < 67 )
			wearLocation = WEARLOCATION_HEAD;
		else
		if( y >= 69 && y < 93 )
			wearLocation = WEARLOCATION_RARM;
		else
		if( y >= 95 && y < 119 )
			wearLocation = WEARLOCATION_ROBE;
		else
		if( y >= 121 && y < 145 )
			wearLocation = WEARLOCATION_ACCESSORY1;
	}
	else
	if( x >= 251 && x < 275 )
	{
		if( y >= 17 && y < 41 )
			wearLocation = WEARLOCATION_HEAD3;
		else
		if( y >= 43 && y < 67 )
			wearLocation = WEARLOCATION_BODY;
		else
		if( y >= 69 && y < 93 )
			wearLocation = WEARLOCATION_LARM;
		else
		if( y >= 95 && y < 119 )
			wearLocation = WEARLOCATION_SHOES;
		else
		if( y >= 121 && y < 145 )
			wearLocation = WEARLOCATION_ACCESSORY2;
	}

	if( m_w / 2 - 25 < x && x < m_w / 2 - 1 && y > 44 && y < 68 )
		wearLocation = WEARLOCATION_ARROW;

	return g_session.CSession::GetEquipedItems(wearLocation);
}


void UIEquipWnd::OnMouseMove(int x, int y) // line 1907-1910 (UIFrameWnd2.cpp)
{
	this->UIFrameWnd::OnMouseMove(x, y);
	this->OnMouseHover(x, y);
}


void UIEquipWnd::OnMouseHover(int x, int y) // line 1913-2006 (UIFrameWnd2.cpp)
{
	ITEM_INFO itemInfo = this->UIEquipWnd::GetItemInfo(x, y);
	if( itemInfo.m_itemIndex != 0 )
	{
		itemInfo.m_isIdentified = true;

		char itemName[64];
		itemInfo.ITEM_INFO::GetItemName(itemName);

		int gx;
		if( x < m_w / 3 )
			gx = 6;
		else
		if( x > 2 * m_w / 3 )
			gx = 251;
		else
		{
			gx = m_w / 2 - 20;
		}

		int gy;
		if( y < 41 )
			gy = -3;
		else
		if( y < 67 )
			gy = 23;
		else
		if( y < 93 )
			gy = 49;
		else
		if( y < 119 )
			gy = 75;
		else
		{
			gy = 101;
		}

		this->UIWindow::GetGlobalCoor(gx, gy);

		if( itemInfo.m_num > 1 )
		{
			char itemHelp[128];
			sprintf(itemHelp, MsgStr(MSI_EA2), itemName, itemInfo.m_num);
			g_modeMgr.CModeMgr::GetCurMode()->CMode::MakeHelpBalloon(itemHelp, gx, gy, g_session.CSession::GetItemDisColor(&itemInfo));
		}
		else
		{
			g_modeMgr.CModeMgr::GetCurMode()->CMode::MakeHelpBalloon(itemName, gx, gy, g_session.CSession::GetItemDisColor(&itemInfo));
		}
	}

	int oldHighlight[3];
	oldHighlight[0] = m_highlightMode[0];
	oldHighlight[1] = m_highlightMode[1];
	oldHighlight[2] = m_highlightMode[2];
	m_highlightMode[0] = -1;
	m_highlightMode[1] = -1;
	m_highlightMode[2] = -1;

	CGameMode* gameMode = g_modeMgr.CModeMgr::GetGameMode();
	if( gameMode->CGameMode::GetDragType() == DT_FROM_ITEMWND )
	{
		if( x >= 0 && y >= 0 && x < m_w && y < m_h )
		{
			ITEM_INFO itemInfo = g_session.CSession::GetItemInfoByIndex(gameMode->CGameMode::GetDragItemIndex());
			if( itemInfo.m_itemIndex != 0 && itemInfo.m_location != 0 )
			{
				int slotNum[3];
				g_session.CSession::BitMaskToSlotNum(itemInfo.m_location, slotNum);

				m_highlightMode[0] = slotNum[0];
				if( slotNum[1] != -1 ) m_highlightMode[1] = slotNum[1];
				if( slotNum[2] != -1 ) m_highlightMode[2] = slotNum[2];
			}
		}
	}

	if( oldHighlight[0] != m_highlightMode[0]
	 || oldHighlight[1] != m_highlightMode[1]
	 || oldHighlight[2] != m_highlightMode[2] )
		this->Invalidate();
}


void UIEquipWnd::StoreInfo() // line 2009-2017 (UIFrameWnd2.cpp)
{
	if ( m_info != NULL )
	{
		m_info->w = m_w;
		m_info->h = m_h;
		m_info->x = m_x;
		m_info->y = m_y;
		m_info->orgHeight = m_orgHeight;
	}
}


void UIEquipWnd::OnDraw() // line 2020-2250 (UIFrameWnd2.cpp)
{
	this->UIWindow::DrawBitmap(0, 0, (CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp("유저인터페이스\\basic_interface\\titlebar_fix.bmp")), false);
	this->UIWindow::TextOutA(17, 4, MsgStr(MSI_EQUIPED_ITEM), 0, 0, 12, 0x00FFFFFF);
	this->UIWindow::TextOutA(16, 3, MsgStr(MSI_EQUIPED_ITEM), 0, 0, 12, 0x00000000);
	if( m_h == 17 )
		return; // minimized.

	this->UIWindow::DrawBitmap(0, 17, (CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp("유저인터페이스\\basic_interface\\equipwin_bg.bmp")), false);

	for( int i = 0; i < 3; ++i )
	{
		int highlightMode = m_highlightMode[i];
		switch( highlightMode )
		{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		{
			int posX[2];
			posX[0] = 4;
			posX[1] = 248;
			this->UIWindow::DrawBitmap(posX[highlightMode / 4], (highlightMode % 4) * 26 + 51, (CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp("유저인터페이스\\basic_interface\\item_invert.bmp")), true);
		}
		break;
		case 8:
		case 9:
		{
			int posX[2];
			posX[0] = 4;
			posX[1] = 248;
			this->UIWindow::DrawBitmap(posX[highlightMode % 4], 25, (CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp("유저인터페이스\\basic_interface\\item_invert.bmp")), true);
		}
		break;
		default:
		break;
		};
	};

	{ // scope
	int posX[2];
	posX[0] = 6;
	posX[1] = 251;

	int txtX[8];
	txtX[0] = 28;
	txtX[1] = 28;
	txtX[2] = 28;
	txtX[3] = 28;
	txtX[4] = 167;
	txtX[5] = 167;
	txtX[6] = 167;
	txtX[7] = 167;

	int txtY[8];
	txtY[0] = 0;
	txtY[1] = 26;
	txtY[2] = 52;
	txtY[3] = 78;
	txtY[4] = 0;
	txtY[5] = 26;
	txtY[6] = 52;
	txtY[7] = 78;

	for( int i = 0; i < 8; ++i )
	{
		ITEM_INFO equipedItem = g_session.CSession::GetEquipedItems(i);
		if( equipedItem.m_itemIndex != 0 && equipedItem.m_num == 1 )
		{
			this->UIFrameWnd::DrawItem(posX[i / 4], (i % 4) * 26 + 44, equipedItem, 0);
			this->UIFrameWnd::DrawItemTextRect(txtX[i] + 5, txtY[i] + 51, 70, equipedItem, 0, 0, 12);
		}
	}
	} // scope

	{ // scope
	int posX[2];
	posX[0] = 6;
	posX[1] = 251;

	int txtX[2];
	txtX[0] = 28;
	txtX[1] = 167;

	for( int i = 8; i < 10; ++i )
	{
		ITEM_INFO equipedItem = g_session.CSession::GetEquipedItems(i);
		if( equipedItem.m_itemIndex != 0 && equipedItem.m_num == 1 )
		{
			this->UIFrameWnd::DrawItem(posX[i % 4], 18, equipedItem, 0);
			this->UIFrameWnd::DrawItemTextRect(txtX[i - 8] + 5, 25, 70, equipedItem, 0, 0, 12);
		}
	}
	} // scope

	mystd::string imfName;
	mystd::string sprName[5];
	mystd::string actName[5];

	mystd::string bodyPaletteName;
	mystd::string headPaletteName;
	int headPalette = g_session.m_headPalette;
	int bodyPalette = g_session.m_bodyPalette;

	CacheInfo info = {};
	int job = g_session.CSession::GetJob();
	char tmpName[256];

	actName[0] = g_session.CSession::GetJobActName(job, g_session.CSession::GetSex(), tmpName);
	sprName[0] = g_session.CSession::GetJobSprName(job, g_session.CSession::GetSex(), tmpName);
	actName[1] = g_session.CSession::GetHeadActName(job, g_session.m_head, g_session.CSession::GetSex(), tmpName);
	sprName[1] = g_session.CSession::GetHeadSprName(job, g_session.m_head, g_session.CSession::GetSex(), tmpName);
	actName[2] = g_session.CSession::GetAccessoryActName(job, g_session.m_head, g_session.CSession::GetSex(), g_session.m_accessory, tmpName);
	sprName[2] = g_session.CSession::GetAccessorySprName(job, g_session.m_head, g_session.CSession::GetSex(), g_session.m_accessory, tmpName);
	actName[3] = g_session.CSession::GetAccessoryActName(job, g_session.m_head, g_session.CSession::GetSex(), g_session.m_accessory2, tmpName);
	sprName[3] = g_session.CSession::GetAccessorySprName(job, g_session.m_head, g_session.CSession::GetSex(), g_session.m_accessory2, tmpName);
	actName[4] = g_session.CSession::GetAccessoryActName(job, g_session.m_head, g_session.CSession::GetSex(), g_session.m_accessory3, tmpName);
	sprName[4] = g_session.CSession::GetAccessorySprName(job, g_session.m_head, g_session.CSession::GetSex(), g_session.m_accessory3, tmpName);

	if( bodyPalette != 0 )
	{
		char palName[64];
		bodyPaletteName = g_session.CSession::GetBodyPaletteName(job, g_session.CSession::GetSex(), bodyPalette, palName);
	}

	if( headPalette != 0 )
	{
		char palName[64];
		headPaletteName = g_session.CSession::GetHeadPaletteName(g_session.m_head, job, g_session.CSession::GetSex(), headPalette, palName);
	}

	imfName = g_session.CSession::GetImfName(job, g_session.m_head, g_session.CSession::GetSex(), tmpName);

	for( int i = 0; i < 5; ++i )
	{
		if( actName[i].size() == 0 || sprName[i].size() == 0 )
			continue;

		CImfRes* imfRes = (CImfRes*)g_resMgr().CResMgr::Get(imfName.c_str());
		CActRes* actRes = (CActRes*)g_resMgr().CResMgr::Get(actName[i].c_str());
		CSprRes* sprRes = (CSprRes*)g_resMgr().CResMgr::Get(sprName[i].c_str());

		CMotion* mot = actRes->CActRes::GetMotion(0, 0);

		static int s_offX = 0; //NOTE: global variable used only in this function
		static int s_offY = 0; //NOTE: global variable used only in this function
		int offX = 0;
		int offY = 0;

		if( i == 1 )
		{
			CActRes* actRes0 = (CActRes*)g_resMgr().CResMgr::Get(actName[0].c_str());
			CMotion* mot0 = actRes0->CActRes::GetMotion(0, 0);

			if( mot->attachCnt != 0 && mot0->attachCnt != 0 )
			{
				CAttachPointInfo* attachInfo = &mot->attachInfo[0];
				CAttachPointInfo* attachInfo0 = &mot0->attachInfo[0];

				if( attachInfo->m_attr == attachInfo0->m_attr )
				{
					offX = attachInfo0->x - attachInfo->x;
					offY = attachInfo0->y - attachInfo->y;
					s_offX = offX;
					s_offY = offY;
				}
			}
		}
		else
		if( i == 2 || i == 3 || i == 4 )
		{
			CActRes* actRes1 = (CActRes*)g_resMgr().CResMgr::Get(actName[1].c_str());
			CMotion* mot1 = actRes1->CActRes::GetMotion(0, 0);

			if( mot->attachCnt != 0 && mot1->attachCnt != 0 )
			{
				CAttachPointInfo* attachInfo = &mot->attachInfo[0];
				CAttachPointInfo* attachInfo1 = &mot1->attachInfo[0];

				if( attachInfo->m_attr == attachInfo1->m_attr )
				{
					offX = attachInfo1->x - attachInfo->x;
					offY = attachInfo1->y - attachInfo->y;
				}
			}

			offX += s_offX;
			offY += s_offY;
		}

		unsigned long* palette;
		if( i == 0 && bodyPalette != 0 )
		{
			palette = static_cast<CPaletteRes*>(g_resMgr().CResMgr::Get(bodyPaletteName.c_str()))->m_pal;
		}
		else
		if( i == 1 && headPalette != 0 )
		{
			palette = static_cast<CPaletteRes*>(g_resMgr().CResMgr::Get(headPaletteName.c_str()))->m_pal;
		}
		else
		{
			palette = sprRes->m_pal;
		}

		unsigned int clip_number = ( i <= 1 ) ? i : 0;
		CSprClip* clip = mot->CMotion::GetClip(clip_number);
		if( clip->sprIndex != -1 )
		{
			SprImg* img = sprRes->m_sprites[clip->clipType][clip->sprIndex];

			CTexture* tex;
			if( clip->clipType != 0 )
			{
				tex = img->tex;
			}
			else
			{
				tex = g_renderer->CRenderer::GetSpriteIndex(*img, (unsigned long)palette, &info);
				if( tex == NULL )
					tex = g_renderer->CRenderer::AddSpriteIndex(*img, palette, &info);
			}

			int clipPosy2 = 0;
			int clipPosy = offY + clip->y + m_h - 18;

			if( clipPosy < 0 )
			{
				clipPosy2 = clipPosy;
				clipPosy = 0;
			}

			m_dc->BltTexture2(offX + clip->x + m_w / 2 + 1, clipPosy, tex, int(info.tu * 256.0), int(info.tv * 256.0 - clipPosy2), img->width, clipPosy2 + img->height, clip->flags, img->isHalfW + 1, img->isHalfH + 1);
		}
	}

	ITEM_INFO arrowItem = g_session.CSession::GetItemInfoByIndex(g_session.CSession::GetEquipArrowIndex());
	if( arrowItem.m_itemIndex != 0 )
	{
		this->UIFrameWnd::DrawItem(m_w / 2 - 25, 44, arrowItem, 0);
		this->UIFrameWnd::DrawItemText(m_w / 2 - 25, 68, arrowItem, 0, 0, 12);
	}
}


int UIEquipWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3) // line 2253-2326 (UIFrameWnd2.cpp)
{
	switch( message )
	{
	case UM_COMMAND:
	{
		switch( val1 )
		{
		case ID_EQUIP_OPTION_OFF:
		{
			if( g_windowMgr.UIWindowMgr::GetMerchantItemMyShopWnd() != NULL )
			{
				g_windowMgr.UIWindowMgr::SendMsg(UIM_OPENCHATWND, 0, 0, 0);
				g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)MsgStr(MSI_PLEASE_CLOSE_STORE), 0x0000FF, 0);
				break;
			}

			this->UIEquipWnd::SendOptionOffToMode();
			m_optionOffButton->Move(m_w / 2 - 18, m_h - 40 + 230 * this->UIEquipWnd::HasOptionOffButton());
			m_optionOpenButton->Move(m_w / 2 - 14, m_h - 60 + 230 * this->UIEquipWnd::HasOptionOpenButton());
			this->Invalidate();
		}
		break;
		case ID_EQUIP_OPTION_OPEN:
		{
			if( !g_windowMgr.UIWindowMgr::DeleteWindow(WID_MERCHANTITEMWND) && !this->UIEquipWnd::HasOptionOpenButton() )
				g_windowMgr.UIWindowMgr::MakeWindow(WID_MERCHANTITEMWND);
		}
		break;
		case ID_MINI:
		{
			int backup_h = m_h;
			int new_h;

			if( m_h == 17 )
			{// restore
				new_h = m_orgHeight;
			}
			else
			{// minimize
				new_h = 17;
				m_orgHeight = m_h;
			}

			this->Resize(m_w, new_h);
			g_windowMgr.UIWindowMgr::UpdateSnapInfo(this);
			g_windowMgr.UIWindowMgr::MakeTopLayer(this);

			if( m_h != backup_h )
				g_snapMgr.CSnapMgr::MoveConnectedObject(this, 0, m_h - backup_h, 3);
		}
		break;
		case ID_CLOSE:
		{
			g_windowMgr.UIWindowMgr::DeleteWindow(WID_EQUIPWND);
		}
		break;
		default:
		break;
		};
	}
	break;
	case UM_SETINFO:
	{
		m_info = reinterpret_cast<EquipWndInfo*>(val1);

		if( !m_info->EquipWndInfo::IsValidInfo() )
			m_info->EquipWndInfo::MakeDefault();

		if( m_info->h != m_info->orgHeight )
			this->SendMsg(NULL, UM_COMMAND, ID_MINI, 0, 0);

		this->Move(m_info->x, m_info->y);
	}
	break;
	case UM_REFRESH:
	{
		m_optionOffButton->Move(m_w / 2 - 18, m_h - 40 + 230 * this->UIEquipWnd::HasOptionOffButton());
		m_optionOpenButton->Move(m_w / 2 - 14, m_h - 60 + 230 * this->UIEquipWnd::HasOptionOpenButton());
		this->Invalidate();
	}
	break;
	default:
	{
		return this->UIFrameWnd::SendMsg(sender, message, val1, val2, val3);
	}
	break;
	};

	return 0;
}


bool UIEquipWnd::HasOptionOffButton() // line 2329-2334 (UIFrameWnd2.cpp)
{
	return ( !IsEffectStatePushCart(g_session.m_effectState)
	      && !IsEffectStateBird(g_session.m_effectState)
	      && !IsEffectStateChicken(g_session.m_effectState) );
}


bool UIEquipWnd::HasOptionOpenButton() // line 2337-2342 (UIFrameWnd2.cpp)
{
	return !IsEffectStatePushCart(g_session.m_effectState);
}


const char* UIEquipWnd::GetOptionOffToolTipText() // line 2345-2354 (UIFrameWnd2.cpp)
{
	if( IsEffectStatePushCart(g_session.m_effectState) )
		return MsgStr(MSI_CARTOFF);
	else
	if( IsEffectStateBird(g_session.m_effectState) )
		return MsgStr(MSI_BIRDOFF);
	else
	if( IsEffectStateChicken(g_session.m_effectState) )
		return MsgStr(MSI_CHIKENOFF);
	else
		return "";
}


const char* UIEquipWnd::GetOptionOpenToolTipText() // line 2357-2362 (UIFrameWnd2.cpp)
{
	return ( IsEffectStatePushCart(g_session.m_effectState) ) ? MsgStr(MSI_OPENCARTWINDOW) : "";
}


void UIEquipWnd::SendOptionOffToMode() // line 2366-2375 (UIFrameWnd2.cpp)
{
	CMode* curMode = g_modeMgr.CModeMgr::GetCurMode();

	if( IsEffectStatePushCart(g_session.m_effectState) )
		curMode->SendMsg(MM_REQ_CARTOFF, 0, 0, 0);
	else
	if( IsEffectStateBird(g_session.m_effectState) )
		curMode->SendMsg(MM_REQ_BIRDOFF, 0, 0, 0);
	else
	if( IsEffectStateChicken(g_session.m_effectState) )
		curMode->SendMsg(MM_REQ_CHIKENOFF, 0, 0, 0);
}
