#include "Account.h"
#include "AccountDB.h"
#include "BillingConnection.h"
#include "Certificate.h"
#include "UserList.h"
#include "UserVerify.h"
#include "Common/EnterTraceLog.h"
#include "Common/Network.h"
#include "Common/NOutputTextMgr.h"
#include "Common/Packet.h"
#include "Common/Thread.h"
#include "Network3/StreamManager.h"
#include "Enums.h"


/// locals
static DWORD g_dwLogTime = timeGetTime();
static bool g_bBillInitialized = true;
static int g_nACCOUNTSERVERTYPE;
static LONG g_cLogPerSec;
static LONG g_LogPerSec;


CBillingConnection::CBillingConnection()
{
	m_BillingServerType = NOMAL_BILLINGSERVER;
	this->CBillingConnection::Init();

	CreateMemberThread<CBillingConnection>(this, &CBillingConnection::SelectThread, NULL);
}


CBillingConnection::~CBillingConnection()
{
}


void CBillingConnection::SetServerType(BILLINGSERVER_TYPE type)
{
	m_BillingServerType = type;
}


void CBillingConnection::Init()
{
	if( m_BillingServerType == NOMAL_BILLINGSERVER )
		g_bBillInitialized = false;

	m_dwLastRecvTime = timeGetTime();
	this->CClient_::Init();
}


void CBillingConnection::Close()
{
	closesocket(m_socket);

	if( m_BillingServerType == NOMAL_BILLINGSERVER )
	{
		g_bBillInitialized = false;
		NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("GUMP BillingServer Disconnected.");
	}

	m_bConnected = false;
}


void CBillingConnection::SelectThread(void* lpParam)
{
	Sleep(100);

	timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 500;

	while( m_bProcessPermit )
	{
		if( !m_bConnected )
		{
			Sleep(1);
			continue;
		}

		fd_set rfds;
		fd_set efds;
		FD_ZERO(&rfds);
		FD_ZERO(&efds);
		FD_SET(m_socket, &rfds);
		FD_SET(m_socket, &efds);

		if( select(FD_SETSIZE, &rfds, 0, &efds, &tv) == SOCKET_ERROR )
		{
			CEnterTraceLog::GetObj()->CEnterTraceLog::LogFile("billing.txt", "select error gle: %d", WSAGetLastError());
			this->CBillingConnection::Close();
			continue;
		}

		if( FD_ISSET(m_socket, &rfds) )
		{
			m_dwLastRecvTime = timeGetTime();

			if( !this->CClient_::Recv() )
			{
				this->CBillingConnection::Close();
				continue;
			}
		}

		if( timeGetTime() - m_dwLastRecvTime > 3600000 )
		{
			CEnterTraceLog::GetObj()->CEnterTraceLog::LogFile("billing.txt", "no message from gums for 60 minutes");
			this->CBillingConnection::Close();
			continue;
		}

		if( FD_ISSET(m_socket, &efds) )
		{
			CEnterTraceLog::GetObj()->CEnterTraceLog::LogFile("billing.txt", "exception is set");
			this->CBillingConnection::Close();
			continue;
		}

		m_bSendable = true;

		if( !m_qSend.CSendQueue::ProcessQueue(this) )
		{
			CEnterTraceLog::GetObj()->CEnterTraceLog::LogFile("billing.txt", "Send Error");
			this->CBillingConnection::Close();
			continue;
		}

		if( m_qSend.m_dwCount > 55000 )
		{
			CEnterTraceLog::GetObj()->CEnterTraceLog::LogFile("billing.txt", "m_qSend.GetCount() %d", m_qSend.CSendQueue::GetCount());
			this->CBillingConnection::Close();
			continue;
		}
	}
}


bool CBillingConnection::Send(char* Packet, int MsgSize)
{
	static int count;

	m_csSend.CCriticalSection::Enter();

	char szUserID[255] = {};
	LONG CurLogCount = InterlockedIncrement(&g_cLogPerSec);
	if( timeGetTime() - g_dwLogTime > 1000 )
	{
		g_dwLogTime = timeGetTime();
		g_LogPerSec = CurLogCount;
		InterlockedExchange(&g_cLogPerSec, 0);

		++count;
		if( count > 60 )
			count = 0;
	}

	this->CClient_::Send(Packet, MsgSize);
	m_dwLastSendQueuedTime = timeGetTime();

	m_csSend.CCriticalSection::Leave();
	return true;
}


