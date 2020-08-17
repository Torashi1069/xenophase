#include "CharacterMgr.h"
#include "CUserBlockMgr.h"
#include "Enum.h"
#include "ExpParameter.h"
#include "GVar.h"
#include "ISvrIOPacketHandler.h"
#include "ObjectRecycleMgr.h"
#include "PC.h"
#include "PCPacketHandler.h"
#include "SkillTypeInfo.h"
#include "SkillTypeInfoMgr.h"
#include "ZoneProcess.h"
#include "ZoneProcessStuff.h"
#include "ZoneScript.h"
#include "AsyncDBWork/NAsyncDBMgr.h"
#include "AsyncDBWork/SaveAllADBWork.h"
#include "Client/InterServerClient/C2InterServerClient.h"
#include "Common/Packet.h"
#include "Common/PacketLengthExMgr.h"
#include "shared/NCriticalErrorLog.h"
#include "shared/shared.h"


CPCPacketHandler::CPCPacketHandler()
{
}


CPCPacketHandler::~CPCPacketHandler()
{
}


void CPCPacketHandler::SetMyOwner(CPC* pc)
{
	m_pc = pc;
}


void CPCPacketHandler::Init()
{
	m_pc = NULL;
	m_RequestNpcTime = 0;
	m_csAuth.CCSAuth::Init();
	m_bLockCashPoint = FALSE;
}


void CPCPacketHandler::OnRecvOverflow(int byteTransferred)
{
}


void CPCPacketHandler::OnRecv(int byteTransferred)
{
}


void CPCPacketHandler::AddSendBytes(int len)
{
	m_pc->m_characterInfo.sendBytes += len;
}


void CPCPacketHandler::OnClose()
{
	if( m_pc->CPC::IsDisconnectable() || m_pc->m_pcClientUpdater.m_disconnectType == MOVE_SERVER )
	{
		m_pc->AddErrorCnt(__FILE__, __LINE__, 65535, timeGetTime() - 4000);
	}
	else
	{
		m_pc->AddErrorCnt(__FILE__, __LINE__, 65535, timeGetTime());
	}
}


int CPCPacketHandler::OnProcess()
{
	if( m_recvQueue->CPacketQueue::GetSize() < 2 )
		return -1;

	int Header = 0;
	m_recvQueue->CPacketQueue::PeekData(2, (char*)&Header);

	std::pair<CPacketLengthExMgr::enumFixedPacketRet,int> fpRet = g_packetLenMapEx.CPacketLengthExMgr::IsFixedPacket(Header);

	unsigned short size;
	if( fpRet.first == CPacketLengthExMgr::FIXED )
	{
		size = fpRet.second;
	}
	else
	if( fpRet.first == CPacketLengthExMgr::VARIABLE )
	{
		if( m_recvQueue->CPacketQueue::GetSize() < 4 )
			return -1;

		int Header = 0;
		m_recvQueue->CPacketQueue::PeekData(4, (char*)&Header);

		size = Header >> 16;
		if( size < fpRet.second )
		{
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "variable packet size minimum guarantee. header(%d) packetSize(%d) min(%d) AID(%d),GID(%d)", Header, size, fpRet.second, m_pc->GetAccountID(), m_pc->CPC::GetCharacterID());
			m_pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
			return 0;
		}
	}
	else
	{
		m_pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
		return 0;
	}

	if( size >= 3000 )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "Packet Size %d OnProcess", size);
		m_pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
		return 0;
	}

	m_pc->m_characterInfo.recvBytes += size;

	if( m_recvQueue->CPacketQueue::GetSize() < size )
		return -1;
	
	int Type = this->CPCPacketHandler::DispatchPacket(Header, size);
	if( Type == -1 )
		return -1;

	return Type;
}


