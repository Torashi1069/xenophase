#include "ScriptLib/Compiler.h"


/// @patch initialize CCompiler members - r2543
hook_method<CCompiler* (CCompiler::*)(void)> CCompiler::_CCompiler(SERVER, "CCompiler::CCompiler");
CCompiler::CCompiler(void) // line 179
{
	m_script.CScript::RegisterHandler(this);
	m_globalErrorFunc = NULL;
	this->CCompiler::SetCmd(CMD_BLOCKBREAK, "__block");
	this->CCompiler::SetCmd(CMD_END, "end");
	this->CCompiler::SetCmd(CMD_VAR, "var");
	this->CCompiler::SetCmd(CMD_IF, "if");
	this->CCompiler::SetCmd(CMD_ELSEIF, "elseif");
	this->CCompiler::SetCmd(CMD_ELSE, "else");
	this->CCompiler::SetCmd(CMD_ENDIF, "endif");
	this->CCompiler::SetCmd(CMD_DECLARE, "declare");
	this->CCompiler::SetCmd(CMD_DEFINE, "define");
	this->CCompiler::SetCmd(CMD_SWITCH, "choose");
	this->CCompiler::SetCmd(CMD_CASE, "case");
	this->CCompiler::SetCmd(CMD_BREAK, "break");
	this->CCompiler::SetCmd(CMD_DEFAULT, "default");
	this->CCompiler::SetCmd(CMD_ENDSWITCH, "endchoose");
	this->CCompiler::SetCmd(CMD_DEFCMD, "defcmd");
	this->CCompiler::SetCmd(CMD_WHILE, "while");
	this->CCompiler::SetCmd(CMD_ENDWHILE, "endwhile");
	this->CCompiler::SetCmd(CMD_EXITWHILE, "exitwhile");

	m_isError = false;
	m_nSwitch = 0;
	m_isCase = false;
	m_nIf = 0;
	memset(m_nSwitchInIf, 0, sizeof(m_nSwitchInIf));
	m_whileBlock = 0;
	m_nCmd = 0;
	memset(m_fileName, 0, sizeof(m_fileName));
}


/// @patch initialize CCompiler members - r2543
/// @custom
HOOKED CCompiler* CCompiler::CCompilerCtorHookHelper(void)
{
	(this->*_CCompiler)();

	m_isError = false;
	m_nSwitch = 0;
	m_isCase = false;
	m_nIf = 0;
	memset(m_nSwitchInIf, 0, sizeof(m_nSwitchInIf));
	m_whileBlock = 0;
	m_nCmd = 0;
	memset(m_fileName, 0, sizeof(m_fileName));

	return this;
}


hook_method<void (CCompiler::*)(void)> CCompiler::__CCompiler(SERVER, "CCompiler::~CCompiler");
CCompiler::~CCompiler(void) // line 206
{
}


hook_method<bool (CCompiler::*)(char* fName)> CCompiler::_LoadDef(SERVER, "CCompiler::LoadDef");
bool CCompiler::LoadDef(char* fName)
{
	return (this->*_LoadDef)(fName);

	FILE* fp = fopen(fName, "r");
	if( fp == NULL )
		return false;

	char line[1024];
	while( fgets(line, 256, fp) )
	{
		char num[1024], name[1024];
		sscanf(line, "%s %s", name, num);
		m_tokenMap->CTokenMap::Set(name, 4, 1, num);
	}

	fclose(fp);
	return true;
}


hook_method<bool (CCompiler::*)(const char* fName, int verDate)> CCompiler::_Run(SERVER, "CCompiler::Run");
bool CCompiler::Run(const char* fName, int verDate)
{
	return (this->*_Run)(fName, verDate);

	//TODO
}


hook_method<void (CCompiler::*)(void)> CCompiler::_Optimize(SERVER, "CCompiler::Optimize");
void CCompiler::Optimize(void) // line 27
{
	return (this->*_Optimize)();

	this->CCompiler::WriteCode(0);
	m_asm.CAsm::Put("\n\n\n");
	m_asm.CAsm::Comment("optimize");
	m_asm.CAsm::Comment("===================================================================");

	for( size_t i = 0; i < m_gotoInfo.size(); ++i )
	{
		int addr;
		m_bin.CBin::Seek(m_gotoInfo[i].pos);
		m_block.CBlock::GetInfo(m_gotoInfo[i].id, addr);
		m_asm.CAsm::Commentf("optimize: move %x - block %d -> addr hex %x:dec ", m_gotoInfo[i].pos, m_gotoInfo[i].id, addr);
		this->CCompiler::WriteNum(addr);
	}
}


hook_method<void (CCompiler::*)(int cmd, char* str)> CCompiler::_SetCmd(SERVER, "CCompiler::SetCmd");
void CCompiler::SetCmd(int cmd, char* str) // line 153
{
	return (this->*_SetCmd)(cmd, str);

	m_tokenMap->CTokenMap::Set(str, 1, cmd, "");
}


hook_method<void (CCompiler::*)(void)> CCompiler::_Release(SERVER, "CCompiler::Release");
void CCompiler::Release(void) // line 167
{
	return (this->*_Release)();

	m_asm.CAsm::Release();
	m_bin.CBin::Release();
	m_gotoInfo.clear();
}


hook_method<void (CCompiler::*)(CCompiler::fnErrorFunc* func)> CCompiler::_SetGlobalErrorFunc(SERVER, "CCompiler::SetGlobalErrorFunc");
void CCompiler::SetGlobalErrorFunc(CCompiler::fnErrorFunc* func) // line 175
{
	return (this->*_SetGlobalErrorFunc)(func);

	m_globalErrorFunc = func;
}


hook_method<void (CCompiler::*)(char* str, ...)> CCompiler::_Error(SERVER, "CCompiler::Error");
void CCompiler::Error(char* str, ...) // line 6
{
//	return (this->*_Error)(str, ...);

	va_list va;
	va_start(va, str);

	m_isError = true;

	char buf[1024];
	vsprintf(buf, str, va);
	m_asm.CAsm::Error(buf);

	if( m_globalErrorFunc != NULL )
	{
		char temp[256];
		memset(temp, 0, sizeof(temp));
		sprintf(temp, "%s, %s", m_fileName, buf);
		m_globalErrorFunc(temp);
	}
}
