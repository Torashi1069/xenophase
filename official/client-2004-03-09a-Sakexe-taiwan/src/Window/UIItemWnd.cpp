#include "GameMode.h"
#include "Globals.h"
#include "ModeMgr.h"
#include "MsgStrings.h"
#include "Base/ResMgr.h"
#include "Base/Util.h"
#include "Window/UIItemWnd.h"
#include "Window/UIScrollBar.h"


UIItemDropCntWnd::UIItemDropCntWnd(void) // line 14
{
}


UIItemDropCntWnd::~UIItemDropCntWnd(void) // line 18
{
}


hook_method<void (UIItemDropCntWnd::*)(int cx, int cy)> UIItemDropCntWnd::_OnCreate(SAKEXE, "UIItemDropCntWnd::OnCreate");
void UIItemDropCntWnd::OnCreate(int cx, int cy) // line 22
{
	return (this->*_OnCreate)(cx, cy);

	m_editCtrl = new UIEditCtrl();
	m_editCtrl->UIWindow::Create(80, 16);
	m_editCtrl->Move(15, 22);
	m_editCtrl->UIEditCtrl::SetTextLimit(6);
	m_editCtrl->UIEditCtrl::SetFrameColor(232, 232, 232);
	this->UIWindow::AddChild(m_editCtrl);
	CGameMode* mode = g_modeMgr.CModeMgr::GetGameMode();

	char Dest[40];
	sprintf(Dest, "%d", mode->CGameMode::GetDragInfo()->m_numDragItem);
	m_editCtrl->SetText(Dest);

	g_windowMgr.UIWindowMgr::SetFocusEdit(m_editCtrl);
	m_editCtrl->UIEditCtrl::MakeSelect();
	const char* itemName = mode->CGameMode::GetDragItemName();

	mystd::string text;
	if( itemName != NULL )
	{
		ITEM_INFO item;
		item.m_itemName = itemName;
		item.m_isIdentified = mode->CGameMode::GetDragInfo()->m_isIdentified;
		item.m_refiningLevel = 0;

		char itemName[128];
		item.ITEM_INFO::GetItemName(itemName);

		text = itemName;
	}

	m_newText = new UIStaticText();
	m_newText->UIWindow::Create(m_w - 30, 15);
	m_newText->Move(15, 6);
	m_newText->UIStaticText::SetText(text.c_str(), 0);
	this->UIWindow::AddChild(m_newText);

	UIBitmapButton* button = new UIBitmapButton();
	mystd::string basedir = "유저인터페이스\\";
	button->UIBitmapButton::SetBitmapName((basedir + "btn_ok"   + ".bmp").c_str(), 0);
	button->UIBitmapButton::SetBitmapName((basedir + "btn_ok_a" + ".bmp").c_str(), 1);
	button->UIBitmapButton::SetBitmapName((basedir + "btn_ok_b" + ".bmp").c_str(), 2);
	button->UIWindow::Create(button->UIBitmapButton::GetBitmapWidth(), button->UIBitmapButton::GetBitmapHeight());
	button->Move(m_w - 55, m_h - 32);
	button->UIWindow::SetId(94);
	this->UIWindow::AddChild(button);

	m_defPushId = 94;
	m_state = 0;
}


hook_method<void (UIItemDropCntWnd::*)(void)> UIItemDropCntWnd::_OnDraw(SAKEXE, "UIItemDropCntWnd::OnDraw");
void UIItemDropCntWnd::OnDraw(void) // line 123
{
	return (this->*_OnDraw)();

	//TODO
}


hook_method<int (UIItemDropCntWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UIItemDropCntWnd::_SendMsg(SAKEXE, "UIItemDropCntWnd::SendMsg");
int UIItemDropCntWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3) // line 127
{
	return (this->*_SendMsg)(sender, message, val1, val2, val3);

	//TODO
}


hook_method<void (UIItemDropCntWnd::*)(int visible)> UIItemDropCntWnd::_SetShow(SAKEXE, "UIItemDropCntWnd::SetShow");
void UIItemDropCntWnd::SetShow(int visible) // line 84
{
	return (this->*_SetShow)(visible);

	//TODO
}


////////////////////////////////////////


UIItemBaseWnd::UIItemBaseWnd(void) // line 518
{
	m_resizer = NULL;
	m_scrollBar = NULL;
	m_viewOffset = 0;
	m_vertScrEnabled = 0;
	m_isBasket = 0;
	m_button[0] = NULL;
	m_button[1] = NULL;
	m_drawNumItem = 1;
}


UIItemBaseWnd::~UIItemBaseWnd(void) // line 532
{
}


hook_method<void (UIItemBaseWnd::*)(int cx, int cy)> UIItemBaseWnd::_OnCreate(SAKEXE, "UIItemBaseWnd::OnCreate");
void UIItemBaseWnd::OnCreate(int cx, int cy) // line 537
{
	return (this->*_OnCreate)(cx, cy);

	;
}


