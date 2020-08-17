#include "GameMode.h"
#include "Globals.h"
#include "Item.h"
#include "ModeMgr.h"
#include "MsgStrings.h"
#include "Picker.h"
#include "Struct.h"


CItem::CItem(void) // line 13
{
	this->CItem::OnInit(); //inlined
}


CItem::~CItem(void) // line 18
{
	this->CItem::OnExit(); //inlined
}


hook_method<void (CItem::*)(void)> CItem::_OnInit(SAKEXE, "CItem::OnInit");
void CItem::OnInit(void) // line 23
{
	return (this->*_OnInit)();
	
	m_zoom = 1.0f;
	m_shouldAddPickInfo = 1;
	m_shadowOn = 1;
	m_colorOfSingleColor = 0xFFFFFF00;
}


hook_method<void (CItem::*)(void)> CItem::_OnExit(SAKEXE, "CItem::OnExit");
void CItem::OnExit(void) // line 31
{
	return (this->*_OnExit)();

	;
}


hook_method<bool (CItem::*)(void)> CItem::_OnProcess(SAKEXE, "CItem::OnProcess");
bool CItem::OnProcess(void) // line 43
{
	return (this->*_OnProcess)();
	
	float stateCnt = (timeGetTime() - m_stateStartTick) * (1/24.0f);
	m_isSingleColor = ( int(stateCnt) % 92 >= 90 );
	if( !m_isJumping )
		return true;
	m_pos.y = ((1/12.0f) * stateCnt + m_sfallingSpeed) * stateCnt + m_sPosY;
	CGameMode* gamemode = g_modeMgr.CModeMgr::GetGameMode();
	if( gamemode->CGameMode::GetWorld()->m_attr->C3dAttr::GetHeight(m_pos.x, m_pos.z) >= m_pos.y )
		return true;
	m_pos.y = gamemode->CGameMode::GetWorld()->m_attr->C3dAttr::GetHeight(m_pos.x, m_pos.z);
	m_isJumping = 0;
	return true;
}


hook_method<void (CItem::*)(matrix& vtm)> CItem::_Render(SAKEXE, "CItem::Render");
void CItem::Render(matrix& vtm) // line 35
{
	return (this->*_Render)(vtm);
	
	if( !m_isVisible )
		return;
	this->CRenderObject::RenderShadow(vtm, m_zoom * 0.4f);
	this->CRenderObject::RenderBody(vtm);
}


hook_method<void (CItem::*)(CGameObject* sender, int message, int arg1, int arg2, int arg3)> CItem::_SendMsg(SAKEXE, "CItem::SendMsg");
void CItem::SendMsg(CGameObject* sender, int message, int arg1, int arg2, int arg3) // line 107
{
	return (this->*_SendMsg)(sender, message, arg1, arg2, arg3);
	
	CGameMode* gameMode = g_modeMgr.CModeMgr::GetGameMode();
	switch( message )
	{
	case 4:
	{
		ITEMSTANDENTRYSTRUCT* item = (ITEMSTANDENTRYSTRUCT*)arg1;
		m_aid = item->ITAID;
		m_itemName = item->name;
		gameMode->CGameMode::GetClientCoor(item->x, item->y, item->subX, item->subY, m_pos.x, m_pos.z);
		gameMode->GetWorld()->m_attr->C3dAttr::GetHeight(m_pos.x, m_pos.z);
		if( item->isJumpEntry )
		{
			m_isJumping = 1;
			m_sfallingSpeed = -0.6f;
			m_pos.y -= 15.0f;
		}
		else
		{
			m_isJumping = 0;
		}
		mystd::string sprName = g_session.CSession::GetItemSpriteFileName(m_itemName.c_str(), item->isIdentified);  sprName += ".spr";
		mystd::string actName = g_session.CSession::GetItemSpriteFileName(m_itemName.c_str(), item->isIdentified);  actName += ".act";
		this->CRenderObject::SetSprName(sprName.c_str());
		this->CRenderObject::SetActName(actName.c_str());
		ITEM_INFO dummyItemInfo;
		dummyItemInfo.m_itemName = m_itemName;
		dummyItemInfo.m_isIdentified = ( item->isIdentified != 0 );
		dummyItemInfo.m_refiningLevel = 0;
		char itemHelp[128];
		char itemName[64];
		dummyItemInfo.ITEM_INFO::GetItemName(itemName);
		sprintf(itemHelp, MsgStr(MSI_EA2), itemName, item->count);
		m_itemName = itemHelp;
		this->CRenderObject::GetActRes();
		m_stateStartTick = timeGetTime();
	}
	break;
	default:
		this->CRenderObject::SendMsg(sender, message, arg1, arg2, arg3);
	break;
	}
}