int CPCPacketHandler::DispatchPacket(short Header, int packetSize) // 2252-4818
{
	if( m_pc->m_isMapLoading )
	{
		if( Header != HEADER_CZ_NOTIFY_ACTORINIT
		 && Header != HEADER_CZ_LESSEFFECT
		 && Header != HEADER_CZ_REQ_REMAINTIME
		 && Header != HEADER_CZ_SRPACKETR2_START
		 && Header != HEADER_CZ_SRCRYPTOR2_START
		 && Header != HEADER_CZ_SRPACKET_START
		 && Header != HEADER_CZ_REQUEST_MOVETOOWNER
		 || Header == HEADER_CZ_REQUEST_TIME
		 || Header == HEADER_CZ_REQUEST_TIME2 )
		{
			++m_pc->m_invalidPacket;
			if( m_pc->m_invalidPacket > 10 )
				m_pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
		}
	}

	if( m_pc->CPC::IsValid() )
	{
		if( Header == HEADER_CZ_ENTER
		 || Header == HEADER_CZ_ENTER2 )
		{
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "Dispatch Packet Fail Second");
			m_pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
			return 0;
		}
	}

	if( !m_pc->CPC::IsValid() )
	{
		if( Header != HEADER_CZ_ENTER
		 && Header != HEADER_CZ_ENTER2
		 && Header != HEADER_CZ_REQUEST_TIME
		 && Header != HEADER_CZ_REQUEST_TIME2
		 && Header != HEADER_CZ_REQUEST_MOVE
		 && Header != HEADER_CZ_REQUEST_MOVE2
		 && Header != HEADER_CZ_REQNAME
		 && Header != HEADER_CZ_REQNAME2
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
	}

	if( m_pc->m_pcClientUpdater.m_disconnectType == MOVE_SERVER || m_pc->m_pcClientUpdater.m_disconnectType == RESTART_HSERVER )
	{
		if( Header != HEADER_CZ_REQUEST_TIME
		 && Header != HEADER_CZ_REQUEST_TIME2
		 && Header != HEADER_CZ_REQUEST_MOVE
		 && Header != HEADER_CZ_REQUEST_MOVE2
		 && Header != HEADER_CZ_REQNAME
		 && Header != HEADER_CZ_REQNAME2
		 && Header != HEADER_CZ_REQ_GUILD_EMBLEM_IMG
		 && Header != HEADER_CZ_CHANGE_DIRECTION
		 && Header != HEADER_CZ_CHANGE_DIRECTION2
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

			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "Dispatch Packet Fail : Name :%s, disconnectType  %d", m_pc->m_characterInfo.characterName, m_pc->m_pcClientUpdater.m_disconnectType);
		}
	}

	m_pc->m_characterTimeInfo.lastPacketArrivedTime = timeGetTime();

	if( m_pc->GetErrorCount() >= 4 )
		return 0;

	switch( Header )
	{
	case 2311: // HEADER_CZ_INVENTORY_TAB
	{// 2371-2374
		PACKET_CZ_INVENTORY_TAB packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CPCPacketHandler::OnCZ_INVENTORY_TAB(packet);
	}
	break;
	case 2037: // HEADER_CZ_GM_FULLSTRIP
	{// 2488-2491
		PACKET_CZ_GM_FULLSTRIP packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

		if( !g_zoneScript.CZoneScript::SearchID(const_cast<char*>(m_pc->CPC::GetAccountName()), CHECK_MOVEAID) )
			break;

		this->CPCPacketHandler::OnCZ_GM_FULLSTRIP(packet);
	}
	break;
	case 2020: // HEADER_CZ_ITEMLISTWIN_RES
	{// 2497-2508
		PACKET_CZ_ITEMLISTWIN_RES* pCZ_ITEMLISTWIN_RES = reinterpret_cast<PACKET_CZ_ITEMLISTWIN_RES*>(_malloca(packetSize));
		m_recvQueue->CPacketQueue::GetData(packetSize, (char*)pCZ_ITEMLISTWIN_RES);
		this->CPCPacketHandler::OnCZ_ITEMLISTWIN_RES((unsigned char*)pCZ_ITEMLISTWIN_RES, packetSize);
		_freea(pCZ_ITEMLISTWIN_RES);
	}
	break;
	case 1095: // HEADER_CZ_BLOCKING_PLAY_CANCEL
	{// 2513-2516
		PACKET_CZ_BLOCKING_PLAY_CANCEL packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
	}
	break;
	case 1091: // HEADER_CZ_SKILL_SELECT_RESPONSE
	{// 2520-2523
		PACKET_CZ_SKILL_SELECT_RESPONSE packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CPCPacketHandler::OnCZ_SKILL_SELECT_RESPONSE(packet);
	}
	break;
	case 728: // HEADER_CZ_CONFIG
	{// 2527-2530
		PACKET_CZ_CONFIG packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CPCPacketHandler::OnCZ_CONFIG(packet);
	}
	break;
	case 726: // HEADER_CZ_EQUIPWIN_MICROSCOPE
	{// 2536-2539
		PACKET_CZ_EQUIPWIN_MICROSCOPE packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CPCPacketHandler::OnCZ_EQUIPWIN_MICROSCOPE(packet);
	}
	break;
	case 719: // HEADER_CZ_MEMORIALDUNGEON_COMMAND
	{// 2545-2548
		PACKET_CZ_MEMORIALDUNGEON_COMMAND packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CPCPacketHandler::OnCZ_MEMORIALDUNGEON_COMMAND(packet);
	}
	break;
	case 711: // HEADER_CZ_PARTY_JOIN_REQ_ACK
	{// 2553-2556
		PACKET_CZ_PARTY_JOIN_REQ_ACK packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CPCPacketHandler::OnCZ_PARTY_JOIN_REQ_ACK(packet);
	}
	break;
	case 712: // HEADER_CZ_PARTY_CONFIG
	{// 2561-2564
		PACKET_CZ_PARTY_CONFIG packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CPCPacketHandler::OnCZ_PARTY_CONFIG(packet);
	}
	break;
	case 708: // HEADER_CZ_PARTY_JOIN_REQ
	{// 2570-2573
		PACKET_CZ_PARTY_JOIN_REQ packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CPCPacketHandler::OnCZ_PARTY_JOIN_REQ(packet);
	}
	break;
	case 671: // HEADER_CZ_MER_COMMAND
	{// 2621-2624
		PACKET_CZ_MER_COMMAND Packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char*)&Packet);
		this->CPCPacketHandler::OnMercenary_Command(&Packet);
	}
	break;
	case 140: // HEADER_CZ_REQUEST_CHAT
	{// 2654-2665
		PACKET_CZ_REQUEST_CHAT* pCZ_REQUEST_CHAT = reinterpret_cast<PACKET_CZ_REQUEST_CHAT*>(_malloca(packetSize));
		m_recvQueue->CPacketQueue::GetData(packetSize, (char*)pCZ_REQUEST_CHAT);
		this->CPCPacketHandler::OnChat(pCZ_REQUEST_CHAT);
		_freea(pCZ_REQUEST_CHAT);
	}
	break;
	case 1078: // HEADER_CZ_ENTER2
	{// 2669-2673
		PACKET_CZ_ENTER2 packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CPCPacketHandler::OnEnter(packet.AID, packet.GID, packet.AuthCode, packet.clientTime, packet.Sex);
	}
	break;
	case 114: // HEADER_CZ_ENTER
	{// ????-????
		PACKET_CZ_ENTER cz_enter;
		m_recvQueue->CPacketQueue::GetData(sizeof(cz_enter), (char*)&cz_enter);
		this->CPCPacketHandler::OnEnter(cz_enter.AID, cz_enter.GID, cz_enter.AuthCode, cz_enter.clientTime, cz_enter.Sex);
	}
	break;
	case 144: // HEADER_CZ_CONTACTNPC
	{// 2691-2697
		PACKET_CZ_CONTACTNPC packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CPCPacketHandler::OnCZ_CONTACTNPC(packet);
	}
	break;
	case 150: // HEADER_CZ_WHISPER
	{// 2699-2700
		this->CPCPacketHandler::OnWhisper(packetSize);
	}
	break;
	case 10513: // HEADER_CONNECTION_CLOSED
	{// 2704-2705
		PACKET_CONNECTION_CLOSED packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		return packet.Type; // NOTE: unusual
	}
	break;
	case 864: // HEADER_CZ_REQUEST_TIME2
	{// 2711-2714
		PACKET_CZ_REQUEST_TIME2 packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CPCPacketHandler::OnRequestTime(packet.clientTime);
	}
	break;
	case 126: // HEADER_CZ_REQUEST_TIME
	{// 2719-2727
		PACKET_CZ_REQUEST_TIME packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		m_pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
		this->CPCPacketHandler::OnRequestTime(packet.clientTime);
	}
	break;
	case 125: // HEADER_CZ_NOTIFY_ACTORINIT
	{// 2729-2730
		this->CPCPacketHandler::OnActorInit(packetSize);
	}
	break;
	case 872: // HEADER_CZ_REQNAME2
	{// 2735-2738
		PACKET_CZ_REQNAME2 packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CPCPacketHandler::OnReqName(packet.AID);
	}
	break;
	case 148: // HEADER_CZ_REQNAME
	{// 2743-2751
		PACKET_CZ_REQNAME packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		m_pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
		this->CPCPacketHandler::OnReqName(packet.AID);
	}
	break;
	case 153: // HEADER_CZ_BROADCAST
	{// 2753-2754
		this->CPCPacketHandler::OnBroadCast(packetSize);
	}
	break;
	case 412: // HEADER_CZ_LOCALBROADCAST
	{// 2756-2757
		this->CPCPacketHandler::OnLocalBroadCast(packetSize);
	}
	break;
	case 865: // HEADER_CZ_CHANGE_DIRECTION2
	{// 2761-2764
		PACKET_CZ_CHANGE_DIRECTION2 packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CPCPacketHandler::OnChangeDir(packet.headDir, packet.dir);
	}
	break;
	case 155: // HEADER_CZ_CHANGE_DIRECTION
	{// 2768-2776
		PACKET_CZ_CHANGE_DIRECTION packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		m_pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
		this->CPCPacketHandler::OnChangeDir(packet.headDir, packet.dir);
	}
	break;
	case 204: // HEADER_CZ_DISCONNECT_CHARACTER
	{// 2778-2779
		this->CPCPacketHandler::OnDisconnectCharacter(packetSize);
	}
	break;
	case 206: // HEADER_CZ_DISCONNECT_ALL_CHARACTER
	{// 2781-2782
		this->CPCPacketHandler::OnDisconnectAllCharacter(packetSize);
	}
	break;
	case 1079: // HEADER_CZ_REQUEST_ACT2
	{// 2786-2789
		PACKET_CZ_REQUEST_ACT2 packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CPCPacketHandler::OnReqAct2(packet.targetGID, packet.action, true);
	}
	break;
	case 137: // HEADER_CZ_REQUEST_ACT
	{// 2791-2792
		this->CPCPacketHandler::OnReqAct1(packetSize, NULL);
	}
	break;
	case 867: // HEADER_CZ_ITEM_THROW2
	{// 2820-2823
		PACKET_CZ_ITEM_THROW2 packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CPCPacketHandler::OnThrowItem(packet.Index, packet.count);
	}
	break;
	case 162: // HEADER_CZ_ITEM_THROW
	{// 2828-2836
		PACKET_CZ_ITEM_THROW packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		m_pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
		this->CPCPacketHandler::OnThrowItem(packet.Index, packet.count);
	}
	break;
	case 1081: // HEADER_CZ_USE_ITEM2
	{// 2841-2844
		PACKET_CZ_USE_ITEM2 packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CPCPacketHandler::OnUseItem2(packet.index, packet.AID);
	}
	break;
	case 167: // HEADER_CZ_USE_ITEM
	{// 2864-2865
		this->CPCPacketHandler::OnUseItem(packetSize);
	}
	break;
	case 169: // HEADER_CZ_REQ_WEAR_EQUIP
	{// 2872-2873
		this->CPCPacketHandler::OnWearEquip(packetSize);
	}
	break;
	case 171: // HEADER_CZ_REQ_TAKEOFF_EQUIP
	{// 2879-2881
		this->CPCPacketHandler::OnTakeOffEquip(packetSize);
	}
	break;
	case 173: // HEADER_CZ_REQ_ITEM_EXPLANATION_BYNAME
	{// 2883-2884
		this->CPCPacketHandler::OnItemExplanationByName(packetSize);
	}
	break;
	case 184: // HEADER_CZ_CHOOSE_MENU
	{// 2886-2887
		this->CPCPacketHandler::OnChooseMenu(packetSize);
	}
	break;
	case 185: // HEADER_CZ_REQ_NEXT_SCRIPT
	{// 2889-2890
		this->CPCPacketHandler::OnReqNextScript(packetSize);
	}
	break;
	case 178: // HEADER_CZ_RESTART
	{// 2892-2893
		this->CPCPacketHandler::OnRestart(packetSize);
	}
	break;
	case 187: // HEADER_CZ_STATUS_CHANGE
	{// 2898-2904
		PACKET_CZ_STATUS_CHANGE packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CPCPacketHandler::OnStatusChange(packet);
	}
	break;
	case 191: // HEADER_CZ_REQ_EMOTION
	{// 2906-2907
		this->CPCPacketHandler::OnReqEmotion(packetSize);
	}
	break;
	case 193: // HEADER_CZ_REQ_USER_COUNT
	{// 2909-2910
		this->CPCPacketHandler::OnReqUserCount(packetSize);
	}
	break;
	case 197: // HEADER_CZ_ACK_SELECT_DEALTYPE
	{// 2920-2921
		this->CPCPacketHandler::OnSelectDealType(packetSize);
	}
	break;
	case 200: // HEADER_CZ_PC_PURCHASE_ITEMLIST
	{// 2923-2924
		this->CPCPacketHandler::OnPurchaseItem(packetSize);
	}
	break;
	case 201: // HEADER_CZ_PC_SELL_ITEMLIST
	{// 2929-2953
		if( packetSize >= 4 + 512 )
		{
			m_pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
			break;
		}

		PACKET_CZ_PC_SELL_ITEMLIST* pCZ_PC_SELL_ITEMLIST = reinterpret_cast<PACKET_CZ_PC_SELL_ITEMLIST*>(_malloca(packetSize));
		m_recvQueue->CPacketQueue::GetData(packetSize, (char*)pCZ_PC_SELL_ITEMLIST);
		this->CPCPacketHandler::OnCZ_PC_SELL_ITEMLIST(pCZ_PC_SELL_ITEMLIST);
		_freea(pCZ_PC_SELL_ITEMLIST);
	}
	break;
	case 207: // HEADER_CZ_SETTING_WHISPER_PC
	{// 2955-2956
		this->CPCPacketHandler::OnSettingWhisperPC(packetSize);
	}
	break;
	case 208: // HEADER_CZ_SETTING_WHISPER_STATE
	{// 2958-2959
		this->CPCPacketHandler::OnSettingWhisperState(packetSize);
	}
	break;
	case 211: // HEADER_CZ_REQ_WHISPER_LIST
	{// 2961-2962
		this->CPCPacketHandler::OnReqWhisperList(packetSize);
	}
	break;
	case 213: // HEADER_CZ_CREATE_CHATROOM
	{// 2964-2965
		this->CPCPacketHandler::OnCreateChatRoom(packetSize);
	}
	break;
	case 217: // HEADER_CZ_REQ_ENTER_ROOM
	{// 2967-2968
		this->CPCPacketHandler::OnReqEnterRoom(packetSize);
	}
	break;
	case 222: // HEADER_CZ_CHANGE_CHATROOM
	{// 2970-2971
		this->CPCPacketHandler::OnChangeChatRoom(packetSize);
	}
	break;
	case 224: // HEADER_CZ_REQ_ROLE_CHANGE
	{// 2973-2974
		this->CPCPacketHandler::OnReqChangeRole(packetSize);
	}
	break;
	case 226: // HEADER_CZ_REQ_EXPEL_MEMBER
	{// 2976-2977
		this->CPCPacketHandler::OnReqExpelMember(packetSize);
	}
	break;
	case 227: // HEADER_CZ_EXIT_ROOM
	{// 2979-2980
		this->CPCPacketHandler::OnExitRoom(packetSize);
	}
	break;
	case 228: // HEADER_CZ_REQ_EXCHANGE_ITEM
	{// 2982-2983
		this->CPCPacketHandler::OnReqExchangeItem(packetSize);
	}
	break;
	case 230: // HEADER_CZ_ACK_EXCHANGE_ITEM
	{// 2985-2986
		this->CPCPacketHandler::OnAckReqExchangeItem(packetSize);
	}
	break;
	case 239: // HEADER_CZ_EXEC_EXCHANGE_ITEM
	{// 2988-2989
		this->CPCPacketHandler::OnExecExchangeItem(packetSize);
	}
	break;
	case 232: // HEADER_CZ_ADD_EXCHANGE_ITEM
	{// 2991-2992
		this->CPCPacketHandler::OnAddExchangeItem(packetSize);
	}
	break;
	case 235: // HEADER_CZ_CONCLUDE_EXCHANGE_ITEM
	{// 2994-2995
		this->CPCPacketHandler::OnConcludeExchangeItem(packetSize);
	}
	break;
	case 237: // HEADER_CZ_CANCEL_EXCHANGE_ITEM
	{// 2997-2998
		this->CPCPacketHandler::OnCancelExchangeItem(packetSize);
	}
	break;
	case 868: // HEADER_CZ_MOVE_ITEM_FROM_BODY_TO_STORE2
	{// 3002-3005
		PACKET_CZ_MOVE_ITEM_FROM_BODY_TO_STORE2 packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CPCPacketHandler::OnMoveItemFromBodyToStore(packet.index, packet.count);
	}
	break;
	case 243: // HEADER_CZ_MOVE_ITEM_FROM_BODY_TO_STORE
	{// 3010-3018
		PACKET_CZ_MOVE_ITEM_FROM_BODY_TO_STORE packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		m_pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
		this->CPCPacketHandler::OnMoveItemFromBodyToStore(packet.index, packet.count);
	}
	break;
	case 869: // HEADER_CZ_MOVE_ITEM_FROM_STORE_TO_BODY2
	{// 3023-3026
		PACKET_CZ_MOVE_ITEM_FROM_STORE_TO_BODY2 packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CPCPacketHandler::OnMoveItemFromStoreToBody(packet.index, packet.count);
	}
	break;
	case 245: // HEADER_CZ_MOVE_ITEM_FROM_STORE_TO_BODY
	{// 3031-3039
		PACKET_CZ_MOVE_ITEM_FROM_STORE_TO_BODY packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		m_pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
		this->CPCPacketHandler::OnMoveItemFromStoreToBody(packet.index, packet.count);
	}
	break;
	case 294: // HEADER_CZ_MOVE_ITEM_FROM_BODY_TO_CART
	{// 3041-3042
		this->CPCPacketHandler::OnMoveItemFromBodyToCart(packetSize);
	}
	break;
	case 295: // HEADER_CZ_MOVE_ITEM_FROM_CART_TO_BODY
	{// 3044-3045
		this->CPCPacketHandler::OnMoveItemFromCartToBody(packetSize);
	}
	break;
	case 296: // HEADER_CZ_MOVE_ITEM_FROM_STORE_TO_CART
	{// 3047-3048
		this->CPCPacketHandler::OnMoveItemFromStoreToCart(packetSize);
	}
	break;
	case 297: // HEADER_CZ_MOVE_ITEM_FROM_CART_TO_STORE
	{// 3050-3051
		this->CPCPacketHandler::OnMoveItemFromCartToStore(packetSize);
	}
	break;
	case 247: // HEADER_CZ_CLOSE_STORE
	{// 3053-3054
		this->CPCPacketHandler::OnCloseStore(packetSize);
	}
	break;
	case 488: // HEADER_CZ_MAKE_GROUP2
	{// 3054-3055
		this->CPCPacketHandler::OnMakeGroup(packetSize);
	}
	break;
	case 249: // HEADER_CZ_MAKE_GROUP
	{// 3057-3058
		this->CPCPacketHandler::OnMakeGroup(packetSize);
	}
	break;
	case 252: // HEADER_CZ_REQ_JOIN_GROUP
	{// 3060-3061
		this->CPCPacketHandler::OnReqJoinGroup(packetSize);
	}
	break;
	case 2326: // HEADER_CZ_REQ_JOIN_GUILD2
	{// 3065-3069
		PACKET_CZ_REQ_JOIN_GUILD2 packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CPCPacketHandler::OnCZ_REQ_JOIN_GUILD2(packet);
	}
	break;
	case 255: // HEADER_CZ_JOIN_GROUP
	{// 3078-3079
		this->CPCPacketHandler::OnJoinGroup(packetSize);
	}
	break;
	case 256: // HEADER_CZ_REQ_LEAVE_GROUP
	{// 3087-3090
		PACKET_CZ_REQ_LEAVE_GROUP packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CPCPacketHandler::OnCZ_REQ_LEAVE_GROUP(packet);
	}
	break;
	case 259: // HEADER_CZ_REQ_EXPEL_GROUP_MEMBER
	{// 3101-3102
		this->CPCPacketHandler::OnReqExpelGroupMember(packetSize);
	}
	break;
	case 264: // HEADER_CZ_REQUEST_CHAT_PARTY
	{// 3104-3105
		this->CPCPacketHandler::OnChatParty(packetSize);
	}
	break;
	case 274: // HEADER_CZ_UPGRADE_SKILLLEVEL
	{// 3108-3109
		this->CPCPacketHandler::OnUpgradeSkillLevel(packetSize);
	}
	break;
	case 280: // HEADER_CZ_CANCEL_LOCKON
	{// 3233-3234
		this->CPCPacketHandler::OnCancelLockOn(packetSize);
	}
	break;
	case 283: // HEADER_CZ_SELECT_WARPPOINT
	{// 3266-3267
		this->CPCPacketHandler::OnSelectWarpPoint(packetSize);
	}
	break;
	case 285: // HEADER_CZ_REMEMBER_WARPPOINT
	{// 3269-3270
		this->CPCPacketHandler::OnRememberWarpPoint(packetSize);
	}
	break;
	case 298: // HEADER_CZ_REQ_CARTOFF
	{// 3272-3273
		this->CPCPacketHandler::OnCartOff(packetSize);
	}
	break;
	case 302: // HEADER_CZ_REQ_CLOSESTORE
	{// 3275-3276
		this->CPCPacketHandler::OnReqCloseMCStore(packetSize);
	}
	break;
	case 303: // HEADER_CZ_REQ_OPENSTORE
	{// 3278-3279
		this->CPCPacketHandler::OnReqOpenMCStore(packetSize);
	}
	break;
	case 434: // HEADER_CZ_REQ_OPENSTORE2
	{// 3281-3282
		this->CPCPacketHandler::OnReqOpenMCStore2(packetSize);
	}
	break;
	case 308: // HEADER_CZ_PC_PURCHASE_ITEMLIST_FROMMC
	{// 3284-3285
		this->CPCPacketHandler::PurchaseItemFromMCStore(packetSize);
	}
	break;
	case 2049: // HEADER_CZ_PC_PURCHASE_ITEMLIST_FROMMC2
	{// 3287-3288
		this->CPCPacketHandler::PurchaseItemFromMCStore2(packetSize);
	}
	break;
	case 304: // HEADER_CZ_REQ_BUY_FROMMC
	{// 3290-3291
		this->CPCPacketHandler::OnReqItemListFromMCStore(packetSize);
	}
	break;
	case 312: // HEADER_CZ_PKMODE_CHANGE
	{// 3293-3294
		this->CPCPacketHandler::OnPKModeChange(packetSize);
	}
	break;
	case 319: // HEADER_CZ_ITEM_CREATE
	{// 3298-3301
		PACKET_CZ_ITEM_CREATE packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		packet.itemName[countof(packet.itemName)-1] = '\0';
		this->CPCPacketHandler::OnItemCreate(packet.itemName);
	}
	break;
	case 2510: // HEADER_CZ_ITEM_CREATE_EX
	{// 3306 +-
		PACKET_CZ_ITEM_CREATE_EX packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CPCPacketHandler::ON_CZ_ITEM_CREATE_EX(packet);
	}
	break;
	case 320: // HEADER_CZ_MOVETO_MAP
	{// 3312-3313
		this->CPCPacketHandler::OnAdminMapMove(packetSize);
	}
	break;
	case 323: // HEADER_CZ_INPUT_EDITDLG
	{// 3315-3316
		this->CPCPacketHandler::OnInputEditDlg(packetSize);
	}
	break;
	case 326: // HEADER_CZ_CLOSE_DIALOG
	{// 3318-3319
		this->CPCPacketHandler::OnCloseDialog(packetSize);
	}
	break;
	case 333: // HEADER_CZ_REQ_GUILD_MENUINTERFACE
	{// 3321-3322
		this->CPCPacketHandler::OnReqGuildMenuInterface(packetSize);
	}
	break;
	case 335: // HEADER_CZ_REQ_GUILD_MENU
	{// 3324-3325
		this->CPCPacketHandler::OnReqGuildMenu(packetSize);
	}
	break;
	case 337: // HEADER_CZ_REQ_GUILD_EMBLEM_IMG
	{// 3333-3336
		this->CPCPacketHandler::OnReqGuildEmblemImg(packetSize);
	}
	break;
	case 339: // HEADER_CZ_REGISTER_GUILD_EMBLEM_IMG
	{// 3338-3339
		this->CPCPacketHandler::OnRegisterGuildEmblemImg(packetSize);
	}
	break;
	case 341: // HEADER_CZ_REQ_CHANGE_MEMBERPOS
	{// 3341-3342
		this->CPCPacketHandler::OnReqChangeMemberPos(packetSize);
	}
	break;
	case 343: // HEADER_CZ_REQ_OPEN_MEMBER_INFO
	{// 3344-3345
		this->CPCPacketHandler::OnReqOpenMemberInfo(packetSize);
	}
	break;
	case 345: // HEADER_CZ_REQ_LEAVE_GUILD
	{// 3347-3348
		this->CPCPacketHandler::OnReqLeaveGuild(packetSize);
	}
	break;
	case 347: // HEADER_CZ_REQ_BAN_GUILD
	{// 3350-3351
		this->CPCPacketHandler::OnReqBanGuild(packetSize);
	}
	break;
	case 349: // HEADER_CZ_REQ_DISORGANIZE_GUILD
	{// 3353-3354
		this->CPCPacketHandler::OnReqDisorganizeGuild(packetSize);
	}
	break;
	case 353: // HEADER_CZ_REG_CHANGE_GUILD_POSITIONINFO
	{// 3356-3357
		this->CPCPacketHandler::OnReqChangeGuildPositionInfo(packetSize);
	}
	break;
	case 357: // HEADER_CZ_REQ_MAKE_GUILD
	{// 3359-3361
		this->CPCPacketHandler::OnReqMakeGuild(packetSize);
	}
	break;
	case 360: // HEADER_CZ_REQ_JOIN_GUILD
	{// 3363-3364
		this->CPCPacketHandler::OnReqJoinGuild(packetSize);
	}
	break;
	case 363: // HEADER_CZ_JOIN_GUILD
	{// 3366-3367
		this->CPCPacketHandler::OnJoinGuild(packetSize);
	}
	break;
	case 366: // HEADER_CZ_GUILD_NOTICE
	{// 3369-3370
		this->CPCPacketHandler::OnGuildNotice(packetSize);
	}
	break;
	case 382: // HEADER_CZ_GUILD_CHAT
	{// 3372-3373
		this->CPCPacketHandler::OnGuildChat(packetSize);
	}
	break;
	case 368: // HEADER_CZ_REQ_ALLY_GUILD
	{// 3375-3376
		this->CPCPacketHandler::OnReqAllyGuild(packetSize);
	}
	break;
	case 370: // HEADER_CZ_ALLY_GUILD
	{// 3380-3381
		this->CPCPacketHandler::OnAllyGuild(packetSize);
	}
	break;
	case 384: // HEADER_CZ_REQ_HOSTILE_GUILD
	{// 3383-3384
		this->CPCPacketHandler::OnReqHostileGuild(packetSize);
	}
	break;
	case 387: // HEADER_CZ_REQ_DELETE_RELATED_GUILD
	{// 3386-3387
		this->CPCPacketHandler::OnReqDeleteRelatedGuild(packetSize);
	}
	break;
	case 376: // HEADER_CZ_REQ_ITEMIDENTIFY
	{// 3391-3392
		this->CPCPacketHandler::OnReqItemIdentify(packetSize);
	}
	break;
	case 329: // HEADER_CZ_REQ_GIVE_MANNER_POINT
	{// 3398-3399
		this->CPCPacketHandler::OnGiveMannerPoint(packetSize);
	}
	break;
	case 378: // HEADER_CZ_REQ_ITEMCOMPOSITION_LIST
	{// 3401-3402
		this->CPCPacketHandler::OnReqItemCompositionList(packetSize);
	}
	break;
	case 380: // HEADER_CZ_REQ_ITEMCOMPOSITION
	{// 3404-3405
		this->CPCPacketHandler::OnReqItemComposition(packetSize);
	}
	break;
	case 509: // HEADER_CZ_REQ_ITEMREPAIR
	{// 3410-3418
		PACKET_CZ_REQ_ITEMREPAIR packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		m_pc->CPC::ReqItemRepair(packet.TargetItemInfo);
	}
	break;
	case 394: // HEADER_CZ_REQ_DISCONNECT
	{// 3421-3422
		this->CPCPacketHandler::OnReqDisconnect(packetSize);
	}
	break;
	case 398: // HEADER_CZ_REQMAKINGITEM
	{// 3424-3425
		this->CPCPacketHandler::OnReqMakingItem(packetSize);
	}
	break;
	case 871: // HEADER_CZ_USE_SKILL_TOGROUND_WITHTALKBOX2
	{// 3429-3437
		PACKET_CZ_USE_SKILL_TOGROUND_WITHTALKBOX2 packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CPCPacketHandler::OnReqUSE_SKILL_TOGROUND_WITHTALKBOX(packet.selectedLevel, packet.SKID, packet.xPos, packet.yPos, packet.contents);
	}
	break;
	case 400: // HEADER_CZ_USE_SKILL_TOGROUND_WITHTALKBOX
	{// 3442-3455
		PACKET_CZ_USE_SKILL_TOGROUND_WITHTALKBOX packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		m_pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
		this->CPCPacketHandler::OnReqUSE_SKILL_TOGROUND_WITHTALKBOX(packet.selectedLevel, packet.SKID, packet.xPos, packet.yPos, packet.contents);
	}
	break;
	case 873: // HEADER_CZ_REQNAME_BYGID2
	{// 3459-3462
		PACKET_CZ_REQNAME_BYGID2 packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CPCPacketHandler::OnReqNameByGID(packet.GID);
	}
	break;
	case 403: // HEADER_CZ_REQNAME_BYGID
	{// 3466-3474
		PACKET_CZ_REQNAME_BYGID packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		m_pc->AddErrorCnt(__FILE__, 3469, 4, timeGetTime());
		this->CPCPacketHandler::OnReqNameByGID(packet.GID);
	}
	break;
	case 407: // HEADER_CZ_RESET
	{// 3476-3477
		this->CPCPacketHandler::OnResetParameter(packetSize);
	}
	break;
	case 408: // HEADER_CZ_CHANGE_MAPTYPE
	{// 3479-3480
		this->CPCPacketHandler::OnChangeMapType(packetSize);
	}
	break;
	case 413: // HEADER_CZ_CHANGE_EFFECTSTATE
	{// 3482-3483
		this->CPCPacketHandler::OnChangeEffectState(packetSize);
	}
	break;
	case 415: // HEADER_CZ_TRYCAPTURE_MONSTER
	{// 3486-3487
		this->CPCPacketHandler::OnTryCaptureMonster(packetSize);
	}
	break;
	case 417: // HEADER_CZ_COMMAND_PET
	{// 3489-3490
		this->CPCPacketHandler::OnCommandPet(packetSize);
	}
	break;
	case 421: // HEADER_CZ_RENAME_PET
	{// 3492-3493
		this->CPCPacketHandler::OnRenamePet(packetSize);
	}
	break;
	case 561: // HEADER_CZ_RENAME_MER
	{// 3495-3496
		this->CPCPacketHandler::OnRenameHomun(packetSize);
	}
	break;
	case 423: // HEADER_CZ_SELECT_PETEGG
	{// 3498-3499
		this->CPCPacketHandler::OnSelectPetEgg(packetSize);
	}
	break;
	case 424: // HEADER_CZ_PETEGG_INFO
	{// 3501-3502
		this->CPCPacketHandler::OnPetEggInfo(packetSize);
	}
	break;
	case 425: // HEADER_CZ_PET_ACT
	{// 3504-3505
		this->CPCPacketHandler::OnPetAct(packetSize);
	}
	break;
	case 430: // HEADER_CZ_REQ_MAKINGARROW
	{// 3509-3526
		PACKET_CZ_REQ_MAKINGARROW packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

		switch( m_pc->CPC::GetPureJob() )
		{
		case JT_GUILLOTINE_CROSS:
			m_pc->CPC::GC_POISONINGWEAPONoperation(packet.id);
		break;
		case JT_MECHANIC:
			m_pc->CPC::NC_MAGICDECOY_operate(packet.id);
		break;
		case JT_WARLOCK:
			m_pc->CPC::WL_READING_SBoperation(packet.id);
		break;
		default:
			m_pc->m_pcitemInventoryMgr.CPCItemInventoryMgr::ReqMakeArrow(packet.id);
			--m_pc->m_lockCounter;
		break;
		};

	}
	break;
	case 603: // HEADER_CZ_REQ_MAKINGITEM
	{// 3529-3530
		this->CPCPacketHandler::OnMakingItem();
	}
	break;
	case 2432: // HEADER_CZ_SELECTCART
	{// 3534-3538
		PACKET_CZ_SELECTCART packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CPCPacketHandler::OnCZ_SELECTCART(packet);
	}
	break;
	case 431: // HEADER_CZ_REQ_CHANGECART
	{// 3544-3569
		PACKET_CZ_REQ_CHANGECART packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CPCPacketHandler::OnCZ_REQ_CHANGECART(packet);
	}
	break;
	case 458: // HEADER_CZ_REQMAKINGHOMUN
	{// 3575-3580
		PACKET_CZ_REQMAKINGHOMUN packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

		if( packet.result )
			m_pc->CPC::AM_ReqMakingHomun();
	}
	break;
	case 439: // HEADER_CZ_GUILD_ZENY
	{// 3585-3586
		this->CPCPacketHandler::OnGuildZeny(packetSize);
	}
	break;
	case 442: // HEADER_CZ_REMOVE_AID
	{// 3591-3597
		PACKET_CZ_REMOVE_AID Packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char*)&Packet);
		this->CPCPacketHandler::OnCZ_REMOVE_AID(Packet);
	}
	break;
	case 443: // HEADER_CZ_SHIFT
	{// 3599-3600
		this->CPCPacketHandler::OnShift(packetSize);
	}
	break;
	case 444: // HEADER_CZ_RECALL
	{// 3602-3603
		this->CPCPacketHandler::OnRecall(packetSize);
	}
	break;
	case 445: // HEADER_CZ_RECALL_GID
	{// 3605-3606
		this->CPCPacketHandler::OnRecallGID(packetSize);
	}
	break;
	case 454: // HEADER_CS_REQ_ENCRYPTION
	{// 3608-3609
		this->CPCPacketHandler::OnReqEncryption(packetSize);
	}
	break;
	case 448: // HEADER_CZ_REQ_REMAINTIME
	{// 3613-3620
		PACKET_CZ_REQ_REMAINTIME cz_req_remaintime;
		m_recvQueue->CPacketQueue::GetData(sizeof(cz_req_remaintime), (char*)&cz_req_remaintime);

		PACKET_REQ_REMAINTIME req_remaintime;
		req_remaintime.PacketType = HEADER_ZH_REQ_REMAINTIME;
		req_remaintime.AID = m_pc->GetAccountID();
		CCharacterMgr::GetObj()->CCharacterMgr::SendToHServer(sizeof(req_remaintime), (char*)&req_remaintime);
	}
	break;
	case 462: // HEADER_CZ_SELECTAUTOSPELL
	{// 3624-3625
		this->CPCPacketHandler::OnSelectAutoSpell(packetSize);
	}
	break;
	case 469: // HEADER_CZ_INPUT_EDITDLGSTR
	{// 3628-3629
		this->CPCPacketHandler::OnInputEditDlgStr(packetSize);
	}
	break;
	case 479: // HEADER_CZ_REQ_ACCOUNTNAME
	{// 3634-3648
		PACKET_CZ_REQ_ACCOUNTNAME packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

		if( !g_zoneScript.CZoneScript::SearchID(m_pc->m_characterInfo.accountName, CHECK_LOCALBROADCAST) )
			break;

		PACKET_ZC_ACK_ACCOUNTNAME outpacket = {};
		outpacket.PacketType = HEADER_ZC_ACK_ACCOUNTNAME;
		outpacket.AID = packet.AID;
		CPC* other = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(packet.AID, PC_TYPE);
		if( other != NULL )
			memcpy_s(outpacket.name, sizeof(packet.AID), other->m_characterInfo.accountName, sizeof(other->m_characterInfo.accountName));
		m_pc->Send(sizeof(outpacket), (char*)&outpacket);
	}
	break;
	case 485: // HEADER_CZ_REQ_JOIN_COUPLE
	{// 3655-3667
		PACKET_CZ_REQ_JOIN_COUPLE packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

		CPC* other = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(packet.AID, PC_TYPE);
		if( other == NULL )
			break;

		PACKET_ZC_REQ_COUPLE reqpacket;
		reqpacket.PacketType = HEADER_ZC_REQ_COUPLE;
		reqpacket.AID = m_pc->GetAccountID();
		reqpacket.GID = m_pc->CPC::GetCharacterID();
		memcpy_s(reqpacket.name, sizeof(reqpacket.name), m_pc->m_characterInfo.characterName, sizeof(m_pc->m_characterInfo.characterName));
		other->Send(sizeof(reqpacket), (char*)&reqpacket);
	}
	break;
	case 483: // HEADER_CZ_JOIN_COUPLE
	{// 3673-3682
		PACKET_CZ_JOIN_COUPLE packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

		CPC* other = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(packet.AID, PC_TYPE);
		if( other == NULL || packet.answer == 0 || m_pc->m_marriageInfo.bMarried )
			break;

		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, m_pc, CM_GETMARRIED, other->CPC::GetCharacterID(), 0, 0, 0);
	}
	break;
	case 487: // HEADER_CZ_DORIDORI
	{// 3690-3734
		PACKET_CZ_DORIDORI packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

		if( m_pc->GetState() != CHARACTER_STATE_SIT )
			break;

		int job = CPC::GetCategorySecondJob(m_pc->m_characterInfo.job);
		if( job == JT_SUPERNOVICE )
		{
			m_pc->m_specialSP = 1;
		}
		else
		if( g_skillTypeInfoMgr.CSkillTypeInfoMgr::IsAvailableJob(m_pc->m_characterInfo.job, SKID_TK_HPTIME) )
		{
			if( m_pc->m_specialSP != 1 && job == JT_STAR && GetServerRandom(0, 20000) % 5000 == 27 )
			{
				m_pc->m_pcSkill.CPCSkill::UpdateStarPlace("", 100);
				m_pc->OnShowEffect(582); //TODO: client's EF_ANGEL3

				PACKET_ZC_STARSKILL outpacket;
				outpacket.PacketType = HEADER_ZC_STARSKILL;
				outpacket.mapName[0] = '\0';
				outpacket.monsterID = 0;
				outpacket.star = 0;
				outpacket.result = 30; // angel
				m_pc->Send(sizeof(outpacket), (char*)&outpacket);
			}

			m_pc->m_specialSP = 1;
		}
	}
	break;
	case 493: // HEADER_CZ_CHOPOKGI
	{// 3742-3745
		PACKET_CZ_CHOPOKGI packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CPCPacketHandler::OnCZ_CHOPOKGI(packet);
	}
	break;
	case 505: // HEADER_CZ_REQ_JOIN_BABY
	{// 3773-3815
		PACKET_CZ_REQ_JOIN_BABY packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

		CPC* partner = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindPCByGID(m_pc->m_marriageInfo.partnerGID);
		if( m_pc->m_familyInfo.familyIndex != 0 || partner != NULL && partner->m_familyInfo.familyIndex != 0 )
		{
			PACKET_ZC_BABYMSG msg;
			msg.PacketType = HEADER_ZC_BABYMSG;
			msg.MsgNo = 0;
			m_pc->Send(sizeof(msg), (char*)&msg);
			break;
		}

		if( m_pc->m_characterInfo.clevel < 70 || partner != NULL && partner->m_characterInfo.clevel < 70 )
		{
			PACKET_ZC_BABYMSG msg;
			msg.PacketType = HEADER_ZC_BABYMSG;
			msg.MsgNo = 1;
			m_pc->Send(sizeof(msg), (char*)&msg);
			break;
		}

		CPC* baby = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(packet.AID, PC_TYPE);
		if( baby == NULL )
			break;

		if( baby->m_marriageInfo.bMarried )
		{
			PACKET_ZC_BABYMSG msg;
			msg.PacketType = HEADER_ZC_BABYMSG;
			msg.MsgNo = 2;
			m_pc->Send(sizeof(msg), (char*)&msg);
			break;
		}

		PACKET_ZC_REQ_BABY reqpacket;
		reqpacket.PacketType = HEADER_ZC_REQ_BABY;
		reqpacket.AID = m_pc->GetAccountID();
		reqpacket.GID = m_pc->CPC::GetCharacterID();
		memcpy_s(reqpacket.name, sizeof(reqpacket.name), m_pc->m_characterInfo.characterName, sizeof(m_pc->m_characterInfo.characterName));
		baby->Send(sizeof(reqpacket), (char*)&reqpacket);
	}
	break;
	case 503: // HEADER_CZ_JOIN_BABY
	{// 3821-3833
		PACKET_CZ_JOIN_BABY packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

		CPC* other = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(packet.AID, PC_TYPE);
		if( other == NULL || packet.answer == 0 || !other->m_marriageInfo.bMarried )
			break;

		if( other->m_characterInfo.sex == SEX_MALE )
			m_pc->CPC::OnMakeFamily(other->CPC::GetCharacterID(), other->m_marriageInfo.partnerGID);
		else
			m_pc->CPC::OnMakeFamily(other->m_marriageInfo.partnerGID, other->CPC::GetCharacterID());
	}
	break;
	case 596: // HEADER_CZ_AGREE_STARPLACE
	{// 3839-3864
		PACKET_CZ_AGREE_STARPLACE packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

		if( packet.which == 10 )
		{
			if( m_pc->m_characterInfo.job >= JT_NOVICE_H && m_pc->m_characterInfo.job <= JT_CHICKEN2_H )
				break;

			if( m_pc->m_characterInfo.CharacterInfo::GetMoney() < 1000000 )
				break;

			if( !m_pc->CPC::ConsumeItem(ITID_BLACK_GEMSTONE, 1, 0, 0) )
				break;

			m_pc->CPC::DeleteMoney(1000000);
			int exp = g_expParameter.CExpParameter::GetNextExp(m_pc->m_characterInfo.clevel, m_pc->m_characterInfo.job) / 99;
			CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, m_pc, CM_ADD_EXP, exp, 0, 0, 0);
		}
		else
		{
			m_pc->CPC::OnStarPlaceRemember(packet.which + 200, 0, 0);
		}
	}
	break;
	case 514: // HEADER_CZ_ADD_FRIENDS
	{// 3868-3869
		this->CPCPacketHandler::OnAddFriend(packetSize);
	}
	break;
	case 515: // HEADER_CZ_DELETE_FRIENDS
	{// 3871-3872
		this->CPCPacketHandler::OnDeleteFriend(packetSize);
	}
	break;
	case 520: // HEADER_CZ_ACK_REQ_ADD_FRIENDS
	{// 3874-3875
		this->CPCPacketHandler::OnAckReqAddFriends(packetSize);
	}
	break;
	case 530: // HEADER_CZ_REQ_GIVE_MANNER_BYNAME
	{// 3882-3883
		this->CPCPacketHandler::OnGiveMannerPointByName(packetSize);
	}
	break;
	case 531: // HEADER_CZ_REQ_STATUS_GM
	{// 3885-3886
		this->CPCPacketHandler::OnReqStatus(packetSize);
	}
	break;
	case 535: // HEADER_CZ_BLACKSMITH_RANK
	case 536: // HEADER_CZ_ALCHEMIST_RANK
	case 549: // HEADER_CZ_TAEKWON_RANK
	case 567: // HEADER_CZ_KILLER_RANK
	{// 3893-3894
		this->CPCPacketHandler::OnReqMakerRanking(Header, packetSize);
	}
	break;
	case 677: // HEADER_CZ_KSY_EVENT
	{// 3898-3899
		this->CPCPacketHandler::OnReqKSY(packetSize);
	}
	break;
	case 541: // HEADER_CZ_LESSEFFECT
	{// 3901-3902
		this->CPCPacketHandler::OnLessEffect(packetSize);
	}
	break;
	case 546: // HEADER_CZ_REQ_WEAPONREFINE
	{// 3907-3909
		PACKET_CZ_REQ_WEAPONREFINE packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		m_pc->CPC::ReqWeaponRefine(packet.Index);
	}
	break;
	case 2512: // HEADER_CZ_NPROTECTGAMEGUARDCSAUTH
	{// 3914-3922
		PACKET_CZ_NPROTECTGAMEGUARDCSAUTH* pCZ_NPROTECTGAMEGUARDCSAUTH = reinterpret_cast<PACKET_CZ_NPROTECTGAMEGUARDCSAUTH*>(_malloca(packetSize));
		if( pCZ_NPROTECTGAMEGUARDCSAUTH == NULL )
			break;
		m_recvQueue->CPacketQueue::GetData(packetSize, (char*)pCZ_NPROTECTGAMEGUARDCSAUTH);
		this->CPCPacketHandler::OnCZ_NPROTECTGAMEGUARDCSAUTH(pCZ_NPROTECTGAMEGUARDCSAUTH);
		_freea(pCZ_NPROTECTGAMEGUARDCSAUTH);
	}
	break;
	case 552: // HEADER_CZ_ACK_GAME_GUARD
	{// 3925-3926
		this->CPCPacketHandler::OnAckGameGuard(packetSize);
	}
	break;
	case 557: // HEADER_CZ_COMMAND_MER
	{// 3930-3931
		this->CPCPacketHandler::OnCommandMercenary(packetSize);
	}
	break;
	case 564: // HEADER_CZ_REQUEST_MOVETOOWNER
	{// 3934-3935
		this->CPCPacketHandler::OnRequestMoveToOwner(packetSize);
	}
	break;
	case 562: // HEADER_CZ_REQUEST_MOVENPC
	{// 3938-3939
		this->CPCPacketHandler::OnRequestMoveNpc(packetSize);
	}
	break;
	case 563: // HEADER_CZ_REQUEST_ACTNPC
	{// 3942-3943
		this->CPCPacketHandler::OnRequestActNpc(packetSize);
	}
	break;
	case 571: // HEADER_CZ_ACK_STORE_PASSWORD
	{// 3946-3948
		if( g_storePasswordCheck == TRUE )
			this->CPCPacketHandler::OnAckStorePassword(packetSize);
	}
	break;
	case 575: // HEADER_CZ_MAIL_GET_LIST
	{// 3953-3954
		this->CPCPacketHandler::OnMailGetList(packetSize);
	}
	break;
	case 577: // HEADER_CZ_MAIL_OPEN
	{// 3956-3957
		this->CPCPacketHandler::OnMailOpen(packetSize);
	}
	break;
	case 579: // HEADER_CZ_MAIL_DELETE
	{// 3959-3960
		this->CPCPacketHandler::OnMailDelete(packetSize);
	}
	break;
	case 580: // HEADER_CZ_MAIL_GET_ITEM
	{// 3962-3963
		this->CPCPacketHandler::OnMailGetItem(packetSize);
	}
	break;
	case 582: // HEADER_CZ_MAIL_RESET_ITEM
	{// 3965-3966
		this->CPCPacketHandler::OnMailResetItem(packetSize);
	}
	break;
	case 583: // HEADER_CZ_MAIL_ADD_ITEM
	{// 3968-3969
		this->CPCPacketHandler::OnMailAddItem(packetSize);
	}
	break;
	case 584: // HEADER_CZ_MAIL_SEND
	{// 3974-3975
		this->CPCPacketHandler::OnMailSend(packetSize);
	}
	break;
	case 627: // HEADER_CZ_REQ_MAIL_RETURN
	{// 3978-3979
		this->CPCPacketHandler::OnMailReturn(packetSize);
	}
	break;
	case 587: // HEADER_CZ_AUCTION_CREATE
	{// 3983-3984
		this->CPCPacketHandler::OnAuctionCreate(packetSize);
	}
	break;
	case 588: // HEADER_CZ_AUCTION_ADD_ITEM
	{// 3986-3987
		this->CPCPacketHandler::OnAuctionAddItem(packetSize);
	}
	break;
	case 589: // HEADER_CZ_AUCTION_ADD
	{// 3989-3990
		this->CPCPacketHandler::OnAuctionAdd(packetSize);
	}
	break;
	case 590: // HEADER_CZ_AUCTION_ADD_CANCEL
	{// 3992-3993
		this->CPCPacketHandler::OnAuctionAddCancel(packetSize);
	}
	break;
	case 591: // HEADER_CZ_AUCTION_BUY
	{// 3995-3996
		this->CPCPacketHandler::OnAuctionBuy(packetSize);
	}
	break;
	case 593: // HEADER_CZ_AUCTION_ITEM_SEARCH
	{// 3998-3999
		this->CPCPacketHandler::OnAuctionItemSearch(packetSize);
	}
	break;
	case 604: // HEADER_CZ_AUCTION_REQ_MY_INFO
	{// 4002-4003
		this->CPCPacketHandler::OnAuctionReqMyInfo(packetSize);
	}
	break;
	case 605: // HEADER_CZ_AUCTION_REQ_MY_SELL_STOP
	{// 4006-4007
		this->CPCPacketHandler::OnAuctionMySellStop(packetSize);
	}
	break;
	case 633: // HEADER_CZ_HUNTINGLIST
	{// 4012-4013
		this->CPCPacketHandler::OnHuntingList(packetSize);
	}
	break;
	case 648: // HEADER_CZ_PC_BUY_CASH_POINT_ITEM
	{// 4017-4018
		this->CPCPacketHandler::OnPCBuyCashPointItem(packetSize);
	}
	break;
	case 1093: // HEADER_CZ_SIMPLE_BUY_CASH_POINT_ITEM
	{// 4020-4021
		this->CPCPacketHandler::OnPCBuyCashPointItemSimpleShop(packetSize);
	}
	break;
	case 658: // HEADER_CZ_STANDING_RESURRECTION
	{// 4024-4025
		this->CPCPacketHandler::OnStandingResurrection(packetSize);
	}
	break;
	case 683: // HEADER_CZ_ACK_CASH_PASSWORD
	{// 4048-4049
		this->CPCPacketHandler::OnCashPassword(packetSize);
	}
	break;
	case 698: // HEADER_CZ_SHORTCUT_KEY_CHANGE
	{// 4053-4054
		this->CPCPacketHandler::OnShortcutKey_Change(packetSize);
	}
	break;
	case 694: // HEADER_CZ_ACTIVE_QUEST
	{// 4058-4059
		this->CPCPacketHandler::OnActiveQuest(packetSize);
	}
	break;
	case 731: // HEADER_CZ_BATTLEFIELD_CHAT
	{// 4063-4064
		this->CPCPacketHandler::OnBattleFieldChat(packetSize);
	}
	break;
	case 753: // HEADER_CZ_PROGRESS
	{// 4090-4091
		this->CPCPacketHandler::OnProgress(packetSize);
	}
	break;
	case 860: // HEADER_CZ_OPEN_SIMPLE_CASHSHOP_ITEMLIST
	{// 4095-4097
		this->CPCPacketHandler::OnCzOpenSimpleCashShopItemList(packetSize);
	}
	break;
	case 862: // HEADER_CZ_CLOSE_WINDOW
	{// 4100-4102
		this->CPCPacketHandler::OnCZOnCloseWindow(packetSize);
	}
	break;
	case 1098: // HEADER_CZ_CLIENT_VERSION
	{// 4115-4117
		this->CPCPacketHandler::OnCZClientVersion(packetSize);
	}
	break;
	case 1099: // HEADER_CZ_CLOSE_SIMPLECASH_SHOP
	{// 4120-4122
		this->CPCPacketHandler::OnCZCloseSimpleCashShop(packetSize);
	}
	break;
	case 2007: // HEADER_CZ_GROUPINFO_CHANGE_V2
	{// 4128-4134
		PACKET_CZ_GROUPINFO_CHANGE_V2 packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CPCPacketHandler::OnCZ_GROUPINFO_CHANGE_V2(packet);
	}
	break;
	case 2010: // HEADER_CZ_CHANGE_GROUP_MASTER
	{// 4136-4137
		this->CPCPacketHandler::OnChangeGroupMaster(packetSize);
	}
	break;
	case 2060: // HEADER_CZ_SIMPLE_CASH_BTNSHOW
	{// 4181-4182
		this->CPCPacketHandler::OnCZSimpleCashBtnShow(packetSize);
	}
	break;
	case 2065: // HEADER_CZ_REQ_OPEN_BUYING_STORE
	{// 4185-4186
		this->CPCPacketHandler::OnReqOpenBuyingStore(packetSize);
	}
	break;
	case 2071: // HEADER_CZ_REQ_CLICK_TO_BUYING_STORE
	{// 4188-4189
		this->CPCPacketHandler::OnReqClickToBuyingStore(packetSize);
	}
	break;
	case 2073: // HEADER_CZ_REQ_TRADE_BUYING_STORE
	{// 4191-4192
		this->CPCPacketHandler::OnReqTradeBuyingStore(packetSize);
	}
	break;
	case 2069: // HEADER_CZ_REQ_CLOSE_BUYING_STORE
	{// 4194-4195
		this->CPCPacketHandler::OnReqCloseBuyingStore(packetSize);
	}
	break;
	case 2101: // HEADER_CZ_SEARCH_STORE_INFO
	{// 4201-4202
		this->CPCPacketHandler::OnSearchStoreInfo(packetSize);
	}
	break;
	case 2104: // HEADER_CZ_SEARCH_STORE_INFO_NEXT_PAGE
	{// 4216-4217
		this->CPCPacketHandler::OnSearchStoreInfoNexPage(packetSize);
	}
	break;
	case 2107: // HEADER_CZ_CLOSE_SEARCH_STORE_INFO
	{// 4222-4223
		this->CPCPacketHandler::OnCloseSearchStoreInfo(packetSize);
	}
	break;
	case 2108: // HEADER_CZ_SSILIST_ITEM_CLICK
	{// 4225-4226
		this->CPCPacketHandler::OnSSIListItemClick(packetSize);
	}
	break;
	case 2114: // HEADER_CZ_RECALL_SSO
	{// 4230-4231
		this->CPCPacketHandler::OnCZRecall_SSO(packetSize);
	}
	break;
	case 2115: // HEADER_CZ_REMOVE_AID_SSO
	{// 4233-4234
		this->CPCPacketHandler::OnCZRecall_SSO(packetSize);
	}
	break;
	case 2116: // HEADER_CZ_SE_CASHSHOP_OPEN
	{// 4239-4242
		PACKET_CZ_SE_CASHSHOP_OPEN packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CPCPacketHandler::OnCZ_SE_CASHSHOP_OPEN(packet);
	}
	break;
	case 2118: // HEADER_CZ_REQ_SE_CASH_TAB_CODE
	{// 4244-4245
		this->CPCPacketHandler::OnCZReqSeCashTabCode(packetSize);
	}
	break;
	case 2120: // HEADER_CZ_SE_PC_BUY_CASHITEM_LIST
	{// 4247-4248
		this->CPCPacketHandler::OnCZSePcBuyCashItemList(packetSize);
	}
	break;
	case 2122: // HEADER_CZ_SE_CASHSHOP_CLOSE
	{// 4250-4251
		this->CPCPacketHandler::OnCZSeCashShopClose(packetSize);
	}
	break;
	case 2249: // HEADER_CZ_REQ_SCHEDULER_CASHITEM
	{// 4258-4261
		PACKET_CZ_REQ_SCHEDULER_CASHITEM packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CPCPacketHandler::OnCZReqSchedulerCashItem(packet);
	}
	break;
	case 275: // HEADER_CZ_USE_SKILL
	case 739: // HEADER_CZ_USE_SKILL_NEW_JAPEN
	{// 4307-4311
		PACKET_CZ_USE_SKILL packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CPCPacketHandler::OnCZ_USE_SKILL(packet.SKID, packet.selectedLevel, packet.targetID);
	}
	break;
	case 1080: // HEADER_CZ_USE_SKILL2
	{// 4317-4321
		PACKET_CZ_USE_SKILL2 packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CPCPacketHandler::OnCZ_USE_SKILL(packet.SKID, packet.selectedLevel, packet.targetID);
	}
	break;
	case 870: // HEADER_CZ_USE_SKILL_TOGROUND2
	{// 4328-4331
		PACKET_CZ_USE_SKILL_TOGROUND2 packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CPCPacketHandler::OnCZ_USE_SKILL_TOGROUND(packet.SKID, packet.selectedLevel, packet.xPos, packet.yPos);
	}
	break;
	case 278: // HEADER_CZ_USE_SKILL_TOGROUND
	{// 4336-4344
		PACKET_CZ_USE_SKILL_TOGROUND packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		m_pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
		this->CPCPacketHandler::OnCZ_USE_SKILL_TOGROUND(packet.SKID, packet.selectedLevel, packet.xPos, packet.yPos);
	}
	break;
	case 863: // HEADER_CZ_REQUEST_MOVE2
	{// 4351-4354
		PACKET_CZ_REQUEST_MOVE2 packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CPCPacketHandler::OnCZ_REQUEST_MOVE(packet.dest);
	}
	break;
	case 133: // HEADER_CZ_REQUEST_MOVE
	{// 4378-4385
		PACKET_CZ_REQUEST_MOVE packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		m_pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
		this->CPCPacketHandler::OnCZ_REQUEST_MOVE(packet.dest);
	}
	break;
	case 866: // HEADER_CZ_ITEM_PICKUP2
	{// 4392-4395
		PACKET_CZ_ITEM_PICKUP2 packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CPCPacketHandler::OnCZ_ITEM_PICKUP(packet.ITAID);
	}
	break;
	case 159: // HEADER_CZ_ITEM_PICKUP
	{// 4429-4438
		PACKET_CZ_ITEM_PICKUP packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		m_pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
		this->CPCPacketHandler::OnCZ_ITEM_PICKUP(packet.ITAID);
	}
	break;
	case 2124: // HEADER_CZ_MACRO_USE_SKILL
	{// 4445-4448
		PACKET_CZ_MACRO_USE_SKILL packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CPCPacketHandler::OnCZ_MACRO_USE_SKILL(packet);
	}
	break;
	case 2125: // HEADER_CZ_MACRO_USE_SKILL_TOGROUND
	{// 4453-4456
		PACKET_CZ_MACRO_USE_SKILL_TOGROUND packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CPCPacketHandler::OnCZ_MACRO_USE_SKILL_TOGROUND(packet);
	}
	break;
	case 2126: // HEADER_CZ_MACRO_REQUEST_MOVE
	{// 4461-4464
		PACKET_CZ_MACRO_REQUEST_MOVE packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CPCPacketHandler::OnCZ_MACRO_REQUEST_MOVE(packet);
	}
	break;
	case 2127: // HEADER_CZ_MACRO_ITEM_PICKUP
	{// 4469-4472
		PACKET_CZ_MACRO_ITEM_PICKUP packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CPCPacketHandler::OnCZ_MACRO_ITEM_PICKUP(packet);
	}
	break;
	case 2128: // HEADER_CZ_MACRO_REQUEST_ACT
	{// 4477-4480
		PACKET_CZ_MACRO_REQUEST_ACT packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CPCPacketHandler::OnCZ_MACRO_REQUEST_ACT(packet);
	}
	break;
	case 2241: // HEADER_CZ_MACRO_START
	{// ????
		PACKET_CZ_MACRO_START packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CPCPacketHandler::OnCZ_MACRO_START(packet);
	}
	break;
	case 2242: // HEADER_CZ_MACRO_STOP
	{// ????
		PACKET_CZ_MACRO_STOP packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CPCPacketHandler::OnCZ_MACRO_STOP(packet);
	}
	break;
	case 2130: // HEADER_CZ_GPK_DYNCODE_RELOAD
	{// 4484-4487
		PACKET_CZ_GPK_DYNCODE_RELOAD packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CPCPacketHandler::OnCZ_GPK_DYNCODE_RELOAD(packet);
	}
	break;
	case 2132: // HEADER_CZ_GPK_AUTH
	{// 4490-4494
		std::vector<char> packet(packetSize);
		PACKET_CZ_GPK_AUTH& cz_gpk_auth = *reinterpret_cast<PACKET_CZ_GPK_AUTH*>(&packet.front());
		m_recvQueue->CPacketQueue::GetData(packet.size(), &packet.front());
		this->CPCPacketHandler::OnCZ_GPK_AUTH(cz_gpk_auth);
	}
	break;
	case 2229: // HEADER_CZ_TRYCOLLECTION
	{// 4499-4502
		PACKET_CZ_TRYCOLLECTION packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CPCPacketHandler::OnCZ_TRYCOLLECTION(packet);
	}
	break;
	case 2263: // HEADER_CZ_REQ_ENTRY_QUEUE_APPLY
	{// 4507-4510
		PACKET_CZ_REQ_ENTRY_QUEUE_APPLY packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CPCPacketHandler::OnCZ_REQ_ENTRY_QUEUE_APPLY(packet);
	}
	break;
	case 2266: // HEADER_CZ_REQ_ENTRY_QUEUE_CANCEL
	{// 4515-4518
		PACKET_CZ_REQ_ENTRY_QUEUE_CANCEL packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CPCPacketHandler::OnCZ_REQ_ENTRY_QUEUE_CANCEL(packet);
	}
	break;
	case 2269: // HEADER_CZ_REPLY_ENTRY_QUEUE_ADMISSION
	{// 4523-4526
		PACKET_CZ_REPLY_ENTRY_QUEUE_ADMISSION packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CPCPacketHandler::OnCZ_REPLY_ENTRY_QUEUE_ADMISSION(packet);
	}
	break;
	case 2272: // HEADER_CZ_REPLY_LOBBY_ADMISSION
	{// 4530-4534
		PACKET_CZ_REPLY_LOBBY_ADMISSION packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CPCPacketHandler::OnCZ_REPLY_LOBBY_ADMISSION(packet);
	}
	break;
	case 2314: // HEADER_CZ_REQ_ENTRY_QUEUE_RANKING
	{// 4614-4617
		PACKET_CZ_REQ_ENTRY_QUEUE_RANKING packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CPCPacketHandler::OnCZ_REQ_ENTRY_QUEUE_RANKING(packet);
	}
	break;
	case 2414: // HEADER_CZ_REQ_MERGE_ITEM
	{// 4622-4627
		PACKET_CZ_REQ_MERGE_ITEM* pCZ_REQ_MERGE_ITEM = reinterpret_cast<PACKET_CZ_REQ_MERGE_ITEM*>(_malloca(packetSize));
		m_recvQueue->CPacketQueue::GetData(packetSize, (char*)pCZ_REQ_MERGE_ITEM);
		this->CPCPacketHandler::OnCZ_REQ_MERGE_ITEM(packetSize, (char*)pCZ_REQ_MERGE_ITEM);
		if( pCZ_REQ_MERGE_ITEM != NULL ) _freea(pCZ_REQ_MERGE_ITEM);
	}
	break;
	case 2420: // HEADER_CZ_CANCEL_MERGE_ITEM
	{// 4631-4633
		PACKET_CZ_CANCEL_MERGE_ITEM packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CPCPacketHandler::OnCZ_CANCEL_MERGE_ITEM();
	}
	break;
	case 2428: // HEADER_CZ_REQ_RANKING
	{// 4647-4651
		PACKET_CZ_REQ_RANKING packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CPCPacketHandler::OnCZ_REQ_RANKING(packet);
	}
	break;
	case 2445: // HEADER_CZ_CLAN_CHAT
	{// ????
		this->CPCPacketHandler::OnCZ_CLAN_CHAT(packetSize);
	}
	break;
	case 2180: // HEADER_CZ_REASSEMBLY_AUTH01
	//...
	case 2221: // HEADER_CZ_REASSEMBLY_AUTH42
	case 2369: // HEADER_CZ_REASSEMBLY_AUTH43
	//...
	case 2410: // HEADER_CZ_REASSEMBLY_AUTH84
	{
		PACKET_CZ_REASSEMBLY_AUTH packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
	}
	break;
	default:
	{// 4804-4818
		g_UserBlockMgr.CUserBlockMgr::AddR2(CUserBlock::TYPE_WARNNING, CUserBlock::REASON_UNKNOWN_PACKET, m_pc->GetAccountID(), CGVar::GetObj()->CGVar::GetUserBlockSecond_when_found_unknown_packet());
		m_recvQueue->CPacketQueue::Reset();
		m_pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "Not Header %d AID : %d", Header, m_pc->GetAccountID());
		return 0;
	}
	break;
	};

	return -1;
}