hook_method<void (UIItemBaseWnd::*)(void)> UIItemBaseWnd::_OnDraw(SAKEXE, "UIItemBaseWnd::OnDraw");
void UIItemBaseWnd::OnDraw(void) // line 540
{
	return (this->*_OnDraw)();

	CBitmapRes* bitmap;

	bitmap = (CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp("유저인터페이스\\basic_interface\\titlebar_left.bmp"));
	this->UIWindow::DrawBitmap(0, 0, bitmap, false);

	bitmap = (CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp("유저인터페이스\\basic_interface\\titlebar_right.bmp"));
	this->UIWindow::DrawBitmap(m_w - bitmap->m_width, 0, bitmap, false);

	for( int i = 0; i < (m_w - 24) / 12 + ((m_w - 24) % 12 != 0); ++i )
	{
		bitmap = (CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp("유저인터페이스\\basic_interface\\titlebar_mid.bmp"));
		this->UIWindow::DrawBitmap(12 + 12*i, 0, bitmap, false);
	}

	if( m_h == 17 )
		return; // collapsed.

	for( int i = 0; i < (m_h - 38) / 8 + ((m_h - 38) % 8 != 0); ++i )
	{
		bitmap = (CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp("유저인터페이스\\basic_interface\\itemwin_left.bmp"));
		this->UIWindow::DrawBitmap(0, 17 + 8*i, bitmap, false);
	}

	for( int i = 0; i < (m_h - 38) / 8 + ((m_h - 38) % 8 != 0); ++i )
	{
		bitmap = (CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp("유저인터페이스\\basic_interface\\itemwin_right.bmp"));
		this->UIWindow::DrawBitmap(m_w - bitmap->m_width, 17 + 8*i, bitmap, false);
	}

	unsigned long rr, gg, bb;
	g_skinMgr.CSkinMgr::GetColorChipColor(2, 2, rr, gg, bb);
	this->UIWindow::DrawBox(20, 17, (m_w - 60) % 32, m_h - 38, BYTE(rr) << 0 | BYTE(gg) << 8 | BYTE(bb) << 16);
	this->UIWindow::DrawBox(20, 17 + (m_h - 38) / 32 * 32, m_w - 24, (m_h - 38) % 32, BYTE(rr) << 0 | BYTE(gg) << 8 | BYTE(bb) << 16);

	const char* bmpName[6];
	bmpName[0] = "유저인터페이스\\basic_interface\\btnbar_left.bmp";
	bmpName[1] = "유저인터페이스\\basic_interface\\btnbar_right.bmp";
	bmpName[2] = "유저인터페이스\\basic_interface\\btnbar_mid.bmp";
	bmpName[3] = "유저인터페이스\\basic_interface\\btnbar_left2.bmp";
	bmpName[4] = "유저인터페이스\\basic_interface\\btnbar_right2.bmp";
	bmpName[5] = "유저인터페이스\\basic_interface\\btnbar_mid2.bmp";

	bitmap = (CBitmapRes*)g_resMgr().CResMgr::Get(bmpName[3 * m_isBasket + 0]);
	this->UIWindow::DrawBitmap(0, m_h - bitmap->m_height, bitmap, false);

	bitmap = (CBitmapRes*)g_resMgr().CResMgr::Get(bmpName[3 * m_isBasket + 1]);
	this->UIWindow::DrawBitmap(m_w - bitmap->m_width, m_h - bitmap->m_height, bitmap, false);

	for( int i = 0; i < (m_w - 42) / 21 + ((m_w - 42) % 21 != 0); ++i )
	{
		bitmap = (CBitmapRes*)g_resMgr().CResMgr::Get(bmpName[3 * m_isBasket + 2]);
		this->UIWindow::DrawBitmap(21 + 21*i, m_h - bitmap->m_height, bitmap, false);
	}

	for( int j = 0; j < (m_h - 38) / 32; ++j )
		for( int i = 0; i < (m_w - 40) / 32; ++i )
			this->UIFrameWnd::DrawItemFrame(40 + 32*i, 17 + 32*j);

	int itemCount = 0;
	int drawCount = 0;

	for( mystd::list<ITEM_INFO>::const_iterator it = m_itemList.begin(); it != m_itemList.end(); ++it )
	{
		++itemCount;

		if( itemCount <= m_itemHorzNum * m_viewOffset )
			continue; // skip entries while seeking to the part being viewed

		if( g_session.CSession::IsPetEgg(atoi(it->m_itemName.c_str())) && it->m_isDamaged )
			continue; // don't display these?

		int itemX = 44 + 32 * drawCount % m_itemHorzNum;
		int itemY = 21 + 32 * drawCount / m_itemHorzNum;

		if( m_drawNumItem != 0 )
			this->UIFrameWnd::DrawItemWithCount(itemX, itemY, *it, false, false);
		else
			this->UIFrameWnd::DrawItem(itemX, itemY, *it, false);

		++drawCount;

		if( drawCount == m_itemHorzNum * m_itemVertNum )
			break; // end of view
	}
}


hook_method<void (UIItemBaseWnd::*)(int x, int y, const DRAG_INFO* const dragInfo)> UIItemBaseWnd::_DragAndDrop(SAKEXE, "UIItemBaseWnd::DragAndDrop");
void UIItemBaseWnd::DragAndDrop(int x, int y, const DRAG_INFO* const dragInfo) // line 871
{
	return (this->*_DragAndDrop)(x, y, dragInfo);

	g_modeMgr.CModeMgr::GetCurMode()->SendMsg(19, 0, 0, 0);
}


