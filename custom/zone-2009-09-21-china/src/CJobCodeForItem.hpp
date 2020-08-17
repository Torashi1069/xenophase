#pragma once
#include "ScriptLib/Interpreter.h"
#include "CInterpretHandler.hpp"
#include "std/map"
#include "std/set"


class CJobCodeForItem : public CInterpretHandler
{
public:
	/* this+0x0  */ //CInterpretHandler
	/* this+0x8  */ CInterpreter m_interpreter;
	/* this+0x4C */ mystd::map<int,mystd::set<short> > m_map;
	/* this+0x58 */ mystd::map<int,mystd::set<short> > m_jobGroup;
	/* this+0x64 */ unsigned long m_allJobsCode;
	/* this+0x68 */ unsigned long m_allJobsCodeWithoutNovice;

	enum
	{
		NOVICE_GR   = 0x0,
		SWORDMAN_GR = 0x1,
		MERCHANT_GR = 0x2,
		MAGICIAN_GR = 0x3,
		ARCHER_GR   = 0x4,
		ACOLYTE_GR  = 0x5,
		THIEF_GR    = 0x6,
		TAEKWON_GR  = 0x7,
	};

	enum
	{
		FUNC_SET       = 0x0,
		FUNC_SetJC_EXN = 0x1,
		FUNC_SetJC_ALL = 0x2,
		FUNC_SetGroup  = 0x3,
		FUNC_SET2      = 0x4,
	};

	//public: void CJobCodeForItem::CJobCodeForItem(void);
	//public: void CJobCodeForItem::~CJobCodeForItem(void);
	public: bool CJobCodeForItem::Init(void);
	public: bool CJobCodeForItem::IsJobForEquip(short job, unsigned long jobCode);
	public: bool CJobCodeForItem::IsJobForArrow(short job);
	public: bool CJobCodeForItem::OnFunc(int func, mystd::deque<TokenData>& parm, TokenData& ret);
	public: void CJobCodeForItem::OnError(const char* str);
	protected: bool CJobCodeForItem::Compile(void);
	protected: bool CJobCodeForItem::FuncSet(mystd::deque<TokenData>& parm);
	protected: bool CJobCodeForItem::FuncSetJC_EXN(mystd::deque<TokenData>& parm);
	protected: bool CJobCodeForItem::FuncSetJC_ALL(mystd::deque<TokenData>& parm);
	protected: bool CJobCodeForItem::FuncSetGroup(mystd::deque<TokenData>& parm);
	protected: bool CJobCodeForItem::FuncSet2(mystd::deque<TokenData>& parm);
private:
	static hook_method<bool (CJobCodeForItem::*)(void)> CJobCodeForItem::_Init;
	static hook_method<bool (CJobCodeForItem::*)(short job, unsigned long jobCode)> CJobCodeForItem::_IsJobForEquip;
	static hook_method<bool (CJobCodeForItem::*)(short job)> CJobCodeForItem::_IsJobForArrow;
	static hook_method<bool (CJobCodeForItem::*)(int func, mystd::deque<TokenData>& parm, TokenData& ret)> CJobCodeForItem::_OnFunc;
	static hook_method<void (CJobCodeForItem::*)(const char* str)> CJobCodeForItem::_OnError;
	static hook_method<bool (CJobCodeForItem::*)(void)> CJobCodeForItem::_Compile;
	static hook_method<bool (CJobCodeForItem::*)(mystd::deque<TokenData>& parm)> CJobCodeForItem::_FuncSet;
	static hook_method<bool (CJobCodeForItem::*)(mystd::deque<TokenData>& parm)> CJobCodeForItem::_FuncSetJC_EXN;
	static hook_method<bool (CJobCodeForItem::*)(mystd::deque<TokenData>& parm)> CJobCodeForItem::_FuncSetJC_ALL;
	static hook_method<bool (CJobCodeForItem::*)(mystd::deque<TokenData>& parm)> CJobCodeForItem::_FuncSetGroup;
	static hook_method<bool (CJobCodeForItem::*)(mystd::deque<TokenData>& parm)> CJobCodeForItem::_FuncSet2;
};
