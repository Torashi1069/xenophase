#include "GameMode.h"
#include "GameWorld.h"
#include "Globals.h"
#include "Packet.h"
#include "Picker.h"
#include "Player.h"
#include "Session.h"
#include "Struct.h"
#include "View.h"
#include "3dLib/Renderer.h"
#include "Device/Control.h"
#include "Resource/Attr.h"
#include "Window/UIControl.h"
#include "Window/UIWindowMgr.h"
#include "Window/UISys.h"
const float infinity = 999999.0;


hook_func<CGameMode* (CGameMode::*)(void)> CGameMode::_cCGameMode("CGameMode::CGameMode");
CGameMode::CGameMode(void)
{
	(this->*_cCGameMode)(); return;
}


hook_func<void (CGameMode::*)(void)> CGameMode::_dCGameMode("CGameMode::~CGameMode");
CGameMode::~CGameMode(void)
{
	(this->*_dCGameMode)(); return;
}


hook_func<int (CGameMode::*)(void)> CGameMode::_OnRun("CGameMode::OnRun");
int CGameMode::OnRun(void)
{
	return (this->*_OnRun)();

	while( m_loopCond )
	{
		if( g_sysQuit )
			break;

		if( !g_windowMgr.UIWindowMgr::IsModalStatus() )
		{
			if( m_nextSubMode != -1 )
			{
				m_subMode = m_nextSubMode;
				m_subModeCnt = 0;
				m_nextSubMode = -1;
				this->OnChangeState(m_subMode);
			}
		}

		this->OnUpdate();
	}

	this->CMode::RunFadeOut(FALSE);
	return 1;
}


hook_func<void (CGameMode::*)(const char* modeName)> CGameMode::_OnInit("CGameMode::OnInit");
void CGameMode::OnInit(const char* modeName)
{
	return (this->*_OnInit)(modeName);
}


hook_func<void (CGameMode::*)(void)> CGameMode::_OnExit("CGameMode::OnExit");
void CGameMode::OnExit(void)
{
	return (this->*_OnExit)();
}


hook_func<void (CGameMode::*)(void)> CGameMode::_OnUpdate("CGameMode::OnUpdate");
void CGameMode::OnUpdate(void)
{
	return (this->*_OnUpdate)();
}


hook_func<void (CGameMode::*)(int a1)> CGameMode::_vfn5("CGameMode::vfn5");
void CGameMode::vfn5(int a1)
{
	return (this->*_vfn5)(a1);
}


hook_func<int (CGameMode::*)(int messageId, int val1, int val2, int val3)> CGameMode::_SendMsg("CGameMode::SendMsg");
int CGameMode::SendMsg(int messageId, int val1, int val2, int val3)
{
	return (this->*_SendMsg)(messageId, val1, val2, val3);
}


hook_func<void (CGameMode::*)(int state)> CGameMode::_OnChangeState("CGameMode::OnChangeState");
void CGameMode::OnChangeState(int state)
{
	return (this->*_OnChangeState)(state);
}


CWorld* CGameMode::GetWorld(void)
{
	return m_world;
}


CView* CGameMode::GetView(void)
{
	return m_view;
}


hook_func<void (CGameMode::*)(void)> CGameMode::_Initialize("CGameMode::Initialize");
void CGameMode::Initialize(void)
{
	return (this->*_Initialize)();
}


hook_func<void (CGameMode::*)(void)> CGameMode::_SetCamera("CGameMode::SetCamera");
void CGameMode::SetCamera(void)
{
	return (this->*_SetCamera)();
}


hook_method<void (CGameMode::*)(void)> CGameMode::_RemoveGameActorAllAndMake("CGameMode::RemoveGameActorAllAndMake");
void CGameMode::RemoveGameActorAllAndMake(void)
{
	return (this->*_RemoveGameActorAllAndMake)();
}


//hook_func<void (CGameMode::*)(vector2d& pos)> CGameMode::_MakeMousePointer("CGameMode::MakeMousePointer");
void CGameMode::MakeMousePointer(vector2d& pos) // inlined
{
//	return (this->*_MakeMousePointer)();

	pos.x = (float)g_mouse.CMouse::GetXPos();
	pos.y = (float)g_mouse.CMouse::GetYPos();
}


hook_func<void (CGameMode::*)(CActorPickInfo* actorInfo, int processType)> CGameMode::_MakeMenu("CGameMode::MakeMenu");
void CGameMode::MakeMenu(CActorPickInfo* actorInfo, int processType)
{
	return (this->*_MakeMenu)(actorInfo, processType);
}


