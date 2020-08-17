#include "Globals.h"
#include "Insult.h"
#include "Mode.h"
#include "ModeMgr.h"
#include "MsgStrings.h"
#include "Base/ResMgr.h"
#include "Resource/ImfRes.h"
#include "Resource/PaletteRes.h"
#include "Resource/Wave.h"
#include "Window/UIChatHisBox.h"
#include "Window/UIControl.h"
#include "Window/UIFrameWnd.h"
#include "Window/UISlotBitmap.h"
#include "Window/UISys.h"
#include <ShellAPI.h>


UIFrameWnd::UIFrameWnd(void) // line 35
{
	m_defPushId = 93;
	m_defCancelPushId = 93;
	m_startGlobalX = 0;
	m_startGlobalY = 0;
}


UIFrameWnd::~UIFrameWnd(void) // line 43
{
}


hook_method<void (UIFrameWnd::*)(int x, int y)> UIFrameWnd::_OnLBtnDown(SAKEXE, "UIFrameWnd::OnLBtnDown");
void UIFrameWnd::OnLBtnDown(int x, int y) // line 64
{
	return (this->*_OnLBtnDown)(x, y);

	g_windowMgr.UIWindowMgr::SetCapture(this);
	int gx = x;
	int gy = y;
	this->UIWindow::GetGlobalCoor(gx, gy);
	m_startGlobalX = gx;
	m_startGlobalY = gy;
	m_orgX = m_x;
	m_orgY = m_y;
	m_transTarget = 128;
	m_transTime = timeGetTime();
	g_snapMgr.CSnapMgr::BeginMove(this);
}


hook_method<void (UIFrameWnd::*)(int x, int y)> UIFrameWnd::_OnMouseMove(SAKEXE, "UIFrameWnd::OnMouseMove");
void UIFrameWnd::OnMouseMove(int x, int y) // line 96
{
	return (this->*_OnMouseMove)(x, y);

	//TODO
}


hook_method<void (UIFrameWnd::*)(int x, int y)> UIFrameWnd::_OnMouseHover(SAKEXE, "UIFrameWnd::OnMouseHover");
void UIFrameWnd::OnMouseHover(int x, int y) // line 93
{
	return (this->*_OnMouseHover)(x, y);

	;
}


hook_method<void (UIFrameWnd::*)(int x, int y)> UIFrameWnd::_OnLBtnUp(SAKEXE, "UIFrameWnd::OnLBtnUp");
void UIFrameWnd::OnLBtnUp(int x, int y) // line 134
{
	return (this->*_OnLBtnUp)(x, y);

	if( this == g_windowMgr.UIWindowMgr::GetCapture() )
	{
		m_transTarget = 255;
		m_transTime = timeGetTime();
		g_windowMgr.UIWindowMgr::ReleaseCapture();
		g_snapMgr.CSnapMgr::EndMove(this);
	}
}


hook_method<int (UIFrameWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UIFrameWnd::_SendMsg(SAKEXE, "UIFrameWnd::SendMsg");
int UIFrameWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3) // line 144
{
	return (this->*_SendMsg)(sender, message, val1, val2, val3);

	//TODO
}


hook_method<void (UIFrameWnd::*)(int x, int y)> UIFrameWnd::_Move(SAKEXE, "UIFrameWnd::Move");
void UIFrameWnd::Move(int x, int y) // line 57
{
	return (this->*_Move)(x, y);

	m_x = x;
	m_y = y;
	this->RefreshSnap();
}


hook_method<bool (UIFrameWnd::*)(void)> UIFrameWnd::_IsFrameWnd(SAKEXE, "UIFrameWnd::IsFrameWnd");
bool UIFrameWnd::IsFrameWnd(void) // line 90 (UIFrameWnd.h)
{
	return (this->*_IsFrameWnd)();

	return true;
}


hook_method<void (UIFrameWnd::*)(void)> UIFrameWnd::_SaveOriginalPos(SAKEXE, "UIFrameWnd::SaveOriginalPos");
void UIFrameWnd::SaveOriginalPos(void) // line 80
{
	return (this->*_SaveOriginalPos)();

	m_orgX = m_x;
	m_orgY = m_y;
}


hook_method<void (UIFrameWnd::*)(int deltaDragX, int deltaDragY)> UIFrameWnd::_MoveDelta(SAKEXE, "UIFrameWnd::MoveDelta");
void UIFrameWnd::MoveDelta(int deltaDragX, int deltaDragY) // line 85
{
	return (this->*_MoveDelta)(deltaDragX, deltaDragY);

	m_x = deltaDragX + m_orgX;
	m_y = deltaDragY + m_orgY;
}


hook_method<void (UIFrameWnd::*)(void)> UIFrameWnd::_RefreshSnap(SAKEXE, "UIFrameWnd::RefreshSnap");
void UIFrameWnd::RefreshSnap(void) // line 47
{
	return (this->*_RefreshSnap)();

	//TODO
}


hook_method<void (UIFrameWnd::*)(int x, int y, const ITEM_INFO& iteminfo, bool forceidentified)> UIFrameWnd::_DrawItem(SAKEXE, "?DrawItem@UIFrameWnd@@IAEXHHABUITEM_INFO@@_N@Z");
void UIFrameWnd::DrawItem(int x, int y, const ITEM_INFO& iteminfo, bool forceidentified)
{
	return (this->*_DrawItem)(x, y, iteminfo, forceidentified);

	//TODO
}


hook_method<void (UIFrameWnd::*)(int x, int y, const char* itemName, bool identified)> UIFrameWnd::_DrawItem2(SAKEXE, "?DrawItem@UIFrameWnd@@IAEXHHPBD_N@Z");
void UIFrameWnd::DrawItem(int x, int y, const char* itemName, bool identified)
{
	return (this->*_DrawItem2)(x, y, itemName, identified);

	//TODO
}


hook_method<void (UIFrameWnd::*)(int x, int y, const ITEM_INFO& iteminfo, bool forceidentified, bool boldtext)> UIFrameWnd::_DrawItemWithCount(SAKEXE, "UIFrameWnd::DrawItemWithCount");
void UIFrameWnd::DrawItemWithCount(int x, int y, const ITEM_INFO& iteminfo, bool forceidentified, bool boldtext) // line 182
{
	return (this->*_DrawItemWithCount)(x, y, iteminfo, forceidentified, boldtext);

	//TODO
}


hook_method<void (UIFrameWnd::*)(int x, int y)> UIFrameWnd::_DrawItemFrame(SAKEXE, "UIFrameWnd::DrawItemFrame");
void UIFrameWnd::DrawItemFrame(int x, int y)
{
	return (this->*_DrawItemFrame)(x, y);

	CBitmapRes* bitmap = (CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp("유저인터페이스\\basic_interface\\itemwin_mid.bmp"));
	this->UIWindow::DrawBitmap(x, y, bitmap, 0);
}


hook_method<void (UIFrameWnd::*)(int x, int y, int width, int height)> UIFrameWnd::_DrawLatticeFrame(SAKEXE, "UIFrameWnd::DrawLatticeFrame");
void UIFrameWnd::DrawLatticeFrame(int x, int y, int width, int height) // line 206
{
	return (this->*_DrawLatticeFrame)(x, y, width, height);

	//TODO
}


hook_method<int (UIFrameWnd::*)(int x, int y, const ITEM_INFO& iteminfo, unsigned long color, int fontType, int fontHeight)> UIFrameWnd::_DrawItemText(SAKEXE, "UIFrameWnd::DrawItemText");
int UIFrameWnd::DrawItemText(int x, int y, const ITEM_INFO& iteminfo, unsigned long color, int fontType, int fontHeight)
{
	return (this->*_DrawItemText)(x, y, iteminfo, color, fontType, fontHeight);

	//TODO
}


hook_method<int (UIFrameWnd::*)(int x, int y, int width, const ITEM_INFO& iteminfo, unsigned long color, int fontType, int fontHeight)> UIFrameWnd::_DrawItemTextRect(SAKEXE, "UIFrameWnd::DrawItemTextRect");
int UIFrameWnd::DrawItemTextRect(int x, int y, int width, const ITEM_INFO& iteminfo, unsigned long color, int fontType, int fontHeight)
{
	return (this->*_DrawItemTextRect)(x, y, width, iteminfo, color, fontType, fontHeight);

	//TODO
}


hook_method<int (UIFrameWnd::*)(int x, int y, int width, const ITEM_INFO& iteminfo, unsigned long color, int fontType, int fontHeight)> UIFrameWnd::_DrawItemObtainTextRect(SAKEXE, "UIFrameWnd::DrawItemObtainTextRect");
int UIFrameWnd::DrawItemObtainTextRect(int x, int y, int width, const ITEM_INFO& iteminfo, unsigned long color, int fontType, int fontHeight)
{
	return (this->*_DrawItemObtainTextRect)(x, y, width, iteminfo, color, fontType, fontHeight);

	//TODO
}