void CPCPacketHandler::UseForcedSkill(char* buf) // ??? (67-70.h)
{
	PACKET_CZ_USE_SKILL& packet = *reinterpret_cast<PACKET_CZ_USE_SKILL*>(buf);
	this->CPCPacketHandler::OnUseSkill(packet.SKID, packet.selectedLevel, packet.targetID);
}


void CPCPacketHandler::UnLockCashPoint() // ??? (71.h)
{
	m_bLockCashPoint = FALSE;
}


//...


void Sned_PACKET_ZC_PARTY_JOIN_REQ_ACK(CPC* const in_pToPlayer, const char* in_pTargetCharName, PACKET_ZC_PARTY_JOIN_REQ_ACK::enumAnswer in_Answer) // 1734-1740
{
	PACKET_ZC_PARTY_JOIN_REQ_ACK packet = {};
	packet.PacketType = HEADER_ZC_PARTY_JOIN_REQ_ACK;
	memcpy_s(packet.characterName, sizeof(packet.characterName), in_pTargetCharName, 24);
	packet.answer = in_Answer;
	in_pToPlayer->Send(sizeof(packet), (char*)&packet);
}


void CPCPacketHandler::OnCZ_PARTY_JOIN_REQ(const PACKET_CZ_PARTY_JOIN_REQ& in_packet) // 1744-1802 (1159-1197)
{
	if( m_pc->m_characterInfo.GroupID == 0 || !m_pc->m_characterInfo.isGroupMaster )
		return;

	char TargetCharName[24] = {};
	memcpy_s(TargetCharName, sizeof(TargetCharName), in_packet.characterName, sizeof(in_packet.characterName));
	TargetCharName[countof(TargetCharName)-1] = '\0';

	CPC* targetPC = CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(TargetCharName);
	if( targetPC != NULL )
	{
		if( targetPC->m_characterInfo.Party.Bit.bRefuseJoinMsg )
		{
			Sned_PACKET_ZC_PARTY_JOIN_REQ_ACK(m_pc, TargetCharName, PACKET_ZC_PARTY_JOIN_REQ_ACK::ANSWER_JOINMSG_REFUSE);
			return;
		}

		if( targetPC->m_characterInfo.GroupID != 0 )
		{
			Sned_PACKET_ZC_PARTY_JOIN_REQ_ACK(m_pc, TargetCharName, PACKET_ZC_PARTY_JOIN_REQ_ACK::ANSWER_ALREADY_OTHERGROUPM);
			return;
		}

		if( targetPC->IsItPossible(MAPPROPERTY_NO_PARTY_FORMATION) == 1 )
		{
			Sned_PACKET_ZC_PARTY_JOIN_REQ_ACK(m_pc, TargetCharName, PACKET_ZC_PARTY_JOIN_REQ_ACK::ANSWER_INVALID_MAPPROPERTY);
			return;
		}

		if( m_pc->IsItPossible(MAPPROPERTY_PREVENT_PARTY_JOIN) == 1 )
		{
			Sned_PACKET_ZC_PARTY_JOIN_REQ_ACK(m_pc, TargetCharName, PACKET_ZC_PARTY_JOIN_REQ_ACK::ANSWER_INVALID_MAPPROPERTY_ME);
			return;
		}

		if( targetPC->IsItPossible(MAPPROPERTY_PREVENT_PARTY_JOIN) == 1 )
		{
			Sned_PACKET_ZC_PARTY_JOIN_REQ_ACK(m_pc, TargetCharName, PACKET_ZC_PARTY_JOIN_REQ_ACK::ANSWER_INVALID_MAPPROPERTY);
			return;
		}
	}

	PACKET_ZI_PARTY_JOIN_REQ packet = {};
	packet.PacketType = HEADER_ZI_PARTY_JOIN_REQ;
	packet.senderAID = m_pc->GetAccountID();
	packet.GRID = m_pc->m_characterInfo.GroupID;
	memcpy_s(packet.TargetCharName, sizeof(packet.TargetCharName), TargetCharName, sizeof(TargetCharName));
	CCharacterMgr::GetObj()->CCharacterMgr::SendToIServer(sizeof(packet), (char*)&packet);
}