hook_func<void (CGameMode::*)(CActorPickInfo* actorInfo, int processType)> CGameMode::_ProcessMouseSnap("CGameMode::ProcessMouseSnap");
void CGameMode::ProcessMouseSnap(CActorPickInfo* actorInfo, int processType)
{
	return (this->*_ProcessMouseSnap)(actorInfo, processType);
}


hook_func<void (CGameMode::*)(int processType)> CGameMode::_ProcessWheel("CGameMode::ProcessWheel");
void CGameMode::ProcessWheel(int processType)
{
	return (this->*_ProcessWheel)(processType);
}


hook_func<void (CGameMode::*)(void)> CGameMode::_ProcessRBtn("CGameMode::ProcessRBtn");
void CGameMode::ProcessRBtn(void)
{
	return (this->*_ProcessRBtn)();
}


hook_func<int (CGameMode::*)(int processType)> CGameMode::_ProcessGroundPick("CGameMode::ProcessGroundPick");
int CGameMode::ProcessGroundPick(int processType)
{
	return (this->*_ProcessGroundPick)(processType);
}


hook_func<void (CGameMode::*)(void)> CGameMode::_UnloadRarelyUsedCaches("CGameMode::UnloadRarelyUsedCaches");
void CGameMode::UnloadRarelyUsedCaches(void)
{
	return (this->*_UnloadRarelyUsedCaches)();
}


hook_func<void (CGameMode::*)(void)> CGameMode::_ProcessReqEmblem("CGameMode::ProcessReqEmblem");
void CGameMode::ProcessReqEmblem(void)
{
	return (this->*_ProcessReqEmblem)();
}


hook_func<void (CGameMode::*)(void)> CGameMode::_ProcessNameWaitingTimer("CGameMode::ProcessNameWaitingTimer");
void CGameMode::ProcessNameWaitingTimer(void)
{
	return (this->*_ProcessNameWaitingTimer)();
}


hook_func<void (CGameMode::*)(void)> CGameMode::_ProcessPeriodicalJobs("CGameMode::ProcessPeriodicalJobs");
void CGameMode::ProcessPeriodicalJobs(void)
{
	return (this->*_ProcessPeriodicalJobs)();
}


hook_func<void (CGameMode::*)(float cx, float cz, int& sx, int& sy, int& cellX, int& cellY)> CGameMode::_GetServerCoor("CGameMode::GetServerCoor");
void CGameMode::GetServerCoor(float cx, float cz, int& sx, int& sy, int& cellX, int& cellY)
{
	return (this->*_GetServerCoor)(cx, cz, sx, sy, cellX, cellY);
}


hook_func<void (CGameMode::*)(float cx, float cz, int& sx, int& sy)> CGameMode::_GetServerCoor2("CGameMode::GetServerCoor(2)");
void CGameMode::GetServerCoor(float cx, float cz, int& sx, int& sy)
{
	return (this->*_GetServerCoor2)(cx, cz, sx, sy);
}


hook_func<void (CGameMode::*)(int sx, int sy, int subX, int subY, float& cx, float& cz)> CGameMode::_GetClientCoor("CGameMode::GetClientCoor");
void CGameMode::GetClientCoor(int sx, int sy, int subX, int subY, float& cx, float& cz)
{
	return (this->*_GetClientCoor)(sx, sy, subX, subY, cx, cz);
}


hook_func<void (CGameMode::*)(int sx, int sy, float& cx, float& cz)> CGameMode::_GetClientCoor2("CGameMode::GetClientCoor(2)");
void CGameMode::GetClientCoor(int sx, int sy, float& cx, float& cz)
{
	return (this->*_GetClientCoor2)(sx, sy, cx, cz);
}


hook_func<bool (CGameMode::*)(int x, int y)> CGameMode::_IsRedCell("CGameMode::IsRedCell");
bool CGameMode::IsRedCell(int x, int y)
{
	return (this->*_IsRedCell)(x, y);

	CAttrCell* cell = m_world->m_attr->C3dAttr::GetCell(x, y);
	if( cell == NULL ) return true;
	if( cell->flag == 1 ) return true;
	if( cell->flag == 5 ) return true;
	return false;
}


hook_func<bool (CGameMode::*)(int sx, int sy, int cellX, int cellY, int dx, int dy)> CGameMode::_CanFindPath("CGameMode::CanFindPath");
bool CGameMode::CanFindPath(int sx, int sy, int cellX, int cellY, int dx, int dy)
{
	return (this->*_CanFindPath)(sx, sy, cellX, cellY, dx, dy);
}