////////////////////////////////////////


UISelectServerWnd::UISelectServerWnd(void) // line 577
{
	m_serverList = 0;
	m_exitButton = 0;
}


UISelectServerWnd::~UISelectServerWnd(void) // line 583
{
}


hook_method<void (UISelectServerWnd::*)(int cx, int cy)> UISelectServerWnd::_OnCreate(SAKEXE, "UISelectServerWnd::OnCreate");
void UISelectServerWnd::OnCreate(int cx, int cy) // line 630
{
	return (this->*_OnCreate)(cx, cy);

	//TODO
}


hook_method<void (UISelectServerWnd::*)(void)> UISelectServerWnd::_OnDestroy(SAKEXE, "UISelectServerWnd::OnDestroy");
void UISelectServerWnd::OnDestroy(void) // line 671
{
	return (this->*_OnDestroy)();

	;
}


hook_method<void (UISelectServerWnd::*)(void)> UISelectServerWnd::_OnDraw(SAKEXE, "UISelectServerWnd::OnDraw");
void UISelectServerWnd::OnDraw(void) // line 674
{
	return (this->*_OnDraw)();

	//TODO
}


hook_method<int (UISelectServerWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UISelectServerWnd::_SendMsg(SAKEXE, "UISelectServerWnd::SendMsg");
int UISelectServerWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3) // line 715
{
	return (this->*_SendMsg)(sender, message, val1, val2, val3);

	//TODO
}


hook_method<void (UISelectServerWnd::*)(const char* regkey)> UISelectServerWnd::_InitDefaultCurItemFromReg(SAKEXE, "UISelectServerWnd::InitDefaultCurItemFromReg");
void UISelectServerWnd::InitDefaultCurItemFromReg(const char* regkey) // line 587
{
	return (this->*_InitDefaultCurItemFromReg)(regkey);

	m_defaultCurItem = g_serviceType;

	HKEY hResultKey;
	if( RegOpenKeyExA(HKEY_LOCAL_MACHINE, g_regPath, 0, KEY_QUERY_VALUE, &hResultKey) != ERROR_SUCCESS )
		return;
	RegCloseKey(hResultKey);
	HKEY hKey;
	if( RegOpenKeyExA(HKEY_LOCAL_MACHINE, g_regPath, 0, KEY_QUERY_VALUE, &hKey) != ERROR_SUCCESS )
		return;
	DWORD REG_TYPE = REG_DWORD;
	DWORD DATALENGTH = 4;
	RegQueryValueExA(hKey, regkey, NULL, &REG_TYPE, (BYTE*)&m_defaultCurItem, &DATALENGTH);
	RegCloseKey(hKey);
}


hook_method<void (UISelectServerWnd::*)(const char* regkey)> UISelectServerWnd::_SaveCurItemToReg(SAKEXE, "UISelectServerWnd::SaveCurItemToReg");
void UISelectServerWnd::SaveCurItemToReg(const char* regkey) // line 611
{
	return (this->*_SaveCurItemToReg)(regkey);

	m_defaultCurItem = m_serverList->UIListBox::GetSelected();

	HKEY hKey;
	DWORD dwDisposition = 0;
	if( RegCreateKeyExA(HKEY_LOCAL_MACHINE, g_regPath, 0, NULL, 0, KEY_ALL_ACCESS, NULL, &hKey, &dwDisposition) != ERROR_SUCCESS )
		return;
	RegSetValueExA(hKey, regkey, 0, REG_DWORD, (const BYTE*)&m_defaultCurItem, 4);
	RegCloseKey(hKey);
}


////////////////////////////////////////


UILoginWnd::UILoginWnd(void) // line 771
{
	m_login = NULL;
	m_password = NULL;
	m_cancelButton = NULL;
	m_isCheckOn = 0;
}


UILoginWnd::~UILoginWnd(void) // line 780
{
}


hook_method<void (UILoginWnd::*)(int cx, int cy)> UILoginWnd::_OnCreate(SAKEXE, "UILoginWnd::OnCreate");
void UILoginWnd::OnCreate(int cx, int cy) // line 783
{
	return (this->*_OnCreate)(cx, cy);

	//TODO
}


hook_method<void (UILoginWnd::*)(void)> UILoginWnd::_OnDestroy(SAKEXE, "UILoginWnd::OnDestroy");
void UILoginWnd::OnDestroy(void) // line 972
{
	return (this->*_OnDestroy)();

	//TODO
}


hook_method<void (UILoginWnd::*)(void)> UILoginWnd::_OnDraw(SAKEXE, "UILoginWnd::OnDraw");
void UILoginWnd::OnDraw(void) // line 975
{
	return (this->*_OnDraw)();

	//TODO
}


hook_method<int (UILoginWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UILoginWnd::_SendMsg(SAKEXE, "UILoginWnd::SendMsg");
int UILoginWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3) // line 988
{
	return (this->*_SendMsg)(sender, message, val1, val2, val3);

	switch( message )
	{
	case UM_DEFPUSH:
		if( m_defPushId != 0 )
			this->SendMsg(this, UM_COMMAND, m_defPushId, 0, 0);
		return 0;
	break;
	case UM_CANCELPUSH:
		if( m_defCancelPushId != 0 )
			this->SendMsg(this, UM_COMMAND, m_defCancelPushId, 0, 0);
		return 0;
	break;
	case UM_COMMAND:
		switch( val1 )
		{
		case 176:
			if( g_serviceType )
			{
				g_modeMgr.CModeMgr::Quit();
				ShellExecuteA(g_hMainWnd, "open", g_regstrationWeb, 0, 0, 1);
			}
			else
			if( g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(MSI_3DAY_FREE), 2, 1, 0, 0) == 97 )
			{
				g_modeMgr.CModeMgr::Quit();
				ShellExecuteA(g_hMainWnd, "open", g_regstrationWeb, 0, 0, 1);
			}
		break;
		case 96:
			PlayWave("버튼소리.wav", 0.0, 0.0, 0.0, 250, 40, 1.0);

			if( m_password->UIEditCtrl::GetTextSize() < 4 || m_login->UIEditCtrl::GetTextSize() < 4 )
			{
				g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(MSI_NAME_MUST_EXCEED_4_CHAR), 0, 1, 0, 0);
				break;
			}

			g_modeMgr.CModeMgr::GetCurMode()->SendMsg(LMM_PASSWORD, (int)m_password->UIEditCtrl::GetText(), 0, 0);
			g_modeMgr.CModeMgr::GetCurMode()->SendMsg(LMM_ID, (int)m_login->UIEditCtrl::GetText(), 0, 0);
			g_modeMgr.CModeMgr::GetCurMode()->SendMsg(LMM_CONNECT_TO_ACSVR, 0, 0, 0);
			g_windowMgr.UIWindowMgr::PostQuit(this);
			this->UILoginWnd::WriteToReg();
		break;
		case 95:
			g_modeMgr.CModeMgr::GetCurMode()->SendMsg(LMM_GOTOSELECTACCOUNT, 0, 0, 0);
		break;
		case 131:
			this->UILoginWnd::WriteToReg();
			if( g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(MSI_DO_YOU_REALLY_WANT_TO_QUIT), 2, 1, 0, 0) == 97 )
			{
				g_modeMgr.CModeMgr::GetCurMode()->SendMsg(MM_QUIT, 0, 0, 0);
				g_windowMgr.UIWindowMgr::PostQuit(this);
			}
		break;
		case 123:
			m_isCheckOn = val2;
			this->UILoginWnd::WriteToReg();
		break;
		case 194:
			g_Bink.CBink::OpenningMain(0);
		break;
		default:
		break;
		}
		return 0;
	break;
	case UM_ENABLE_CANCEL:
		m_cancelButton->Move(234, 96);
		return 0;
	break;
	default:
		return this->UIWindow::SendMsg(sender, message, val1, val2, val3);
	break;
	}
}


hook_method<void (UILoginWnd::*)(void)> UILoginWnd::_StoreInfo(SAKEXE, "UILoginWnd::StoreInfo");
void UILoginWnd::StoreInfo(void) // line 866
{
	return (this->*_StoreInfo)();

	//TODO
}


hook_method<void (UILoginWnd::*)(void)> UILoginWnd::_InitFromReg(SAKEXE, "UILoginWnd::InitFromReg");
void UILoginWnd::InitFromReg(void) // line 870
{
	return (this->*_InitFromReg)();

	//TODO
}