hook_method<void (UIItemBaseWnd::*)(void)> UIItemBaseWnd::_RecalcScrbarPos(SAKEXE, "UIItemBaseWnd::RecalcScrbarPos");
void UIItemBaseWnd::RecalcScrbarPos(void) // line 654
{
	return (this->*_RecalcScrbarPos)();

	//TODO
}


////////////////////////////////////////


UIMerchantItemShopWnd::UIMerchantItemShopWnd(void) // line 1573
{
	m_info = NULL;
	m_curItem = -1;
}


UIMerchantItemShopWnd::~UIMerchantItemShopWnd(void) // line 1580
{
}


hook_method<void (UIMerchantItemShopWnd::*)(int cx, int cy)> UIMerchantItemShopWnd::_OnCreate(SAKEXE, "UIMerchantItemShopWnd::OnCreate");
void UIMerchantItemShopWnd::OnCreate(int cx, int cy) // line 1584
{
	return (this->*_OnCreate)(cx, cy);

	m_resizer = new UIResizer();
	m_resizer->UIWindow::Create(16, 16);
	m_resizer->UIResizer::SetType(RT_DOWN);
	m_resizer->UIResizer::SetBitmap("유저인터페이스\\btn_resize.bmp");
	m_resizer->Move(m_w - 15, m_h - 15);
	m_resizer->UIResizer::SetColor(0xFFFF00FF, 0xFFFF00FF);
	this->UIWindow::AddChild(m_resizer);

	m_scrollBar = new UIScrollBar();
	m_scrollBar->UIScrollBar::Create(m_w - 15, 14, 1, m_h - 38);
	this->UIWindow::AddChild(m_scrollBar);

	m_itemHorzNum = 1;
	m_itemVertNum = (cy - 38) / 32;
	this->SendMsg(NULL, 23, 0, 0, 0);
}


hook_method<void (UIMerchantItemShopWnd::*)(int x, int y)> UIMerchantItemShopWnd::_OnLBtnDown(SAKEXE, "UIMerchantItemShopWnd::OnLBtnDown");
void UIMerchantItemShopWnd::OnLBtnDown(int x, int y) // line 1782
{
	return (this->*_OnLBtnDown)(x, y);

	//TODO
}


hook_method<void (UIMerchantItemShopWnd::*)(int x, int y)> UIMerchantItemShopWnd::_OnRBtnDown(SAKEXE, "UIMerchantItemShopWnd::OnRBtnDown");
void UIMerchantItemShopWnd::OnRBtnDown(int x, int y) // line 1809
{
	return (this->*_OnRBtnDown)(x, y);

	//TODO
}


hook_method<void (UIMerchantItemShopWnd::*)(int x, int y)> UIMerchantItemShopWnd::_OnMouseHover(SAKEXE, "UIMerchantItemShopWnd::OnMouseHover");
void UIMerchantItemShopWnd::OnMouseHover(int x, int y) // line 1821
{
	return (this->*_OnMouseHover)(x, y);

	//TODO
}