hook_func<bool (CGameMode::*)(int x, int y)> CGameMode::_IsRegisterCell("CGameMode::IsRegisterCell");
bool CGameMode::IsRegisterCell(int x, int y)
{
	return (this->*_IsRegisterCell)(x, y);

	for( mystd::map<unsigned long,CellPos>::const_iterator it = m_actorPosList.begin(); it != m_actorPosList.end(); ++it )
		if( it->second.x == x && it->second.y == y )
			return true; // cell is occupied

	return false; // cell is empty
}


hook_func<bool (CGameMode::*)(int& dx, int& dy)> CGameMode::_GetClosestValidCell("CGameMode::GetClosestValidCell");
bool CGameMode::GetClosestValidCell(int& dx, int& dy)
{
	return (this->*_GetClosestValidCell)(dx, dy);

	int offset[18] = {
		 0, 0,
		 1, 0,
		 1, 1,
		 1,-1,
		-1, 0,
		-1, 1,
		-1,-1,
		 0, 1,
		 0,-1};

	int sx, sy, cellX, cellY; // current player position
	this->CGameMode::GetServerCoor(m_world->m_player->m_pos.x, m_world->m_player->m_pos.z, sx, sy, cellX, cellY);

	int deltaX = sx - dx;
	int deltaY = sy - dy;

	if( abs(deltaX) < abs(deltaY) )
	{// vertical movement
		if( deltaY == 0 )
			return false;

		int signY = (((deltaY <= 0) - 1) & 2) - 1;
		for( int y = dy; y != sy; y += signY )
		{
			int x = dx + deltaX * (y - dy) / deltaY;
			for( int offIndex = 0; offIndex < countof(offset) / 2; ++offIndex )
			{
				int destX = x + offset[2*offIndex + 0];
				int destY = y + offset[2*offIndex + 1];

				if( this->CGameMode::IsRedCell(destX, destY) ) // inlined
					continue; // cell is not walkable

				if( this->CGameMode::IsRegisterCell(destX, destY) ) // inlined
					continue; // cell is occupied

				if( !this->CGameMode::CanFindPath(sx, sy, cellX, cellY, destX, destY) )
					return false; // cell is not reachable

				dx = destX;
				dy = destY;
				return true;
			}
		}
	}
	else
	{// horizontal movement
		if( deltaX == 0 )
			return false;

		int signX = (((deltaX <= 0) - 1) & 2) - 1;
		for( int x = dx; x != sx; x += signX )
		{
			int y = dy + deltaY * (y - dx) / deltaX;
			for( int offIndex = 0; offIndex < countof(offset) / 2; ++offIndex )
			{
				int destX = x + offset[2*offIndex + 0];
				int destY = y + offset[2*offIndex + 1];

				if( this->CGameMode::IsRedCell(destX, destY) ) // inlined
					continue; // cell is not walkable

				if( this->CGameMode::IsRegisterCell(destX, destY) ) // inlined
					continue; // cell is occupied

				if( !this->CGameMode::CanFindPath(sx, sy, cellX, cellY, destX, destY) )
					return false; // cell is not reachable

				dx = destX;
				dy = destY;
				return true;
			}
		}
	}

	return false;
}


hook_func<void (CGameMode::*)(void)> CGameMode::_InvalidatePlayerGage("CGameMode::InvalidatePlayerGage");
void CGameMode::InvalidatePlayerGage(void)
{
	return (this->*_InvalidatePlayerGage)();
}


hook_func<void (CGameMode::*)(void)> CGameMode::_HideCheck("CGameMode::HideCheck");
void CGameMode::HideCheck(void)
{
	return (this->*_HideCheck)();
}


hook_func<void (CGameMode::*)(int time)> CGameMode::_HideMousePointer("CGameMode::HideMousePointer");
void CGameMode::HideMousePointer(int time)
{
	return (this->*_HideMousePointer)(time);
}