hook_method<void (UILoginWnd::*)(void)> UILoginWnd::_WriteToReg(SAKEXE, "UILoginWnd::WriteToReg");
void UILoginWnd::WriteToReg(void) // line 929
{
	return (this->*_WriteToReg)();

	//TODO
}


hook_method<void (UILoginWnd::*)(void)> UILoginWnd::_OpenRegistPage(SAKEXE, "UILoginWnd::OpenRegistPage");
void UILoginWnd::OpenRegistPage(void) // line 984
{
	return (this->*_OpenRegistPage)();

	//TODO
}


////////////////////////////////////////


UINoticeWnd::UINoticeWnd(void) // line 1058
{
	for( int i = 0; i < 20; ++i )
		m_NoticeMessage[i] = new UIStaticText();

	m_NoticeTotalLine = 20;
	m_NoticeDisplayLine = 0;
	m_TotalPage = 0;
	m_PresentPage = 0;
	m_PageStartLine[0] = 0;
	m_PageLastLine[0] = 0;
	m_PagePresentLine = 0;

	g_windowMgr.UIWindowMgr::SetFocusEdit(this);
}


UINoticeWnd::~UINoticeWnd(void) // line 1077
{
}


hook_method<void (UINoticeWnd::*)(int cx, int cy)> UINoticeWnd::_OnCreate(SAKEXE, "UINoticeWnd::OnCreate");
void UINoticeWnd::OnCreate(int cx, int cy) // line 1080
{
	return (this->*_OnCreate)(cx, cy);

	//TODO
}


hook_method<void (UINoticeWnd::*)(void)> UINoticeWnd::_OnDestroy(SAKEXE, "UINoticeWnd::OnDestroy");
void UINoticeWnd::OnDestroy(void) // line 1320
{
	return (this->*_OnDestroy)();

	//TODO
}


hook_method<void (UINoticeWnd::*)(void)> UINoticeWnd::_OnDraw(SAKEXE, "UINoticeWnd::OnDraw");
void UINoticeWnd::OnDraw(void) // line 1327
{
	return (this->*_OnDraw)();

	//TODO
}


hook_method<void (UINoticeWnd::*)(int wheel)> UINoticeWnd::_OnWheel(SAKEXE, "UINoticeWnd::OnWheel");
void UINoticeWnd::OnWheel(int wheel) // line 1406
{
	return (this->*_OnWheel)(wheel);

	//TODO
}


hook_method<void (UINoticeWnd::*)(int x, int y)> UINoticeWnd::_OnMouseHover(SAKEXE, "UINoticeWnd::OnMouseHover");
void UINoticeWnd::OnMouseHover(int x, int y) // line 1324
{
	return (this->*_OnMouseHover)(x, y);

	//TODO
}


hook_method<int (UINoticeWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UINoticeWnd::_SendMsg(SAKEXE, "UINoticeWnd::SendMsg");
int UINoticeWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3) // line 1415
{
	return (this->*_SendMsg)(sender, message, val1, val2, val3);

	//TODO
}


hook_method<void (UINoticeWnd::*)(void)> UINoticeWnd::_PrintNotice(SAKEXE, "UINoticeWnd::PrintNotice");
void UINoticeWnd::PrintNotice(void) // line 1514
{
	return (this->*_PrintNotice)();

	//TODO
}


////////////////////////////////////////


UIMakeCharWnd::UIMakeCharWnd(void) // line 2333
{
	m_stateCnt = 0;
	m_nameEditCtrl = 0;

	int(& param)[8] = *(int(*)[8])g_modeMgr.CModeMgr::GetCurMode()->SendMsg(10016, 0, 0, 0);
	m_charInfo.Str = param[0];
	m_charInfo.Agi = param[1];
	m_charInfo.Vit = param[2];
	m_charInfo.Int = param[3];
	m_charInfo.Dex = param[4];
	m_charInfo.Luk = param[5];
	m_charInfo.headpalette = param[6];
	m_charInfo.head = param[7];
	m_charInfo.level = 1;
	m_charInfo.sppoint = 1;
	m_charInfo.name[0] = '\0';
	m_charInfo.job = 0;
	m_charInfo.jobpoint = 0;
	m_charInfo.maxhp = 100;
	m_charInfo.hp = 100;
	m_charInfo.maxsp = 100;
	m_charInfo.sp = 100;
	m_charInfo.exp = 0;
	m_charInfo.CharNum = g_charInfo.CharNum;
	m_charInfo.bodypalette = 0;
	m_charInfo.shield = 0;
	m_charInfo.accessory2 = 0;
	m_charInfo.accessory3 = 0;
	m_charInfo.headpalette = 0;
	m_viewChar.x = 95;
	m_viewChar.y = 213;
	m_viewChar.baseAction = 0;
	m_viewChar.curAction = 0;
	m_viewChar.curMotion = 0;

	char buf[256];
	char buf2[64];

	m_viewChar.actName[0] = g_session.CSession::GetJobActName(m_charInfo.job, g_session.CSession::GetSex(), buf);
	m_viewChar.sprName[0] = g_session.CSession::GetJobSprName(m_charInfo.job, g_session.CSession::GetSex(), buf);

	if( g_session.CSession::GetSex() == 1 )
		if( m_charInfo.head == 13 )
			m_charInfo.head = 14;

	int head = m_charInfo.head;
	m_viewChar.actName[1] = g_session.CSession::GetHeadActName(m_charInfo.job, head, g_session.CSession::GetSex(), buf);
	m_viewChar.sprName[1] = g_session.CSession::GetHeadSprName(m_charInfo.job, head, g_session.CSession::GetSex(), buf);
	m_charInfo.head = head;

	m_viewChar.bodyPalette = m_charInfo.bodypalette;
	if( m_viewChar.bodyPalette != 0 )
		m_viewChar.bodyPaletteName = g_session.CSession::GetBodyPaletteName(m_charInfo.job, g_session.CSession::GetSex(), m_charInfo.bodypalette, buf2);

	m_viewChar.headPalette = m_charInfo.headpalette;
	if( m_viewChar.headPalette != 0 )
		m_viewChar.headPaletteName = g_session.CSession::GetHeadPaletteName(head, m_charInfo.job, g_session.CSession::GetSex(), m_charInfo.headpalette, buf2);

	m_viewChar.imfName = g_session.CSession::GetImfName(m_charInfo.job, m_charInfo.head, g_session.CSession::GetSex(), buf);
}


UIMakeCharWnd::~UIMakeCharWnd(void) // line 2413
{
}


hook_method<void (UIMakeCharWnd::*)(int cx, int cy)> UIMakeCharWnd::_OnCreate(SERVER, "UIMakeCharWnd::OnCreate");
void UIMakeCharWnd::OnCreate(int cx, int cy) // line 2417
{
	return (this->*_OnCreate)(cx, cy);

	int i;

	g_modeMgr.CModeMgr::GetCurMode()->SendMsg(0x271E, 0, 0, 0);
	m_nameEditCtrl = new UIBitmapEditCtrl();
	m_nameEditCtrl->UIBitmapEditCtrl::SetBitmap("유저인터페이스\\login_interface\\name-edit.bmp");
	m_nameEditCtrl->UIWindow::Create(m_nameEditCtrl->UIWindow::GetWidth(), m_nameEditCtrl->UIWindow::GetHeight());
	m_nameEditCtrl->Move(62, 244);
	m_nameEditCtrl->UIEditCtrl::SetTextLimit(24);
	m_nameEditCtrl->UIWindow::SetId(94);
	this->UIWindow::AddChild(m_nameEditCtrl);
	this->UIMakeCharWnd::MakeButton();
	for( i = 0; i < 6; ++i )
	{
		m_text[i] = new UIStaticText();
		m_text[i]->UIStaticText::SetText("", 0);
		m_text[i]->UIWindow::Move(144 * (i / 6) + 489, 16 * (i % 6) + 42);
		this->UIWindow::AddChild(m_text[i]);
	}
	this->UIMakeCharWnd::InitTextControls();
	g_windowMgr.UIWindowMgr::SetFocusEdit(m_nameEditCtrl);
	m_defPushId = 94;
}


hook_method<void (UIMakeCharWnd::*)(void)> UIMakeCharWnd::_OnProcess(SERVER, "UIMakeCharWnd::OnProcess");
void UIMakeCharWnd::OnProcess(void) // line 2449
{
	return (this->*_OnProcess)();

	if( m_stateCnt % 34 )
		m_viewChar.curMotion = 0;
	else
	{
		this->Invalidate();
		m_viewChar.curMotion = 0;
		++m_viewChar.curAction;
		if( m_viewChar.curAction >= m_viewChar.baseAction + 8 )
			m_viewChar.curAction = m_viewChar.baseAction;
	}
	++m_stateCnt;
}


