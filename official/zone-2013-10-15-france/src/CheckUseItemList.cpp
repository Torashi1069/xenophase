#include "CheckUseItemList.h"


/// singleton instance
CCheckUseItemList*& CCheckUseItemList::m_self = VTOR<CCheckUseItemList*>(DetourFindFunction(EXEPATH(), "CCheckUseItemList::m_self"));


CCheckUseItemList::CCheckUseItemList()
{
}


CCheckUseItemList::~CCheckUseItemList()
{
	m_createItemList.clear();
}


bool CCheckUseItemList::CreateInstance()
{
	CCheckUseItemList* m_self = new(std::nothrow) CCheckUseItemList();
	if( m_self == NULL )
		return false;

	return true;
}


void CCheckUseItemList::DestroyInstance()
{
	delete m_self;
	m_self = NULL;
}


CCheckUseItemList* CCheckUseItemList::GetObj() ///@custom
{
	return m_self;
}


void CCheckUseItemList::AddItemID_Create(unsigned short ITEMID)
{
	m_createItemList[ITEMID] = 1;
}


bool CCheckUseItemList::IsLimited_Create(unsigned short ITEMID)
{
	std::map<unsigned short,char>::iterator iter = m_createItemList.find(ITEMID);
	if( iter == m_createItemList.end() )
		return false;

	return true;
}
