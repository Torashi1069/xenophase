#include "ScriptLib/Compiler.h"


hook_method<void (CCompiler::*)(int code)> CCompiler::_WriteCode(SERVER, "CCompiler::WriteCode");
void CCompiler::WriteCode(int code) // line 23
{
	return (this->*_WriteCode)(code);

	//TODO
}


hook_method<void (CCompiler::*)(int n)> CCompiler::_WriteNum(SERVER, "CCompiler::WriteNum");
void CCompiler::WriteNum(int n) // line 55
{
	return (this->*_WriteNum)(n);

	//TODO
}