void CPCPacketHandler::OnCZ_PARTY_CONFIG(const PACKET_CZ_PARTY_CONFIG& in_packet) // ????-???? (1201-1210)
{
	m_pc->m_characterInfo.Party.Bit.bRefuseJoinMsg = in_packet.bRefuseJoinMsg;

	PACKET_ZC_PARTY_CONFIG outpacket = {};
	outpacket.PacketType = HEADER_ZC_PARTY_CONFIG;
	outpacket.bRefuseJoinMsg = m_pc->m_characterInfo.Party.Bit.bRefuseJoinMsg;
	m_pc->Send(sizeof(outpacket), (char*)&outpacket);
}


void CPCPacketHandler::OnCZ_PARTY_JOIN_REQ_ACK(const PACKET_CZ_PARTY_JOIN_REQ_ACK& in_packet) // ????-???? (1214-1225)
{
	PACKET_ZC_PARTY_JOIN_REQ_ACK::enumAnswer answer = ( in_packet.bAccept ) ? PACKET_ZC_PARTY_JOIN_REQ_ACK::ANSWER_JOIN_ACCEPT : PACKET_ZC_PARTY_JOIN_REQ_ACK::ANSWER_JOIN_REFUSE;
	Send_PACKET_ZI_PARTY_JOIN_REQ_ACK(m_pc->GetAccountID(), in_packet.GRID, answer);
}


void CPCPacketHandler::OnCZ_MEMORIALDUNGEON_COMMAND(const PACKET_CZ_MEMORIALDUNGEON_COMMAND& in_packet) // 1834-1852 (1229-1247)
{
	if( in_packet.Command == PACKET_CZ_MEMORIALDUNGEON_COMMAND::COMMAND_SUBSCRIPTION_CANCEL
	 || in_packet.Command == PACKET_CZ_MEMORIALDUNGEON_COMMAND::COMMAND_MEMORIALDUNGEON_DESTROY
	 || in_packet.Command == PACKET_CZ_MEMORIALDUNGEON_COMMAND::COMMAND_MEMORIALDUNGEON_DESTROY_FORCE )
		return; //FIXME: doesn't this effectively disable this packet?

	PACKET_ZI_MEMORIALDUNGEON_COMMAND packet = {};
	packet.PacketType = HEADER_ZI_MEMORIALDUNGEON_COMMAND;
	packet.AID = m_pc->GetAccountID();
	packet.GID = m_pc->CPC::GetCharacterID();
	packet.Command = in_packet.Command;
	C2InterServerClient::GetObj()->C2InterServerClient::Send(sizeof(packet), (char*)&packet);
}


hook_func<void (__stdcall *)()> CPCPacketHandler__OnCZ_EQUIPWIN_MICROSCOPE(EXEPATH(), "CPCPacketHandler::OnCZ_EQUIPWIN_MICROSCOPE");
void CPCPacketHandler::OnCZ_EQUIPWIN_MICROSCOPE(const PACKET_CZ_EQUIPWIN_MICROSCOPE& in_packet) // 1951-2012
{
	void* hookptr = CPCPacketHandler__OnCZ_EQUIPWIN_MICROSCOPE;
	__asm mov ecx, in_packet
	__asm push this
	__asm call hookptr
	return; //TODO
}


