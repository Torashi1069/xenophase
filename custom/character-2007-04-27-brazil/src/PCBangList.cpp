#include "PCBangList.h"


/// singleton instance
static CListedPCBangIPList gListedPCBangipLists;
CListedPCBangIPList* CSingleton<CListedPCBangIPList>::ms_Singleton;


CListedPCBangIPList::CListedPCBangIPList()
{
}


CListedPCBangIPList::~CListedPCBangIPList()
{
	if( m_setIPList.size() != 0 )
		m_setIPList.clear();
}