BOOL CBillingConnection::Process(char* buf, int* len)
{
	int pos = 0;
	const int maxpos = *len - 1;

	int packetlen = 0;
	while( pos < maxpos )
	{
		char* packet = &buf[pos];
		
		int i = 0;
		while( 1 )
		{
			if( packet[i] == '\t' )
			{// token separator
				if( packet[i+1] == '\0' )
				{
					packetlen = i + 1 + 1;
					break; // found end of packet.
				}

				if( packet[i+1] == '\t' )
					return FALSE; // empty token!

				i += 2;
			}
			else
			{// simple character
				i += 1;
			}
			
			if( pos + i >= maxpos )
			{
				if( i >= 0 ) // ??!!
				{
					*len = pos;
					return TRUE;
				}

				break;
			}
		}// while

		pos += packetlen;

		if( this->CBillingConnection::ProcessPacket(packet, packetlen) == FALSE )
			return FALSE;

	}// while

	*len = pos;
	return TRUE;
}


BOOL CBillingConnection::ProcessPacket(char* packet, int len)
{
	CAccountDB* pAccountDB = &g_AccountDB[m_socket % 5];

	int nSeqNum = 0;
	int nMsgType = 0;
	int nGameID = 0;
	char szUserID[255] = {};
	int nUserType = 0;
	int nTime = 0;
	int nargs = sscanf_s(packet, "GUMP/1.2\t%d\x1D""%d\t%d\t%s\t%d\t%d\t", &nSeqNum, &nMsgType, &nGameID, szUserID, &nUserType, &nTime);

	switch( nMsgType )
	{
	case 2:
	{
		CEnterTraceLog::GetObj()->CEnterTraceLog::LogFile("billing.txt", "### heart_beat ###");
	}
	break;
	case 11:
	{
		if( nargs != 5 )
		{
			CEnterTraceLog::GetObj()->CEnterTraceLog::LogFile("billing.txt", "nType %d fail in process! nArgNum: %d", nMsgType, nargs);
			break;
		}

		g_certificate.CCertificate::AnswerCertificate(pAccountDB->CAccountDB::GetAID(szUserID), 1, 0);
	}
	break;
	case 12:
	{
		g_certificate.CCertificate::AnswerCertificate(pAccountDB->CAccountDB::GetAID(szUserID), 0, 13);
	}
	break;
	case 13:
	case 14:
	case 16:
	case 18:
	case 19:
	{
		if( nargs != 5 )
		{
			CEnterTraceLog::GetObj()->CEnterTraceLog::LogFile("billing.txt", "nMsgType %d fail in process!", nMsgType);
			break;
		}

		CEnterTraceLog::GetObj()->CEnterTraceLog::LogFile("billing.txt", "### Login failed ### %s nMsgType: %d", szUserID, nMsgType);
		g_certificate.CCertificate::AnswerCertificate(pAccountDB->CAccountDB::GetAID(szUserID), 0, nMsgType);
	}
	break;
	case 15:
	{
		CEnterTraceLog::GetObj()->CEnterTraceLog::LogFile("billing.txt", "not expected message nMsgType %d nArgNum: %d", nMsgType, nargs);
	}
	break;
	case 17:
	{
		if( nargs != 5 )
		{
			CEnterTraceLog::GetObj()->CEnterTraceLog::LogFile("billing.txt", "nMsgType %d fail in process! nArgNum: %d", nMsgType, nargs);
			break;
		}

		SUSER_ user = {};
		DWORD dwAID = pAccountDB->CAccountDB::GetAID(szUserID);

		if( g_userList.CUserList::Get(dwAID, &user) == TRUE && g_nACCOUNTSERVERTYPE != 1 )
		{
			SCERTIFICATE certificate = {};
			g_certificate.CCertificate::GetCertificate(dwAID, certificate);
			certificate.m_dwIP = user.m_nIP;
			certificate.m_dwAID = dwAID;
			certificate.m_CharIndex = -1;
			g_certificate.CCertificate::TryCertificate(certificate);

			char szIP[100] = {};
			CNetwork::GetObj()->CNetwork::GetTextIP(certificate.m_dwIP, szIP);

			char szLogin[1000] = {};
			_snprintf_s(szLogin, sizeof(szLogin), _TRUNCATE, "GUMP/1.2\t1\x1D""10\t\1\t%d\t%s\t1\t11\t%s\t%s\t", GAME_ID, szUserID, szIP, szIP);
			this->Send(szLogin, strlen(szLogin) + 1);
		}
	}
	break;
	case 21:
	{
		if( nargs != 5 )
		{
			CEnterTraceLog::GetObj()->CEnterTraceLog::LogFile("billing.txt", "nMsgType %d fail in process! nArgNum: %d", nMsgType, nargs);
			break;
		}
	}
	break;
	case 22:
	{
	}
	break;
	case 51:
	case 52:
	case 53:
	{
		if( nargs != 6 )
		{
			CEnterTraceLog::GetObj()->CEnterTraceLog::LogFile("billing.txt", "nType %d fail in process! nArgNum: %d", nMsgType, nargs);
			break;
		}
	}
	break;
	case 64:
	{
		if( nargs != 5 )
		{
			CEnterTraceLog::GetObj()->CEnterTraceLog::LogFile("billing.txt", "nType %d fail in process! nArgNum: %d", nMsgType, nargs);
			break;
		}
	}
	break;
	case 61:
	case 62:
	case 63:
	case 65:
	{
		if( nargs != 5 )
		{
			CEnterTraceLog::GetObj()->CEnterTraceLog::LogFile("billing.txt", "nMsgType %d fail in process! nArgNum: %d", nMsgType, nargs);
			break;
		}

		SUSER_ user = {};
		DWORD dwAID = pAccountDB->CAccountDB::GetAID(szUserID);

		if( nMsgType == 65 )
		{
			if( g_userList.CUserList::Get(dwAID, &user) == TRUE )
			{
				SCERTIFICATE certificate = {};
				certificate.m_dwAID = user.m_nAID;
				certificate.m_dwIP = user.m_nIP;
				certificate.m_dwCharIP = -1;
				certificate.m_CharIndex = -1;
				g_certificate.CCertificate::TryCertificate(certificate);

				char szIP[64] = {};
				CNetwork::GetObj()->CNetwork::GetTextIP(user.m_nIP, szIP);

				char szLogin[1000] = {};
				_snprintf_s(szLogin, 1000u, _TRUNCATE, "GUMP/1.2\t1\x1D""10\t1\t%d\t%s\t1\t11\t%s\t%s\t", GAME_ID, user.m_szID, szIP, szIP);
				this->Send(szLogin, strlen(szLogin) + 1);

				break;
			}
		}
		else
		{
			CEnterTraceLog::GetObj()->CEnterTraceLog::MessagePrint("Disconnect Message(%d) - %s", nMsgType, szUserID);
		}

		g_userList.CUserList::Delete(dwAID);
		CSingleton<CUserVerify>::getSingletonPtr()->CUserVerify::DeleteUserVerify(dwAID);

		PACKET_AH_DISCONNECT ah_disconnect;
		ah_disconnect.PacketType = HEADER_AH_DISCONNECT;
		ah_disconnect.AID = dwAID;
		ah_disconnect.reason = ( nMsgType == 65 ) ? BAN_UNFAIR : BAN_PAY_OUT;
		g_CharSvrStreamMgr.CStreamManager::Broadcast((char*)&ah_disconnect, sizeof(ah_disconnect));

		char buf[1000] = {};
		_snprintf_s(buf, 1000, _TRUNCATE, "GUMP/1.2\t1\x1D""20\t%d\t%s\t1\t", GAME_ID, szUserID);
		this->Send(buf, strlen(buf) + 1);
	}
	break;
	case 88:
	{
		if( nargs != 5 )
		{
			CEnterTraceLog::GetObj()->CEnterTraceLog::LogFile("billing.txt", "nType %d fail in process! nArgNum: %d", nMsgType, nargs);
			break;
		}
	}
	break;
	case 99:
	{
		CEnterTraceLog::GetObj()->CEnterTraceLog::LogFile("billing.txt", "MESSAGE_ERROR!!!!!!!!!");
	}
	break;
	case 100:
	{
		if( m_BillingServerType == NOMAL_BILLINGSERVER )
		{
			g_bBillInitialized = true;
			NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("GUMP BillingServer Connected.");
		}

		CEnterTraceLog::GetObj()->CEnterTraceLog::LogFile("billing.txt", "### BILL(%s) Initialize success ###", ( m_BillingServerType == NOMAL_BILLINGSERVER ) ? "NomalBilling" : "GameBangBilling");
	}
	break;
	default:
	{
		CEnterTraceLog::GetObj()->CEnterTraceLog::MessagePrint("not defined!! BILL nMsgType: %d", nMsgType);
		CEnterTraceLog::GetObj()->CEnterTraceLog::LogFile("billing.txt", "not defined!! BILL nMsgType: %d", nMsgType);
	}
	break;
	};

	return TRUE;
}


DWORD CBillingConnection::GetLastQueuedTime()
{
	return m_dwLastSendQueuedTime;
}


void SendHeartBeatToBill(BILLINGSERVER_TYPE billingServerType)
{
/*
	//FIXME: code not available
*/
}
