#include "Globals.h" // Trace(), ErrorMsg()
#include "Packet.h"
#include "Device/Connection.h"
////////////////////////////////////////


/// static members
WSADATA& CConnection::s_wsaData = VTOR<WSADATA>(DetourFindFunction(SAKEXE, "CConnection::s_wsaData"));
HINSTANCE& CConnection::s_wsmodule = VTOR<HINSTANCE>(DetourFindFunction(SAKEXE, "CConnection::s_wsmodule"));
SENDFUNC*& CConnection::s_wsSend = VTOR<SENDFUNC*>(DetourFindFunction(SAKEXE, "CConnection::s_wsSend"));
RECVFUNC*& CConnection::s_wsRecv = VTOR<RECVFUNC*>(DetourFindFunction(SAKEXE, "CConnection::s_wsRecv"));


CConnection::CConnection()
: m_socket(INVALID_SOCKET), m_bBlock(false), m_dwTime(0)
{
	this->CConnection::ResetQueue();
}


CConnection::~CConnection()
{
}


void CConnection::SetBlock(bool bBlock)
{
	m_bBlock = bBlock;

	if( !bBlock )
	{// flush block queue
		while( m_blockQueue.CPacketQueue::GetSize() != 0 )
		{
			int iSize = m_blockQueue.CPacketQueue::GetSize();
			const char* pData = m_blockQueue.CPacketQueue::GetDataPtr();

			m_sendQueue.CPacketQueue::InsertData(iSize, pData);
			m_blockQueue.CPacketQueue::RemoveData(iSize);
			this->CConnection::OnSend();
		}
	}
}


void CConnection::SetDelay(DWORD dwDelay)
{
	m_dwTime = dwDelay;
}


bool CConnection::Connect(const ServerAddress* addr)
{
	this->CConnection::SetBlock(false);
	this->CConnection::ResetQueue();

	m_socket = socket(AF_INET, SOCK_STREAM, 0);
	if( m_socket == INVALID_SOCKET )
		return false;

	u_long ul = 1;
	if( ioctlsocket(m_socket, FIONBIO, &ul) == SOCKET_ERROR )
	{
		ErrorMsg("Failed to setup select mode");
		return false;
	}

	memset(&m_addr, 0, sizeof(m_addr));
	m_addr.sin_family = AF_INET;
	m_addr.sin_addr.s_addr = inet_addr(addr->ip);
	m_addr.sin_port = htons(addr->port);

	if( connect(m_socket, (sockaddr*)&m_addr, sizeof(m_addr)) == SOCKET_ERROR )
	{
		if( WSAGetLastError() != WSAEWOULDBLOCK )
		{
			Trace("connect error %d", WSAGetLastError());
			this->CConnection::Disconnect();
			return false;
		}
	}

	return true;
}


bool CConnection::Poll()
{
	if( m_socket != INVALID_SOCKET )
	{
		return ( this->CConnection::OnRecv() && this->CConnection::OnSend() );
	}
	else
	{
		return true;
	}
}


void CConnection::Disconnect()
{
	if( m_socket != INVALID_SOCKET )
	{
		closesocket(m_socket);
		m_socket = INVALID_SOCKET;
		m_sendQueue.CPacketQueue::Init(40*1024);
		m_blockQueue.CPacketQueue::Init(40*1024);
	}
}


void CConnection::Send(int size, const char* buf)
{
	if( m_socket != INVALID_SOCKET )
	{
		if( m_bBlock )
		{
			m_blockQueue.CPacketQueue::InsertData(size, buf);
		}
		else
		{
			m_sendQueue.CPacketQueue::InsertData(size, buf);
			this->CConnection::OnSend();
		}
	}
}


int CConnection::Recv(char* buf, int size, bool mustRecv)
{
	int iRecv;

	if( mustRecv )
	{
		iRecv = ( m_recvQueue.CPacketQueue::GetData(size, buf) ) ? size : 0;
	}
	else
	{
		iRecv = min(size, m_recvQueue.CPacketQueue::GetSize());
		m_recvQueue.CPacketQueue::GetData(iRecv, buf);
	}

	return iRecv;
}


void CConnection::ResetQueue()
{
	m_recvQueue.CPacketQueue::Init(40*1024);
	m_sendQueue.CPacketQueue::Init(40*1024);
	m_blockQueue.CPacketQueue::Init(40*1024);
}


bool CConnection::OnSend()
{
	while( m_dwTime < timeGetTime() && m_sendQueue.CPacketQueue::GetSize() != 0 )
	{
		timeval tval;
		tval.tv_sec = 0;
		tval.tv_usec = 0;

		fd_set fdwrite;
		FD_ZERO(&fdwrite);
		FD_SET(m_socket, &fdwrite);

		int nfds = select(0, NULL, &fdwrite, NULL, &tval);
		if( nfds == SOCKET_ERROR )
			continue;
		if( nfds <= 0 )
			break;

		const char* pData = m_sendQueue.CPacketQueue::GetDataPtr();
		int iSize = m_sendQueue.CPacketQueue::GetSize();

		int sent = s_wsSend(m_socket, pData, iSize, 0);
		if( sent == SOCKET_ERROR )
		{
			if( WSAGetLastError() == WSAEWOULDBLOCK || WSAGetLastError() == WSAENOTCONN )
				continue;

			this->CConnection::Disconnect();
			return false;
		}

		m_sendQueue.CPacketQueue::RemoveData(sent);
	}

	return true;
}


bool CConnection::OnRecv()
{
	timeval tval;
	tval.tv_sec = 0;
	tval.tv_usec = 0;

	fd_set fdread;
	FD_ZERO(&fdread);
	FD_SET(m_socket, &fdread);

	int nfds = select(0, &fdread, NULL, NULL, &tval);
	if( nfds == SOCKET_ERROR || nfds <= 0 )
		return true;

	char tempBuf[2048];
	int rcvd = s_wsRecv(m_socket, tempBuf, sizeof(tempBuf), 0);
	if( rcvd == SOCKET_ERROR )
	{
		if( WSAGetLastError() == WSAEWOULDBLOCK || WSAGetLastError() == WSAENOTCONN )
			return true;

		this->CConnection::Disconnect();
		return false;
	}

	if( rcvd <= 0 )
	{
		this->CConnection::Disconnect();
		return false;
	}

	m_recvQueue.CPacketQueue::InsertData(rcvd, tempBuf);
	return true;
}


void CConnection::OnConnect()
{
}


void CConnection::OnClose()
{
}


bool CConnection::Startup()
{
	if( WSAStartup(MAKEWORD(1,1), &s_wsaData) != 0 )
	{
		ErrorMsg("Failed to load Winsock library!");
		WSACleanup();
		return false;
	}

	s_wsmodule = LoadLibraryA("ws2_32.dll");
	s_wsSend = (SENDFUNC*)GetProcAddress(s_wsmodule, "send");
	s_wsRecv = (RECVFUNC*)GetProcAddress(s_wsmodule, "recv");

	if( s_wsSend == NULL )
	{
		s_wsSend = &send;
		MessageBoxA(NULL, "GetProcAddress(\"send\") Failed.", "Module Hooking Error", MB_OK);
	}

	if( s_wsRecv == NULL )
	{
		s_wsRecv = &recv;
		MessageBoxA(NULL, "GetProcAddress(\"recv\") Failed.", "Module Hooking Error", MB_OK);
	}

	return true;
}


void CConnection::Cleanup()
{
	WSACleanup();
	FreeLibrary(s_wsmodule);
}


////////////////////////////////////////


CRagConnection::CRagConnection()
{
	this->CRagConnection::InitPacketMap();
}


bool CRagConnection::SendPacket(int size, const char* buf)
{
	if( m_socket != INVALID_SOCKET )
	{
		if( m_bBlock )
		{
			m_blockQueue.CPacketQueue::InsertData(size, buf);
		}
		else
		{
			m_sendQueue.CPacketQueue::InsertData(size, buf);
			this->CConnection::OnSend();
		}
	}

	return true;
}


bool CRagConnection::RecvPacket(char* buf)
{
	WORD packetHeader;
	if( !m_recvQueue.CPacketQueue::PeekData(2, (char*)&packetHeader) )
		return false;

	WORD packetLength;
	if( this->CRagConnection::IsFixedPacket(packetHeader) )
	{
		packetLength = (WORD)this->CRagConnection::GetPacketSize(packetHeader);
	}
	else
	{
		DWORD headerWithSize;
		if( !m_recvQueue.CPacketQueue::PeekData(4, (char*)&headerWithSize) )
			return false;

		packetLength = headerWithSize >> 16;
	}

	if( !m_recvQueue.CPacketQueue::GetData(packetLength, buf) )
		return false;

	return true;
}