hook_method<void (CItem::*)(RENDER_INFO_RECT& info, const float tlvertX, const float tlvertY)> CItem::_SetRenderInfo(SAKEXE, "CItem::SetRenderInfo");
void CItem::SetRenderInfo(RENDER_INFO_RECT& info, const float tlvertX, const float tlvertY) // line 63
{
	return (this->*_SetRenderInfo)(info, tlvertX, tlvertY);

	if( m_shouldAddPickInfo )
	{
		static int minRectLength;
		static bool minRectLength_initialized = false;
		if( !minRectLength_initialized )
		{
			minRectLength_initialized = true;
			minRectLength = int(g_renderer->CRenderer::GetScreenXFactor() * 34.0f);
		}
		CActorPickInfo* pickInfo = new CActorPickInfo();
		if( info.left <= info.right )
			pickInfo->m_vectors[0].x = info.left;
		else
			pickInfo->m_vectors[0].x = info.right;
		pickInfo->m_vectors[0].y = info.top;
		pickInfo->m_vectors[0].z = info.oow + 300.0f;
		if( info.left <= info.right )//TODO: recheck
			pickInfo->m_vectors[1].x = info.right;
		else
			pickInfo->m_vectors[1].x = info.left;
		pickInfo->m_vectors[1].y = info.bottom;
		pickInfo->m_vectors[1].z = info.oow + 300.0f;
		pickInfo->m_job = JT_LAST;
		pickInfo->m_gid = m_aid;
		pickInfo->m_isPkState = 0;
		pickInfo->m_classType = 1;
		if( int(pickInfo->m_vectors[1].x - pickInfo->m_vectors[0].x) < minRectLength )
		{
			pickInfo->m_vectors[1].x = pickInfo->m_vectors[1].x + ((minRectLength - int(pickInfo->m_vectors[1].x - pickInfo->m_vectors[0].x)) / 2);
			pickInfo->m_vectors[0].x = pickInfo->m_vectors[0].x - ((minRectLength - int(pickInfo->m_vectors[1].x - pickInfo->m_vectors[0].x)) / 2);
		}
		if( int(pickInfo->m_vectors[1].y - pickInfo->m_vectors[0].y) < minRectLength )
		{
			pickInfo->m_vectors[1].y = pickInfo->m_vectors[1].y + ((minRectLength - int(pickInfo->m_vectors[1].y - pickInfo->m_vectors[0].y)) / 2);
			pickInfo->m_vectors[0].y = pickInfo->m_vectors[0].y - ((minRectLength - int(pickInfo->m_vectors[1].y - pickInfo->m_vectors[0].y)) / 2);
		}
		g_actorPickNode.CActorPickNode::AddPickInfo(pickInfo);
	}
	this->SetTlvert(tlvertX, tlvertY);
}


//hook_method<unsigned long (CItem::*)(void)> CItem::_GetAID(SAKEXE, "CItem::GetAID");
unsigned long CItem::GetAID(void) // line ??
{
//	return (this->*_GetAID)();

	return m_aid;
}