hook_func<void (CGameMode::*)(void)> CGameMode::_ProcessInput("CGameMode::ProcessInput");
void CGameMode::ProcessInput(void)
{
	return (this->*_ProcessInput)();

	g_mouse.CMouse::ReadState();
	int processType = g_windowMgr.UIWindowMgr::ProcessInput();
	g_windowMgr.UIWindowMgr::OnProcess();
	this->CGameMode::ProcessNameBalloon();
	this->CMode::ProcessHelpBalloon();
	this->CGameMode::ProcessRBtn();
	this->CGameMode::ProcessWheel(processType);
	this->CMode::ProcessKeyBoard();
	this->CGameMode::ProcessPeriodicalJobs(); // inlined

	if( processType == 2 )
		processType = 0;

	if( m_skillUseInfo.m_skillUseType != SUT_NOSKILL )
	{
		if( g_session.m_isQ2begin == 0 )
		{
			if( g_mouse.CMouse::GetWheel() > 0 )
				this->SendMsg(93, 1, 0, 0);
			else
			if( g_mouse.CMouse::GetWheel() < 0 )
				this->SendMsg(94, 1, 0, 0);
		}

		g_session.m_isQ2begin = 0;
	}

	if( g_mouse.CMouse::GetLBtn() == BTN_UP )
	{
		if( m_world->m_player != NULL )
			m_world->m_player->SendMsg(0, 15, 0, 0, 0);
		this->SendMsg(17, g_mouse.CMouse::GetXPos(), g_mouse.CMouse::GetYPos(), 0);
		if( g_windowMgr.m_menu != NULL )
			g_windowMgr.UIWindowMgr::DeleteWindow(WID_MENUWND);
		m_isAutoMoveClickOn = 1;
	}

	g_shiftKeyPressed = GetAsyncKeyState(VK_SHIFT) >> 8;

	vector2d pos;
	this->CGameMode::MakeMousePointer(pos); // inlined
	CActorPickInfo* actorInfo = g_actorPickNode.CActorPickNode::FindPickInfo(pos);

	if( g_windowMgr.m_exchangeWnd == NULL )
		this->CGameMode::MakeMenu(actorInfo, processType);

	this->CGameMode::ProcessMouseSnap(actorInfo, processType);
	this->CGameMode::HideCheck();

	if( m_isOnQuest || m_isPlayerDead || g_windowMgr.m_exchangeWnd || g_windowMgr.m_itemStoreWnd || g_windowMgr.m_mailListWnd || g_windowMgr.m_mailViewWnd || g_windowMgr.m_auctionWnd )
	{
		if( actorInfo != NULL && processType == 0 )
			this->CGameMode::MakeNameBalloon(actorInfo->m_gid);
	}
	else
	{
		processType = this->CGameMode::ProcessActorPick(processType, actorInfo);
		processType = this->CGameMode::ProcessGroundPick(processType);
		this->CGameMode::ProcessLockOnMouse();
	}

	if( g_mouse.CMouse::GetLBtn() == BTN_DOWN )
	{
		g_checkBOT = 0;
		this->SendMsg(71, 0, 0, 0);
		if( timeGetTime() > m_noMoveStartTick + 5000 )
			m_noMove = 0;
		m_leftBtnClickTick = timeGetTime();
	}

	if( g_session.m_StateInfoOn )
		this->CGameMode::ProcessStateInfoBalloon(g_mouse.CMouse::GetXPos(), g_mouse.CMouse::GetYPos());

	if( m_skillUseInfo.m_skillUseType != SUT_NOSKILL )
	{
		if( processType == 0 )
			this->CMode::SetCursorAction(10);
	}
	else
	{
		if( processType == 0 && g_mouse.CMouse::GetRBtn() != BTN_PRESSED )
			this->CMode::SetCursorAction(0);
	}

	m_oldMouseX = g_mouse.CMouse::GetXPos();
	m_oldMouseY = g_mouse.CMouse::GetXPos();
}


hook_func<bool (CGameMode::*)(int& dx, int& dy)> CGameMode::_GetGroundAttrPos("CGameMode::GetGroundAttrPos");
bool CGameMode::GetGroundAttrPos(int& dx, int& dy)
{
	return (this->*_GetGroundAttrPos)(dx, dy);

	CRayPicker picker;
	ray3d ray;

	g_renderer->CRenderer::BuildRay(g_mouse.CMouse::GetXPos(), g_mouse.CMouse::GetYPos(), m_view->CView::GetFrom(), m_view->CView::GetViewMatrix(), &ray);
	picker.CRayPicker::Build(ray, m_world->CWorld::GetRootNode());

	float nearest = infinity;
	for( mystd::list<SceneGraphNode*>::const_iterator ni = picker.m_cubeletList.begin(); ni != picker.m_cubeletList.end(); ++ni )
	{
		SceneGraphNode* node = *ni;
		C3dAttr* attr = node->m_attr;

		for( int y = node->m_attrArea.top; y <= node->m_attrArea.bottom; ++y )
		{
			for( int x = node->m_attrArea.left; x <= node->m_attrArea.right; ++x )
			{
				float dist = attr->C3dAttr::RayTest(ray, x, y);
				if( dist < nearest )
				{
					nearest = dist;
					dx = x;
					dy = y;
				}
			}
		}
	}

	return ( nearest < infinity );
}


