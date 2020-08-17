#include "CGVar.h"
#include "InterServer.h"


/// singleton instance
CGVar*& CGVar::m_cpSelf = VTOR<CGVar*>(DetourFindFunction(EXEPATH(), "CGVar::m_cpSelf"));


CGVar::CGVar()
: m_bOK(false)
{
	m_bOK = false;

	if( this->CGVar::Create() )
		m_bOK = true;
}


CGVar::~CGVar()
{
	this->CGVar::Destroy();
}


bool CGVar::Create()
{
	m_AsyncDBThreadNum = GetPrivateProfileIntA("ASYNC DATABASE", "work thread num", 10, g_infFile);
	return true;
}


void CGVar::Destroy()
{
}


bool CGVar::CreateInstance()
{
	if( m_cpSelf != NULL )
		return false;

	m_cpSelf = new(std::nothrow) CGVar();
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->CGVar::isOK() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void CGVar::DestroyInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


CGVar* CGVar::GetObj() /// @custom
{
	return m_cpSelf;
}


bool CGVar::isOK() const
{
	return m_bOK;
}


int CGVar::GetAsyncDBThreadNum()
{
	return m_AsyncDBThreadNum;
}


void CGVar::SetGlobalDBPwd(const std::string in_GlobalDBPwd)
{
	m_GlobalDBPwd = in_GlobalDBPwd;
}


void CGVar::SetCharacterDBPwd(const std::string in_CharacterDBPwd)
{
	m_CharacterDBPwd = in_CharacterDBPwd;
}


std::string CGVar::GetGlobalDBPwd()
{
	return m_GlobalDBPwd;
}


std::string CGVar::GetCharacterDBPwd()
{
	return m_CharacterDBPwd;
}