hook_func<void (__stdcall *)()> CPCPacketHandler__OnCZ_ITEMLISTWIN_RES(EXEPATH(), "CPCPacketHandler::OnCZ_ITEMLISTWIN_RES");
void CPCPacketHandler::OnCZ_ITEMLISTWIN_RES(const unsigned char* in_pPacket, const int in_PacketSize) // 2039-2075
{
	void* hookptr = CPCPacketHandler__OnCZ_ITEMLISTWIN_RES;
	__asm mov ecx, in_PacketSize
	__asm mov edx, in_pPacket
	__asm push this
	__asm call hookptr
	return; //TODO
}


void CPCPacketHandler::OnCZ_GM_FULLSTRIP(const PACKET_CZ_GM_FULLSTRIP& in_packet) // 2078-2116
{
	CPC* pPC = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(in_packet.TargetAID, PC_TYPE);
	if( pPC == NULL )
		return;

	pPC->m_pcitemInventoryMgr.CPCItemInventoryMgr::TakeOffEquip(LOCATION_RARM);
	pPC->m_pcitemInventoryMgr.CPCItemInventoryMgr::TakeOffEquip(LOCATION_BODY);
	pPC->m_pcitemInventoryMgr.CPCItemInventoryMgr::TakeOffEquip(LOCATION_LARM);
	pPC->m_pcitemInventoryMgr.CPCItemInventoryMgr::TakeOffEquip(LOCATION_HEAD_TMB);
	pPC->m_pcitemInventoryMgr.CPCItemInventoryMgr::TakeOffEquip(LOCATION_ACCESSORY1);
	pPC->m_pcitemInventoryMgr.CPCItemInventoryMgr::TakeOffEquip(LOCATION_ACCESSORY2);

	pPC->CPC::CheckWeaponState();

	pPC->SetEffective(EFST_NOEQUIPWEAPON, 60000, 1, 0, 0, 0);
	pPC->SetEffective(EFST_NOEQUIPARMOR, 60000, 1, 0, 0, 0);
	pPC->SetEffective(EFST_NOEQUIPSHIELD, 60000, 1, 0, 0, 0);
	pPC->SetEffective(EFST_NOEQUIPHELM, 60000, 1, 0, 0, 0);
	pPC->SetEffective(EFST_NOEQUIPACCESSARY, 60000, 1, 0, 0, 0);
}


hook_func<void (CPCPacketHandler::*)(const PACKET_CZ_SKILL_SELECT_RESPONSE& in_packet)> CPCPacketHandler__OnCZ_SKILL_SELECT_RESPONSE(EXEPATH(), "CPCPacketHandler::OnCZ_SKILL_SELECT_RESPONSE");
void CPCPacketHandler::OnCZ_SKILL_SELECT_RESPONSE(const PACKET_CZ_SKILL_SELECT_RESPONSE& in_packet) // 2119-2172
{
	return (this->*CPCPacketHandler__OnCZ_SKILL_SELECT_RESPONSE)(in_packet);
	//TODO
}


void CPCPacketHandler::OnCZ_CONFIG(const PACKET_CZ_CONFIG& in_packet) // 2175-2190
{
	if( in_packet.Config == PACKET_CZ_CONFIG::CONFIG_OPEN_EQUIPMENT_WINDOW )
	{
		m_pc->m_characterInfo.bOpenEquipmentWin = ( in_packet.Value != 0 );

		PACKET_ZC_CONFIG packet = {};
		packet.PacketType = HEADER_ZC_CONFIG;
		packet.Config = PACKET_CZ_CONFIG::CONFIG_OPEN_EQUIPMENT_WINDOW;
		packet.Value = m_pc->m_characterInfo.bOpenEquipmentWin;
		m_pc->Send(sizeof(packet), (char*)&packet);
	}
}


void CPCPacketHandler::OnCZ_INVENTORY_TAB(const PACKET_CZ_INVENTORY_TAB& in_packet) // 2239 +-
{
	if( !m_pc->CPC::IsValid() )
	{
		m_pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
		return;
	}

	Request request;
	request.par1 = in_packet.Index;
	request.par2 = in_packet.NORMALorPRIVATE;
	request.Request::SetID(RT_REQ_INVENTORY_TAB);
	m_pc->CPC::OnDispatchClientRequest(&request);
}


void CPCPacketHandler::OnCZ_SELECTCART(const PACKET_CZ_SELECTCART& in_packet) // ????
{
}


//...


void CPCPacketHandler::OnChat(const PACKET_CZ_REQUEST_CHAT* in_pPacket) // 4821-4892
{
	//TODO
}


void CPCPacketHandler::OnEnter(const unsigned long in_AID, const unsigned long in_GID, const int in_AuthCode, const unsigned long in_clientTime, const unsigned char in_Sex) // 4955-5114
{
	PACKET_ZH_LOGON packet;
	packet.PacketType = HEADER_ZH_LOGON;
	packet.AID = in_AID;
	packet.GID = in_GID;
	packet.AuthCode = in_AuthCode;
	packet.curUser = CCharacterMgr::GetObj()->CCharacterMgr::GetCurPlayChar();
	packet.sex = 0;

	m_pc->CPC::SetMapLoadingFlag(TRUE);
	if( CCharacterMgr::GetObj()->CCharacterMgr::SearchPCFromIndexInfo(in_AID) )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "try duplicate login AID: %d, %d", in_AID, m_pc->CClient::GetErrorCount());
		m_pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
		return;
	}

	if( in_AID <= PC_MINIMUM_AID || in_GID <= PC_MINIMUM_GID ) //FIXME: off-by-one mismatch
	{
		m_pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "PC Index Valid (AID:%d <= 100000) or (newGID:%d <= 100000)", in_AID, in_GID);
		return;
	}

	m_pc->m_characterTimeInfo.connectedTime = timeGetTime();
	m_pc->m_characterTimeInfo.clientLocalConnectTime = in_clientTime;
	m_pc->m_characterInfo.sex = in_Sex;
	m_pc->m_pcClientUpdater.CPCClientUpdater::SetAccountID(in_AID);
	m_pc->m_pcClientUpdater.CPCClientUpdater::SetCharacterID(in_GID);
	m_pc->m_pcClientUpdater.CPCClientUpdater::SetAuthCode(in_AuthCode);

	CCharacterMgr::GetObj()->CCharacterMgr::AddPCToIndexInfo(in_AID, m_pc->m_index, m_pc->m_characterTimeInfo.connectedTime);
	CCharacterMgr::GetObj()->CCharacterMgr::SendToHServer(sizeof(packet), (char*)&packet);
}


void CPCPacketHandler::OnChatParty(int len) // 4895-4927
{
	//TODO
}


void CPCPacketHandler::OnMove(PACKET_CZ_REQUEST_MOVE* move_req) // 5262-5298
{
	//TODO
}


void CPCPacketHandler::OnRequestTime(const unsigned long in_clientTime) // 5301-5322
{
	//TODO
}


void CPCPacketHandler::OnActorInit(int len) // 5329-5359
{
	//TODO
}


void CPCPacketHandler::OnReqName(const unsigned long in_AID) // 5505-5605
{
	//TODO
}


void CPCPacketHandler::OnWhisper(int len) // 5608-5677
{
	//TODO
}


void CPCPacketHandler::OnLocalBroadCast(int len) // 5681-5707
{
	//TODO
}


void CPCPacketHandler::OnBroadCast(int len) // 5710-5746
{
	//TODO
}


void CPCPacketHandler::OnChangeDir(const short in_headDir, const unsigned char in_dir) // 5750-5770
{
	//TODO
}


void CPCPacketHandler::OnDisconnectCharacter(int len) // 5773-5807
{
	//TODO
}


void CPCPacketHandler::OnDisconnectAllCharacter(int len) // 5810-5833
{
	//TODO
}


void CPCPacketHandler::OnReqAct2(const unsigned long in_targetGID, const unsigned char in_action, const bool in_bRequestClient) // 5840-6708
{
	//TODO
}


void CPCPacketHandler::OnReqAct1(int packetSize, char* buf) // 6714-6745
{
	//TODO
}


void CPCPacketHandler::OnThrowItem(const unsigned short in_Index, const short in_count) // 6779-6792
{
	//TODO
}


void CPCPacketHandler::OnUseItem2(const unsigned short in_index, const unsigned long in_AID) // 6797-6848
{
	//TODO
}


void CPCPacketHandler::OnUseItem(int len) // 6851-6878
{
	//TODO
}


void CPCPacketHandler::OnWearEquip(int len) // 6942-6996
{
	//TODO
}


void CPCPacketHandler::OnTakeOffEquip(int len) // 7051-7102
{
	//TODO
}


void CPCPacketHandler::OnItemExplanationByName(int len) // 7105-7110
{
	m_pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
}


void CPCPacketHandler::OnChooseMenu(int len) // 7113-7150
{
	//TODO
}


void CPCPacketHandler::OnReqNextScript(int len) // 7153-7193
{
	//TODO
}


void CPCPacketHandler::OnRestart_QUIT_RESTART() // 7211-7215
{
	//TODO
}


void CPCPacketHandler::OnRestart_QUIT_EXIT() // 7222-7264
{
	//TODO
}


bool CPCPacketHandler::OnRestart_QUIT_EXIT_Part1() // 7270-7521
{
	return false;
	//TODO
/*
	if( m_pc->CPC::IsValid() != TRUE )
		return false;

	if( !g_zoneScript.CZoneScript::SearchID(m_pc->m_characterInfo.accountName, CHECK_CHANGEEFFECTSTATE) )
		m_pc->ResetEffectState(EFFECTSTATE_SPECIALHIDING);

	CSaveAllADBWork* cpDBWork = CObjectRecycleMgr<CSaveAllADBWork>::Instance()->CObjectRecycleMgr<CSaveAllADBWork>::Get();
	if( cpDBWork == NULL )
		return false;

	cpDBWork->CSaveAllADBWork::Init(CSaveAllADBWork::AFTER_ACTION_QUIT_EXIT, m_pc->GetAccountID(), m_pc->CPC::GetCharacterID());

	m_pc->CPC::GetDBInfo(5, &cpDBWork->m_CharacterData.m_data);
	memcpy_s(cpDBWork->m_CharacterData.m_characterName, 24, m_pc->m_characterInfo.characterName, 24);
	cpDBWork->m_CharacterData.m_bActive = true;

	if( m_pc->m_pcSkill.m_warpInfo.size() != 0 )
		cpDBWork->m_WaprpInfoData.CSaveAllADBWork::CWarpInfoData::SetWarpInfo(&m_pc->m_pcSkill.m_warpInfo);

	m_pc->CPC::CancelMCStore();
	m_pc->m_pcitemInventoryMgr.CPCItemInventoryMgr::CancelBuyingStore();
	m_pc->CPC::ClearSearchStoreInfo();

	cpDBWork->m_BodyItemData.m_Length = m_pc->m_pcitemInventoryMgr.CPCItemInventoryMgr::GetBodyItemDBFormat(cpDBWork->m_BodyItemData.m_data, sizeof(cpDBWork->m_BodyItemData.m_data));
	cpDBWork->m_BodyItemData.m_bActive = true;

	m_pc->CPC::GetEfstListDBFmt_And_UpdateResetFlag(&cpDBWork->m_Effect3rd.m_List, true);

	cpDBWork->m_StateData.m_Length = m_pc->CActor::GetStateDBFmt(cpDBWork->m_StateData.m_Data, sizeof(cpDBWork->m_StateData.m_Data));
	cpDBWork->m_StateData.m_bActive = true;

	cpDBWork->m_MercenaryData.m_Owner.m_data = m_pc->m_pcBattle.m_Mercenary;
	cpDBWork->m_MercenaryData.m_Owner.m_bActive = true;

	CNpcMercenary* cpMercenary = m_pc->m_pcBattle.CPCBattle::GetMercenary();
	if( cpMercenary != NULL )
	{
		m_pc->m_pcBattle.CPCBattle::Mercenary_SaveToProxyDB();

		memcpy(&cpDBWork->m_MercenaryData.m_Character.m_Info, &m_pc->m_pcBattle.m_Mercenary.m_ProxyDB.m_Info, sizeof(cpDBWork->m_MercenaryData.m_Character.m_Info));

		cpDBWork->m_MercenaryData.m_Character.m_EffectLength = m_pc->m_pcBattle.m_Mercenary.m_ProxyDB.m_EffectLength;
		if( m_pc->m_pcBattle.m_Mercenary.m_ProxyDB.m_EffectLength > 0 )
			memcpy_s(cpDBWork->m_MercenaryData.m_Character.m_EffectData, 512, m_pc->m_pcBattle.m_Mercenary.m_ProxyDB.m_EffectData, m_pc->m_pcBattle.m_Mercenary.m_ProxyDB.m_EffectLength);

		cpDBWork->m_MercenaryData.m_Character.m_StateLength = m_pc->m_pcBattle.m_Mercenary.m_ProxyDB.m_StateLength;
		if( m_pc->m_pcBattle.m_Mercenary.m_ProxyDB.m_StateLength > 0 )
			memcpy_s(cpDBWork->m_MercenaryData.m_Character.m_StateData, 512, m_pc->m_pcBattle.m_Mercenary.m_ProxyDB.m_StateData, m_pc->m_pcBattle.m_Mercenary.m_ProxyDB.m_StateLength);

		if( cpMercenary->GetEffective(EFST_BERSERK, 0) > 0 )
			cpDBWork->m_MercenaryData.m_Character.m_Info.hp = 100;

		cpDBWork->m_MercenaryData.m_Character.m_bActive = true;
	}

	if( m_pc->m_pcitemInventoryMgr.CPCItemInventoryMgr::IsStoreOpen() )
	{
		cpDBWork->m_StoreItemData.m_Length = m_pc->CPC::GetStoreItemDBFormat(cpDBWork->m_StoreItemData.m_Data, sizeof(cpDBWork->m_StoreItemData.m_Data));
		cpDBWork->m_StoreItemData.m_bActive = true;
	}

	if( m_pc->m_pcitemInventoryMgr.m_cartItem.m_isFirstCartOn )
	{
		cpDBWork->m_CartItemData.m_Length = m_pc->m_pcitemInventoryMgr.CPCItemInventoryMgr::GetCartItemDBFormat(cpDBWork->m_CartItemData.m_Data, (const int)v2);
		cpDBWork->m_CartItemData.m_bActive = true;
	}

	cpDBWork->m_questEventData.m_isUpdate = m_pc->m_questEvent.m_isUpdateData;
	if( m_pc->m_questEvent.m_isUpdateData == true )
	{
		cpDBWork->m_questEventData.m_length_quest = m_pc->m_questEvent.CPCQuestEvent::Save_QuestInfo(cpDBWork->m_questEventData.m_data_quset, sizeof(cpDBWork->m_questEventData.m_data_quset));
		cpDBWork->m_questEventData.m_length_hunt = m_pc->m_questEvent.CPCQuestEvent::Save_Quest_Hunt(cpDBWork->m_questEventData.m_data_hunt, sizeof(cpDBWork->m_questEventData.m_data_hunt));
		cpDBWork->m_questEventData.m_length_time = m_pc->m_questEvent.CPCQuestEvent::Save_Quest_Time(cpDBWork->m_questEventData.m_data_time, sizeof(cpDBWork->m_questEventData.m_data_time));
		cpDBWork->m_questEventData.m_length_complete = m_pc->m_questEvent.CPCQuestEvent::Save_CompleteQuest(cpDBWork->m_questEventData.m_data_complete, sizeof(cpDBWork->m_questEventData.m_data_complete));
	}

	m_pc->m_pcSkill.CPCSkill::GetSkill3rdDBFormat(&cpDBWork->m_Skill.m_List);

	m_pc->m_Elemental.CPCElemental::GetSaveData(&cpDBWork->m_ElementalData);

	m_pc->m_pcBattle.m_Homun.CPCBattleHomun::GetHomunDBFmt(m_pc->m_pcBattle.CPCBattle::GetMyHomun(), &cpDBWork->m_HomunData);

	if( !NAsyncDBMgr::GetObj()->NAsyncDBMgr::RequestWork(cpDBWork) )
	{
		CObjectRecycleMgr<CSaveAllADBWork>::Instance()->CObjectRecycleMgr<CSaveAllADBWork>::Put(cpDBWork);
		return false;
	}

	m_pc->SetEffective(EFST_NOACTION_WAIT, 40000, cpDBWork->NAsyncDBWork::GetIdentity(), cpDBWork->NAsyncDBWork::GetType(), timeGetTime(), FALSE);
	return true;
*/
}


void CPCPacketHandler::OnRestart_QUIT_EXIT_Part2() // 7529-7582
{
	//TODO
}


void CPCPacketHandler::OnRestart(int len) // 7589-7611
{
	//TODO
}


void CPCPacketHandler::OnStatusChange(const PACKET_CZ_STATUS_CHANGE& in_packet) // 7617-7861
{
	//TODO
}


void CPCPacketHandler::OnReqEmotion(int len) // 8184-8209
{
	//TODO
}


void CPCPacketHandler::OnReqUserCount(int len) // 8212-8233
{
	//TODO
}


void CPCPacketHandler::OnSelectDealType(int len) // 8236-8245
{
	//TODO
}


void CPCPacketHandler::OnPurchaseItem(int len) // 8291-8323
{
	//TODO
}


hook_func<void (CPCPacketHandler::*)(const PACKET_CZ_PC_SELL_ITEMLIST* const in_pPacket)> CPCPacketHandler__OnCZ_PC_SELL_ITEMLIST(EXEPATH(), "CPCPacketHandler::OnCZ_PC_SELL_ITEMLIST");
void CPCPacketHandler::OnCZ_PC_SELL_ITEMLIST(const PACKET_CZ_PC_SELL_ITEMLIST* const in_pPacket) // 8328-8366
{
	return (this->*CPCPacketHandler__OnCZ_PC_SELL_ITEMLIST)(in_pPacket);
	//TODO
}


void CPCPacketHandler::OnSellItem(int len) // ??? (6941-6976)
{
	//TODO
}


void CPCPacketHandler::OnSettingWhisperPC(int len) // 8411-8433
{
	//TODO
}


void CPCPacketHandler::OnSettingWhisperState(int len) // 8437-8452
{
	//TODO
}


void CPCPacketHandler::OnReqWhisperList(int len2) // 8455-8467
{
	//TODO
}


void CPCPacketHandler::OnCreateChatRoom(int len) // 8470-8533
{
	//TODO
}


void CPCPacketHandler::OnReqEnterRoom(int len) // 8536-8581
{
	//TODO
}


void CPCPacketHandler::OnChangeChatRoom(int len) // 8584-8597
{
	//TODO
}


void CPCPacketHandler::OnReqChangeRole(int len) // 8600-8605
{
	//TODO
}


void CPCPacketHandler::OnReqExpelMember(int len) // 8608-8613
{
	//TODO
}


void CPCPacketHandler::OnExitRoom(int len) // 8616-8629
{
	//TODO
}


void CPCPacketHandler::OnReqExchangeItem(int len) // 8632-8659
{
	//TODO
}


void CPCPacketHandler::OnAckReqExchangeItem(int len) // 8662-8695
{
	//TODO
}


