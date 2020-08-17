#pragma once
extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h> 
}


class NLuaState
{
private:
	/* this+0 */ //const NLuaState::`vftable';
	/* this+4 */ lua_State* m_pLuaState;
	/* this+8 */ bool m_bOK;

private:
	bool Create();
	void Destroy();

public:
	bool isOK() const;
	operator lua_State*();
	lua_State* operator()();

public:
	NLuaState();
	virtual ~NLuaState();
};


namespace {
std::string MakeFormatString(const char* in_pFmt, ...)
{
	va_list va;
	va_start(va, in_pFmt);

	char Buffer[2048+1] = {};
	_vsnprintf(Buffer, countof(Buffer), in_pFmt, va);

	return Buffer;
}
}; // namespace