hook_func<void (CGameMode::*)(int val1, int val2)> CGameMode::_ProcessTalkType("CGameMode::ProcessTalkType");
void CGameMode::ProcessTalkType(int val1, int val2)
{
	return (this->*_ProcessTalkType)(val1, val2);
}


hook_func<void (CGameMode::*)(void)> CGameMode::_ProcessLockOnMouse("CGameMode::ProcessLockOnMouse");
void CGameMode::ProcessLockOnMouse(void)
{
	return (this->*_ProcessLockOnMouse)();
}


hook_func<int (CGameMode::*)(int processType, CActorPickInfo* actorInfo)> CGameMode::_ProcessActorPick("CGameMode::ProcessActorPick");
int CGameMode::ProcessActorPick(int processType, CActorPickInfo* actorInfo)
{
	return (this->*_ProcessActorPick)(processType, actorInfo);
}


hook_func<void (CGameMode::*)(unsigned long aid)> CGameMode::_MakeNameBalloon("CGameMode::MakeNameBalloon");
void CGameMode::MakeNameBalloon(unsigned long aid)
{
	return (this->*_MakeNameBalloon)(aid);
/*
	if( aid == 0 )
		return;

	m_nameActorAid = aid;

	CGameActor* actor = m_world->CWorld::GetGameActorByAID(aid);
	if( actor != NULL )
	{
		if( actor->CGameActor::GetJob() != JT_WARPNPC )
		{
			m_nameDisplayed = 0;
			this->CGameMode::MakeActorNameBalloon(actor);

			if( this->dummy_538[33] )
			{
				if( g_session.CSession::IsPc(actor->CGameActor::GetJob()) )
				{
					if( unknown_libname_1886(g_session.CSession::GetAid()) )
					{
						string& s = this->CGameMode::sub_5A43E0(aid);
						g_windowMgr.UIWindowMgr::sub_5035F0(s.c_str());
					}
				}
			}
		}
		return;
	}

	if( aid == g_session.CSession::GetAid() )
	{
		m_nameDisplayed = 0;
		this->CGameMode::MakeActorNameBalloon(m_world->m_player);
		return;
	}

	CItem* item = m_world->CWorld::GetItemByAID(aid);
	if( item != NULL )
	{
		mystd::string nameMsg = item->m_itemName.c_str();
		m_nameDisplayed = 0;
		this->CGameMode::MakeNameBalloonTextWindow((UIWindow**)&m_nameBalloon);
		m_nameBalloon->SetNameText(nameMsg.c_str());
		m_nameBalloon->SetEmblemResName("");
		m_nameBalloon->UIBalloonText::SetFntColor(0x95EFFF, 0);
		m_nameBalloonWidth = m_nameBalloon->UIWindow::GetWidth();
		m_nameBalloonHeight = m_nameBalloon->UIWindow::GetHeight();
		this->CGameMode::MoveBalloonTextWindow(m_nameBalloon, item);
	}
*/
}


