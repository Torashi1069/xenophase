#include "shared/NLuaState.h"


NLuaState::NLuaState()
: m_pLuaState(NULL)
{
	m_bOK = false;

	if( this->NLuaState::Create() )
		m_bOK = true;
}


NLuaState::~NLuaState()
{
	this->NLuaState::Destroy();
}


bool NLuaState::Create()
{
	m_pLuaState = lua_open();
	return ( m_pLuaState != NULL );
}


void NLuaState::Destroy()
{
	if( m_pLuaState != NULL )
	{
		lua_close(m_pLuaState);
		m_pLuaState = NULL;
	}
}


bool NLuaState::isOK() const
{
	return m_bOK;
}


NLuaState::operator lua_State*()
{
	return m_pLuaState;
}


lua_State* NLuaState::operator()()
{
	return m_pLuaState;
}