hook_method<void (UIMerchantItemShopWnd::*)(void)> UIMerchantItemShopWnd::_OnDraw(SAKEXE, "UIMerchantItemShopWnd::OnDraw");
void UIMerchantItemShopWnd::OnDraw(void) // line 1607
{
	return (this->*_OnDraw)();

	CBitmapRes* bitmap;
	unsigned long rr, gg, bb;

	bitmap = (CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp("유저인터페이스\\basic_interface\\titlebar_left.bmp"));
	this->UIWindow::DrawBitmap(0, 0, bitmap, false);

	bitmap = (CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp("유저인터페이스\\basic_interface\\titlebar_right.bmp"));
	this->UIWindow::DrawBitmap(m_w - bitmap->m_width, 0, bitmap, false);

	for( int i = 0; i < (m_w - 24) / 12 + ((m_w - 24) % 12 != 0); ++i )
	{
		bitmap = (CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp("유저인터페이스\\basic_interface\\titlebar_mid.bmp"));
		this->UIWindow::DrawBitmap(12 + 12*i, 0, bitmap, false);
	}

	if( m_h == 17 )
		return; // collapsed.

	for( int i = 0; i < (m_h - 38) / 8 + ((m_h - 38) % 8 != 0); ++i )
	{
		bitmap = (CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp("유저인터페이스\\basic_interface\\itemwin_left.bmp"));
		this->UIWindow::DrawBitmap(0, 17 + 8*i, bitmap, 0);
	}

	for( int i = 0; i < (m_h - 38) / 8 + ((m_h - 38) % 8 != 0); ++i )
	{
		bitmap = (CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp("유저인터페이스\\basic_interface\\itemwin_right.bmp"));
		this->UIWindow::DrawBitmap(m_w - bitmap->m_width, 17 + 8*i, bitmap, 0);
	}

	g_skinMgr.CSkinMgr::GetColorChipColor(2, 2, rr, gg, bb);
	this->UIWindow::DrawBox(20, 17, (m_w - 60) % 32, m_h - 38, BYTE(rr) << 0 | BYTE(gg) << 8 | BYTE(bb) << 16);
	this->UIWindow::DrawBox(20, 17 + (m_h - 38) / 32 * 32, m_w - 24, (m_h - 38) % 32, BYTE(rr) << 0 | BYTE(gg) << 8 | BYTE(bb) << 16);

	const char* bmpName[6];
	bmpName[0] = "유저인터페이스\\basic_interface\\btnbar_left.bmp";
	bmpName[1] = "유저인터페이스\\basic_interface\\btnbar_right.bmp";
	bmpName[2] = "유저인터페이스\\basic_interface\\btnbar_mid.bmp";
	bmpName[3] = "유저인터페이스\\basic_interface\\btnbar_left2.bmp";
	bmpName[4] = "유저인터페이스\\basic_interface\\btnbar_right2.bmp";
	bmpName[5] = "유저인터페이스\\basic_interface\\btnbar_mid2.bmp";

	bitmap = (CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp(bmpName[3 * m_isBasket + 0]));
	this->UIWindow::DrawBitmap(0, m_h - bitmap->m_height, bitmap, false);

	bitmap = (CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp(bmpName[3 * m_isBasket + 1]));
	this->UIWindow::DrawBitmap(m_w - bitmap->m_width, m_h - bitmap->m_height, bitmap, false);

	for( int i = 0; i < (m_w - 42) / 21 + ((m_w - 42) % 21 != 0); ++i )
	{
		bitmap = (CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp(bmpName[3 * m_isBasket + 2]));
		this->UIWindow::DrawBitmap(21 + 21*i, m_h - bitmap->m_height, bitmap, false);
	}

	for( int i = 0; i < (m_h - 38) / 32; ++i )
		this->UIFrameWnd::DrawItemFrame(40, 17 + 32*i);

	g_skinMgr.CSkinMgr::GetColorChipColor(2, 2, rr, gg, bb);
	this->UIWindow::DrawBox(72, 17, (m_w - 40) / 32 * 32 - 32, (m_h - 38) / 32 * 32, BYTE(rr) << 0 | BYTE(gg) << 8 | BYTE(bb) << 16);

	char moneyTxt[128];
	const NamePair& name = g_modeMgr.CModeMgr::GetGameMode()->CGameMode::GetActorName(m_aid);
	if( name.cName.size() != 0 )
	{
		sprintf(moneyTxt, "%s - %s", MsgStr(MSI_ITEM_MERCHANT_STORE), name.cName.c_str());
	}
	else
	{
		g_windowMgr.UIWindowMgr::AddToNameWaitingWindowList(this);
		sprintf(moneyTxt, "%s", MsgStr(MSI_ITEM_MERCHANT_STORE));
	}

	this->UIWindow::TextOutA(17, 3, moneyTxt, 0, 0, 12, 0xFFFFFF);
	this->UIWindow::TextOutA(16, 2, moneyTxt, 0, 0, 12, 0x000000);

	int drawCount = 0;
	int itemCount = 0;

	for( mystd::list<ITEM_INFO>::const_iterator it = m_itemList.begin(); it != m_itemList.end(); ++it )
	{
		++itemCount;

		if( itemCount <= m_itemHorzNum * m_viewOffset )
			continue; // skip entries while seeking to the part being viewed

		if( g_session.CSession::IsPetEgg(atoi(it->m_itemName.c_str())) && it->m_isDamaged )
			continue; // don't display these?

		int itemX = 32 * drawCount % m_itemHorzNum + 40;
		int itemY = 32 * drawCount / m_itemHorzNum + 17;

		if( m_curItem == itemCount )
		{
			g_skinMgr.CSkinMgr::GetColorChipColor(6, 2, rr, gg, bb);
			this->UIWindow::DrawBox(itemX + 32, itemY + 2, 191, 28, BYTE(rr) << 0 | BYTE(gg) << 8 | BYTE(bb) << 16);
		}

		this->UIFrameWnd::DrawItemWithCount(itemX + 4, itemY + 4, *it, 0, 0);

		int w = this->UIWindow::GetTextWidth("Z", 0, 0, 12, 0);
		this->UIWindow::TextOutA(m_w - w - 18, itemY + 12, "Z", 0, 0, 12, 0);

		char priceText[128];
		char buf[128];
		if( it->m_price == it->m_realPrice )
			sprintf(priceText, " %s ", GetNumberText(it->m_price, buf));
		else
			sprintf(priceText, " %d -> %s ", it->m_price, GetNumberText(it->m_realPrice, buf));

		w += this->UIWindow::GetTextWidth(priceText, 0, 0, 12, false);

		if( it->m_price >= 100000000 ) this->UIWindow::TextOutWithTwoColors(m_w - w - 18, itemY + 12, priceText, 0x64C8C8, 0x000000, 0, 0, 12);
		else
		if( it->m_price >=  10000000 ) this->UIWindow::TextOutA            (m_w - w - 18, itemY + 12, priceText, 0x000000, 0x000000, 12, 0x0000FF);
		else
		if( it->m_price >=   1000000 ) this->UIWindow::TextOutWithTwoColors(m_w - w - 18, itemY + 12, priceText, 0x00FF00, 0x000000, 0, 0, 12);
		else
		if( it->m_price >=    100000 ) this->UIWindow::TextOutA            (m_w - w - 18, itemY + 12, priceText, 0x000000, 0x000000, 12, 0xFF0000);
		else
		if( it->m_price >=     10000 ) this->UIWindow::TextOutA            (m_w - w - 18, itemY + 12, priceText, 0x000000, 0x000000, 12, 0xFF1EFF);
		else
		if( it->m_price >=      1000 ) this->UIWindow::TextOutWithTwoColors(m_w - w - 18, itemY + 12, priceText, 0x00FFFF, 0x0000FF, 0, 0, 12);
		else
		if( it->m_price >=       100 ) this->UIWindow::TextOutWithTwoColors(m_w - w - 18, itemY + 12, priceText, 0xFFFF00, 0xFF0000, 0, 0, 12);
		else
		if( it->m_price >=        10 ) this->UIWindow::TextOutWithTwoColors(m_w - w - 18, itemY + 12, priceText, 0xC800C8, 0xFF0000, 0, 0, 12);
		else
									   this->UIWindow::TextOutWithTwoColors(m_w - w - 18, itemY + 12, priceText, 0xFFFF00, 0x000000, 0, 0, 12);

		this->UIFrameWnd::DrawItemTextRect(itemX + 36, itemY + 12, m_w - w - itemX - 66, *it, 0, 0, 12);

		++drawCount;

		if( drawCount == m_itemHorzNum * m_itemVertNum )
			break; // end of view
	}
}


