#include "BattleFieldMapRes.h"
#include "CharacterMgr.h"
#include "Msg.h"
#include "NPC.h"
#include "PC.h"
#include "ZoneProcess.h"
#include "Common/Packet.h"
#include "NpcServer/NpcSvr.h"


CBattleFieldMapRes::CBattleFieldMapRes(const int in_mapType)
: CMapRes(in_mapType)
{
	memset(&m_mapInfo, 0, sizeof(m_mapInfo));
	memset(&m_stateInfo, 0, sizeof(m_stateInfo));
	m_campNpc = NULL;
	m_aliveCheck = false;
	m_checkNpcNoti = false;
	m_campCommand = false;
}


void CBattleFieldMapRes::ClearState()
{
	memset(&m_stateInfo, 0, sizeof(m_stateInfo));
	m_a_aliveMemberList.clear();
	m_b_aliveMemberList.clear();
	m_aliveCheck = false;
	m_checkNpcNoti = false;
}


void CBattleFieldMapRes::UpdateCampPoint(char campID, int value)
{
	if( campID == 65 )
	{
		m_stateInfo.a_point += value;
	}
	else
	if( campID == 66 )
	{
		m_stateInfo.b_point += value;
	}
	else
	{
		return;
	}

	this->CBattleFieldMapRes::NotifyCampPoint();
}


void CBattleFieldMapRes::GetPacketBattleFieldPoint(int& len, char* buf, const int in_nMaxBufSize)
{
	len = 0;

	if( !m_mapInfo.isPointNotify )
		return;

	len = sizeof(PACKET_ZC_BATTLEFIELD_NOTIFY_POINT);

	PACKET_ZC_BATTLEFIELD_NOTIFY_POINT packet;
	packet.PacketType = HEADER_ZC_BATTLEFIELD_NOTIFY_POINT;
	packet.pointCampA = static_cast<short>(m_stateInfo.a_point);
	packet.pointCampB = static_cast<short>(m_stateInfo.b_point);
	memcpy_s(buf, in_nMaxBufSize, &packet, sizeof(packet));
}


int CBattleFieldMapRes::GetCampPoint(char campID)
{
	if( campID == 65 )
	{
		return m_stateInfo.a_point;
	}
	else
	if( campID == 66 )
	{
		return m_stateInfo.b_point;
	}
	else
	{
		return 0;
	}
}


void CBattleFieldMapRes::UpdateRespawnPoint2ByNPC(char killerCampID)
{
	if( killerCampID == 65 )
	{
		this->CBattleFieldMapRes::UpdateRespawnPoint2(65, m_mapInfo.aX2, m_mapInfo.aY2);
		this->CBattleFieldMapRes::UpdateRespawnPoint2(66, 0, 0);
	}
	else
	if( killerCampID == 66 )
	{
		this->CBattleFieldMapRes::UpdateRespawnPoint2(65, 0, 0);
		this->CBattleFieldMapRes::UpdateRespawnPoint2(66, m_mapInfo.bX2, m_mapInfo.bY2);
	}
	else
	{
		return;
	}
}


void CBattleFieldMapRes::UpdateRespawnPoint2(char campID, short xPos, short yPos)
{
	if( campID == 0 )
		return;

	std::vector<CCharacter*>** sectionListPointer = this->CMapRes::GetSectionList();
	int n = this->CMapRes::GetSectionSize();

	for( int i = 0; i < n; ++i )
	{
		std::vector<CCharacter*>* sectionList = sectionListPointer[i];
		if( sectionList == NULL )
			continue;

		for( std::vector<CCharacter*>::const_iterator iter = sectionList->begin(); iter != sectionList->end(); ++iter )
		{
			CCharacter* ch = *iter;
			if( ch == NULL || ch->GetType() != PC_TYPE )
				continue;

			if( campID == ch->GetCampID() )
				static_cast<CPC*>(ch)->CPC::UpdateBattleFieldRespawnPoint2(xPos, yPos);
		}
	}
}