hook_method<void (UIMakeCharWnd::*)(void)> UIMakeCharWnd::_OnDestroy(SERVER, "UIMakeCharWnd::OnDestroy");
void UIMakeCharWnd::OnDestroy(void) // line 2464
{
	return (this->*_OnDestroy)();

	;
}


hook_method<void (UIMakeCharWnd::*)(void)> UIMakeCharWnd::_OnDraw(SERVER, "UIMakeCharWnd::OnDraw");
void UIMakeCharWnd::OnDraw(void) // line 2468
{
	return (this->*_OnDraw)();

	CBitmapRes* bitmapRes = (CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp("유저인터페이스\\login_interface\\win_make.bmp"));
	this->UIWindow::DrawBitmap(0, 0, bitmapRes, false);
	this->UIMakeCharWnd::DrawHexagon();

	CacheInfo info;
	memset(&info, 0, sizeof(CacheInfo));

	for( int i = 0; i < 2; ++i )
	{
		CImfRes* imfRes = (CImfRes*)g_resMgr().CResMgr::Get(m_viewChar.imfName.c_str());
		CActRes* actRes = (CActRes*)g_resMgr().CResMgr::Get(m_viewChar.actName[i * 4].c_str());
		CSprRes* sprRes = (CSprRes*)g_resMgr().CResMgr::Get(m_viewChar.sprName[i * 4].c_str());
		CMotion* motion = actRes->CActRes::GetMotion(m_viewChar.curAction, m_viewChar.curMotion);
		POINT p = imfRes->CImfRes::GetPoint(i, m_viewChar.curAction, m_viewChar.curMotion);
		int offX = p.x;
		int offY = p.y;

		if( i == 1 )
		{
			CActRes* otherActRes = (CActRes*)g_resMgr().CResMgr::Get(m_viewChar.actName[0].c_str());
			CMotion* otherMotion = otherActRes->CActRes::GetMotion(m_viewChar.curAction, m_viewChar.curMotion);

			if( motion->attachCnt && otherMotion->attachCnt )
			{
				CAttachPointInfo* attachpoint = &motion->attachInfo[0];
				CAttachPointInfo* otherAttachpoint = &otherMotion->attachInfo[0];

				if( attachpoint->m_attr == otherAttachpoint->m_attr )
				{
					offX += otherAttachpoint->x - attachpoint->x;
					offY += otherAttachpoint->y - attachpoint->y;
				}
			}
		}

		unsigned long* palette = sprRes->m_pal;
		if( i == 0 )
		{
			if( m_viewChar.bodyPalette )
			{
				CPaletteRes* paletteRes = (CPaletteRes*)g_resMgr().CResMgr::Get(m_viewChar.bodyPaletteName.c_str());
				palette = paletteRes->m_pal;
			}
		}
		else
		if( i == 1 )
		{
			if( m_viewChar.headPalette )
			{
				CPaletteRes* paletteRes = (CPaletteRes*)g_resMgr().CResMgr::Get(m_viewChar.headPaletteName.c_str());
				palette = paletteRes->m_pal;
			}
		}

		CSprClip* sprClip = motion->CMotion::GetClip(i);
		SprImg* sprImg = sprRes->m_sprites[sprClip->clipType][sprClip->sprIndex];

		CTexture* tex;
		if( sprClip->clipType )
			tex = sprImg->tex;
		else
		{
			tex = g_renderer->CRenderer::GetSpriteIndex(*sprImg, (unsigned long)palette, &info);
			if( tex == NULL )
				tex = g_renderer->CRenderer::AddSpriteIndex(*sprImg, palette, &info);
		}

		m_dc->BltTexture2(m_viewChar.x + sprClip->x + offX, m_viewChar.y + sprClip->y + offY, tex, (int)(info.tu * 256.0), (int)(info.tv * 256.0), sprImg->width, sprImg->height, sprClip->flags, sprImg->isHalfW + 1, sprImg->isHalfH + 1);
	}
}


hook_method<void (UIMakeCharWnd::*)(void)> UIMakeCharWnd::_DrawHexagon(SERVER, "UIMakeCharWnd::DrawHexagon");
void UIMakeCharWnd::DrawHexagon(void) // line 2534
{
	return (this->*_DrawHexagon)();
	
	int maxXPos[6];
	maxXPos[0] = 288;
	maxXPos[1] = 356;
	maxXPos[2] = 356;
	maxXPos[3] = 288;
	maxXPos[4] = 220;
	maxXPos[5] = 220;

	int maxYPos[6];
	maxYPos[0] = 86;
	maxYPos[1] = 126;
	maxYPos[2] = 206;
	maxYPos[3] = 244;
	maxYPos[4] = 206;
	maxYPos[5] = 126;

	int params[6];
	params[1] = m_charInfo.Vit;
	params[0] = m_charInfo.Str;
	params[2] = m_charInfo.Luk;
	params[4] = m_charInfo.Dex;
	params[3] = m_charInfo.Int;
	params[5] = m_charInfo.Agi;
	
	int xPos[6];
	int yPos[6];
	for( int i = 0; i < 6; ++i )
	{
		xPos[i] = (maxXPos[i] - 288) * params[i] / 9 + 288;
		yPos[i] = (maxYPos[i] - 166) * params[i] / 9 + 166;
	}

	for( int i = 0, j = 1; i < 6; ++i, ++j )
	{
		if( j == 6 )
			j = 0;
		this->UIWindow::DrawTriangleDC(288, 166, xPos[i], yPos[i], xPos[j], yPos[j], 0xCE977C);
	}
}


