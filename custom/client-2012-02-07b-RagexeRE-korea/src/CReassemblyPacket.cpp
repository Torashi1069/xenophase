#include "CReassemblyPacket.h"


/// singleton instance
CReassemblyPacket*& CReassemblyPacket::m_cpSelf = VTOR<CReassemblyPacket*>(SymDB::Find("CReassemblyPacket::m_cpSelf"));


CReassemblyPacket::CReassemblyPacket()
{
	m_currentVal = 0;
	m_mulFactor = 0;
	m_addFactor = 0;
	m_bOK = true;
}


CReassemblyPacket::~CReassemblyPacket()
{
}


bool CReassemblyPacket::CreateInstance()
{
    if( m_cpSelf != NULL )
        return false;

	m_cpSelf = new(std::nothrow) CReassemblyPacket();
	if( m_cpSelf == NULL )
		return false;

    if( !m_cpSelf->CReassemblyPacket::isOK() )
    {
        delete m_cpSelf;
        m_cpSelf = NULL;
        return false;
    }

    return true;
}


void CReassemblyPacket::DestroyInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


CReassemblyPacket* CReassemblyPacket::GetObj()
{
	return m_cpSelf;
}


bool CReassemblyPacket::isOK() const
{
	return m_bOK;
}


void CReassemblyPacket::Seed(DWORD startVal, DWORD mulFactor, DWORD addFactor)
{
	m_currentVal = startVal;
	m_mulFactor = mulFactor;
	m_addFactor = addFactor;
}


int CReassemblyPacket::GetVal()
{
	m_currentVal = m_currentVal * m_mulFactor + m_addFactor;
	return (m_currentVal >> 16) & 0x7FFF;
}