hook_method<void (UIMerchantItemShopWnd::*)(int x, int y, const DRAG_INFO* const dragInfo)> UIMerchantItemShopWnd::_DragAndDrop(SAKEXE, "UIMerchantItemShopWnd::DragAndDrop");
void UIMerchantItemShopWnd::DragAndDrop(int x, int y, const DRAG_INFO* const dragInfo) // line 1846
{
	return (this->*_DragAndDrop)(x, y, dragInfo);

	//TODO
}


hook_method<int (UIMerchantItemShopWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UIMerchantItemShopWnd::_SendMsg(SAKEXE, "UIMerchantItemShopWnd::SendMsg");
int UIMerchantItemShopWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3) // line 1884
{
	return (this->*_SendMsg)(sender, message, val1, val2, val3);

	switch( message )
	{
	case 34:
	{
		MerchantItemShopWndInfo* info = (MerchantItemShopWndInfo*)val1;

		m_info = info;
		if( !m_info->MerchantItemShopWndInfo::IsValidInfo() )
			m_info->MerchantItemShopWndInfo::MakeDefault();

		this->SendMsg(NULL, 14, 3, m_info->w, m_info->h);
		this->Move(m_info->x, m_info->y);
	}
	break;
	case 28:
	{
		m_aid = val1;
	}
	break;
	case 38:
	{
		CGameMode* mode = g_modeMgr.CModeMgr::GetGameMode();

		ITEM_INFO itemInfo;
		itemInfo.ITEM_INFO::CopyItemInfo(mode->CGameMode::GetDragInfo());
		g_session.CSession::DecMerchantPurchaseItem(itemInfo);

		if( g_windowMgr.UIWindowMgr::GetMerchantItemPurchaseWnd() != NULL )
			g_windowMgr.UIWindowMgr::GetMerchantItemPurchaseWnd()->SendMsg(NULL, 23, 0, 0, 0);

		this->SendMsg(NULL, 23, 0, 0, 0);
		mode->SendMsg(19, 0, 0, 0);
	}
	break;
	case 36:
	{
		m_titleText->UIStaticText::SetTextWithNewWidth(MsgStr(MSI_SHOPITEMS));
	}
	break;
	case 14:
	{
		if( val1 != RT_DOWN )
			break;

		int width = ( val2 < 232 ) ? 232 : ( val2 > 320 ) ? 320 : val2;
		int height = ( val3 < 120 ) ? 120 : ( val3 > 336 ) ? 336 : val3;

		int cx = 280 + (width - 280) / 32 * 32;
		int cy = 120 + (height - 120) / 32 * 32;

		if( cx != m_w || cy != m_h )
		{
			this->Resize(cx, cy);
			m_itemHorzNum = 1;
			m_itemVertNum = (cy - 38) / 32;
			m_resizer->Move(m_w - 15, m_h - 15);
			m_scrollBar->Move(m_w - 15, 14);
			m_scrollBar->Resize(m_scrollBar->UIWindow::GetWidth(), m_h - 38);
			this->UIItemBaseWnd::RecalcScrbarPos();
		}

		g_windowMgr.UIWindowMgr::UpdateSnapInfo(this);
	}
	break;
	case 23:
	{
		m_itemList.clear();

		int numItem = g_session.CSession::GetNumMerchantShopItem();
		for( int i = 0; i < numItem; ++i )
		{
			ITEM_INFO itemInfo = g_session.CSession::GetMerchantShopItemInfoBySequence(i);

			if( itemInfo.m_itemIndex == 0 )
				continue;

			m_itemList.push_back(itemInfo);
		}

		this->Invalidate();
		this->UIItemBaseWnd::RecalcScrbarPos();
	}
	break;
	default:
		return this->UIItemBaseWnd::SendMsg(sender, message, val1, val2, val3);
	}

	return 0;
}