void CBattleFieldMapRes::BroadcastToCamp(char campID, int len, char* buf)
{
	if( campID == 0 )
		return;

	std::vector<CCharacter*>** sectionListPointer = this->CMapRes::GetSectionList();
	int n = this->CMapRes::GetSectionSize();

	for( int i = 0; i < n; ++i )
	{
		std::vector<CCharacter*>* sectionList = sectionListPointer[i];
		if( sectionList == NULL )
			continue;

		for( std::vector<CCharacter*>::const_iterator iter = sectionList->begin(); iter != sectionList->end(); ++iter )
		{
			CCharacter* ch = *iter;
			if( ch == NULL || ch->GetType() != PC_TYPE )
				continue;

			if( campID == ch->GetCampID() )
				CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, ch, CM_SEND_PACKET, len, (int)buf, 0, 0);
		}
	}
}


void CBattleFieldMapRes::MovePlayerToRespawnPoint(char campID, short RP_No, unsigned long npcID)
{
	std::vector<CPC*> pcList;

	std::vector<CCharacter*>** sectionListPointer = this->CMapRes::GetSectionList();
	int n = this->CMapRes::GetSectionSize();

	for( int i = 0; i < n; ++i )
	{
		std::vector<CCharacter*>* sectionList = sectionListPointer[i];
		if( sectionList == NULL )
			continue;

		for( std::vector<CCharacter*>::const_iterator iter = sectionList->begin(); iter != sectionList->end(); ++iter )
		{
			CCharacter* ch = *iter;
			if( ch == NULL || ch->GetType() != PC_TYPE )
				continue;

			if( (campID == 0 && ch->GetCampID() != 0) || campID == ch->GetCampID() )
				pcList.push_back(static_cast<CPC*>(ch));
		}
	}

	for( std::vector<CPC*>::iterator iter = pcList.begin(); iter != pcList.end(); ++iter )
		(*iter)->CPC::MoveToBattleFieldRespawnPoint(RP_No, npcID);
}


void CBattleFieldMapRes::SetBattleFieldMapInfo(char* key, char* value)
{
	if( strcmp(key, "A_X2") == 0 )
	{
		m_mapInfo.aX2 = atoi(value);
	}
	else
	if( strcmp(key, "A_Y2") == 0 )
	{
		m_mapInfo.aY2 = atoi(value);
	}
	else
	if( strcmp(key, "B_X2") == 0 )
	{
		m_mapInfo.bX2 = atoi(value);
	}
	else
	if( strcmp(key, "B_Y2") == 0 )
	{
		m_mapInfo.bY2 = atoi(value);
	}
	else
	if( strcmp(key, "POINT_NOTIFY") == 0 )
	{
		if( strcmp(value, "ON") == 0 )
			m_mapInfo.isPointNotify = true;
	}
	else
	if( strcmp(key, "PK_POINT") == 0 )
	{
		if( strcmp(value, "ON") == 0 )
			m_mapInfo.isPKPoint = true;
	}
	else
	if( strcmp(key, "ALIVE_PC") == 0 )
	{
		if( strcmp(value, "ON") == 0 )
			m_mapInfo.isAlivePCCheck = true;
	}
	else
	if( strcmp(key, "NPC_NOTIFY") == 0 )
	{
		if( strcmp(value, "ON") == 0 )
			m_mapInfo.isNpcNotify = true;
	}
}


BOOL CBattleFieldMapRes::AddCharacter(int xCellPos, int yCellPos, CCharacter* character)
{
	if( this->CMapRes::AddCharacter(xCellPos, yCellPos, character) != TRUE )
		return FALSE;

	if( character != NULL && character->GetType() == PC_TYPE && !m_aliveCheck )
		this->CBattleFieldMapRes::InsertAliveMember(character->GetCampID(), character->GetAccountID());

	return TRUE;
}


