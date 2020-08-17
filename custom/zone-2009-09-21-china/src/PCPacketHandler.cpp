#include "CAgitMapRes.hpp"
#include "BattleFieldMapRes.h"
#include "CharacterMgr.h"
#include "CCharInfoDB.hpp"
#include "ErrorLog.h"
#include "CharacterMgr.h"
#include "CExpParameter.hpp"
#include "Guild.h"
#include "ItemLog.h"
#include "CMsg.hpp"
#include "CNpcMob.hpp"
#include "PathFinder.h"
#include "PC.h"
#include "PCPacketHandler.h"
#include "CSkillTypeInfoMgr.hpp"
#include "Room.h"
#include "RoomMgr.h"
#include "ZGuildMgr.h"
#include "ZoneScript.h"
#include "ZLib.h"
#include "zoneprocess.h"
#include "Common/Packet.h"
#include "enum.hpp"
#include "globals.hpp"
#include "struct.hpp"
#include "shared.h" // Trace
#include "Custom/AtCommand.h"
#include "Custom/GlobalChat.h"
#include "Custom/Settings.h"
#include "Custom/umage.hpp" // ITID_AUTOTRADE, AREA_SIZE
#include <math.h>


CPCPacketHandler::CPCPacketHandler(void) // line 91
{
}// line 102


CPCPacketHandler::~CPCPacketHandler(void) // line 105
{
}


hook_method<void (CPCPacketHandler::*)(int OnRecvOverflow)> CPCPacketHandler::_OnRecvOverflow(SERVER, "CPCPacketHandler::OnRecvOverflow");
void CPCPacketHandler::OnRecvOverflow(int byteTransferred) // line ???
{
	return (this->*_OnRecvOverflow)(byteTransferred);

	;
}


hook_method<void (CPCPacketHandler::*)(int OnRecvOverflow)> CPCPacketHandler::_OnRecv(SERVER, "CPCPacketHandler::OnRecv");
void CPCPacketHandler::OnRecv(int byteTransferred) // line ???
{
	return (this->*_OnRecv)(byteTransferred);

	;
}


hook_method<int  (CPCPacketHandler::*)(void)> CPCPacketHandler::_OnProcess(SERVER, "CPCPacketHandler::OnProcess");
int CPCPacketHandler::OnProcess(void) // line 454
{
	return (this->*_OnProcess)();

	int Header = 0;
	int size;

	if( m_recvQueue->CPacketQueue::GetSize() < 2 )
		return -1;

	m_recvQueue->CPacketQueue::PeekData(2, (char *)&Header);
	if( this->CPCPacketHandler::IsFixedPacket(Header) )
	{
		size = (unsigned short) this->CPCPacketHandler::GetPacketSize(Header);
	}
	else
	{
		if( m_recvQueue->CPacketQueue::GetSize() < 4 )
			return -1;

		m_recvQueue->CPacketQueue::PeekData(4, (char *)&size);
		size = size >> 16;
	}

	if( size >= 3000 )
	{
		char Buf[256];
		Trace("AE:CPCPacketHandler packetSize overflow\n");
		memset(Buf, 0, sizeof(Buf));
		sprintf(Buf, "Packet Size %d OnProcess  \n", size);
		g_errorLogs->CErrorLog::CriticalErrorLog(Buf, 530, ".\\PCPacketHandler.cpp");
		m_pc->AddErrorCount(".\\PCPacketHandler.cpp", 531, 4, timeGetTime());
		return 0;
	}

	m_pc->m_characterInfo.recvBytes += size;
	if( m_recvQueue->CPacketQueue::GetSize() < size )
		return -1;

	return this->CPCPacketHandler::DispatchPacket(Header, size);
}


hook_method<void (CPCPacketHandler::*)(void)> CPCPacketHandler::_OnClose(SERVER, "CPCPacketHandler::OnClose");
HOOKED void CPCPacketHandler::OnClose(void) // line 170
{
	if( m_pc->m_pcitemInventoryMgr.IsMCStoreOpen() )
	{// check autotrade
		if( m_pc->CPC::GetItem(ITID_AUTOTRADE) != 0 )
		{// autotrade activation
			// remove autotrade item
			m_pc->CPC::SetItem(ITID_AUTOTRADE, 0);
			// deal with pet/homun/mercenary
			m_pc->ConvertPetToPetEgg();
			m_pc->m_pcBattle.CPCBattle::RestHomun(true);
			m_pc->m_pcBattle.CPCBattle::Mercenary_Release(true);
			// drop buffers
			m_pc->m_asyncStream->Init(this);
			// detach
			return;
		}
	}

	return (this->*_OnClose)();

	if( m_pc->CPC::IsDisconnectable() || m_pc->m_pcClientUpdater.m_disconnectType == MOVE_SERVER )
		m_pc->AddErrorCount(".\\PCPacketHandler.cpp", 174, 65535, timeGetTime() - 4000);
	else
		m_pc->AddErrorCount(".\\PCPacketHandler.cpp", 176, 65535, timeGetTime());
}


