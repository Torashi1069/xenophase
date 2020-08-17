#pragma once
//#include <lua.h>
typedef struct lua_State lua_State;


class CLua
{
public:
	CLua();
	~CLua();

public:
	void Init();
	void Destroy();
	void RegisterFuncs();
	void ErrorMsg(const char* caption, const char* fmt, ...);
	bool Load(const char* filename);
	bool Execute(mystd::string funcname, const char* argfmt, ...);

private:
	lua_State* m_LuaState;
};