hook_method<int (UIMakeCharWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UIMakeCharWnd::_SendMsg(SERVER, "UIMakeCharWnd::SendMsg");
int UIMakeCharWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3) // line 2559
{
	return (this->*_SendMsg)(sender, message, val1, val2, val3);

	int head;
	char filename[256];
	int data[8];
	bool isGoodSentence;
	bool isOnlyEnglish;
	bool isBadNameWithSpaceChar;
	
	if( message == 0)// enter pressed
	{
		char tmpName[24];
		strcpy(tmpName, m_nameEditCtrl->UIEditCtrl::GetText());
		memcpy(m_charInfo.name, tmpName, 24);
		this->SendMsg(0, 6, m_defPushId, 0, 0);
		return 0;
	}

	switch( message )
	{
	case 0: // enter pressed
		this->SendMsg(0, 6, m_defPushId, 0, 0);
		break;
	case 1: // escape pressed
		this->SendMsg(0, 6, m_defCancelPushId, 0, 0);
		break;
	case 6: // button pressed
		switch( val1 )
		{
		case 94: // ok button
			if( m_nameEditCtrl->UIEditCtrl::GetTextSize() < 4 )
			{
				g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(MSI_ENTER_NAME_MORE_THAN_4_CHAR), 0, 1, 0, 0);
				g_modeMgr.CModeMgr::GetCurMode()->SendMsg(10015, (int)m_nameEditCtrl->UIEditCtrl::GetText(), 0, 0);
				data[0] = m_charInfo.Str;
				data[1] = m_charInfo.Agi;
				data[2] = m_charInfo.Vit;
				data[3] = m_charInfo.Int;
				data[4] = m_charInfo.Dex;
				data[5] = m_charInfo.Luk;
				data[6] = m_charInfo.headpalette;
				data[7] = m_charInfo.head;
				g_modeMgr.CModeMgr::GetCurMode()->SendMsg(10017, (int)data, 0, 0);
				break;
			}

			isGoodSentence = g_insultFilter.CInsultFilter::IsGoodSentence(m_nameEditCtrl->UIEditCtrl::GetText());
			isOnlyEnglish = true;
			if( g_serviceType == ServiceAmerica )
				isOnlyEnglish = g_session.CSession::IsOnlyEnglish(m_nameEditCtrl->UIEditCtrl::GetText());
			isBadNameWithSpaceChar = g_session.CSession::IsBadNameWithSpaceChar(m_nameEditCtrl->UIEditCtrl::GetText());
			if( isGoodSentence && isOnlyEnglish && !isBadNameWithSpaceChar )
			{
				if( m_nameEditCtrl->UIEditCtrl::GetTextSize() >= 24 )
				{
					g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(MSI_NAMELENGTH_TOO_LONG), 0, 1, 0, 0);
					m_nameEditCtrl->SetText("");
					break;
				}

				char tmpName[24];
				memset(tmpName, 0, sizeof(tmpName));
				strcpy(tmpName, m_nameEditCtrl->UIEditCtrl::GetText());
				memcpy(m_charInfo.name, tmpName, sizeof(m_charInfo.name));
				if( strstr(tmpName, "그라비티") )
					break;
				if( strstr(tmpName, "김학규") )
					break;
				strlwr(tmpName);
				if( strstr(tmpName, "gravity") )
					break;
				if( strstr(tmpName, "neolith") )
					break;
				g_modeMgr.CModeMgr::GetCurMode()->SendMsg(10005, 0, 0, 0);
				g_windowMgr.PostQuit(this);
			}
			else
			{
				if( !isGoodSentence )
					g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(MSI_BAD_NAME), 0, 1, 0, 0);
				if( !isOnlyEnglish )
					g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(MSI_ENGLISHONLY), 0, 1, 0, 0);
				if( isBadNameWithSpaceChar )
					g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(MSI_NO_SPACE_IN_NAME), 0, 1, 0, 0);
			}
			g_modeMgr.CModeMgr::GetCurMode()->SendMsg(10015, (int)m_nameEditCtrl->UIEditCtrl::GetText(), 0, 0);
			int data[8];
			data[0] = m_charInfo.Str;
			data[1] = m_charInfo.Agi;
			data[2] = m_charInfo.Vit;
			data[3] = m_charInfo.Int;
			data[4] = m_charInfo.Dex;
			data[5] = m_charInfo.Luk;
			data[6] = m_charInfo.headpalette;
			data[7] = m_charInfo.head;
			g_modeMgr.CModeMgr::GetCurMode()->SendMsg(10017, (int)data, 0, 0);
			break;
		case 95: // cancel button
			g_windowMgr.UIWindowMgr::PostQuit(this);
			g_modeMgr.CModeMgr::GetCurMode()->SendMsg(0, 10004, 0, 0);
			break;
		case 115: // str button
			if( m_charInfo.Int >= 2 )
			{
				--m_charInfo.Int;
				++m_charInfo.Str;
				if( m_charInfo.Int + m_charInfo.Str != 10 )
				{
					m_charInfo.Int = 5;
					m_charInfo.Str = 5;
				}
				this->UIMakeCharWnd::InitTextControls();
			}
			break;
		case 116: // agi button
			if( m_charInfo.Luk >= 2 )
			{
				--m_charInfo.Luk;
				++m_charInfo.Agi;
				if( m_charInfo.Luk + m_charInfo.Agi != 10 )
				{
					m_charInfo.Luk = 5;
					m_charInfo.Agi = 5;
				}
				this->UIMakeCharWnd::InitTextControls();
			}
			break;
		case 117: // vit button
			if( m_charInfo.Dex >= 2 )
			{
				--m_charInfo.Dex;
				++m_charInfo.Vit;
				if( m_charInfo.Dex + m_charInfo.Vit != 10 )
				{
					m_charInfo.Dex = 5;
					m_charInfo.Vit = 5;
				}
				this->UIMakeCharWnd::InitTextControls();
			}
			break;
		case 118: // int button
			if( m_charInfo.Str >= 2 )
			{
				--m_charInfo.Str;
				++m_charInfo.Int;
				if( m_charInfo.Str + m_charInfo.Int != 10 )
				{
					m_charInfo.Str = 5;
					m_charInfo.Int = 5;
				}
				this->UIMakeCharWnd::InitTextControls();
			}
			break;
		case 119: // dex button
			if( m_charInfo.Vit >= 2 )
			{
				--m_charInfo.Vit;
				++m_charInfo.Dex;
				if( m_charInfo.Vit + m_charInfo.Dex != 10 )
				{
					m_charInfo.Vit = 5;
					m_charInfo.Dex = 5;
				}
				this->UIMakeCharWnd::InitTextControls();
			}
			break;
		case 120: // luk button
			if( m_charInfo.Agi >= 2 )
			{
				--m_charInfo.Agi;
				++m_charInfo.Luk;
				if( m_charInfo.Agi + m_charInfo.Luk != 10 )
				{
					m_charInfo.Agi = 5;
					m_charInfo.Luk = 5;
				}
				this->UIMakeCharWnd::InitTextControls();
			}
			break;
		case 136: // next head button
			this->Invalidate();
			++m_charInfo.head;
			if( m_charInfo.head == 20 )
				m_charInfo.head = 1;
			head = m_charInfo.head;
			g_session.GetHeadActName(m_charInfo.job, head, g_session.GetSex(), filename);
			m_viewChar.actName[1] = filename;
			g_session.GetHeadSprName(m_charInfo.job, head, g_session.GetSex(), filename);
			m_viewChar.sprName[1] = filename;
			g_session.GetImfName(m_charInfo.job, head, g_session.GetSex(), filename);
			m_viewChar.imfName = filename;
			if( m_viewChar.headPalette )
			{
				g_session.GetHeadPaletteName(m_charInfo.job, head, g_session.GetSex(), m_viewChar.headPalette, filename);
				m_viewChar.headPaletteName = filename;
				Trace("headPaletteName = %s", filename);
			}
			break;
		case 137: // prev head button
			this->Invalidate();
			--m_charInfo.head;
			if( m_charInfo.head == 0 )
				m_charInfo.head = 19;
			head = m_charInfo.head;
			g_session.GetHeadActName(m_charInfo.job, head, g_session.GetSex(), filename);
			m_viewChar.actName[1] = filename;
			g_session.GetHeadSprName(m_charInfo.job, head, g_session.GetSex(), filename);
			m_viewChar.sprName[1] = filename;
			g_session.GetImfName(m_charInfo.job, head, g_session.GetSex(), filename);
			m_viewChar.imfName = filename;
			if( m_viewChar.headPalette )
			{
				g_session.GetHeadPaletteName(m_charInfo.job, head, g_session.GetSex(), m_viewChar.headPalette, filename);
				m_viewChar.headPaletteName = filename;
				Trace("headPaletteName = %s", filename);
			}
			break;
		case 188: // change hair button
			++m_viewChar.headPalette;
			if( m_viewChar.headPalette > 8 )
				m_viewChar.headPalette = 0;
			g_session.GetHeadPaletteName(m_charInfo.job, head, g_session.GetSex(), m_viewChar.headPalette, filename);
			m_charInfo.headpalette = m_viewChar.headPalette;
			m_viewChar.headPaletteName = filename;
			break;
		}
		break;
	default:
		this->UIWindow::SendMsg(sender, message, val1, val2, val3);
		break;
	}

	return 0;
}


