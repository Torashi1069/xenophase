#pragma once
#include "shared/NLuaState.h"


class NLuaThread
{
public:
	bool isOK() const;
	operator lua_State*();
	lua_State* GetStatePtr();

public:
	NLuaThread(NLuaState& in_LuaState);
	virtual ~NLuaThread();

private:
	/* this+0 */ //const NLuaThread::`vftable';
	/* this+4 */ lua_State* m_pLuaThread;
	/* this+8 */ bool m_bOK;

private:
	bool Create(NLuaState& in_LuaState);
};
