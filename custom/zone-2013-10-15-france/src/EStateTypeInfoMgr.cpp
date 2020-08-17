#include "EStateTypeInfoMgr.h"


/// singleton instance
EStateTypeInfoMgr*& EStateTypeInfoMgr::m_cpSelf = VTOR<EStateTypeInfoMgr*>(DetourFindFunction(EXEPATH(), "EStateTypeInfoMgr::m_cpSelf"));


EStateTypeInfoMgr::EStateTypeInfoMgr()
{
	m_bOK = false;

	if( this->EStateTypeInfoMgr::Create()
	 && this->EStateTypeInfoMgr::LoadConfigFile() )
		m_bOK = true;
}


EStateTypeInfoMgr::~EStateTypeInfoMgr()
{
	this->EStateTypeInfoMgr::Destroy();
}


void EStateTypeInfoMgr::Destroy()
{
	for( ESTATETYPEINFO_CONTAINER::iterator iter = m_ESateTypeInfoList.begin(); iter != m_ESateTypeInfoList.end(); ++iter )
		delete iter->second;

	m_ESateTypeInfoList.clear();
	m_EStateTypeInfoNameList.clear();
}


bool EStateTypeInfoMgr::LoadConfigFile() // 87-174
{
	return false;
	//TODO
}


bool EStateTypeInfoMgr::Create() // 177-941-1233
{
	return false;
	//TODO
}


bool EStateTypeInfoMgr::CreateInstance() // 1236-1244
{
	if( m_cpSelf != NULL )
		return false;

	m_cpSelf = new(std::nothrow) EStateTypeInfoMgr();
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->EStateTypeInfoMgr::isOK() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void EStateTypeInfoMgr::DestoryInstance() // 1246-1249
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


EStateTypeInfoMgr* EStateTypeInfoMgr::GetObj() /// @custom
{
	return m_cpSelf;
}


bool EStateTypeInfoMgr::isOK() const
{
	return m_bOK;
}


ESTATE* EStateTypeInfoMgr::GetPtr(const int in_EStateID) // 1252-1258
{
	return NULL;
	//TODO
}


ESTATE* EStateTypeInfoMgr::GetPtr(const char* in_EStateName) // 1261-1267
{
	return NULL;
	//TODO
}


void EStateTypeInfoMgr::SetComplete(const int in_EStateID, CActor* in_cpActor, const int in_Time, const int in_Val1, const int in_Val2, const int in_Val3) // 1278-1283
{
	//TODO
}


bool EStateTypeInfoMgr::SetCheckup(const int in_EStateID, CActor* in_cpActor, int& io_Time, int& io_Val1, int& io_Val2, int& io_Val3) // 1293-1299
{
	return false;
	//TODO
}


void EStateTypeInfoMgr::ResetComplete(const int in_EStateID, CActor* in_cpActor, const int in_Val1, const int in_Val2, const int in_Val3) // 1309-1314
{
	//TODO
}


bool EStateTypeInfoMgr::ResetCheckup(const int in_EStateID, CActor* in_cpActor, const int in_Val, EFFECTIVE_INFO* io_pInfo) // 1322-1328
{
	return false;
	//TODO
}


void EStateTypeInfoMgr::Process(const int in_EStateID, CActor* in_cpActor, EFFECTIVE_INFO* io_pInfo) // 1335-1340
{
	//TODO
}


bool EStateTypeInfoMgr::InitScript() // 1404-1410
{
	return false;
	//TODO
}


bool EStateTypeInfoMgr::RunScript(const unsigned long in_AID, const int in_EventType, const int in_EStateID) // 1414-1435
{
	return false;
	//TODO
}


int EStateTypeInfoMgr::GetEStateID(const char* in_EStateName) // 1443-1447
{
	return 0;
	//TODO
}


namespace {
std::set<int> GetInfinityTimeEfstSaveTbl() // 1519-1605
{
	return std::set<int>();
	//TODO
}
}; // namespace


bool EStateTypeInfoMgr::IsSaveInfinitTimeEfst(const int in_Efst) const // 1609-1612
{
	return false;
	//TODO
}


bool EStateTypeInfoMgr::IsSave(const unsigned long in_CurTM, const int in_Efst, const EFFECTIVE_INFO& in_Data) // 1615-1627
{
	return false;
	//TODO
}
