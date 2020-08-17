#pragma once
#include "ScriptLib/Compiler.h"
#include "ScriptDefine.h"


class CScriptCompiler
{
	/* this+0 */ private: CCompiler* m_compiler;

	public: CScriptCompiler::CScriptCompiler(void);
	public: CScriptCompiler::~CScriptCompiler(void);
	public: bool CScriptCompiler::Init(void);
	private: void CScriptCompiler::Reset(void);
	private: bool CScriptCompiler::InitTokenMap(void);
	private: bool CScriptCompiler::InitItemScript(void);
	private: bool CScriptCompiler::InitNpcScript(void);
	private: bool CScriptCompiler::InitSkillScript(void);
	private: bool CScriptCompiler::InitBuffScript(void);
	private: HOOKED bool CScriptCompiler::InitDungenNpcScript(void);
	//private: bool CScriptCompiler::XoR_NpcScript_Verification(void);
	private: bool CScriptCompiler::SetAsm(char* fName);
	private: bool CScriptCompiler::SetBin(char* fName);
	private: bool CScriptCompiler::LoadEnum(const char* fName, int verDate);
	private: bool CScriptCompiler::LoadDef(char* fName);
	private: bool CScriptCompiler::Run(const char* fName, int verDate);
	private: bool CScriptCompiler::LoadV2(void);
	private: bool CScriptCompiler::StdDefine(char* str, int num);
	private: bool CScriptCompiler::StdDeclare(char* func, char* param, int num, bool isBlockCheck);
	private: void CScriptCompiler::Error(const char* str, ...);
	private: void CScriptCompiler::Compelete(void);

private:
	static hook_method<bool (CScriptCompiler::*)(void)> CScriptCompiler::_Init;
	static hook_method<void (CScriptCompiler::*)(void)> CScriptCompiler::_Reset;
	static hook_method<bool (CScriptCompiler::*)(void)> CScriptCompiler::_InitTokenMap;
	static hook_method<bool (CScriptCompiler::*)(void)> CScriptCompiler::_InitItemScript;
	static hook_method<bool (CScriptCompiler::*)(void)> CScriptCompiler::_InitNpcScript;
	static hook_method<bool (CScriptCompiler::*)(void)> CScriptCompiler::_InitSkillScript;
	static hook_method<bool (CScriptCompiler::*)(void)> CScriptCompiler::_InitBuffScript;
	static hook_method<bool (CScriptCompiler::*)(void)> CScriptCompiler::_InitDungenNpcScript;
	static hook_method<bool (CScriptCompiler::*)(char* fName)> CScriptCompiler::_SetAsm;
	static hook_method<bool (CScriptCompiler::*)(char* fName)> CScriptCompiler::_SetBin;
	static hook_method<bool (CScriptCompiler::*)(const char* fName, int verDate)> CScriptCompiler::_LoadEnum;
	static hook_method<bool (CScriptCompiler::*)(char* fName)> CScriptCompiler::_LoadDef;
	static hook_method<bool (CScriptCompiler::*)(const char* fName, int verDate)> CScriptCompiler::_Run;
	static hook_method<bool (CScriptCompiler::*)(void)> CScriptCompiler::_LoadV2;
	static hook_method<bool (CScriptCompiler::*)(char* str, int num)> CScriptCompiler::_StdDefine;
	static hook_method<bool (CScriptCompiler::*)(char* func, char* param, int num, bool isBlockCheck)> CScriptCompiler::_StdDeclare;
	static hook_method<void (CScriptCompiler::*)(const char* str, ...)> CScriptCompiler::_Error;
	static hook_method<void (CScriptCompiler::*)(void)> CScriptCompiler::_Compelete;
};


const char* __cdecl GetScriptFileName(SCRIPT_FILE_TYPE file);
