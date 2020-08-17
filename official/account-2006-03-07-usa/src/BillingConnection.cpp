#include "Account.h"
#include "AccountDB.h"
#include "BillingConnection.h"
#include "Certificate.h"
#include "UserList.h"
#include "UserVerify.h"
#include "Common/Network.h"
#include "Common/Packet.h"
#include "Common/Reporter.h"
#include "Common/Thread.h"
#include "Network2/StreamManager.h"
#include "Enums.h" // enumBANTYPE


CBillingConnection::CBillingConnection(int idx)
{
	m_nMyID = idx;
	m_listen_socket = INVALID_SOCKET;
	m_bInitialized = false;
	this->CClient_::Init();

	CreateMemberThread<CBillingConnection>(this, &CBillingConnection::SelectThread, NULL);
}


CBillingConnection::~CBillingConnection()
{
}


void CBillingConnection::Init()
{
	m_bInitialized = false;
	this->CClient_::Init();
}


void CBillingConnection::Close()
{
	if( m_socket != INVALID_SOCKET )
	{
		closesocket(m_socket);
		m_socket = INVALID_SOCKET;
	}

	m_bInitialized = false;
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
			Sleep(100);
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
			CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("select error gle: %d\n", WSAGetLastError());
			this->CBillingConnection::Close();
			continue;
		}

		if( FD_ISSET(m_socket, &rfds) )
		{
			if( !this->CClient_::Recv() )
			{
				this->CBillingConnection::Close();
				continue;
			}
		}

		if( FD_ISSET(m_socket, &efds) )
		{
			CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("exception is set\n");
			this->CBillingConnection::Close();
			continue;
		}

		m_bSendable = true;

		if( !m_qSend.CSendQueue::ProcessQueue(this) )
		{
			CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("Send Error\n");
			this->CBillingConnection::Close();
			continue;
		}

		if( m_qSend.m_dwCount > 55000 )
		{
			CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("m_qSend.GetCount() %d\n", m_qSend.m_dwCount);
			this->CBillingConnection::Close();
			continue;
		}
	}
}


bool CBillingConnection::Send(char* Packet, int MsgSize)
{
	m_csSend.CCriticalSection::Enter();

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
	CAccountDB* pAccountDB = &g_AccountDB[m_nMyID];

	int nSeqNum = 0;
	int nMsgType = 0;
	int nGameID = 0;
	char szUserID[255] = {};
	int nUserType = 0;
	int nTime = 0;
	int nargs = sscanf(packet, "GUMP/1.2\t%d\x1D""%d\t%d\t%s\t%d\t%d\t", &nSeqNum, &nMsgType, &nGameID, szUserID, &nUserType, &nTime);

	switch( nMsgType )
	{
	case 2:
	{
		CSingleton<CReporter>::getSingletonPtr()->CReporter::MessagePrint("### heart_beat ###\n");
	}
	break;
	case 11:
	{
		if( nargs != 5 )
		{
			CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("nType %d fail in process! nArgNum: %d\n", nMsgType, nargs);
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
			CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("nMsgType %d fail in process!\n", nMsgType);
			break;
		}

		CSingleton<CReporter>::getSingletonPtr()->CReporter::MessagePrint("### Login failed ### %s nMsgType: %d\n", szUserID, nMsgType);
		g_certificate.CCertificate::AnswerCertificate(pAccountDB->CAccountDB::GetAID(szUserID), 0, nMsgType);
	}
	break;
	case 15:
	{
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("not expected message nMsgType %d nArgNum: %d\n", nMsgType, nargs);
	}
	break;
	case 17:
	{
		if( nargs != 5 )
		{
			CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("nMsgType %d fail in process! nArgNum: %d\n", nMsgType, nargs);
			break;
		}

		SUSER_ user = {};
		DWORD dwAID = pAccountDB->CAccountDB::GetAID(szUserID);

		if( g_userList.CUserList::Get(dwAID, &user) == TRUE )
		{
			SCERTIFICATE certificate = {};
			g_certificate.CCertificate::GetCertificate(dwAID, certificate);
			certificate.m_dwIP = user.m_nIP;
			certificate.m_dwAID = dwAID;
			certificate.m_CharIndex = -1;
			g_certificate.CCertificate::TryCertificate(certificate);

			char szIP[100] = {};
			CSingleton<CNetwork>::getSingletonPtr()->CNetwork::GetTextIP(certificate.m_dwIP, szIP);

			char szLogin[1000] = {};
			sprintf(szLogin, "GUMP/1.2\t1\x1D""10\t1\t%d\t%s\t1\t11\t%s\t%s\t", g_GameID[m_nMyID], szUserID, szIP, szIP);
			this->Send(szLogin, strlen(szLogin) + 1);
		}
	}
	break;
	case 21:
	{
		if( nargs != 5 )
		{
			CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("nMsgType %d fail in process! nArgNum: %d\n", nMsgType, nargs);
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
			CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("nType %d fail in process! nArgNum: %d\n", nMsgType, nargs);
			break;
		}
	}
	break;
	case 64:
	{
		if( nargs != 5 )
		{
			CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("nType %d fail in process! nArgNum: %d\n", nMsgType, nargs);
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
			CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("nMsgType %d fail in process! nArgNum: %d\n", nMsgType, nargs);
			break;
		}

		SUSER_ user;
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

				char szIP[100];
				CSingleton<CNetwork>::getSingletonPtr()->CNetwork::GetTextIP(user.m_nIP, szIP);

				char szLogin[1000] = {};
				sprintf(szLogin, "GUMP/1.2\t1\x1D""10\t1\t%d\t%s\t1\t11\t%s\t%s\t", g_GameID[m_nMyID], user.m_szID, szIP, szIP);
				this->Send(szLogin, strlen(szLogin) + 1);

				break;
			}
		}
		else
		{
			CSingleton<CReporter>::getSingletonPtr()->CReporter::MessagePrint("Disconnect Message(%d) - %s\n", nMsgType, szUserID);
		}

		g_userList.CUserList::Delete(dwAID);
		CSingleton<CUserVerify>::getSingletonPtr()->CUserVerify::DeleteUserVerify(dwAID);

		PACKET_AH_DISCONNECT ah_disconnect;
		ah_disconnect.PacketType = HEADER_AH_DISCONNECT;
		ah_disconnect.AID = dwAID;
		ah_disconnect.reason = ( nMsgType == 65 ) ? BAN_UNFAIR : BAN_PAY_OUT;
		g_CharSvrStreamMgr.CStreamManager::Broadcast((char*)&ah_disconnect, sizeof(ah_disconnect));
	}
	break;
	case 88:
	{
		if( nargs != 5 )
		{
			CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("nType %d fail in process! nArgNum: %d\n", nMsgType, nargs);
			break;
		}
	}
	break;
	case 99:
	{
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("MESSAGE_ERROR!!!!!!!!!\n");
	}
	break;
	case 100:
	{
		if( !m_bInitialized )
		{
			m_bInitialized = true;
			CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("### BILL Initialize success %d ###\n", m_nMyID);
		}
	}
	break;
	default:
	{
		CSingleton<CReporter>::getSingletonPtr()->CReporter::MessagePrint("not defined!! BILL nMsgType: %d\n", nMsgType);
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("not defined!! BILL nMsgType: %d\n", nMsgType);
	}
	break;
	};

	return TRUE;
}


DWORD CBillingConnection::GetLastQueuedTime()
{
	return m_dwLastSendQueuedTime;
}