hook_method<void (UIMakeCharWnd::*)(void)> UIMakeCharWnd::_MakeButton(SERVER, "UIMakeCharWnd::MakeButton");
void UIMakeCharWnd::MakeButton(void) // line 2850
{
	return (this->*_MakeButton)();

	{// ok/cancel/stat buttons
		mystd::string pathName = "유저인터페이스\\";

		const char* buttonName[24];
		buttonName[0] = "btn_ok";
		buttonName[1] = "btn_ok_a";
		buttonName[2] = "btn_ok_b";
		buttonName[3] = "btn_cancel";
		buttonName[4] = "btn_cancel_a";
		buttonName[5] = "btn_cancel_b";
		buttonName[6] = "login_interface\\arw-str0";
		buttonName[7] = "login_interface\\arw-str1";
		buttonName[8] = "login_interface\\arw-str0";
		buttonName[9] = "login_interface\\arw-agi0";
		buttonName[10] = "login_interface\\arw-agi1";
		buttonName[11] = "login_interface\\arw-agi0";
		buttonName[12] = "login_interface\\arw-vit0";
		buttonName[13] = "login_interface\\arw-vit1";
		buttonName[14] = "login_interface\\arw-vit0";
		buttonName[15] = "login_interface\\arw-int0";
		buttonName[16] = "login_interface\\arw-int1";
		buttonName[17] = "login_interface\\arw-int0";
		buttonName[18] = "login_interface\\arw-dex0";
		buttonName[19] = "login_interface\\arw-dex1";
		buttonName[20] = "login_interface\\arw-dex0";
		buttonName[21] = "login_interface\\arw-luk0";
		buttonName[22] = "login_interface\\arw-luk1";
		buttonName[23] = "login_interface\\arw-luk0";

		const char* toolTip[8];
		toolTip[0] = "";
		toolTip[1] = "";
		toolTip[2] = MsgStr(MSI_DESC_STR);
		toolTip[3] = MsgStr(MSI_DESC_AGI);
		toolTip[4] = MsgStr(MSI_DESC_VIT);
		toolTip[5] = MsgStr(MSI_DESC_INT);
		toolTip[6] = MsgStr(MSI_DESC_DEX);
		toolTip[7] = MsgStr(MSI_DESC_LUK);

		int ids[8];
		ids[0] = 94;
		ids[1] = 95;
		ids[2] = 115;
		ids[3] = 116;
		ids[4] = 117;
		ids[5] = 118;
		ids[6] = 119;
		ids[7] = 120;

		int pos[16];
		pos[0] = 483;
		pos[1] = 318;
		pos[2] = 530;
		pos[3] = 318;
		pos[4] = 270;
		pos[5] = 50;
		pos[6] = 190;
		pos[7] = 104;
		pos[8] = 349;
		pos[9] = 104;
		pos[10] = 270;
		pos[11] = 244;
		pos[12] = 190;
		pos[13] = 190;
		pos[14] = 349;
		pos[15] = 190;

		for( int i = 0; i < 8; ++i )
		{
			UIBitmapButton* btn = new UIBitmapButton();
			btn->UIBitmapButton::SetBitmapName((pathName + buttonName[3 * i + 0] + ".bmp").c_str(), 0);
			btn->UIBitmapButton::SetBitmapName((pathName + buttonName[3 * i + 1] + ".bmp").c_str(), 1);
			btn->UIBitmapButton::SetBitmapName((pathName + buttonName[3 * i + 2] + ".bmp").c_str(), 2);
			btn->UIWindow::Create(btn->UIBitmapButton::GetBitmapWidth(), btn->UIBitmapButton::GetBitmapHeight());
			btn->UIWindow::Move(pos[2 * i + 0], pos[2 * i + 1]);
			btn->UIWindow::SetId(ids[i]);
			btn->UIButton::SetToolTip(toolTip[i]);
			this->UIWindow::AddChild(btn);
		}
	}
	{// head/hair buttons
		mystd::string pathName = "유저인터페이스\\";

		const char* buttonName[9];
		buttonName[0] = "scroll1left";
		buttonName[1] = "scroll1left";
		buttonName[2] = "scroll1left";
		buttonName[3] = "scroll1right";
		buttonName[4] = "scroll1right";
		buttonName[5] = "scroll1right";
		buttonName[6] = "scroll0up";
		buttonName[7] = "scroll0up";
		buttonName[8] = "scroll0up";
		
		int ids[3];
		ids[0] = 137;
		ids[1] = 136;
		ids[2] = 188;

		int pos[6];
		pos[0] = 48;
		pos[1] = 135;
		pos[2] = 130;
		pos[3] = 135;
		pos[4] = 89;
		pos[5] = 101;
		
		const char* toolTip[3];
		toolTip[0] = MsgStr(MSI_SELECT_HAIR_STYLE);
		toolTip[1] = MsgStr(MSI_SELECT_HAIR_STYLE);
		toolTip[2] = MsgStr(MSI_SELECT_HAIR_COLOR);

		for( int i = 0; i < 3; ++i )
		{
			UIBitmapButton* btn = new UIBitmapButton();
			btn->UIBitmapButton::SetBitmapName((pathName + buttonName[3 * i + 0] + ".bmp").c_str(), 0);
			btn->UIBitmapButton::SetBitmapName((pathName + buttonName[3 * i + 1] + ".bmp").c_str(), 1);
			btn->UIBitmapButton::SetBitmapName((pathName + buttonName[3 * i + 2] + ".bmp").c_str(), 2);
			btn->UIWindow::Create(btn->UIBitmapButton::GetBitmapWidth(), btn->UIBitmapButton::GetBitmapHeight());
			btn->UIWindow::Move(pos[2 * i + 0], pos[2 * i + 1]);
			btn->UIWindow::SetId(ids[i]);
			btn->UIButton::SetToolTip(toolTip[i]);
			this->UIWindow::AddChild(btn);
		}
	}
}


hook_method<void (UIMakeCharWnd::*)(void)> UIMakeCharWnd::_InitTextControls(SERVER, "UIMakeCharWnd::InitTextControls");
void UIMakeCharWnd::InitTextControls(void) // line 2939
{
	return (this->*_InitTextControls)();

	char buf[100];
	sprintf(buf, "%d", m_charInfo.Str); m_text[0]->UIStaticText::SetTextWithNewWidth(buf);
	sprintf(buf, "%d", m_charInfo.Agi); m_text[1]->UIStaticText::SetTextWithNewWidth(buf);
	sprintf(buf, "%d", m_charInfo.Vit); m_text[2]->UIStaticText::SetTextWithNewWidth(buf);
	sprintf(buf, "%d", m_charInfo.Int); m_text[3]->UIStaticText::SetTextWithNewWidth(buf);
	sprintf(buf, "%d", m_charInfo.Dex); m_text[4]->UIStaticText::SetTextWithNewWidth(buf);
	sprintf(buf, "%d", m_charInfo.Luk); m_text[5]->UIStaticText::SetTextWithNewWidth(buf);
}


////////////////////////////////////////


UIChatWnd::UIChatWnd(void) // line 2959
{
	m_commonChat = NULL;
	m_whisperChat = NULL;
	m_lastFocusChat = NULL;
	m_resizer = NULL;
	m_listBox = NULL;
	m_state = 0;
	m_comboMode = 0;
}


UIChatWnd::~UIChatWnd(void) // line 2971
{
}


hook_method<void (UIChatWnd::*)(int cx, int cy)> UIChatWnd::_OnCreate(SAKEXE, "UIChatWnd::OnCreate");
void UIChatWnd::OnCreate(int cx, int cy) // line 2974
{
	return (this->*_OnCreate)(cx, cy);

	if( cy > 24 )
	{
		m_state = (cy - 98) / 42 + 1;
		if( m_state > 4 )
			m_state = 4;
	}
	else
	{
		m_state = 0;
	}

	m_commonChat = new UIChatEditCtrl();
	m_commonChat->UIWindow::Create(460, 16);
	m_commonChat->Move(110, this->UIWindow::GetHeight() - 20);
	m_commonChat->UIEditCtrl::SetTextLimit(70);
	m_commonChat->UIEditCtrl::SetFrameColor(240, 240, 240);
	this->UIWindow::AddChild(m_commonChat);
	m_lastFocusChat = m_commonChat;
	g_windowMgr.UIWindowMgr::SetFocusEdit(m_commonChat);

	m_whisperChat = new UIWhisperEditCtrl();
	m_whisperChat->UIWindow::Create(90, 16);
	m_whisperChat->Move(6, this->UIWindow::GetHeight() - 20);
	m_whisperChat->UIEditCtrl::SetTextLimit(24);
	m_whisperChat->UIEditCtrl::SetFrameColor(240, 240, 240);
	this->UIWindow::AddChild(m_whisperChat);
	m_defPushId = 94;

	m_resizer = new UIResizer();
	m_resizer->UIResizer::SetBitmap("유저인터페이스\\basic_interface\\dialog_mid.bmp");
	m_resizer->UIWindow::Create(m_resizer->UIWindow::GetWidth(), m_resizer->UIWindow::GetHeight());
	m_resizer->UIResizer::SetType(RT_LEFT);
	m_resizer->Move(2, this->UIWindow::GetHeight() - m_resizer->UIWindow::GetHeight());
	this->UIWindow::AddChild(m_resizer);

	mystd::string pathName = "유저인터페이스\\basic_interface\\";

	const char* buttonName[9];
	buttonName[0] = "dialog_btn1";
	buttonName[1] = "dialog_btn1";
	buttonName[2] = "dialog_btn2";
	buttonName[3] = "sys_base_off";
	buttonName[4] = "sys_base_on";
	buttonName[5] = "sys_base_on";
	buttonName[6] = "sys_base_off";
	buttonName[7] = "sys_base_on";
	buttonName[8] = "sys_base_on";

	int ids[3];
	ids[0] = 135;
	ids[1] = 122;
	ids[2] = 147;

	int pos[6];
	pos[0] = 97;
	pos[1] = m_h - 21;
	pos[2] = 586;
	pos[3] = m_h - 17;
	pos[4] = 572;
	pos[5] = m_h - 17;

	for( int index = 0; index < countof(m_buttons); ++index )
	{
		UIBitmapButton* btn = new UIBitmapButton();
		m_buttons[index] = btn;

		btn->UIBitmapButton::SetBitmapName((pathName + buttonName[3*index+0] + ".bmp").c_str(), 0);
		btn->UIBitmapButton::SetBitmapName((pathName + buttonName[3*index+1] + ".bmp").c_str(), 1);
		btn->UIBitmapButton::SetBitmapName((pathName + buttonName[3*index+2] + ".bmp").c_str(), 2);

		btn->UIWindow::Create(btn->UIBitmapButton::GetBitmapWidth(), btn->UIBitmapButton::GetBitmapHeight());
		btn->Move(pos[2*index+0], pos[2*index+1]);
		btn->UIWindow::SetId(ids[index]);
		this->UIWindow::AddChild(btn);
	}

	m_listBox = new UIChatHisBox();
	m_listBox->Create2(0, 0, 590, 74, false);

	if( cy - 74 < 24 )
	{
		m_listBox->Move(5, -74);
	}
	else
	{
		m_listBox->Move(5, 0);
	}

	m_listBox->UIWindow::SetId(94);
	this->UIWindow::AddChild(m_listBox);

	UIResizer* resizer = new UIResizer();
	resizer->UIWindow::Create(m_w - 26, 6);
	resizer->UIResizer::SetType(RT_UP);
	resizer->Move(3, 0);
	resizer->UIResizer::SetColor(0xFFFF00FFu, 0xFFFF00FFu);
	this->UIWindow::AddChild(resizer);

	int gx = 0;
	int gy = 0;
	this->UIWindow::GetGlobalCoor(gx, gy);

	m_boxInfo.x = gx + 3;
	m_boxInfo.cy = m_h - 24;
	m_boxInfo.color2 = 0;
	m_boxInfo.drawEdge = 0;
	m_boxInfo.y = gy;
	m_boxInfo.cx = m_w - 6;
	m_boxInfo.color = 0x66000000u;
}


