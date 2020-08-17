#include "shared/NLuaThread.h"


NLuaThread::NLuaThread(NLuaState& in_LuaState)
: m_pLuaThread(NULL), m_bOK(false)
{
	if( this->NLuaThread::Create(in_LuaState) )
		m_bOK = true;
}


NLuaThread::~NLuaThread()
{
	m_pLuaThread = NULL;
}


bool NLuaThread::Create(NLuaState& in_LuaState)
{
	m_pLuaThread = lua_newthread(in_LuaState);
	return ( m_pLuaThread != NULL );
}


bool NLuaThread::isOK() const
{
	return m_bOK;
}


NLuaThread::operator lua_State*()
{
	return m_pLuaThread;
}


lua_State* NLuaThread::GetStatePtr()
{
	return m_pLuaThread;
}