void CPCPacketHandler::OnAddExchangeItem(int len) // 8698-8709
{
	//TODO
}


void CPCPacketHandler::OnConcludeExchangeItem(int len) // 8712-8717
{
	//TODO
}


void CPCPacketHandler::OnCancelExchangeItem(int len) // 8720-8725
{
	//TODO
}


void CPCPacketHandler::OnExecExchangeItem(int len) // 8729-8843
{
	//TODO
}


void CPCPacketHandler::OnMoveItemFromBodyToStore(const short in_index, const int in_count) // 8847-8849
{
	m_pc->CPC::MoveItem(MOVEITEM_BODY_STORE, in_index, in_count);
}


void CPCPacketHandler::OnMoveItemFromStoreToBody(const short in_index, const int in_count) // 8853-8855
{
	m_pc->CPC::MoveItem(MOVEITEM_STORE_BODY, in_index, in_count);
}


void CPCPacketHandler::OnMoveItemFromBodyToCart(int len) // 8858-8901
{
	//TODO
}


void CPCPacketHandler::OnMoveItemFromCartToBody(int len) // 8904-8941
{
	//TODO
}


void CPCPacketHandler::OnMoveItemFromStoreToCart(int len) // 8944-8976
{
	//TODO
}


void CPCPacketHandler::OnMoveItemFromCartToStore(int len) // 8979-8989
{
	//TODO
}


void CPCPacketHandler::OnCloseStore(int len) // 8992-9000
{
	//TODO
}


void CPCPacketHandler::OnMakeGroup(int len) // 9003-9064
{
	//TODO
}


void CPCPacketHandler::OnReqJoinGroup(int len) // 9067-9077
{
	//TODO
}


void CPCPacketHandler::OnCZ_REQ_JOIN_GUILD2(const PACKET_CZ_REQ_JOIN_GUILD2& in_Packet) // ????
{
}


void CPCPacketHandler::OnJoinGroup(int len) // 9157-9167
{
	//TODO
}


void CPCPacketHandler::OnCZ_REQ_LEAVE_GROUP(const PACKET_CZ_REQ_LEAVE_GROUP& in_packet) // 9171-9197
{
	if( m_pc->IsItPossible(MAPPROPERTY_PREVENT_PARTY_LEAVE) == 1 )
	{
		PACKET_ZC_DELETE_MEMBER_FROM_GROUP outpacket;
		outpacket.PacketType = HEADER_ZC_DELETE_MEMBER_FROM_GROUP;
		outpacket.AID = m_pc->GetAccountID();
		memcpy_s(outpacket.characterName, sizeof(outpacket.characterName), m_pc->m_characterInfo.characterName, sizeof(m_pc->m_characterInfo.characterName));
		outpacket.result = GROUPMEMBER_PREVENT_DELETE_LEAVE;
		m_pc->Send(sizeof(outpacket), (char*)&outpacket);
	}
	else
	{
		PACKET_ZI_REQ_LEAVE_GROUP outpacket;
		outpacket.PacketType = HEADER_ZI_REQ_LEAVE_GROUP;
		outpacket.AID = m_pc->GetAccountID();
		outpacket.GID = m_pc->CPC::GetCharacterID();
		CCharacterMgr::GetObj()->CCharacterMgr::SendToIServer(10, (char*)&outpacket);
	}
}


void CPCPacketHandler::OnReqExpelGroupMember(int len) // 9202-9230
{
	//TODO
}


void CPCPacketHandler::OnUpgradeSkillLevel(int len) // 9253-9432
{
	//TODO
}


namespace {
void SendPACKET_ZC_USESKILL_ACK2(CPC* cpPlayer, unsigned long in_TargetAID, unsigned short in_SKID, int in_SkillProperty, int in_XPos, int in_YPos, int in_DelayTime, bool in_IsDisposable) // 9444-9458
{
	PACKET_ZC_USESKILL_ACK2 outpacket;
	outpacket.PacketType = HEADER_ZC_USESKILL_ACK2;
	outpacket.property = in_SkillProperty;
	outpacket.SKID = in_SKID;
	outpacket.delayTime = in_DelayTime;
	outpacket.targetID = in_TargetAID;
	outpacket.xPos = in_XPos;
	outpacket.yPos = in_YPos;
	outpacket.AID = cpPlayer->GetAccountID();
	outpacket.isDisposable = in_IsDisposable;
	cpPlayer->Send(sizeof(outpacket), (char*)&outpacket);
	cpPlayer->CCharacter::MultiCast((char*)&outpacket, sizeof(outpacket));
}
}; // namespace


void CPCPacketHandler::OnUseSkill(const unsigned short in_SKID, const short in_selectedLevel, unsigned long in_targetID) // 9469-10017
{
	if( m_pc->GetEffective(EFST_NOACTION_WAIT, 0) )
		return;
	
	PC_SKILL_INFO* skInfo = m_pc->m_pcSkill.CPCSkill::GetSkill(in_SKID, FALSE);
	if( skInfo == NULL )
		return;

	bool isNoCastingByCashItem = false;
	if( skInfo->skillUseType == 4 )
	{
		if( in_targetID != m_pc->GetAccountID() )
			return;

		isNoCastingByCashItem = true;
	}

	int SKType = skInfo->type;
	switch( SKType )
	{
	case FIXED_SKILL:
	case DYNAMIC_SKILL:
	case IMITATION_SKILL:
	{
		if( !m_pc->CPC::IsSkillUsable(in_SKID) )
			return;

		unsigned long enemyAID = m_pc->GetEffective(EFST_BLADESTOP, 0);
		if( enemyAID != 0 )
		{
			if( in_SKID != SKID_MO_CHAINCOMBO && in_targetID != enemyAID )
				return;
		}
	}
	break;
	case DISPOSABLE_SKILL:
	{
		if( m_pc->CPC::GetSpellCasting() != 0 && in_SKID != SKID_SA_CASTCANCEL && in_SKID != SKID_SO_SPELLFIST )
		{
			m_pc->CPC::OnEnableItemMove(FALSE);
			Trace("Can not use skill on casting sate!!\n");
			return;
		}

		if( m_pc->m_scrollItemIndex != 0 )
		{
			if( !m_pc->m_pcitemInventoryMgr.CPCItemInventoryMgr::DeleteItem(BODY, static_cast<short>(m_pc->m_scrollItemIndex), 1) )
			{
				m_pc->m_scrollItemIndex = 0;
				return;
			}

			m_pc->CPC::NotifyDeleteItemFromBody(static_cast<unsigned short>(m_pc->m_scrollItemIndex), 1, PACKET_ZC_DELETE_ITEM_FROM_BODY::DELETE_TYPE_USE_SKILL);
			m_pc->m_scrollItemIndex = 0;
		}
	}
	break;
	};

	if( in_SKID == SKID_SL_SMA )
	{
		if( !m_pc->GetEffective(EFST_SMA_READY, 0) )
			return;
	}

	if( in_SKID == SKID_SR_DRAGONCOMBO || in_SKID == SKID_SR_FALLENEMPIRE || in_SKID == SKID_SR_TIGERCANNON || in_SKID == SKID_SR_KNUCKLEARROW || in_SKID == SKID_SR_GATEOFHELL )
	{
		if( in_targetID == m_pc->GetAccountID() )
			in_targetID = m_pc->CPC::GetTargetAID();
	}

	CCharacter* ch = CCharacterMgr::GetObj()->CCharacterMgr::FastFindCharacter(in_targetID);
	if( ch == NULL )
		return;

	if( in_SKID == SKID_WE_MALE || in_SKID == SKID_WE_FEMALE )
	{
		if( m_pc->m_marriageInfo.partnerGID == 0 )
			return;

		CCharacter* partnerCH = CCharacterMgr::GetObj()->CCharacterMgr::FindPCByGID(m_pc->m_marriageInfo.partnerGID);
		if( partnerCH == NULL || partnerCH->CCharacter::GetMapRes() != m_pc->CCharacter::GetMapRes() )
			return;

		in_targetID = partnerCH->GetAccountID();
		ch = partnerCH;
	}

	if( !m_pc->CCharacter::IsDirectPath(ch, FALSE) )
		return;

	int state;
	ch->GetParameterValue(VAR_STATE, state);

	int reqEffective = EFST_TRICKDEAD;
	ch->GetParameterValue(VAR_GETEFFECTIVE, reqEffective);

	if( in_SKID == SKID_ALL_RESURRECTION )
	{
		if( reqEffective )
			return;

		if( !ch->IsRightProperty(PROPERTY_UNDEAD) && state != CHARACTER_STATE_DEAD )
			return;
	}
	else
	if( in_SKID == SKID_WM_DEADHILLHERE )
	{
		if( reqEffective || state != CHARACTER_STATE_DEAD )
			return;
	}
	else
	{
		if( state == CHARACTER_STATE_DEAD && !reqEffective )
			return;
	}

	if( in_targetID != m_pc->m_characterInfo.accountID )
	{
		int effectState;
		ch->GetParameterValue(VAR_EFFECTSTATE, effectState);

		if( effectState & (EFFECTSTATE_HIDING | EFFECTSTATE_BURROW) )
			return;
	}

	BOOL cancelLockOn = TRUE;

	if( CPC::GetCategorySecondJob(m_pc->m_characterInfo.job) == JT_MONK )
	{
		if( in_SKID == SKID_MO_EXTREMITYFIST )
		{
			if( m_pc->GetEffective(EFST_COMBOATTACK, 0) == POSTDELAY_COMBOFINISH )
				cancelLockOn = FALSE;
			if( m_pc->GetEffective(EFST_COMBOATTACK, 0) == POSTDELAY_CHAINCRUSH )
				cancelLockOn = FALSE;
		}
		else
		if( in_SKID == SKID_MO_CHAINCOMBO || in_SKID == SKID_MO_COMBOFINISH || in_SKID == SKID_CH_TIGERFIST || in_SKID == SKID_CH_CHAINCRUSH )
			cancelLockOn = FALSE;
	}

	if( in_SKID == SKID_GC_COUNTERSLASH || in_SKID == SKID_GC_WEAPONCRUSH )
	{
		cancelLockOn = FALSE;
	}
	else
	if( in_SKID == SKID_SR_DRAGONCOMBO )
	{
		int delayType = m_pc->GetEffective(EFST_COMBOATTACK, 0);
		if( delayType == POSTDELAY_TRIPLEATTACK || delayType == POSTDELAY_TRIPLEATTACK + POSTDELAY_COMBOATTACK_BLOCK )
			cancelLockOn = FALSE;
	}
	else
	if( in_SKID == SKID_SR_FALLENEMPIRE )
	{
		int delayType = m_pc->GetEffective(EFST_COMBOATTACK, 0);
		if( delayType == POSTDELAY_DRAGONCOMBO || delayType == POSTDELAY_DRAGONCOMBO + POSTDELAY_COMBOATTACK_BLOCK )
			cancelLockOn = FALSE;
	}
	else
	if( in_SKID == SKID_SR_TIGERCANNON || in_SKID == SKID_SR_GATEOFHELL )
	{
		int delayType = m_pc->GetEffective(EFST_COMBOATTACK, 0);
		if( delayType == POSTDELAY_FALLENEMPIRE || delayType == POSTDELAY_FALLENEMPIRE + POSTDELAY_COMBOATTACK_BLOCK )
			cancelLockOn = FALSE;
	}

	if( in_SKID >= SKID_SA_MONOCELL && in_SKID <= SKID_SA_COMA )
	{
		unsigned long abraSKID = m_pc->m_pcSkill.CPCSkill::GetSKIDFromAbracadabra();
		if( abraSKID == 0 || abraSKID != in_SKID )
			return;
	}

	if( in_SKID == SKID_TK_STORMKICK || in_SKID == SKID_TK_DOWNKICK || in_SKID == SKID_TK_TURNKICK || in_SKID == SKID_TK_COUNTER )
		cancelLockOn = FALSE;

	if( in_SKID == SKID_TK_JUMPKICK )
	{
		if( m_pc->GetEffective(EFST_DODGE_READY, 0) )
			cancelLockOn = FALSE;
	}

	if( cancelLockOn )
		m_pc->CPC::CancelLockOnMode();

	int sklevel = m_pc->m_pcSkill.CPCSkill::GetSkillLevel(in_SKID, 0);
	if( in_SKID == SKID_HT_BLITZBEAT )
	{
		if( sklevel > 5 )
			sklevel = 5;
	}

	if( sklevel <= 0 )
		return;

	if( in_selectedLevel > 0 )
	{
		if( sklevel > in_selectedLevel )
			sklevel = in_selectedLevel;
	}

	if( !m_pc->CPC::IsSkillEnable(in_SKID, sklevel, ch) )
		return;

	CSkillTypeInfo* skilltypeInfo = g_skillTypeInfoMgr.CSkillTypeInfoMgr::SearchSkillTypeInfo(in_SKID);
	if( skilltypeInfo == NULL )
		return;

	if( skilltypeInfo->CSkillTypeInfo::GetType() == SKILLTYPE_PASSIVE )
		return;

	if( ch != m_pc )
	{
		short skrange = m_pc->m_pcSkill.CPCSkill::GetSkillRange(in_SKID, in_selectedLevel);

		if( CPC::GetCategorySecondJob(m_pc->m_characterInfo.job) == JT_SUPERNOVICE
		 || in_SKID == SKID_AC_DOUBLE
		 || in_SKID == SKID_AC_SHOWER
		 || in_SKID == SKID_AC_CHARGEARROW
		 || in_SKID == SKID_HT_BLITZBEAT
		 || in_SKID == SKID_HT_POWER )
		{
			int range = skrange + m_pc->CPC::GetPlusAttRange();
			if( range > 14 )
				range = 14;

			if( !m_pc->IsMyArea(ch, range + 1) )
				return;
		}
		else
		{
			int desXPos, desYPos;
			ch->GetParameterValue(VAR_CURXPOS, desXPos);
			ch->GetParameterValue(VAR_CURYPOS, desYPos);

			int dx = m_pc->m_pathInfo.m_moveInfo.xPos - desXPos;
			int dy = m_pc->m_pathInfo.m_moveInfo.yPos - desYPos;
			double distance = sqrt(double(dx * dx + dy * dy));

			if( distance > skrange + 1 )
				return;
		}
	}

	if( m_pc->GetEffective(EFST_RUN, 0) != 0 && in_SKID != SKID_TK_RUN )
	{
		m_pc->SetEffective(EFST_NOT_EXTREMITYFIST, 500, m_pc->GetEffective(EFST_RUN, 0), 0, 0, 0);
		m_pc->ResetEffective(EFST_RUN, 0);
	}

	m_pc->m_pcClientUpdater.CPCClientUpdater::StopMove();

	if( SKType != DISPOSABLE_SKILL )
	{
		time_t atime;
		m_pc->CPC::GetAttackLastTime(atime);

		time_t CurTM = timeGetTime();
		if( CurTM - atime < m_pc->CPC::GetAttackMotionTime() + g_AMTterm ) //TODO: should be unsigned
			return;

		if( in_SKID != SKID_BD_ENCORE )
			m_pc->CPC::SetAttackLastTime(CurTM);
	}

	if( in_SKID >= SKID_BD_LULLABY && in_SKID <= SKID_BD_SIEGFRIED )
	{
		CPC* parnterPC = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FastFindCharacter(m_pc->m_pcSkill.CPCSkill::GetPartnerAID());
		if( parnterPC != NULL )
		{
			short partnersklevel = parnterPC->m_pcSkill.CPCSkill::GetSkillLevel(in_SKID, 0);
			sklevel = (sklevel + partnersklevel) / 2;
		}
	}

	const int cost = m_pc->GetSPcostForSkill(in_SKID, sklevel, SKType, skilltypeInfo);
	if( SKType != DISPOSABLE_SKILL && SKType != TEMPORARY_DISPOSABLE_SKILL && m_pc->CPC::GetSP() < cost )
	{
		m_pc->SkillUseAck(in_SKID, 0, false, USESKILL_FAIL_SP_INSUFFICIENT);
		return;
	}

	if( m_pc->GetEffective(EFST_CLOAKINGEXCEED, 0) )
	{
		if( in_SKID != SKID_GC_CLOAKINGEXCEED && in_SKID != SKID_TF_HIDING && in_SKID != SKID_AS_CLOAKING )
			m_pc->ResetEffective(EFST_CLOAKINGEXCEED, 0);
	}
	else
	{
		if( in_SKID != SKID_AS_CLOAKING && in_SKID != SKID_ST_CHASEWALK )
		{
			if( m_pc->GetEffectState() & EFFECTSTATE_HIDING )
				m_pc->ResetEffectState(EFFECTSTATE_FOOTPRINT | EFFECTSTATE_HIDING);
		}
	}

	m_pc->ResetEffective(EFST_SPELLFIST, 0);

	int castTM;
	if( isNoCastingByCashItem == true )
		castTM = 0;
	else
		castTM = m_pc->m_pcBattle.CPCBattle::GetSKCastingTM(skilltypeInfo, sklevel, ch, 0, 0, cost);

	COMMAND_QUEUE command;
	command.commandID = USE_SKILL_IN;
	command.executionTime = timeGetTime();
	command.sender = m_pc->GetAccountID();
	command.par1 = in_SKID;
	command.par2 = in_targetID;
	command.par3 = sklevel;
	command.par4 = cost;
	bool IsDisposable = ( SKType == DISPOSABLE_SKILL || SKType == TEMPORARY_DISPOSABLE_SKILL );
	SendPACKET_ZC_USESKILL_ACK2(m_pc, in_targetID, in_SKID, skilltypeInfo->GetProperty(), 0, 0, castTM, IsDisposable);
	if( castTM > 0 )
	{
		m_pc->CPC::SetSpellCasting(in_SKID, sklevel);
		m_pc->m_magicTargetAID = in_targetID;
	}
	CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(m_pc, in_targetID, CM_MAGICLOCKONED, m_pc->GetAccountID(), 0, 0, 0);
	command.executionTime += castTM;
	m_pc->InsertCommand(&command);

	int val = m_pc->GetEffective(EFST_MAGICPOWER, 0);
	if( val != 0 )
	{
		if( val & 0xFFFFFF00 )
			m_pc->ResetEffective(EFST_MAGICPOWER, 0);
		else
		if( skilltypeInfo->CSkillTypeInfo::GetPattern() == SKILLPATT_ATTACKSPELL )
			m_pc->UpdateEffective(EFST_MAGICPOWER, 0x100, 0);
	}

	m_pc->CPC::SetLastTargetAID(in_targetID);
}


void CPCPacketHandler::OnUseGuildSkill(const unsigned short in_SKID, const short in_selectedLevel, const unsigned long in_targetID) // 10021-10163
{
	//TODO
}


void CPCPacketHandler::OnUseSkill_Merce(const unsigned short in_SKID, const short in_selectedLevel, const unsigned long in_targetID) // 10289-10410
{
	//TODO
}


void CPCPacketHandler::OnReqUSE_SKILL_TOGROUND_WITHTALKBOX(const short in_selectedLevel, const unsigned short in_SKID, const short in_xPos, const short in_yPos, const char* in_contents) // 10419-10436
{
	//TODO
}


void CPCPacketHandler::OnCancelLockOn(int len) // 10635-10639
{
	//TODO
/*
	PACKET_CZ_CANCEL_LOCKON packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

	m_pc->CPC::CancelLockOnMode();
*/
}