hook_method<void (CPCPacketHandler::*)(CPC* pc)> CPCPacketHandler::_SetMyOwner(SERVER, "CPCPacketHandler::SetMyOwner");
void CPCPacketHandler::SetMyOwner(CPC* pc) // line ???
{
	return (this->*_SetMyOwner)(pc);

	m_pc = pc;
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_AddSendBytes(SERVER, "CPCPacketHandler::AddSendBytes");
void CPCPacketHandler::AddSendBytes(int len) // line 165
{
	return (this->*_AddSendBytes)(len);

	m_pc->m_characterInfo.sendBytes += len;
}


hook_method<void (CPCPacketHandler::*)(void)> CPCPacketHandler::_Init(SERVER, "CPCPacketHandler::Init");
void CPCPacketHandler::Init(void) // line 114
{
	return (this->*_Init)();

	m_pc = NULL;
	m_RequestNpcTime = 0;
	m_csAuth.CCSAuth::Init();
	m_bLockCashPoint = 0;
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnBroadCast(SERVER, "CPCPacketHandler::OnBroadCast");
void CPCPacketHandler::OnBroadCast(int len) // line 3769
{
	return (this->*_OnBroadCast)(len);

	if( len > 200 )
	{
		m_pc->AddErrorCount(".\\PCPacketHandler.cpp", 3771, 4, timeGetTime());
		return;
	}

	char buf[256];
	m_recvQueue->CPacketQueue::GetData(len, buf);

	if( m_pc->m_isValid == 0 )
	{
		m_pc->AddErrorCount(".\\PCPacketHandler.cpp", 3779, 4, timeGetTime());
		return;
	}

	if( g_zoneScript->CZoneScript::SearchID(m_pc->m_characterInfo.accountName, CHECK_BROADCAST) == 0 )
		return;

	PACKET_ZI_BROADCAST& packet = *(PACKET_ZI_BROADCAST*)buf;
	packet.PacketType = HEADER_ZI_BROADCAST; // re-brand packet
	g_characterMgr->CCharacterMgr::SendToIServer(len, buf);
}


hook_method<void (CPCPacketHandler::*)(int packetlen)> CPCPacketHandler::_OnMove(SERVER, "?OnMove@CPCPacketHandler@@AAEXH@Z");
void CPCPacketHandler::OnMove(int packetlen) // line 3317
{
	return (this->*_OnMove)(packetlen);

	PACKET_CZ_REQUEST_MOVE move_req;
	m_recvQueue->CPacketQueue::GetData(sizeof(move_req), (char*)&move_req);

	if( m_pc->m_isValid == 0 )
	{
		Trace("AE:OnMove m_pcInvalid\n");
		g_errorLogs->CErrorLog::CriticalErrorLog("On Move Error\n", 3336, ".\\PCPacketHandler.cpp");
		m_pc->AddErrorCount(".\\PCPacketHandler.cpp", 3337, 4, timeGetTime());
		return;
	}

	if( timeGetTime() - m_pc->m_pathInfo.m_moveInfo.LastTime < 350 )
		return;

	if( m_pc->CPC::IsMovable() == 0 )
		return;

	if( m_pc->GetEffective(EFST_RUN, 0) )
		return;

	if( m_pc->m_open_simpleCashShop )
		return;

	m_pc->m_isTraderOpen = 0;
	if( m_pc->m_eventNo != 0 )
		this->CPCPacketHandler::ForcedCloseDialog(m_pc->m_lastNPCAID);
	m_pc->CPC::CancelLockOnMode();

	if( this->CPCPacketHandler::StartPath(&move_req, timeGetTime()) == 0 )
		return;

	m_pc->m_characterInfo.headDir = 0;

	int sx, xsubcell;
	int sy, ysubcell;
	TransformFloatPosCellPos(m_pc->m_pathInfo.CPathInfo::GetStartPointX(), sx, xsubcell);
	TransformFloatPosCellPos(m_pc->m_pathInfo.CPathInfo::GetStartPointY(), sy, ysubcell);

	PACKET_ZC_NOTIFY_PLAYERMOVE MyMove;
	MyMove.PacketType = HEADER_ZC_NOTIFY_PLAYERMOVE;
	MyMove.moveStartTime = m_pc->m_pathInfo.m_moveInfo.LastTime;
	EncodeSrcDst(sx, sy, m_pc->m_pathInfo.m_moveInfo.dxPos, m_pc->m_pathInfo.m_moveInfo.dyPos, xsubcell, ysubcell, MyMove.MoveData);

	m_pc->CPC::Send(sizeof(MyMove), (char*)&MyMove);
	this->CPCPacketHandler::BroadcastNewPosition(m_pc->m_pathInfo.m_moveInfo.dxPos, m_pc->m_pathInfo.m_moveInfo.dyPos);
}


hook_method<void (CPCPacketHandler::*)(PACKET_CZ_REQUEST_MOVE* move_req)> CPCPacketHandler::_OnMove2(SERVER, "?OnMove@CPCPacketHandler@@QAEXPAUPACKET_CZ_REQUEST_MOVE@@@Z");
void CPCPacketHandler::OnMove(PACKET_CZ_REQUEST_MOVE* move_req) // line 3397
{
	return (this->*_OnMove2)(move_req);

	if( m_pc->m_isValid == 0 )
	{
		Trace("AE:OnMove pc invalid2");
		g_errorLogs->CErrorLog::CriticalErrorLog("OnMove Error\n", 3400, ".\\PCPacketHandler.cpp");
		m_pc->AddErrorCount(".\\PCPacketHandler.cpp", 3401, 4, timeGetTime());
		return;
	}

	if( m_pc->CPC::IsMovable() == 0 )
		return;

	m_pc->m_open_simpleCashShop = 0;
	m_pc->m_isTraderOpen = 0;

	if( this->CPCPacketHandler::StartPath(move_req, timeGetTime()) == 0 )
		return;

	int sx, xsubcell;
	int sy, ysubcell;
	TransformFloatPosCellPos(m_pc->m_pathInfo.CPathInfo::GetStartPointX(), sx, xsubcell);
	TransformFloatPosCellPos(m_pc->m_pathInfo.CPathInfo::GetStartPointY(), sy, ysubcell);

	PACKET_ZC_NOTIFY_PLAYERMOVE MyMove;
	MyMove.PacketType = HEADER_ZC_NOTIFY_PLAYERMOVE;
	MyMove.moveStartTime = m_pc->m_pathInfo.m_moveInfo.LastTime;
	EncodeSrcDst(sx, sy, m_pc->m_pathInfo.m_moveInfo.dxPos, m_pc->m_pathInfo.m_moveInfo.dyPos, xsubcell, ysubcell, MyMove.MoveData);

	m_pc->CPC::Send(sizeof(MyMove), (char*)&MyMove);
}


hook_method<BOOL (CPCPacketHandler::*)(PACKET_CZ_REQUEST_MOVE* p_MoveReq, DWORD startTime)> CPCPacketHandler::_StartPath(SERVER, "CPCPacketHandler::StartPath");
BOOL CPCPacketHandler::StartPath(PACKET_CZ_REQUEST_MOVE* p_MoveReq, DWORD startTime) // line 1001
{
	return (this->*_StartPath)(p_MoveReq, startTime);

	int dx, dy, dir;
	DecodePosDir(p_MoveReq->dest, dx, dy, dir);

	CMapRes* mapRes = m_pc->CCharacter::GetMapRes();
	if( mapRes == NULL || !mapRes->CMapRes::IsMovableCell(dx, dy) )
		return FALSE;

	float curX, curY;
	if( m_pc->m_pathInfo.m_moveInfo.state != CHARACTER_STATE_MOVE )
	{
		curX = (float)m_pc->m_pathInfo.m_moveInfo.xPos;
		curY = (float)m_pc->m_pathInfo.m_moveInfo.yPos;
	}
	else
	{
		m_pc->m_pathInfo.CPathInfo::GetPos(m_pc->CPC::GetSpeed(), startTime, curX, curY, dir);
	}

	int sx, sy, xM, yM;
	TransformFloatPosCellPos(curX, sx, xM);
	TransformFloatPosCellPos(curY, sy, yM);

	if( dx == curX && dy == curY )
	{
		PACKET_ZC_NOTIFY_PLAYERMOVE MyMove;
		MyMove.PacketType = HEADER_ZC_NOTIFY_PLAYERMOVE;
		MyMove.moveStartTime = timeGetTime();
		EncodeSrcDst(sx, sy, dx, dy, xM, yM, MyMove.MoveData);
		m_pc->CPC::Send(sizeof(MyMove), (char*)&MyMove);

		return FALSE;
	}

	int xPos = dx;
	int yPos = dy;
	if( m_pc->GetHealthState() & HEALTHSTATE_CONFUSION )
	{
		xPos = sx;
		yPos = sy;
		mapRes->CMapRes::GetRandomPosByRange(xPos, yPos, 7, 7, 0);
	}

	if( !mapRes->CMapRes::FindPath(startTime, sx, sy, xM, yM, xPos, yPos, m_pc->CPC::GetSpeed(), &m_pc->m_pathInfo) )
		return FALSE;

	m_pc->m_pathInfo.m_moveInfo.state = CHARACTER_STATE_MOVE;
	m_pc->m_pathInfo.m_moveInfo.LastTime = startTime;
	m_pc->m_pathInfo.m_moveInfo.dxPos = xPos;
	m_pc->m_pathInfo.m_moveInfo.dyPos = yPos;
	return TRUE;
}


hook_method<void (CPCPacketHandler::*)(void)> CPCPacketHandler::_LockOnAttack(SERVER, "CPCPacketHandler::LockOnAttack");
void CPCPacketHandler::LockOnAttack(void) // line 8552-8562
{
	return (this->*_LockOnAttack)();

	// TODO
}


void CPCPacketHandler::CounterAttack(unsigned long targetID)
{
	PACKET_CZ_REQUEST_ACT packet;
	packet.PacketType = HEADER_CZ_REQUEST_ACT;
	packet.action = ACTION_ATTACK;
	packet.targetGID = targetID;
	this->CPCPacketHandler::OnReqAct1(sizeof(packet), (char*)&packet);
}


hook_method<int  (CPCPacketHandler::*)(short Header, int packetSize)> CPCPacketHandler::_DispatchPacket(SERVER, "CPCPacketHandler::DispatchPacket");
HOOKED int CPCPacketHandler::DispatchPacket(short Header, int packetSize) // line 1577-3055
{
	if( m_pc->m_isMapLoading
		&&(Header != HEADER_CZ_NOTIFY_ACTORINIT
		&& Header != HEADER_CZ_LESSEFFECT
		&& Header != HEADER_CZ_REQ_REMAINTIME
		&& Header != HEADER_CZ_SRPACKETR2_START
		&& Header != HEADER_CZ_SRCRYPTOR2_START
		&& Header != HEADER_CZ_SRPACKET_START
		|| Header == HEADER_CZ_REQUEST_TIME)
		&& Header != HEADER_CZ_REQUEST_MOVETOOWNER )
	{
		char buf[3000];
		m_recvQueue->CPacketQueue::GetData(packetSize, buf);
		m_recvQueue->CPacketQueue::InsertData(packetSize, buf);
		return -1;
	}

	return (this->*_DispatchPacket)(Header, packetSize);

	if( m_pc->m_isMapLoading
		&&(Header != HEADER_CZ_NOTIFY_ACTORINIT
		&& Header != HEADER_CZ_LESSEFFECT
		&& Header != HEADER_CZ_REQ_REMAINTIME
		&& Header != HEADER_CZ_SRPACKETR2_START
		&& Header != HEADER_CZ_SRCRYPTOR2_START
		&& Header != HEADER_CZ_SRPACKET_START
		|| Header == HEADER_CZ_REQUEST_TIME)
		&& Header != HEADER_CZ_REQUEST_MOVETOOWNER )
	{
		++m_pc->m_invalidPacket;
		if( m_pc->m_invalidPacket > 10 )
			m_pc->AddErrorCount(".\\PCPacketHandler.cpp", 1605, 4, timeGetTime());
	}

	if( !m_pc->m_isValid
		&& Header != HEADER_CZ_ENTER
		&& Header != HEADER_CZ_ENTER2
		&& Header != HEADER_CZ_REQUEST_TIME
		&& Header != HEADER_CZ_REQUEST_MOVE
		&& Header != HEADER_CZ_REQNAME
		&& Header != HEADER_CZ_REQ_GUILD_EMBLEM_IMG
		&& Header != HEADER_CZ_REQUEST_CHAT
		&& Header != HEADER_CZ_NOTIFY_ACTORINIT
		&& Header != HEADER_CZ_RESTART
		&& Header != HEADER_CS_REQ_ENCRYPTION
		&& Header != HEADER_CZ_SRPACKETR2_START
		&& Header != HEADER_CZ_SRCRYPTOR2_START
		&& Header != HEADER_CZ_SRPACKET_START
		&& Header != HEADER_CZ_REQUEST_MOVE_NEW_JAPEN )
		return 0;

	if( m_pc->m_isValid
		&& (Header == HEADER_CZ_ENTER || Header == HEADER_CZ_ENTER2) )
	{
		Trace("AE:DispatchPacket Failure2\n");
		g_errorLogs->CErrorLog::CriticalErrorLog("Dispatch Packet Fail Second\n", 1633, ".\\PCPacketHandler.cpp");
		m_pc->AddErrorCount(".\\PCPacketHandler.cpp", 1634, 4, timeGetTime());
		return 0;
	}

	if( (m_pc->m_pcClientUpdater.m_disconnectType == MOVE_SERVER || m_pc->m_pcClientUpdater.m_disconnectType == RESTART_HSERVER)
		&& Header != HEADER_CZ_REQUEST_TIME
		&& Header != HEADER_CZ_REQUEST_MOVE
		&& Header != HEADER_CZ_REQNAME
		&& Header != HEADER_CZ_REQ_GUILD_EMBLEM_IMG
		&& Header != HEADER_CZ_CHANGE_DIRECTION
		&& Header != HEADER_CZ_REQUEST_MOVE_NEW_JAPEN )
	{
		if( Header != HEADER_CZ_MOVETO_MAP )
		{
			if( m_pc->GetEffective(EFST_NOACTION_WAIT, 0) )
				return -1;

			Trace("DispatchPacket Failure : Not allow client packet!\n");
			Trace("Header : %d\n", Header);
			Trace("m_pc->m_pcClientUpdater.m_disconnectType : %d\n", m_pc->m_pcClientUpdater.m_disconnectType);
			return 0;
		}

		char LogBuffer[80];
		sprintf(LogBuffer, "Dispatch Packet Fail : Name :%s, disconnectType  %d", m_pc->m_characterInfo.characterName, m_pc->m_pcClientUpdater.m_disconnectType);
		g_errorLogs->CErrorLog::CriticalErrorLog(LogBuffer, 1650, ".\\PCPacketHandler.cpp");
	}

	m_pc->m_characterTimeInfo.lastPacketArrivedTime = timeGetTime();

	if( m_pc->CPC::GetErrorCount() >= 4 )
		return 0;

	switch( Header )
	{
	case HEADER_CONNECTION_CLOSED:
	{
		PACKET_CONNECTION_CLOSED msg;
		m_recvQueue->CPacketQueue::GetData(sizeof(msg), (char *)&msg);
	}
	break;
	case HEADER_CZ_ITEMLISTWIN_RES:
	{
		mystd::vector<char> reqpacket(packetSize, 0);
		m_recvQueue->CPacketQueue::GetData(packetSize, &reqpacket.front());
	}
	break;
	case HEADER_ZC_BLOCKING_PLAY_CANCEL:
	{
		PACKET_ZC_BLOCKING_PLAY_CANCEL zc_blocking_play_cancel;
		m_recvQueue->CPacketQueue::GetData(sizeof(zc_blocking_play_cancel), (char *)&zc_blocking_play_cancel);
	}
	break;
	case HEADER_CZ_SIMPLE_BUY_CASH_POINT_ITEM:
	{
		this->CPCPacketHandler::OnPCBuyCashPointItemSimpleShop(packetSize);
	}
	break;
	case HEADER_CZ_CLIENT_VERSION:
	{
		this->CPCPacketHandler::OnCZClientVersion(packetSize);
	}
	break;
	case HEADER_CZ_CLOSE_SIMPLECASH_SHOP:
	{
		this->CPCPacketHandler::OnCZCloseSimpleCashShop(packetSize);
	}
	break;
	case HEADER_CZ_USE_ITEM2:
	{
		PACKET_CZ_USE_ITEM2 msg;
		m_recvQueue->CPacketQueue::GetData(sizeof(msg), (char *)&msg);
		this->CPCPacketHandler::OnUseItem2(msg.index, msg.AID);
	}
	break;
	case HEADER_CZ_SKILL_SELECT_RESPONSE:
	{
		PACKET_CZ_SKILL_SELECT_RESPONSE msg;
		m_recvQueue->CPacketQueue::GetData(sizeof(msg), (char *)&msg);
	}
	break;
	case HEADER_CZ_REQUEST_ACT2:
	{
		PACKET_CZ_REQUEST_ACT2 msg;
		m_recvQueue->CPacketQueue::GetData(sizeof(msg), (char *)&msg);
		this->CPCPacketHandler::OnReqAct2(msg.targetGID, msg.action, true);
	}
	break;
	case HEADER_CZ_USE_SKILL2:
	{
		PACKET_CZ_USE_SKILL2 msg;
		m_recvQueue->CPacketQueue::GetData(sizeof(msg), (char *)&msg);
		switch( g_skillTypeInfoMgr->CSkillTypeInfoMgr::GetSKClass(msg.SKID) )
		{
		case 0: this->CPCPacketHandler::OnUseSkill(msg.SKID, msg.selectedLevel, msg.targetID); break;
		case 1: this->CPCPacketHandler::OnUseSkill_Merce(msg.SKID, msg.selectedLevel, msg.targetID); break;
		case 2: this->CPCPacketHandler::OnUseGuildSkill(msg.SKID, msg.selectedLevel, msg.targetID); break;
		case 3: this->CPCPacketHandler::OnMercenary_UseSkill(msg.SKID, msg.selectedLevel, msg.targetID); break;
		default: break;
		}
		m_pc->m_pcSkill.CPCSkill::SetSKIDFromAbracadabra(0);
	}
	break;
	case HEADER_CZ_ENTER2:
	{
		PACKET_CZ_ENTER2 reqpacket;
		m_recvQueue->CPacketQueue::GetData(sizeof(reqpacket), (char *)&reqpacket);
		this->CPCPacketHandler::OnEnter(reqpacket.AID, reqpacket.GID, reqpacket.AuthCode, reqpacket.clientTime, reqpacket.Sex);
	}
	break;
	case HEADER_CZ_CONFIG:
	{
		PACKET_CZ_CONFIG msg;
		m_recvQueue->CPacketQueue::GetData(sizeof(msg), (char *)&msg);
		this->CPCPacketHandler::OnCZ_CONFIG(msg);
	}
	break;
	case HEADER_CZ_EQUIPWIN_MICROSCOPE:
	{
		PACKET_CZ_EQUIPWIN_MICROSCOPE msg;
		m_recvQueue->CPacketQueue::GetData(sizeof(msg), (char *)&msg);
		this->CPCPacketHandler::OnCZ_EQUIPWIN_MICROSCOPE(msg);
	}
	break;
	case HEADER_CZ_MEMORIALDUNGEON_COMMAND:
	{
		PACKET_CZ_MEMORIALDUNGEON_COMMAND msg;
		m_recvQueue->CPacketQueue::GetData(sizeof(msg), (char *)&msg);
		this->CPCPacketHandler::OnCZ_MEMORIALDUNGEON_COMMAND(msg);
	}
	break;
	case HEADER_CZ_PARTY_JOIN_REQ_ACK:
	{
		PACKET_CZ_PARTY_JOIN_REQ_ACK msg;
		m_recvQueue->CPacketQueue::GetData(sizeof(msg), (char *)&msg);
		this->CPCPacketHandler::OnCZ_PARTY_JOIN_REQ_ACK(msg);
	}
	break;
	case HEADER_CZ_PARTY_CONFIG:
	{
		PACKET_CZ_PARTY_CONFIG msg;
		m_recvQueue->CPacketQueue::GetData(sizeof(msg), (char *)&msg);
		this->CPCPacketHandler::OnCZ_PARTY_CONFIG(msg);
	}
	break;
	case HEADER_CZ_PARTY_JOIN_REQ:
	{
		PACKET_CZ_PARTY_JOIN_REQ reqpacket;
		m_recvQueue->CPacketQueue::GetData(sizeof(reqpacket), (char *)&reqpacket);
		this->CPCPacketHandler::OnCZ_PARTY_JOIN_REQ(reqpacket);
	}
	break;
	case HEADER_CZ_MER_COMMAND:
	{
		PACKET_CZ_MER_COMMAND msg;
		m_recvQueue->CPacketQueue::GetData(sizeof(msg), (char *)&msg);
		this->CPCPacketHandler::OnMercenary_Command(&msg);
	}
	break;
	case HEADER_CZ_USE_SKILL_NEW_JAPEN:
	{
		PACKET_CZ_USE_SKILL msg; //FIXME: guessed type
		m_recvQueue->CPacketQueue::GetData(sizeof(msg), (char *)&msg);
		switch( g_skillTypeInfoMgr->CSkillTypeInfoMgr::GetSKClass(msg.SKID) )
		{
		case 0: this->CPCPacketHandler::OnUseSkill(msg.SKID, msg.selectedLevel, msg.targetID); break;
		case 1: this->CPCPacketHandler::OnUseSkill_Merce(msg.SKID, msg.selectedLevel, msg.targetID); break;
		case 2: this->CPCPacketHandler::OnUseGuildSkill(msg.SKID, msg.selectedLevel, msg.targetID); break;
		case 3: this->CPCPacketHandler::OnMercenary_UseSkill(msg.SKID, msg.selectedLevel, msg.targetID); break;
		default: break;
		}
		m_pc->m_pcSkill.CPCSkill::SetSKIDFromAbracadabra(0);
		break;
	}
	case HEADER_CZ_GANGSI_RANK:
	{
		this->CPCPacketHandler::OnReqMakerRanking2(packetSize);
	}
	break;
	case HEADER_CZ_DEATH_QUESTION:
	{
		this->CPCPacketHandler::OnReqDeathQuestion(packetSize);
	}
	break;
	case HEADER_CZ_KSY_EVENT:
	{
		this->CPCPacketHandler::OnReqKSY(packetSize);
	}
	break;
	case HEADER_CZ_HUNTINGLIST:
	{
		this->CPCPacketHandler::OnHuntingList(packetSize);
	}
	break;
	case HEADER_CZ_PC_BUY_CASH_POINT_ITEM:
	{
		this->CPCPacketHandler::OnPCBuyCashPointItem(packetSize);
	}
	break;
	case HEADER_CZ_STANDING_RESURRECTION:
	{
		this->CPCPacketHandler::OnStandingResurrection(packetSize);
	}
	break;
	case HEADER_CZ_ACK_CASH_PASSWORD:
	{
		this->CPCPacketHandler::OnCashPassword(packetSize);
	}
	break;
	case HEADER_CZ_SHORTCUT_KEY_CHANGE:
	{
		this->CPCPacketHandler::OnShortcutKey_Change(packetSize);
	}
	break;
	case HEADER_CZ_ACTIVE_QUEST:
	{
		this->CPCPacketHandler::OnActiveQuest(packetSize);
	}
	break;
	case HEADER_CZ_BATTLEFIELD_CHAT:
	{
		this->CPCPacketHandler::OnBattleFieldChat(packetSize);
	}
	break;
	case HEADER_CZ_PROGRESS:
	{
		this->CPCPacketHandler::OnProgress(packetSize);
	}
	break;
	case HEADER_CZ_REASSEMBLY_IDENTITY:
	case HEADER_CZ_REASSEMBLY_IDENTITY__M01:
	case HEADER_CZ_REASSEMBLY_IDENTITY__M02:
	case HEADER_CZ_REASSEMBLY_IDENTITY__M03:
	case HEADER_CZ_REASSEMBLY_IDENTITY__M04:
	case HEADER_CZ_REASSEMBLY_IDENTITY__M05:
	case HEADER_CZ_REASSEMBLY_IDENTITY__M06:
	case HEADER_CZ_REASSEMBLY_IDENTITY__M07:
	case HEADER_CZ_REASSEMBLY_IDENTITY__M08:
	case HEADER_CZ_REASSEMBLY_IDENTITY__M09:
	case HEADER_CZ_REASSEMBLY_IDENTITY__M10:
	case HEADER_CZ_REASSEMBLY_IDENTITY__M11:
	case HEADER_CZ_REASSEMBLY_IDENTITY__M12:
	case HEADER_CZ_REASSEMBLY_IDENTITY__M13:
	case HEADER_CZ_REASSEMBLY_IDENTITY__M14:
	case HEADER_CZ_REASSEMBLY_IDENTITY__M15:
	case HEADER_CZ_REASSEMBLY_IDENTITY__M16:
	case HEADER_CZ_REASSEMBLY_IDENTITY__M17:
	case HEADER_CZ_REASSEMBLY_IDENTITY__M18:
	case HEADER_CZ_REASSEMBLY_IDENTITY__M19:
	case HEADER_CZ_REASSEMBLY_IDENTITY__M20:
	case HEADER_CZ_REASSEMBLY_IDENTITY__M21:
	case HEADER_CZ_REASSEMBLY_IDENTITY__M22:
	case HEADER_CZ_REASSEMBLY_IDENTITY__M23:
	case HEADER_CZ_REASSEMBLY_IDENTITY__M24:
	case HEADER_CZ_REASSEMBLY_IDENTITY__M25:
	case HEADER_CZ_REASSEMBLY_IDENTITY__M26:
	case HEADER_CZ_REASSEMBLY_IDENTITY__M27:
	case HEADER_CZ_REASSEMBLY_IDENTITY__M28:
	case HEADER_CZ_REASSEMBLY_IDENTITY__M29:
	case HEADER_CZ_REASSEMBLY_IDENTITY__M30:
	case HEADER_CZ_REASSEMBLY_IDENTITY__M31:
	case HEADER_CZ_REASSEMBLY_IDENTITY__M32:
	case HEADER_CZ_REASSEMBLY_IDENTITY__M33:
	case HEADER_CZ_REASSEMBLY_IDENTITY__M34:
	case HEADER_CZ_REASSEMBLY_IDENTITY__M35:
	case HEADER_CZ_REASSEMBLY_IDENTITY__M36:
	case HEADER_CZ_REASSEMBLY_IDENTITY__M37:
	case HEADER_CZ_REASSEMBLY_IDENTITY__M38:
	case HEADER_CZ_REASSEMBLY_IDENTITY__M39:
	case HEADER_CZ_REASSEMBLY_IDENTITY__M40:
	case HEADER_CZ_REASSEMBLY_IDENTITY__M41:
	{
		PACKET_CZ_REASSEMBLY_IDENTITY msg;
		m_recvQueue->CPacketQueue::GetData(sizeof(msg), (char *)&msg);
	}
	break;
	case HEADER_CZ_OPEN_SIMPLE_CASHSHOP_ITEMLIST:
	{
		this->CPCPacketHandler::OnCzOpenSimpleCashShopItemList(packetSize);
	}
	break;
	case HEADER_CZ_CLOSE_WINDOW:
	{
		this->CPCPacketHandler::OnCZOnCloseWindow(packetSize);
	}
	break;
	case HEADER_CZ_REQ_MAIL_RETURN:
	{
		this->CPCPacketHandler::OnMailReturn(packetSize);
	}
	break;
	case HEADER_CZ_LOCALBROADCAST:
	{
		this->CPCPacketHandler::OnLocalBroadCast(packetSize);
	}
	break;
	case HEADER_CZ_MAKE_GROUP2:
	{
		this->CPCPacketHandler::OnMakeGroup(packetSize);
	}
	break;
	case HEADER_CZ_REQ_OPENSTORE2:
	{
		this->CPCPacketHandler::OnReqOpenMCStore2(packetSize);
	}
	break;
	case HEADER_CZ_GUILD_CHAT:
	{
		this->CPCPacketHandler::OnGuildChat(packetSize);
	}
	break;
	case HEADER_CZ_REQ_ALLY_GUILD:
	{
		this->CPCPacketHandler::OnReqAllyGuild(packetSize);
	}
	break;
	case HEADER_CZ_ALLY_GUILD:
	{
		this->CPCPacketHandler::OnAllyGuild(packetSize);
	}
	break;
	case HEADER_CZ_REQ_HOSTILE_GUILD:
	{
		this->CPCPacketHandler::OnReqHostileGuild(packetSize);
	}
	break;
	case HEADER_CZ_REQ_DELETE_RELATED_GUILD:
	{
		this->CPCPacketHandler::OnReqDeleteRelatedGuild(packetSize);
	}
	break;
	case HEADER_CZ_REQ_ITEMIDENTIFY:
	{
		this->CPCPacketHandler::OnReqItemIdentify(packetSize);
	}
	break;
	case HEADER_CZ_REQ_ITEMCOMPOSITION_LIST:
	{
		this->CPCPacketHandler::OnReqItemCompositionList(packetSize);
	}
	break;
	case HEADER_CZ_REQ_ITEMCOMPOSITION:
	{
		this->CPCPacketHandler::OnReqItemComposition(packetSize);
	}
	break;
	case HEADER_CZ_REQ_ITEMREPAIR:
	{
		PACKET_CZ_REQ_ITEMREPAIR reqpacket;
		m_recvQueue->CPacketQueue::GetData(sizeof(reqpacket), (char *)&reqpacket);
		m_pc->CPC::ReqItemRepair(reqpacket.TargetItemInfo);
	}
	break;
	case HEADER_CZ_REQ_DISCONNECT:
	{
		this->CPCPacketHandler::OnReqDisconnect(packetSize);
	}
	break;
	case HEADER_CZ_REQMAKINGITEM:
	{
		this->CPCPacketHandler::OnReqMakingItem(packetSize);
	}
	break;
	case HEADER_CZ_USE_SKILL_TOGROUND_WITHTALKBOX:
	{
		this->CPCPacketHandler::OnReqUSE_SKILL_TOGROUND_WITHTALKBOX(packetSize);
	}
	break;
	case HEADER_CZ_REQNAME_BYGID:
	{
		this->CPCPacketHandler::OnReqNameByGID(packetSize);
	}
	break;
	case HEADER_CZ_RESET:
	{
		this->CPCPacketHandler::OnResetParameter(packetSize);
	}
	break;
	case HEADER_CZ_CHANGE_MAPTYPE:
	{
		this->CPCPacketHandler::OnChangeMapType(packetSize);
	}
	break;
	case HEADER_CZ_CHANGE_EFFECTSTATE:
	{
		this->CPCPacketHandler::OnChangeEffectState(packetSize);
	}
	break;
	case HEADER_CZ_TRYCAPTURE_MONSTER:
	{
		this->CPCPacketHandler::OnTryCaptureMonster(packetSize);
	}
	break;
	case HEADER_CZ_COMMAND_PET:
	{
		this->CPCPacketHandler::OnCommandPet(packetSize);
	}
	break;
	case HEADER_CZ_RENAME_PET:
	{
		this->CPCPacketHandler::OnRenamePet(packetSize);
	}
	break;
	case HEADER_CZ_RENAME_MER:
	{
		this->CPCPacketHandler::OnRenameHomun(packetSize);
	}
	break;
	case HEADER_CZ_SELECT_PETEGG:
	{
		this->CPCPacketHandler::OnSelectPetEgg(packetSize);
	}
	break;
	case HEADER_CZ_PETEGG_INFO:
	{
		this->CPCPacketHandler::OnPetEggInfo(packetSize);
	}
	break;
	case HEADER_CZ_PET_ACT:
	{
		this->CPCPacketHandler::OnPetAct(packetSize);
	}
	break;
	case HEADER_CZ_REQ_MAKINGARROW:
	{
		PACKET_CZ_REQ_MAKINGARROW msg;
		m_recvQueue->CPacketQueue::GetData(sizeof(msg), (char *)&msg);
		m_pc->m_pcitemInventoryMgr.CPCItemInventoryMgr::ReqMakeArrow(msg.id);
		--m_pc->m_lockCounter;
	}
	break;
	case HEADER_CZ_REQ_MAKINGITEM:
	{
		this->CPCPacketHandler::OnMakingItem();
	}
	break;
	case HEADER_CZ_REQ_CHANGECART:
	{
		PACKET_CZ_REQ_CHANGECART packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char *)&packet);

		if( m_pc->m_pcitemInventoryMgr.CPCItemInventoryMgr::GetBodyItemWeightByPercent() >= 90 )
			break;

		if( !m_pc->CPC::IsSkillUsable(SKID_MC_CHANGECART) )
			break;

		int isCartOn;
		m_pc->GetParameterValue(VAR_ISCARTON, isCartOn);
		if( !isCartOn )
			break;

		switch( packet.num )
		{
		case 1:
			if( m_pc->m_characterInfo.clevel > 0 )
				m_pc->SetEffectState(EFFECTSTATE_PUSHCART);
		break;
		case 2:
			if( m_pc->m_characterInfo.clevel > 40 )
				m_pc->SetEffectState(EFFECTSTATE_PUSHCART2);
		break;
		case 3:
			if( m_pc->m_characterInfo.clevel > 65 )
				m_pc->SetEffectState(EFFECTSTATE_PUSHCART3);
		break;
		case 4:
			if( m_pc->m_characterInfo.clevel > 80 )
				m_pc->SetEffectState(EFFECTSTATE_PUSHCART4);
		break;
		case 5:
			if( m_pc->m_characterInfo.clevel > 90 )
				m_pc->SetEffectState(EFFECTSTATE_PUSHCART5);
		break;
		}
	}
	break;
	case HEADER_CZ_REQMAKINGHOMUN:
	{
		PACKET_CZ_REQMAKINGHOMUN msg;
		m_recvQueue->CPacketQueue::GetData(sizeof(msg), (char *)&msg);
		if( msg.result )
			m_pc->CPC::AM_ReqMakingHomun();
	}
	break;
	case HEADER_CZ_GUILD_ZENY:
	{
		this->CPCPacketHandler::OnGuildZeny(packetSize);
	}
	break;
	case HEADER_CZ_REMOVE_AID:
	{
		this->CPCPacketHandler::OnRemoveAID(packetSize);
	}
	break;
	case HEADER_CZ_SHIFT:
	{
		this->CPCPacketHandler::OnShift(packetSize);
	}
	break;
	case HEADER_CZ_RECALL:
	{
		this->CPCPacketHandler::OnRecall(packetSize);
	}
	break;
	case HEADER_CZ_RECALL_GID:
	{
		this->CPCPacketHandler::OnRecallGID(packetSize);
	}
	break;
	case HEADER_CS_REQ_ENCRYPTION:
	{
		this->CPCPacketHandler::OnReqEncryption(packetSize);
	}
	break;
	case HEADER_CZ_REQ_REMAINTIME:
	{
		PACKET_CZ_REQ_REMAINTIME cz_req_remaintime;
		m_recvQueue->CPacketQueue::GetData(sizeof(cz_req_remaintime), (char *)&cz_req_remaintime);

		PACKET_ZH_REQ_REMAINTIME msg;
		msg.PacketType = HEADER_ZH_REQ_REMAINTIME;
		msg.AID = m_pc->GetAccountID();
		g_characterMgr->CCharacterMgr::SendToHServer(sizeof(msg), (const char *)&msg);
	}
	break;
	case HEADER_CZ_SELECTAUTOSPELL:
	{
		this->CPCPacketHandler::OnSelectAutoSpell(packetSize);
	}
	break;
	case HEADER_CZ_INPUT_EDITDLGSTR:
	{
		this->CPCPacketHandler::OnInputEditDlgStr(packetSize);
	}
	break;
	case HEADER_CZ_REQ_ACCOUNTNAME:
	{
		PACKET_CZ_REQ_ACCOUNTNAME msg;
		m_recvQueue->CPacketQueue::GetData(sizeof(msg), (char *)&msg);

		if( g_zoneScript->CZoneScript::SearchID(m_pc->m_characterInfo.accountName, CHECK_LOCALBROADCAST) == 0 )
			break; // doesn't have gm privilege

		PACKET_ZC_ACK_ACCOUNTNAME packet;
		packet.PacketType = HEADER_ZC_ACK_ACCOUNTNAME;
		packet.AID = msg.AID;
		CPC* pc = (CPC*)g_characterMgr->CCharacterMgr::FindCharacter(msg.AID, PC_TYPE);
		if( pc != NULL )
			memcpy(packet.name, pc->m_characterInfo.accountName, sizeof(packet.name));

		m_pc->CPC::Send(sizeof(packet), (char*)&packet);
	}
	break;
	case HEADER_CZ_REQ_JOIN_COUPLE:
	{
		PACKET_CZ_REQ_JOIN_COUPLE msg;
		m_recvQueue->CPacketQueue::GetData(sizeof(msg), (char *)&msg);

		CPC* pc = (CPC*)g_characterMgr->CCharacterMgr::FindCharacter(msg.AID, PC_TYPE);
		if( pc == NULL )
			break;

		PACKET_ZC_REQ_COUPLE packet;
		packet.PacketType = HEADER_ZC_REQ_COUPLE;
		packet.AID = m_pc->GetAccountID();
		packet.GID = m_pc->CPC::GetCharacterID();
		memcpy(packet.name, m_pc->m_characterInfo.characterName, sizeof(packet.name));
		pc->CPC::Send(sizeof(packet), (char*)&packet);
	}
	break;
	case HEADER_CZ_JOIN_COUPLE:
	{
		PACKET_CZ_JOIN_COUPLE reqpacket;
		m_recvQueue->CPacketQueue::GetData(sizeof(reqpacket), (char *)&reqpacket);

		CPC* pc = (CPC*)g_characterMgr->CCharacterMgr::FindCharacter(reqpacket.AID, PC_TYPE);
		if( pc == NULL || reqpacket.answer == 0 || m_pc->m_marriageInfo.bMarried )
			break;

		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_GETMARRIED, pc->CPC::GetCharacterID(), 0, 0, 0);
	}
	break;
	case HEADER_CZ_DORIDORI:
	{
		PACKET_CZ_DORIDORI msg;
		m_recvQueue->CPacketQueue::GetData(sizeof(msg), (char *)&msg);

		if( m_pc->GetState() != 6 )
			break;

		if( m_pc->CPC::GetCategorySecondJob() == JT_SUPERNOVICE )
		{
			m_pc->m_specialSP = 1;
			break;
		}

		if( g_skillTypeInfoMgr->CSkillTypeInfoMgr::IsAvailableJob(m_pc->m_characterInfo.job, SKID_TK_HPTIME) == 0 )
			break;

		if( m_pc->m_specialSP == 1 )
			break;

		if( m_pc->CPC::GetCategorySecondJob() == JT_STAR && GetServerRandom(0, 20000) % 5000 == 27 )
		{
			m_pc->m_pcSkill.CPCSkill::LoadStarPlaceInfo();
			m_pc->m_pcSkill.CPCSkill::UpdateStarPlace("", 100);
			m_pc->OnShowEffect(EF_ANGEL3);

			PACKET_ZC_STARSKILL packet;
			packet.PacketType = HEADER_ZC_STARSKILL;
			packet.mapName[0] = '\0';
			packet.monsterID = 0;
			packet.star = 0;
			packet.result = 30;
			m_pc->CPC::Send(sizeof(packet), (char *)&packet);
		}

		m_pc->m_specialSP = 1;
	}
	break;
	case HEADER_CZ_CHOPOKGI:
	{
		PACKET_CZ_CHOPOKGI msg;
		m_recvQueue->CPacketQueue::GetData(sizeof(msg), (char *)&msg);

		if( m_pc->CPC::GetCategorySecondJob() != JT_SUPERNOVICE )
			break;

		int exp;
		m_pc->GetParameterValue(VAR_EXP, exp);

		int nextexp = g_expParameter->CExpParameter::GetNextExp(m_pc->m_characterInfo.clevel, m_pc->m_characterInfo.job);

		double rate = (double)exp / (double)nextexp * 1000.0;
		if( nextexp != 0 && (int)rate != 0 && (int)rate % 100 == 0 )
		{
			m_pc->SetEffective(EFST_EXPLOSIONSPIRITS, 180000, 500, 0, 0, 0);
			m_pc->CPC::NotifyUseSkill(SKID_MO_EXPLOSIONSPIRITS, m_pc->m_characterInfo.accountID, m_pc->m_characterInfo.accountID, 5, true);
		}
	}
	break;
	case HEADER_CZ_REQ_JOIN_BABY:
	{
		PACKET_CZ_REQ_JOIN_BABY packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char *)&packet);

		CPC* partner = g_characterMgr->CCharacterMgr::FindPCByGID(m_pc->m_marriageInfo.partnerGID);
		if( m_pc->m_familyInfo.familyIndex != 0 || (partner != NULL && partner->m_familyInfo.familyIndex != 0) )
		{
			PACKET_ZC_BABYMSG msg;
			msg.PacketType = HEADER_ZC_BABYMSG;
			msg.MsgNo = 0;
			m_pc->CPC::Send(sizeof(msg), (char *)&msg);
			break;
		}

		if( m_pc->m_characterInfo.clevel < 70 || (partner != NULL && partner->m_characterInfo.clevel < 70) )
		{
			PACKET_ZC_BABYMSG msg;
			msg.PacketType = HEADER_ZC_BABYMSG;
			msg.MsgNo = 1;
			m_pc->CPC::Send(sizeof(msg), (char *)&msg);
			break;
		}

		CPC* baby = (CPC*)g_characterMgr->CCharacterMgr::FindCharacter(packet.AID, PC_TYPE);
		if( baby == NULL )
			break;

		if( baby->m_marriageInfo.bMarried )
		{
			PACKET_ZC_BABYMSG msg;
			msg.PacketType = HEADER_ZC_BABYMSG;
			msg.MsgNo = 2;
			m_pc->CPC::Send(sizeof(msg), (char *)&msg);
			break;
		}

		PACKET_ZC_REQ_BABY msg;
		msg.PacketType = HEADER_ZC_REQ_BABY;
		msg.AID = m_pc->GetAccountID();
		msg.GID = m_pc->CPC::GetCharacterID();
		memcpy(msg.name, m_pc->m_characterInfo.characterName, sizeof(msg.name));
		baby->CPC::Send(sizeof(msg), (char *)&msg);
	}
	break;
	case HEADER_CZ_JOIN_BABY:
	{
		PACKET_CZ_JOIN_BABY reqpacket;
		m_recvQueue->CPacketQueue::GetData(sizeof(reqpacket), (char *)&reqpacket);

		CPC* parent = (CPC*)g_characterMgr->CCharacterMgr::FindCharacter(reqpacket.AID, PC_TYPE);
		if( parent == NULL )
			break;

		if( reqpacket.answer == 0 )
			break;

		if( parent->m_marriageInfo.bMarried == FALSE )
			break;

		if( parent->m_characterInfo.sex == SEX_MALE )
			m_pc->CPC::OnMakeFamily(parent->CPC::GetCharacterID(), parent->m_marriageInfo.partnerGID);
		else
			m_pc->CPC::OnMakeFamily(parent->m_marriageInfo.partnerGID, parent->CPC::GetCharacterID());
	}
	break;
	case HEADER_CZ_AGREE_STARPLACE:
	{
		PACKET_CZ_AGREE_STARPLACE msg;
		m_recvQueue->CPacketQueue::GetData(sizeof(msg), (char *)&msg);

		if( msg.which != 10 )
		{
			m_pc->CPC::OnStarPlaceRemember(msg.which + 200, 0, 0);
		}
		else
		{// "Do you agree to cast the magic spell that consumes 1 Black Gemstone and 1,000,000 Zeny?"
			if( (m_pc->m_characterInfo.job < JT_NOVICE_H || m_pc->m_characterInfo.job > JT_CHICKEN2_H)
			&& m_pc->m_characterInfo.money >= 1000000
			&& m_pc->CPC::ConsumeItem(7710, 1, 0) ) // Black_Gemstone
			{
				m_pc->CPC::DeleteMoney(1000000);
				int exp = g_expParameter->CExpParameter::GetNextExp(m_pc->m_characterInfo.clevel) / 99;
				g_characterMgr->CCharacterMgr::SendMsg(m_pc, m_pc, CM_ADD_EXP, exp, 0, 0, 0);
			}
		}
	}
	break;
	case HEADER_CZ_ADD_FRIENDS:
	{
		this->CPCPacketHandler::OnAddFriend(packetSize);
	}
	break;
	case HEADER_CZ_DELETE_FRIENDS:
	{
		this->CPCPacketHandler::OnDeleteFriend(packetSize);
	}
	break;
	case HEADER_CZ_ACK_REQ_ADD_FRIENDS:
	{
		this->CPCPacketHandler::OnAckReqAddFriends(packetSize);
	}
	break;
	case HEADER_CZ_REQ_GIVE_MANNER_BYNAME:
	{
		this->CPCPacketHandler::OnGiveMannerPointByName(packetSize);
	}
	break;
	case HEADER_CZ_REQ_STATUS_GM:
	{
		this->CPCPacketHandler::OnReqStatus(packetSize);
	}
	break;
	case HEADER_CZ_BLACKSMITH_RANK:
	case HEADER_CZ_ALCHEMIST_RANK:
	case HEADER_CZ_TAEKWON_RANK:
	case HEADER_CZ_KILLER_RANK:
	{
		this->CPCPacketHandler::OnReqMakerRanking(Header, packetSize);
	}
	break;
	case HEADER_CZ_LESSEFFECT:
	{
		this->CPCPacketHandler::OnLessEffect(packetSize);
	}
	break;
	case HEADER_CZ_REQ_WEAPONREFINE:
	{
		PACKET_CZ_REQ_WEAPONREFINE msg;
		m_recvQueue->CPacketQueue::GetData(sizeof(msg), (char *)&msg);
		m_pc->CPC::ReqWeaponRefine(msg.Index);
	}
	break;
	case HEADER_CZ_ACK_GAME_GUARD:
	{
		this->CPCPacketHandler::OnAckGameGuard(packetSize);
	}
	break;
	case HEADER_CZ_COMMAND_MER:
	{
		this->CPCPacketHandler::OnCommandMercenary(packetSize);
	}
	break;
	case HEADER_CZ_REQUEST_MOVETOOWNER:
	{
		this->CPCPacketHandler::OnRequestMoveToOwner(packetSize);
	}
	break;
	case HEADER_CZ_REQUEST_MOVENPC:
	{
		this->CPCPacketHandler::OnRequestMoveNpc(packetSize);
	}
	break;
	case HEADER_CZ_REQUEST_ACTNPC:
	{
		this->CPCPacketHandler::OnRequestActNpc(packetSize);
	}
	break;
	case HEADER_CZ_ACK_STORE_PASSWORD:
	{
		if( g_storePasswordCheck == 1 )
			this->CPCPacketHandler::OnAckStorePassword(packetSize);
	}
	break;
	case HEADER_CZ_MAIL_GET_LIST:
	{
		this->CPCPacketHandler::OnMailGetList(packetSize);
	}
	break;
	case HEADER_CZ_MAIL_OPEN:
	{
		this->CPCPacketHandler::OnMailOpen(packetSize);
	}
	break;
	case HEADER_CZ_MAIL_DELETE:
	{
		this->CPCPacketHandler::OnMailDelete(packetSize);
	}
	break;
	case HEADER_CZ_MAIL_GET_ITEM:
	{
		this->CPCPacketHandler::OnMailGetItem(packetSize);
	}
	break;
	case HEADER_CZ_MAIL_RESET_ITEM:
	{
		this->CPCPacketHandler::OnMailResetItem(packetSize);
	}
	break;
	case HEADER_CZ_MAIL_ADD_ITEM:
	{
		this->CPCPacketHandler::OnMailAddItem(packetSize);
	}
	break;
	case HEADER_CZ_MAIL_SEND:
	{
		this->CPCPacketHandler::OnMailSend(packetSize);
	}
	break;
	case HEADER_CZ_AUCTION_CREATE:
	{
		this->CPCPacketHandler::OnAuctionCreate(packetSize);
	}
	break;
	case HEADER_CZ_AUCTION_ADD_ITEM:
	{
		this->CPCPacketHandler::OnAuctionAddItem(packetSize);
	}
	break;
	case HEADER_CZ_AUCTION_ADD:
	{
		this->CPCPacketHandler::OnAuctionAdd(packetSize);
	}
	break;
	case HEADER_CZ_AUCTION_ADD_CANCEL:
	{
		this->CPCPacketHandler::OnAuctionAddCancel(packetSize);
	}
	break;
	case HEADER_CZ_AUCTION_BUY:
	{
		this->CPCPacketHandler::OnAuctionBuy(packetSize);
	}
	break;
	case HEADER_CZ_AUCTION_ITEM_SEARCH:
	{
		this->CPCPacketHandler::OnAuctionItemSearch(packetSize);
	}
	break;
	case HEADER_CZ_AUCTION_REQ_MY_INFO:
	{
		this->CPCPacketHandler::OnAuctionReqMyInfo(packetSize);
	}
	break;
	case HEADER_CZ_AUCTION_REQ_MY_SELL_STOP:
	{
		this->CPCPacketHandler::OnAuctionMySellStop(packetSize);
	}
	break;
	case HEADER_CZ_REQUEST_MOVE:
	{
		this->CPCPacketHandler::OnMove(packetSize);
	}
	break;
	case HEADER_CZ_REQUEST_CHAT:
	{
		this->CPCPacketHandler::OnChat(packetSize);
	}
	break;
	case HEADER_CZ_CONTACTNPC:
	{
		this->CPCPacketHandler::OnContactNPC(packetSize);
	}
	break;
	case HEADER_CZ_WHISPER:
	{
		this->CPCPacketHandler::OnWhisper(packetSize);
	}
	break;
	case HEADER_CZ_REQUEST_TIME:
	{
		this->CPCPacketHandler::OnRequestTime(packetSize);
	}
	break;
	case HEADER_CZ_NOTIFY_ACTORINIT:
	{
		this->CPCPacketHandler::OnActorInit(packetSize);
	}
	break;
	case HEADER_CZ_REQNAME:
	{
		this->CPCPacketHandler::OnReqName(packetSize);
	}
	break;
	case HEADER_CZ_BROADCAST:
	{
		this->CPCPacketHandler::OnBroadCast(packetSize);
	}
	break;
	case HEADER_CZ_CHANGE_DIRECTION:
	{
		this->CPCPacketHandler::OnChangeDir(packetSize);
	}
	break;
	case HEADER_CZ_DISCONNECT_CHARACTER:
	{
		this->CPCPacketHandler::OnDisconnectCharacter(packetSize);
	}
	break;
	case HEADER_CZ_DISCONNECT_ALL_CHARACTER:
	{
		this->CPCPacketHandler::OnDisconnectAllCharacter(packetSize);
	}
	break;
	case HEADER_CZ_REQUEST_ACT:
	{
		this->CPCPacketHandler::OnReqAct1(packetSize, 0);
	}
	break;
	case HEADER_CZ_ITEM_PICKUP:
	{
		this->CPCPacketHandler::OnPickUpItem(packetSize);
	}
	break;
	case HEADER_CZ_ITEM_THROW:
	{
		this->CPCPacketHandler::OnThrowItem(packetSize);
	}
	break;
	case HEADER_CZ_USE_ITEM:
	{
		this->CPCPacketHandler::OnUseItem(packetSize);
	}
	break;
	case HEADER_CZ_REQ_WEAR_EQUIP:
	{
		this->CPCPacketHandler::OnWearEquip(packetSize);
	}
	break;
	case HEADER_CZ_REQ_TAKEOFF_EQUIP:
	{
		this->CPCPacketHandler::OnTakeOffEquip(packetSize);
	}
	break;
	case HEADER_CZ_REQ_ITEM_EXPLANATION_BYNAME:
	{
		this->CPCPacketHandler::OnItemExplanationByName(packetSize);
	}
	break;
	case HEADER_CZ_CHOOSE_MENU:
	{
		this->CPCPacketHandler::OnChooseMenu(packetSize);
	}
	break;
	case HEADER_CZ_REQ_NEXT_SCRIPT:
	{
		this->CPCPacketHandler::OnReqNextScript(packetSize);
	}
	break;
	case HEADER_CZ_RESTART:
	{
		this->CPCPacketHandler::OnRestart(packetSize);
	}
	break;
	case HEADER_CZ_STATUS_CHANGE:
	{
		this->CPCPacketHandler::OnStatusChange(packetSize);
	}
	break;
	case HEADER_CZ_REQ_EMOTION:
	{
		this->CPCPacketHandler::OnReqEmotion(packetSize);
	}
	break;
	case HEADER_CZ_REQ_USER_COUNT:
	{
		this->CPCPacketHandler::OnReqUserCount(packetSize);
	}
	break;
	case HEADER_CZ_ACK_SELECT_DEALTYPE:
	{
		this->CPCPacketHandler::OnSelectDealType(packetSize);
	}
	break;
	case HEADER_CZ_PC_PURCHASE_ITEMLIST:
	{
		this->CPCPacketHandler::OnPurchaseItem(packetSize);
	}
	break;
	case HEADER_CZ_PC_SELL_ITEMLIST:
	{
		this->CPCPacketHandler::OnSellItem(packetSize);
	}
	break;
	case HEADER_CZ_SETTING_WHISPER_PC:
	{
		this->CPCPacketHandler::OnSettingWhisperPC(packetSize);
	}
	break;
	case HEADER_CZ_SETTING_WHISPER_STATE:
	{
		this->CPCPacketHandler::OnSettingWhisperState(packetSize);
	}
	break;
	case HEADER_CZ_REQ_WHISPER_LIST:
	{
		this->CPCPacketHandler::OnReqWhisperList(packetSize);
	}
	break;
	case HEADER_CZ_CREATE_CHATROOM:
	{
		this->CPCPacketHandler::OnCreateChatRoom(packetSize);
	}
	break;
	case HEADER_CZ_REQ_ENTER_ROOM:
	{
		this->CPCPacketHandler::OnReqEnterRoom(packetSize);
	}
	break;
	case HEADER_CZ_CHANGE_CHATROOM:
	{
		this->CPCPacketHandler::OnChangeChatRoom(packetSize);
	}
	break;
	case HEADER_CZ_REQ_ROLE_CHANGE:
	{
		this->CPCPacketHandler::OnReqChangeRole(packetSize);
	}
	break;
	case HEADER_CZ_REQ_EXPEL_MEMBER:
	{
		this->CPCPacketHandler::OnReqExpelMember(packetSize);
	}
	break;
	case HEADER_CZ_EXIT_ROOM:
	{
		this->CPCPacketHandler::OnExitRoom(packetSize);
	}
	break;
	case HEADER_CZ_REQ_EXCHANGE_ITEM:
	{
		this->CPCPacketHandler::OnReqExchangeItem(packetSize);
	}
	break;
	case HEADER_CZ_ACK_EXCHANGE_ITEM:
	{
		this->CPCPacketHandler::OnAckReqExchangeItem(packetSize);
	}
	break;
	case HEADER_CZ_EXEC_EXCHANGE_ITEM:
	{
		this->CPCPacketHandler::OnExecExchangeItem(packetSize);
	}
	break;
	case HEADER_CZ_ADD_EXCHANGE_ITEM:
	{
		this->CPCPacketHandler::OnAddExchangeItem(packetSize);
	}
	break;
	case HEADER_CZ_CONCLUDE_EXCHANGE_ITEM:
	{
		this->CPCPacketHandler::OnConcludeExchangeItem(packetSize);
	}
	break;
	case HEADER_CZ_CANCEL_EXCHANGE_ITEM:
	{
		this->CPCPacketHandler::OnCancelExchangeItem(packetSize);
	}
	break;
	case HEADER_CZ_MOVE_ITEM_FROM_BODY_TO_STORE:
	{
		this->CPCPacketHandler::OnMoveItemFromBodyToStore(packetSize);
	}
	break;
	case HEADER_CZ_MOVE_ITEM_FROM_STORE_TO_BODY:
	{
		this->CPCPacketHandler::OnMoveItemFromStoreToBody(packetSize);
	}
	break;
	case HEADER_CZ_MOVE_ITEM_FROM_BODY_TO_CART:
	{
		this->CPCPacketHandler::OnMoveItemFromBodyToCart(packetSize);
	}
	break;
	case HEADER_CZ_MOVE_ITEM_FROM_CART_TO_BODY:
	{
		this->CPCPacketHandler::OnMoveItemFromCartToBody(packetSize);
	}
	break;
	case HEADER_CZ_MOVE_ITEM_FROM_STORE_TO_CART:
	{
		this->CPCPacketHandler::OnMoveItemFromStoreToCart(packetSize);
	}
	break;
	case HEADER_CZ_MOVE_ITEM_FROM_CART_TO_STORE:
	{
		this->CPCPacketHandler::OnMoveItemFromCartToStore(packetSize);
	}
	break;
	case HEADER_CZ_CLOSE_STORE:
	{
		this->CPCPacketHandler::OnCloseStore(packetSize);
	}
	break;
	case HEADER_CZ_REQ_JOIN_GROUP:
	{
		this->CPCPacketHandler::OnReqJoinGroup(packetSize);
	}
	break;
	case HEADER_CZ_CHANGE_GROUPEXPOPTION:
	{
		this->CPCPacketHandler::OnChangeGroupExpOption(packetSize);
	}
	break;
	case HEADER_CZ_JOIN_GROUP:
	{
		this->CPCPacketHandler::OnJoinGroup(packetSize);
	}
	break;
	case HEADER_CZ_REQ_LEAVE_GROUP:
	{
		PACKET_CZ_REQ_LEAVE_GROUP msg;
		m_recvQueue->CPacketQueue::GetData(sizeof(msg), (char *)&msg);
		this->CPCPacketHandler::OnCZ_REQ_LEAVE_GROUP(msg);
	}
	break;
	case HEADER_CZ_REQ_EXPEL_GROUP_MEMBER:
	{
		this->CPCPacketHandler::OnReqExpelGroupMember(packetSize);
	}
	break;
	case HEADER_CZ_REQUEST_CHAT_PARTY:
	{
		this->CPCPacketHandler::OnChatParty(packetSize);
	}
	break;
	case HEADER_CZ_UPGRADE_SKILLLEVEL:
	{
		this->CPCPacketHandler::OnUpgradeSkillLevel(packetSize);
	}
	break;
	case HEADER_CZ_CANCEL_LOCKON:
	{
		this->CPCPacketHandler::OnCancelLockOn(packetSize);
	}
	break;
	case HEADER_CZ_USE_SKILL_TOGROUND:
	{
		PACKET_CZ_USE_SKILL_TOGROUND msg;
		m_recvQueue->CPacketQueue::GetData(sizeof(msg), (char *)&msg);

		if( g_skillTypeInfoMgr->CSkillTypeInfoMgr::GetSKClass(msg.SKID) == 3 )
			this->CPCPacketHandler::OnMercenary_UseSkill_ToGround(msg);
		else
			this->CPCPacketHandler::OnUseSkillToGround(msg);
	}
	break;
	case HEADER_CZ_SELECT_WARPPOINT:
	{
		this->CPCPacketHandler::OnSelectWarpPoint(packetSize);
	}
	break;
	case HEADER_CZ_REMEMBER_WARPPOINT:
	{
		this->CPCPacketHandler::OnRememberWarpPoint(packetSize);
	}
	break;
	case HEADER_CZ_REQ_CARTOFF:
	{
		this->CPCPacketHandler::OnCartOff(packetSize);
	}
	break;
	case HEADER_CZ_REQ_CLOSESTORE:
	{
		this->CPCPacketHandler::OnReqCloseMCStore(packetSize);
	}
	break;
	case HEADER_CZ_REQ_OPENSTORE:
	{
		this->CPCPacketHandler::OnReqOpenMCStore(packetSize);
	}
	break;
	case HEADER_CZ_PC_PURCHASE_ITEMLIST_FROMMC:
	{
		this->CPCPacketHandler::PurchaseItemFromMCStore(packetSize);
	}
	break;
	case HEADER_CZ_REQ_BUY_FROMMC:
	{
		this->CPCPacketHandler::OnReqItemListFromMCStore(packetSize);
	}
	break;
	case HEADER_CZ_PKMODE_CHANGE:
	{
		this->CPCPacketHandler::OnPKModeChange(packetSize);
	}
	break;
	case HEADER_CZ_ITEM_CREATE:
	{
		this->CPCPacketHandler::OnItemCreate(packetSize);
	}
	break;
	case HEADER_CZ_MOVETO_MAP:
	{
		this->CPCPacketHandler::OnAdminMapMove(packetSize);
	}
	break;
	case HEADER_CZ_INPUT_EDITDLG:
	{
		this->CPCPacketHandler::OnInputEditDlg(packetSize);
	}
	break;
	case HEADER_CZ_CLOSE_DIALOG:
	{
		this->CPCPacketHandler::OnCloseDialog(packetSize);
	}
	break;
	case HEADER_CZ_REQ_GUILD_MENUINTERFACE:
	{
		this->CPCPacketHandler::OnReqGuildMenuInterface(packetSize);
	}
	break;
	case HEADER_CZ_REQ_GUILD_MENU:
	{
		this->CPCPacketHandler::OnReqGuildMenu(packetSize);
	}
	break;
	case HEADER_CZ_REQ_GUILD_EMBLEM_IMG:
	{
		this->CPCPacketHandler::OnReqGuildEmblemImg(packetSize);
	}
	break;
	case HEADER_CZ_REGISTER_GUILD_EMBLEM_IMG:
	{
		this->CPCPacketHandler::OnRegisterGuildEmblemImg(packetSize);
	}
	break;
	case HEADER_CZ_REQ_CHANGE_MEMBERPOS:
	{
		this->CPCPacketHandler::OnReqChangeMemberPos(packetSize);
	}
	break;
	case HEADER_CZ_REQ_OPEN_MEMBER_INFO:
	{
		this->CPCPacketHandler::OnReqOpenMemberInfo(packetSize);
	}
	break;
	case HEADER_CZ_REQ_LEAVE_GUILD:
	{
		this->CPCPacketHandler::OnReqLeaveGuild(packetSize);
	}
	break;
	case HEADER_CZ_REQ_BAN_GUILD:
	{
		this->CPCPacketHandler::OnReqBanGuild(packetSize);
	}
	break;
	case HEADER_CZ_REQ_DISORGANIZE_GUILD:
	{
		this->CPCPacketHandler::OnReqDisorganizeGuild(packetSize);
	}
	break;
	case HEADER_CZ_REG_CHANGE_GUILD_POSITIONINFO:
	{
		this->CPCPacketHandler::OnReqChangeGuildPositionInfo(packetSize);
	}
	break;
	case HEADER_CZ_REQ_MAKE_GUILD:
	{
		this->CPCPacketHandler::OnReqMakeGuild(packetSize);
	}
	break;
	case HEADER_CZ_REQ_JOIN_GUILD:
	{
		this->CPCPacketHandler::OnReqJoinGuild(packetSize);
	}
	break;
	case HEADER_CZ_JOIN_GUILD:
	{
		this->CPCPacketHandler::OnJoinGuild(packetSize);
	}
	break;
	case HEADER_CZ_GUILD_NOTICE:
	{
		this->CPCPacketHandler::OnGuildNotice(packetSize);
	}
	break;
	case HEADER_CZ_REQ_GIVE_MANNER_POINT:
	{
		this->CPCPacketHandler::OnGiveMannerPoint(packetSize);
	}
	break;
	case HEADER_CZ_MAKE_GROUP:
	{
		this->CPCPacketHandler::OnMakeGroup(packetSize); //NOTE: won't parse correctly
	}
	break;
	case HEADER_CZ_USE_SKILL:
	{
		PACKET_CZ_USE_SKILL msg;
		m_recvQueue->CPacketQueue::GetData(sizeof(msg), (char *)&msg);
		switch( g_skillTypeInfoMgr->CSkillTypeInfoMgr::GetSKClass(msg.SKID) )
		{
		case 0: this->CPCPacketHandler::OnUseSkill(msg.SKID, msg.selectedLevel, msg.targetID); break;
		case 1: this->CPCPacketHandler::OnUseSkill_Merce(msg.SKID, msg.selectedLevel, msg.targetID); break;
		case 2: this->CPCPacketHandler::OnUseGuildSkill(msg.SKID, msg.selectedLevel, msg.targetID); break;
		case 3: this->CPCPacketHandler::OnMercenary_UseSkill(msg.SKID, msg.selectedLevel, msg.targetID); break;
		default: break;
		}
		m_pc->m_pcSkill.CPCSkill::SetSKIDFromAbracadabra(0);
	}
	break;
	case HEADER_CZ_ENTER:
	{
		PACKET_CZ_ENTER reqpacket;
		m_recvQueue->CPacketQueue::GetData(sizeof(reqpacket), (char *)&reqpacket);
		this->CPCPacketHandler::OnEnter(reqpacket.AID, reqpacket.GID, reqpacket.AuthCode, reqpacket.clientTime, reqpacket.Sex);
	}
	break;
	default:
	{
		m_recvQueue->CPacketQueue::Reset();
		m_pc->AddErrorCount(".\\PCPacketHandler.cpp", 3048, 4, timeGetTime());
		g_errorLogs->CErrorLog::CriticalErrorLogFmt(".\\PCPacketHandler.cpp", 3049, "Not Header %d AID : %d", Header, m_pc->GetAccountID());
		Trace("not Header pchandler:%d\n", Header);
		return 0;
	}
	break;
	}

	return -1;
}