hook_func<void (CGameMode::*)(CGameActor* theActor)> CGameMode::_MakeActorNameBalloon("CGameMode::MakeActorNameBalloon");
void CGameMode::MakeActorNameBalloon(CGameActor* theActor)
{
	return (this->*_MakeActorNameBalloon)(theActor);
/*
	this->CGameMode::MakeNameBalloonTextWindow((UIWindow**)&m_nameBalloon);

	const NamePair& np = this->CGameMode::GetActorName(theActor->CGameActor::GetGID());
	if( !np.cName._Len )
		return;

	np.cName = this->CGameMode::sub_5A43E0(theActor->m_gid);
	bool cutSharp = !theActor->CGameActor::IsThisPC(theActor->CGameActor::GetJob());
	m_nameBalloon->SetNameText(np, cutSharp);

	char emblemResName[256];
	const char* pemblemResName;

	if( theActor->GetGdid() && g_session.m_emblemState )
	{
		g_session.CSession::GetEmblemFileName(emblemResName, theActor->GetGdid(), theActor->GetEmblemVersion());
		pemblemResName = emblemResName;
	}
	else
	{
		pemblemResName = "";
	}

	m_nameBalloon->SetEmblemResName(pemblemResName);
	m_nameBalloonWidth = m_nameBalloon->UIWindow::GetWidth();
	m_nameBalloonHeight = m_nameBalloon->UIWindow::GetHeight();

	if( g_serviceType != 12 )
	{
		int job = theActor->CGameActor::GetJob();
		unsigned long color;

		if( IsNameYellow(theActor->m_gid) )
			color = 0x0000FFFF;
		else
		if( IsNameSpecific(theActor->m_gid) )
			color = IsNameSpecific(theActor->m_gid);
		else
		if( this->field_230->sub_5B7650(theActor->m_gid) != this->field_230._Last )
			color = 0x006A6DEE;
		else
		if( job > 45 && job < 1000 )
			color = 0x00F7B895;
		else
		if( job > 1000 && job < 4000 )
			color = 0x00C3C3FF;
		else
			color = 0x00FFFFFF;

		m_nameBalloon->m_fontColor = color;
		m_nameBalloon->m_bgColor = 0;
	}
	else
	{
		switch( theActor->m_gid )
		{
		case 1610001:
		case 1610002:
		case 1610003:
		case 1610004:
		case 1610006:
		case 1610007:
		case 1610009:
		case 1610010:
			m_nameBalloon->m_fontColor = 0x000000FF;
			m_nameBalloon->m_bgColor = 0x00646464;
			break;
		default:
			int job = theActor->CGameActor::GetJob();
			unsigned long color;

			if( IsNameYellow(theActor->m_gid) )
				color = 0x0000FFFF;
			else
			if( IsNameSpecific(theActor->m_gid) )
				color = IsNameSpecific(theActor->m_gid);
			else
			if( this->field_230->sub_5B7650(theActor->m_gid) != this->field_230._Last )
				color = 0x006A6DEE;
			else
			if( job > 45 && job < 1000 )
				color = 0x00F7B895;
			else
			if( job > 1000 && job < 4000 )
				color = 0x00C3C3FF;
			else
				color = 0x00FFFFFF;

			m_nameBalloon->m_fontColor = color;
			m_nameBalloon->m_bgColor = 0;
			break;
		}
	}

	// this->field_4[444] = actor->baselevel, word_837FAC = g_session.baselevel?
	if( !theActor->CGameActor::IsThisPC(theActor->CGameActor::GetJob()) && *(_WORD *)&this->field_4[444] > 0 && theActor->CGameActor::sub_6F12D0() )
	{
		int difference = word_837FAC - *(_WORD *)&this->field_4[444];

		if( difference < -10 )
		{
			m_nameBalloon->m_fontColor = 0x000000FF;
			m_nameBalloon->m_bgColor = 0x00000000;
		}
		else
		if( difference > 15 )
		{
			m_nameBalloon->m_fontColor = 0x009B9B9B;
			m_nameBalloon->m_bgColor = 0x00000000;
		}
	}

	this->CGameMode::MoveBalloonTextWindow(m_nameBalloon, theActor);
*/
}


hook_func<void (CGameMode::*)(void)> CGameMode::_ProcessNameBalloon("CGameMode::ProcessNameBalloon");
void CGameMode::ProcessNameBalloon(void)
{
	return (this->*_ProcessNameBalloon)();
}