void CPCPacketHandler::LockOnAttack() // 10642-10648
{
	//TODO
}


void CPCPacketHandler::CounterAttack(unsigned long targetID) // 10651-10659
{
	//TODO
}


void CPCPacketHandler::OnSelectWarpPoint(int len) // 10666-10740
{
	//TODO
}


void CPCPacketHandler::OnRememberWarpPoint(int len) // 10743-10755
{
	//TODO
}


void CPCPacketHandler::OnCartOff(int len) // 10758-10763
{
	//TODO
}


void CPCPacketHandler::OnReqCloseMCStore(int len) // 10766-10777
{
	//TODO
}


void CPCPacketHandler::OnReqOpenMCStore(int len) // 10780-10798
{
	//TODO
}


void CPCPacketHandler::OnReqOpenMCStore2(int len) // 10801-10944
{
	//TODO
}


void CPCPacketHandler::OnReqItemListFromMCStore(int len) // 10947-10965
{
	//TODO
}


void CPCPacketHandler::PurchaseItemFromMCStore(int len) // 10968-10997
{
	//TODO
}


void CPCPacketHandler::PurchaseItemFromMCStore2(int len) // 11001-11033
{
	//TODO
}


void CPCPacketHandler::OnPKModeChange(int len) // 11036-11048
{
	//TODO
}


namespace {
void SendGMWhisper(CPC* in_PC, const char* in_pFmt, ...) // 11052-11068
{
	char buf[2048] = {};
	PACKET_ZC_WHISPER& packet = *reinterpret_cast<PACKET_ZC_WHISPER*>(buf);

	va_list va;
	va_start(va, in_pFmt);
	_vsnprintf_s(packet.Text, sizeof(buf) - sizeof(packet), _TRUNCATE, in_pFmt, va);

	packet.PacketType = HEADER_ZC_WHISPER;
	packet.PacketLength = sizeof(packet) + strlen(packet.Text) + 1;
	strcpy(packet.sender, "SERVER");
	in_PC->CPC::ForceSend(packet.PacketLength, (char*)&packet);
}


bool GM_RegenBoss(CPC* in_PC, const char* in_String) // 11071-11111
{
	return false;
	//TODO
}


bool GM_OneKillMonster(CPC* in_PC, const char* in_String) // 11114-11139
{
	return false;
	//TODO
}


bool GM_BossInfo(CPC* in_PC, const char* in_String) // 11142-11185
{
	return false;
	//TODO
}


bool GM_TryCaptureMonster(CPC* in_PC, const char* in_String) // 11229-11295
{
	return false;
	//TODO
}
}; // namespace


void CPCPacketHandler::OnItemCreate(const std::string in_cmdline) // 11913-12628
{
	//TODO
}


void CPCPacketHandler::OnAdminMapMove(int len) // 12631-12702
{
	//TODO
}


void CPCPacketHandler::OnInputEditDlg(int len) // 12705-12710
{
	//TODO
}


void CPCPacketHandler::OnCloseDialog(int len) // 12713-12720
{
	//TODO
}


void CPCPacketHandler::OnReqGuildMenuInterface(int len) // 12726-12777
{
	//TODO
}


void CPCPacketHandler::OnReqGuildMenu(int len) // 12780-13041
{
	//TODO
}


void CPCPacketHandler::OnReqGuildEmblemImg(int len) // 13090-13182
{
	//TODO
}


void CPCPacketHandler::OnRegisterGuildEmblemImg(int len) // 13187-13223
{
	//TODO
}


void CPCPacketHandler::OnReqChangeMemberPos(int len) // 13226-13270
{
	//TODO
}


void CPCPacketHandler::OnReqOpenMemberInfo(int len) // 13273-13300
{
	//TODO
}


void CPCPacketHandler::OnReqLeaveGuild(int len) // 13303-13334
{
	//TODO
}


void CPCPacketHandler::OnReqBanGuild(int len) // 13337-13403
{
	//TODO
}


void CPCPacketHandler::OnReqDisorganizeGuild(int len) // 13407-13450
{
	//TODO
}


void CPCPacketHandler::OnReqChangeGuildPositionInfo(int len) // 13453-13489
{
	//TODO
}


void CPCPacketHandler::OnReqMakeGuild(int packetLen) // 13494-13627
{
	//TODO
}


void CPCPacketHandler::OnReqJoinGuild(int packetSize) // 13631-13688
{
	//TODO
}


void CPCPacketHandler::OnJoinGuild(int packetSize) // 13692-13754
{
	//TODO
}


void CPCPacketHandler::OnGiveMannerPoint(int packetSize) // 13757-13879
{
	//TODO
}


void CPCPacketHandler::OnGuildNotice(int packetSize) // 13882-13901
{
	//TODO
}


void CPCPacketHandler::OnGuildChat(int packetSize) // 13904-13942
{
	//TODO
}


void CPCPacketHandler::OnReqAllyGuild(int packetSize) // 13945-14021
{
	//TODO
}


void CPCPacketHandler::OnAllyGuild(int packetSize) // 14024-14076
{
	//TODO
}


void CPCPacketHandler::SendAckReqAllyGuild(unsigned long AID, unsigned char answer) // 14079-14084
{
	//TODO
}


void CPCPacketHandler::OnReqItemIdentify(int len) // 14087-14091
{
	//TODO
}


void CPCPacketHandler::OnReqItemCompositionList(int len) // 14094-14099
{
	//TODO
}


void CPCPacketHandler::OnReqItemComposition(int len) // 14102-14108
{
	//TODO
}


void CPCPacketHandler::OnReqHostileGuild(int len) // 14111-14160
{
	//TODO
}


void CPCPacketHandler::SendAckReqHostileGuild(unsigned long AID, unsigned char answer) // 14163-14168
{
	//TODO
}


void CPCPacketHandler::OnReqDeleteRelatedGuild(int Len) // 14171-14205
{
	//TODO
}


void CPCPacketHandler::OnReqDisconnect(int len) // 14208-14224
{
	//TODO
}


void CPCPacketHandler::OnReqMakingItem(int len) // 14227-14259
{
	//TODO
}


void CPCPacketHandler::ResetReqGuildTime() // 14262-14266
{
	m_ReqGuildEmblemTime = timeGetTime() - 10000;

	for( int i = 0; i < countof(m_ReqGuildMenuTime); ++i )
		m_ReqGuildMenuTime[i] = timeGetTime() - 10000;
}


void CPCPacketHandler::OnReqNameByGID(const unsigned long in_GID) // 14270-14284
{
	//TODO
}


void CPCPacketHandler::OnReqGuildMemberInfo(int len) // ???? (10665-10694)
{
	//TODO
}


void CPCPacketHandler::OnResetParameter(int len) // 14319-14348 (10697-10721)
{
	//TODO
}


void CPCPacketHandler::OnChangeMapType(int len) // 14351-14388 (10724-10734)
{
	//TODO
}


void CPCPacketHandler::OnChangeEffectState(int len) // 14391-14405
{
	//TODO
}


void CPCPacketHandler::OnTryCaptureMonster(int len) // 14408-14419
{
	//TODO
}


void CPCPacketHandler::OnCZ_TRYCOLLECTION(const PACKET_CZ_TRYCOLLECTION& in_packet) // 14426 +-
{
	m_pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
}


void CPCPacketHandler::OnCommandPet(int len) // 14431-14443
{
	//TODO
}


void CPCPacketHandler::OnRenamePet(int len) // 14446-14458 (10780-10792)
{
	//TODO
}


void CPCPacketHandler::OnRenameHomun(int len) // 14461-14476
{
	//TODO
}


void CPCPacketHandler::OnSelectPetEgg(int len) // 14479-14490
{
	//TODO
}


void CPCPacketHandler::OnPetEggInfo(int len) // 14493-14504
{
	//TODO
}


void CPCPacketHandler::OnPetAct(int len) // 14507-14518 (10841-10852)
{
	//TODO
}


void CPCPacketHandler::OnMakingItem() // 14521-14545 (10855-10860)
{
	//TODO
}


void CPCPacketHandler::OnGuildZeny(int len) // 14549-14583
{
	PACKET_CZ_GUILD_ZENY in;
	m_recvQueue->CPacketQueue::GetData(sizeof(in), (char*)&in);
}


void MakeLower(char* text) // 14586-14595
{
	//TODO
}


void CPCPacketHandler::OnShift(int len) // 14662-14725 (10962-11001)
{
	//TODO
}


void CPCPacketHandler::OnRecall(int len) // 14728-14781 (11004-11049)
{
	//TODO
}


void CPCPacketHandler::OnRecallGID(int len) // 14784-14845 (11052-11085)
{
	//TODO
}


void CPCPacketHandler::OnReqEncryption(int len) // 14848-14864 (11088-11104)
{
	//TODO
}


void CPCPacketHandler::OnSelectAutoSpell(int len) // 14868-14892 (11108-11132)
{
	//TODO
}


void CPCPacketHandler::OnInputEditDlgStr(int len) // 14898-14915 (11138-11155)
{
	//TODO
}


void CPCPacketHandler::OnSit() // ???? (11158-11168)
{
	//TODO
}


void CPCPacketHandler::OnAddFriend(int len) // 14929-14952
{
	//TODO
}


void CPCPacketHandler::OnDeleteFriend(int len) // 14955-14965
{
	//TODO
}


void CPCPacketHandler::OnAckReqAddFriends(int len) // 14968-14995
{
	//TODO
}


void CPCPacketHandler::OnReqPVPPoint(int len) // ?14998-15007? (11234-11241)
{
	//TODO
}


void CPCPacketHandler::OnGiveMannerPointByName(int len) // 15010-15035 (11245-11266)
{
	//TODO
}


void CPCPacketHandler::OnReqStatus(int len) // 15038-15052
{
	//TODO
}


void CPCPacketHandler::OnReqMakerRanking(const short in_PacketType, const int in_PacketLength) // 15057-15100
{
	//TODO
}


void CPCPacketHandler::OnReqKSY(int len) // 15103-15107
{
	//TODO
}


void CPCPacketHandler::OnLessEffect(int len) // 15110-15115 (11418-11423)
{
	PACKET_CZ_LESSEFFECT packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

	m_pc->CPC::SetLessEffect(packet.isLess);
}


void CPCPacketHandler::OnAckGameGuard(int len) // 15129-15151 (11426-11445)
{
	//TODO
}


void CPCPacketHandler::OnCommandMercenary(int len) // 15154-15186
{
	//TODO
}


void CPCPacketHandler::OnRequestMoveToOwner(int len) // 15190-15220
{
	//TODO
}


void CPCPacketHandler::OnRequestMoveNpc(int len) // 15224-15267
{
	//TODO
}


hook_func<void (__stdcall *)()> CPCPacketHandler__OnRequestActNpc(EXEPATH(), "CPCPacketHandler::OnRequestActNpc");
void CPCPacketHandler::OnRequestActNpc(int len) // 15271-15311
{
	void* hookptr = CPCPacketHandler__OnRequestActNpc;
	__asm mov ecx, this
	__asm call hookptr
	return; //TODO
/*
	if( !this->CPCPacketHandler::CheckRequestNpcTime() )
		return;

	PACKET_CZ_REQUEST_ACTNPC packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

	if( !m_pc->CPC::IsValid() )
	{
		m_pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
		return;
	}

	if( packet.GID == m_pc->m_pcBattle.m_myHomunID )
	{
		if( packet.action == 0 )
		{
			CNpcHomun* pHomun = m_pc->m_pcBattle.CPCBattle::GetMyHomun();
			if( pHomun != NULL )
			{
				if( pHomun->m_npcSkill.m_spellCastingSKID == 0 )
				{
					if( CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, packet.GID, CM_ATTACK_ENEMY, packet.targetGID, 0, 0, 0) )
					{
						int enemyAID = packet.targetGID;
						if( packet.targetGID == pHomun->GetAccountID() )
							enemyAID = 0;

						pHomun->m_npcStateUpdater.m_npcStateInfo.enemyAID = enemyAID;
					}
				}
			}
		}
	}

	if( packet.GID == m_pc->m_pcBattle.m_mercenaryID )
		this->CPCPacketHandler::OnMercenary_RequestActNpc(&packet);
*/
}


void CPCPacketHandler::OnAckStorePassword(int len) // 15318-15322
{
	//TODO
}


bool CPCPacketHandler::CheckRequestNpcTime() // 15325-15334
{
	return ( abs((int)GetTickCount() - (int)m_RequestNpcTime) >= 200 );
}


void CPCPacketHandler::OnMailGetList(int len) // 15337-15350
{
	//TODO
}


void CPCPacketHandler::OnMailOpen(int len) // 15353-15367
{
	//TODO
}


void CPCPacketHandler::OnMailDelete(int len) // 15370-15384
{
	//TODO
}


void CPCPacketHandler::OnMailGetItem(int len) // 15387-15400
{
	//TODO
}


void CPCPacketHandler::OnMailResetItem(int len) // 15403-15421
{
	//TODO
}


void CPCPacketHandler::OnMailAddItem(int len) // 15424-15446
{
	//TODO
}


void CPCPacketHandler::OnMailSend(int len) // 15466-15580
{
	//TODO
}


void CPCPacketHandler::OnMailReturn(int len) // 15584-15608
{
	//TODO
}


void CPCPacketHandler::OnAuctionCreate(int len) // 15612-15618
{
	//TODO
}


void CPCPacketHandler::OnAuctionAddItem(int len) // 15622-15633
{
	//TODO
}


void CPCPacketHandler::OnAuctionAdd(int len) // 15637-15714
{
	//TODO
}


void CPCPacketHandler::OnAuctionAddCancel(int len) // 15717-15735
{
	//TODO
}


void CPCPacketHandler::OnAuctionBuy(int len) // 15738-15764
{
	//TODO
}


void CPCPacketHandler::OnAuctionItemSearch(int len) // 15767-15789
{
	//TODO
}


void CPCPacketHandler::OnAuctionReqMyInfo(int len) // 15792-15800
{
	//TODO
}


void CPCPacketHandler::OnAuctionMySellStop(int len) // 15803-15814
{
	//TODO
}


void CPCPacketHandler::OnHuntingList(int len) // 15821-15834
{
	//TODO
}


void CPCPacketHandler::OnPCBuyCashPointItem(const int len) // 15841-15959
{
	//TODO
}


void CPCPacketHandler::OnPCBuyCashPointItemSimpleShop(int len) // 15962-16011
{
	//TODO
}


void CPCPacketHandler::OnStandingResurrection(int len) // 16016-16020 (12142-12152)
{
	//TODO
}


bool CPCPacketHandler::SendMsgItemScriptEvent(int senderAID, unsigned long msgID, int par1, int par2, int par3) // 16023-16032
{
	return false;
	//TODO
}


bool CPCPacketHandler::CheckMap(unsigned long AID, unsigned long type) // 16036-16061
{
	return false;
	//TODO
}


bool CPCPacketHandler::ForcedCloseDialog(unsigned long NPCID) // ??? (12196-12202)
{
	return false;
	//TODO
}


hook_func<void (CPCPacketHandler::*)(const PACKET_CZ_MER_COMMAND* in_pPacket)> CPCPacketHandler__OnMercenary_Command(EXEPATH(), "CPCPacketHandler::OnMercenary_Command");
void CPCPacketHandler::OnMercenary_Command(const PACKET_CZ_MER_COMMAND* in_pPacket) // 16074-16095
{
	return (this->*CPCPacketHandler__OnMercenary_Command)(in_pPacket);
	//TODO
/*
	if( !this->CPCPacketHandler::CheckRequestNpcTime() )
		return;

	if( !m_pc->CPC::IsValid() )
	{
		m_pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
		return;
	}

	int mercenaryAID = m_pc->m_pcBattle.m_mercenaryID;
	if( mercenaryAID == 0 )
		return;

	if( in_pPacket->command == PACKET_CZ_MER_COMMAND::COMMAND_REQ_PROPERTY )
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(m_pc, mercenaryAID, CM_MERCE_PROPERTY, 0, 0, 0, 0);
	else
	if( in_pPacket->command == PACKET_CZ_MER_COMMAND::COMMAND_REQ_DELETE )
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(m_pc, mercenaryAID, CM_MERCE_DELETE, mercenaryAID, 2, 0, 0);
*/
}


hook_func<void (__stdcall *)()> CPCPacketHandler__OnMercenary_RequestActNpc(EXEPATH(), "CPCPacketHandler::OnMercenary_RequestActNpc");
void CPCPacketHandler::OnMercenary_RequestActNpc(const PACKET_CZ_REQUEST_ACTNPC* in_pPacket) // 16103-16130
{
	void* hookptr = CPCPacketHandler__OnMercenary_RequestActNpc;
	__asm mov ebx, in_pPacket
	__asm mov ecx, this
	__asm call hookptr
	return; //TODO
/*
	CNpcMercenary* pMercenary = m_pc->m_pcBattle.CPCBattle::GetMercenary();
	if( pMercenary == NULL )
		return;

	if( in_pPacket->GID != pMercenary->GetAccountID() )
		return;

	if( !this->CPCPacketHandler::CheckRequestNpcTime() )
		return;

	if( !m_pc->CPC::IsValid() )
	{
		m_pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
		return;
	}

	if( pMercenary->m_npcSkill.m_spellCastingSKID != 0 && pMercenary->GetSKLevel(SKID_SA_FREECAST) == 0 )
		return;

	if( in_pPacket->action != 0 )
		return;

	CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, in_pPacket->GID, CM_ATTACK_ENEMY, in_pPacket->targetGID, 0, 0, 0);
*/
}


hook_func<void (__stdcall *)()> CPCPacketHandler__OnMercenary_UseSkill(EXEPATH(), "CPCPacketHandler::OnMercenary_UseSkill");
void CPCPacketHandler::OnMercenary_UseSkill(const unsigned short in_SKID, const short in_selectedLevel, unsigned long in_targetID) // 16136-16211
{
	void* hookptr = CPCPacketHandler__OnMercenary_UseSkill;
	__asm push in_targetID
	__asm push in_selectedLevel
	__asm push in_SKID
	__asm push this
	__asm call CPCPacketHandler__OnMercenary_UseSkill
	return; //TODO
}


void CPCPacketHandler::OnCashPassword(int len) // 16422-16429 (12536-12543)
{
	//TODO
}


void CPCPacketHandler::OnShortcutKey_Change(int len) // 16432-16446
{
	//TODO
}


void CPCPacketHandler::OnActiveQuest(int len) // 16450-16459
{
	//TODO
}


void CPCPacketHandler::OnBattleFieldChat(int len) // 16463-16490
{
	//TODO
}


void CPCPacketHandler::BroadcastNewPosition(int dx, int dy) // 16493-16527
{
	//TODO
}


void CPCPacketHandler::NotifyBattleFieldPoint() // 16530-16540
{
	//TODO
}


void CPCPacketHandler::OnProgress(int len) // 16543-16582 (12665-12703)
{
	//TODO
}


void CPCPacketHandler::OnCzOpenSimpleCashShopItemList(int len) // 16585-16607
{
	//TODO
}


void CPCPacketHandler::OnCZOnCloseWindow(int len) // 16610-16620
{
	//TODO
}