hook_method<void (CPCPacketHandler::*)(const unsigned long in_AID, const unsigned long in_GID, const int in_AuthCode, const unsigned long in_clientTime, const unsigned char in_Sex)> CPCPacketHandler::_OnEnter(SERVER, "CPCPacketHandler::OnEnter");
void CPCPacketHandler::OnEnter(const unsigned long in_AID, const unsigned long in_GID, const int in_AuthCode, const unsigned long in_clientTime, const unsigned char in_Sex)
{
	return (this->*_OnEnter)(in_AID, in_GID, in_AuthCode, in_clientTime, in_Sex);

	PACKET_ZH_LOGON packet;
	packet.PacketType = HEADER_ZH_LOGON;
	packet.AID = in_AID;
	packet.GID = in_GID;
	packet.AuthCode = in_AuthCode;
	packet.curUser = 0;
	packet.sex = 0;

	packet.curUser = g_characterMgr->CCharacterMgr::GetCurPlayChar();
	m_pc->CPC::SetMapLoadingFlag(1);

	if( g_characterMgr->CCharacterMgr::SearchPCFromIndexInfo(in_AID) != NULL )
	{
		g_errorLogs->CErrorLog::CriticalErrorLogFmt(".\\PCPacketHandler.cpp", 3221, "try duplicate login AID: %d, %d", in_AID, m_pc->CPC::GetErrorCount());
		m_pc->AddErrorCount(".\\PCPacketHandler.cpp", 3222, 4, timeGetTime());
		return;
	}

	if( in_AID <= PC_MINIMUM_AID || in_GID <= PC_MINIMUM_GID )
	{
		m_pc->AddErrorCount(".\\PCPacketHandler.cpp", 3225, 4, timeGetTime());
		g_errorLogs->CErrorLog::CriticalErrorLogFmt(".\\PCPacketHandler.cpp", 3226, "PC Index Valid (AID:%d <= 100000) or (newGID:%d <= 100000)", in_AID, in_GID);
		return;
	}

	m_pc->m_characterTimeInfo.connectedTime = timeGetTime();
	m_pc->m_characterTimeInfo.clientLocalConnectTime = in_clientTime;
	m_pc->m_characterInfo.sex = in_Sex;
	m_pc->m_pcClientUpdater.CPCClientUpdater::SetAccountID(in_AID);
	m_pc->m_pcClientUpdater.CPCClientUpdater::SetCharacterID(in_GID);
	m_pc->m_pcClientUpdater.CPCClientUpdater::SetAuthCode(in_AuthCode);

	g_characterMgr->CCharacterMgr::AddPCToIndexInfo(in_AID, m_pc->m_index, m_pc->m_characterTimeInfo.connectedTime);
	g_characterMgr->CCharacterMgr::SendToHServer(sizeof(packet), (const char *)&packet);
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnChat(SERVER, "CPCPacketHandler::OnChat");
HOOKED void CPCPacketHandler::OnChat(int len) // line 3058-3165
{
	char packetbuf[256];
	m_recvQueue->PeekData(sizeof(packetbuf), packetbuf);

	char *name, *message;
	int namelen_, messagelen;
	if( clif_process_message(m_pc, packetbuf, 0, &name, &namelen_, &message, &messagelen) )
	{
		if( AtCommand(m_pc, message) )
		{
			m_recvQueue->RemoveData(len);
			return;
		}
	}

	return (this->*_OnChat)(len);

	if( len > 220 || (unsigned int)len <= 4 )
	{
		Trace("AE:Chat LengthInvalid\n");
		g_errorLogs->CErrorLog::CriticalErrorLog("Chat Length Invalid\n", 3062, ".\\PCPacketHandler.cpp");
		m_pc->AddErrorCount(".\\PCPacketHandler.cpp", 3063, 4, timeGetTime());
		return; // invalid packet length
	}

	char buffer[256];
	m_recvQueue->CPacketQueue::GetData(len, buffer);
	buffer[255] = '\0';
	PACKET_CZ_REQUEST_CHAT* packet = reinterpret_cast<PACKET_CZ_REQUEST_CHAT*>(&buffer);

	if( m_pc != NULL && m_pc->IsItPossible(MAPPROPERTY_NO_CHATTING) != 0 )
	{
		m_pc->CPC::SendZCMsg(MSI_NO_CHATTING);
		return; // can't chat in this map
	}

	int namelen = (int)strlen(m_pc->m_characterInfo.characterName);
	if( len <= namelen )
	{
		Trace("AE:Name length Invalid\n");
		g_errorLogs->CErrorLog::CriticalErrorLog("Name Length Invalid\n", 3086, ".\\PCPacketHandler.cpp");
		m_pc->AddErrorCount(".\\PCPacketHandler.cpp", 3087, 4, timeGetTime());
		return; // message smaller than name
	}

	if ( strncmp(m_pc->m_characterInfo.characterName, packet->Text, namelen) != 0 )
	{
		Trace("AE:Invalid name compare\n");
		g_errorLogs->CErrorLog::CriticalErrorLog("Invalid Name Chat\n", 3093, ".\\PCPacketHandler.cpp");
		m_pc->AddErrorCount(".\\PCPacketHandler.cpp", 3094, 4, timeGetTime());
		return; // name mismatch
	}

	if( m_pc->CPC::IsBadGuy() || m_pc->GetEffective(EFST_CRYSTAL, 0) != 0 )
		return; // player can't chat in the current state

	PACKET_ZC_NOTIFY_PLAYERCHAT* playerpacket = reinterpret_cast<PACKET_ZC_NOTIFY_PLAYERCHAT*>(&buffer);
	playerpacket->PacketType = HEADER_ZC_NOTIFY_PLAYERCHAT;
	m_pc->Send(len, (char*)playerpacket);

	char sendBuffer[256];
	PACKET_ZC_NOTIFY_CHAT* outpacket = reinterpret_cast<PACKET_ZC_NOTIFY_CHAT*>(&sendBuffer);
	outpacket->PacketType = HEADER_ZC_NOTIFY_CHAT;
	outpacket->PacketLength = len + 4;
	outpacket->GID = m_pc->m_pcClientUpdater.CPCClientUpdater::GetAccountID();
	memcpy(outpacket->Text, playerpacket->Text, len - 4);

	CRoom* room = g_roomMgr->CRoomMgr::SearchRoom(m_pc->CPC::GetRoomID());
	if( room )
	{
		room->CRoom::BroadCast(len + 4, (char*)outpacket, m_pc->GetAccountID());
	}
	else
	{
		mystd::vector<ClientCache*>& cacheList = m_pc->m_neighborCache.CNeighborCache::GetListPoint();
		for( mystd::vector<ClientCache*>::iterator iter = cacheList.begin(); iter != cacheList.end(); ++iter )
		{
			ClientCache* clientCache = *iter;

			CPC* other = g_characterMgr->CCharacterMgr::FindCharacterByIndex(clientCache->AID, clientCache->Index);
			if( other == NULL || m_pc->m_pcClientUpdater.CPCClientUpdater::IsMyArea(other, 9) == 0 || m_pc->CPC::GetRoomID() != other->CPC::GetRoomID() )
				continue;

			g_characterMgr->CCharacterMgr::SendMsg(m_pc, other, CM_CHAT, len + 4, (int)outpacket, 0, 0);
		}
	}
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnRequestTime(SERVER, "CPCPacketHandler::OnRequestTime");
void CPCPacketHandler::OnRequestTime(int len)
{
	return (this->*_OnRequestTime)(len);

	PACKET_CZ_REQUEST_TIME inpacket;
	m_recvQueue->CPacketQueue::GetData(sizeof(inpacket), (char *)&inpacket);

	m_pc->m_characterTimeInfo.LastClientTime = inpacket.clientTime;

	if( SPEEDHACK_DETECTETIME > 0 && SPEEDHACK_DETECTETIME <= abs(int((timeGetTime() - inpacket.clientTime) - (m_pc->m_characterTimeInfo.connectedTime - m_pc->m_characterTimeInfo.clientLocalConnectTime))) )
	{
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_NOTIFY_BAN, 3, 0, 0, 0);
		return;
	}

	if( !m_pc->CPC::IsSendable() )
		return;

	PACKET_ZC_NOTIFY_TIME outpacket;
	outpacket.PacketType = HEADER_ZC_NOTIFY_TIME;
	outpacket.time = timeGetTime();
	m_pc->CPC::Send(sizeof(outpacket), (char *)&outpacket);
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnActorInit(SERVER, "CPCPacketHandler::OnActorInit");
void CPCPacketHandler::OnActorInit(int len) // line 22
{
	return (this->*_OnActorInit)(len);

	PACKET_CZ_NOTIFY_ACTORINIT packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char *)&packet);

	m_pc->CPC::SetMapLoadingFlag(0);

	if( !m_pc->m_isValid )
	{
		Trace("AE:Actor Init pc invalid\n");
		g_errorLogs->CErrorLog::CriticalErrorLog("Actor Init Fail\n", 28, ".\\PCPacketHandlerLower.cpp");
		m_pc->AddErrorCount(".\\PCPacketHandlerLower.cpp", 29, 4,timeGetTime());
		return;
	}

	if( !m_pc->m_pcClientUpdater.CPCClientUpdater::AddSectionMgr() )
	{
		Trace("AE:ActorInit AddSection fail\n");
		g_errorLogs->CErrorLog::CriticalErrorLog("Add Section Fail\n", 36, ".\\PCPacketHandlerLower.cpp");
		m_pc->AddErrorCount(".\\PCPacketHandlerLower.cpp", 37, 4, timeGetTime());
		return;
	}

	m_pc->m_pcClientUpdater.CPCClientUpdater::SetSendable(1);
	m_pc->m_pcClientUpdater.CPCClientUpdater::NotifyLongParameter(VAR_MAXEXP, g_expParameter->CExpParameter::GetNextExp(m_pc->m_characterInfo.clevel, m_pc->m_characterInfo.job));
	m_pc->m_pcClientUpdater.CPCClientUpdater::NotifyLongParameter(VAR_MAXJOBEXP, g_expParameter->CExpParameter::GetNextJobExp(m_pc->m_characterInfo.joblevel, m_pc->m_characterInfo.job));
	m_pc->m_pcClientUpdater.CPCClientUpdater::NotifyParameter(VAR_MAXWEIGHT, m_pc->CPC::GetBodyMaxItemWeight());
	m_pc->m_pcClientUpdater.CPCClientUpdater::NotifyParameter(VAR_WEIGHT, m_pc->CPC::GetBodyItemWeight());
	m_pc->m_pcClientUpdater.CPCClientUpdater::NotifyParameter(VAR_SPPOINT, m_pc->m_characterInfo.sppoint);
	m_pc->m_pcitemInventoryMgr.CPCItemInventoryMgr::NotifyItemInfo(0);
	m_pc->CPC::InitEnemyInfo();
	m_pc->m_pcClientUpdater.CPCClientUpdater::ReqStatus();

	int isCartOn;
	m_pc->GetParameterValue(VAR_ISCARTON, isCartOn);
	if( isCartOn )
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_CARTON, 0, 0, 0, (int)this) ;

	m_pc->SetEffectState(m_pc->CPC::GetEffectState());
	m_pc->m_loadingCompleteTime = timeGetTime();
	m_pc->m_pcBattle.CPCBattle::CallHomun(0);
	m_pc->m_scrollItemIndex = 0;

	if( m_pc->CCharacter::GetMapRes() != NULL )
	{
		unsigned char property_packet[26];
		PACKET_ZC_MAPPROPERTY& packet = *(PACKET_ZC_MAPPROPERTY*)property_packet;
		packet.PacketType = HEADER_ZC_MAPPROPERTY;
		packet.PacketLength = sizeof(property_packet);
		packet.type = m_pc->CCharacter::GetMapRes()->CMapRes::GetType();
		m_pc->CCharacter::GetMapRes()->CMapRes::GetProprtyByteArray(packet.array, 20);
		m_pc->CPC::Send(packet.PacketLength, (char*)&packet);

		PACKET_ZC_NOTIFY_MAPPROPERTY2 outpacket;
		outpacket.PacketType = HEADER_ZC_NOTIFY_MAPPROPERTY2;
		outpacket.type = m_pc->CCharacter::GetMapRes()->CMapRes::GetType();
		m_pc->CPC::Send(sizeof(outpacket), (char*)&outpacket);

		if( m_pc->IsItPossible(MAPPROPERTY_PKSERVER) )
		{
			PACKET_ZC_NOTIFY_MAPPROPERTY outpacket;
			outpacket.PacketType = HEADER_ZC_NOTIFY_MAPPROPERTY;
			outpacket.type = 4;
			m_pc->CPC::Send(sizeof(outpacket), (char*)&outpacket);
		}
		else
		if( m_pc->IsItPossible(MAPPROPERTY_PVPSERVER) )
		{
			PACKET_ZC_NOTIFY_MAPPROPERTY outpacket;
			outpacket.PacketType = HEADER_ZC_NOTIFY_MAPPROPERTY;
			outpacket.type = 5;
			m_pc->CPC::Send(sizeof(outpacket), (char*)&outpacket);
		}

		if( m_pc->IsItPossible(MAPPROPERTY_COUNT_PK) )
			m_pc->CPC::UpdatePVPWinPoint(0);

		if( m_pc->m_characterInfo.GroupID && m_pc->IsItPossible(MAPPROPERTY_NO_PARTY_FORMATION) )
		{
			PACKET_ZI_REQ_LEAVE_GROUP outpacket;
			outpacket.PacketType = HEADER_ZI_REQ_LEAVE_GROUP;
			outpacket.AID = m_pc->GetAccountID();
			outpacket.GID = m_pc->CPC::GetCharacterID();
			g_characterMgr->CCharacterMgr::SendToIServer(sizeof(outpacket), (char*)&outpacket);

			m_pc->CPC::SendZCMsg(MSI_NOPARTY);
		}
	}

	if( m_pc->IsSiegeMode() || m_pc->CCharacter::IsBattleFieldMode() )
		m_pc->ResetEffective(EFST_ENDURE, 0);

	m_pc->m_pcClientUpdater.CPCClientUpdater::NotifyParameter(VAR_SPEED, m_pc->CPC::GetSpeed());
	m_pc->m_pcClientUpdater.CPCClientUpdater::NotifySpiritsInfo(m_pc);

	if( m_pc->GetEffective(EFST_BDPLAYING, 0) )
		m_pc->m_pcSkill.CPCSkill::SetPosPlayingSkill(m_pc->m_pathInfo.m_moveInfo.xPos, m_pc->m_pathInfo.m_moveInfo.yPos);

	if( m_pc->GetEffective(EFST_SG_WARM, 0) )
		m_pc->m_pcSkill.CPCSkill::SetPosPlayingSkill(m_pc->m_pathInfo.m_moveInfo.xPos, m_pc->m_pathInfo.m_moveInfo.yPos);

	m_pc->m_pcClientUpdater.CPCClientUpdater::NotifySpriteChange(m_pc, 2, m_pc->m_characterInfo.weapon);

	if( m_pc->m_pcBattle.m_Mercenary.CPCBattleMercenary::isCall() && !m_pc->m_pcBattle.CPCBattle::MercenaryCall(CPCBattle::LOAD, 0) )
	{
		Trace("AE:ActorInit MercenaryCall fail\n");
		g_errorLogs->CErrorLog::CriticalErrorLog("MercenaryCall Fail\n", 267, ".\\PCPacketHandlerLower.cpp");
		m_pc->AddErrorCount(".\\PCPacketHandlerLower.cpp", 268, 4, timeGetTime());
		return;
	}

	if( m_pc->m_PCBangInfo.isPCBang && m_pc->m_PCBangInfo.NotifyToClientCnt > 0 )
	{
		PACKET_ZC_PCBANG_EFFECT pcbang_effect_packet;
        pcbang_effect_packet.PacketType = HEADER_ZC_PCBANG_EFFECT;
        pcbang_effect_packet.ExpFactor = (int)(m_pc->m_PCBangInfo.ExpFactor * 100.0) - 100;
        pcbang_effect_packet.ExpFactor2 = (int)(m_pc->m_PCBangInfo.ExpFactor2 * 100.0) - 100;
		pcbang_effect_packet.DropFactor = (int)((m_pc->m_PCBangInfo.DropFactor - 1.0) * 100.0);
		m_pc->CPC::Send(sizeof(pcbang_effect_packet), (char *)&pcbang_effect_packet);
        m_pc->m_PCBangInfo.NotifyToClientCnt = 0;
	}

	m_pc->m_pcClientUpdater.CPCClientUpdater::NotifyBattleFieldCampInfo(m_pc);
	this->CPCPacketHandler::NotifyBattleFieldPoint();
	this->CPCPacketHandler::ResetReqGuildTime();

	int GDID = 0;
	m_pc->GetParameterValue(VAR_GDID, GDID);

	if( GDID != 0 )
	{
		Trace("Logon 한 유저의 GDID = %d \n", GDID);
		CZGuildInfo* g = (CZGuildInfo*)g_ZGuildMgr->CGuildMgr::SearchGuild(GDID);
		if( g != NULL )
		{
			g->CZGuildInfo::SendGuildNotice(m_pc->GetAccountID());
			if( g->CGuild::IsMaster(m_pc->m_characterInfo.characterID) )
				m_pc->m_pcSkill.CPCSkill::SetMasterSkill(g);
		}
	}
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnContactNPC(SERVER, "CPCPacketHandler::OnContactNPC");
void CPCPacketHandler::OnContactNPC(int len)
{
	return (this->*_OnContactNPC)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int packetSize)> CPCPacketHandler::_OnReqName(SERVER, "CPCPacketHandler::OnReqName");
