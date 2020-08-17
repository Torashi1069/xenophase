#include "ScriptLib/Script.h"


CScriptLine::CScriptLine(char* line) // line 193
{
	m_line = line;
	m_cur = line;
}


CScriptLine::~CScriptLine(void) // line ???
{
}


hook_method<void (CScript::*)(CScriptHandler* handler)> CScript::_RegisterHandler(SERVER, "CScript::RegisterHandler");
void CScript::RegisterHandler(CScriptHandler* handler) // line 412
{
	return (this->*_RegisterHandler)(handler);

	//TODO
}