int CRagConnection::GetPacketSize(int packetType)
{
	return max(2, m_packetLenMap[packetType]);
}


short CRagConnection::GetPacketType(const char* buf)
{
	return *(short*)buf;
}


bool CRagConnection::IsFixedPacket(int packetType)
{
	return ( m_packetLenMap[packetType] != -1 );
}


void CRagConnection::InitPacketMap()
{
	#define REGN(id,len,H,T) { m_packetLenMap[id] = len; C_ASSERT( id == H ); C_ASSERT( len == sizeof(T) ); }
	#define REGV(id,len,H,T) { m_packetLenMap[id] =  -1; C_ASSERT( id == H ); C_ASSERT( len == sizeof(T) ); }

	REGN(100, 55, HEADER_CA_LOGIN, PACKET_CA_LOGIN);
	REGN(101, 17, HEADER_CH_ENTER, PACKET_CH_ENTER);
	REGN(102, 3, HEADER_CH_SELECT_CHAR, PACKET_CH_SELECT_CHAR);
	REGN(103, 37, HEADER_CH_MAKE_CHAR, PACKET_CH_MAKE_CHAR);
	REGN(104, 46, HEADER_CH_DELETE_CHAR, PACKET_CH_DELETE_CHAR);
	REGV(105, 47, HEADER_AC_ACCEPT_LOGIN, PACKET_AC_ACCEPT_LOGIN);
	REGN(106, 23, HEADER_AC_REFUSE_LOGIN, PACKET_AC_REFUSE_LOGIN);
	REGV(107, 4, HEADER_HC_ACCEPT_ENTER, PACKET_HC_ACCEPT_ENTER);
	REGN(108, 3, HEADER_HC_REFUSE_ENTER, PACKET_HC_REFUSE_ENTER);
	REGN(109, 108, HEADER_HC_ACCEPT_MAKECHAR, PACKET_HC_ACCEPT_MAKECHAR);
	REGN(110, 3, HEADER_HC_REFUSE_MAKECHAR, PACKET_HC_REFUSE_MAKECHAR);
	REGN(111, 2, HEADER_HC_ACCEPT_DELETECHAR, PACKET_HC_ACCEPT_DELETECHAR);
	REGN(112, 3, HEADER_HC_REFUSE_DELETECHAR, PACKET_HC_REFUSE_DELETECHAR);
	REGN(113, 28, HEADER_HC_NOTIFY_ZONESVR, PACKET_HC_NOTIFY_ZONESVR);
	REGN(114, 19, HEADER_CZ_ENTER, PACKET_CZ_ENTER);
	REGN(115, 11, HEADER_ZC_ACCEPT_ENTER, PACKET_ZC_ACCEPT_ENTER);
	REGN(116, 3, HEADER_ZC_REFUSE_ENTER, PACKET_ZC_REFUSE_ENTER);
	REGV(117, 11, HEADER_ZC_NOTIFY_INITCHAR, PACKET_ZC_NOTIFY_INITCHAR);
	REGN(118, 9, HEADER_ZC_NOTIFY_UPDATECHAR, PACKET_ZC_NOTIFY_UPDATECHAR);
	REGN(119, 5, HEADER_ZC_NOTIFY_UPDATEPLAYER, PACKET_ZC_NOTIFY_UPDATEPLAYER);
	REGN(120, 54, HEADER_ZC_NOTIFY_STANDENTRY, PACKET_ZC_NOTIFY_STANDENTRY);
	REGN(121, 53, HEADER_ZC_NOTIFY_NEWENTRY, PACKET_ZC_NOTIFY_NEWENTRY);
	REGN(122, 58, HEADER_ZC_NOTIFY_ACTENTRY, PACKET_ZC_NOTIFY_ACTENTRY);
	REGN(123, 60, HEADER_ZC_NOTIFY_MOVEENTRY, PACKET_ZC_NOTIFY_MOVEENTRY);
	REGN(124, 41, HEADER_ZC_NOTIFY_STANDENTRY_NPC, PACKET_ZC_NOTIFY_STANDENTRY_NPC);
	REGN(125, 2, HEADER_CZ_NOTIFY_ACTORINIT, PACKET_CZ_NOTIFY_ACTORINIT);
	REGN(126, 6, HEADER_CZ_REQUEST_TIME, PACKET_CZ_REQUEST_TIME);
	REGN(127, 6, HEADER_ZC_NOTIFY_TIME, PACKET_ZC_NOTIFY_TIME);
	REGN(128, 7, HEADER_ZC_NOTIFY_VANISH, PACKET_ZC_NOTIFY_VANISH);
	REGN(129, 3, HEADER_SC_NOTIFY_BAN, PACKET_SC_NOTIFY_BAN);
	REGN(130, 2, HEADER_CZ_REQUEST_QUIT, PACKET_CZ_REQUEST_QUIT);
	REGN(131, 2, HEADER_ZC_ACCEPT_QUIT, PACKET_ZC_ACCEPT_QUIT);
	REGN(132, 2, HEADER_ZC_REFUSE_QUIT, PACKET_ZC_REFUSE_QUIT);
	REGN(133, 5, HEADER_CZ_REQUEST_MOVE, PACKET_CZ_REQUEST_MOVE);
	REGN(134, 16, HEADER_ZC_NOTIFY_MOVE, PACKET_ZC_NOTIFY_MOVE);
	REGN(135, 12, HEADER_ZC_NOTIFY_PLAYERMOVE, PACKET_ZC_NOTIFY_PLAYERMOVE);
	REGN(136, 10, HEADER_ZC_STOPMOVE, PACKET_ZC_STOPMOVE);
	REGN(137, 7, HEADER_CZ_REQUEST_ACT, PACKET_CZ_REQUEST_ACT);
	REGN(138, 29, HEADER_ZC_NOTIFY_ACT, PACKET_ZC_NOTIFY_ACT);
	REGN(139, 23, HEADER_ZC_NOTIFY_ACT_POSITION, PACKET_ZC_NOTIFY_ACT_POSITION);
	REGV(140, 4, HEADER_CZ_REQUEST_CHAT, PACKET_CZ_REQUEST_CHAT);
	REGV(141, 8, HEADER_ZC_NOTIFY_CHAT, PACKET_ZC_NOTIFY_CHAT);
	REGV(142, 4, HEADER_ZC_NOTIFY_PLAYERCHAT, PACKET_ZC_NOTIFY_PLAYERCHAT);
//	REGN(143, 6, HEADER_SERVER_ENTRY_ACK, PACKET_SERVER_ENTRY_ACK);
	REGN(144, 7, HEADER_CZ_CONTACTNPC, PACKET_CZ_CONTACTNPC);
	REGN(145, 22, HEADER_ZC_NPCACK_MAPMOVE, PACKET_ZC_NPCACK_MAPMOVE);
	REGN(146, 28, HEADER_ZC_NPCACK_SERVERMOVE, PACKET_ZC_NPCACK_SERVERMOVE);
	REGN(147, 2, HEADER_ZC_NPCACK_ENABLE, PACKET_ZC_NPCACK_ENABLE);
	REGN(148, 6, HEADER_CZ_REQNAME, PACKET_CZ_REQNAME);
	REGN(149, 30, HEADER_ZC_ACK_REQNAME, PACKET_ZC_ACK_REQNAME);
	REGV(150, 28, HEADER_CZ_WHISPER, PACKET_CZ_WHISPER);
	REGV(151, 28, HEADER_ZC_WHISPER, PACKET_ZC_WHISPER);
	REGN(152, 3, HEADER_ZC_ACK_WHISPER, PACKET_ZC_ACK_WHISPER);
	REGV(153, 4, HEADER_CZ_BROADCAST, PACKET_CZ_BROADCAST);
	REGV(154, 4, HEADER_ZC_BROADCAST, PACKET_ZC_BROADCAST);
	REGN(155, 5, HEADER_CZ_CHANGE_DIRECTION, PACKET_CZ_CHANGE_DIRECTION);
	REGN(156, 9, HEADER_ZC_CHANGE_DIRECTION, PACKET_ZC_CHANGE_DIRECTION);
	REGN(157, 17, HEADER_ZC_ITEM_ENTRY, PACKET_ZC_ITEM_ENTRY);
	REGN(158, 17, HEADER_ZC_ITEM_FALL_ENTRY, PACKET_ZC_ITEM_FALL_ENTRY);
	REGN(159, 6, HEADER_CZ_ITEM_PICKUP, PACKET_CZ_ITEM_PICKUP);
	REGN(160, 23, HEADER_ZC_ITEM_PICKUP_ACK, PACKET_ZC_ITEM_PICKUP_ACK);
	REGN(161, 6, HEADER_ZC_ITEM_DISAPPEAR, PACKET_ZC_ITEM_DISAPPEAR);
	REGN(162, 6, HEADER_CZ_ITEM_THROW, PACKET_CZ_ITEM_THROW);
	REGV(163, 4, HEADER_ZC_NORMAL_ITEMLIST, PACKET_ZC_NORMAL_ITEMLIST);
	REGV(164, 4, HEADER_ZC_EQUIPMENT_ITEMLIST, PACKET_ZC_EQUIPMENT_ITEMLIST);
	REGV(165, 4, HEADER_ZC_STORE_NORMAL_ITEMLIST, PACKET_ZC_STORE_NORMAL_ITEMLIST);
	REGV(166, 4, HEADER_ZC_STORE_EQUIPMENT_ITEMLIST, PACKET_ZC_STORE_EQUIPMENT_ITEMLIST);
	REGN(167, 8, HEADER_CZ_USE_ITEM, PACKET_CZ_USE_ITEM);
	REGN(168, 7, HEADER_ZC_USE_ITEM_ACK, PACKET_ZC_USE_ITEM_ACK);
	REGN(169, 6, HEADER_CZ_REQ_WEAR_EQUIP, PACKET_CZ_REQ_WEAR_EQUIP);
	REGN(170, 7, HEADER_ZC_REQ_WEAR_EQUIP_ACK, PACKET_ZC_REQ_WEAR_EQUIP_ACK);
	REGN(171, 4, HEADER_CZ_REQ_TAKEOFF_EQUIP, PACKET_CZ_REQ_TAKEOFF_EQUIP);
	REGN(172, 7, HEADER_ZC_REQ_TAKEOFF_EQUIP_ACK, PACKET_ZC_REQ_TAKEOFF_EQUIP_ACK);
//	REGN(173, 4, HEADER_CZ_REQ_ITEM_EXPLANATION_BYNAME, PACKET_CZ_REQ_ITEM_EXPLANATION_BYNAME);
	REGV(174, 4, HEADER_ZC_REQ_ITEM_EXPLANATION_ACK, PACKET_ZC_REQ_ITEM_EXPLANATION_ACK);
	REGN(175, 6, HEADER_ZC_ITEM_THROW_ACK, PACKET_ZC_ITEM_THROW_ACK);
	REGN(176, 8, HEADER_ZC_PAR_CHANGE, PACKET_ZC_PAR_CHANGE);
	REGN(177, 8, HEADER_ZC_LONGPAR_CHANGE, PACKET_ZC_LONGPAR_CHANGE);
	REGN(178, 3, HEADER_CZ_RESTART, PACKET_CZ_RESTART);
	REGN(179, 3, HEADER_ZC_RESTART_ACK, PACKET_ZC_RESTART_ACK);
	REGV(180, 8, HEADER_ZC_SAY_DIALOG, PACKET_ZC_SAY_DIALOG);
	REGN(181, 6, HEADER_ZC_WAIT_DIALOG, PACKET_ZC_WAIT_DIALOG);
	REGN(182, 6, HEADER_ZC_CLOSE_DIALOG, PACKET_ZC_CLOSE_DIALOG);
	REGV(183, 8, HEADER_ZC_MENU_LIST, PACKET_ZC_MENU_LIST);
	REGN(184, 7, HEADER_CZ_CHOOSE_MENU, PACKET_CZ_CHOOSE_MENU);
	REGN(185, 6, HEADER_CZ_REQ_NEXT_SCRIPT, PACKET_CZ_REQ_NEXT_SCRIPT);
	REGN(186, 2, HEADER_CZ_REQ_STATUS, PACKET_CZ_REQ_STATUS);
	REGN(187, 5, HEADER_CZ_STATUS_CHANGE, PACKET_CZ_STATUS_CHANGE);
	REGN(188, 6, HEADER_ZC_STATUS_CHANGE_ACK, PACKET_ZC_STATUS_CHANGE_ACK);
	REGN(189, 44, HEADER_ZC_STATUS, PACKET_ZC_STATUS);
	REGN(190, 5, HEADER_ZC_STATUS_CHANGE, PACKET_ZC_STATUS_CHANGE);
	REGN(191, 3, HEADER_CZ_REQ_EMOTION, PACKET_CZ_REQ_EMOTION);
	REGN(192, 7, HEADER_ZC_EMOTION, PACKET_ZC_EMOTION);
	REGN(193, 2, HEADER_CZ_REQ_USER_COUNT, PACKET_CZ_REQ_USER_COUNT);
	REGN(194, 6, HEADER_ZC_USER_COUNT, PACKET_ZC_USER_COUNT);
	REGN(195, 8, HEADER_ZC_SPRITE_CHANGE, PACKET_ZC_SPRITE_CHANGE);
	REGN(196, 6, HEADER_ZC_SELECT_DEALTYPE, PACKET_ZC_SELECT_DEALTYPE);
	REGN(197, 7, HEADER_CZ_ACK_SELECT_DEALTYPE, PACKET_CZ_ACK_SELECT_DEALTYPE);
	REGV(198, 4, HEADER_ZC_PC_PURCHASE_ITEMLIST, PACKET_ZC_PC_PURCHASE_ITEMLIST);
	REGV(199, 4, HEADER_ZC_PC_SELL_ITEMLIST, PACKET_ZC_PC_SELL_ITEMLIST);
	REGV(200, 4, HEADER_CZ_PC_PURCHASE_ITEMLIST, PACKET_CZ_PC_PURCHASE_ITEMLIST);
	REGV(201, 4, HEADER_CZ_PC_SELL_ITEMLIST, PACKET_CZ_PC_SELL_ITEMLIST);
	REGN(202, 3, HEADER_ZC_PC_PURCHASE_RESULT, PACKET_ZC_PC_PURCHASE_RESULT);
	REGN(203, 3, HEADER_ZC_PC_SELL_RESULT, PACKET_ZC_PC_SELL_RESULT);
	REGN(204, 6, HEADER_CZ_DISCONNECT_CHARACTER, PACKET_CZ_DISCONNECT_CHARACTER);
	REGN(205, 3, HEADER_ZC_ACK_DISCONNECT_CHARACTER, PACKET_ZC_ACK_DISCONNECT_CHARACTER);
	REGN(206, 2, HEADER_CZ_DISCONNECT_ALL_CHARACTER, PACKET_CZ_DISCONNECT_ALL_CHARACTER);
	REGN(207, 27, HEADER_CZ_SETTING_WHISPER_PC, PACKET_CZ_SETTING_WHISPER_PC);
	REGN(208, 3, HEADER_CZ_SETTING_WHISPER_STATE, PACKET_CZ_SETTING_WHISPER_STATE);
	REGN(209, 4, HEADER_ZC_SETTING_WHISPER_PC, PACKET_ZC_SETTING_WHISPER_PC);
	REGN(210, 4, HEADER_ZC_SETTING_WHISPER_STATE, PACKET_ZC_SETTING_WHISPER_STATE);
	REGN(211, 2, HEADER_CZ_REQ_WHISPER_LIST, PACKET_CZ_REQ_WHISPER_LIST);
	REGV(212, 4, HEADER_ZC_WHISPER_LIST, PACKET_ZC_WHISPER_LIST);
	REGV(213, 15, HEADER_CZ_CREATE_CHATROOM, PACKET_CZ_CREATE_CHATROOM);
	REGN(214, 3, HEADER_ZC_ACK_CREATE_CHATROOM, PACKET_ZC_ACK_CREATE_CHATROOM);
	REGV(215, 17, HEADER_ZC_ROOM_NEWENTRY, PACKET_ZC_ROOM_NEWENTRY);
	REGN(216, 6, HEADER_ZC_DESTROY_ROOM, PACKET_ZC_DESTROY_ROOM);
	REGN(217, 14, HEADER_CZ_REQ_ENTER_ROOM, PACKET_CZ_REQ_ENTER_ROOM);
	REGN(218, 3, HEADER_ZC_REFUSE_ENTER_ROOM, PACKET_ZC_REFUSE_ENTER_ROOM);
	REGV(219, 8, HEADER_ZC_ENTER_ROOM, PACKET_ZC_ENTER_ROOM);
	REGN(220, 28, HEADER_ZC_MEMBER_NEWENTRY, PACKET_ZC_MEMBER_NEWENTRY);
	REGN(221, 29, HEADER_ZC_MEMBER_EXIT, PACKET_ZC_MEMBER_EXIT);
	REGV(222, 15, HEADER_CZ_CHANGE_CHATROOM, PACKET_CZ_CHANGE_CHATROOM);
	REGV(223, 17, HEADER_ZC_CHANGE_CHATROOM, PACKET_ZC_CHANGE_CHATROOM);
	REGN(224, 30, HEADER_CZ_REQ_ROLE_CHANGE, PACKET_CZ_REQ_ROLE_CHANGE);
	REGN(225, 30, HEADER_ZC_ROLE_CHANGE, PACKET_ZC_ROLE_CHANGE);
	REGN(226, 26, HEADER_CZ_REQ_EXPEL_MEMBER, PACKET_CZ_REQ_EXPEL_MEMBER);
	REGN(227, 2, HEADER_CZ_EXIT_ROOM, PACKET_CZ_EXIT_ROOM);
	REGN(228, 6, HEADER_CZ_REQ_EXCHANGE_ITEM, PACKET_CZ_REQ_EXCHANGE_ITEM);
	REGN(229, 26, HEADER_ZC_REQ_EXCHANGE_ITEM, PACKET_ZC_REQ_EXCHANGE_ITEM);
	REGN(230, 3, HEADER_CZ_ACK_EXCHANGE_ITEM, PACKET_CZ_ACK_EXCHANGE_ITEM);
	REGN(231, 3, HEADER_ZC_ACK_EXCHANGE_ITEM, PACKET_ZC_ACK_EXCHANGE_ITEM);
	REGN(232, 8, HEADER_CZ_ADD_EXCHANGE_ITEM, PACKET_CZ_ADD_EXCHANGE_ITEM);
	REGN(233, 19, HEADER_ZC_ADD_EXCHANGE_ITEM, PACKET_ZC_ADD_EXCHANGE_ITEM);
	REGN(234, 5, HEADER_ZC_ACK_ADD_EXCHANGE_ITEM, PACKET_ZC_ACK_ADD_EXCHANGE_ITEM);
	REGN(235, 2, HEADER_CZ_CONCLUDE_EXCHANGE_ITEM, PACKET_CZ_CONCLUDE_EXCHANGE_ITEM);
	REGN(236, 3, HEADER_ZC_CONCLUDE_EXCHANGE_ITEM, PACKET_ZC_CONCLUDE_EXCHANGE_ITEM);
	REGN(237, 2, HEADER_CZ_CANCEL_EXCHANGE_ITEM, PACKET_CZ_CANCEL_EXCHANGE_ITEM);
	REGN(238, 2, HEADER_ZC_CANCEL_EXCHANGE_ITEM, PACKET_ZC_CANCEL_EXCHANGE_ITEM);
	REGN(239, 2, HEADER_CZ_EXEC_EXCHANGE_ITEM, PACKET_CZ_EXEC_EXCHANGE_ITEM);
	REGN(240, 3, HEADER_ZC_EXEC_EXCHANGE_ITEM, PACKET_ZC_EXEC_EXCHANGE_ITEM);
	REGN(241, 2, HEADER_ZC_EXCHANGEITEM_UNDO, PACKET_ZC_EXCHANGEITEM_UNDO);
	REGN(242, 6, HEADER_ZC_NOTIFY_STOREITEM_COUNTINFO, PACKET_ZC_NOTIFY_STOREITEM_COUNTINFO);
	REGN(243, 8, HEADER_CZ_MOVE_ITEM_FROM_BODY_TO_STORE, PACKET_CZ_MOVE_ITEM_FROM_BODY_TO_STORE);
	REGN(244, 21, HEADER_ZC_ADD_ITEM_TO_STORE, PACKET_ZC_ADD_ITEM_TO_STORE);
	REGN(245, 8, HEADER_CZ_MOVE_ITEM_FROM_STORE_TO_BODY, PACKET_CZ_MOVE_ITEM_FROM_STORE_TO_BODY);
	REGN(246, 8, HEADER_ZC_DELETE_ITEM_FROM_STORE, PACKET_ZC_DELETE_ITEM_FROM_STORE);
	REGN(247, 2, HEADER_CZ_CLOSE_STORE, PACKET_CZ_CLOSE_STORE);
	REGN(248, 2, HEADER_ZC_CLOSE_STORE, PACKET_ZC_CLOSE_STORE);
	REGN(249, 26, HEADER_CZ_MAKE_GROUP, PACKET_CZ_MAKE_GROUP);
	REGN(250, 3, HEADER_ZC_ACK_MAKE_GROUP, PACKET_ZC_ACK_MAKE_GROUP);
	REGV(251, 28, HEADER_ZC_GROUP_LIST, PACKET_ZC_GROUP_LIST);
	REGN(252, 6, HEADER_CZ_REQ_JOIN_GROUP, PACKET_CZ_REQ_JOIN_GROUP);
	REGN(253, 27, HEADER_ZC_ACK_REQ_JOIN_GROUP, PACKET_ZC_ACK_REQ_JOIN_GROUP);
	REGN(254, 30, HEADER_ZC_REQ_JOIN_GROUP, PACKET_ZC_REQ_JOIN_GROUP);
	REGN(255, 10, HEADER_CZ_JOIN_GROUP, PACKET_CZ_JOIN_GROUP);
	REGN(256, 2, HEADER_CZ_REQ_LEAVE_GROUP, PACKET_CZ_REQ_LEAVE_GROUP);
	REGN(257, 6, HEADER_ZC_GROUPINFO_CHANGE, PACKET_ZC_GROUPINFO_CHANGE);
	REGN(258, 6, HEADER_CZ_CHANGE_GROUPEXPOPTION, PACKET_CZ_CHANGE_GROUPEXPOPTION);
	REGN(259, 30, HEADER_CZ_REQ_EXPEL_GROUP_MEMBER, PACKET_CZ_REQ_EXPEL_GROUP_MEMBER);
	REGN(260, 79, HEADER_ZC_ADD_MEMBER_TO_GROUP, PACKET_ZC_ADD_MEMBER_TO_GROUP);
	REGN(261, 31, HEADER_ZC_DELETE_MEMBER_FROM_GROUP, PACKET_ZC_DELETE_MEMBER_FROM_GROUP);
	REGN(262, 10, HEADER_ZC_NOTIFY_HP_TO_GROUPM, PACKET_ZC_NOTIFY_HP_TO_GROUPM);
	REGN(263, 10, HEADER_ZC_NOTIFY_POSITION_TO_GROUPM, PACKET_ZC_NOTIFY_POSITION_TO_GROUPM);
	REGV(264, 4, HEADER_CZ_REQUEST_CHAT_PARTY, PACKET_CZ_REQUEST_CHAT_PARTY);
	REGV(265, 8, HEADER_ZC_NOTIFY_CHAT_PARTY, PACKET_ZC_NOTIFY_CHAT_PARTY);
	REGN(266, 4, HEADER_ZC_MVP_GETTING_ITEM, PACKET_ZC_MVP_GETTING_ITEM);
	REGN(267, 6, HEADER_ZC_MVP_GETTING_SPECIAL_EXP, PACKET_ZC_MVP_GETTING_SPECIAL_EXP);
	REGN(268, 6, HEADER_ZC_MVP, PACKET_ZC_MVP);
	REGN(269, 2, HEADER_ZC_THROW_MVPITEM, PACKET_ZC_THROW_MVPITEM);
	REGN(270, 11, HEADER_ZC_SKILLINFO_UPDATE, PACKET_ZC_SKILLINFO_UPDATE);
	REGV(271, 4, HEADER_ZC_SKILLINFO_LIST, PACKET_ZC_SKILLINFO_LIST);
	REGN(272, 10, HEADER_ZC_ACK_TOUSESKILL, PACKET_ZC_ACK_TOUSESKILL);
	REGN(273, 39, HEADER_ZC_ADD_SKILL, PACKET_ZC_ADD_SKILL);
	REGN(274, 4, HEADER_CZ_UPGRADE_SKILLLEVEL, PACKET_CZ_UPGRADE_SKILLLEVEL);
	REGN(275, 10, HEADER_CZ_USE_SKILL, PACKET_CZ_USE_SKILL);
	REGN(276, 31, HEADER_ZC_NOTIFY_SKILL, PACKET_ZC_NOTIFY_SKILL);
	REGN(277, 35, HEADER_ZC_NOTIFY_SKILL_POSITION, PACKET_ZC_NOTIFY_SKILL_POSITION);
	REGN(278, 10, HEADER_CZ_USE_SKILL_TOGROUND, PACKET_CZ_USE_SKILL_TOGROUND);
	REGN(279, 18, HEADER_ZC_NOTIFY_GROUNDSKILL, PACKET_ZC_NOTIFY_GROUNDSKILL);
	REGN(280, 2, HEADER_CZ_CANCEL_LOCKON, PACKET_CZ_CANCEL_LOCKON);
	REGN(281, 13, HEADER_ZC_STATE_CHANGE, PACKET_ZC_STATE_CHANGE);
	REGN(282, 15, HEADER_ZC_USE_SKILL, PACKET_ZC_USE_SKILL);
	REGN(283, 20, HEADER_CZ_SELECT_WARPPOINT, PACKET_CZ_SELECT_WARPPOINT);
	REGN(284, 68, HEADER_ZC_WARPLIST, PACKET_ZC_WARPLIST);
	REGN(285, 2, HEADER_CZ_REMEMBER_WARPPOINT, PACKET_CZ_REMEMBER_WARPPOINT);
	REGN(286, 3, HEADER_ZC_ACK_REMEMBER_WARPPOINT, PACKET_ZC_ACK_REMEMBER_WARPPOINT);
	REGN(287, 16, HEADER_ZC_SKILL_ENTRY, PACKET_ZC_SKILL_ENTRY);
	REGN(288, 6, HEADER_ZC_SKILL_DISAPPEAR, PACKET_ZC_SKILL_DISAPPEAR);
	REGN(289, 14, HEADER_ZC_NOTIFY_CARTITEM_COUNTINFO, PACKET_ZC_NOTIFY_CARTITEM_COUNTINFO);
	REGV(290, 4, HEADER_ZC_CART_EQUIPMENT_ITEMLIST, PACKET_ZC_CART_EQUIPMENT_ITEMLIST);
	REGV(291, 4, HEADER_ZC_CART_NORMAL_ITEMLIST, PACKET_ZC_CART_NORMAL_ITEMLIST);
	REGN(292, 21, HEADER_ZC_ADD_ITEM_TO_CART, PACKET_ZC_ADD_ITEM_TO_CART);
	REGN(293, 8, HEADER_ZC_DELETE_ITEM_FROM_CART, PACKET_ZC_DELETE_ITEM_FROM_CART);
	REGN(294, 8, HEADER_CZ_MOVE_ITEM_FROM_BODY_TO_CART, PACKET_CZ_MOVE_ITEM_FROM_BODY_TO_CART);
	REGN(295, 8, HEADER_CZ_MOVE_ITEM_FROM_CART_TO_BODY, PACKET_CZ_MOVE_ITEM_FROM_CART_TO_BODY);
	REGN(296, 8, HEADER_CZ_MOVE_ITEM_FROM_STORE_TO_CART, PACKET_CZ_MOVE_ITEM_FROM_STORE_TO_CART);
	REGN(297, 8, HEADER_CZ_MOVE_ITEM_FROM_CART_TO_STORE, PACKET_CZ_MOVE_ITEM_FROM_CART_TO_STORE);
	REGN(298, 2, HEADER_CZ_REQ_CARTOFF, PACKET_CZ_REQ_CARTOFF);
	REGN(299, 2, HEADER_ZC_CARTOFF, PACKET_ZC_CARTOFF);
	REGN(300, 3, HEADER_ZC_ACK_ADDITEM_TO_CART, PACKET_ZC_ACK_ADDITEM_TO_CART);
	REGN(301, 4, HEADER_ZC_OPENSTORE, PACKET_ZC_OPENSTORE);
	REGN(302, 2, HEADER_CZ_REQ_CLOSESTORE, PACKET_CZ_REQ_CLOSESTORE);
	REGV(303, 84, HEADER_CZ_REQ_OPENSTORE, PACKET_CZ_REQ_OPENSTORE);
	REGN(304, 6, HEADER_CZ_REQ_BUY_FROMMC, PACKET_CZ_REQ_BUY_FROMMC);
	REGN(305, 86, HEADER_ZC_STORE_ENTRY, PACKET_ZC_STORE_ENTRY);
	REGN(306, 6, HEADER_ZC_DISAPPEAR_ENTRY, PACKET_ZC_DISAPPEAR_ENTRY);
	REGV(307, 8, HEADER_ZC_PC_PURCHASE_ITEMLIST_FROMMC, PACKET_ZC_PC_PURCHASE_ITEMLIST_FROMMC);
	REGV(308, 8, HEADER_CZ_PC_PURCHASE_ITEMLIST_FROMMC, PACKET_CZ_PC_PURCHASE_ITEMLIST_FROMMC);
	REGN(309, 7, HEADER_ZC_PC_PURCHASE_RESULT_FROMMC, PACKET_ZC_PC_PURCHASE_RESULT_FROMMC);
	REGV(310, 8, HEADER_ZC_PC_PURCHASE_MYITEMLIST, PACKET_ZC_PC_PURCHASE_MYITEMLIST);
	REGN(311, 6, HEADER_ZC_DELETEITEM_FROM_MCSTORE, PACKET_ZC_DELETEITEM_FROM_MCSTORE);
	REGN(312, 3, HEADER_CZ_PKMODE_CHANGE, PACKET_CZ_PKMODE_CHANGE);
	REGN(313, 16, HEADER_ZC_ATTACK_FAILURE_FOR_DISTANCE, PACKET_ZC_ATTACK_FAILURE_FOR_DISTANCE);
	REGN(314, 4, HEADER_ZC_ATTACK_RANGE, PACKET_ZC_ATTACK_RANGE);
	REGN(315, 4, HEADER_ZC_ACTION_FAILURE, PACKET_ZC_ACTION_FAILURE);
	REGN(316, 4, HEADER_ZC_EQUIP_ARROW, PACKET_ZC_EQUIP_ARROW);
	REGN(317, 6, HEADER_ZC_RECOVERY, PACKET_ZC_RECOVERY);
	REGN(318, 24, HEADER_ZC_USESKILL_ACK, PACKET_ZC_USESKILL_ACK);
	REGN(319, 26, HEADER_CZ_ITEM_CREATE, PACKET_CZ_ITEM_CREATE);
	REGN(320, 22, HEADER_CZ_MOVETO_MAP, PACKET_CZ_MOVETO_MAP);
	REGN(321, 14, HEADER_ZC_COUPLESTATUS, PACKET_ZC_COUPLESTATUS);
	REGN(322, 6, HEADER_ZC_OPEN_EDITDLG, PACKET_ZC_OPEN_EDITDLG);
	REGN(323, 10, HEADER_CZ_INPUT_EDITDLG, PACKET_CZ_INPUT_EDITDLG);
	REGN(324, 23, HEADER_ZC_COMPASS, PACKET_ZC_COMPASS);
	REGN(325, 19, HEADER_ZC_SHOW_IMAGE, PACKET_ZC_SHOW_IMAGE);
	REGN(326, 6, HEADER_CZ_CLOSE_DIALOG, PACKET_CZ_CLOSE_DIALOG);
	REGN(327, 39, HEADER_ZC_AUTORUN_SKILL, PACKET_ZC_AUTORUN_SKILL);
	REGN(328, 8, HEADER_ZC_RESURRECTION, PACKET_ZC_RESURRECTION);
	REGN(329, 9, HEADER_CZ_REQ_GIVE_MANNER_POINT, PACKET_CZ_REQ_GIVE_MANNER_POINT);
	REGN(330, 6, HEADER_ZC_ACK_GIVE_MANNER_POINT, PACKET_ZC_ACK_GIVE_MANNER_POINT);
	REGN(331, 27, HEADER_ZC_NOTIFY_MANNER_POINT_GIVEN, PACKET_ZC_NOTIFY_MANNER_POINT_GIVEN);
	REGV(332, 4, HEADER_ZC_MYGUILD_BASIC_INFO, PACKET_ZC_MYGUILD_BASIC_INFO);
	REGN(333, 2, HEADER_CZ_REQ_GUILD_MENUINTERFACE, PACKET_CZ_REQ_GUILD_MENUINTERFACE);
	REGN(334, 6, HEADER_ZC_ACK_GUILD_MENUINTERFACE, PACKET_ZC_ACK_GUILD_MENUINTERFACE);
	REGN(335, 6, HEADER_CZ_REQ_GUILD_MENU, PACKET_CZ_REQ_GUILD_MENU);
	REGN(336, 110, HEADER_ZC_GUILD_INFO, PACKET_ZC_GUILD_INFO);
	REGN(337, 6, HEADER_CZ_REQ_GUILD_EMBLEM_IMG, PACKET_CZ_REQ_GUILD_EMBLEM_IMG);
	REGV(338, 12, HEADER_ZC_GUILD_EMBLEM_IMG, PACKET_ZC_GUILD_EMBLEM_IMG);
	REGV(339, 4, HEADER_CZ_REGISTER_GUILD_EMBLEM_IMG, PACKET_CZ_REGISTER_GUILD_EMBLEM_IMG);
	REGV(340, 4, HEADER_ZC_MEMBERMGR_INFO, PACKET_ZC_MEMBERMGR_INFO);
	REGV(341, 4, HEADER_CZ_REQ_CHANGE_MEMBERPOS, PACKET_CZ_REQ_CHANGE_MEMBERPOS);
	REGV(342, 4, HEADER_ZC_ACK_REQ_CHANGE_MEMBERS, PACKET_ZC_ACK_REQ_CHANGE_MEMBERS);
	REGN(343, 6, HEADER_CZ_REQ_OPEN_MEMBER_INFO, PACKET_CZ_REQ_OPEN_MEMBER_INFO);
	REGN(344, 2, HEADER_ZC_ACK_OPEN_MEMBER_INFO, PACKET_ZC_ACK_OPEN_MEMBER_INFO); //NOTE: was -1 instead of 2
	REGN(345, 54, HEADER_CZ_REQ_LEAVE_GUILD, PACKET_CZ_REQ_LEAVE_GUILD);
	REGN(346, 66, HEADER_ZC_ACK_LEAVE_GUILD, PACKET_ZC_ACK_LEAVE_GUILD);
	REGN(347, 54, HEADER_CZ_REQ_BAN_GUILD, PACKET_CZ_REQ_BAN_GUILD);
	REGN(348, 90, HEADER_ZC_ACK_BAN_GUILD, PACKET_ZC_ACK_BAN_GUILD);
	REGN(349, 42, HEADER_CZ_REQ_DISORGANIZE_GUILD, PACKET_CZ_REQ_DISORGANIZE_GUILD);
	REGN(350, 6, HEADER_ZC_ACK_DISORGANIZE_GUILD_RESULT, PACKET_ZC_ACK_DISORGANIZE_GUILD_RESULT);
	REGN(351, 42, HEADER_ZC_ACK_DISORGANIZE_GUILD, PACKET_ZC_ACK_DISORGANIZE_GUILD);
	REGV(352, 4, HEADER_ZC_POSITION_INFO, PACKET_ZC_POSITION_INFO);
	REGV(353, 4, HEADER_CZ_REG_CHANGE_GUILD_POSITIONINFO, PACKET_CZ_REG_CHANGE_GUILD_POSITIONINFO);
	REGV(354, 6, HEADER_ZC_GUILD_SKILLINFO, PACKET_ZC_GUILD_SKILLINFO);
	REGV(355, 4, HEADER_ZC_BAN_LIST, PACKET_ZC_BAN_LIST);
	REGV(356, 4, HEADER_ZC_OTHER_GUILD_LIST, PACKET_ZC_OTHER_GUILD_LIST);
	REGN(357, 30, HEADER_CZ_REQ_MAKE_GUILD, PACKET_CZ_REQ_MAKE_GUILD);
	REGV(358, 4, HEADER_ZC_POSITION_ID_NAME_INFO, PACKET_ZC_POSITION_ID_NAME_INFO);
	REGN(359, 3, HEADER_ZC_RESULT_MAKE_GUILD, PACKET_ZC_RESULT_MAKE_GUILD);
	REGN(360, 14, HEADER_CZ_REQ_JOIN_GUILD, PACKET_CZ_REQ_JOIN_GUILD);
	REGN(361, 3, HEADER_ZC_ACK_REQ_JOIN_GUILD, PACKET_ZC_ACK_REQ_JOIN_GUILD);
	REGN(362, 30, HEADER_ZC_REQ_JOIN_GUILD, PACKET_ZC_REQ_JOIN_GUILD);
	REGN(363, 10, HEADER_CZ_JOIN_GUILD, PACKET_CZ_JOIN_GUILD);
	REGN(364, 43, HEADER_ZC_UPDATE_GDID, PACKET_ZC_UPDATE_GDID);
	REGN(365, 14, HEADER_ZC_UPDATE_CHARSTAT, PACKET_ZC_UPDATE_CHARSTAT);
	REGN(366, 186, HEADER_CZ_GUILD_NOTICE, PACKET_CZ_GUILD_NOTICE);
	REGN(367, 182, HEADER_ZC_GUILD_NOTICE, PACKET_ZC_GUILD_NOTICE);
	REGN(368, 14, HEADER_CZ_REQ_ALLY_GUILD, PACKET_CZ_REQ_ALLY_GUILD);
	REGN(369, 30, HEADER_ZC_REQ_ALLY_GUILD, PACKET_ZC_REQ_ALLY_GUILD);
	REGN(370, 10, HEADER_CZ_ALLY_GUILD, PACKET_CZ_ALLY_GUILD);
	REGN(371, 3, HEADER_ZC_ACK_REQ_ALLY_GUILD, PACKET_ZC_ACK_REQ_ALLY_GUILD);
	REGV(372, 4, HEADER_ZC_ACK_CHANGE_GUILD_POSITIONINFO, PACKET_ZC_ACK_CHANGE_GUILD_POSITIONINFO);
	REGN(373, 6, HEADER_CZ_REQ_GUILD_MEMBER_INFO, PACKET_CZ_REQ_GUILD_MEMBER_INFO);
	REGN(374, 106, HEADER_ZC_ACK_GUILD_MEMBER_INFO, PACKET_ZC_ACK_GUILD_MEMBER_INFO);
	REGV(375, 4, HEADER_ZC_ITEMIDENTIFY_LIST, PACKET_ZC_ITEMIDENTIFY_LIST);
	REGN(376, 4, HEADER_CZ_REQ_ITEMIDENTIFY, PACKET_CZ_REQ_ITEMIDENTIFY);
	REGN(377, 5, HEADER_ZC_ACK_ITEMIDENTIFY, PACKET_ZC_ACK_ITEMIDENTIFY);
	REGN(378, 4, HEADER_CZ_REQ_ITEMCOMPOSITION_LIST, PACKET_CZ_REQ_ITEMCOMPOSITION_LIST);
	REGV(379, 4, HEADER_ZC_ITEMCOMPOSITION_LIST, PACKET_ZC_ITEMCOMPOSITION_LIST);
	REGN(380, 6, HEADER_CZ_REQ_ITEMCOMPOSITION, PACKET_CZ_REQ_ITEMCOMPOSITION);
	REGN(381, 7, HEADER_ZC_ACK_ITEMCOMPOSITION, PACKET_ZC_ACK_ITEMCOMPOSITION);
	REGV(382, 4, HEADER_CZ_GUILD_CHAT, PACKET_CZ_GUILD_CHAT);
	REGV(383, 4, HEADER_ZC_GUILD_CHAT, PACKET_ZC_GUILD_CHAT);
	REGN(384, 6, HEADER_CZ_REQ_HOSTILE_GUILD, PACKET_CZ_REQ_HOSTILE_GUILD);
	REGN(385, 3, HEADER_ZC_ACK_REQ_HOSTILE_GUILD, PACKET_ZC_ACK_REQ_HOSTILE_GUILD);
	REGN(386, 106, HEADER_ZC_MEMBER_ADD, PACKET_ZC_MEMBER_ADD);
	REGN(387, 10, HEADER_CZ_REQ_DELETE_RELATED_GUILD, PACKET_CZ_REQ_DELETE_RELATED_GUILD);
	REGN(388, 10, HEADER_ZC_DELETE_RELATED_GUILD, PACKET_ZC_DELETE_RELATED_GUILD);
	REGN(389, 34, HEADER_ZC_ADD_RELATED_GUILD, PACKET_ZC_ADD_RELATED_GUILD);
//	REGN(390, 6, HEADER_COLLECTORDEAD, PACKET_COLLECTORDEAD);
	REGN(391, 6, HEADER_PING, PACKET_PING);
	REGN(392, 8, HEADER_ZC_ACK_ITEMREFINING, PACKET_ZC_ACK_ITEMREFINING);
	REGN(393, 4, HEADER_ZC_NOTIFY_MAPINFO, PACKET_ZC_NOTIFY_MAPINFO);
	REGN(394, 4, HEADER_CZ_REQ_DISCONNECT, PACKET_CZ_REQ_DISCONNECT);
	REGN(395, 4, HEADER_ZC_ACK_REQ_DISCONNECT, PACKET_ZC_ACK_REQ_DISCONNECT);
	REGN(396, 29, HEADER_ZC_MONSTER_INFO, PACKET_ZC_MONSTER_INFO);
	REGV(397, 4, HEADER_ZC_MAKABLEITEMLIST, PACKET_ZC_MAKABLEITEMLIST);
	REGN(398, 10, HEADER_CZ_REQMAKINGITEM, PACKET_CZ_REQMAKINGITEM);
	REGN(399, 6, HEADER_ZC_ACK_REQMAKINGITEM, PACKET_ZC_ACK_REQMAKINGITEM);
	REGN(400, 90, HEADER_CZ_USE_SKILL_TOGROUND_WITHTALKBOX, PACKET_CZ_USE_SKILL_TOGROUND_WITHTALKBOX);
	REGN(401, 86, HEADER_ZC_TALKBOX_CHATCONTENTS, PACKET_ZC_TALKBOX_CHATCONTENTS);
	REGN(402, 24, HEADER_ZC_UPDATE_MAPINFO, PACKET_ZC_UPDATE_MAPINFO);
	REGN(403, 6, HEADER_CZ_REQNAME_BYGID, PACKET_CZ_REQNAME_BYGID);
	REGN(404, 30, HEADER_ZC_ACK_REQNAME_BYGID, PACKET_ZC_ACK_REQNAME_BYGID);
	REGN(405, 102, HEADER_ZC_ACK_REQNAMEALL, PACKET_ZC_ACK_REQNAMEALL);
	REGN(406, 9, HEADER_ZC_MSG_STATE_CHANGE, PACKET_ZC_MSG_STATE_CHANGE);
	REGN(407, 4, HEADER_CZ_RESET, PACKET_CZ_RESET);
	REGN(408, 8, HEADER_CZ_CHANGE_MAPTYPE, PACKET_CZ_CHANGE_MAPTYPE);
	REGN(409, 4, HEADER_ZC_NOTIFY_MAPPROPERTY, PACKET_ZC_NOTIFY_MAPPROPERTY);
	REGN(410, 14, HEADER_ZC_NOTIFY_RANKING, PACKET_ZC_NOTIFY_RANKING);
	REGN(411, 10, HEADER_ZC_NOTIFY_EFFECT, PACKET_ZC_NOTIFY_EFFECT);
	REGN(412, 4, HEADER_CZ_LOCALBROADCAST, PACKET_CZ_BROADCAST);
	REGN(413, 6, HEADER_CZ_CHANGE_EFFECTSTATE, PACKET_CZ_CHANGE_EFFECTSTATE);
	REGN(414, 2, HEADER_ZC_START_CAPTURE, PACKET_ZC_START_CAPTURE);
	REGN(415, 6, HEADER_CZ_TRYCAPTURE_MONSTER, PACKET_CZ_TRYCAPTURE_MONSTER);
	REGN(416, 3, HEADER_ZC_TRYCAPTURE_MONSTER, PACKET_ZC_TRYCAPTURE_MONSTER);
	REGN(417, 3, HEADER_CZ_COMMAND_PET, PACKET_CZ_COMMAND_PET);
	REGN(418, 35, HEADER_ZC_PROPERTY_PET, PACKET_ZC_PROPERTY_PET);
	REGN(419, 5, HEADER_ZC_FEED_PET, PACKET_ZC_FEED_PET);
	REGN(420, 11, HEADER_ZC_CHANGESTATE_PET, PACKET_ZC_CHANGESTATE_PET);
	REGN(421, 26, HEADER_CZ_RENAME_PET, PACKET_CZ_RENAME_PET);
	REGV(422, 4, HEADER_ZC_PETEGG_LIST, PACKET_ZC_PETEGG_LIST);
	REGN(423, 4, HEADER_CZ_SELECT_PETEGG, PACKET_CZ_SELECT_PETEGG);
	REGN(424, 4, HEADER_CZ_PETEGG_INFO, PACKET_CZ_PETEGG_INFO);
	REGN(425, 6, HEADER_CZ_PET_ACT, PACKET_CZ_PET_ACT);
	REGN(426, 10, HEADER_ZC_PET_ACT, PACKET_ZC_PET_ACT);
	REGN(427, 12, HEADER_ZC_PAR_CHANGE_USER, PACKET_ZC_PAR_CHANGE_USER);
	REGN(428, 6, HEADER_ZC_SKILL_UPDATE, PACKET_ZC_SKILL_UPDATE);
	REGV(429, 4, HEADER_ZC_MAKINGARROW_LIST, PACKET_ZC_MAKINGARROW_LIST);
	REGN(430, 4, HEADER_CZ_REQ_MAKINGARROW, PACKET_CZ_REQ_MAKINGARROW);
	REGN(431, 4, HEADER_CZ_REQ_CHANGECART, PACKET_CZ_REQ_CHANGECART);
	REGN(432, 11, HEADER_ZC_NPCSPRITE_CHANGE, PACKET_ZC_NPCSPRITE_CHANGE);
	REGN(433, 7, HEADER_ZC_SHOWDIGIT, PACKET_ZC_SHOWDIGIT);
	REGV(434, 85, HEADER_CZ_REQ_OPENSTORE2, PACKET_CZ_REQ_OPENSTORE2);
	REGN(435, 67, HEADER_ZC_SHOW_IMAGE2, PACKET_ZC_SHOW_IMAGE2);
	REGN(436, 12, HEADER_ZC_CHANGE_GUILD, PACKET_ZC_CHANGE_GUILD);
	REGN(437, 18, HEADER_SC_BILLING_INFO, PACKET_SC_BILLING_INFO);
	REGN(438, 114, HEADER_ZC_GUILD_INFO2, PACKET_ZC_GUILD_INFO2);
	REGN(439, 6, HEADER_CZ_GUILD_ZENY, PACKET_CZ_GUILD_ZENY);
	REGN(440, 3, HEADER_ZC_GUILD_ZENY_ACK, PACKET_ZC_GUILD_ZENY_ACK);
	REGN(441, 6, HEADER_ZC_DISPEL, PACKET_ZC_DISPEL);
	REGN(442, 26, HEADER_CZ_REMOVE_AID, PACKET_CZ_REMOVE_AID);
	REGN(443, 26, HEADER_CZ_SHIFT, PACKET_CZ_SHIFT);
	REGN(444, 26, HEADER_CZ_RECALL, PACKET_CZ_RECALL);
	REGN(445, 26, HEADER_CZ_RECALL_GID, PACKET_CZ_RECALL_GID);
	REGN(446, 2, HEADER_AC_ASK_PNGAMEROOM, PACKET_AC_ASK_PNGAMEROOM);
	REGN(447, 3, HEADER_CA_REPLY_PNGAMEROOM, PACKET_CA_REPLY_PNGAMEROOM);
	REGN(448, 2, HEADER_CZ_REQ_REMAINTIME, PACKET_CZ_REQ_REMAINTIME);
	REGN(449, 14, HEADER_ZC_REPLY_REMAINTIME, PACKET_ZC_REPLY_REMAINTIME);
	REGN(450, 10, HEADER_ZC_INFO_REMAINTIME, PACKET_ZC_INFO_REMAINTIME);
	REGV(451, 16, HEADER_ZC_BROADCAST2, PACKET_ZC_BROADCAST2);
	REGN(452, 22, HEADER_ZC_ADD_ITEM_TO_STORE2, PACKET_ZC_ADD_ITEM_TO_STORE2);
	REGN(453, 22, HEADER_ZC_ADD_ITEM_TO_CART2, PACKET_ZC_ADD_ITEM_TO_CART2);
	REGN(454, 4, HEADER_CS_REQ_ENCRYPTION, PACKET_CS_REQ_ENCRYPTION);
	REGN(455, 2, HEADER_SC_ACK_ENCRYPTION, PACKET_SC_ACK_ENCRYPTION);
	REGN(456, 13, HEADER_ZC_USE_ITEM_ACK2, PACKET_ZC_USE_ITEM_ACK2);
	REGN(457, 97, HEADER_ZC_SKILL_ENTRY2, PACKET_ZC_SKILL_ENTRY2);
//	REGN(458, 3, HEADER_CZ_REQMAKINGHOMUN, PACKET_CZ_REQMAKINGHOMUN);
	REGN(459, 9, HEADER_CZ_MONSTER_TALK, PACKET_CZ_MONSTER_TALK);
	REGN(460, 9, HEADER_ZC_MONSTER_TALK, PACKET_ZC_MONSTER_TALK);
	REGN(461, 30, HEADER_ZC_AUTOSPELLLIST, PACKET_ZC_AUTOSPELLLIST);
	REGN(462, 6, HEADER_CZ_SELECTAUTOSPELL, PACKET_CZ_SELECTAUTOSPELL);
	REGN(463, 28, HEADER_ZC_DEVOTIONLIST, PACKET_ZC_DEVOTIONLIST);
	REGN(464, 8, HEADER_ZC_SPIRITS, PACKET_ZC_SPIRITS);
	REGN(465, 14, HEADER_ZC_BLADESTOP, PACKET_ZC_BLADESTOP);
	REGN(466, 10, HEADER_ZC_COMBODELAY, PACKET_ZC_COMBODELAY);
	REGN(467, 35, HEADER_ZC_SOUND, PACKET_ZC_SOUND);
	REGN(468, 6, HEADER_ZC_OPEN_EDITDLGSTR, PACKET_ZC_OPEN_EDITDLGSTR);
	REGN(469, 8, HEADER_CZ_INPUT_EDITDLGSTR, PACKET_CZ_INPUT_EDITDLGSTR); //NOTE: was 8 instead of -1
	REGN(470, 4, HEADER_ZC_NOTIFY_MAPPROPERTY2, PACKET_ZC_NOTIFY_MAPPROPERTY2);
	REGN(471, 11, HEADER_ZC_SPRITE_CHANGE2, PACKET_ZC_SPRITE_CHANGE2);
	REGN(472, 54, HEADER_ZC_NOTIFY_STANDENTRY2, PACKET_ZC_NOTIFY_STANDENTRY2);
	REGN(473, 53, HEADER_ZC_NOTIFY_NEWENTRY2, PACKET_ZC_NOTIFY_NEWENTRY2);
	REGN(474, 60, HEADER_ZC_NOTIFY_MOVEENTRY2, PACKET_ZC_NOTIFY_MOVEENTRY2);
	REGN(475, 2, HEADER_CA_REQ_HASH, PACKET_CA_REQ_HASH);
	REGV(476, 4, HEADER_AC_ACK_HASH, PACKET_AC_ACK_HASH);
	REGN(477, 47, HEADER_CA_LOGIN2, PACKET_CA_LOGIN2);
	REGN(478, 33, HEADER_ZC_NOTIFY_SKILL2, PACKET_ZC_NOTIFY_SKILL2);
	REGN(479, 6, HEADER_CZ_REQ_ACCOUNTNAME, PACKET_CZ_REQ_ACCOUNTNAME);
	REGN(480, 30, HEADER_ZC_ACK_ACCOUNTNAME, PACKET_ZC_ACK_ACCOUNTNAME);
	REGN(481, 8, HEADER_ZC_SPIRITS2, PACKET_ZC_SPIRITS2);
	REGN(482, 34, HEADER_ZC_REQ_COUPLE, PACKET_ZC_REQ_COUPLE);
	REGN(483, 14, HEADER_CZ_JOIN_COUPLE, PACKET_CZ_JOIN_COUPLE);
	REGN(484, 2, HEADER_ZC_START_COUPLE, PACKET_ZC_START_COUPLE);
	REGN(485, 6, HEADER_CZ_REQ_JOIN_COUPLE, PACKET_CZ_REQ_JOIN_COUPLE);
	REGN(486, 26, HEADER_ZC_COUPLENAME, PACKET_ZC_COUPLENAME);
	REGN(487, 2, HEADER_CZ_DORIDORI, PACKET_CZ_DORIDORI);
	REGN(488, 28, HEADER_CZ_MAKE_GROUP2, PACKET_CZ_MAKE_GROUP2);
	REGN(489, 81, HEADER_ZC_ADD_MEMBER_TO_GROUP2, PACKET_ZC_ADD_MEMBER_TO_GROUP2);
	REGN(490, 6, HEADER_ZC_CONGRATULATION, PACKET_ZC_CONGRATULATION);
	REGN(491, 10, HEADER_ZC_NOTIFY_POSITION_TO_GUILDM, PACKET_ZC_NOTIFY_POSITION_TO_GUILDM);
	REGN(492, 26, HEADER_ZC_GUILD_MEMBER_MAP_CHANGE, PACKET_ZC_GUILD_MEMBER_MAP_CHANGE);
	REGN(493, 2, HEADER_CZ_CHOPOKGI, PACKET_CZ_CHOPOKGI);
	REGV(494, 4, HEADER_ZC_NORMAL_ITEMLIST2, PACKET_ZC_NORMAL_ITEMLIST2);
	REGV(495, 4, HEADER_ZC_CART_NORMAL_ITEMLIST2, PACKET_ZC_CART_NORMAL_ITEMLIST2);
	REGV(496, 4, HEADER_ZC_STORE_NORMAL_ITEMLIST2, PACKET_ZC_STORE_NORMAL_ITEMLIST2);
	REGV(497, 4, HEADER_AC_NOTIFY_ERROR, PACKET_AC_NOTIFY_ERROR);
	REGN(498, 20, HEADER_ZC_UPDATE_CHARSTAT2, PACKET_ZC_UPDATE_CHARSTAT2);
	REGN(499, 10, HEADER_ZC_NOTIFY_EFFECT2, PACKET_ZC_NOTIFY_EFFECT2);
	REGN(500, 32, HEADER_ZC_REQ_EXCHANGE_ITEM2, PACKET_ZC_REQ_EXCHANGE_ITEM2);
	REGN(501, 9, HEADER_ZC_ACK_EXCHANGE_ITEM2, PACKET_ZC_ACK_EXCHANGE_ITEM2);
	REGN(502, 34, HEADER_ZC_REQ_BABY, PACKET_ZC_REQ_BABY);
	REGN(503, 14, HEADER_CZ_JOIN_BABY, PACKET_CZ_JOIN_BABY);
	REGN(504, 2, HEADER_ZC_START_BABY, PACKET_ZC_START_BABY);
	REGN(505, 6, HEADER_CZ_REQ_JOIN_BABY, PACKET_CZ_REQ_JOIN_BABY);
}


