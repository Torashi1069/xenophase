#include "Account.h"
#include "UserList.h"
#include "UserVerify.h"
#include "Common/Reporter.h"
#include "Common/Thread.h"


/// singleton instance
static CUserVerify g_UserVerify;
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
				SUSER_ user;
				if( g_userList.CUserList::Bring(dwAID, &user) == TRUE )
				{
				}
				else
				{
				}
			}
		}// for
	}// while

	CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("threadUserVerify OUT\n");
}