hook_method<void (UIMerchantItemShopWnd::*)(void)> UIMerchantItemShopWnd::_StoreInfo(SAKEXE, "UIMerchantItemShopWnd::StoreInfo");
void UIMerchantItemShopWnd::StoreInfo(void) // line 1875
{
	return (this->*_StoreInfo)();

	if( m_info == NULL )
		return;

	m_info->x = m_x;
	m_info->y = m_y;
	m_info->w = m_w;
	m_info->h = m_h;
}


////////////////////////////////////////


UIMerchantItemPurchaseWnd::UIMerchantItemPurchaseWnd(void) // line 2452
{
	m_aid = 0;
	m_info = 0;
	m_curItem = -1;
}


UIMerchantItemPurchaseWnd::~UIMerchantItemPurchaseWnd(void) // line 2460
{
}


hook_method<void (UIMerchantItemPurchaseWnd::*)(int cx, int cy)> UIMerchantItemPurchaseWnd::_OnCreate(SAKEXE, "UIMerchantItemPurchaseWnd::OnCreate");
void UIMerchantItemPurchaseWnd::OnCreate(int cx, int cy) // line 2464
{
	return (this->*_OnCreate)(cx, cy);

	//TODO
}


hook_method<void (UIMerchantItemPurchaseWnd::*)(int x, int y)> UIMerchantItemPurchaseWnd::_OnLBtnDown(SAKEXE, "UIMerchantItemPurchaseWnd::OnLBtnDown");
void UIMerchantItemPurchaseWnd::OnLBtnDown(int x, int y) // line 2660
{
	return (this->*_OnLBtnDown)(x, y);

	//TODO
}


hook_method<void (UIMerchantItemPurchaseWnd::*)(int x, int y)> UIMerchantItemPurchaseWnd::_OnRBtnDown(SAKEXE, "UIMerchantItemPurchaseWnd::OnRBtnDown");
void UIMerchantItemPurchaseWnd::OnRBtnDown(int x, int y) // line 2687
{
	return (this->*_OnRBtnDown)(x, y);

	//TODO
}


hook_method<void (UIMerchantItemPurchaseWnd::*)(int x, int y)> UIMerchantItemPurchaseWnd::_OnMouseHover(SAKEXE, "UIMerchantItemPurchaseWnd::OnMouseHover");
void UIMerchantItemPurchaseWnd::OnMouseHover(int x, int y) // line 2699
{
	return (this->*_OnMouseHover)(x, y);

	//TODO
}


hook_method<void (UIMerchantItemPurchaseWnd::*)(void)> UIMerchantItemPurchaseWnd::_OnDraw(SAKEXE, "UIMerchantItemPurchaseWnd::OnDraw");
void UIMerchantItemPurchaseWnd::OnDraw(void) // line 2527
{
	return (this->*_OnDraw)();

	//TODO
}


hook_method<void (UIMerchantItemPurchaseWnd::*)(int x, int y, const DRAG_INFO* const dragInfo)> UIMerchantItemPurchaseWnd::_DragAndDrop(SAKEXE, "UIMerchantItemPurchaseWnd::DragAndDrop");
void UIMerchantItemPurchaseWnd::DragAndDrop(int x, int y, const DRAG_INFO* const dragInfo) // line 2719
{
	return (this->*_DragAndDrop)(x, y, dragInfo);

	//TODO
}


hook_method<int (UIMerchantItemPurchaseWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UIMerchantItemPurchaseWnd::_SendMsg(SAKEXE, "UIMerchantItemPurchaseWnd::SendMsg");
int UIMerchantItemPurchaseWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3) // line 2768
{
	return (this->*_SendMsg)(sender, message, val1, val2, val3);

	//TODO
}


hook_method<void (UIMerchantItemPurchaseWnd::*)(void)> UIMerchantItemPurchaseWnd::_StoreInfo(SAKEXE, "UIMerchantItemPurchaseWnd::StoreInfo");
void UIMerchantItemPurchaseWnd::StoreInfo(void) // line 2759
{
	return (this->*_StoreInfo)();

	//TODO
}


////////////////////////////////////////


UIMerchantItemWnd::UIMerchantItemWnd(void) // line 3375
{
	m_info = NULL;
}


UIMerchantItemWnd::~UIMerchantItemWnd(void) // line 3381
{
}


////////////////////////////////////////


UIItemWnd::UIItemWnd(void) // line 3854
{
	m_curRadioBtn[0] = NULL;
	m_curRadioBtn[1] = NULL;
	m_curRadioBtn[2] = NULL;
	m_curTab = 0;
	m_info = NULL;
}


UIItemWnd::~UIItemWnd(void) // line 3868
{
}


hook_method<bool (UIItemWnd::*)(void)> UIItemWnd::_IsUpdateNeed(SAKEXE, "UIItemWnd::IsUpdateNeed");
bool UIItemWnd::IsUpdateNeed(void) // line 584 (UIFrameWnd.h)
{
	return (this->*_IsUpdateNeed)();

	//TODO
}


hook_method<void (UIItemWnd::*)(int cx, int cy)> UIItemWnd::_OnCreate(SAKEXE, "UIItemWnd::OnCreate");
void UIItemWnd::OnCreate(int cx, int cy) // line 3872
{
	return (this->*_OnCreate)(cx, cy);

	//TODO
}