hook_func<void (CGameMode::*)(int xPos, int yPos)> CGameMode::_ProcessStateInfoBalloon("CGameMode::ProcessStateInfoBalloon");
void CGameMode::ProcessStateInfoBalloon(int xPos, int yPos)
{
	return (this->*_ProcessStateInfoBalloon)(xPos, yPos);

	if( m_stateinfoBalloon != NULL )
		m_stateinfoBalloon->SetShow(0);

	int nStates = stateId.size() / 3;
	if( nStates == 0 )
		return;

	int nMaxVertical = (g_renderer->CRenderer::GetHeight() - 169) / 35;
	int nColumns = nStates / nMaxVertical + ( nStates % nMaxVertical != 0 );

	int xPosMax = g_renderer->CRenderer::GetWidth() - 18;
	if( xPos < xPosMax - 45 * nColumns + 15 || xPos > xPosMax )
	{
		m_lastEfstId = -1;
		return;
	}

	if( yPos < 168 || yPos > 168 + 35 * nMaxVertical )
	{
		m_lastEfstId = -1;
		return;
	}

	int xDelta = xPosMax - xPos;
	int xSize = 45 * (xDelta / 45 + (xDelta % 45 != 0));
	if( xSize - 15 < xDelta && xDelta < xSize )
		return;

	int yDelta = yPos - 168;
	int ySize = 35 * (yDelta / 35 + (yDelta % 35 != 0));
	if( ySize - 5 < yDelta && yDelta < ySize )
		return;

	int nIconPos = yDelta / 35 + xDelta / 45 * nMaxVertical;
	if( nIconPos >= nStates )
		return;

	int efstId = g_session.m_DrawList[nIconPos];
	if( efstId == -1 )
	{
		m_lastEfstId = -1;

		if( m_stateinfoBalloon != NULL )
			m_stateinfoBalloon->UIBalloonText::SetText(" ", 35);

		return;
	}

	int bHaveTimeLimit = 0;
	int posOfTimeLimit = -1;
	g_session.m_lua->CLua::Execute("GetTimeLimitInfo", "d>dd", efstId, &bHaveTimeLimit, &posOfTimeLimit);

	int efstId2 = efstId;
	mystd::string strRemainingTime;
	if( bHaveTimeLimit )
		strRemainingTime = this->CGameMode::GetStateRemainingTimeStr(efstId, &efstId2);

	if( m_lastEfstId == efstId )
	{
		if( m_stateinfoBalloon != NULL )
			if( m_stateinfoBalloon->UITransBalloonText::GetText(0) != " " )
				m_stateinfoBalloon->SetShow(1);
	}
	else
	{
		if( m_stateinfoBalloon != NULL )
		{
			m_stateinfoBalloon->UIBalloonText::SetText(" ", 35);
		}
		else
		{
			m_stateinfoBalloon = new UITransBalloonText();
			m_stateinfoBalloon->UIWindow::Create(50, 50);
			g_windowMgr.UIWindowMgr::AddWindow(m_stateinfoBalloon);
			m_stateinfoBalloon->UIBalloonText::SetFntSize(11);
			m_stateinfoBalloon->UITransBalloonText::SetBorderLineColor(0xC0C0C0);
		}

		for( int i = 1; true; ++i )
		{
			int textR, textG, textB;
			const char* szDesc;

			do //FIXME: what's the point of looping here?
			{
				textR = 0;
				textG = 0;
				textB = 0;
				szDesc = NULL;
			}
			while( !g_session.m_lua->CLua::Execute("GetStateIconDescript", "dd>sddd", efstId2, i, &szDesc, &textR, &textG, &textB) );

			mystd::string strDesc = szDesc;
			if( strDesc.size() == 0 )
			{
				if( m_stateinfoBalloon->UITransBalloonText::GetText(0) != " " )
				{
					m_stateinfoBalloon->SetShow(1);

					int x = xPosMax - nIconPos / nMaxVertical * 45 - m_stateinfoBalloon->UIWindow::GetWidth() - 30;
					int y = 171 + nIconPos % nMaxVertical * 35;

					if( y > g_renderer->CRenderer::GetHeight() - m_stateinfoBalloon->UIWindow::GetHeight() )
						y = g_renderer->CRenderer::GetHeight() - m_stateinfoBalloon->UIWindow::GetHeight();

					m_stateinfoBalloon->Move(x, y);
				}

				m_lastEfstId = efstId;
				break;
			}

			if( i == posOfTimeLimit )
			{// this line undergoes special processing
				char* descBuf = new char[strDesc.size() + strRemainingTime.size()]; //FIXME: no room for zero terminator
				sprintf(descBuf, strDesc.c_str(), strRemainingTime.c_str());
				strDesc = descBuf;
				delete[] descBuf;
			}

			COLORREF textColor = BYTE(textR) << 0 | BYTE(textG) << 8 | BYTE(textB) << 16 | BYTE(0) << 24;

			if( i == 1 )
			{// initial insert
				m_stateinfoBalloon->UITransBalloonText::SetText(strDesc.c_str(), textColor);
			}
			else
			if( m_stateinfoBalloon->UITransBalloonText::GetText(0) != " " )
			{// followup insert
				m_stateinfoBalloon->UITransBalloonText::AddText(strDesc.c_str(), textColor);
			}
		}
	}

	if( bHaveTimeLimit && strRemainingTime.size() != 0 && posOfTimeLimit != -1 )
	{// update status duration text
		if( m_stateinfoBalloon != NULL )
		{
			const char* szDesc = 0;
			if( g_session.m_lua->CLua::Execute("GetStateIconDescript", "dd>s", efstId2, posOfTimeLimit, &szDesc) )
			{
				mystd::string strDesc = szDesc;
				char* descBuf = new char[strDesc.size() + strRemainingTime.size()]; //FIXME: no room for zero terminator
				sprintf(descBuf, strDesc.c_str(), strRemainingTime.c_str());
				strDesc = descBuf;
				delete[] descBuf;

				m_stateinfoBalloon->UITransBalloonText::ChangeText(strDesc.c_str(), posOfTimeLimit - 1);
			}
		}
	}
}