HOOKED void CPCPacketHandler::OnReqName(int packetSize)
{
//	return (this->*_OnReqName)(packetSize);

	PACKET_CZ_REQNAME packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char *)&packet);

	if( !m_pc->m_isValid )
	{
		Trace("AE:OnReqName pc invalid\n");
		m_pc->AddErrorCount(".\\PCPacketHandler.cpp", 3616, 4, timeGetTime());
		return;
	}

	CCharacter* ch = g_characterMgr->CCharacterMgr::FindCharacter(packet.AID, UNKNOWN_TYPE);
	if( ch == NULL )
		return;

	if( !m_pc->IsMyArea(ch, AREA_SIZE) )
		return;

	if( ch->GetType() != PC_TYPE )
	{// non-player object, or not online
		g_characterMgr->CCharacterMgr::SendMsg(m_pc, packet.AID, CM_REQ_NAME, 0, 0, 0, 0);
		return;
	}

	CPC* pc = (CPC*)ch;

	int GDID = 0;
	pc->GetParameterValue(VAR_GDID, GDID);

	int GID = pc->m_characterInfo.characterID;
	if( GID == 0 )
		return;

	if( IsSetting(SETTING_KILLER_SYSTEM) && pc->CPC::IsCrazyKiller() )
	{
		PACKET_ZC_NOTIFY_CRAZYKILLER killerpacket;
		killerpacket.PacketType = HEADER_ZC_NOTIFY_CRAZYKILLER;
		killerpacket.AID = packet.AID;
		killerpacket.isCrazyKiller = pc->CPC::IsCrazyKiller();
		m_pc->CPC::Send(sizeof(killerpacket), (char *)&killerpacket);
	}

	CGuild* g = NULL;
	if( GDID != 0 )
	{
		g = g_ZGuildMgr->CGuildMgr::SearchGuild(GDID);
		if( g == NULL )
			Trace("로딩된 GDID가 없습니다.\n");
	}
	
	if( g == NULL && pc->m_characterInfo.partyID[0] == '\0' )
	{
		PACKET_ZC_ACK_REQNAME outpacket;
		outpacket.PacketType = HEADER_ZC_ACK_REQNAME;
		outpacket.AID = packet.AID;
		memcpy(outpacket.CName, pc->m_characterInfo.characterName, sizeof(outpacket.CName));
		outpacket.CName[23] = 0;
		m_pc->CPC::Send(sizeof(outpacket), (char *)&outpacket);
		return;
	}

	PACKET_ZC_ACK_REQNAMEALL ZCPacket;
	ZCPacket.PacketType = HEADER_ZC_ACK_REQNAMEALL;
	ZCPacket.AID = packet.AID;

	// char name
	memcpy(ZCPacket.CName, pc->m_characterInfo.characterName, sizeof(ZCPacket.CName));

	// guild name
	memset(ZCPacket.GName, 0, sizeof(ZCPacket.GName));
	if( g != NULL && g->GetGuildName()[0] != '\0' )
		memcpy(ZCPacket.GName, g->GetGuildName(), sizeof(ZCPacket.GName));

	// party name
	memset(ZCPacket.PName, 0, sizeof(ZCPacket.PName));
	memcpy(ZCPacket.PName, pc->m_characterInfo.partyID, sizeof(ZCPacket.PName));

	// guild position
	memset(ZCPacket.RName, 0, sizeof(ZCPacket.RName));
	if( g != NULL )
	{
	char* posName = g->CGuild::GetPosName(g->CGuild::GetGuildPosID(GID));
	if( posName != NULL )
		memcpy(ZCPacket.RName, posName, sizeof(ZCPacket.RName));
	}

	m_pc->CPC::Send(sizeof(ZCPacket), (char*)&ZCPacket);
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnWhisper(SERVER, "CPCPacketHandler::OnWhisper");
HOOKED void CPCPacketHandler::OnWhisper(int len)
{
	char packetbuf[256];
	m_recvQueue->PeekData(sizeof(packetbuf), packetbuf);

	char *name, *message;
	int namelen, messagelen;
	if( clif_process_message(m_pc, packetbuf, 1, &name, &namelen, &message, &messagelen) )
	{
		if( AtCommand(m_pc, message) )
		{
			m_recvQueue->RemoveData(len);
			return;
		}

		if( name[0] == '#' )
		{
			clif_parse_globalchat(m_pc, name, message);
			m_recvQueue->RemoveData(len);
			return;
		}
	}

	return (this->*_OnWhisper)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnChangeDir(SERVER, "CPCPacketHandler::OnChangeDir");
void CPCPacketHandler::OnChangeDir(int len)
{
	return (this->*_OnChangeDir)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnDisconnectCharacter(SERVER, "CPCPacketHandler::OnDisconnectCharacter");
void CPCPacketHandler::OnDisconnectCharacter(int len)
{
	return (this->*_OnDisconnectCharacter)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnDisconnectAllCharacter(SERVER, "CPCPacketHandler::OnDisconnectAllCharacter");
void CPCPacketHandler::OnDisconnectAllCharacter(int len)
{
	return (this->*_OnDisconnectAllCharacter)(len);

	PACKET_CZ_DISCONNECT_ALL_CHARACTER packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

	if( m_pc->m_isValid == 0 )
	{
		Trace("AE:DisconnectAllCharacter\n");
		m_pc->AddErrorCount(".\\PCPacketHandler.cpp", 3858, 4, timeGetTime());
		return;
	}

	if( g_zoneScript->CZoneScript::SearchID(m_pc->m_characterInfo.accountName, CHECK_DISCONNECTALLCHAR) == 0 )
		return;

	PACKET_ZI_DISCONNECT_ALL outpacket;
	outpacket.PacketType = HEADER_ZI_DISCONNECT_ALL;
	g_characterMgr->CCharacterMgr::SendToIServer(sizeof(outpacket), (char*)&outpacket);
}


hook_method<void (CPCPacketHandler::*)(int packetSize, char* buf)> CPCPacketHandler::_OnReqAct1(SERVER, "CPCPacketHandler::OnReqAct1");
void CPCPacketHandler::OnReqAct1(int packetSize, char* buf)
{
	return (this->*_OnReqAct1)(packetSize, buf);

	PACKET_CZ_REQUEST_ACT packet;
	bool bFromClient = ( buf == NULL );

	if( !bFromClient )
		memcpy(&packet, buf, sizeof(packet));
	else
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char *)&packet);

	this->CPCPacketHandler::OnReqAct2(packet.targetGID, packet.action, bFromClient);
}


hook_method<void (CPCPacketHandler::*)(const unsigned long in_targetGID, const unsigned char in_action, const bool in_bRequestClient)> CPCPacketHandler::_OnReqAct2(SERVER, "CPCPacketHandler::OnReqAct2");
void CPCPacketHandler::OnReqAct2(const unsigned long in_targetGID, const unsigned char in_action, const bool in_bRequestClient)
{
	return (this->*_OnReqAct2)(in_targetGID, in_action, in_bRequestClient);

	if( !m_pc->m_isValid )
	{
		m_pc->AddErrorCount(__FILE__, __LINE__, 4, timeGetTime());
		return;
	}

	if( m_pc->GetState() == CHARACTER_STATE_DEAD )
		return;

	BOOL result = FALSE;
	BOOL isArrowATK = FALSE;

	PACKET_ZC_NOTIFY_ACT outpacket;
	outpacket.PacketType = HEADER_ZC_NOTIFY_ACT;
	outpacket.GID = m_pc->GetAccountID();
	outpacket.targetGID = in_targetGID;
	outpacket.action = in_action;
	outpacket.leftDamage = 0;

	switch( in_action )
	{
	case ACTION_ATTACK_REPEAT:
	{
		if( in_bRequestClient && m_pc->CPC::GetTargetAID() == in_targetGID )
			return;

		outpacket.action = ACTION_ATTACK;
	}
	// fall through
	case ACTION_ATTACK:
	{
		if( in_action == ACTION_ATTACK_REPEAT )
		{
			m_pc->CPC::SetLockOnMode(TRUE);
			m_pc->CPC::SetTargetAID(in_targetGID);
		}
		else
		{
			m_pc->CPC::CancelLockOnMode();
		}

		m_pc->m_pcClientUpdater.CPCClientUpdater::StopMove();

		CCharacter* target = g_characterMgr->CCharacterMgr::FastFindCharacter(in_targetGID);
		if( target == NULL )
		{
			m_pc->CPC::CancelLockOnMode();
			return;
		}

		int chType = target->GetType();

		if( !target->IsTarget(m_pc, TARGET_TRAP) )
		{
			m_pc->CPC::CancelLockOnMode();
			return;
		}

		if( m_pc->GetEffective(EFST_NOACTION, 0) && m_pc->GetEffective(EFST_AUTOGUARD, 0) )
			return;

		if( target->IsAvoidable(RACETYPE_HUMAN, 0, 0) || !m_pc->CPC::IsAttackable(0) )
		{
			m_pc->CPC::CancelLockOnMode();
			return;
		}

		if( m_pc->GetEffective(EFST_COMBOATTACK, 0)
		 || m_pc->m_pcSkill.m_spellCastingSKID != 0 && m_pc->m_pcSkill.CPCSkill::GetSkillLevel(SKID_SA_FREECAST, 0) == 0
		 || m_pc->GetEffective(EFST_STORMKICK_READY, 0)
		 || m_pc->GetEffective(EFST_DOWNKICK_READY, 0)
		 || m_pc->GetEffective(EFST_TURNKICK_READY, 0)
		 || m_pc->GetEffective(EFST_COUNTER_READY, 0) )
			return;

		 BOOL isRangeAttack = ( m_pc->CPC::GetAttackDistance() >= 4.0 );

		 if( m_pc->m_mapRes == NULL )
			 return;

		int desXPos;
		int desYPos;
		target->GetParameterValue(VAR_CURXPOS, desXPos);
		target->GetParameterValue(VAR_CURYPOS, desYPos);

		if( !m_pc->m_mapRes->CMapRes::IsDirectPath(m_pc->m_pathInfo.m_moveInfo.xPos, m_pc->m_pathInfo.m_moveInfo.yPos, desXPos, desYPos, !isRangeAttack) )
			return;

		if( !m_pc->CPC::IsAttackableRange(desXPos, desYPos) )
		{
			m_pc->CPC::InformAttFailureForDistance(in_targetGID, desXPos, desYPos);

			if( m_pc->CPC::IsLockOnMode() )
				m_pc->CPC::CancelLockOnMode();

			return;
		}

		outpacket.attackMT = m_pc->CPC::GetAttackMotionTime();

		int target_attackedMT;
		target->GetParameterValue(VAR_ATTACKEDMT, target_attackedMT);
		outpacket.attackedMT = target_attackedMT;

		if( (m_pc->GetEffectState() & EFFECTSTATE_HIDING) && !m_pc->GetEffective(EFST_INVISIBILITY, 0) )
			m_pc->ResetEffectState(EFST_HIDING);

		int attackProperty = PROPERTY_NOTHING;

		if( chType == PC_TYPE )
		{
			CPC* targetPC = static_cast<CPC*>(target);

			int reqEffective = EFST_AUTOCOUNTER;
			target->GetParameterValue(VAR_GETEFFECTIVE, reqEffective);
			if( reqEffective == 1 )
			{
				int dir;
				m_pc->GetParameterValue(VAR_CURDIR, dir);

				int enemyDir[3];
				targetPC->GetParameterValue(VAR_CURDIR, enemyDir[0]);
				enemyDir[1] = (enemyDir[0] - 1) % 8;
				enemyDir[2] = (enemyDir[0] + 1) % 8;

				if( dir != enemyDir[0] && dir != enemyDir[1] && dir != enemyDir[2] )
				{
					targetPC->UpdateEffective(EFST_AUTOCOUNTER, 1, 0);
					targetPC->m_packetHandler.CPCPacketHandler::CounterAttack(m_pc->GetAccountID());
					m_pc->CPC::CancelLockOnMode();
					return;
				}

				targetPC->UpdateParameterValue(VAR_RESETEFFECTIVE, EFST_AUTOCOUNTER);
			}

			attackProperty = m_pc->GetWeaponProperty(LOCATION_RARM, FALSE);

			if( targetPC->GetEffective(EFST_POISONREACT, 1) == 1 && attackProperty == PROPERTY_POISON )
			{
				targetPC->UpdateEffective(EFST_POISONREACT, 1, 1);
				targetPC->m_packetHandler.CPCPacketHandler::CounterAttack(m_pc->GetAccountID());
				m_pc->CPC::CancelLockOnMode();
				return;
			}

			if( targetPC->GetEffective(EFST_BLADESTOP, 0) < 0 )
			{
				int skLevel = - targetPC->GetEffective(EFST_BLADESTOP, 0);
				int time = g_skillTypeInfoMgr->CSkillTypeInfoMgr::SendMsg(NULL, SKID_MO_BLADESTOP, SM_GETINFO_SKILL, skLevel, 0, 0, 0);
				targetPC->SetEffective(EFST_BLADESTOP, time, m_pc->GetAccountID(), 0, 0, 0);
				m_pc->SetEffective(EFST_BLADESTOP, time, targetPC->GetAccountID(), 0, 0, 0);
				return;
			}
		}
		else
		if( chType == NPC_MOB_TYPE )
		{
			CNPC* targetNPC = static_cast<CNPC*>(target);

			int reqEffective = EFST_AUTOCOUNTER;
			targetNPC->GetParameterValue(VAR_GETEFFECTIVE, reqEffective);
			if( reqEffective == 1 )
			{
				int dir;
				m_pc->GetParameterValue(VAR_CURDIR, dir);

				int enemyDir[3];
				targetNPC->GetParameterValue(VAR_CURDIR, enemyDir[0]);
				enemyDir[1] = (enemyDir[0] - 1) % 8;
				enemyDir[2] = (enemyDir[0] + 1) % 8;

				if( dir != enemyDir[0] && dir != enemyDir[1] && dir != enemyDir[2] )
				{
					targetNPC->UpdateEffective(EFST_AUTOCOUNTER, 1, 0);
					targetNPC->CNPC::CancelNPCSkill();
					targetNPC->CNPC::SetEnemyAID(m_pc->GetAccountID());
					targetNPC->CNPC::SetCurrentFSMState(7);
					m_pc->CPC::CancelLockOnMode();
					return;
				}

				targetNPC->UpdateParameterValue(VAR_RESETEFFECTIVE, EFST_AUTOCOUNTER);
			}

			int rate = targetNPC->GetEffective(EFST_WEAPONBRAKER, 0);
			if( rate != 0 && !isRangeAttack && GetServerRandom(0, 20000) % 1000 < rate )
				g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_DAMAGE_WEAPON, 0, 0, 0, 0);
		}

		LONG time = timeGetTime();
		outpacket.startTime = time;

		LONG atime;
		m_pc->CPC::GetAttackLastTime(atime);

		if( !m_pc->GetEffective(EFST_AUTOCOUNTER, 0) && m_pc->GetEffective(EFST_POISONREACT, 1) < 2 && time - atime < 2 * outpacket.attackMT ) //TODO: check signedness
			return;

		m_pc->CPC::SetAttackLastTime(time);

		CITP* itp = m_pc->CPC::GetITPEquipedWeapon();
		if( itp != NULL && (itp->GetType() == TYPE_BOW || itp->GetType() == TYPE_GUN) )
		{
			if( !m_pc->m_pcitemInventoryMgr.CPCItemInventoryMgr::GetEquipedArrow() )
			{
				m_pc->CPC::CancelLockOnMode();
				return;
			}

			isArrowATK = TRUE;
		}

		bool isConsumePlusArrow = false;
		int damage = m_pc->m_pcBattle.CPCBattle::GetPhysicalATKDamage(target, isRangeAttack, &outpacket, isConsumePlusArrow);

		int lucky;
		target->GetParameterValue(VAR_ISLUCKY, lucky);
		if( lucky )
		{
			outpacket.damage = 0;
			outpacket.action = ACTION_ATTACK_LUCKY;
			g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_SEND_DAMAGEPACKET, sizeof(outpacket), (int)&outpacket, 0, 0);
			break;
		}

		if( damage > 0 )
		{
			if( m_pc->CPC::GetCategorySecondJob() == JT_HUNTER )
			{
				int skLevel = m_pc->m_pcSkill.CPCSkill::GetSkillLevel(SKID_HT_BLITZBEAT, 0);
				if( skLevel > 0 )
				{
					int jobLevel;
					m_pc->GetParameterValue(VAR_JOBLEVEL, jobLevel);

					int numHits = min((jobLevel - 1)/10, skLevel);

					if( (m_pc->GetEffectState() & EFFECTSTATE_BIRD) && itp != NULL && itp->GetType() == TYPE_BOW )
					{
						if( GetServerRandom(0, 20000) % 1000 < 3 * m_pc->CPC::GetLukValue() )
						{
							m_pc->m_pcSkill.CPCSkill::UpdateSkillType(SKID_HT_BLITZBEAT, 3, numHits);
							g_characterMgr->CCharacterMgr::SendMsg(m_pc, m_pc, CM_USE_SKILL, SKID_HT_BLITZBEAT, target->GetAccountID(), numHits, 0);
						}
					}
				}
			}
		}

		if( !m_pc->CPC::AttackByAutoSpell(target->GetAccountID()) )
			break;

		m_pc->m_pcBattle.CPCBattle::ModifyDamage_ATK(target, damage, isRangeAttack, FALSE, outpacket.action == ACTION_ATTACK_CRITICAL);
		if( damage > 0 )
		{
			int reqEffective = EFST_LEXAETERNA;
			target->GetParameterValue(VAR_GETEFFECTIVE, reqEffective);
			if( reqEffective != 0 )
			{
				damage *= 2;
				target->UpdateParameterValue(VAR_RESETEFFECTIVE, EFST_LEXAETERNA);
			}

			if( chType == PC_TYPE || chType == NPC_MERSOL_TYPE )
			{
				if( target->GetEffective(EFST_KYRIE, 0) > 0 )
				{
					int remain = target->GetEffective(EFST_BARRIER, 0) - damage;

					target->UpdateEffective(EFST_KYRIE, -1, 0);
					target->UpdateEffective(EFST_BARRIER, -damage, 0);

					damage = ( remain >= 0 ) ? 0 : -remain;

					if( target->GetEffective(EFST_KYRIE, 0) == 1 || target->GetEffective(EFST_BARRIER, 0) <= 0 )
					{
						target->ResetEffective(EFST_KYRIE, 0);
						target->ResetEffective(EFST_BARRIER, 0);
					}
				}
			}

			if( chType == PC_TYPE )
			{
				CPC* targetPC = static_cast<CPC*>(target);

				targetPC->CPC::Act_EFST_KAAHI();
				if( targetPC->CPC::Act_EFST_DWARNING(m_pc) == 1 )
					damage = 0;
				if( targetPC->CPC::Act_EFST_KAUPE() == 1 )
					damage = 0;
			}

			if( target->GetEffective(EFST_WALLSHIFT, 0) )
			{
				target->OnShowEffect(462);
				damage = 0;
				target->SetEffective(EFST_WALLSHIFT, 100, 2, 0, 0, 1);
			}
		}

		if( chType == PC_TYPE )
		{
			CPC* targetPC = static_cast<CPC*>(target);

			targetPC->m_pcBattle.CPCBattle::ModifyDamage_ATKED(m_pc, damage, isRangeAttack, 1, 0, 0, 0);

			unsigned long agentAID = targetPC->GetAccountID();
			targetPC->CPC::ModifyDamage(m_pc, damage, isRangeAttack, 1, agentAID, 0, 0);

			if( agentAID != targetPC->GetAccountID() )
			{
				CCharacter* agent = g_characterMgr->CCharacterMgr::FindCharacter(agentAID, UNKNOWN_TYPE);
				if( agent != NULL )
				{
					target = agent;
					chType = agent->GetType();
				}
			}
		}
		else
		if( chType == NPC_MOB_TYPE || chType == NPC_MERSOL_TYPE )
		{
			CNPC* targetNPC = static_cast<CNPC*>(target);

			targetNPC->CNPC::ModifyDamage_ATKED(m_pc, damage, isRangeAttack, 1, 0, 0);
			targetNPC->CNPC::ModifyDamage(damage, isRangeAttack, 1, m_pc, 0);
		}

		if( damage > 0 && outpacket.count == 2 )
		{
			outpacket.damage = 2 * damage;
			outpacket.action = ACTION_ATTACK_MULTIPLE;
		}
		else
		{
			outpacket.damage = damage;
		}

		if( !target->IsDamageMotionPossible() )
			outpacket.action = ( ACTION_ATTACK_MULTIPLE ) ? ACTION_ATTACK_MULTIPLE_NOMOTION : ACTION_ATTACK_NOMOTION;

		if( m_pc->CPC::GetCategorySecondJob() == JT_ASSASSIN )
		{
			if( outpacket.damage > 0 && itp != NULL && itp->GetClass() == WEAPONTYPE_CATARRH )
			{
				int skLevelDouble = m_pc->m_pcSkill.CPCSkill::GetSkillLevel(SKID_TF_DOUBLE, 0);
				outpacket.leftDamage = outpacket.leftDamage * (2 * skLevelDouble + 1) / 100;
			}
			else
			{
				IVItEquipItem* itemLeft = m_pc->m_pcitemInventoryMgr.CPCItemInventoryMgr::GetEquipedItem(LOCATION_LARM);
				if( itemLeft != NULL )
				{
					CITP* itpLeft = g_itpMgr->CITPMgr::GetITP(itemLeft->m_ID);
					if( itpLeft != NULL )
					{
						if( itpLeft->GetType() == TYPE_WEAPON )
						{
							outpacket.leftDamage = m_pc->CPC::GetAttackFinalDamage(target, LOCATION_LARM, 0, 100, 100, 1, 0, 0, 0);

							int skLevelLeft = m_pc->m_pcSkill.CPCSkill::GetSkillLevel(SKID_AS_LEFT, 0);
							if( skLevelLeft > 5 )
								skLevelLeft = 5;

							int leftPlusAttPower = g_skillTypeInfoMgr->CSkillTypeInfoMgr::SendMsg(NULL, SKID_AS_LEFT, SM_GET_PLUSATTPOWER, skLevelLeft, 0, 0, 0);
							outpacket.leftDamage = outpacket.leftDamage * leftPlusAttPower / 100;

							if( outpacket.damage > 0 && itp != NULL )
							{
								int skLevelRight = m_pc->m_pcSkill.CPCSkill::GetSkillLevel(SKID_AS_RIGHT, 0);
								if( skLevelRight > 5 )
									skLevelRight = 5;

								int rightPlusAttPower = g_skillTypeInfoMgr->CSkillTypeInfoMgr::SendMsg(NULL, SKID_AS_RIGHT, SM_GET_PLUSATTPOWER, skLevelRight, 0, 0, 0);
								outpacket.damage = outpacket.damage * rightPlusAttPower / 100;
							}
						}
					}
				}
			}
		}

		if( chType == PC_TYPE )
		{
			if( isRangeAttack )
			{
				if( g_characterMgr->CCharacterMgr::GetSkill(SKID_AL_PNEUMA, desXPos, desYPos, m_pc->m_mapRes) )
				{
					outpacket.damage = 0;
					outpacket.leftDamage = 0;
				}
			}
			else
			{
				CSkill* skillSW = g_characterMgr->CCharacterMgr::GetSkill(SKID_MG_SAFETYWALL, desXPos, desYPos, m_pc->m_mapRes);
				if( skillSW != NULL )
				{
					g_characterMgr->CCharacterMgr::SendMsg(m_pc, skillSW, CM_SKILLOBJ_DECLIFECOUNT, 0, 0, 0, 0);
					outpacket.damage = 0;
					outpacket.leftDamage = 0;
				}
			}
		}
		else
		if( chType == NPC_MOB_TYPE )
		{
			CNPC* targetNPC = static_cast<CNPC*>(target);

			if( isRangeAttack )
			{
				targetNPC->CNPC::SetRangedAttacked(1, m_pc->GetAccountID());
				if( g_characterMgr->CCharacterMgr::GetSkill(SKID_AL_PNEUMA, desXPos, desYPos, m_pc->m_mapRes) )
				{
					outpacket.damage = 0;
					outpacket.leftDamage = 0;
				}
			}
			else
			{
				CSkill* skillSW = g_characterMgr->CCharacterMgr::GetSkill(SKID_MG_SAFETYWALL, desXPos, desYPos, m_pc->m_mapRes);
				if( skillSW != NULL )
				{
					g_characterMgr->CCharacterMgr::SendMsg(m_pc, skillSW, CM_SKILLOBJ_DECLIFECOUNT, 0, 0, 0, 0);
					outpacket.damage = 0;
					outpacket.leftDamage = 0;
				}
			}
		}

		if( outpacket.leftDamage + outpacket.damage > 0 )
		{
			if( chType == NPC_MOB_TYPE )
			{
				CNPC* targetNPC = static_cast<CNPC*>(target);

				if( targetNPC->CNPC::GetCharacterInfo()->def == 100 )
				{
					outpacket.damage = 1;
					outpacket.leftDamage = 0;
				}
				else
				if( targetNPC->CNPC::GetCharacterInfo()->def == 128 )
				{
					m_pc->CPC::KnuckBack(targetNPC, 3, 100, 1);
					outpacket.damage = 1;
					outpacket.leftDamage = 0;
				}

				int npcJob;
				targetNPC->GetParameterValue(VAR_JOB, npcJob);
				if( npcJob == JT_EMPELIUM )
				{
					if( g_ZGuildMgr->CZGuildMgr::GetGuildSkillLevel(m_pc->m_characterInfo.GuildID, SKID_GD_APPROVAL) >= 1 )
					{
						int GDID = 0;
						targetNPC->GetParameterValue(VAR_GDID, GDID);
					}
					else
					{
						outpacket.damage = 0;
						outpacket.leftDamage = 0;
					}
				}
			}

			int damageRate;
			if( m_pc->IsItPossible(MAPPROPERTY_PKSERVER) && chType == PC_TYPE )
			{
				if( isRangeAttack )
					damageRate = 70;
				else
					damageRate = 80;
			}
			else
			{
				if( isRangeAttack )
					damageRate = m_pc->IsItPossible(MAPPROPERTY_RANGE_DAMAGE);
				else
					damageRate = m_pc->IsItPossible(MAPPROPERTY_NORMAL_DAMAGE);
			}

			if( damageRate != 100 )
			{
				if( outpacket.damage > 1 )
				{
					outpacket.damage = outpacket.damage * damageRate / 100;
					if( outpacket.damage < 1 )
						outpacket.damage = 1;
				}

				if( outpacket.leftDamage > 1 )
				{
					outpacket.leftDamage = outpacket.leftDamage * damageRate / 100;
					if( outpacket.leftDamage < 1 )
						outpacket.leftDamage = 1;
				}
			}

			m_pc->CPC::DrainDamage(outpacket.leftDamage + outpacket.damage);

			COMMAND_QUEUE command;
			command.commandID = ATTACKED_IN;

			if( outpacket.count > 1 )
				command.commandID = MULTIPLE_ATTACKED_IN;
			else
			if( chType == NPC_MOB_TYPE )
			{
				CNPC* targetNPC = static_cast<CNPC*>(target);
				int otherAttRange = targetNPC->CNPC::GetAttackRange();
				if( targetNPC->CNPC::GetCurrentFSMState() == 7 && targetNPC->CNPC::GetEnemyAID() != m_pc->GetAccountID() && m_pc->IsMyArea(targetNPC, otherAttRange + 1) )
					command.commandID = MILLI_ATTACKED_IN;
			}

			command.executionTime = timeGetTime() + outpacket.attackMT + 10;
			command.sender = m_pc->m_pcClientUpdater.CPCClientUpdater::GetAccountID();
			command.par1 = outpacket.leftDamage + outpacket.damage;
			command.par2 = outpacket.count;
			command.par3 = 0;
			command.par4 = !isRangeAttack;
			command.par6 = attackProperty;
			target->InsertCommand(&command);

			if( m_pc->m_characterInfo.splashRange != 0 )
			{
				command.commandID = SPLASH_ATTACK_IN;
				command.executionTime = timeGetTime();
				command.sender = m_pc->GetAccountID();
				command.par1 = 0;
				command.par2 = desXPos;
				command.par3 = desYPos;
				command.par4 = target->GetAccountID();
				command.par5 = 1;
				m_pc->InsertCommand(&command);
			}
		}

		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_SEND_DAMAGEPACKET, sizeof(outpacket), (int)&outpacket, 0, 0);

		if( outpacket.damage != 0 )
			m_pc->CPC::SetReadyMotion(0);
	}
	break;
	case ACTION_SIT:
	{
		if( !m_pc->CPC::IsSitable() )
			return;

		int skLevel = m_pc->m_pcSkill.CPCSkill::GetSkillLevel(SKID_NV_BASIC, 0);
		if( !g_skillTypeInfoMgr->CSkillTypeInfoMgr::SendMsg(m_pc, SKID_NV_BASIC, 2, skLevel, 0, 0, 0) )
		{
			m_pc->SkillUseAck(SKID_NV_BASIC, 2, 0, 0);
			return;
		}

		if( m_pc->GetState() != CHARACTER_STATE_MOVE )
		{
			m_pc->CPC::SetState(CHARACTER_STATE_SIT);
			outpacket.startTime = timeGetTime();
			result = TRUE;
		}

		m_pc->CPC::CancelLockOnMode();
	}
	break;
	case ACTION_STAND:
	{
		if( !m_pc->CPC::IsSitable() )
			return;

		int skLevel = m_pc->m_pcSkill.CPCSkill::GetSkillLevel(SKID_NV_BASIC, 0);
		if( !g_skillTypeInfoMgr->CSkillTypeInfoMgr::SendMsg(m_pc, SKID_NV_BASIC, 2, skLevel, 0, 0, 0) )
		{
			m_pc->SkillUseAck(SKID_NV_BASIC, 2, 0, 0);
			return;
		}

		if( m_pc->GetState() != CHARACTER_STATE_MOVE )
		{
			m_pc->CPC::SetState(CHARACTER_STATE_STAND);
			outpacket.startTime = timeGetTime();
			result = TRUE;
		}

		if( m_pc->GetEffective(EFST_TENSIONRELAX, 0) )
			m_pc->ResetEffective(EFST_TENSIONRELAX, 0);
	}
	break;
	default:
	break;
	};

	if( in_action == ACTION_ATTACK_REPEAT || in_action == ACTION_ATTACK )
	{
		if( isArrowATK )
		{
			int arrowITID = m_pc->CPC::ConsumeEquipedArrow(1);
			m_pc->m_pcBattle.CPCBattle::CheckConsumedArrow(arrowITID);
		}
	}

	if( result )
	{
		m_pc->CPC::Send(sizeof(outpacket), (char*)&outpacket);
		m_pc->CCharacter::MultiCast((char*)&outpacket, sizeof(outpacket));
	}
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnMakeGroup(SERVER, "CPCPacketHandler::OnMakeGroup");
void CPCPacketHandler::OnMakeGroup(int len)
{
	return (this->*_OnMakeGroup)(len);

	Trace("PACKET_CZ_MAKE_GROUP\n");

	PACKET_CZ_MAKE_GROUP2 packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

	int skLevel = m_pc->m_pcSkill.CPCSkill::GetSkillLevel(SKID_NV_BASIC, 0);
	if( g_skillTypeInfoMgr->CSkillTypeInfoMgr::SendMsg(m_pc, SKID_NV_BASIC, 4, skLevel, 0, 0, 0) == 0 )
	{
		m_pc->SkillUseAck(SKID_NV_BASIC, 4, false, 0);
	}
	else
	if( m_pc->m_characterInfo.GroupID != 0 )
	{
		PACKET_ZC_ACK_MAKE_GROUP outpacket;
		outpacket.PacketType = HEADER_ZC_ACK_MAKE_GROUP;
		outpacket.result = 2;
		m_pc->CPC::Send(sizeof(outpacket), (char*)&outpacket);
	}
	else
	if( m_pc->IsItPossible(MAPPROPERTY_NO_PARTY_FORMATION) == 1 )
	{
		PACKET_ZC_ACK_MAKE_GROUP outpacket;
		outpacket.PacketType = HEADER_ZC_ACK_MAKE_GROUP;
		outpacket.result = 3;
		m_pc->CPC::Send(sizeof(outpacket), (char*)&outpacket);
	}
	else
	{
		PACKET_ZI_MAKE_GROUP2 outpacket2;
		outpacket2.PacketType = HEADER_ZI_MAKE_GROUP2;
		outpacket2.AID = m_pc->GetAccountID();
		outpacket2.GID = m_pc->m_characterInfo.characterID;
		outpacket2.ItemPickupRule = packet.ItemPickupRule;
		outpacket2.ItemDivisionRule = packet.ItemDivisionRule;
		memcpy(outpacket2.groupName, packet.groupName, sizeof(outpacket2.groupName));
		g_characterMgr->CCharacterMgr::SendToIServer(sizeof(outpacket2), (const char*)&outpacket2);
	}
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnReqJoinGroup(SERVER, "CPCPacketHandler::OnReqJoinGroup");
void CPCPacketHandler::OnReqJoinGroup(int len)
{
	return (this->*_OnReqJoinGroup)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnJoinGroup(SERVER, "CPCPacketHandler::OnJoinGroup");
void CPCPacketHandler::OnJoinGroup(int len)
{
	return (this->*_OnJoinGroup)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnReqExpelGroupMember(SERVER, "CPCPacketHandler::OnReqExpelGroupMember");
void CPCPacketHandler::OnReqExpelGroupMember(int len)
{
	return (this->*_OnReqExpelGroupMember)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnReqNameByGID(SERVER, "CPCPacketHandler::OnReqNameByGID");
void CPCPacketHandler::OnReqNameByGID(int len)
{
	return (this->*_OnReqNameByGID)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnPickUpItem(SERVER, "CPCPacketHandler::OnPickUpItem");
void CPCPacketHandler::OnPickUpItem(int len)
{
	return (this->*_OnPickUpItem)(len);

	PACKET_CZ_ITEM_PICKUP packet;
	m_recvQueue->GetData(sizeof(packet), (char *)&packet);
	if ( !m_pc->m_isValid )
	{
		m_pc->AddErrorCount(".\\PCPacketHandler.cpp", 5556, 4, timeGetTime());
		return;
	}

	m_pc->CancelLockOnMode();

	Request request;
	request.Request::SetID(RT_REQ_PICKUPITEM);
	request.par1 = packet.ITAID;
	m_pc->OnDispatchClientRequest(&request);
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnThrowItem(SERVER, "CPCPacketHandler::OnThrowItem");
void CPCPacketHandler::OnThrowItem(int len)
{
	return (this->*_OnThrowItem)(len);

	//TODO
}


/// Parses out item use request packet and delegates to OnUseItem2().
hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnUseItem(SERVER, "CPCPacketHandler::OnUseItem");
void CPCPacketHandler::OnUseItem(int len)
{
	return (this->*_OnUseItem)(len);

	if( !m_pc->m_isValid )
	{
		m_pc->AddErrorCount(".\\PCPacketHandler.cpp", 5627, 4, timeGetTime());
		return;
	}

	PACKET_CZ_USE_ITEM packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char *)&packet);
	this->CPCPacketHandler::OnUseItem2(packet.index, packet.AID);
}


hook_method<void (CPCPacketHandler::*)(const unsigned short in_index, const unsigned long in_AID)> CPCPacketHandler::_OnUseItem2(SERVER, "CPCPacketHandler::OnUseItem2");
void CPCPacketHandler::OnUseItem2(const unsigned short in_index, const unsigned long in_AID)
{
	return (this->*_OnUseItem2)(in_index, in_AID);

	if( !this->m_pc->m_isValid )
	{
		m_pc->AddErrorCount(".\\PCPacketHandler.cpp", 5592, 4, timeGetTime());
		return;
	}

	if( m_pc->GetEffective(EFST_BERSERK, 0) > 0 )
	{
		Trace("use item fail EFST_BERSERK\n");
		return;
	}

	if( m_pc->GetEffective(EFST_CRYSTAL, 0)
	||  m_pc->GetEffective(EFST_DA_EDARKNESS, 0) )
	{
		Trace("use item fail EFST_CRYSTAL || EFST_DA_EDARKNESS\n");
		return;
	}

	Request request;
	request.par2 = in_AID;
	request.Request::SetID(RT_REQ_USEITEM);
	request.par1 = in_index;
	m_pc->CPC::OnDispatchClientRequest(&request);

	if( m_pc->GetEffective(EFST_TENSIONRELAX, 0) )
		m_pc->ResetEffective(EFST_TENSIONRELAX, 0);
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnWearEquip(SERVER, "CPCPacketHandler::OnWearEquip");
void CPCPacketHandler::OnWearEquip(int len)
{
	return (this->*_OnWearEquip)(len);

	PACKET_CZ_REQ_WEAR_EQUIP packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char *)&packet);

	if( !m_pc->m_isValid )
	{
		m_pc->AddErrorCount(".\\PCPacketHandler.cpp", 5685, 4, timeGetTime());
		return;
	}

	if( m_pc->GetState() == CHARACTER_STATE_DEAD )
		return;

	if( !m_pc->CPC::IsItemMovable() )
	{
		Trace("OnWearEquip Impossible\n");
		return;
	}

	Request request;
	request.Request::SetID(RT_REQ_WEAREQUIP);
	request.par1 = packet.index;
	request.par2 = ( packet.wearLocation ) ? packet.wearLocation : 32768;

	m_pc->CPC::OnDispatchClientRequest(&request);
	m_pc->CPC::CheckWeaponState();
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnTakeOffEquip(SERVER, "CPCPacketHandler::OnTakeOffEquip");
void CPCPacketHandler::OnTakeOffEquip(int len)
{
	return (this->*_OnTakeOffEquip)(len);

	PACKET_CZ_REQ_TAKEOFF_EQUIP packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char *)&packet);

	if( !m_pc->m_isValid )
	{
		m_pc->AddErrorCount(".\\PCPacketHandler.cpp", 5718, 4, timeGetTime());
		return;
	}

	if( m_pc->GetState() == CHARACTER_STATE_DEAD )
		return;

	if( !m_pc->CPC::IsItemMovable() )
	{
		Trace("OnTakeOffEqup Impossible\n");
		return;
	}

	Request request;
	request.Request::SetID(RT_REQ_TAKEOFFEQUIP);
	request.par1 = packet.index;

	m_pc->CPC::OnDispatchClientRequest(&request);
	m_pc->CPC::CheckWeaponState();
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnPurchaseItem(SERVER, "CPCPacketHandler::OnPurchaseItem");
void CPCPacketHandler::OnPurchaseItem(int len)
{
	return (this->*_OnPurchaseItem)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnSellItem(SERVER, "CPCPacketHandler::OnSellItem");
void CPCPacketHandler::OnSellItem(int len)
{
	return (this->*_OnSellItem)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnItemExplanationByName(SERVER, "CPCPacketHandler::OnItemExplanationByName");
void CPCPacketHandler::OnItemExplanationByName(int len)
{
	return (this->*_OnItemExplanationByName)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnChooseMenu(SERVER, "CPCPacketHandler::OnChooseMenu");
void CPCPacketHandler::OnChooseMenu(int len)
{
	return (this->*_OnChooseMenu)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnReqNextScript(SERVER, "CPCPacketHandler::OnReqNextScript");
void CPCPacketHandler::OnReqNextScript(int len)
{
	return (this->*_OnReqNextScript)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnRestart(SERVER, "CPCPacketHandler::OnRestart");
void CPCPacketHandler::OnRestart(int len)
{
	return (this->*_OnRestart)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(void)> CPCPacketHandler::_OnRestart_QUIT_RESTART(SERVER, "CPCPacketHandler::OnRestart_QUIT_RESTART");
void CPCPacketHandler::OnRestart_QUIT_RESTART(void)
{
	return (this->*_OnRestart_QUIT_RESTART)();

	//TODO
}


hook_method<void (CPCPacketHandler::*)(void)> CPCPacketHandler::_OnRestart_QUIT_EXIT(SERVER, "CPCPacketHandler::OnRestart_QUIT_EXIT");
void CPCPacketHandler::OnRestart_QUIT_EXIT(void)
{
	return (this->*_OnRestart_QUIT_EXIT)();

	if( !m_pc->CPC::IsDisconnectable() )
	{
		PACKET_ZC_ACK_REQ_DISCONNECT outpacket;
		outpacket.PacketType = HEADER_ZC_ACK_REQ_DISCONNECT;
		outpacket.result = 1;
		m_pc->CPC::Send(sizeof(PACKET_ZC_ACK_REQ_DISCONNECT), (char *)&outpacket);
		return;
	}

	if( m_pc->GetEffective(EFST_NOACTION_WAIT,0) )
		return;

	PACKET_ZC_NOTIFY_VANISH broadcast;
	broadcast.PacketType = HEADER_ZC_NOTIFY_VANISH;
	broadcast.GID = m_pc->m_pcClientUpdater.CPCClientUpdater::GetAccountID();
	broadcast.type = 2;
	m_pc->CCharacter::MultiCast((char *)&broadcast, sizeof(PACKET_ZC_NOTIFY_VANISH));

	m_pc->m_pcClientUpdater.CPCClientUpdater::RemoveSectionMgr();

	if( m_pc->GetState() == CHARACTER_STATE_DEAD && !m_pc->GetEffective(EFST_TRICKDEAD,0) )
	{
		strncpy(m_pc->m_characterInfo.mapName, m_pc->CPC::GetRestartMapName(), sizeof(m_pc->m_characterInfo.mapName));
		m_pc->m_pathInfo.m_moveInfo.xPos = m_pc->m_characterInfo.sxPos;
		m_pc->m_pathInfo.m_moveInfo.yPos = m_pc->m_characterInfo.syPos;
	}

	m_pc->CPC::DisableAllCommand();
	m_pc->CPC::CancelExchangeItem();

	if( m_pc->GetEffective(EFST_BERSERK,0) > 0 )
		m_pc->m_characterInfo.hp = 100;

	if( !this->CPCPacketHandler::OnRestart_QUIT_EXIT_Part1() )
		m_pc->AddErrorCount(".\\PCPacketHandler.cpp", 5898, 4, timeGetTime());
}


hook_method<bool (CPCPacketHandler::*)(void)> CPCPacketHandler::_OnRestart_QUIT_EXIT_Part1(SERVER, "CPCPacketHandler::OnRestart_QUIT_EXIT_Part1");
bool CPCPacketHandler::OnRestart_QUIT_EXIT_Part1(void)
{
	return (this->*_OnRestart_QUIT_EXIT_Part1)();

	//TODO
}


hook_method<void (CPCPacketHandler::*)(void)> CPCPacketHandler::_OnRestart_QUIT_EXIT_Part2(SERVER, "CPCPacketHandler::OnRestart_QUIT_EXIT_Part2");
void CPCPacketHandler::OnRestart_QUIT_EXIT_Part2(void)
{
	return (this->*_OnRestart_QUIT_EXIT_Part2)();

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnStatusChange(SERVER, "CPCPacketHandler::OnStatusChange");
void CPCPacketHandler::OnStatusChange(int len)
{
	return (this->*_OnStatusChange)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnReqEmotion(SERVER, "CPCPacketHandler::OnReqEmotion");
void CPCPacketHandler::OnReqEmotion(int len)
{
	return (this->*_OnReqEmotion)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnReqUserCount(SERVER, "CPCPacketHandler::OnReqUserCount");
void CPCPacketHandler::OnReqUserCount(int len)
{
	return (this->*_OnReqUserCount)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnSelectDealType(SERVER, "CPCPacketHandler::OnSelectDealType");
void CPCPacketHandler::OnSelectDealType(int len)
{
	return (this->*_OnSelectDealType)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnSettingWhisperPC(SERVER, "CPCPacketHandler::OnSettingWhisperPC");
void CPCPacketHandler::OnSettingWhisperPC(int len)
{
	return (this->*_OnSettingWhisperPC)(len);

	PACKET_CZ_SETTING_WHISPER_PC packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char *)&packet);

	PACKET_ZC_SETTING_WHISPER_PC outpacket;
	outpacket.PacketType = HEADER_ZC_SETTING_WHISPER_PC;
	if( packet.type != 0 )
	{
		outpacket.type = 1;
		outpacket.result = ( m_pc->CPC::DeleteExWhisperList(packet.name) == 0 );
	}
	else
	{
		outpacket.type = 0;
		outpacket.result = ( m_pc->CPC::AddExWhisperList(packet.name) != 0 ? 0 : 2 );
	}
	m_pc->CPC::Send(sizeof(outpacket), (char *)&outpacket);
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnSettingWhisperState(SERVER, "CPCPacketHandler::OnSettingWhisperState");
void CPCPacketHandler::OnSettingWhisperState(int len)
{
	return (this->*_OnSettingWhisperState)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len2)> CPCPacketHandler::_OnReqWhisperList(SERVER, "CPCPacketHandler::OnReqWhisperList");
void CPCPacketHandler::OnReqWhisperList(int len2)
{
	return (this->*_OnReqWhisperList)(len2);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnCreateChatRoom(SERVER, "CPCPacketHandler::OnCreateChatRoom");
void CPCPacketHandler::OnCreateChatRoom(int len)
{
	return (this->*_OnCreateChatRoom)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnReqEnterRoom(SERVER, "CPCPacketHandler::OnReqEnterRoom");
void CPCPacketHandler::OnReqEnterRoom(int len)
{
	return (this->*_OnReqEnterRoom)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnChangeChatRoom(SERVER, "CPCPacketHandler::OnChangeChatRoom");
void CPCPacketHandler::OnChangeChatRoom(int len)
{
	return (this->*_OnChangeChatRoom)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnReqChangeRole(SERVER, "CPCPacketHandler::OnReqChangeRole");
void CPCPacketHandler::OnReqChangeRole(int len)
{
	return (this->*_OnReqChangeRole)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnReqExpelMember(SERVER, "CPCPacketHandler::OnReqExpelMember");
void CPCPacketHandler::OnReqExpelMember(int len)
{
	return (this->*_OnReqExpelMember)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnExitRoom(SERVER, "CPCPacketHandler::OnExitRoom");
void CPCPacketHandler::OnExitRoom(int len)
{
	return (this->*_OnExitRoom)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnReqExchangeItem(SERVER, "CPCPacketHandler::OnReqExchangeItem");
void CPCPacketHandler::OnReqExchangeItem(int len) // line 6986-7008
{
	return (this->*_OnReqExchangeItem)(len);

	PACKET_CZ_REQ_EXCHANGE_ITEM packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

	if( g_zoneScript->CZoneScript::SearchID(m_pc->m_characterInfo.accountName, CHECK_ITEM_RESTRICT) != 1 )
		m_pc->CPC::ReqExchangeItem(packet.AID);
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnAckReqExchangeItem(SERVER, "CPCPacketHandler::OnAckReqExchangeItem");
void CPCPacketHandler::OnAckReqExchangeItem(int len)
{
	return (this->*_OnAckReqExchangeItem)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnExecExchangeItem(SERVER, "CPCPacketHandler::OnExecExchangeItem");
void CPCPacketHandler::OnExecExchangeItem(int len)
{
	return (this->*_OnExecExchangeItem)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnAddExchangeItem(SERVER, "CPCPacketHandler::OnAddExchangeItem");
void CPCPacketHandler::OnAddExchangeItem(int len)
{
	return (this->*_OnAddExchangeItem)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnConcludeExchangeItem(SERVER, "CPCPacketHandler::OnConcludeExchangeItem");
void CPCPacketHandler::OnConcludeExchangeItem(int len)
{
	return (this->*_OnConcludeExchangeItem)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnCancelExchangeItem(SERVER, "CPCPacketHandler::OnCancelExchangeItem");
void CPCPacketHandler::OnCancelExchangeItem(int len)
{
	return (this->*_OnCancelExchangeItem)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnCancelLockOn(SERVER, "CPCPacketHandler::OnCancelLockOn");
void CPCPacketHandler::OnCancelLockOn(int len)
{
	return (this->*_OnCancelLockOn)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnMoveItemFromBodyToStore(SERVER, "CPCPacketHandler::OnMoveItemFromBodyToStore");
void CPCPacketHandler::OnMoveItemFromBodyToStore(int len)
{
	return (this->*_OnMoveItemFromBodyToStore)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnMoveItemFromStoreToBody(SERVER, "CPCPacketHandler::OnMoveItemFromStoreToBody");
void CPCPacketHandler::OnMoveItemFromStoreToBody(int len)
{
	return (this->*_OnMoveItemFromStoreToBody)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnMoveItemFromBodyToCart(SERVER, "CPCPacketHandler::OnMoveItemFromBodyToCart");
void CPCPacketHandler::OnMoveItemFromBodyToCart(int len)
{
	return (this->*_OnMoveItemFromBodyToCart)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnMoveItemFromCartToBody(SERVER, "CPCPacketHandler::OnMoveItemFromCartToBody");
void CPCPacketHandler::OnMoveItemFromCartToBody(int len)
{
	return (this->*_OnMoveItemFromCartToBody)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnMoveItemFromStoreToCart(SERVER, "CPCPacketHandler::OnMoveItemFromStoreToCart");
void CPCPacketHandler::OnMoveItemFromStoreToCart(int len)
{
	return (this->*_OnMoveItemFromStoreToCart)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnMoveItemFromCartToStore(SERVER, "CPCPacketHandler::OnMoveItemFromCartToStore");
void CPCPacketHandler::OnMoveItemFromCartToStore(int len)
{
	return (this->*_OnMoveItemFromCartToStore)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnCloseStore(SERVER, "CPCPacketHandler::OnCloseStore");
void CPCPacketHandler::OnCloseStore(int len)
{
	return (this->*_OnCloseStore)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnChatParty(SERVER, "CPCPacketHandler::OnChatParty");
HOOKED void CPCPacketHandler::OnChatParty(int len) // lines 3168-3200
{
	char packetbuf[256];
	m_recvQueue->PeekData(sizeof(packetbuf), packetbuf);

	char *name, *message;
	int namelen, messagelen;
	if( clif_process_message(m_pc, packetbuf, 0, &name, &namelen, &message, &messagelen) )
	{
		if( AtCommand(m_pc, message) )
		{
			m_recvQueue->RemoveData(len);
			return;
		}
	}

	return (this->*_OnChatParty)(len);

	if ( len > 220 || (unsigned int)len <= 4 )
	{
		m_pc->AddErrorCount(".\\PCPacketHandler.cpp", 3170, 4, timeGetTime());
		return; // invalid packet length
	}

	PACKET_CZ_REQUEST_CHAT_PARTY packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char *)&packet);
	int textlen = len - sizeof(packet);
	char buf[512];
	m_recvQueue->CPacketQueue::GetData(textlen, buf);

	if( m_pc != NULL && m_pc->IsItPossible(MAPPROPERTY_NO_CHATTING) != 0 )
	{
		m_pc->CPC::SendZCMsg(MSI_NO_CHATTING);
		return; // can't chat in this map
	}

	if ( m_pc->CPC::IsBadGuy() != 0 )
		return; // player can't chat in the current state

	PACKET_ZI_CHAT_PARTY outpacket;
	outpacket.PacketType = HEADER_ZI_CHAT_PARTY;
	outpacket.PacketLength = sizeof(outpacket) + textlen;
	outpacket.AID = m_pc->GetAccountID();
	outpacket.GRID = m_pc->m_characterInfo.GroupID;
	g_characterMgr->CCharacterMgr::SendToIServer(sizeof(outpacket), (const char *)&outpacket);
	g_characterMgr->CCharacterMgr::SendToIServer(textlen, buf);
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnUpgradeSkillLevel(SERVER, "CPCPacketHandler::OnUpgradeSkillLevel");
void CPCPacketHandler::OnUpgradeSkillLevel(int len)
{
	return (this->*_OnUpgradeSkillLevel)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(const unsigned short in_SKID, const short in_selectedLevel, unsigned long in_targetID)> CPCPacketHandler::_OnUseSkill(SERVER, "CPCPacketHandler::OnUseSkill");
void CPCPacketHandler::OnUseSkill(const unsigned short in_SKID, const short in_selectedLevel, unsigned long in_targetID)
{
	return (this->*_OnUseSkill)(in_SKID, in_selectedLevel, in_targetID);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(const unsigned short in_SKID, const short in_selectedLevel, const unsigned long in_targetID)> CPCPacketHandler::_OnUseGuildSkill(SERVER, "CPCPacketHandler::OnUseGuildSkill");
void CPCPacketHandler::OnUseGuildSkill(const unsigned short in_SKID, const short in_selectedLevel, const unsigned long in_targetID)
{
	return (this->*_OnUseGuildSkill)(in_SKID, in_selectedLevel, in_targetID);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(const unsigned short in_SKID, const short in_selectedLevel, const unsigned long in_targetID)> CPCPacketHandler::_OnUseSkill_Merce(SERVER, "CPCPacketHandler::OnUseSkill_Merce");
void CPCPacketHandler::OnUseSkill_Merce(const unsigned short in_SKID, const short in_selectedLevel, const unsigned long in_targetID)
{
	return (this->*_OnUseSkill_Merce)(in_SKID, in_selectedLevel, in_targetID);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(const PACKET_CZ_USE_SKILL_TOGROUND& packet)> CPCPacketHandler::_OnUseSkillToGround(SERVER, "CPCPacketHandler::OnUseSkillToGround");
void CPCPacketHandler::OnUseSkillToGround(const PACKET_CZ_USE_SKILL_TOGROUND& packet) // line 8363
{
	return (this->*_OnUseSkillToGround)(packet);

	if( m_pc->GetEffective(EFST_NOACTION_WAIT,0) )
		return;

	int SKType = m_pc->m_pcSkill.CPCSkill::GetSkillType(packet.SKID);
	switch( SKType )
	{
	case 0:
	case 1:
	case 4:
		if( !m_pc->CPC::IsSkillUsable(packet.SKID) )
			return;
	break;
	case 2:
		if( m_pc->m_pcSkill.m_spellCastingSKID != 0 && packet.SKID != SKID_SA_CASTCANCEL )
		{
			Trace("Can not use skill on casting sate!!\n");
			return;
		}
	break;
	default:
	break;
	}

	m_pc->CPC::CancelLockOnMode();

	short skLevel = m_pc->m_pcSkill.CPCSkill::GetSkillLevel(packet.SKID, 0);
	if( skLevel <= 0 )
		return;

	if( packet.selectedLevel > 0 && packet.selectedLevel < skLevel )
		skLevel = packet.selectedLevel;

	CSkillTypeInfo* skilltypeInfo = g_skillTypeInfoMgr->CSkillTypeInfoMgr::SearchSkillTypeInfo(packet.SKID);
	if( skilltypeInfo == NULL || m_pc->m_mapRes == NULL )
		return;

	if( !m_pc->m_mapRes->CMapRes::IsDirectPath(m_pc->m_pathInfo.m_moveInfo.dxPos, m_pc->m_pathInfo.m_moveInfo.dyPos, packet.xPos, packet.yPos, 0) )
	{
		m_pc->SkillUseAck(packet.SKID, 0, false, 10);
		return;
	}

	if( !m_pc->CPC::IsSkillEnable(packet.SKID, skLevel, 0) )
		return;

	if( m_pc->GetEffective(EFST_RUN, 0) )
		m_pc->ResetEffective(EFST_RUN, 0);

	int range = g_skillTypeInfoMgr->CSkillTypeInfoMgr::GetAttackRange(packet.SKID, packet.selectedLevel) + m_pc->CPC::GetPlusAttRange() + 1;
	if( range > 14 )
		range = 14;

	int dx = m_pc->m_pathInfo.m_moveInfo.xPos - packet.xPos;
	int dy = m_pc->m_pathInfo.m_moveInfo.yPos - packet.yPos;
	if( packet.SKID == SKID_AC_SHOWER )
	{// square distance check
		if( abs(dx) > range || abs(dy) > range )
			return;
	}
	else
	{// circular distance check
		if( range + 1 < sqrt((double)(dx * dx + dy * dy)) )
			return;
	}

	m_pc->m_pcClientUpdater.CPCClientUpdater::StopMove();

	LONG atime;
	m_pc->CPC::GetAttackLastTime(atime);
	int now = timeGetTime();
	if( now - atime < m_pc->CPC::GetAttackMotionTime() + g_AMTterm )
		return;
	m_pc->CPC::SetAttackLastTime(now);

	int spCost = skilltypeInfo->GetSPCost(skLevel);
	if( SKType != 2 && SKType != 3 )
	{
		if( m_pc->m_characterInfo.reducePercentSP != 0 )
		{
			spCost -= spCost * m_pc->m_characterInfo.reducePercentSP / 100;
			if( spCost < 1 )
				spCost = 1;
		}

		if( m_pc->CPC::GetSP() < spCost )
		{
			m_pc->SkillUseAck(packet.SKID, 0, false, 1);
			return;
		}
	}

	if( m_pc->GetEffectState() & 4 )
		m_pc->ResetEffectState(4);

	COMMAND_QUEUE command;
	command.par1 = 46;
	command.par2 = timeGetTime();
	command.par3 = m_pc->GetAccountID();
	command.par4 = packet.SKID;
	command.par5 = packet.xPos;
	command.par6 = packet.yPos;
	command.par7 = skLevel;

	int delay = m_pc->m_pcBattle.CPCBattle::GetSKCastingTM(skilltypeInfo, skLevel, 0, packet.xPos, packet.yPos, 0);
	if( delay > 0 )
	{
		PACKET_ZC_USESKILL_ACK outpacket;
		outpacket.PacketType = HEADER_ZC_USESKILL_ACK;
		outpacket.SKID = packet.SKID;
		outpacket.yPos = packet.yPos;
		outpacket.delayTime = delay;
		outpacket.targetID = 0;
		outpacket.xPos = packet.xPos;
		outpacket.AID = m_pc->GetAccountID();
		m_pc->CPC::Send(sizeof(outpacket), (char*)&outpacket);
		m_pc->CCharacter::MultiCast((char*)&outpacket, sizeof(outpacket));

		command.par2 += delay;
		command.executionTime = skilltypeInfo->GetProperty(); //NOTE:misuse?
		m_pc->CPC::SetSpellCasting(packet.SKID, skLevel);
	}

	m_pc->InsertCommand(&command);

	int flag = m_pc->GetEffective(EFST_MAGICPOWER, 0);
	if( flag != 0 )
	{
		if( flag & 0xFFFFFF00 )
			m_pc->ResetEffective(EFST_MAGICPOWER, 0);
		else
		if( skilltypeInfo->CSkillTypeInfo::GetPattern() == 2 )
			m_pc->UpdateEffective(EFST_MAGICPOWER, 256, 0);
	}

	m_pc->m_lastTargetAID = 0;
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnSelectWarpPoint(SERVER, "CPCPacketHandler::OnSelectWarpPoint");
void CPCPacketHandler::OnSelectWarpPoint(int len)
{
	return (this->*_OnSelectWarpPoint)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnRememberWarpPoint(SERVER, "CPCPacketHandler::OnRememberWarpPoint");
void CPCPacketHandler::OnRememberWarpPoint(int len)
{
	return (this->*_OnRememberWarpPoint)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnCartOff(SERVER, "CPCPacketHandler::OnCartOff");
void CPCPacketHandler::OnCartOff(int len)
{
	return (this->*_OnCartOff)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnReqCloseMCStore(SERVER, "CPCPacketHandler::OnReqCloseMCStore");
HOOKED void CPCPacketHandler::OnReqCloseMCStore(int len)
{
	if( !m_pc->m_pcitemInventoryMgr.IsMCStoreOpen() )
	{
		m_recvQueue->CPacketQueue::RemoveData(sizeof(PACKET_CZ_REQ_CLOSESTORE));
		return;
	}

	return (this->*_OnReqCloseMCStore)(len);

	PACKET_CZ_REQ_CLOSESTORE packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char *)&packet);

	PACKET_ZC_DISAPPEAR_ENTRY outpacket;
	outpacket.PacketType = HEADER_ZC_DISAPPEAR_ENTRY;
	outpacket.makerAID = m_pc->GetAccountID();
	m_pc->CCharacter::MultiCast((char *)&outpacket, sizeof(outpacket));

	m_pc->CPC::CancelMCStore();
	--m_pc->m_lockCounter;
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnReqOpenMCStore(SERVER, "CPCPacketHandler::OnReqOpenMCStore");
void CPCPacketHandler::OnReqOpenMCStore(int len)
{
	return (this->*_OnReqOpenMCStore)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnReqOpenMCStore2(SERVER, "CPCPacketHandler::OnReqOpenMCStore2");
void CPCPacketHandler::OnReqOpenMCStore2(int len)
{
	return (this->*_OnReqOpenMCStore2)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_PurchaseItemFromMCStore(SERVER, "CPCPacketHandler::PurchaseItemFromMCStore");
void CPCPacketHandler::PurchaseItemFromMCStore(int len)
{
	return (this->*_PurchaseItemFromMCStore)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnReqItemListFromMCStore(SERVER, "CPCPacketHandler::OnReqItemListFromMCStore");
void CPCPacketHandler::OnReqItemListFromMCStore(int len)
{
	return (this->*_OnReqItemListFromMCStore)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnPKModeChange(SERVER, "CPCPacketHandler::OnPKModeChange");
void CPCPacketHandler::OnPKModeChange(int len)
{
	return (this->*_OnPKModeChange)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnItemCreate(SERVER, "CPCPacketHandler::OnItemCreate");
void CPCPacketHandler::OnItemCreate(int len)
{
	return (this->*_OnItemCreate)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnAdminMapMove(SERVER, "CPCPacketHandler::OnAdminMapMove");
void CPCPacketHandler::OnAdminMapMove(int len)
{
	return (this->*_OnAdminMapMove)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnChangeGroupExpOption(SERVER, "CPCPacketHandler::OnChangeGroupExpOption");
void CPCPacketHandler::OnChangeGroupExpOption(int len)
{
	return (this->*_OnChangeGroupExpOption)(len);

	PACKET_CZ_CHANGE_GROUPEXPOPTION packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char *)&packet);

	if( !m_pc->CPC::IsFamilySharePossible() )
	{
		PACKET_ZI_CHANGE_EXPOPTION outpacket;
		outpacket.PacketType = HEADER_ZI_CHANGE_EXPOPTION;
		outpacket.GRID = m_pc->m_characterInfo.GroupID;
		outpacket.AID = m_pc->GetAccountID();
		outpacket.expOption = packet.expOption;
		g_characterMgr->CCharacterMgr::SendToIServer(sizeof(outpacket), (const char *)&outpacket);
	}
	else
	{
		PACKET_ZI_CHANGE_EXPOPTION2 outpacket2;
		outpacket2.PacketType = HEADER_ZI_CHANGE_EXPOPTION2;
		outpacket2.GRID = m_pc->m_characterInfo.GroupID;
		outpacket2.AID = m_pc->GetAccountID();
		outpacket2.expOption = packet.expOption;
		g_characterMgr->CCharacterMgr::SendToIServer(sizeof(outpacket2), (const char *)&outpacket2);

		for( mystd::list<unsigned long>::const_iterator it = m_pc->m_groupMember.begin(); it != m_pc->m_groupMember.end(); ++it )
		{
			unsigned long AID = *it;
			CPC* pc = (CPC *)g_characterMgr->CCharacterMgr::FindCharacter(AID, UNKNOWN_TYPE);
			if( pc )
				pc->m_familyInfo.expOption = 1;
		}
	}
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnInputEditDlg(SERVER, "CPCPacketHandler::OnInputEditDlg");
void CPCPacketHandler::OnInputEditDlg(int len)
{
	return (this->*_OnInputEditDlg)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnCloseDialog(SERVER, "CPCPacketHandler::OnCloseDialog");
void CPCPacketHandler::OnCloseDialog(int len)
{
	return (this->*_OnCloseDialog)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnReqItemIdentify(SERVER, "CPCPacketHandler::OnReqItemIdentify");
void CPCPacketHandler::OnReqItemIdentify(int len)
{
	return (this->*_OnReqItemIdentify)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnReqItemCompositionList(SERVER, "CPCPacketHandler::OnReqItemCompositionList");
void CPCPacketHandler::OnReqItemCompositionList(int len)
{
	return (this->*_OnReqItemCompositionList)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnReqItemComposition(SERVER, "CPCPacketHandler::OnReqItemComposition");
void CPCPacketHandler::OnReqItemComposition(int len)
{
	return (this->*_OnReqItemComposition)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnReqDisconnect(SERVER, "CPCPacketHandler::OnReqDisconnect");
void CPCPacketHandler::OnReqDisconnect(int len)
{
	return (this->*_OnReqDisconnect)(len);

	PACKET_CZ_REQ_DISCONNECT Packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char *)&Packet);

	PACKET_ZC_ACK_REQ_DISCONNECT outpacket;
	outpacket.PacketType = HEADER_ZC_ACK_REQ_DISCONNECT;
	if( m_pc->CPC::IsDisconnectable() )
	{
		outpacket.result = 0;
		m_pc->CPC::DisableAllCommand();
		Trace("Disconnect OK Message\n");
	}
	else
	{
		outpacket.result = 1;
		Trace("DISCONNEDT impossible MESSANGE\n");
	}
	m_pc->CPC::Send(4, (char *)&outpacket);
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnSelectAutoSpell(SERVER, "CPCPacketHandler::OnSelectAutoSpell");
void CPCPacketHandler::OnSelectAutoSpell(int len)
{
	return (this->*_OnSelectAutoSpell)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnReqGuildMenuInterface(SERVER, "CPCPacketHandler::OnReqGuildMenuInterface");
void CPCPacketHandler::OnReqGuildMenuInterface(int len)
{
	return (this->*_OnReqGuildMenuInterface)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnReqGuildMenu(SERVER, "CPCPacketHandler::OnReqGuildMenu");
void CPCPacketHandler::OnReqGuildMenu(int len)
{
	return (this->*_OnReqGuildMenu)(len);

	PACKET_CZ_REQ_GUILD_MENU packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char *)&packet);

	switch( packet.Type )
	{
	case 0:
	{
		if( timeGetTime() - m_ReqGuildMenuTime[0] < 10000 )
			break;

		m_ReqGuildMenuTime[0] = timeGetTime();

		int GDID = 0;
		m_pc->GetParameterValue(VAR_GDID, GDID);

		if( GDID == 0 )
			break;

		CGuild* g = g_ZGuildMgr->CGuildMgr::SearchGuild(GDID);
		if( g == NULL )
		{
			Trace("로딩된 GDID가 없습니다.\n");
			break;
		}

		PACKET_ZC_GUILD_INFO2 ZCPacket;
		ZCPacket.PacketType = HEADER_ZC_GUILD_INFO2;
		ZCPacket.exp = g->CGuild::GetExp();
		ZCPacket.GDID = g->CGuild::GetGDID();
		memcpy(ZCPacket.guildname, g->CGuild::GetGuildName(), sizeof(ZCPacket.guildname));
		memcpy(ZCPacket.masterName, g->CGuild::GetMasterName(), sizeof(ZCPacket.masterName));
		ZCPacket.honor = g->CGuild::GetHonor();
		ZCPacket.level = g->CGuild::GetLevel();
		memcpy(ZCPacket.manageLand, g->CGuild::GetManageLand(), sizeof(ZCPacket.manageLand));
		ZCPacket.maxExp = g_expParameter->CExpParameter::GetGuildNextExp(g->CGuild::GetLevel());
		ZCPacket.maxUserNum = g->CGuild::GetMaxUserNum();
		ZCPacket.point = g->CGuild::GetPoint();
		ZCPacket.userAverageLevel = g->CGuild::GetAverageLevel();
		ZCPacket.userNum = g->CGuild::GetGuildMemberOnline();
		ZCPacket.virtue = g->CGuild::GetVirtue();
		ZCPacket.emblemVersion = g->CGuild::GetEmblemVersion();
		ZCPacket.zeny = g->CGuild::GetMoney();

		unsigned long AID = m_pc->GetAccountID();
		if( AID == 0 )
			break;

		g_characterMgr->CCharacterMgr::SendMsg(0, AID, 25, 114, (int)&ZCPacket, 0, 0);

		int size = g->CGuild::GetGuildAllySize();
		if( size == 0 )
		{
			Trace("등록된 동맹(적대) 길드가 없습니다.\n");
			break;
		}

		PACKET_ZC_MYGUILD_BASIC_INFO Packet;
		Packet.PacketType = HEADER_ZC_MYGUILD_BASIC_INFO;
		Packet.PacketLength = 4 + size * 32;

		char Info[3072];
		memset(Info, 0, sizeof(Info));
		g->CGuild::GetGuildAllyInfo(Info);

		g_characterMgr->CCharacterMgr::SendMsg(0, AID, 25, 4, (int)&Packet, 0, 0);
		g_characterMgr->CCharacterMgr::SendMsg(0, AID, 25, size * 32, (int)&Info, 0, 0);
	}
	break;
	case 1:
	{
		if( timeGetTime() - m_ReqGuildMenuTime[1] < 10000 )
			break;

		m_ReqGuildMenuTime[1] = timeGetTime();

		int GDID = 0;
		m_pc->GetParameterValue(VAR_GDID, GDID);

		if( GDID == 0 )
			break;

		CGuild* g = g_ZGuildMgr->CGuildMgr::SearchGuild(GDID);
		if( g == NULL )
		{
			Trace("로딩된 GDID가 없습니다.\n");
			break;
		}

		unsigned long AID = m_pc->GetAccountID();
		if( AID == 0 )
			break;

		int msize = g->CGuild::GetGuildMSize();
		if( msize == 0 )
		{
			Trace("등록된 길드 원이 없습니다.\n");
			break;
		}

		int possize = g->CGuild::GetGuildMPosSize();
		if( possize == 0 )
		{
			Trace("등록된 길드 직위 설정정보가 없습니다.\n");
			break;
		}

		PACKET_ZC_POSITION_ID_NAME_INFO NPacket;
		NPacket.PacketType = HEADER_ZC_POSITION_ID_NAME_INFO;
		NPacket.PacketLength = 4 + possize * 28;

		char Info[3072];
		memset(Info, 0, sizeof(Info));
		g->CGuild::GetGuildPosID(Info);

		g_characterMgr->CCharacterMgr::SendMsg(0, AID, 25, 4, (int)&NPacket, 0, 0);
		g_characterMgr->CCharacterMgr::SendMsg(0, AID, 25, 28 * possize, (int)Info, 0, 0);

		PACKET_ZC_MEMBERMGR_INFO Packet;
		Packet.PacketType = HEADER_ZC_MEMBERMGR_INFO;
		Packet.PacketLength = 4 + msize * 104;

		char Buf[7840];
		memset(Buf, 0, sizeof(Buf));
		if( !((CZGuildInfo*)g)->CZGuildInfo::GetGuildMInfo(Buf) )
			break;
		
		g_characterMgr->CCharacterMgr::SendMsg(0, AID, 25, 4, (int)&Packet, 0, 0);
		g_characterMgr->CCharacterMgr::SendMsg(0, AID, 25, 104 * msize, (int)&Buf, 0, 0);
	}
	break;
	case 4:
	{
		if( timeGetTime() - m_ReqGuildMenuTime[2] < 10000 )
			break;

		m_ReqGuildMenuTime[2] = timeGetTime();

		int GDID;
		m_pc->GetParameterValue(VAR_GDID, GDID);
		if( GDID == 0 )
			break;

		CGuild* g = g_ZGuildMgr->CGuildMgr::SearchGuild(GDID);
		if( g == NULL )
		{
			Trace("로딩된 GDID가 없습니다.\n");
			break;
		}

		unsigned long AID = m_pc->GetAccountID();
		if( AID == 0 )
			break;

		int size = g->CGuild::GetGuildBanishSize();
		if( size == 0 )
		{
			Trace("등록된 길드 Ban List가 없습니다.\n");
			break;
		}

		PACKET_ZC_BAN_LIST Packet;
		Packet.PacketType = HEADER_ZC_BAN_LIST;
		Packet.PacketLength = 4 + size * 88;

		char Buf[4440];
		memset(Buf, 0, sizeof(Buf));
		g->CGuild::GetGuildBanishInfo(Buf);

		g_characterMgr->CCharacterMgr::SendMsg(0, AID, 25, 4, (int)&Packet, 0, 0);
		g_characterMgr->CCharacterMgr::SendMsg(0, AID, 25, size * 88, (int)&Buf, 0, 0);
	}
	break;
	case 2:
	{
		if( timeGetTime() - m_ReqGuildMenuTime[3] < 10000 )
			break;

		m_ReqGuildMenuTime[3] = timeGetTime();

		int GDID;
		m_pc->GetParameterValue(VAR_GDID, GDID);

		if( GDID == 0 )
		{
			Trace("로딩된 GDID가 없습니다.\n");
			break;
		}

		CGuild* g = g_ZGuildMgr->CGuildMgr::SearchGuild(GDID);
		if( g == NULL )
			break;

		unsigned long AID = m_pc->GetAccountID();
		if( AID == 0 )
			break;

		int size = g->CGuild::GetGuildMPosSize();
		if( size == 0 )
		{
			Trace("등록된 길드 직위 설정정보가 없습니다.\n");
			break;
		}

		PACKET_ZC_POSITION_ID_NAME_INFO Packet;
		Packet.PacketType = HEADER_ZC_POSITION_ID_NAME_INFO;
		Packet.PacketLength = 4 + size * 28;

		char Info[3072];
		memset(Info, 0, sizeof(Info));
		g->CGuild::GetGuildPosID(Info);

		g_characterMgr->CCharacterMgr::SendMsg(0, AID, 25, 4, (int)&Packet, 0, 0);
		g_characterMgr->CCharacterMgr::SendMsg(0, AID, 25, size * 28, (int)&Info, 0, 0);

		PACKET_ZC_POSITION_INFO Packet2;
		Packet2.PacketType = HEADER_ZC_POSITION_INFO;
		Packet2.PacketLength = 4 + size * 16;

		char Buf[3072];
		memset(Buf, 0, sizeof(Buf));
		g->CGuild::GetGuildMPosition(Buf);

		g_characterMgr->CCharacterMgr::SendMsg(0, AID, 25, 4, (int)&Packet2, 0, 0);
		g_characterMgr->CCharacterMgr::SendMsg(0, AID, 25, size * 16, (int)&Buf, 0, 0);
	}
	break;
	case 6:
	{
		int GDID = 0;
		m_pc->GetParameterValue(VAR_GDID, GDID);

		if( GDID != 0 )
		{
			CZGuildInfo* g = (CZGuildInfo*)g_ZGuildMgr->CGuildMgr::SearchGuild(GDID);
			if( g != NULL )
				g->CZGuildInfo::SendGuildNotice(m_pc->GetAccountID());
		}
	}
	break;
	case 3:
	{
		if( m_pc->m_characterInfo.GuildID != 0 )
		{
			CZGuildInfo* g = (CZGuildInfo*)g_ZGuildMgr->CGuildMgr::SearchGuild(m_pc->m_characterInfo.GuildID);
			if( g != NULL )
				g->CZGuildInfo::NotifySkillInfo(m_pc->GetAccountID());
		}
	}
	break;
	default:
	break;
	}
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnReqGuildEmblemImg(SERVER, "CPCPacketHandler::OnReqGuildEmblemImg");
void CPCPacketHandler::OnReqGuildEmblemImg(int len)
{
	return (this->*_OnReqGuildEmblemImg)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnRegisterGuildEmblemImg(SERVER, "CPCPacketHandler::OnRegisterGuildEmblemImg");
HOOKED void CPCPacketHandler::OnRegisterGuildEmblemImg(int len)
{
//	return (this->*_OnRegisterGuildEmblemImg)(len);

	if( len > 3072 || len <= 4 )
	{
		m_pc->AddErrorCount(".\\PCPacketHandler.cpp", 9645, 4, timeGetTime());
		return;
	}

	char Buf[3072];
	memset(Buf, 0, sizeof(Buf));
	m_recvQueue->CPacketQueue::GetData(len, Buf);
	PACKET_CZ_REGISTER_GUILD_EMBLEM_IMG& CZPacket = *(PACKET_CZ_REGISTER_GUILD_EMBLEM_IMG*)Buf;

	int GDID = 0;
	m_pc->GetParameterValue(VAR_GDID, GDID);
	if( GDID == 0 )
		return;

	char Emblem[3072];
	memset(Emblem, 0, sizeof(Emblem));
	memcpy(Emblem, CZPacket.Emblem, len - sizeof(CZPacket));

	// validate emblem bitmap data
	CZLib zlib;
	char tmp[3072];
	unsigned long destlen = sizeof(tmp);
	if( 0 != zlib.Uncompress((unsigned char*)tmp, &destlen, (unsigned char*)Emblem, sizeof(Emblem)) )
		return;
	if( destlen != sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + 24 * 24 * sizeof(RGBTRIPLE) )
		return;
	BITMAPFILEHEADER& bmfh = *(BITMAPFILEHEADER*)&tmp[0];
	BITMAPINFOHEADER& bmih = *(BITMAPINFOHEADER*)&tmp[14];
	if( bmih.biBitCount != 24 || bmih.biWidth != 24 || bmih.biHeight != 24 )
		return;

	PACKET_ZI_REGISTER_GUILD_EMBLEM_IMG ZIPacket;
	ZIPacket.PacketType = HEADER_ZI_REGISTER_GUILD_EMBLEM_IMG;
	ZIPacket.PacketLength = sizeof(ZIPacket) + len - sizeof(CZPacket);
	ZIPacket.GDID = GDID;
	ZIPacket.AID = m_pc->GetAccountID();
	ZIPacket.GID = m_pc->CPC::GetCharacterID();

	g_characterMgr->CCharacterMgr::SendToIServer(sizeof(ZIPacket), (const char *)&ZIPacket);
	g_characterMgr->CCharacterMgr::SendToIServer(len - sizeof(CZPacket), Emblem);
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnReqChangeMemberPos(SERVER, "CPCPacketHandler::OnReqChangeMemberPos");
void CPCPacketHandler::OnReqChangeMemberPos(int len)
{
	return (this->*_OnReqChangeMemberPos)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnReqOpenMemberInfo(SERVER, "CPCPacketHandler::OnReqOpenMemberInfo");
void CPCPacketHandler::OnReqOpenMemberInfo(int len)
{
	return (this->*_OnReqOpenMemberInfo)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnReqLeaveGuild(SERVER, "CPCPacketHandler::OnReqLeaveGuild");
void CPCPacketHandler::OnReqLeaveGuild(int len)
{
	return (this->*_OnReqLeaveGuild)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnReqBanGuild(SERVER, "CPCPacketHandler::OnReqBanGuild");
void CPCPacketHandler::OnReqBanGuild(int len)
{
	return (this->*_OnReqBanGuild)(len);

	PACKET_CZ_REQ_BAN_GUILD packet;
	m_recvQueue->CPacketQueue::GetData(54, (char*)&packet);

	if( m_pc->m_mapRes == NULL )
		return;

	if( m_pc->m_mapRes->IsAgit() && ((CAgitMapRes*)m_pc->m_mapRes)->CAgitMapRes::IsSiegeTime() )
		return; // can't expel on woe maps during woe

	unsigned long GDID = 0;
	m_pc->GetParameterValue(VAR_GDID, (int&)GDID);
	if( GDID == 0 )
		return;

	CGuild* g = g_ZGuildMgr->CGuildMgr::SearchGuild(GDID);
	if( g == NULL )
		return;

	if( !g->CGuild::isPenaltyRight(m_pc->CPC::GetCharacterID()) )
		return; // need to have the right to expel

	PACKET_ZI_REQ_BAN_GUILD ZIPacket;
	ZIPacket.PacketType = HEADER_ZI_REQ_BAN_GUILD;
	ZIPacket.GDID = packet.GDID;
	ZIPacket.AID = packet.AID;
	ZIPacket.GID = packet.GID;
	ZIPacket.MyGID = m_pc->CPC::GetCharacterID();
	ZIPacket.AccountName; // uninitialized
	memcpy(ZIPacket.reasonDesc, packet.reasonDesc, sizeof(ZIPacket.reasonDesc));
	g_characterMgr->CCharacterMgr::SendToIServer(sizeof(ZIPacket), (char*)&ZIPacket);
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnReqDisorganizeGuild(SERVER, "CPCPacketHandler::OnReqDisorganizeGuild");
void CPCPacketHandler::OnReqDisorganizeGuild(int len)
{
	return (this->*_OnReqDisorganizeGuild)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnReqChangeGuildPositionInfo(SERVER, "CPCPacketHandler::OnReqChangeGuildPositionInfo");
void CPCPacketHandler::OnReqChangeGuildPositionInfo(int len)
{
	return (this->*_OnReqChangeGuildPositionInfo)(len);

	//TODO
}


/// @patch backport "disable hostile request", "disable ally request" setting from 20100527ZoneProcess - r2616
hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnReqHostileGuild(SERVER, "CPCPacketHandler::OnReqHostileGuild");
HOOKED void CPCPacketHandler::OnReqHostileGuild(int len)
{
	if( CSettings::GetObj()->m_bDisableGuildHostileRequest != 0 )
	{
		PACKET_CZ_REQ_HOSTILE_GUILD Packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char *)&Packet);
		return;
	}

	return (this->*_OnReqHostileGuild)(len);

	PACKET_CZ_REQ_HOSTILE_GUILD Packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char *)&Packet);

	unsigned long AID = m_pc->GetAccountID();
	if( AID == 0 )
		return;

	unsigned long GDID = 0;
	m_pc->GetParameterValue(VAR_GDID, (int&)GDID);
	if( GDID == 0 )
		return;

	CGuild* g = g_ZGuildMgr->CGuildMgr::SearchGuild(GDID);
	if( g == NULL )
		return;

	if( g->CGuild::GetHostileCount() >= 3 )
	{
		this->CPCPacketHandler::SendAckReqHostileGuild(AID, RESULT_HOSTILE_OVERSIZE);
		return;
	}

	CPC* target = (CPC *)g_characterMgr->CCharacterMgr::FindCharacter(Packet.AID, PC_TYPE);
	if( target == NULL )
		return;

	target->CPC::GetCharacterID();

	unsigned long OtherGDID = 0;
	target->GetParameterValue(VAR_GDID, (int&)OtherGDID);
	if( OtherGDID == 0 || GDID == OtherGDID )
		return;

	if( g->CGuild::FindHostileGuild(OtherGDID) )
	{
		this->CPCPacketHandler::SendAckReqHostileGuild(AID, RESULT_HOSTILE_ALREADY_HOSTILE);
		return;
	}

	PACKET_ZI_REQ_HOSTILE_GUILD ZIPacket;
	ZIPacket.PacketType = HEADER_ZI_REQ_HOSTILE_GUILD;
	ZIPacket.GDID = GDID;
	ZIPacket.OtherGDID = OtherGDID;
	ZIPacket.MyAID = AID;

	g_characterMgr->CCharacterMgr::SendToIServer(sizeof(ZIPacket), (const char *)&ZIPacket);
}


hook_method<void (CPCPacketHandler::*)(unsigned long AID, unsigned char answer)> CPCPacketHandler::_SendAckReqAllyGuild(SERVER, "CPCPacketHandler::SendAckReqAllyGuild");
void CPCPacketHandler::SendAckReqAllyGuild(unsigned long AID, unsigned char answer)
{
	return (this->*_SendAckReqAllyGuild)(AID, answer);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(unsigned long AID, unsigned char answer)> CPCPacketHandler::_SendAckReqHostileGuild(SERVER, "CPCPacketHandler::SendAckReqHostileGuild");
void CPCPacketHandler::SendAckReqHostileGuild(unsigned long AID, unsigned char answer)
{
	return (this->*_SendAckReqHostileGuild)(AID, answer);

	//TODO
}


/// @patch backport "disable hostile request", "disable ally request" setting from 20100527ZoneProcess - r2616
hook_method<void (CPCPacketHandler::*)(int packetSize)> CPCPacketHandler::_OnReqAllyGuild(SERVER, "CPCPacketHandler::OnReqAllyGuild");
HOOKED void CPCPacketHandler::OnReqAllyGuild(int packetSize)
{
	if( CSettings::GetObj()->m_bDisableGuildAllyRequest != 0 )
	{
		PACKET_CZ_REQ_ALLY_GUILD Packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char *)&Packet);
		return;
	}

	return (this->*_OnReqAllyGuild)(packetSize);

	PACKET_CZ_REQ_ALLY_GUILD Packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char *)&Packet);

	unsigned long GDID = 0;
	m_pc->GetParameterValue(VAR_GDID, (int&)GDID);
	if( GDID == 0 )
		return;

	if( CAgitMapRes::IsSiegeTime(m_pc->m_mapRes) )
		return; // can't ally during woe time

	CGuild* g = g_ZGuildMgr->CGuildMgr::SearchGuild(GDID);
	if( g == NULL )
		return;

	if( g->CGuild::GetAllyCount() >= 3 )
	{
		this->CPCPacketHandler::SendAckReqAllyGuild(Packet.MyAID, REQMYGUILD_OVERSIZE);
		return; // max. alliances reached
	}

	CPC* target = (CPC *)g_characterMgr->CCharacterMgr::FindCharacter(Packet.AID, PC_TYPE);
	if( target == NULL )
		return;

	target->CPC::GetCharacterID();

	unsigned long OtherGDID = 0;
	target->GetParameterValue(VAR_GDID, (int&)OtherGDID);
	if( OtherGDID == 0 || GDID == OtherGDID )
		return;

	CGuild* tg = g_ZGuildMgr->CGuildMgr::SearchGuild(OtherGDID);
	if( tg == NULL )
		return;

	if( tg->CGuild::GetAllyCount() >= 3 )
	{
		this->CPCPacketHandler::SendAckReqAllyGuild(Packet.MyAID, REQALLYGUILD_OVERSIZE);
		return; // max. alliances reached
	}

	if( g->CGuild::FindAllyGuild(OtherGDID) && tg->CGuild::FindAllyGuild(GDID) )
	{
		this->CPCPacketHandler::SendAckReqAllyGuild(Packet.MyAID, REQALLYGUILD_ALREADY_ALLIED);
		return; // already allied
	}

	PACKET_ZC_REQ_ALLY_GUILD ZCPacket;
	ZCPacket.PacketType = HEADER_ZC_REQ_ALLY_GUILD;
	ZCPacket.otherAID = Packet.MyAID;
	if( g->CGuild::GetGuildName() == NULL )
		return; // should never happen
	memcpy(ZCPacket.guildName, g->CGuild::GetGuildName(), sizeof(ZCPacket.guildName));

	g_characterMgr->CCharacterMgr::SendMsg(NULL, Packet.AID, CM_SEND_PACKET, sizeof(ZCPacket), (int)&ZCPacket, 0, 0);
}


hook_method<void (CPCPacketHandler::*)(int packetSize)> CPCPacketHandler::_OnAllyGuild(SERVER, "CPCPacketHandler::OnAllyGuild");
void CPCPacketHandler::OnAllyGuild(int packetSize)
{
	return (this->*_OnAllyGuild)(packetSize);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int packetSize)> CPCPacketHandler::_OnGuildNotice(SERVER, "CPCPacketHandler::OnGuildNotice");
void CPCPacketHandler::OnGuildNotice(int packetSize)
{
	return (this->*_OnGuildNotice)(packetSize);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int packetSize)> CPCPacketHandler::_OnGuildChat(SERVER, "CPCPacketHandler::OnGuildChat");
HOOKED void CPCPacketHandler::OnGuildChat(int packetSize) // line 10212-10250
{
	char packetbuf[256];
	m_recvQueue->PeekData(sizeof(packetbuf), packetbuf);

	char *name, *message;
	int namelen, messagelen;
	if( clif_process_message(m_pc, packetbuf, 0, &name, &namelen, &message, &messagelen) )
	{
		if( AtCommand(m_pc, message) )
		{
			m_recvQueue->RemoveData(packetSize);
			return;
		}
	}

	return (this->*_OnGuildChat)(packetSize);

	if( packetSize - 4 <= 0 || packetSize > 1024 )
	{
		m_pc->AddErrorCount(".\\PCPacketHandler.cpp", 10217, 4, timeGetTime());
		return; // invalid packet length
	}

	char Buf[1024];
	memset(Buf, 0, sizeof(Buf));
	m_recvQueue->CPacketQueue::GetData(packetSize, Buf);
	PACKET_CZ_GUILD_CHAT* packet = reinterpret_cast<PACKET_CZ_GUILD_CHAT*>(&Buf);

	if( m_pc != NULL && m_pc->IsItPossible(MAPPROPERTY_NO_CHATTING) != 0 )
	{
		m_pc->CPC::SendZCMsg(MSI_NO_CHATTING);
		return; // can't chat in this map
	}

	int textLen = packetSize - sizeof(PACKET_CZ_GUILD_CHAT);
	if( textLen > 100 )
		return; // too much text

	int GDID = 0;
	m_pc->GetParameterValue(VAR_GDID, GDID);
	if( GDID == 0 )
		return; // not in a guild

	if ( m_pc->CPC::IsBadGuy() != 0 )
		return; // player can't chat in the current state

	PACKET_ZI_GUILD_CHAT ZIPacket;
	ZIPacket.GDID = GDID;
	ZIPacket.PacketLength = textLen + sizeof(ZIPacket);
	ZIPacket.PacketType = HEADER_ZI_GUILD_CHAT;
	g_characterMgr->CCharacterMgr::SendToIServer(sizeof(ZIPacket), (const char *)&ZIPacket);
	g_characterMgr->CCharacterMgr::SendToIServer(textLen, packet->Text);
}


hook_method<void (CPCPacketHandler::*)(int packetLen)> CPCPacketHandler::_OnReqMakeGuild(SERVER, "CPCPacketHandler::OnReqMakeGuild");
HOOKED void CPCPacketHandler::OnReqMakeGuild(int packetLen)
{
//	return (this->*_OnReqMakeGuild)(packetLen);

	PACKET_CZ_REQ_MAKE_GUILD Packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char *)&Packet);

	if( g_ForeignCode != 4 )
	{
		if( Packet.GName[0] == ' ' )
			return;

		if( Packet.GName[strlen(Packet.GName)-1] == ' ' )
			return;

		if( strchr(Packet.GName, 0xA1A1) != NULL ) // '　'
			return;
	}

	for( size_t i = 0; i < strlen(Packet.GName); ++i )
		if( Packet.GName[i] == '#' )
			return;

	if( !m_pc->CPC::ConsumeItemForSkill(714, 1) )
	{
		PACKET_ZC_RESULT_MAKE_GUILD ZCPacket;
		ZCPacket.PacketType = HEADER_ZC_RESULT_MAKE_GUILD;
		ZCPacket.result = 3;
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc->GetAccountID(), CM_SEND_PACKET, sizeof(ZCPacket), (int)&ZCPacket, 0, 0);
		return;
	}

	m_pc->m_pcitemInventoryMgr.CPCItemInventoryMgr::InsertEmpeliumItem(714);

	if( strlen(Packet.GName) > sizeof(Packet.GName) - 1 )
		return;

	PACKET_ZI_REQ_MAKE_GUILD ZIPacket;
	ZIPacket.PacketType = HEADER_ZI_REQ_MAKE_GUILD;
	ZIPacket.GDID = 0;
	ZIPacket.GID = Packet.GID;
	ZIPacket.AID = m_pc->GetAccountID();
	memcpy(ZIPacket.GName, Packet.GName, sizeof(ZIPacket.GName));
	memcpy(ZIPacket.MName, m_pc->m_characterInfo.characterName, sizeof(ZIPacket.MName));
	memcpy(ZIPacket.AccountName, m_pc->m_characterInfo.accountName, sizeof(ZIPacket.AccountName));
	g_characterMgr->CCharacterMgr::SendToIServer(sizeof(ZIPacket), (const char *)&ZIPacket);

	Trace("%s 가 %s길드 만들기 ...\n", ZIPacket.MName, ZIPacket.GName);
}


hook_method<void (CPCPacketHandler::*)(int packetSize)> CPCPacketHandler::_OnReqJoinGuild(SERVER, "CPCPacketHandler::OnReqJoinGuild");
void CPCPacketHandler::OnReqJoinGuild(int packetSize)
{
	return (this->*_OnReqJoinGuild)(packetSize);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int packetSize)> CPCPacketHandler::_OnJoinGuild(SERVER, "CPCPacketHandler::OnJoinGuild");
void CPCPacketHandler::OnJoinGuild(int packetSize)
{
	return (this->*_OnJoinGuild)(packetSize);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int Len)> CPCPacketHandler::_OnReqDeleteRelatedGuild(SERVER, "CPCPacketHandler::OnReqDeleteRelatedGuild");
void CPCPacketHandler::OnReqDeleteRelatedGuild(int Len)
{
	return (this->*_OnReqDeleteRelatedGuild)(Len);

	//TODO
}


//hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnReqGuildMemberInfo(SERVER, "CPCPacketHandler::OnReqGuildMemberInfo");
void CPCPacketHandler::OnReqGuildMemberInfo(int len)
{
//	return (this->*_OnReqGuildMemberInfo)(len);

	PACKET_CZ_REQ_GUILD_MEMBER_INFO packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char *)&packet);

	int GDID = 0;
	m_pc->GetParameterValue(VAR_GDID, GDID);
	if( GDID == 0 )
		return;

	CGuild* g = g_ZGuildMgr->CGuildMgr::SearchGuild(GDID);
	if( g == NULL )
	{
		Trace("로딩된 GDID가 없습니다.\n");
		return;
	}

	unsigned long AID = m_pc->GetAccountID();
	if( AID == 0 )
		return;
	
	GUILD_MEMBER_INFO Info;
	g->CGuild::GetGuildMemberInfo(packet.GID, Info);

	PACKET_ZC_ACK_GUILD_MEMBER_INFO ZCPacket;
	ZCPacket.PacketType = HEADER_ZC_ACK_GUILD_MEMBER_INFO;
	memcpy(&ZCPacket.Info, &Info, sizeof(ZCPacket.Info));
	g_characterMgr->CCharacterMgr::SendMsg(NULL, AID, CM_SEND_PACKET, sizeof(ZCPacket), (int)&ZCPacket, 0, 0);
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnResetParameter(SERVER, "CPCPacketHandler::OnResetParameter");
void CPCPacketHandler::OnResetParameter(int len)
{
	return (this->*_OnResetParameter)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnChangeMapType(SERVER, "CPCPacketHandler::OnChangeMapType");
void CPCPacketHandler::OnChangeMapType(int len)
{
	return (this->*_OnChangeMapType)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnLocalBroadCast(SERVER, "CPCPacketHandler::OnLocalBroadCast");
void CPCPacketHandler::OnLocalBroadCast(int len)
{
	return (this->*_OnLocalBroadCast)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnChangeEffectState(SERVER, "CPCPacketHandler::OnChangeEffectState");
void CPCPacketHandler::OnChangeEffectState(int len)
{
	return (this->*_OnChangeEffectState)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(void)> CPCPacketHandler::_ResetReqGuildTime(SERVER, "CPCPacketHandler::ResetReqGuildTime");
void CPCPacketHandler::ResetReqGuildTime(void)
{
	return (this->*_ResetReqGuildTime)();

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnGuildZeny(SERVER, "CPCPacketHandler::OnGuildZeny");
void CPCPacketHandler::OnGuildZeny(int len)
{
	return (this->*_OnGuildZeny)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnReqMakingItem(SERVER, "CPCPacketHandler::OnReqMakingItem");
void CPCPacketHandler::OnReqMakingItem(int len)
{
	return (this->*_OnReqMakingItem)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnReqUSE_SKILL_TOGROUND_WITHTALKBOX(SERVER, "CPCPacketHandler::OnReqUSE_SKILL_TOGROUND_WITHTALKBOX");
void CPCPacketHandler::OnReqUSE_SKILL_TOGROUND_WITHTALKBOX(int len)
{
	return (this->*_OnReqUSE_SKILL_TOGROUND_WITHTALKBOX)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int packetSize)> CPCPacketHandler::_OnGiveMannerPoint(SERVER, "CPCPacketHandler::OnGiveMannerPoint");
void CPCPacketHandler::OnGiveMannerPoint(int packetSize)
{
	return (this->*_OnGiveMannerPoint)(packetSize);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnGiveMannerPointByName(SERVER, "CPCPacketHandler::OnGiveMannerPointByName");
void CPCPacketHandler::OnGiveMannerPointByName(int len)
{
	return (this->*_OnGiveMannerPointByName)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnTryCaptureMonster(SERVER, "CPCPacketHandler::OnTryCaptureMonster");
void CPCPacketHandler::OnTryCaptureMonster(int len)
{
	return (this->*_OnTryCaptureMonster)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnCommandPet(SERVER, "CPCPacketHandler::OnCommandPet");
void CPCPacketHandler::OnCommandPet(int len)
{
	return (this->*_OnCommandPet)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnRenamePet(SERVER, "CPCPacketHandler::OnRenamePet");
void CPCPacketHandler::OnRenamePet(int len)
{
	return (this->*_OnRenamePet)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnRenameHomun(SERVER, "CPCPacketHandler::OnRenameHomun");
void CPCPacketHandler::OnRenameHomun(int len)
{
	return (this->*_OnRenameHomun)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnSelectPetEgg(SERVER, "CPCPacketHandler::OnSelectPetEgg");
void CPCPacketHandler::OnSelectPetEgg(int len)
{
	return (this->*_OnSelectPetEgg)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnPetEggInfo(SERVER, "CPCPacketHandler::OnPetEggInfo");
void CPCPacketHandler::OnPetEggInfo(int len)
{
	return (this->*_OnPetEggInfo)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnPetAct(SERVER, "CPCPacketHandler::OnPetAct");
void CPCPacketHandler::OnPetAct(int len)
{
	return (this->*_OnPetAct)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(void)> CPCPacketHandler::_OnMakingItem(SERVER, "CPCPacketHandler::OnMakingItem");
void CPCPacketHandler::OnMakingItem(void)
{
	return (this->*_OnMakingItem)();

	//TODO
}


static void __cdecl MakeLower(char* text) // line 10817-10826
{
	for( size_t i = 0; i < strlen(text); ++i )
		if( text[i] > 0 && isupper(text[i]) )
			text[i] += 0x20;
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnRemoveAID(SERVER, "CPCPacketHandler::OnRemoveAID");
void CPCPacketHandler::OnRemoveAID(int len) // line 10829-10874
{
	return (this->*_OnRemoveAID)(len);

	PACKET_CZ_REMOVE_AID Packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char*)&Packet);

	if( g_zoneScript->CZoneScript::SearchID(m_pc->m_characterInfo.accountName, CHECK_MOVEAID) == 0 )
		return; // gm privilege required

	char Buf[256] = {};
	sprintf(Buf, "Remove AID %s Target %s", m_pc->m_characterInfo.accountName, Packet.AccountName);
	g_errorLogs->CErrorLog::MoveLog(Buf);

	CPC* target = g_characterMgr->CCharacterMgr::FindCharacter(Packet.AccountName);
	if( target != NULL )
	{// warp self to target
		int desXPos = 0;
		int desYPos = 0;
		target->GetParameterValue(VAR_CURXPOS, desXPos);
		target->GetParameterValue(VAR_CURYPOS, desYPos);

		if( target->CCharacter::GetMapRes() == NULL )
			return;

		MS_MAPMOVE outpar;
		outpar.Set(target->CCharacter::GetMapRes()->CMapRes::GetName(), desXPos, desYPos, 0);
		g_characterMgr->CCharacterMgr::SendMsg(m_pc, m_pc, CM_MAPMOVE, (int)&outpar, VT_TELEPORT, 0, 0);

		this->CPCPacketHandler::ResetReqGuildTime();
	}
	else
	{// request location of target AccountName so that it can be warped to
		MakeLower(Packet.AccountName);

		PACKET_ZI_MOVE ZIPacket;
		ZIPacket.PacketType = HEADER_ZI_MOVE;
		ZIPacket.MoveType = SHIFTAID;
		ZIPacket.SrcID = m_pc->GetAccountID();
		ZIPacket.DestX = m_pc->m_pathInfo.m_moveInfo.dxPos; //NOTE: unused?
		ZIPacket.DestY = m_pc->m_pathInfo.m_moveInfo.dyPos; //NOTE: unused?
		memcpy(ZIPacket.DestName, Packet.AccountName, 24);
		g_characterMgr->CCharacterMgr::SendToIServer(sizeof(ZIPacket), (char*)&ZIPacket);
	}
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnShift(SERVER, "CPCPacketHandler::OnShift");
void CPCPacketHandler::OnShift(int len) // line 10878-10917
{
	return (this->*_OnShift)(len);

	PACKET_CZ_SHIFT Packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char*)&Packet);

	if( g_zoneScript->CZoneScript::SearchID(m_pc->m_characterInfo.accountName, CHECK_SHIFT) == 0 )
		return; // gm privilege required

	CPC* target = g_characterMgr->CCharacterMgr::FindCharacter(Packet.CharacterName);
	if( target != NULL )
	{// warp self to target
		int desXPos = 0;
		int desYPos = 0;
		target->GetParameterValue(VAR_CURXPOS, desXPos);
		target->GetParameterValue(VAR_CURYPOS, desYPos);

		if( target->CCharacter::GetMapRes() == NULL )
			return;

		MS_MAPMOVE outpar;
		outpar.Set(target->CCharacter::GetMapRes()->CMapRes::GetName(), desXPos, desYPos, 0);
		g_characterMgr->CCharacterMgr::SendMsg(m_pc, m_pc, CM_MAPMOVE, (int)&outpar, VT_TELEPORT, 0, 0);

		this->CPCPacketHandler::ResetReqGuildTime();
	}
	else
	{// request location of target CharacterName so that it can be warped to
		PACKET_ZI_MOVE ZIPacket;
		ZIPacket.PacketType = HEADER_ZI_MOVE;
		ZIPacket.MoveType = SHIFTGID;
		ZIPacket.SrcID = m_pc->GetAccountID();
		ZIPacket.DestX = m_pc->m_pathInfo.m_moveInfo.dxPos; //NOTE: unused?
		ZIPacket.DestY = m_pc->m_pathInfo.m_moveInfo.dyPos; //NOTE: unused?
		memcpy(ZIPacket.DestName, Packet.CharacterName, 24);
		g_characterMgr->CCharacterMgr::SendToIServer(sizeof(ZIPacket), (char*)&ZIPacket);
	}
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnRecall(SERVER, "CPCPacketHandler::OnRecall");
void CPCPacketHandler::OnRecall(int len) // line 10920-10965
{
	return (this->*_OnRecall)(len);

	PACKET_CZ_RECALL Packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char*)&Packet);

	if( g_zoneScript->CZoneScript::SearchID(m_pc->m_characterInfo.accountName, CHECK_CALLAID) == 0 )
		return; // gm privilege required

	char Buf[256] = {};
	sprintf(Buf, "ReCall AID %s Target %s", m_pc->m_characterInfo.accountName, Packet.AccountName);
	g_errorLogs->CErrorLog::MoveLog(Buf);

	CPC* target = g_characterMgr->CCharacterMgr::FindCharacter(Packet.AccountName);
	if( target != NULL )
	{// warp target to self
		int desXPos = 0;
		int desYPos = 0;
		m_pc->GetParameterValue(VAR_CURXPOS, desXPos);
		m_pc->GetParameterValue(VAR_CURYPOS, desYPos);

		if( m_pc->CPC::GetMapRes() == NULL )
			return;

		MS_MAPMOVE outpar;
		outpar.Set(m_pc->CCharacter::GetMapRes()->CMapRes::GetName(), desXPos, desYPos, 0);
		g_characterMgr->CCharacterMgr::SendMsg(target, target, CM_MAPMOVE, (int)&outpar, VT_TELEPORT, 0, 0);
	}
	else
	{// request that target AccountName be warped to our coordinates
		MakeLower(Packet.AccountName);

		PACKET_ZI_MOVE ZIPacket;
		ZIPacket.PacketType = HEADER_ZI_MOVE;
		ZIPacket.MoveType = SUMMONAID;
		ZIPacket.SrcID = m_pc->GetAccountID();
		ZIPacket.DestX = m_pc->m_pathInfo.m_moveInfo.dxPos; //NOTE: unused?
		ZIPacket.DestY = m_pc->m_pathInfo.m_moveInfo.dyPos; //NOTE: unused?
		memcpy(ZIPacket.DestName, Packet.AccountName, 24);
		g_characterMgr->CCharacterMgr::SendToIServer(sizeof(ZIPacket), (char*)&ZIPacket);
	}
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnRecallGID(SERVER, "CPCPacketHandler::OnRecallGID");
void CPCPacketHandler::OnRecallGID(int len) // line 10968-11001
{
	return (this->*_OnRecallGID)(len);

	PACKET_CZ_RECALL_GID Packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char*)&Packet);

	if( g_zoneScript->CZoneScript::SearchID(m_pc->m_characterInfo.accountName, CHECK_CALLGID) == 0 )
		return; // gm privilege required

	CPC* target = g_characterMgr->CCharacterMgr::FindCharacter(Packet.CharacterName);
	if( target != NULL )
	{// warp target to self
		int desXPos = 0;
		int desYPos = 0;
		m_pc->GetParameterValue(VAR_CURXPOS, desXPos);
		m_pc->GetParameterValue(VAR_CURYPOS, desYPos);

		if( m_pc->CPC::GetMapRes() == NULL )
			return;

		MS_MAPMOVE outpar;
		outpar.Set(m_pc->CCharacter::GetMapRes()->CMapRes::GetName(), desXPos, desYPos, 0);
		g_characterMgr->CCharacterMgr::SendMsg(target, target, CM_MAPMOVE, (int)&outpar, VT_TELEPORT, 0, 0);
	}
	else
	{// request that the target CharacterName be warped to our coordinates
		PACKET_ZI_MOVE ZIPacket;
		ZIPacket.PacketType = HEADER_ZI_MOVE;
		ZIPacket.MoveType = SUMMONGID;
		ZIPacket.SrcID = m_pc->GetAccountID();
		ZIPacket.DestX = m_pc->m_pathInfo.m_moveInfo.dxPos; //NOTE: unused?
		ZIPacket.DestY = m_pc->m_pathInfo.m_moveInfo.dyPos; //NOTE: unused?
		memcpy(ZIPacket.DestName, Packet.CharacterName, 24);
		g_characterMgr->CCharacterMgr::SendToIServer(sizeof(ZIPacket), (char*)&ZIPacket);
	}
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnReqEncryption(SERVER, "CPCPacketHandler::OnReqEncryption");
void CPCPacketHandler::OnReqEncryption(int len)
{
	return (this->*_OnReqEncryption)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnInputEditDlgStr(SERVER, "CPCPacketHandler::OnInputEditDlgStr");
void CPCPacketHandler::OnInputEditDlgStr(int len)
{
	return (this->*_OnInputEditDlgStr)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnAddFriend(SERVER, "CPCPacketHandler::OnAddFriend");
void CPCPacketHandler::OnAddFriend(int len)
{
	return (this->*_OnAddFriend)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnDeleteFriend(SERVER, "CPCPacketHandler::OnDeleteFriend");
void CPCPacketHandler::OnDeleteFriend(int len)
{
	return (this->*_OnDeleteFriend)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnAckReqAddFriends(SERVER, "CPCPacketHandler::OnAckReqAddFriends");
void CPCPacketHandler::OnAckReqAddFriends(int len)
{
	return (this->*_OnAckReqAddFriends)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnReqStatus(SERVER, "CPCPacketHandler::OnReqStatus");
void CPCPacketHandler::OnReqStatus(int len)
{
	return (this->*_OnReqStatus)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(const short in_PacketType, const int in_PacketLength)> CPCPacketHandler::_OnReqMakerRanking(SERVER, "CPCPacketHandler::OnReqMakerRanking");
void CPCPacketHandler::OnReqMakerRanking(const short in_PacketType, const int in_PacketLength)
{
	return (this->*_OnReqMakerRanking)(in_PacketType, in_PacketLength);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnReqMakerRanking2(SERVER, "CPCPacketHandler::OnReqMakerRanking2");
void CPCPacketHandler::OnReqMakerRanking2(int len)
{
	return (this->*_OnReqMakerRanking2)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnReqDeathQuestion(SERVER, "CPCPacketHandler::OnReqDeathQuestion");
void CPCPacketHandler::OnReqDeathQuestion(int len)
{
	return (this->*_OnReqDeathQuestion)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnReqKSY(SERVER, "CPCPacketHandler::OnReqKSY");
void CPCPacketHandler::OnReqKSY(int len)
{
	return (this->*_OnReqKSY)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnLessEffect(SERVER, "CPCPacketHandler::OnLessEffect");
void CPCPacketHandler::OnLessEffect(int len)
{
	return (this->*_OnLessEffect)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnAckGameGuard(SERVER, "CPCPacketHandler::OnAckGameGuard");
void CPCPacketHandler::OnAckGameGuard(int len)
{
	return (this->*_OnAckGameGuard)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnRequestMoveToOwner(SERVER, "CPCPacketHandler::OnRequestMoveToOwner");
void CPCPacketHandler::OnRequestMoveToOwner(int len)
{
	return (this->*_OnRequestMoveToOwner)(len);

	if( !this->CPCPacketHandler::CheckRequestNpcTime() )
		return;

	PACKET_CZ_REQUEST_MOVETOOWNER packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

	if( !m_pc->m_isValid )
	{
		m_pc->AddErrorCount(4, timeGetTime());
		return;
	}

	if( m_pc->m_isMapLoading )
		return;

	if( packet.GID == m_pc->m_pcBattle.m_myHomunID )
		g_characterMgr->CCharacterMgr::SendMsg(NULL, packet.GID, CM_MOVETO_MYOWNER, 2, 0, 0, 0);

	if( packet.GID == m_pc->m_pcBattle.m_mercenaryID )
		g_characterMgr->CCharacterMgr::SendMsg(NULL, packet.GID, CM_MOVETO_MYOWNER, 2, 0, 0, 0);
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnRequestMoveNpc(SERVER, "CPCPacketHandler::OnRequestMoveNpc");
void CPCPacketHandler::OnRequestMoveNpc(int len)
{
	return (this->*_OnRequestMoveNpc)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnRequestActNpc(SERVER, "CPCPacketHandler::OnRequestActNpc");
void CPCPacketHandler::OnRequestActNpc(int len)
{
	return (this->*_OnRequestActNpc)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnCommandMercenary(SERVER, "CPCPacketHandler::OnCommandMercenary");
void CPCPacketHandler::OnCommandMercenary(int len)
{
	return (this->*_OnCommandMercenary)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnAckStorePassword(SERVER, "CPCPacketHandler::OnAckStorePassword");
void CPCPacketHandler::OnAckStorePassword(int len)
{
	return (this->*_OnAckStorePassword)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnMailGetList(SERVER, "CPCPacketHandler::OnMailGetList");
void CPCPacketHandler::OnMailGetList(int len)
{
	return (this->*_OnMailGetList)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnMailOpen(SERVER, "CPCPacketHandler::OnMailOpen");
void CPCPacketHandler::OnMailOpen(int len)
{
	return (this->*_OnMailOpen)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnMailDelete(SERVER, "CPCPacketHandler::OnMailDelete");
void CPCPacketHandler::OnMailDelete(int len)
{
	return (this->*_OnMailDelete)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnMailGetItem(SERVER, "CPCPacketHandler::OnMailGetItem");
void CPCPacketHandler::OnMailGetItem(int len)
{
	return (this->*_OnMailGetItem)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnMailResetItem(SERVER, "CPCPacketHandler::OnMailResetItem");
void CPCPacketHandler::OnMailResetItem(int len)
{
	return (this->*_OnMailResetItem)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnMailAddItem(SERVER, "CPCPacketHandler::OnMailAddItem");
void CPCPacketHandler::OnMailAddItem(int len)
{
	return (this->*_OnMailAddItem)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnMailSend(SERVER, "CPCPacketHandler::OnMailSend");
HOOKED void CPCPacketHandler::OnMailSend(int len)
{
	if( len > sizeof(PACKET_CZ_MAIL_SEND) + 2048 ) //TODO: hardcoded size
	{
		g_errorLogs->CErrorLog::CriticalErrorLogFmt(__FILE__, __LINE__, "Buffer overflow exploit attempt, len=%d (AID=%d,GID=%d)", len, m_pc->m_characterInfo.accountID, m_pc->m_characterInfo.characterID);
		m_recvQueue->CPacketQueue::RemoveData(len);
		return;		
	}

	return (this->*_OnMailSend)(len);

	PACKET_CZ_MAIL_SEND packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char *)&packet);

	int v3 = len - sizeof(packet);
	char buf[2048];
	m_recvQueue->CPacketQueue::GetData(v3, buf); //FIXME: client-controlled buffer overflow vulnerability

	if( g_isSendMailOn == 0 )
		return;

	if( v3 >= 200 )
		v3 = 200;

	unsigned long AID;
	unsigned long GID;
	if( strlen(packet.ReceiveName) == 0
	||  !g_charInfoDB->CCharInfoDB::GetCharacterID(packet.ReceiveName, AID, GID)
	||  AID == m_pc->GetAccountID() )
	{
		m_pc->m_pcitemInventoryMgr.CPCItemInventoryMgr::CancelMailItem(1, 1);

		PACKET_ZC_MAIL_REQ_SEND Packet;
		Packet.PacketType = HEADER_ZC_MAIL_REQ_SEND;
		Packet.Result = PACKET_ZC_MAIL_REQ_SEND::RESULT_USER_NOT_FOUND;
		m_pc->CPC::Send(sizeof(Packet), (char *)&Packet);
		return;
	}

	IVItItem item;
	int ItemCounter;
	char ItemBuffer[40];
	int ItemLen;
	unsigned long Money;
	m_pc->m_pcitemInventoryMgr.CPCItemInventoryMgr::GetMailItem(item, ItemCounter, ItemBuffer, ItemLen, Money);

	PACKET_ZI_MAIL_SEND ZIPacket;
	ZIPacket.PacketType = HEADER_ZI_MAIL_SEND;
	ZIPacket.PacketLength = sizeof(ZIPacket) + v3;
	ZIPacket.AID = AID;
	ZIPacket.GID = GID;
	if( strlen(packet.Header) == 0 )
		strcpy(packet.Header, "Mail");
	memcpy(ZIPacket.Header, packet.Header, sizeof(ZIPacket.Header));
	ZIPacket.Header[sizeof(ZIPacket.Header)-1] = '\0';
	memcpy(ZIPacket.ItemInfo, ItemBuffer, sizeof(ZIPacket.ItemInfo));
	ZIPacket.ItemLen = ItemLen;
	ZIPacket.Money = Money;
	memcpy(ZIPacket.SendName, m_pc->m_characterInfo.characterName, sizeof(ZIPacket.SendName));
	ZIPacket.SendAID = m_pc->GetAccountID();
	g_characterMgr->CCharacterMgr::SendToIServer(sizeof(ZIPacket), (const char *)&ZIPacket);
	g_characterMgr->CCharacterMgr::SendToIServer(v3, buf);

	m_pc->CPC::AsyncSaveBodyItem();

	CommonItemInfo ItemInfo;
	CPCItemInventoryMgr::DBValueParser(&ItemInfo, ItemBuffer, ItemLen);
	g_itemLog->CItemLog::AddMailSendLog(0, 25, m_pc, AID, GID, packet.ReceiveName, &ItemInfo, Money);
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnMailReturn(SERVER, "CPCPacketHandler::OnMailReturn");
void CPCPacketHandler::OnMailReturn(int len)
{
	return (this->*_OnMailReturn)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnAuctionCreate(SERVER, "CPCPacketHandler::OnAuctionCreate");
void CPCPacketHandler::OnAuctionCreate(int len)
{
	return (this->*_OnAuctionCreate)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnAuctionAddItem(SERVER, "CPCPacketHandler::OnAuctionAddItem");
void CPCPacketHandler::OnAuctionAddItem(int len)
{
	return (this->*_OnAuctionAddItem)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnAuctionAdd(SERVER, "CPCPacketHandler::OnAuctionAdd");
void CPCPacketHandler::OnAuctionAdd(int len)
{
	return (this->*_OnAuctionAdd)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnAuctionAddCancel(SERVER, "CPCPacketHandler::OnAuctionAddCancel");
void CPCPacketHandler::OnAuctionAddCancel(int len)
{
	return (this->*_OnAuctionAddCancel)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnAuctionBuy(SERVER, "CPCPacketHandler::OnAuctionBuy");
void CPCPacketHandler::OnAuctionBuy(int len)
{
	return (this->*_OnAuctionBuy)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnAuctionItemSearch(SERVER, "CPCPacketHandler::OnAuctionItemSearch");
void CPCPacketHandler::OnAuctionItemSearch(int len)
{
	return (this->*_OnAuctionItemSearch)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnAuctionReqMyInfo(SERVER, "CPCPacketHandler::OnAuctionReqMyInfo");
void CPCPacketHandler::OnAuctionReqMyInfo(int len)
{
	return (this->*_OnAuctionReqMyInfo)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnAuctionMySellStop(SERVER, "CPCPacketHandler::OnAuctionMySellStop");
void CPCPacketHandler::OnAuctionMySellStop(int len)
{
	return (this->*_OnAuctionMySellStop)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnHuntingList(SERVER, "CPCPacketHandler::OnHuntingList");
void CPCPacketHandler::OnHuntingList(int len)
{
	return (this->*_OnHuntingList)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnPCBuyCashPointItem(SERVER, "CPCPacketHandler::OnPCBuyCashPointItem");
void CPCPacketHandler::OnPCBuyCashPointItem(int len)
{
	return (this->*_OnPCBuyCashPointItem)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnPCBuyCashPointItemSimpleShop(SERVER, "CPCPacketHandler::OnPCBuyCashPointItemSimpleShop");
void CPCPacketHandler::OnPCBuyCashPointItemSimpleShop(int len)
{
	return (this->*_OnPCBuyCashPointItemSimpleShop)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnStandingResurrection(SERVER, "CPCPacketHandler::OnStandingResurrection");
void CPCPacketHandler::OnStandingResurrection(int len)
{
	return (this->*_OnStandingResurrection)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnCashPassword(SERVER, "CPCPacketHandler::OnCashPassword");
void CPCPacketHandler::OnCashPassword(int len)
{
	return (this->*_OnCashPassword)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnShortcutKey_Change(SERVER, "CPCPacketHandler::OnShortcutKey_Change");
HOOKED void CPCPacketHandler::OnShortcutKey_Change(int len)
{
//	return (this->*_OnShortcutKey_Change)(len);

	PACKET_CZ_SHORTCUT_KEY_CHANGE packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char *)&packet);

	if( packet.Index >= countof(m_pc->m_characterInfo.ShortCutKey) )
	{
//		m_pc->AddErrorCount(".\\PCPacketHandler.cpp", 12470, 4, timeGetTime());
		return;
	}

	m_pc->CPC::OnShortcutKey_Change(packet.Index, packet.ShortCutKey);
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnActiveQuest(SERVER, "CPCPacketHandler::OnActiveQuest");
void CPCPacketHandler::OnActiveQuest(int len)
{
	return (this->*_OnActiveQuest)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnBattleFieldChat(SERVER, "CPCPacketHandler::OnBattleFieldChat");
HOOKED void CPCPacketHandler::OnBattleFieldChat(int len)
{
	if( len > 4 + 512 ) //TODO: hardcoded size
	{
		g_errorLogs->CErrorLog::CriticalErrorLogFmt(__FILE__, __LINE__, "Buffer overflow exploit attempt, len=%d (AID=%d,GID=%d)", len, m_pc->m_characterInfo.accountID, m_pc->m_characterInfo.characterID);
		m_recvQueue->CPacketQueue::RemoveData(len);
		return;		
	}

	return (this->*_OnBattleFieldChat)(len);

	PACKET_CZ_BATTLEFIELD_CHAT packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

	char chatBuf[512];
	memset(chatBuf, 0, sizeof(chatBuf));

	unsigned int msglen = len - sizeof(packet);
	m_recvQueue->CPacketQueue::GetData(msglen, chatBuf); //FIXME: client-controlled buffer overflow vulnerability

	if( !m_pc->CCharacter::IsBattleFieldMode() )
		return;

	int campID = m_pc->GetCampID();

	PACKET_ZC_BATTLEFIELD_CHAT outpacket;
	memset(&outpacket, 0, sizeof(outpacket));
	outpacket.PacketType = HEADER_ZC_BATTLEFIELD_CHAT;
	outpacket.PacketLength = sizeof(PACKET_ZC_BATTLEFIELD_CHAT) + msglen;
	outpacket.accountID = m_pc->GetAccountID();
	strncpy(outpacket.name, m_pc->m_characterInfo.characterName, sizeof(outpacket.name));
	
	char temp[1024] = {};
	memcpy(&temp[0], (char *)&outpacket, sizeof(outpacket));
	memcpy(&temp[32], chatBuf, msglen);
	((CBattleFieldMapRes*)m_pc->CCharacter::GetMapRes())->CBattleFieldMapRes::BroadcastToCamp(campID, outpacket.PacketLength, temp);
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnProgress(SERVER, "CPCPacketHandler::OnProgress");
void CPCPacketHandler::OnProgress(int len)
{
	return (this->*_OnProgress)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnCzOpenSimpleCashShopItemList(SERVER, "CPCPacketHandler::OnCzOpenSimpleCashShopItemList");
void CPCPacketHandler::OnCzOpenSimpleCashShopItemList(int len)
{
	return (this->*_OnCzOpenSimpleCashShopItemList)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnCZOnCloseWindow(SERVER, "CPCPacketHandler::OnCZOnCloseWindow");
void CPCPacketHandler::OnCZOnCloseWindow(int len)
{
	return (this->*_OnCZOnCloseWindow)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnCZClientVersion(SERVER, "CPCPacketHandler::OnCZClientVersion");
void CPCPacketHandler::OnCZClientVersion(int len)
{
	return (this->*_OnCZClientVersion)(len);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnCZCloseSimpleCashShop(SERVER, "CPCPacketHandler::OnCZCloseSimpleCashShop");
void CPCPacketHandler::OnCZCloseSimpleCashShop(int len)
{
	return (this->*_OnCZCloseSimpleCashShop)(len);

	//TODO
}


hook_method<bool (CPCPacketHandler::*)(int packetType)> CPCPacketHandler::_IsFixedPacket(SERVER, "CPCPacketHandler::IsFixedPacket");
bool CPCPacketHandler::IsFixedPacket(int packetType)
{
	return (this->*_IsFixedPacket)(packetType);

	//TODO
}


hook_method<int  (CPCPacketHandler::*)(int packetType)> CPCPacketHandler::_GetPacketSize(SERVER, "CPCPacketHandler::GetPacketSize");
int CPCPacketHandler::GetPacketSize(int packetType)
{
	return (this->*_GetPacketSize)(packetType);

	//TODO
}


hook_method<bool (CPCPacketHandler::*)(void)> CPCPacketHandler::_CheckRequestNpcTime(SERVER, "CPCPacketHandler::CheckRequestNpcTime");
bool CPCPacketHandler::CheckRequestNpcTime(void)
{
	return (this->*_CheckRequestNpcTime)();

	//TODO
}


hook_method<bool (CPCPacketHandler::*)(int senderAID, unsigned long msgID, int par1, int par2, int par3)> CPCPacketHandler::_SendMsgItemScriptEvent(SERVER, "CPCPacketHandler::SendMsgItemScriptEvent");
bool CPCPacketHandler::SendMsgItemScriptEvent(int senderAID, unsigned long msgID, int par1, int par2, int par3)
{
	return (this->*_SendMsgItemScriptEvent)(senderAID, msgID, par1, par2, par3);

	//TODO
}


hook_method<bool (CPCPacketHandler::*)(unsigned long AID, unsigned long type)> CPCPacketHandler::_CheckMap(SERVER, "CPCPacketHandler::CheckMap");
bool CPCPacketHandler::CheckMap(unsigned long AID, unsigned long type)
{
	return (this->*_CheckMap)(AID, type);

	//TODO
}

hook_method<bool (CPCPacketHandler::*)(unsigned long NPCID)> CPCPacketHandler::_ForcedCloseDialog(SERVER, "CPCPacketHandler::ForcedCloseDialog");
bool CPCPacketHandler::ForcedCloseDialog(unsigned long NPCID)
{
	return (this->*_ForcedCloseDialog)(NPCID);

	//TODO
}

hook_method<void (CPCPacketHandler::*)(void)> CPCPacketHandler::_NotifyBattleFieldPoint(SERVER, "CPCPacketHandler::NotifyBattleFieldPoint");
void CPCPacketHandler::NotifyBattleFieldPoint(void)
{
	return (this->*_NotifyBattleFieldPoint)();

	//TODO
}


//hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnGroupInfoChangeV2(SERVER, "CPCPacketHandler::OnGroupInfoChangeV2");
void CPCPacketHandler::OnGroupInfoChangeV2(int len) // line ???
{
//	return (this->*_OnGroupInfoChangeV2)(len);

	PACKET_CZ_GROUPINFO_CHANGE_V2 packet;
	m_recvQueue->CPacketQueue::GetData(8, (char *)&packet);

	if( !m_pc->m_characterInfo.isGroupMaster )
		return;

	if( !m_pc->CPC::IsFamilySharePossible() )
	{
		PACKET_ZI_GROUPINFO_CHANGE_V2 outpacket;
		outpacket.PacketType = HEADER_ZI_GROUPINFO_CHANGE_V2;
		outpacket.GRID = m_pc->m_characterInfo.GroupID;
		outpacket.MasterAID = m_pc->GetAccountID();
		outpacket.FamilyGroup = 0;
		outpacket.expOption = packet.expOption;
		outpacket.ItemPickupRule = packet.ItemPickupRule;
		outpacket.ItemDivisionRule = packet.ItemDivisionRule;
		g_characterMgr->CCharacterMgr::SendToIServer(sizeof(outpacket), (const char *)&outpacket);
	}
	else
	{
		//outpacket.FamilyGroup = 1;
		//FIXME: is there a packet send missing here?

		for( mystd::list<unsigned long>::const_iterator it = m_pc->m_groupMember.begin(); it != m_pc->m_groupMember.end(); ++it )
		{
			unsigned long AID = *it;
			CPC* pc = (CPC *)g_characterMgr->CCharacterMgr::FindCharacter(AID, UNKNOWN_TYPE);
			if( pc != NULL )
				pc->m_familyInfo.expOption = 1;
		}
	}
}


//hook_method<void (CPCPacketHandler::*)(int len)> CPCPacketHandler::_OnSeekParty(SERVER, "CPCPacketHandler::OnSeekParty");
void CPCPacketHandler::OnSeekParty(int len) // line ???
{
//	return (this->*_OnSeekParty)(len);

	PACKET_CZ_SEEK_PARTY packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char *)&packet);

	if( m_pc->m_characterInfo.GroupID != 0 )
		return; // already in a party

	if( m_pc && m_pc->IsItPossible(31) )
	{
		m_pc->CPC::SendZCMsg(MSI_NO_CHATTING);
		return;
	}

	if( m_pc->CPC::IsBadGuy() )
		return;

	if( m_pc->GetEffective(EFST_CRYSTAL, 0) )
		return;

	PACKET_ZI_SEEK_PARTY outpacket;
	outpacket.PacketType = HEADER_ZI_SEEK_PARTY;
	memcpy(outpacket.Name, m_pc->m_characterInfo.characterName, sizeof(outpacket.Name));
	outpacket.Job = m_pc->m_characterInfo.job;
	outpacket.Level = m_pc->m_characterInfo.clevel;
	memcpy(outpacket.mapName, m_pc->m_characterInfo.mapName, sizeof(outpacket.mapName));
	outpacket.Option = packet.Option;
	g_characterMgr->CCharacterMgr::SendToIServer(sizeof(outpacket), (const char *)&outpacket);
}


hook_method<void (CPCPacketHandler::*)(int dx, int dy)> CPCPacketHandler::_BroadcastNewPosition(SERVER, "CPCPacketHandler::BroadcastNewPosition");
void CPCPacketHandler::BroadcastNewPosition(int dx, int dy) // line 12523-12565
{
	return (this->*_BroadcastNewPosition)(dx, dy);

	if( m_pc->CCharacter::IsBattleFieldMode() )
	{
		PACKET_ZC_BATTLEFIELD_NOTIFY_POSITION packet; memset(&packet, 0, sizeof(packet));
		packet.PacketType = HEADER_ZC_BATTLEFIELD_NOTIFY_POSITION;
		packet.accountID = m_pc->GetAccountID();
		strncpy(packet.name, m_pc->m_characterInfo.characterName, 24);
		packet.job = m_pc->m_characterInfo.job;
		packet.x = dx;
		packet.y = dy;

		reinterpret_cast<CBattleFieldMapRes*>(m_pc->m_mapRes)->CBattleFieldMapRes::BroadcastToCamp(m_pc->GetCampID(), sizeof(packet), (char *)&packet);
	}
	else if( m_pc->CPC::isNotifyPosition(dx, dy) == 1 )
	{
		if( m_pc->m_characterInfo.GroupID != 0 )
			m_pc->CPC::NotifyPositionToParty(dx, dy);

		if( m_pc->m_characterInfo.GuildID != 0 )
			m_pc->CPC::NotifyPositionToGuild(dx, dy);
	}
}


hook_method<void (CPCPacketHandler::*)(const PACKET_CZ_MER_COMMAND* in_pPacket)> CPCPacketHandler::_OnMercenary_Command(SERVER, "CPCPacketHandler::OnMercenary_Command");
void CPCPacketHandler::OnMercenary_Command(const PACKET_CZ_MER_COMMAND* in_pPacket)
{
	return (this->*_OnMercenary_Command)(in_pPacket);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(const PACKET_CZ_REQUEST_ACTNPC* in_pPacket)> CPCPacketHandler::_OnMercenary_RequestActNpc(SERVER, "CPCPacketHandler::OnMercenary_RequestActNpc");
void CPCPacketHandler::OnMercenary_RequestActNpc(const PACKET_CZ_REQUEST_ACTNPC* in_pPacket)
{
	return (this->*_OnMercenary_RequestActNpc)(in_pPacket);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(const unsigned short in_SKID, const short in_selectedLevel, unsigned long in_targetID)> CPCPacketHandler::_OnMercenary_UseSkill(SERVER, "CPCPacketHandler::OnMercenary_UseSkill");
void CPCPacketHandler::OnMercenary_UseSkill(const unsigned short in_SKID, const short in_selectedLevel, unsigned long in_targetID)
{
	return (this->*_OnMercenary_UseSkill)(in_SKID, in_selectedLevel, in_targetID);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(const PACKET_CZ_USE_SKILL_TOGROUND& in_Packet)> CPCPacketHandler::_OnMercenary_UseSkill_ToGround(SERVER, "CPCPacketHandler::OnMercenary_UseSkill_ToGround");
void CPCPacketHandler::OnMercenary_UseSkill_ToGround(const PACKET_CZ_USE_SKILL_TOGROUND& in_Packet)
{
	return (this->*_OnMercenary_UseSkill_ToGround)(in_Packet);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(const PACKET_CZ_PARTY_JOIN_REQ& in_packet)> CPCPacketHandler::_OnCZ_PARTY_JOIN_REQ(SERVER, "CPCPacketHandler::OnCZ_PARTY_JOIN_REQ");
void CPCPacketHandler::OnCZ_PARTY_JOIN_REQ(const PACKET_CZ_PARTY_JOIN_REQ& in_packet) // line 1160-1198
{
	return (this->*_OnCZ_PARTY_JOIN_REQ)(in_packet);

	if( m_pc->m_characterInfo.GroupID == 0 ||
		m_pc->m_characterInfo.isGroupMaster == 0 )
		return; // not party owner

	char TargetCharName[24]; memcpy(TargetCharName, in_packet.characterName, sizeof(TargetCharName));
	TargetCharName[countof(TargetCharName) - 1] = '\0';

	CPC* targetPC = g_characterMgr->CCharacterMgr::FindCharacter(TargetCharName);
	if( targetPC != NULL )
	{
		if( targetPC->m_characterInfo.Party.Bit.bRefuseJoinMsg == 1 )
		{
			Sned_PACKET_ZC_PARTY_JOIN_REQ_ACK(m_pc, TargetCharName, PACKET_ZC_PARTY_JOIN_REQ_ACK::ANSWER_JOINMSG_REFUSE);
			return; // target auto-refused
		}
		if( targetPC->m_characterInfo.GroupID != 0 )
		{
			Sned_PACKET_ZC_PARTY_JOIN_REQ_ACK(m_pc, TargetCharName, PACKET_ZC_PARTY_JOIN_REQ_ACK::ANSWER_ALREADY_OTHERGROUPM);
			return; // target already in a party
		}
		if( targetPC->IsItPossible(MAPPROPERTY_NO_PARTY_FORMATION) == 1 )
		{
			Sned_PACKET_ZC_PARTY_JOIN_REQ_ACK(m_pc, TargetCharName, PACKET_ZC_PARTY_JOIN_REQ_ACK::ANSWER_INVALID_MAPPROPERTY);
			return; // target can't join party in this map
		}
	}

	PACKET_ZI_PARTY_JOIN_REQ packet;
	packet.senderAID = 0;
	packet.GRID = 0;
	memset(packet.TargetCharName, 0, sizeof(packet.TargetCharName));

	packet.PacketType = HEADER_ZI_PARTY_JOIN_REQ;
	packet.senderAID = m_pc->GetAccountID();
	packet.GRID = m_pc->m_characterInfo.GroupID;
	memcpy(packet.TargetCharName, TargetCharName, sizeof(packet.TargetCharName));
	g_characterMgr->CCharacterMgr::SendToIServer(sizeof(packet), (const char *)&packet);
}


hook_method<void (CPCPacketHandler::*)(const PACKET_CZ_PARTY_CONFIG& in_packet)> CPCPacketHandler::_OnCZ_PARTY_CONFIG(SERVER, "CPCPacketHandler::OnCZ_PARTY_CONFIG");
void CPCPacketHandler::OnCZ_PARTY_CONFIG(const PACKET_CZ_PARTY_CONFIG& in_packet)
{
	return (this->*_OnCZ_PARTY_CONFIG)(in_packet);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(const PACKET_CZ_PARTY_JOIN_REQ_ACK& in_packet)> CPCPacketHandler::_OnCZ_PARTY_JOIN_REQ_ACK(SERVER, "CPCPacketHandler::OnCZ_PARTY_JOIN_REQ_ACK");
void CPCPacketHandler::OnCZ_PARTY_JOIN_REQ_ACK(const PACKET_CZ_PARTY_JOIN_REQ_ACK& in_packet)
{
	return (this->*_OnCZ_PARTY_JOIN_REQ_ACK)(in_packet);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(const PACKET_CZ_MEMORIALDUNGEON_COMMAND& in_packet)> CPCPacketHandler::_OnCZ_MEMORIALDUNGEON_COMMAND(SERVER, "CPCPacketHandler::OnCZ_MEMORIALDUNGEON_COMMAND");
void CPCPacketHandler::OnCZ_MEMORIALDUNGEON_COMMAND(const PACKET_CZ_MEMORIALDUNGEON_COMMAND& in_packet)
{
	return (this->*_OnCZ_MEMORIALDUNGEON_COMMAND)(in_packet);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(const PACKET_CZ_EQUIPWIN_MICROSCOPE& in_packet)> CPCPacketHandler::_OnCZ_EQUIPWIN_MICROSCOPE(SERVER, "CPCPacketHandler::OnCZ_EQUIPWIN_MICROSCOPE");
void CPCPacketHandler::OnCZ_EQUIPWIN_MICROSCOPE(const PACKET_CZ_EQUIPWIN_MICROSCOPE& in_packet)
{
	return (this->*_OnCZ_EQUIPWIN_MICROSCOPE)(in_packet);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(const PACKET_CZ_CONFIG& in_packet)> CPCPacketHandler::_OnCZ_CONFIG(SERVER, "CPCPacketHandler::OnCZ_CONFIG");
void CPCPacketHandler::OnCZ_CONFIG(const PACKET_CZ_CONFIG& in_packet)
{
	return (this->*_OnCZ_CONFIG)(in_packet);

	//TODO
}


hook_method<void (CPCPacketHandler::*)(const PACKET_CZ_REQ_LEAVE_GROUP& in_packet)> CPCPacketHandler::_OnCZ_REQ_LEAVE_GROUP(SERVER, "CPCPacketHandler::OnCZ_REQ_LEAVE_GROUP");
void CPCPacketHandler::OnCZ_REQ_LEAVE_GROUP(const PACKET_CZ_REQ_LEAVE_GROUP& in_packet)
{
	return (this->*_OnCZ_REQ_LEAVE_GROUP)(in_packet);

	//TODO
}


hook_method<void (__cdecl *)(CPC*const in_pToPlayer, const char* in_pTargetCharName, enum PACKET_ZC_PARTY_JOIN_REQ_ACK::enumAnswer in_Answer)> _Sned_PACKET_ZC_PARTY_JOIN_REQ_ACK(SERVER, "Sned_PACKET_ZC_PARTY_JOIN_REQ_ACK");
void __cdecl Sned_PACKET_ZC_PARTY_JOIN_REQ_ACK(CPC*const in_pToPlayer, const char* in_pTargetCharName, enum PACKET_ZC_PARTY_JOIN_REQ_ACK::enumAnswer in_Answer) // line 1150-1156
{
	return (_Sned_PACKET_ZC_PARTY_JOIN_REQ_ACK)(in_pToPlayer, in_pTargetCharName, in_Answer);

	PACKET_ZC_PARTY_JOIN_REQ_ACK packet;
	memset(packet.characterName, 0, sizeof(packet.characterName));
	packet.answer = static_cast<enum PACKET_ZC_PARTY_JOIN_REQ_ACK::enumAnswer>(0);

	packet.PacketType = HEADER_ZC_PARTY_JOIN_REQ_ACK;
	memcpy(packet.characterName, in_pTargetCharName, sizeof(packet.characterName));
	packet.answer = in_Answer;
	in_pToPlayer->CPC::Send(sizeof(packet), (char *)&packet);
}