hook_method<void (UIItemWnd::*)(void)> UIItemWnd::_OnDestroy(SAKEXE, "UIItemWnd::OnDestroy");
void UIItemWnd::OnDestroy(void) // line 3921
{
	return (this->*_OnDestroy)();

	//TODO
}


hook_method<void (UIItemWnd::*)(void)> UIItemWnd::_OnDraw(SAKEXE, "UIItemWnd::OnDraw");
void UIItemWnd::OnDraw(void) // line 3924
{
	return (this->*_OnDraw)();

	//TODO
}


hook_method<void (UIItemWnd::*)(int x, int y)> UIItemWnd::_OnLBtnDblClk(SAKEXE, "UIItemWnd::OnLBtnDblClk");
void UIItemWnd::OnLBtnDblClk(int x, int y) // line 4097
{
	return (this->*_OnLBtnDblClk)(x, y);

	//TODO
}


hook_method<void (UIItemWnd::*)(int x, int y)> UIItemWnd::_OnLBtnDown(SAKEXE, "UIItemWnd::OnLBtnDown");
void UIItemWnd::OnLBtnDown(int x, int y) // line 4072
{
	return (this->*_OnLBtnDown)(x, y);

	//TODO
}


hook_method<void (UIItemWnd::*)(int x, int y)> UIItemWnd::_OnRBtnDown(SAKEXE, "UIItemWnd::OnRBtnDown");
void UIItemWnd::OnRBtnDown(int x, int y) // line 4085
{
	return (this->*_OnRBtnDown)(x, y);

	//TODO
}


hook_method<void (UIItemWnd::*)(int x, int y)> UIItemWnd::_OnMouseHover(SAKEXE, "UIItemWnd::OnMouseHover");
void UIItemWnd::OnMouseHover(int x, int y) // line 4143
{
	return (this->*_OnMouseHover)(x, y);

	//TODO
}


hook_method<int (UIItemWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UIItemWnd::_SendMsg(SAKEXE, "UIItemWnd::SendMsg");
int UIItemWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3) // line 4183
{
	return (this->*_SendMsg)(sender, message, val1, val2, val3);

	//TODO
}


hook_method<void (UIItemWnd::*)(int x, int y, const DRAG_INFO* const dragInfo)> UIItemWnd::_DragAndDrop(SAKEXE, "UIItemWnd::DragAndDrop");
void UIItemWnd::DragAndDrop(int x, int y, const DRAG_INFO* const dragInfo) // line 4454
{
	return (this->*_DragAndDrop)(x, y, dragInfo);

	//TODO
}


hook_method<void (UIItemWnd::*)(void)> UIItemWnd::_StoreInfo(SAKEXE, "UIItemWnd::StoreInfo");
void UIItemWnd::StoreInfo(void) // line 4169
{
	return (this->*_StoreInfo)();

	//TODO
}


hook_method<bool (UIItemWnd::*)(const ITEM_INFO* const itemInfo)> UIItemWnd::_Sort(SAKEXE, "UIItemWnd::Sort");
bool UIItemWnd::Sort(const ITEM_INFO* const itemInfo) // line 4370
{
	return (this->*_Sort)(itemInfo);

	//TODO
}


hook_method<void (UIItemWnd::*)(void)> UIItemWnd::_RefreshRadioBtn(SAKEXE, "UIItemWnd::RefreshRadioBtn");
void UIItemWnd::RefreshRadioBtn(void) // line 4164
{
	return (this->*_RefreshRadioBtn)();

	//TODO
}


hook_method<ITEM_INFO (UIItemWnd::*)(int x, int y)> UIItemWnd::_GetItemInfo(SAKEXE, "UIItemWnd::GetItemInfo");
ITEM_INFO UIItemWnd::GetItemInfo(int x, int y) // line 4036
{
	return (this->*_GetItemInfo)(x, y);

	//TODO
}


////////////////////////////////////////


UIItemStoreWnd::UIItemStoreWnd(void) // line 4497
{
	m_resizer = NULL;
	m_scrollBar = NULL;
	m_viewOffset = 0;
	m_vertScrEnabled = 0;
	m_button[0] = NULL;
	m_button[1] = NULL;
	m_curRadioBtn[0] = NULL;
	m_curRadioBtn[1] = NULL;
	m_curRadioBtn[2] = NULL;
	m_curTab = 0;
	m_drawNumItem = 1;
	m_isBasket = 1;
	m_info = NULL;
}


////////////////////////////////////////


UISkillListWnd::UISkillListWnd(void) // line 5045
{
	m_button[0] = NULL;
	m_button[1] = NULL;
	m_info = NULL;
	m_curItem = -1;
	m_itemHorzNum = 1;
}


UISkillListWnd::~UISkillListWnd(void) // line N/A
{
}


hook_method<void (UISkillListWnd::*)(int cx, int cy)> UISkillListWnd::_OnCreate(SAKEXE, "UISkillListWnd::OnCreate");
void UISkillListWnd::OnCreate(int cx, int cy) // line 5058
{
	return (this->*_OnCreate)(cx, cy);

	//TODO
}


hook_method<void (UISkillListWnd::*)(void)> UISkillListWnd::_OnDraw(SAKEXE, "UISkillListWnd::OnDraw");
void UISkillListWnd::OnDraw(void) // line 5187
{
	return (this->*_OnDraw)();

	//TODO
}


