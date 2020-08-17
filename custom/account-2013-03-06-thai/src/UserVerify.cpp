#include "Account.h"
#include "AccountDB.h"
#include "UserList.h"
#include "UserVerify.h"
#include "Common/EnterTraceLog.h"
#include "Common/Packet.h"
#include "Common/Thread.h"
#include "Network3/StreamManager.h"
#include "Enums.h"


/// singleton instance
static CUserVerify g_userVerify;
CUserVerify* CSingleton<CUserVerify>::ms_Singleton;


CUserVerify::CUserVerify()
{
	CreateMemberThread<CUserVerify>(this, &CUserVerify::threadUserVerify, NULL);
}


CUserVerify::~CUserVerify()
{
}


void CUserVerify::UpdateUserVerify(DWORD dwAID, DWORD dwVerifyTime)
{
	int nHash = dwAID % 100;
	if( nHash < 0 )
		return;

	m_csUserVerify[nHash].Enter();

	std::list<SUSERVERIFY>::iterator it;
	for( it = m_listUserVerify[nHash].begin(); it != m_listUserVerify[nHash].end(); ++it )
	{
		if( it->m_dwAID == dwAID )
		{
			m_listUserVerify[nHash].erase(it);
			break;
		}
	}

	SUSERVERIFY userVerify;
	userVerify.m_dwAID = dwAID;
	userVerify.m_dwVerifyTime = timeGetTime() + dwVerifyTime;
	m_listUserVerify[nHash].push_back(userVerify);

	m_csUserVerify[nHash].Leave();
}


void CUserVerify::DeleteUserVerify(DWORD dwAID)
{
	int nHash = dwAID % 100;
	if( nHash < 0 )
		return;

	m_csUserVerify[nHash].Enter();

	std::list<SUSERVERIFY>::iterator it;
	for( it = m_listUserVerify[nHash].begin(); it != m_listUserVerify[nHash].end(); ++it )
	{
		if( it->m_dwAID == dwAID )
		{
			m_listUserVerify[nHash].erase(it);
			break;
		}
	}

	m_csUserVerify[nHash].Leave();
}


void CUserVerify::threadUserVerify(void* lpParam)
{
	while( g_bProcessPermit )
	{
		for( int i = 0; i < 100; ++i )
		{
			Sleep(2);

			m_csUserVerify[i].Enter();

			DWORD dwAID = -1;

			std::list<SUSERVERIFY>::iterator it;
			for( it = m_listUserVerify[i].begin(); it != m_listUserVerify[i].end(); ++it )
			{
				if( timeGetTime() > it->m_dwVerifyTime )
				{
					dwAID = it->m_dwAID;
					m_listUserVerify[i].erase(it);
					break;
				}
			}

			m_csUserVerify[i].Leave();

			if( dwAID != -1 )
			{
				PACKET_AH_DISCONNECT ah_disconnect = {};
				ah_disconnect.PacketType = HEADER_AH_DISCONNECT;
				ah_disconnect.AID = dwAID;
				ah_disconnect.reason = BAN_UNFAIR; //???
				g_CharSvrStreamMgr.CStreamManager::Broadcast((char*)&ah_disconnect, sizeof(ah_disconnect));

				SUSER_ user;
				if( g_userList.CUserList::Bring(dwAID, &user) == TRUE )
				{
					if( user.m_nIsGameStarted )
					{
						char szExit[512] = {}; //NOTE: unused
						_snprintf_s(szExit, sizeof(szExit), _TRUNCATE, "GUMP/1.2" "\t" "1" "\x1D" "20" "\t" "%d" "\t" "%s" "\t" "1" "\t", GAME_ID, user.m_szID);
					}
					
				}
				else
				{
					char szID[255] = {};
					g_AccountDB[0].CAccountDB::GetID(dwAID, szID);
					if( strlen(szID) != 0 )
					{
						char szExit[512] = {}; //NOTE: unused
						_snprintf_s<sizeof(szExit)>(szExit, sizeof(szExit), "GUMP/1.2" "\t" "1" "\x1D" "20" "\t" "%d" "\t" "%s" "\t" "1" "\t", GAME_ID, szID);
					}
				}
			}
		}// for
	}// while

	CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "threadUserVerify OUT\n");
}
