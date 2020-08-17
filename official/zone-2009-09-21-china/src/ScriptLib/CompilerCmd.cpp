#include "ScriptLib/Compiler.h"


hook_method<bool (CCompiler::*)(CScriptLine& line, int cmd)> CCompiler::_OnControl(SERVER, "CCompiler::OnControl");
bool CCompiler::OnControl(CScriptLine& line, int cmd) // line 391
{
	return (this->*_OnControl)(line, cmd);

	//TODO
}


hook_method<bool (CCompiler::*)(CScriptLine& line, int cmd)> CCompiler::_OnCommand(SERVER, "CCompiler::OnCommand");
bool CCompiler::OnCommand(CScriptLine& line, int cmd) // line 360
{
	return (this->*_OnCommand)(line, cmd);

	//TODO
}
