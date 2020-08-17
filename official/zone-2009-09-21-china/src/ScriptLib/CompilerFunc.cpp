#include "ScriptLib/Compiler.h"


hook_method<bool (CCompiler::*)(CScriptLine& line, int cmd, char* parm)> CCompiler::_OnFunc(SERVER, "CCompiler::OnFunc");
bool CCompiler::OnFunc(CScriptLine& line, int cmd, char* parm) // line 6
{
	return (this->*_OnFunc)(line, cmd, parm);

	//TODO
}