////////////////////////////////////////


class hook_ptr<struct mystd::_Tree<int, struct mystd::pair<int const, int>, struct mystd::map<int, int, struct mystd::less<int>, class mystd::allocator<int>>::_Kfn, struct mystd::less<int>, class mystd::allocator<int>>::_Node *> mystd::_Tree<int, struct mystd::pair<int const, int>, struct mystd::map<int, int, struct mystd::less<int>, class mystd::allocator<int>>::_Kfn, struct mystd::less<int>, class mystd::allocator<int>>::_Nil(SAKEXE, "?_Nil@?$_Tree@HU?$pair@$$CBHH@std@@U_Kfn@?$map@HHU?$less@H@std@@V?$allocator@H@2@@2@U?$less@H@2@V?$allocator@H@2@@std@@1PAU_Node@12@A");
class hook_val<unsigned int> mystd::_Tree<int, struct mystd::pair<int const, int>, struct mystd::map<int, int, struct mystd::less<int>, class mystd::allocator<int>>::_Kfn, struct mystd::less<int>, class mystd::allocator<int>>::_Nilrefs(SAKEXE, "?_Nilrefs@?$_Tree@HU?$pair@$$CBHH@std@@U_Kfn@?$map@HHU?$less@H@std@@V?$allocator@H@2@@2@U?$less@H@2@V?$allocator@H@2@@std@@1IA");
