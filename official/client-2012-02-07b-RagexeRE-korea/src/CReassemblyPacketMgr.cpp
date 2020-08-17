#include "CReassemblyPacket.h"
#include "CReassemblyPacketMgr.h"


/// singleton instance
CReassemblyPacketMgr*& CReassemblyPacketMgr::m_cpSelf = VTOR<CReassemblyPacketMgr*>(SymDB::Find("CReassemblyPacketMgr::m_cpSelf"));


CReassemblyPacketMgr::CReassemblyPacketMgr()
: m_bOK(false)
{
	if( this->CReassemblyPacketMgr::Create() )
		m_bOK = true;
}


CReassemblyPacketMgr::~CReassemblyPacketMgr()
{
	this->CReassemblyPacketMgr::Destroy();
}


bool CReassemblyPacketMgr::Create()
{
    return CReassemblyPacket::CreateInstance();
}


void CReassemblyPacketMgr::Destroy()
{
	CReassemblyPacket::DestroyInstance();
}


bool CReassemblyPacketMgr::CreateInstance()
{
    if( m_cpSelf != NULL )
        return false;

	m_cpSelf = new(std::nothrow) CReassemblyPacketMgr();
	if( m_cpSelf == NULL )
		return false;

    if( !m_cpSelf->CReassemblyPacketMgr::isOK() )
    {
        delete m_cpSelf;
        m_cpSelf = NULL;
        return false;
    }

    return true;
}


void CReassemblyPacketMgr::DestroyInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


//CReassemblyPacketMgr* CReassemblyPacketMgr::GetObj()
//{
//	return m_cpSelf;
//}


bool CReassemblyPacketMgr::isOK() const
{
	return m_bOK;
}