hook_method<void (UIChatWnd::*)(void)> UIChatWnd::_OnDraw(SAKEXE, "UIChatWnd::OnDraw");
void UIChatWnd::OnDraw(void) // line 3202
{
	return (this->*_OnDraw)();

	//TODO
}


hook_method<void (UIChatWnd::*)(void)> UIChatWnd::_OnDraw2(SAKEXE, "UIChatWnd::OnDraw2");
void UIChatWnd::OnDraw2(void) // line 3194
{
	return (this->*_OnDraw2)();

	//TODO
}


hook_method<void (UIChatWnd::*)(int x, int y)> UIChatWnd::_OnLBtnDown(SAKEXE, "UIChatWnd::OnLBtnDown");
void UIChatWnd::OnLBtnDown(int x, int y) // line 3072
{
	return (this->*_OnLBtnDown)(x, y);

	//TODO
}


hook_method<void (UIChatWnd::*)(int x, int y)> UIChatWnd::_OnMouseMove(SAKEXE, "UIChatWnd::OnMouseMove");
void UIChatWnd::OnMouseMove(int x, int y) // line 3077
{
	return (this->*_OnMouseMove)(x, y);

	//TODO
}


hook_method<void (UIChatWnd::*)(int x,int y)> UIChatWnd::_OnLBtnUp(SAKEXE, "UIChatWnd::OnLBtnUp");
void UIChatWnd::OnLBtnUp(int x,int y) // line 3083
{
	return (this->*_OnLBtnUp)(x, y);

	//TODO
}


hook_method<int (UIChatWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UIChatWnd::_SendMsg(SAKEXE, "UIChatWnd::SendMsg");
int UIChatWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3) // line 3277
{
//	return (this->*_SendMsg)(sender, message, val1, val2, val3);

	switch( message )
	{
	case UM_DELETE_WHISPER_NAME:
	{
		mystd::string str = (const char*)val1;
		size_t size = m_whisperChat->m_hisChat.size();

		mystd::vector<mystd::string>::iterator it;
		int pos = 0;
		for( it = m_whisperChat->m_hisChat.begin(); it != m_whisperChat->m_hisChat.end(); ++it )
		{
			if( *it == str )
			{
				m_whisperChat->m_hisChat.erase(it);

				if( m_whisperChat->m_curHis == pos )
					m_whisperChat->m_curHis = size - 1;
				else
				if( m_whisperChat->m_curHis > pos )
					m_whisperChat->m_curHis = m_whisperChat->m_curHis - 1;

				return 0;
			}

			++pos;
		}
	}
	break;
	case UM_GET_EDIT_FOCUS:
		g_windowMgr.UIWindowMgr::SetFocusEdit(m_commonChat);
	break;
	case UM_COMBOBOX_SELECTED:
		if( m_comboMode == 0 )
		{// name selection menu
			if( val1 >= 0 && val1 <= (int)m_whisperChat->m_hisChat.size() )
			{
				g_windowMgr.UIWindowMgr::SetFocusEdit(m_commonChat);
				const char* text = ( val1 != m_whisperChat->m_hisChat.size() ) ? m_whisperChat->m_hisChat[val1].c_str() : "";
				m_whisperChat->SetText(text);
				m_whisperChat->m_curHis = val1;
			}
		}
		else
		if( m_comboMode == 1 )
		{// message type selection menu
			g_session.m_talkType = val1;

			if( val1 == 0 )
			{
				m_commonChat->UIEditCtrl::SetTextColor(0, 0, 0);
			}
			else
			if( val1 == 1 )
			{
				m_commonChat->UIEditCtrl::SetTextColor(128, 0, 128);
			}
			else
			if( val1 == 2 )
			{
				m_commonChat->UIEditCtrl::SetTextColor(0, 128, 128);
			}

			this->Invalidate();
		}
	break;
	case UM_ADDCHAT:
	{
		const char* msg = (const char*)val1;
		unsigned long color = (unsigned long)val2;

		mystd::vector<mystd::string> strings;
		CutString(msg, strings, 94);

		for( size_t i = 0; i < strings.size(); ++i )
			m_listBox->AddItem(strings[i].c_str(), color);
	}
	break;
	case UM_SETINFO:
		if( g_windowMgr.m_chatWndX < 0 || g_windowMgr.m_chatWndY < 0 || g_windowMgr.m_chatWndX > g_renderer->CRenderer::GetWidth() - m_w || g_windowMgr.m_chatWndY > g_renderer->CRenderer::GetHeight() - m_h )
		{
			g_windowMgr.m_chatWndX = 0;
			g_windowMgr.m_chatWndY = g_renderer->CRenderer::GetHeight() - m_h;
		}

		m_x = g_windowMgr.m_chatWndX;
		m_y = g_windowMgr.m_chatWndY;
		this->UIChatWnd::SetState(g_windowMgr.m_chatWndStatus);
		this->Move(m_x, m_y);
	break;
	case UM_COMMAND:
		switch( val1 )
		{
		case 147: // message type selection menu button
		{
			m_comboMode = 1;

			if( g_windowMgr.UIWindowMgr::GetComboBoxWnd() != NULL )
				g_windowMgr.UIWindowMgr::DeleteWindow(WID_COMBOBOXWND);

			UIFrameWnd* wnd = g_windowMgr.UIWindowMgr::MakeWindow(WID_COMBOBOXWND);
			wnd->SendMsg(NULL, UM_ADDITEM, (int)MsgStr(MSI_SEND_TO_ALL), 0, 0);
			wnd->SendMsg(NULL, UM_ADDITEM, (int)MsgStr(MSI_SEND_TO_PARTY), 0, 0);
			wnd->SendMsg(NULL, UM_ADDITEM, (int)MsgStr(MSI_SEND_TO_GUILD), 0, 0);
			wnd->SendMsg(NULL, UM_SETCURITEM, g_session.m_talkType, 0, 0);
			wnd->Resize(112, 48);
			wnd->SendMsg(NULL, UM_SET_CALLER_WID, 1, 0, 0);

			int gx = m_w - 115;
			int gy = m_h - 24;
			this->UIWindow::GetGlobalCoor(gx, gy);
			wnd->Move(gx + 1, gy - 47);
		}
		break;
		case 135: // name selection menu button
		{
			m_comboMode = 0;
			if( g_windowMgr.UIWindowMgr::GetComboBoxWnd() != NULL  )
				g_windowMgr.UIWindowMgr::DeleteWindow(WID_COMBOBOXWND);
			size_t size = m_whisperChat->m_hisChat.size();

			if( size == 0 )
			{
				g_windowMgr.UIWindowMgr::SendMsg(UIM_OPENCHATWND, 0, 0, 0);
				g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)MsgStr(MSI_NOWHISPERLIST), 0x0000FF, 0);
				break;
			}

			UIFrameWnd* wnd = g_windowMgr.UIWindowMgr::MakeWindow(WID_COMBOBOXWND);
			for( size_t i = 0; i < size; ++i )
				wnd->SendMsg(NULL, UM_ADDITEM, (int)m_whisperChat->m_hisChat[i].c_str(), 0, 0);
			wnd->SendMsg(NULL, UM_ADDITEM, (int)"", 0, 0);

			int height = 16 * (size + 1);
			if( height >= 80 )
				height = 80;

			wnd->SendMsg(NULL, UM_SETCURITEM, m_whisperChat->m_curHis, 0, 0);
			wnd->Resize(112, height);
			wnd->SendMsg(NULL, UM_SET_CALLER_WID, 1, 0, 0);

			int gx = 0;
			int gy = m_h - 24;
			this->UIWindow::GetGlobalCoor(gx, gy);

			wnd->Move(gx + 1, gy - height + 1);
		}
		break;
		case 94: // message send
		{
			char chatBuf[256];
			strcpy(chatBuf, m_commonChat->UIEditCtrl::GetText());

			m_commonChat->UIChatEditCtrl::StoreInHistory();
			m_lastFocusChat = m_commonChat;
			g_windowMgr.UIWindowMgr::SetFocusEdit(m_commonChat);

			if( strlen(chatBuf) == 0 )
				break;

			if( g_serviceType == 1 && !g_session.CSession::IsOnlyEnglish(chatBuf) )
			{
				g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)MsgStr(MSI_ENGLISHONLY), 0x0000FF, 0);
				break;
			}

			if( m_whisperChat->UIEditCtrl::GetTextSize() != 0 && chatBuf[0] != '/' )
			{
				g_windowMgr.UIWindowMgr::SetChatMsg(chatBuf);
				g_modeMgr.CModeMgr::GetCurMode()->SendMsg(MM_WHISPERMSG, (int)m_whisperChat->UIEditCtrl::GetText(), 0, 0);
			}
			else
			{
				mystd::string param[3];
				TALKTYPE talkType;
				int pos = g_session.CSession::GetTalkType(chatBuf, &talkType, param);
				if( pos != -1 )
					g_windowMgr.UIWindowMgr::SetChatMsg(&chatBuf[pos]);
				g_modeMgr.CModeMgr::GetCurMode()->SendMsg(MM_PROCESS_TALK_TYPE, (int)talkType, (int)param, 0);
			}
		}
		break;
		case 122: // chatbox resize button
			this->SendMsg(NULL, UM_TOGGLEPUSH, 0, 0, 0);
		break;
		default:
		break;
		}
	break;
	case UM_RESIZE:
		if( val1 == 2 )
		{
			if( val3 < 56 )
			{
				if( m_state != 0 )
					this->UIChatWnd::SetState(0);
			}
			else
			{
				int newState = (val3 - 56) / 14 + 1;
				if( newState > 15 )
					newState = 15;

				if( m_state != newState )
					this->UIChatWnd::SetState(newState);
			}
		}
	break;
	case UM_TOGGLEPUSH:
	{
		int pos = 2 * (val1 == 0) - 1;
		if( m_state != 0 )
			pos += m_state + 2 * pos;
		
		if( pos > 0 )
		{
			this->UIChatWnd::SetState(pos + 1 - pos % 3);
		}
		else
		if( m_state == 0 )
		{
			this->UIChatWnd::SetState(pos);
		}
		else
		{
			this->UIChatWnd::SetState(0);
		}
	}
	break;
	case UM_PAGEUPPUSH:
		if( m_listBox->UIListBox::IsVertScrEnabled() )
			m_listBox->SendMsg(NULL, UM_SCROLLVERTPAGEUP, 0, 0, 0);
	break;
	case UM_PAGEDOWNPUSH:
		if( m_listBox->UIListBox::IsVertScrEnabled() )
			m_listBox->SendMsg(NULL, UM_SCROLLVERTPAGEDOWN, 0, 0, 0);
	break;
	case 15:
		this->UIChatWnd::SetState(val1);
	break;
	case UM_OPENCHATWND:
		if( m_state == 0 )
			this->UIChatWnd::SetState(1);
	break;
	default:
		if( message == 0 )
		{
			if( m_defPushId != 0 )
				this->SendMsg(this, UM_COMMAND, m_defPushId, 0, 0);
		}
		else
		if( message == 1 )
		{
			if( m_defCancelPushId != 0 )
				this->SendMsg(this, UM_COMMAND, m_defCancelPushId, 0, 0);
		}
		else
		{
			return this->UIWindow::SendMsg(sender, message, val1, val2, val3);
		}
	break;
	}

	return 0;
}


