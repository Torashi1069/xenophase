#include "Globals.h"
#include "Mode.h"
#include "ModeMgr.h"
#include "MsgStrings.h" // UIBmp()
#include "Base/ResMgr.h"
#include "Resource/ImfRes.h"
#include "Resource/PaletteRes.h"
#include "Window/UISelectCharWnd.h"
#include "Window/UISlotBitmap.h"


UISelectCharWnd::UISelectCharWnd(void) // line 1604-1626
{
	m_stateCnt = 0;
	m_okButton = NULL;
	m_makeButton = NULL;
	m_cancelButton = NULL;
	m_deleteButton = NULL;
	m_chargeButton = NULL;
	m_noticeButton = NULL;
	m_dontmove = 0;

	for( int i = 0; i < 9; ++i )
	{
		m_isEmpty[i] = TRUE;
		m_isAvailable[i] = ( i < 5 );
	}

	m_curSlot = 0;
	m_curPage = 0;
	m_pageCount = 1;
}


UISelectCharWnd::~UISelectCharWnd(void) // line 1629-1630
{
}


void UISelectCharWnd::OnCreate(int cx, int cy) // line 1808-1938
{
	this->UISelectCharWnd::InitFromReg();

	g_charInfo.CharNum = LOBYTE(m_curSlot) + 3 * LOBYTE(m_curPage);

	int states[3];
	for( int i = 0; i < 3; ++i )
		states[i] = ( m_curSlot != i );

	for( int i = 0; i < 3; ++i )
	{
		UISlotBitmap* bitmap = new UISlotBitmap();
		bitmap->UIStaticBitmap::SetBitmap("유저인터페이스\\login_interface\\box_select.bmp");
		bitmap->UIWindow::Create(bitmap->UIWindow::GetWidth(), bitmap->UIWindow::GetHeight());
		bitmap->Move(56 + i * 163, 40);
		bitmap->UIWindow::SetId(ID_SLOT);
		this->UIWindow::AddChild(bitmap);
		m_slots[i] = bitmap;
		bitmap->SendMsg(this, UM_SETSTATE, states[i], 0, 0);
	}

	if( g_extended_slot )
	{
		m_pageCount = 3;

		UIBitmapButton* btnleft = new UIBitmapButton();;
		btnleft->UIBitmapButton::SetBitmapName("유저인터페이스\\scroll1left.bmp", 0);
		btnleft->UIBitmapButton::SetBitmapName("유저인터페이스\\scroll1left.bmp", 1);
		btnleft->UIBitmapButton::SetBitmapName("유저인터페이스\\scroll1left.bmp", 2);
		btnleft->UIWindow::Create(btnleft->UIBitmapButton::GetBitmapWidth(), btnleft->UIBitmapButton::GetBitmapHeight());
		btnleft->Move(44, 110);
		btnleft->UIWindow::SetId(ID_MINUS);
		this->UIWindow::AddChild(btnleft);

		UIBitmapButton* btnright = new UIBitmapButton();
		btnright->UIBitmapButton::SetBitmapName("유저인터페이스\\scroll1right.bmp", 0);
		btnright->UIBitmapButton::SetBitmapName("유저인터페이스\\scroll1right.bmp", 1);
		btnright->UIBitmapButton::SetBitmapName("유저인터페이스\\scroll1right.bmp", 2);
		btnright->UIWindow::Create(btnright->UIBitmapButton::GetBitmapWidth(), btnright->UIBitmapButton::GetBitmapHeight());
		btnright->Move(520, 110);
		btnright->UIWindow::SetId(ID_PLUS);
		this->UIWindow::AddChild(btnright);
	}

	for( int i = 0; i < 12; ++i )
	{
		m_text[i] = new UIStaticText();
		m_text[i]->UIWindow::Create(90, 15);
		m_text[i]->UIStaticText::SetText("", 0);
		m_text[i]->Move(69 + 144 * (i / 6), 206 + 16 * (i % 6));
		this->UIWindow::AddChild(m_text[i]);
	}

	this->UISelectCharWnd::InitTextControls();

	for( int m = 0; m < 9; ++m )
	{
		CHARACTER_INFO* charInfo = (CHARACTER_INFO*)g_modeMgr.CModeMgr::GetCurMode()->SendMsg(MM_QUERYCHARICTORINFO, m, 0, 0);
		if( charInfo == NULL )
			continue;

		char tmpName[256];

		int n = charInfo->CharNum;

		m_isEmpty[n] = FALSE;
		m_viewChar[n].baseAction = 0;
		m_viewChar[n].curAction = 0;
		m_viewChar[n].curMotion = 0;
		m_viewChar[n].x = 124 + 163 * (n % 3);
		m_viewChar[n].y = 157;

		m_viewChar[n].actName[0] = g_session.CSession::GetJobActName(charInfo->job, g_session.CSession::GetSex(), tmpName);
		m_viewChar[n].sprName[0] = g_session.CSession::GetJobSprName(charInfo->job, g_session.CSession::GetSex(), tmpName);

		int head = charInfo->head;
		m_viewChar[n].actName[1] = g_session.CSession::GetHeadActName(charInfo->job, head, g_session.CSession::GetSex(), tmpName);
		m_viewChar[n].sprName[1] = g_session.CSession::GetHeadSprName(charInfo->job, head, g_session.CSession::GetSex(), tmpName);
		m_viewChar[n].actName[2] = g_session.CSession::GetAccessoryActName(charInfo->job, head, g_session.CSession::GetSex(), charInfo->accessory, tmpName);
		m_viewChar[n].sprName[2] = g_session.CSession::GetAccessorySprName(charInfo->job, head, g_session.CSession::GetSex(), charInfo->accessory, tmpName);

		charInfo->head = head;
		m_viewChar[n].actName[3] = g_session.CSession::GetAccessoryActName(charInfo->job, head, g_session.CSession::GetSex(), charInfo->accessory2, tmpName);
		m_viewChar[n].sprName[3] = g_session.CSession::GetAccessorySprName(charInfo->job, head, g_session.CSession::GetSex(), charInfo->accessory2, tmpName);
		m_viewChar[n].actName[4] = g_session.CSession::GetAccessoryActName(charInfo->job, head, g_session.CSession::GetSex(), charInfo->accessory3, tmpName);
		m_viewChar[n].sprName[4] = g_session.CSession::GetAccessorySprName(charInfo->job, head, g_session.CSession::GetSex(), charInfo->accessory3, tmpName);

		m_viewChar[n].bodyPalette = charInfo->bodypalette;
		if( charInfo->bodypalette != 0 )
		{
			char palName[64];
			m_viewChar[n].bodyPaletteName = g_session.CSession::GetBodyPaletteName(charInfo->job, g_session.CSession::GetSex(), charInfo->bodypalette, palName);
		}

		m_viewChar[n].headPalette = charInfo->headpalette;
		if( charInfo->headpalette != 0 )
		{
			char palName[64];
			m_viewChar[n].headPaletteName = g_session.CSession::GetHeadPaletteName(head, charInfo->job, g_session.CSession::GetSex(), charInfo->headpalette, palName);
		}

		m_viewChar[n].imfName = g_session.CSession::GetImfName(charInfo->job, charInfo->head, g_session.CSession::GetSex(), tmpName);
	}

	this->UISelectCharWnd::MakeButton(ID_CANCEL);
	if( m_isEmpty[m_curSlot + 3 * m_curPage] )
	{
		this->UISelectCharWnd::MakeButton(ID_MAKE);
	}
	else
	{
		this->UISelectCharWnd::MakeButton(ID_OK);
		this->UISelectCharWnd::MakeButton(ID_DELETE);
	}

	m_defPushId = ID_OK;
}


