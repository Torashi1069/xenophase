#include "PCBangList.h"


CListedPCBangIPList::CListedPCBangIPList()
{
}


CListedPCBangIPList::~CListedPCBangIPList()
{
	if( m_setIPList.size() != 0 )
		m_setIPList.clear();
}
