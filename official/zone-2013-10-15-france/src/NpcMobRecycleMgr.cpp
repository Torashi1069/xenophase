#include "NpcMobRecycleMgr.h"
#include "ZoneProcess.h"


/// singleton instance
CNpcMobRecycleMgr*& CNpcMobRecycleMgr::m_cpSelf = VTOR<CNpcMobRecycleMgr*>(DetourFindFunction(EXEPATH(), "CNpcMobRecycleMgr::m_cpSelf"));


CNpcMobRecycleMgr::CNpcMobRecycleMgr(const int in_MaxGeneratorNum)
: m_WastepaperBasket(), m_GeneratorCnt(0), m_MaxGeneratorNum(in_MaxGeneratorNum), m_bOK(false)
{
	m_bOK = true;
}


CNpcMobRecycleMgr::~CNpcMobRecycleMgr()
{
	for( std::list<CNpcMob*>::iterator iter = m_WastepaperBasket.begin(); iter != m_WastepaperBasket.end(); ++iter )
		delete *iter;
}


hook_func<void (CNpcMobRecycleMgr::*)()> CNpcMobRecycleMgr__Process(EXEPATH(), "CNpcMobRecycleMgr::Process");
void CNpcMobRecycleMgr::Process()
{
	return (this->*CNpcMobRecycleMgr__Process)(); //TODO

	if( m_GeneratorCnt >= m_MaxGeneratorNum )
		return;

	++m_GeneratorCnt; //FIXME: incremented too early

	CNpcMob* pNpcMob = new(std::nothrow) CNpcMob();
	if( pNpcMob == NULL )
		return; 

	this->CNpcMobRecycleMgr::Put(pNpcMob);
}


void CNpcMobRecycleMgr::Put(CNpcMob* in_cpNpcMob)
{
	if( in_cpNpcMob == NULL )
		return;

	m_WastepaperBasket.push_back(in_cpNpcMob);
}


hook_func<CNpcMob* (CNpcMobRecycleMgr::*)()> CNpcMobRecycleMgr__Get(EXEPATH(), "CNpcMobRecycleMgr::Get");
CNpcMob* CNpcMobRecycleMgr::Get()
{
	return (this->*CNpcMobRecycleMgr__Get)(); //TODO

	if( m_WastepaperBasket.size() != 0 )
	{
		CNpcMob* pNpcMob = m_WastepaperBasket.front();
		m_WastepaperBasket.pop_front();
		pNpcMob->Init();
		return pNpcMob;
	}
	else
	{
		CNpcMob* pNpcMob = new(std::nothrow) CNpcMob();
		return pNpcMob;
	}
}


bool CNpcMobRecycleMgr::CreateInstance()
{
	if( m_cpSelf != NULL )
		return false;

	int MaxGeneratorNum = (int)GetPrivateProfileIntA("NPCMOB", "recycle object generator num", 3000, g_infFile);
	if( MaxGeneratorNum < 10 )
		MaxGeneratorNum = 10;
	if( MaxGeneratorNum > 3000 )
		MaxGeneratorNum = 3000;

	m_cpSelf = new(std::nothrow) CNpcMobRecycleMgr(MaxGeneratorNum);
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->CNpcMobRecycleMgr::isOK() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void CNpcMobRecycleMgr::DestroyInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


CNpcMobRecycleMgr* CNpcMobRecycleMgr::GetObj() /// @custom
{
	return m_cpSelf;
}


bool CNpcMobRecycleMgr::isOK() const
{
	return m_bOK;
}
