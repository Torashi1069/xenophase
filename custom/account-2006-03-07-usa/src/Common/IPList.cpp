#include "Common/IPList.h"


CIPList::CIPList()
{
	m_pIPList = new tag_HashedIPList[100];
}


CIPList::~CIPList()
{
	if( m_pIPList != NULL )
	{
		for( int i = 0; i < 100; ++i )
		{
			stdext::hash_map<WORD,tag_IPRange*>::iterator it;
			for( it = m_pIPList[i].m_map.begin(); it != m_pIPList[i].m_map.end(); ++it )
				delete it->second;

			m_pIPList[i].m_map.clear();
		}

		delete[] m_pIPList;
	}
}


bool CIPList::AddIP(DWORD dwLowIP, DWORD dwHighIP)
{
	in_addr low, high;
	low.s_addr = dwLowIP;
	high.s_addr = dwHighIP;

	WORD prefix = low.S_un.S_un_w.s_w1;
	tag_HashedIPList* p = &m_pIPList[prefix % 100];

	if( low.S_un.S_un_w.s_w1 != high.S_un.S_un_w.s_w1 // different /16
	||  low.S_un.S_un_b.s_b3 > high.S_un.S_un_b.s_b3  // bad order
	||  low.S_un.S_un_b.s_b4 > high.S_un.S_un_b.s_b4 )
		return false;

	p->m_cs.Enter();

	tag_IPRange* range;
	stdext::hash_map<WORD,tag_IPRange*>::iterator it = p->m_map.find(prefix);
	if( it != p->m_map.end() )
		range = it->second;
	else
	{
		range = new tag_IPRange;
		if( range == NULL )
		{
			p->m_cs.Leave();
			return false;
		}

		memset(range, 0, sizeof(*range));
		range->baseIP = prefix;
		p->m_map[range->baseIP] = range;
	}

	BYTE start3 = low.S_un.S_un_b.s_b3;
	BYTE end3 = high.S_un.S_un_b.s_b3;
	range->list[start3].exist = true;

	if( end3 == start3 )
	{
		BYTE start4 = low.S_un.S_un_b.s_b4;
		BYTE end4 = high.S_un.S_un_b.s_b4;
		memset(&range->list[start3].list[start4], true, (end4 - start4 + 1) * sizeof(bool));
	}
	else
	{
		BYTE start4 = low.S_un.S_un_b.s_b3;
		BYTE end4 = high.S_un.S_un_b.s_b4;
		memset(&range->list[start3].list[start4], true, (256 - start4) * sizeof(bool));

		for( int i = start3 + 1; i < end3 - start3 - 1; ++i )
		{
			range->list[i].exist = true;
			memset(&range->list[i].list[start4], true, (end4 - start4 + 1) * sizeof(bool));
		}

		range->list[end3].exist = true;
		memset(&range->list[end3].list, true, (end4 - 0) * sizeof(bool));
	}

	p->m_cs.Leave();
	return true;
}


bool CIPList::IsExist(DWORD dwIP)
{
	WORD prefix = static_cast<WORD>(dwIP);
	tag_HashedIPList* p = &m_pIPList[prefix % 100];

	p->m_cs.Enter();
	stdext::hash_map<WORD,tag_IPRange*>::const_iterator result = p->m_map.find(prefix);
	p->m_cs.Leave();

	if( result == p->m_map.end() )
		return false;

	tag_IPRange* iprange = result->second;
	tag_range* range = &iprange->list[BYTE(dwIP >> 16)];
	return ( range->exist && range->list[BYTE(dwIP >> 24)] == true );
}
