#include "BlockIPManager.h"
#include "Common/Network.h"
#include "Common/Reporter.h"


/// singleton instance
static CBlockIPManager g_CBlockIPManagerInstance;
CBlockIPManager* CSingleton<CBlockIPManager>::ms_Singleton;


CBlockIPManager::CBlockIPManager()
{
	m_pBlockData = new tag_blockdata[100];
}


CBlockIPManager::~CBlockIPManager()
{
	delete[] m_pBlockData;
}


bool CBlockIPManager::IsBlock(DWORD dwKey)
{
	tag_blockdata* p = &m_pBlockData[dwKey % 100];
	stdext::hash_map<DWORD,tag_info>::iterator it;

	bool result;
	p->m_cs.Enter();

	it = p->m_mapBlockInfo.find(dwKey);
	if( it == p->m_mapBlockInfo.end() || it->second.incorrectCount < 5 )
	{// not blocked
		result = false;
	}
	else
	if( timeGetTime() >= it->second.dwBlockTime )
	{// not blocked anymore
		if( it->second.incorrectCount >= 20 )
			p->m_mapBlockInfo.erase(it);

		result = false;
	}
	else
	{// still blocked
		result = true;
	}

	p->m_cs.Leave();
	return result;
}


void CBlockIPManager::IncreaseIncorrectCount(char* szName, DWORD dwAID, DWORD dwIP, unsigned char keyType)
{
	DWORD dwKey = ( keyType == 0 ) ? dwAID : dwIP;
	tag_blockdata* p = &m_pBlockData[dwKey % 100];
	stdext::hash_map<DWORD,tag_info>::iterator it;
	tag_info tmp;

	p->m_cs.Enter();

	it = p->m_mapBlockInfo.find(dwKey);
	if( it == p->m_mapBlockInfo.end() )
	{
		tmp.dwBlockTime = 0;
		tmp.incorrectCount = 1;
	}
	else
	{
		tmp.dwBlockTime = it->second.dwBlockTime;
		tmp.incorrectCount = it->second.incorrectCount + 1;

		if( tmp.incorrectCount == 5 )
		{
			tmp.dwBlockTime = timeGetTime() + 300000;

			char ipbuf[32];
			CSingleton<CNetwork>::getSingletonPtr()->CNetwork::GetTextIP(dwIP, ipbuf);
			CSingleton<CReporter>::getSingletonPtr()->CReporter::FilePrint("IncorrectPassList_5.txt", "AID: %d\tID: %s\t IP: %s", dwAID, szName, ipbuf);
		}
		else
		if( tmp.incorrectCount == 20 )
		{
			tmp.dwBlockTime = timeGetTime() + 1800000;

			char ipbuf[32];
			CSingleton<CNetwork>::getSingletonPtr()->CNetwork::GetTextIP(dwIP, ipbuf);
			CSingleton<CReporter>::getSingletonPtr()->CReporter::FilePrint("IncorrectPassList_20.txt", "AID: %d\tID: %s\t IP: %s", dwAID, szName, ipbuf);
		}
	}

	p->m_mapBlockInfo[dwKey] = tmp;

	p->m_cs.Leave();
}


void CBlockIPManager::ClearIncorrectCount(DWORD dwKey)
{
	tag_blockdata* p = &m_pBlockData[dwKey % 100];
	stdext::hash_map<DWORD,tag_info>::iterator it;

	p->m_cs.Enter();

	it = p->m_mapBlockInfo.find(dwKey);
	if( it != p->m_mapBlockInfo.end() )
		it->second.incorrectCount = 0;

	p->m_cs.Leave();
}


bool CBlockIPManager::loadBlockIPListFile(char* szFileName)
{
	FILE* f = fopen(szFileName, "r");
	if( f == NULL )
		return false;

	while( !feof(f) )
	{
		char szBuf[512];
		if( fgets(szBuf, sizeof(szBuf), f) == NULL )
		{
			fclose(f);
			return false;
		}

		char highip[64];
		char lowip[64];
		sscanf(szBuf, "%s %s", lowip, highip);

		DWORD dwHighIP = CSingleton<CNetwork>::getSingletonPtr()->CNetwork::GetDWORDIP(highip);
		DWORD dwLowIP = CSingleton<CNetwork>::getSingletonPtr()->CNetwork::GetDWORDIP(lowip);
		m_iplistPermanentBlock.CIPList::AddIP(dwLowIP, dwHighIP);
	}

//	fclose(f); //FIXME
	return true;
}


bool CBlockIPManager::IsPermanentBlock(DWORD dwKey)
{
	return m_iplistPermanentBlock.CIPList::IsExist(dwKey);
}
