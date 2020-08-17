#pragma once
#include "ScriptLib/Asm.h"
#include "ScriptLib/Bin.h"
#include "ScriptLib/Block.h"
#include "ScriptLib/Script.h"
#include "std/map"
#include "std/stack"
#include "std/vector"


class CCompiler : public CScriptHandler
{
	struct vtable_t // const CCompiler::`vftable'
	{
		bool CCompiler::OnControl(CScriptLine& line, int cmd);
		bool CCompiler::OnCommand(CScriptLine& line, int cmd);
		bool CCompiler::OnFunc(CScriptLine& line, int cmd, char* parm);
		bool CCompiler::OnVar(CScriptLine& line, char* name);
		void CCompiler::Error(char* str, ...);
	};

public:
	struct GotoInfo
	{
		/* this+0 */ int pos;
		/* this+4 */ int id;
	};

	typedef void (__cdecl fnErrorFunc)(const char *);

	/* this+  0 */ public: //CScriptHandler baseclass_0;
	/* this+  8 */ private: bool m_isError;
	/* this+ 12 */ private: int m_nSwitch;
	/* this+ 16 */ private: bool m_isCase;
	/* this+ 20 */ private: CBlock m_block;
	/* this+112 */ private: CScript m_script;
	/* this+172 */ private: CAsm m_asm;
	/* this+180 */ private: CBin m_bin;
	/* this+184 */ private: mystd::vector<CCompiler::GotoInfo> m_gotoInfo;
	/* this+200 */ private: mystd::deque<int> m_label;
	/* this+232 */ private: mystd::map<int,bool> m_blockCheckMap;
	/* this+244 */ private: mystd::stack<int> m_whileStack;
	/* this+276 */ private: int m_nIf;
	/* this+280 */ private: int m_nSwitchInIf[30];
	/* this+400 */ private: int m_whileBlock;
	/* this+404 */ private: int m_nCmd;
	/* this+408 */ private: fnErrorFunc* m_globalErrorFunc;
	/* this+412 */ private: char m_fileName[256];

public:
	enum
	{
		CMD_END        = 0,
		CMD_VAR        = 1,
		CMD_IF         = 2,
		CMD_ELSEIF     = 3,
		CMD_ELSE       = 4,
		CMD_ENDIF      = 5,
		CMD_DECLARE    = 6,
		CMD_DEFINE     = 7,
		CMD_SWITCH     = 8,
		CMD_CASE       = 9,
		CMD_BREAK      = 10,
		CMD_DEFAULT    = 11,
		CMD_ENDSWITCH  = 12,
		CMD_DEFCMD     = 13,
		CMD_BLOCKBREAK = 14,
		CMD_WHILE      = 15,
		CMD_ENDWHILE   = 16,
		CMD_EXITWHILE  = 17,
	};

	public: CCompiler::CCompiler(void);
	public: CCompiler::~CCompiler(void);
	//public: bool CCompiler::LoadEnum(const char *, int);
	public: bool CCompiler::LoadDef(char* fName);
	//public: bool CCompiler::SetBin(char *);
	//public: bool CCompiler::SetAsm(char *);
	public: bool CCompiler::Run(const char* fName, int verDate);
	public: void CCompiler::Optimize(void);
	public: void CCompiler::SetCmd(int cmd, char* str);
	public: void CCompiler::Release(void);
	public: void CCompiler::SetGlobalErrorFunc(CCompiler::fnErrorFunc* func);
	public: virtual bool CCompiler::OnControl(CScriptLine& line, int cmd);
	public: virtual bool CCompiler::OnCommand(CScriptLine& line, int cmd);
	public: virtual bool CCompiler::OnFunc(CScriptLine& line, int cmd, char* parm);
	public: virtual bool CCompiler::OnVar(CScriptLine& line, char* name);
	//private: bool CCompiler::CmdBlockBreak(class CScriptLine &);
	//private: bool CCompiler::CmdVar(class CScriptLine &);
	//private: bool CCompiler::CmdIf(class CScriptLine &);
	//private: bool CCompiler::CmdElseIf(class CScriptLine &);
	//private: bool CCompiler::CmdElse(class CScriptLine &);
	//private: bool CCompiler::CmdEndIf(class CScriptLine &);
	//private: bool CCompiler::CmdEnd(class CScriptLine &);
	//private: bool CCompiler::CmdDeclare(class CScriptLine &);
	//private: bool CCompiler::CmdDefine(class CScriptLine &);
	//private: bool CCompiler::CmdSwitch(class CScriptLine &);
	//private: bool CCompiler::CmdCase(class CScriptLine &);
	//private: bool CCompiler::CmdBreak(class CScriptLine &);
	//private: bool CCompiler::CmdDefault(class CScriptLine &);
	//private: bool CCompiler::CmdEndSwitch(class CScriptLine &);
	//private: bool CCompiler::CmdDefCmd(class CScriptLine &);
	//private: bool CCompiler::CmdWhile(class CScriptLine &);
	//private: bool CCompiler::CmdEndWhile(class CScriptLine &);
	//private: bool CCompiler::CmdExitWhile(class CScriptLine &);
	//private: void CCompiler::WriteGotoBlock(int);
	private: void CCompiler::WriteCode(int code);
	//private: void CCompiler::WriteFunc(int);
	//private: void CCompiler::WriteCall(char *);
	//private: void CCompiler::WriteType(char);
	//private: void CCompiler::WriteVar(char *);
	private: void CCompiler::WriteNum(int n);
	//private: void CCompiler::WriteStr(char *);
	//private: bool CCompiler::WriteOp(char *);
	//private: bool CCompiler::GetDefVar(class CScriptLine &, char *, int &);
	//private: bool CCompiler::Value(class CScriptLine &, bool);
	//private: bool CCompiler::IsNum(char *);
	//private: void CCompiler::Goto(int);
	private: virtual void CCompiler::Error(char* str, ...);
	//private: bool CCompiler::CheckSwitchBlock();

private:
	static hook_method<CCompiler* (CCompiler::*)(void)> CCompiler::_CCompiler;
	static hook_method<void (CCompiler::*)(void)> CCompiler::__CCompiler;
	static hook_method<void (CCompiler::*)(fnErrorFunc* func)> CCompiler::_SetGlobalErrorFunc;
	static hook_method<bool (CCompiler::*)(char* fName)> CCompiler::_LoadDef;
	static hook_method<bool (CCompiler::*)(const char* fName, int verDate)> CCompiler::_Run;
	static hook_method<void (CCompiler::*)(void)> CCompiler::_Optimize;
	static hook_method<void (CCompiler::*)(int cmd, char* str)> CCompiler::_SetCmd;
	static hook_method<void (CCompiler::*)(void)> CCompiler::_Release;
	static hook_method<bool (CCompiler::*)(CScriptLine& line, int cmd)> CCompiler::_OnControl;
	static hook_method<bool (CCompiler::*)(CScriptLine& line, int cmd)> CCompiler::_OnCommand;
	static hook_method<bool (CCompiler::*)(CScriptLine& line, int cmd, char* parm)> CCompiler::_OnFunc;
	static hook_method<bool (CCompiler::*)(CScriptLine& line, char* name)> CCompiler::_OnVar;
	static hook_method<void (CCompiler::*)(int code)> CCompiler::_WriteCode;
	static hook_method<void (CCompiler::*)(int n)> CCompiler::_WriteNum;
	static hook_method<void (CCompiler::*)(char* str, ...)> CCompiler::_Error;
};


C_ASSERT( sizeof CCompiler == 668 );
