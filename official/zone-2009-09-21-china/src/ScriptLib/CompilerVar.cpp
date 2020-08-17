#include "ScriptLib/Compiler.h"


hook_method<bool (CCompiler::*)(CScriptLine& line, char* name)> CCompiler::_OnVar(SERVER, "CCompiler::OnVar");
bool CCompiler::OnVar(CScriptLine& line, char* name) // line 78
{
	return (this->*_OnVar)(line, name);

	//TODO
}