void UISelectCharWnd::OnProcess(void) // line 2021
{
}


void UISelectCharWnd::OnDraw(void) // line 2024-2116
{
	CBitmapRes* bmp = (CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp("유저인터페이스\\login_interface\\win_select.bmp"));
	this->UIWindow::DrawBitmap(0, 0, bmp, false);

	for( int j = 0; j < 3; ++j )
	{
		int n = j + 3 * m_curPage;

		if( !m_isAvailable[n] )
		{
			this->UIWindow::TextOutA(82 + j * 163, 107, "Not Avaliable", 0, 1, 18, 0);
			continue;
		}

		if( m_isEmpty[n] )
			continue;

		CacheInfo info = {};
		for( int i = 0; i < 5; ++i )
		{
			if( m_viewChar[n].actName[i].size() == 0 || m_viewChar[n].sprName[i].size() == 0 )
				continue;

			CImfRes* imfRes = (CImfRes*)g_resMgr().CResMgr::Get(m_viewChar[n].imfName.c_str());
			CActRes* actRes = (CActRes*)g_resMgr().CResMgr::Get(m_viewChar[n].actName[i].c_str());
			CSprRes* sprRes = (CSprRes*)g_resMgr().CResMgr::Get(m_viewChar[n].sprName[i].c_str());

			CMotion* mot = actRes->CActRes::GetMotion(m_viewChar[n].curAction, m_viewChar[n].curMotion);
			
			static int s_offX = 0; //NOTE: global variable used only in this function
			static int s_offY = 0; //NOTE: global variable used only in this function
			int offX = 0;
			int offY = 0;

			if( i == 1 )
			{
				CActRes* actRes0 = (CActRes*)g_resMgr().CResMgr::Get(m_viewChar[n].actName[0].c_str());
				CMotion* mot0 = actRes0->CActRes::GetMotion(m_viewChar[n].curAction, m_viewChar[n].curMotion);

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
				CActRes* actRes1 = (CActRes*)g_resMgr().CResMgr::Get(m_viewChar[n].actName[1].c_str());
				CMotion* mot1 = actRes1->CActRes::GetMotion(m_viewChar[n].curAction, m_viewChar[n].curMotion);

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
			if( i == 0 && m_viewChar[n].bodyPalette != 0 )
			{
				CPaletteRes* palres = (CPaletteRes*)g_resMgr().CResMgr::Get(m_viewChar[n].bodyPaletteName.c_str());
				palette = palres->m_pal;
			}
			else
			if( i == 1 && m_viewChar[n].headPalette != 0 )
			{
				CPaletteRes* palres = (CPaletteRes*)g_resMgr().CResMgr::Get(m_viewChar[n].headPaletteName.c_str());
				palette = palres->m_pal;
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

				m_dc->BltTexture2(offX + clip->x + m_viewChar[n].x, offY + clip->y + m_viewChar[n].y, tex, int(info.tu * 256.0), int(info.tv * 256.0), img->width, img->height, clip->flags, img->isHalfW + 1, img->isHalfH + 1);
			}
		}
	}
}


hook_method<void (UISelectCharWnd::*)(int x, int y)> UISelectCharWnd::_OnMouseMove(SAKEXE, "UISelectCharWnd::OnMouseMove");
void UISelectCharWnd::OnMouseMove(int x, int y) // line 2119
{
	return (this->*_OnMouseMove)(x, y);

	//TODO
}


hook_method<void (UISelectCharWnd::*)(int x, int y)> UISelectCharWnd::_OnLBtnDown(SAKEXE, "UISelectCharWnd::OnLBtnDown");
void UISelectCharWnd::OnLBtnDown(int x, int y) // line 2124
{
	return (this->*_OnLBtnDown)(x, y);

	//TODO
}


hook_method<int (UISelectCharWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UISelectCharWnd::_SendMsg(SAKEXE, "UISelectCharWnd::SendMsg");
int UISelectCharWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3) // line 2129
{
	return (this->*_SendMsg)(sender, message, val1, val2, val3);

	//TODO
}


hook_method<void (UISelectCharWnd::*)(void)> UISelectCharWnd::_InvalidateWallPaper(SAKEXE, "UISelectCharWnd::InvalidateWallPaper");
void UISelectCharWnd::InvalidateWallPaper(void) // line 1805
{
	return (this->*_InvalidateWallPaper)();

	;
}


hook_method<void (UISelectCharWnd::*)(int id)> UISelectCharWnd::_MakeButton(SAKEXE, "UISelectCharWnd::MakeButton");
void UISelectCharWnd::MakeButton(int id) // line 1633
{
	return (this->*_MakeButton)(id);

	//TODO
}


hook_method<void (UISelectCharWnd::*)(int id)> UISelectCharWnd::_DeleteButton(SAKEXE, "UISelectCharWnd::DeleteButton");
void UISelectCharWnd::DeleteButton(int id) // line 1740
{
	return (this->*_DeleteButton)(id);

	//TODO
}


void UISelectCharWnd::InitTextControls(void) // line 1764
{
	CHARACTER_INFO* charInfo = (CHARACTER_INFO*)g_modeMgr.CModeMgr::GetCurMode()->SendMsg(8, m_curSlot + 3 * m_curPage, 0, 0);
	if( charInfo != NULL )
	{
		char buf[100];
		char nameBuf[24+1];
		memcpy(nameBuf, charInfo->name, 24); nameBuf[24] = '\0';
		m_text[0]->UIStaticText::SetTextWithShorten(nameBuf);
		m_text[1]->UIStaticText::SetTextWithShorten(g_session.m_jobNameTable[charInfo->job]);
		sprintf(buf, "%d", charInfo->level);
		m_text[2]->UIStaticText::SetTextWithShorten(buf);
		sprintf(buf, "%d", charInfo->exp);
		m_text[3]->UIStaticText::SetTextWithShorten(buf);
		sprintf(buf, "%d", charInfo->hp);
		m_text[4]->UIStaticText::SetTextWithShorten(buf);
		sprintf(buf, "%d", charInfo->sp);
		m_text[5]->UIStaticText::SetTextWithShorten(buf);
		sprintf(buf, "%d", charInfo->Str);
		m_text[6]->UIStaticText::SetTextWithShorten(buf);
		sprintf(buf, "%d", charInfo->Agi);
		m_text[7]->UIStaticText::SetTextWithShorten(buf);
		sprintf(buf, "%d", charInfo->Vit);
		m_text[8]->UIStaticText::SetTextWithShorten(buf);
		sprintf(buf, "%d", charInfo->Int);
		m_text[9]->UIStaticText::SetTextWithShorten(buf);
		sprintf(buf, "%d", charInfo->Dex);
		m_text[10]->UIStaticText::SetTextWithShorten(buf);
		sprintf(buf, "%d", charInfo->Luk);
		m_text[11]->UIStaticText::SetTextWithShorten(buf);
	}
	else
	{
		for( int i = 0; i < 12; ++i )
			m_text[i]->UIStaticText::SetText("", 0);
	}
}


hook_method<void (UISelectCharWnd::*)(void)> UISelectCharWnd::_InitFromReg(SAKEXE, "UISelectCharWnd::InitFromReg");
void UISelectCharWnd::InitFromReg(void) // line 1941
{
	return (this->*_InitFromReg)();

	//TODO
}


hook_method<void (UISelectCharWnd::*)(void)> UISelectCharWnd::_WriteToReg(SAKEXE, "UISelectCharWnd::WriteToReg");
void UISelectCharWnd::WriteToReg(void) // line 1977
{
	return (this->*_WriteToReg)();

	//TODO
}