hook_method<bool (UIChatWnd::*)(BOXINFO* boxInfo)> UIChatWnd::_GetTransBoxInfo(SAKEXE, "UIChatWnd::GetTransBoxInfo");
bool UIChatWnd::GetTransBoxInfo(BOXINFO* boxInfo) // line 3092
{
	return (this->*_GetTransBoxInfo)(boxInfo);

	//TODO
}


hook_method<void (UIChatWnd::*)(int x, int y)> UIChatWnd::_Move(SAKEXE, "UIChatWnd::Move");
void UIChatWnd::Move(int x, int y) // line 3174
{
	return (this->*_Move)(x, y);

	//TODO
}


hook_method<void (UIChatWnd::*)(int cx, int cy)> UIChatWnd::_Resize(SAKEXE, "UIChatWnd::Resize");
void UIChatWnd::Resize(int cx, int cy) // line 3186
{
	return (this->*_Resize)(cx, cy);

	//TODO
}


hook_method<void (UIChatWnd::*)(void)> UIChatWnd::_StoreInfo(SAKEXE, "UIChatWnd::StoreInfo");
void UIChatWnd::StoreInfo(void) // line 3221
{
	return (this->*_StoreInfo)();

	//TODO
}


hook_method<void (UIChatWnd::*)(int visible)> UIChatWnd::_SetShow(SAKEXE, "UIChatWnd::SetShow");
void UIChatWnd::SetShow(int visible) // line 3208
{
	return (this->*_SetShow)(visible);

	//TODO
}


hook_method<void (UIChatWnd::*)(int state)> UIChatWnd::_SetState(SAKEXE, "UIChatWnd::SetState");
void UIChatWnd::SetState(int state) // line 3103
{
	return (this->*_SetState)(state);

	//TODO
}


hook_method<void (UIChatWnd::*)(void)> UIChatWnd::_WriteChatToFile(SAKEXE, "UIChatWnd::WriteChatToFile");
void UIChatWnd::WriteChatToFile(void) // line 3228
{
	return (this->*_WriteChatToFile)();

	//TODO
}


////////////////////////////////////////


UIChatRoomWnd::UIChatRoomWnd(void) // line 3548
{
	m_info = NULL;
}


UIChatRoomWnd::~UIChatRoomWnd(void) // line 3553
{
}


hook_method<void (UIChatRoomWnd::*)(void)> UIChatRoomWnd::_WriteChatToFile(SAKEXE, "UIChatRoomWnd::WriteChatToFile");
void UIChatRoomWnd::WriteChatToFile(void) // line 3702
{
	return (this->*_WriteChatToFile)();

	//TODO
}


class hook_ptr<struct mystd::_Tree<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> >,struct mystd::pair<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> > const ,unsigned long>,struct mystd::map<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> >,unsigned long,struct mystd::less<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> > >,class mystd::allocator<unsigned long> >::_Kfn,struct mystd::less<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> > >,class mystd::allocator<unsigned long> >::_Node *> mystd::_Tree<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> >,struct mystd::pair<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> > const ,unsigned long>,struct mystd::map<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> >,unsigned long,struct mystd::less<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> > >,class mystd::allocator<unsigned long> >::_Kfn,struct mystd::less<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> > >,class mystd::allocator<unsigned long> >::_Nil(SAKEXE, "?_Nil@?$_Tree@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@U?$pair@$$CBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@K@2@U_Kfn@?$map@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@KU?$less@V?$basic_sfbd19024");
class hook_val<unsigned int> mystd::_Tree<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> >,struct mystd::pair<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> > const ,unsigned long>,struct mystd::map<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> >,unsigned long,struct mystd::less<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> > >,class mystd::allocator<unsigned long> >::_Kfn,struct mystd::less<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> > >,class mystd::allocator<unsigned long> >::_Nilrefs(SAKEXE, "?_Nilrefs@?$_Tree@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@U?$pair@$$CBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@K@2@U_Kfn@?$map@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@KU?$less@V?$bas1a456136");


////////////////////////////////////////


UIPetInfoWnd::UIPetInfoWnd(void) // line 4463
{
}


UIPetInfoWnd::~UIPetInfoWnd(void) // line 4468
{
}


////////////////////////////////////////


UICntWnd::UICntWnd(void) // line 5065-5067
{
}


UICntWnd::~UICntWnd(void) // line 5070-5072
{
}


hook_method<void (UICntWnd::*)(int cx, int cy)> UICntWnd::_OnCreate(SAKEXE, "UICntWnd::OnCreate");
void UICntWnd::OnCreate(int cx, int cy) // line 5075-5113
{
	return (this->*_OnCreate)(cx, cy);

	//TODO
}


hook_method<void (UICntWnd::*)(void)> UICntWnd::_OnDraw(SAKEXE, "UICntWnd::OnDraw");
void UICntWnd::OnDraw(void) // line 5116-5118
{
	return (this->*_OnDraw)();

	//TODO
}


hook_method<int (UICntWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UICntWnd::_SendMsg(SAKEXE, "UICntWnd::SendMsg");
int UICntWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3) // line 5121-5154
{
	return (this->*_SendMsg)(sender, message, val1, val2, val3);

	//TODO
}


////////////////////////////////////////
