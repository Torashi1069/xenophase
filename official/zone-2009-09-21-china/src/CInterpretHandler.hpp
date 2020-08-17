#pragma once
#include "struct.hpp"
#include "std/deque"
#include "ScriptLib/Interpreter.h"


class CInterpretHandler
{
	struct vtable_t
	{
		bool (CInterpretHandler::* OnFunc)(int func, mystd::deque<TokenData>& parm, TokenData& ret); //__purecall
		void (CInterpretHandler::* OnError)(const char* str); //__purecall
	};

	/* this+0 */ public: // const CInterpretHandler::`vftable';
	/* this+4 */ protected: VarMap* m_varMap;

	public: CInterpretHandler::CInterpretHandler(void);
	public: CInterpretHandler::~CInterpretHandler(void);
	public: void CInterpretHandler::SetVarMap(VarMap* varMap);
	public: virtual bool CInterpretHandler::OnFunc(int func, mystd::deque<TokenData>& parm, TokenData& ret) = 0;
	public: virtual void CInterpretHandler::OnError(const char* str) = 0;

private:
	static hook_method<void (CInterpretHandler::*)(VarMap* varMap)> CInterpretHandler::_SetVarMap;
};