void CBattleFieldMapRes::InsertAliveMember(char campID, unsigned long accountID)
{
	if( !m_mapInfo.isAlivePCCheck )
		return;

	std::list<unsigned long>* aliveMemberList;
	if( campID == 65 )
	{
		aliveMemberList = &m_a_aliveMemberList;
	}
	else
	if( campID == 66 )
	{
		aliveMemberList = &m_b_aliveMemberList;
	}
	else
	{
		return;
	}

	for( std::list<unsigned long>::const_iterator iter = aliveMemberList->begin(); iter != aliveMemberList->end(); ++iter )
		if( *iter == accountID )
			return; // already present.

	aliveMemberList->push_back(accountID);
	m_stateInfo.a_point = m_a_aliveMemberList.size();
	m_stateInfo.b_point = m_b_aliveMemberList.size();
	this->CBattleFieldMapRes::NotifyCampPoint();
}


void CBattleFieldMapRes::DeleteAliveMember(char campID, unsigned long accountID)
{
	if( !m_mapInfo.isAlivePCCheck )
		return;

	std::list<unsigned long>* aliveMemberList;
	if( campID == 65 )
	{
		aliveMemberList = &m_a_aliveMemberList;
	}
	else
	if( campID == 66 )
	{
		aliveMemberList = &m_b_aliveMemberList;
	}
	else
	{
		return;
	}

	for( std::list<unsigned long>::iterator iter = aliveMemberList->begin(); iter != aliveMemberList->end(); ++iter )
	{
		if( *iter == accountID )
		{
			aliveMemberList->erase(iter);
			m_stateInfo.a_point = m_a_aliveMemberList.size();
			m_stateInfo.b_point = m_b_aliveMemberList.size();
			this->CBattleFieldMapRes::NotifyCampPoint();
			this->CBattleFieldMapRes::SendNpcServer();
			return; // found.
		}
	}
}


void CBattleFieldMapRes::NotifyCampPoint()
{
	char packet[256] = {};
	int len;

	this->CBattleFieldMapRes::GetPacketBattleFieldPoint(len, packet, sizeof(packet));
	if( len == 0 )
		return;

	this->CMapRes::Send(len, packet, 0, 0);
}


void CBattleFieldMapRes::RegisterNpc(CNPC* npc)
{
	if( npc == NULL )
		return;

	m_campNpc = npc;
}


void CBattleFieldMapRes::SendNpcServer()
{
	if( !m_mapInfo.isNpcNotify || !m_checkNpcNoti || m_campNpc == NULL )
		return;

	CZNPC2Msg msg;
	msg.CMsg::SetMsgID(ZNPC2MSG_CALLEVENT);
	msg.par1 = NPCEVENT_ONCAMPCOMMAND;
	g_npcSvr.CNpcSvr::SendMsg(0, m_campNpc->GetAccountID(), &msg);
}


int CBattleFieldMapRes::GetAliveMemberCount(char campCode)
{
	if( campCode == 65 )
	{
		return m_a_aliveMemberList.size();
	}
	else
	if( campCode == 66 )
	{
		return m_b_aliveMemberList.size();
	}
	else
	{
		return 0;
	}
}


void CBattleFieldMapRes::StartAliveCheck()
{
	m_aliveCheck = true;
}


bool CBattleFieldMapRes::IsAliveCheck()
{
	return m_aliveCheck;
}


void CBattleFieldMapRes::SetNpcNotify_Switch(const char* sw)
{
	m_checkNpcNoti = ( strcmp(sw, "on") == 0 );
}


bool CBattleFieldMapRes::SetBattleFieldMovePostion(const char campID, const int xPos, const int yPos)
{
	if( campID == 65 )
	{
		m_mapInfo.aX2 = xPos;
		m_mapInfo.aY2 = yPos;
		return true;
	}
	else
	if( campID == 66 )
	{
		m_mapInfo.bX2 = xPos;
		m_mapInfo.bY2 = yPos;
		return true;
	}
	else
	{
		return false;
	}
}


bool CBattleFieldMapRes::IsBattleField()
{
	return true;
}


bool CBattleFieldMapRes::IsPKPoint()
{
	return m_mapInfo.isPKPoint;
}


bool CBattleFieldMapRes::IsAlivePCCheck()
{
	return m_mapInfo.isAlivePCCheck;
}