void CPCPacketHandler::RequestSit() // 16675-16683 (12788-12798)
{
	//TODO
}


void CPCPacketHandler::OnCZClientVersion(int len) // 16687-16691 (12802-12806)
{
	//TODO
}


void CPCPacketHandler::OnCZCloseSimpleCashShop(int len) // 16696-16710 (12811-12820)
{
	//TODO
}


void CPCPacketHandler::OnCZSimpleCashBtnShow(int len) // 16713-16727
{
	//TODO
}


hook_func<void (__stdcall *)()> CPCPacketHandler__OnCZ_GROUPINFO_CHANGE_V2(EXEPATH(), "CPCPacketHandler::OnCZ_GROUPINFO_CHANGE_V2");
void CPCPacketHandler::OnCZ_GROUPINFO_CHANGE_V2(const PACKET_CZ_GROUPINFO_CHANGE_V2& in_packet) // 16779-16804
{
	void* hookptr = CPCPacketHandler__OnCZ_GROUPINFO_CHANGE_V2;
	__asm lea ecx, in_packet
	__asm push this
	__asm call hookptr
	return; //TODO
}


void CPCPacketHandler::OnChangeGroupMaster(int len) // 16911-16925 (12892-12906)
{
	//TODO
}


void CPCPacketHandler::OnSeekParty(int len) // ???? (12909-12946)
{
	//TODO
}


void CPCPacketHandler::OnSeekPartyMember(int len) // ???? (12949-12984)
{
	//TODO
}


void CPCPacketHandler::OnReqOpenBuyingStore(const int len) // 17007-17111
{
	//TODO
}


void CPCPacketHandler::OnReqClickToBuyingStore(const int len) // 17118-17137
{
	//TODO
}


void CPCPacketHandler::OnReqTradeBuyingStore(const int len) // 17141-17170
{
	//TODO
}


void CPCPacketHandler::OnReqCloseBuyingStore(const int len) // 17194-17199
{
	//TODO
}


void CPCPacketHandler::OnSearchStoreInfo(const int len) // 17300-17352
{
	//TODO
}


void CPCPacketHandler::OnSearchStoreInfoNexPage(const int len) // 17433-17457
{
	//TODO
}


void CPCPacketHandler::OnCloseSearchStoreInfo(const int len) // 17461-17466
{
	//TODO
}


void CPCPacketHandler::OnSSIListItemClick(const int len) // 17547-17595
{
	//TODO
}


bool CPCPacketHandler::CheckSameMap(unsigned long AID, unsigned long type) // 17601-17617
{
	return false;
	//TODO
}


void CPCPacketHandler::OnCZMove_AID_SSO(const int len) // 17760-17807
{
	//TODO
}


void CPCPacketHandler::OnCZRecall_SSO(const int len) // 17760-17807
{
	//TODO
}


void CPCPacketHandler::OnCZReqSchedulerCashItem(const PACKET_CZ_REQ_SCHEDULER_CASHITEM& packet) // 17811-17816
{
	//TODO
}


void CPCPacketHandler::OnCZ_SE_CASHSHOP_OPEN(const PACKET_CZ_SE_CASHSHOP_OPEN& in_packet) // 17821-17849
{
	//TODO
}


void CPCPacketHandler::OnCZReqSeCashTabCode(const int len) // 17855-17859
{
	//TODO
}


void CPCPacketHandler::OnCZSePcBuyCashItemList(const int len) // 17862-17924
{
	//TODO
}


void CPCPacketHandler::OnCZSeCashShopClose(const int len) // 17927-17938
{
	//TODO
}


void CPCPacketHandler::OnCZ_USE_SKILL(const int in_SKID, const int in_Level, const unsigned long in_TargetID) // 17947-17971
{
	switch( g_skillTypeInfoMgr.CSkillTypeInfoMgr::GetSKClass(in_SKID) )
	{
	case SKCLASS_NORMAL:
		this->CPCPacketHandler::OnUseSkill(in_SKID, in_Level, in_TargetID);
	break;
	case SKCLASS_HOMUN:
		this->CPCPacketHandler::OnUseSkill_Merce(in_SKID, in_Level, in_TargetID);
	break;
	case SKCLASS_GUILD:
		this->CPCPacketHandler::OnUseGuildSkill(in_SKID, in_Level, in_TargetID);
	break;
	case SKCLASS_MERCE2:
		this->CPCPacketHandler::OnMercenary_UseSkill(in_SKID, in_Level, in_TargetID);
	break;
	};

	m_pc->m_pcSkill.CPCSkill::SetSKIDFromAbracadabra(0);
}


hook_func<void (__stdcall *)()> CPCPacketHandler__OnMercenary_UseSkill_ToGround(EXEPATH(), "CPCPacketHandler::OnMercenary_UseSkill_ToGround");
void CPCPacketHandler::OnMercenary_UseSkill_ToGround(const int in_SKID, const int in_SelectedLevel, const int in_targetXpos, const int in_targetYpos) // 17977-18136
{
	void* hookptr = CPCPacketHandler__OnMercenary_UseSkill_ToGround;
	__asm push in_targetYpos
	__asm push in_targetXpos
	__asm push in_SelectedLevel
	__asm push in_SKID
	__asm push this
	__asm call hookptr
	return; //TODO
}


hook_func<void (CPCPacketHandler::*)(const int in_SKID, const int in_SelectedLevel, const int in_targetXpos, const int in_targetYpos)> CPCPacketHandler__OnUseSkillToGround_Homun(EXEPATH(), "CPCPacketHandler::OnUseSkillToGround_Homun");
void CPCPacketHandler::OnUseSkillToGround_Homun(const int in_SKID, const int in_SelectedLevel, const int in_targetXpos, const int in_targetYpos) // 18141-18252
{
	(this->*CPCPacketHandler__OnUseSkillToGround_Homun)(in_SKID, in_SelectedLevel, in_targetXpos, in_targetYpos);
	//TODO
}


hook_func<void (__stdcall *)()> CPCPacketHandler__OnUseSkillToGround(EXEPATH(), "CPCPacketHandler::OnUseSkillToGround");
void CPCPacketHandler::OnUseSkillToGround(const int in_SKID, const int in_SelectedLevel, const int in_targetXpos, const int in_targetYpos) // 18257-18455
{
	void* hookptr = CPCPacketHandler__OnUseSkillToGround;
	__asm push in_targetYpos
	__asm push in_targetXpos
	__asm push in_SelectedLevel
	__asm push in_SKID
	__asm mov eax, this
	__asm call hookptr
	return; //TODO

	if( m_pc->GetEffective(EFST_NOACTION_WAIT, 0) )
		return;

	int SKType = m_pc->m_pcSkill.CPCSkill::GetSkillType(in_SKID);
	switch( SKType )
	{
	case FIXED_SKILL:
	case DYNAMIC_SKILL:
	case IMITATION_SKILL:
		if( !m_pc->CPC::IsSkillUsable(in_SKID) )
			return;
	break;
	case DISPOSABLE_SKILL:
		if( m_pc->CPC::GetSpellCasting() != 0 && in_SKID != SKID_SA_CASTCANCEL )
		{
			Trace("Can not use skill on casting sate!!\n");
			return;
		}
	break;
	};

	m_pc->CPC::CancelLockOnMode();

	short sklevel = m_pc->m_pcSkill.CPCSkill::GetSkillLevel(in_SKID, 0);
	if( sklevel <= 0 )
		return;

	if( in_SelectedLevel > 0 && sklevel > in_SelectedLevel )
		sklevel = in_SelectedLevel;

	CSkillTypeInfo* skilltypeInfo = g_skillTypeInfoMgr.CSkillTypeInfoMgr::SearchSkillTypeInfo(in_SKID);
	if( skilltypeInfo == NULL )
		return;

	if( m_pc->m_mapRes == NULL )
		return;

	if( !m_pc->m_mapRes->CMapRes::IsDirectPath(m_pc->m_pathInfo.m_moveInfo.dxPos, m_pc->m_pathInfo.m_moveInfo.dyPos, in_targetXpos, in_targetYpos, FALSE) )
	{
		m_pc->SkillUseAck(in_SKID, 0, false, USESKILL_FAIL);
		return;
	}

	if( !m_pc->CPC::IsSkillEnable(in_SKID, sklevel, NULL) )
		return;

	if( m_pc->GetEffective(EFST_RUN, 0) )
		m_pc->ResetEffective(EFST_RUN, 0);

	int range = g_skillTypeInfoMgr.CSkillTypeInfoMgr::GetAttackRange(in_SKID, in_SelectedLevel) + m_pc->CPC::GetPlusAttRange() + 1;
	if( range > 14 )
		range = 14;

	int dx = m_pc->m_pathInfo.m_moveInfo.xPos - in_targetXpos;
	int dy = m_pc->m_pathInfo.m_moveInfo.yPos - in_targetYpos;
	if( in_SKID == SKID_AC_SHOWER )
	{
		if( abs(dx) > range || abs(dy) > range )
			return;
	}
	else
	{
		if( sqrt(double(dx * dx + dy * dy)) > range + 1 )
			return;
	}

	m_pc->m_pcClientUpdater.CPCClientUpdater::StopMove();

	time_t atime;
	m_pc->CPC::GetAttackLastTime(atime);
	DWORD CurTM = timeGetTime();

	if( CurTM - atime >= DWORD(g_AMTterm + m_pc->CPC::GetAttackMotionTime()) )
	{
		m_pc->CPC::SetAttackLastTime(CurTM);

		const int SPCost = m_pc->GetSPcostForSkill(in_SKID, sklevel, SKType, skilltypeInfo);
		if( SKType != DISPOSABLE_SKILL && SKType != TEMPORARY_DISPOSABLE_SKILL && m_pc->CPC::GetSP() < SPCost )
		{
			m_pc->SkillUseAck(in_SKID, 0, false, USESKILL_FAIL_SP_INSUFFICIENT);
			return;
		}

		if( m_pc->GetEffective(EFST_CLOAKINGEXCEED, 0) )
			m_pc->ResetEffective(EFST_CLOAKINGEXCEED, 0);

		if( m_pc->GetEffectState() & EFFECTSTATE_HIDING )
			m_pc->ResetEffectState(EFFECTSTATE_HIDING);

		m_pc->ResetEffective(EFST_SPELLFIST, 0);
		const int CastTM = m_pc->m_pcBattle.CPCBattle::GetSKCastingTM(skilltypeInfo, sklevel, 0, in_targetXpos, in_targetYpos, SPCost);

		COMMAND_QUEUE command;
		command.commandID = USE_GROUNDSKILL_IN;
		command.executionTime = timeGetTime();
		command.sender = m_pc->GetAccountID();
		command.par1 = in_SKID;
		command.par2 = in_targetXpos;
		command.par3 = in_targetYpos;
		command.par4 = sklevel;
		command.par5 = SPCost;
		bool IsDisposable = ( SKType == DISPOSABLE_SKILL || SKType == TEMPORARY_DISPOSABLE_SKILL );
		SendPACKET_ZC_USESKILL_ACK2(m_pc, 0, in_SKID, skilltypeInfo->GetProperty(), in_targetXpos, in_targetYpos, CastTM, IsDisposable);
		if( CastTM > 0 )
			m_pc->CPC::SetSpellCasting(in_SKID, sklevel);
		command.executionTime += CastTM;
		m_pc->InsertCommand(&command);

		int val = m_pc->GetEffective(EFST_MAGICPOWER, 0);
		if( val != 0 )
		{
			if( val & 0xFFFFFF00 )
				m_pc->ResetEffective(EFST_MAGICPOWER, 0);
			else
			if( skilltypeInfo->CSkillTypeInfo::GetPattern() == SKILLPATT_ATTACKSPELL )
				m_pc->UpdateEffective(EFST_MAGICPOWER, 0x100, 0);
		}

		m_pc->CPC::SetLastTargetAID(0);
	}
}


void CPCPacketHandler::OnCZ_REQUEST_MOVE(const unsigned char* in_dest) // 18549-18615
{
	//TODO
}


void CPCPacketHandler::OnCZ_USE_SKILL_TOGROUND(const int in_SKID, const int in_SelectedLevel, const int in_targetXpos, const int in_targetYpos) // 18461-18478
{
	int skClass = g_skillTypeInfoMgr.CSkillTypeInfoMgr::GetSKClass(in_SKID);
	if( skClass == SKCLASS_HOMUN )
		this->CPCPacketHandler::OnUseSkillToGround_Homun(in_SKID, in_SelectedLevel, in_targetXpos, in_targetYpos);
	else
	if( skClass == SKCLASS_MERCE2 )
		this->CPCPacketHandler::OnMercenary_UseSkill_ToGround(in_SKID, in_SelectedLevel, in_targetXpos, in_targetYpos);
	else
	{
		this->CPCPacketHandler::OnUseSkillToGround(in_SKID, in_SelectedLevel, in_targetXpos, in_targetYpos);
	}
}


BOOL CPCPacketHandler::StartPath(const unsigned char in_dest[3], const DWORD in_startTime) // 18485-18540
{
	return FALSE;
	//TODO
}


void CPCPacketHandler::OnCZ_ITEM_PICKUP(const unsigned long in_ITAID) // 18620-18632
{
	//TODO
}


void CPCPacketHandler::OnCZ_MACRO_USE_SKILL(const PACKET_CZ_MACRO_USE_SKILL& in_packet) // 18667 +-
{
	m_pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
}


void CPCPacketHandler::OnCZ_MACRO_USE_SKILL_TOGROUND(const PACKET_CZ_MACRO_USE_SKILL_TOGROUND in_packet) // 18702 +-
{
	m_pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
}


void CPCPacketHandler::OnCZ_MACRO_REQUEST_MOVE(const PACKET_CZ_MACRO_REQUEST_MOVE& in_packet) // 18735 +-
{
	m_pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
}


void CPCPacketHandler::OnCZ_MACRO_ITEM_PICKUP(const PACKET_CZ_MACRO_ITEM_PICKUP in_packet) // 18768 +-
{
	m_pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
}


void CPCPacketHandler::OnCZ_MACRO_REQUEST_ACT(const PACKET_CZ_MACRO_REQUEST_ACT& in_packet) // 18801 +-
{
	m_pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
}


void CPCPacketHandler::OnCZ_MACRO_START(const PACKET_CZ_MACRO_START& in_packet) // ????
{
}


void CPCPacketHandler::OnCZ_MACRO_STOP(const PACKET_CZ_MACRO_STOP& in_packet) // ????
{
}


void CPCPacketHandler::OnCZ_GPK_DYNCODE_RELOAD(const PACKET_CZ_GPK_DYNCODE_RELOAD& in_packet) // 18941 +-
{
	m_pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
}


void CPCPacketHandler::OnCZ_GPK_AUTH(const PACKET_CZ_GPK_AUTH& in_packet) // 18995 +-
{
	m_pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
}


void CPCPacketHandler::OnCZ_REMOVE_AID(const PACKET_CZ_REMOVE_AID& in_packet) // 19011-19067
{
	//TODO
}


void CPCPacketHandler::OnCZ_CONTACTNPC(const PACKET_CZ_CONTACTNPC& in_Packet) // 19099-19179
{
	//TODO
}


hook_func<void (__stdcall *)()> CPCPacketHandler__OnCZ_CHOPOKGI(EXEPATH(), "CPCPacketHandler::OnCZ_CHOPOKGI");
void CPCPacketHandler::OnCZ_CHOPOKGI(const PACKET_CZ_CHOPOKGI& in_packet) // 19185-19226
{
	void* hookptr = CPCPacketHandler__OnCZ_CHOPOKGI;
	__asm mov edi, this
	__asm call hookptr
	return; //TODO
/*
	if( CPC::GetCategorySecondJob(m_pc->m_characterInfo.job) != JT_SUPERNOVICE )
		return;

	if( m_pc->m_characterInfo.clevel >= GetMaxCharacterLevel(m_pc->m_characterInfo.job) )
		return;

	int myEXP = 0;
	m_pc->GetParameterValue(VAR_EXP, myEXP);
	if( myEXP <= 0 )
		return;

	int nextEXP = g_expParameter.CExpParameter::GetNextExp(m_pc->m_characterInfo.clevel, m_pc->m_characterInfo.job);
	if( nextEXP <= 0 )
		return;

	if( int((double)myEXP / (double)nextEXP * 1000.0) % 100 != 0 )
		return;

	m_pc->SetEffective(EFST_EXPLOSIONSPIRITS, 180000, 500, 0, 0, 0);
	m_pc->CPC::NotifyUseSkill(SKID_MO_EXPLOSIONSPIRITS, m_pc->m_characterInfo.accountID, m_pc->m_characterInfo.accountID, 5, true);
*/
}


void CPCPacketHandler::OnCZ_REQ_ENTRY_QUEUE_APPLY(const PACKET_CZ_REQ_ENTRY_QUEUE_APPLY& in_packet) // 19245 +-
{
	m_pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
}


void CPCPacketHandler::OnCZ_REQ_ENTRY_QUEUE_CANCEL(const PACKET_CZ_REQ_ENTRY_QUEUE_CANCEL& in_packet) // 19264 +-
{
	m_pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
}


void CPCPacketHandler::OnCZ_REPLY_ENTRY_QUEUE_ADMISSION(const PACKET_CZ_REPLY_ENTRY_QUEUE_ADMISSION& in_packet) // 19283 +-
{
	m_pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
}


void CPCPacketHandler::OnCZ_REPLY_LOBBY_ADMISSION(const PACKET_CZ_REPLY_LOBBY_ADMISSION& in_packet) // 19304 +-
{
	m_pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
}


void CPCPacketHandler::OnCZ_REQ_ENTRY_QUEUE_RANKING(const PACKET_CZ_REQ_ENTRY_QUEUE_RANKING& in_packet) // 19323 +-
{
	m_pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
}


namespace _CHANGE_CART {
std::map<int,int> GetTableInfo() // 19419-19442
{
	return std::map<int,int>();
	//TODO
}


bool IsAbleChangeCart(const int in_num, const int in_Level) // 19445-19450
{
	return false;
	//TODO
}
}; // namespace


void CPCPacketHandler::OnCZ_REQ_CHANGECART(const PACKET_CZ_REQ_CHANGECART& in_packet) // 19453-19462
{
	//TODO
}


void CPCPacketHandler::OnCZ_REQ_MERGE_ITEM(const int in_packetSize, const char* in_pPacket) // 19565-19626
{
	//TODO
}


void CPCPacketHandler::OnCZ_CANCEL_MERGE_ITEM() // 19629-19632
{
	--m_pc->m_lockCounter;
	m_pc->CCharacter::SetInstantVar(CInstantVar::OPEN_MERGE_ITEM, 0);
}


void CPCPacketHandler::OnCZ_REQ_RANKING(const PACKET_CZ_REQ_RANKING& in_packet) // ????
{
}


void CPCPacketHandler::OnCZ_CLAN_CHAT(const int len) // ????
{
}


void CPCPacketHandler::ON_CZ_ITEM_CREATE_EX(const PACKET_CZ_ITEM_CREATE_EX& in_packet) // ????
{
}


void CPCPacketHandler::OnCZ_NPROTECTGAMEGUARDCSAUTH(const PACKET_CZ_NPROTECTGAMEGUARDCSAUTH* in_pPacket) // ????
{
}
