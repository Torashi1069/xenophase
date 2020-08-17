#include "MapTypePropertyMgr.h"


/// singleton instance
CMapTypePropertyMgr*& CMapTypePropertyMgr::m_cpSelf = VTOR<CMapTypePropertyMgr*>(DetourFindFunction(EXEPATH(), "CMapTypePropertyMgr::m_cpSelf"));
const std::string& CMapTypePropertyMgr::m_MapTypePropertyFileName = VTOR<const std::string>(DetourFindFunction(EXEPATH(), "CMapTypePropertyMgr::m_MapTypePropertyFileName")); // = "MapTypeProperty.txt";


CMapTypePropertyMgr::CMapTypePropertyMgr()
: m_DefaultProperty(-1)
{
	m_bOK = false;

	if( this->CMapTypePropertyMgr::Create() )
		m_bOK = true;
}


CMapTypePropertyMgr::~CMapTypePropertyMgr()
{
	this->CMapTypePropertyMgr::Destroy();
}


bool CMapTypePropertyMgr::Create()
{
	return this->CMapTypePropertyMgr::Anaysis(m_MapTypePropertyFileName);
}


void CMapTypePropertyMgr::Destroy()
{
}


bool CMapTypePropertyMgr::CreateInstance()
{
	if( m_cpSelf != NULL )
		return false;

	m_cpSelf = new(std::nothrow) CMapTypePropertyMgr();
	if( m_cpSelf == NULL )
		return false;
	
	if( !m_cpSelf->CMapTypePropertyMgr::isOK() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void CMapTypePropertyMgr::DestroyInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


CMapTypePropertyMgr* CMapTypePropertyMgr::GetObj() /// @custom
{
	return m_cpSelf;
}


bool CMapTypePropertyMgr::isOK() const
{
	return m_bOK;
}


hook_func<bool (__stdcall *)(CMapTypePropertyMgr* self, const std::string in_strFileName)> CMapTypePropertyMgr__Anaysis(EXEPATH(), "CMapTypePropertyMgr::Anaysis");
bool CMapTypePropertyMgr::Anaysis(const std::string in_strFileName)
{
	return (CMapTypePropertyMgr__Anaysis)(this, in_strFileName);
	//TODO
}


CMapTypeProperty& CMapTypePropertyMgr::GetProperty(const int in_MapType)
{
	MAPTYPEPROPERTY_CONTAINER_ITER iter = m_MapTypePropertyContainer.find(in_MapType);
	if( iter == m_MapTypePropertyContainer.end() )
		return m_DefaultProperty;

	return iter->second;
}