hook_method<void (UISkillListWnd::*)(int x, int y)> UISkillListWnd::_OnLBtnDown(SAKEXE, "UISkillListWnd::OnLBtnDown");
void UISkillListWnd::OnLBtnDown(int x, int y) // line 5486
{
	return (this->*_OnLBtnDown)(x, y);

	//TODO
}


hook_method<void (UISkillListWnd::*)(int x, int y)> UISkillListWnd::_OnLBtnDblClk(SAKEXE, "UISkillListWnd::OnLBtnDblClk");
void UISkillListWnd::OnLBtnDblClk(int x, int y) // line 5469
{
	return (this->*_OnLBtnDblClk)(x, y);

	//TODO
}


hook_method<void (UISkillListWnd::*)(int x, int y)> UISkillListWnd::_OnRBtnDown(SAKEXE, "UISkillListWnd::OnRBtnDown");
void UISkillListWnd::OnRBtnDown(int x, int y) // line 5506
{
	return (this->*_OnRBtnDown)(x, y);

	//TODO
}


hook_method<void (UISkillListWnd::*)(int x, int y)> UISkillListWnd::_OnRBtnUp(SAKEXE, "UISkillListWnd::OnRBtnUp");
void UISkillListWnd::OnRBtnUp(int x, int y) // line 5521
{
	return (this->*_OnRBtnUp)(x, y);

	//TODO
}


hook_method<void (UISkillListWnd::*)(int x, int y)> UISkillListWnd::_OnMouseHover(SAKEXE, "UISkillListWnd::OnMouseHover");
void UISkillListWnd::OnMouseHover(int x, int y) // line 5526
{
	return (this->*_OnMouseHover)(x, y);

	//TODO
}


hook_method<int (UISkillListWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UISkillListWnd::_SendMsg(SAKEXE, "UISkillListWnd::SendMsg");
int UISkillListWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3) // line 5539
{
	return (this->*_SendMsg)(sender, message, val1, val2, val3);

	//TODO
}


hook_method<void (UISkillListWnd::*)(void)> UISkillListWnd::_StoreInfo(SAKEXE, "UISkillListWnd::StoreInfo");
void UISkillListWnd::StoreInfo(void) // line 5530
{
	return (this->*_StoreInfo)();

	//TODO
}


hook_method<void (UISkillListWnd::*)(int wheel)> UISkillListWnd::_OnWheel(SAKEXE, "UISkillListWnd::OnWheel");
void UISkillListWnd::OnWheel(int wheel) // line 5834
{
	return (this->*_OnWheel)(wheel);

	//TODO
}


hook_method<bool (UISkillListWnd::*)(void)> UISkillListWnd::_IsUpdateNeed(SAKEXE, "UISkillListWnd::IsUpdateNeed");
bool UISkillListWnd::IsUpdateNeed(void) // line 435 (UIFrameWnd.h)
{
	return (this->*_IsUpdateNeed)();

	//TODO
}


hook_method<void (UISkillListWnd::*)(void)> UISkillListWnd::_RecalcScrbarPos(SAKEXE, "UISkillListWnd::RecalcScrbarPos");
void UISkillListWnd::RecalcScrbarPos(void) // line 5847
{
	return (this->*_RecalcScrbarPos)();

	//TODO
}


hook_method<void (UISkillListWnd::*)(void)> UISkillListWnd::_RefreshButton(SAKEXE, "UISkillListWnd::RefreshButton");
void UISkillListWnd::RefreshButton(void) // line 5167
{
	return (this->*_RefreshButton)();

	//TODO
}


hook_method<SKILL_INFO (UISkillListWnd::*)(int viewCnt)> UISkillListWnd::_GetSkillInfoByViewCnt(SAKEXE, "UISkillListWnd::GetSkillInfoByViewCnt");
SKILL_INFO UISkillListWnd::GetSkillInfoByViewCnt(int viewCnt) // line 5380
{
	return (this->*_GetSkillInfoByViewCnt)(viewCnt);

	//TODO
}


hook_method<SKILL_INFO (UISkillListWnd::*)(int curItem)> UISkillListWnd::_GetSkillInfo(SAKEXE, "?GetSkillInfo@UISkillListWnd@@IAE?AUSKILL_INFO@@H@Z");
SKILL_INFO UISkillListWnd::GetSkillInfo(int curItem) // line 5453
{
	return (this->*_GetSkillInfo)(curItem);

	//TODO
}


hook_method<SKILL_INFO (UISkillListWnd::*)(int x, int drawCount)> UISkillListWnd::_GetSkillInfo2(SAKEXE, "?GetSkillInfo@UISkillListWnd@@IAE?AUSKILL_INFO@@HH@Z");
SKILL_INFO UISkillListWnd::GetSkillInfo(int x, int drawCount) // line 5395
{
	return (this->*_GetSkillInfo2)(x, drawCount);

	//TODO
}


hook_method<int (UISkillListWnd::*)(int x, int y)> UISkillListWnd::_GetCurItem(SAKEXE, "UISkillListWnd::GetCurItem");
int UISkillListWnd::GetCurItem(int x, int y) // line 5424
{
	return (this->*_GetCurItem)(x, y);

	//TODO
}


////////////////////////////////////////
