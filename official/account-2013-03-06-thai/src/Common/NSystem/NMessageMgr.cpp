#include "Common/NSystem/NInter.h"
#include "Common/NSystem/NMessageMgr.h"
#include "Common/NSyncObject.h"


/// singleton instance
NMessageMgr* NMessageMgr::m_cpSelf;


NMessageMgr::NMessageMgr()
{
	m_bOK = false;
	InitializeCriticalSection(&m_CS);
	m_bOK = true;
}


NMessageMgr::~NMessageMgr()
{
	DeleteCriticalSection(&m_CS);
}


bool NMessageMgr::CreateInstance()
{
	m_cpSelf = new(std::nothrow) NMessageMgr();
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->m_bOK )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void NMessageMgr::DestroyInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


/// @custom
NMessageMgr* NMessageMgr::GetObj()
{
	return m_cpSelf;
}


bool NMessageMgr::isOK() const
{
	return m_bOK;
}


bool NMessageMgr::Insert(const unsigned int in_ID, NInter* in_Obj)
{
	NSyncObject sync(m_CS);

	m_ObjContainer.insert(std::pair<unsigned int,NInter*>(in_ID, in_Obj));
	return true;
}


void NMessageMgr::Remove(const unsigned int in_ID, NInter* in_Obj)
{
	NSyncObject sync(m_CS);

	std::map<unsigned int,NInter*>::iterator it = m_ObjContainer.find(in_ID);
	if( it == m_ObjContainer.end() || it->second != in_Obj )
		return;

	m_ObjContainer.erase(it);
}


bool NMessageMgr::Post(const unsigned int in_ID, const unsigned int in_Msg, const unsigned int in_wParam, const unsigned int in_lParam)
{
	NSyncObject sync(m_CS);

	std::map<unsigned int,NInter*>::iterator it = m_ObjContainer.find(in_ID);
	if( it == m_ObjContainer.end() )
		return false;

	it->second->Receive(in_Msg, in_wParam, in_lParam);
	return true;
}