hook_func<mystd::string (CGameMode::*)(int in_EFST, int* out_EFST)> CGameMode::_GetStateRemainingTimeStr("CGameMode::GetStateRemainingTimeStr");
mystd::string CGameMode::GetStateRemainingTimeStr(int in_EFST, int* out_EFST)
{
	return (this->*_GetStateRemainingTimeStr)(in_EFST, out_EFST);

	mystd::string str;
	*out_EFST = in_EFST;
	
	for( mystd::vector<int>::const_iterator it = stateId.begin(); it != stateId.end(); it += 3 )
	{
		int EFST = *(it + 0);
		int tick = *(it + 1);
		int val3 = *(it + 2);

		if( EFST == 42 )
			EFST = 12;

		if( in_EFST != EFST )
			continue; // keep searching

		*out_EFST = EFST; //FIXME: what's the point?

		if( tick == 999999 || tick == 0 )
			break; // infinite duration.

		int total = tick / 1000 - timeGetTime() / 1000;

		int hours = total / 3600;
		if( hours != 0 )
		{
			char buf[100];
			sprintf(buf, "%d 시간 ", hours);
			str += buf;
		}

		int remain_seconds = total % 3600;

		int minutes = remain_seconds / 60;
		if( minutes != 0 )
		{
			char buf[100];
			sprintf(buf, "%d 분 ", minutes);
			str += buf;
		}

		int seconds = remain_seconds % 60;
		if( seconds != 0 )
		{
			char buf[100];
			sprintf(buf, "%d 초", seconds);
			str += buf;
		}

		break; // string complete.
	}

	return str;
}


hook_func<CGameActor* (CGameMode::*)(int job)> CGameMode::_NewNpc("CGameMode::NewNpc");
CGameActor* CGameMode::NewNpc(int job)
{
	return (this->*_NewNpc)(job);

	//TODO
}


hook_func<void (CGameMode::*)(int GID, int effectState, int clevel, int showEFST)> CGameMode::_GameModeShowEFST("CGameMode::GameModeShowEFST");
void CGameMode::GameModeShowEFST(int GID, int effectState, int clevel, int showEFST)
{
	return (this->*_GameModeShowEFST)(GID, effectState, clevel, showEFST);

	//TODO
}


hook_func<void (CGameMode::*)(CGameActor* theActor, int gdid, int emblemVer)> CGameMode::_MakeEmblemWnd("CGameMode::MakeEmblemWnd");
void CGameMode::MakeEmblemWnd(CGameActor* theActor, int gdid, int emblemVer)
{
	return (this->*_MakeEmblemWnd)(theActor, gdid, emblemVer);

	//TODO
}


hook_func<mystd::string (CGameMode::*)(int aid)> CGameMode::_GetActorName2010("CGameMode::GetActorName2010");
mystd::string CGameMode::GetActorName2010(int aid)
{
	return (this->*_GetActorName2010)(aid);

	//TODO
}


class hook_ptr<struct mystd::_Tree<unsigned long,struct mystd::pair<unsigned long const ,struct CellPos>,struct mystd::map<unsigned long,struct CellPos,struct mystd::less<unsigned long>,class mystd::allocator<struct CellPos> >::_Kfn,struct mystd::less<unsigned long>,class mystd::allocator<struct CellPos> >::_Node *> mystd::_Tree<unsigned long,struct mystd::pair<unsigned long const ,struct CellPos>,struct mystd::map<unsigned long,struct CellPos,struct mystd::less<unsigned long>,class mystd::allocator<struct CellPos> >::_Kfn,struct mystd::less<unsigned long>,class mystd::allocator<struct CellPos> >::_Nil("std::map<unsigned long,CellPos>::_Nil");
class hook_val<unsigned int> mystd::_Tree<unsigned long,struct mystd::pair<unsigned long const ,struct CellPos>,struct mystd::map<unsigned long,struct CellPos,struct mystd::less<unsigned long>,class mystd::allocator<struct CellPos> >::_Kfn,struct mystd::less<unsigned long>,class mystd::allocator<struct CellPos> >::_Nilrefs("std::map<unsigned long,CellPos>::_Nilrefs");
