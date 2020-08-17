#include "shared/N3System/N3DataTransferMgr.h"
#include "shared/N3System/N3SyncObject.h"


/// singleton instance
N3DataTransferMgr*& N3DataTransferMgr::m_cpSelf = VTOR<N3DataTransferMgr*>(DetourFindFunction(EXEPATH(), "N3DataTransferMgr::m_cpSelf"));


N3DataTransferMgr::N3DataTransferMgr()
: m_bOK(false)
{
	InitializeCriticalSection(&m_CS);
	m_bOK = true;
}


N3DataTransferMgr::~N3DataTransferMgr()
{
	DeleteCriticalSection(&m_CS);
}


namespace {
class lcDataTransferKeyGenerator
{
public:
	lcDataTransferKeyGenerator() { m_Cnt = 0; }
	virtual ~lcDataTransferKeyGenerator() { }

public:
	unsigned int operator()() { return m_Cnt++; }

private:
	/* this+0 */ //const lcDataTransferKeyGenerator::`vftable';
	/* this+4 */ unsigned int m_Cnt;
};

lcDataTransferKeyGenerator& InstancelcDataTransferKeyGenerator = VTOR<lcDataTransferKeyGenerator>(DetourFindFunction(EXEPATH(), "?InstancelcDataTransferKeyGenerator@?A0x4cc94413@@3VlcDataTransferKeyGenerator@1@A"));
}; // namespace


std::string N3DataTransferMgr::GetStr(unsigned int in_Key)
{
	N3SyncObject sync(m_CS);

	DATAMAP::iterator iter = m_DataMap.find(in_Key);
	if( iter == m_DataMap.end() )
		return std::string();

	return std::string(iter->second.m_data.begin(), iter->second.m_data.end());
}


std::vector<unsigned char> N3DataTransferMgr::Get(unsigned int in_Key)
{
	N3SyncObject sync(m_CS);

	DATAMAP::iterator iter = m_DataMap.find(in_Key);
	if( iter == m_DataMap.end() )
		return std::vector<unsigned char>();

	return iter->second.m_data;
}


unsigned int N3DataTransferMgr::Put(std::string in_Str)
{
	return this->N3DataTransferMgr::Put(std::vector<unsigned char>(in_Str.begin(), in_Str.end()));
}


unsigned int N3DataTransferMgr::Put(std::vector<unsigned char>& in_Data)
{
	N3SyncObject sync(m_CS);

	unsigned long Time = time(NULL);
	unsigned int myKey = InstancelcDataTransferKeyGenerator();

	m_DataMap[myKey] = N3DataTransferMgr::lcData(in_Data, Time);

	DATAMAP::const_iterator iter = m_DataMap.begin();
	if( iter != m_DataMap.end() && Time > iter->second.m_Time + DATA_GUARANTEE_TIME_SEC )
		m_DataMap.erase(m_DataMap.begin()); // expired

	return myKey;
}


bool N3DataTransferMgr::CreateInstance()
{
	if( m_cpSelf != NULL )
		return false;

	m_cpSelf = new(std::nothrow) N3DataTransferMgr();
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->N3DataTransferMgr::isOK() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void N3DataTransferMgr::DestroyInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


N3DataTransferMgr* N3DataTransferMgr::GetObj() /// @custom
{
	return m_cpSelf;
}


bool N3DataTransferMgr::isOK() const
{
	return m_bOK;
}
