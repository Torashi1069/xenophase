#pragma once
#include "Account.h"
#include "Common/CriticalSection.h"
#include "Common/Network.h"
#include "Common/Thread.h"


class CTBlockTime
{
public:
	CTBlockTime();
	~CTBlockTime();
	void UpdateBlockTime(DWORD dwAID, DWORD dwBlockTime);
//	void DeleteBlockTime(DWORD dwAID);
	BOOL IsBlock(DWORD dwAID);
	void threadBlockTime(void* lpParam);
	void AddIncorrectCount(DWORD dwAID, char* szID, DWORD dwIP);
	void SetIncorrectCount(DWORD dwAID, int8_t nCount);

private:
	/* this+       0 */ stdext::hash_map<DWORD,DWORD> m_mapBlockTime;
	/* this+      44 */ CCriticalSection m_csBlockTime;
	/* this+      68 */ int8_t m_PassIncorrect[MAX_ACCOUNTID];
	/* this+10000068 */ CCriticalSection m_csPassIncorrect;
};


void CTBlockTime::SetIncorrectCount(DWORD dwAID, int8_t nCount)
{
	m_csPassIncorrect.Enter();
	m_PassIncorrect[dwAID] = nCount;
	m_csPassIncorrect.Leave();
}


void CTBlockTime::AddIncorrectCount(DWORD dwAID, char* szID, DWORD dwIP)
{
	if( dwAID >= MAX_ACCOUNTID )
		return;

	m_csPassIncorrect.Enter();

	++m_PassIncorrect[dwAID];

	if( m_PassIncorrect[dwAID] == 20 )
	{
		this->CTBlockTime::UpdateBlockTime(dwAID, 300000); // 5 minute ban

		FILE* fp = NULL;
		fopen_s(&fp, "PassIncorrectLog1.txt", "a");

		if( fp != NULL )
		{
			time_t ltime;
			time(&ltime);

			tm now;
			localtime_s(&now, &ltime);

			char szTime[1024] = {};
			strftime(szTime, sizeof(szTime), "%Y-%m-%d %H:%M:%S", &now);

			char szIP[100] = {};
			CNetwork::GetObj()->CNetwork::GetTextIP(dwIP, szIP);

			fprintf_s(fp, "%s\t%s\t%s\n");
			fclose(fp);
		}
	}
	else
	if( m_PassIncorrect[dwAID] == 40 )
	{
		this->CTBlockTime::UpdateBlockTime(dwAID, 10800000); // 3 hour ban

		FILE* fp = NULL;
		fopen_s(&fp, "PassIncorrectLog2.txt", "a");

		if( fp != NULL )
		{
			time_t ltime;
			time(&ltime);

			tm now;
			localtime_s(&now, &ltime);

			char szTime[1024] = {};
			strftime(szTime, sizeof(szTime), "%Y-%m-%d %H:%M:%S", &now);

			char szIP[100] = {};
			CNetwork::GetObj()->CNetwork::GetTextIP(dwIP, szIP);

			fprintf_s(fp, "%s\t%s\t%s\n");
			fclose(fp);
		}

		m_PassIncorrect[dwAID] = 0;
	}

	m_csPassIncorrect.Leave();
}


CTBlockTime::CTBlockTime()
{
	m_csPassIncorrect.Enter();
	memset(m_PassIncorrect, (int8_t)0, sizeof(m_PassIncorrect));
	m_csPassIncorrect.Leave();

	CreateMemberThread<CTBlockTime>(this, &CTBlockTime::threadBlockTime, NULL);
}


CTBlockTime::~CTBlockTime()
{
}


void CTBlockTime::UpdateBlockTime(DWORD dwAID, DWORD dwBlockTime)
{
	m_csBlockTime.Enter();
	m_mapBlockTime[dwAID] = timeGetTime() + dwBlockTime;
	m_csBlockTime.Leave();
}


//void CTBlockTime::DeleteBlockTime(DWORD dwAID)
//{
//	//TODO
//}


BOOL CTBlockTime::IsBlock(DWORD dwAID)
{
	BOOL bIsBlock;
	m_csBlockTime.Enter();

	stdext::hash_map<DWORD,DWORD>::const_iterator it = m_mapBlockTime.find(dwAID);
	bIsBlock = ( it != m_mapBlockTime.end() ) ? TRUE : FALSE;

	m_csBlockTime.Leave();
	return bIsBlock;
}


void CTBlockTime::threadBlockTime(void* lpParam)
{
	while( g_bProcessPermit )
	{
		Sleep(100);

		m_csBlockTime.Enter();

		for( stdext::hash_map<DWORD,DWORD>::iterator it = m_mapBlockTime.begin(); it != m_mapBlockTime.end(); ++it )
		{
			if( timeGetTime() > it->second )
			{
				m_mapBlockTime.erase(it);
				break;
			}
		}

		m_csBlockTime.Leave();
	}
}
