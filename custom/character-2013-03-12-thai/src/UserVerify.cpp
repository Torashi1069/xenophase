#include "Character.h" // g_UserList
#include "UserList.h"
#include "UserVerify.h"
#include "Common/EnterTraceLog.h"
#include "Common/Thread.h"


/// singleton instance
static CUserVerify g_UserVerify;
CUserVerify* CSingleton<CUserVerify>::ms_Singleton;


CUserVerify::CUserVerify()
{
	m_bThread = false;
}


CUserVerify::~CUserVerify()
{
}


void CUserVerify::StartThread()
{
	m_bThread = true;
	CreateMemberThread<CUserVerify>(this, &CUserVerify::threadUserVerify, NULL);
}


void CUserVerify::EndThread()
{
	m_bThread = false;
}


void CUserVerify::UpdateUserVerify(DWORD dwAID, DWORD dwVerifyTime)
{
	if( !m_bThread )
		return;

	int nHash = dwAID % 100;
	if( nHash < 0 )
	{
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "CUserVerify::UpdateUserVerify() (nHash = %d)", nHash);
		return;
	}

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
	userVerify.m_dwLastPingTime = timeGetTime();
	userVerify.m_dwVerifyTime = timeGetTime() + dwVerifyTime;
	m_listUserVerify[nHash].push_back(userVerify);

	m_csUserVerify[nHash].Leave();
}


int CUserVerify::Get(DWORD dwAID, SUSERVERIFY& UserVerifyInfo)
{
	if( !m_bThread )
		return false;

	int nHash = dwAID % 100;
	if( nHash < 0 )
	{
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "CUserVerify::Get() 0 > (nHash = %d) AID:%d ", nHash, dwAID);
		return false;
	}

	BOOL bRet = FALSE;
	m_csUserVerify[nHash].Enter();

	std::list<SUSERVERIFY>::iterator it;
	for( it = m_listUserVerify[nHash].begin(); it != m_listUserVerify[nHash].end(); ++it )
	{
		if( it->m_dwAID == dwAID )
		{
			UserVerifyInfo.m_dwAID = it->m_dwAID;
			UserVerifyInfo.m_dwVerifyTime = it->m_dwVerifyTime;
			UserVerifyInfo.m_dwLastPingTime = it->m_dwLastPingTime;
			bRet = TRUE;
			break;
		}
	}

	m_csUserVerify[nHash].Leave();
	return bRet;
}


void CUserVerify::DeleteUserVerify(DWORD dwAID)
{
	if( !m_bThread )
		return;

	int nHash = dwAID % 100;
	if( nHash < 0 )
	{
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "CUserVerify::DeleteUserVerify() (nHash = %d)", nHash);
		return;
	}

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


void CUserVerify::threadUserVerify(void* pVoid)
{
	while( m_bThread )
	{
		for( int i = 0; i < 100; ++i )
		{
			Sleep(2);

			DWORD dwAID = -1;

			m_csUserVerify[i].Enter();

			std::list<SUSERVERIFY>::iterator it;
			for( it = m_listUserVerify[i].begin(); it != m_listUserVerify[i].end(); ++it )
			{
				if( timeGetTime() > it->m_dwVerifyTime )
				{
					dwAID = it->m_dwAID;
					m_listUserVerify[i].erase(it);
					break; // found one.
				}
			}

			m_csUserVerify[i].Leave();

			if( dwAID != -1 )
				g_UserList.CUserList::Delete(dwAID);
		}
	}
}
