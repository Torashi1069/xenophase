#include "CInterpretHandler.hpp"
#include "ScriptLib/Interpreter.h"


enum
{
	CODE_END  = 0,
	CODE_MOV  = 1,
	CODE_ADD  = 2,
	CODE_SUB  = 3,
	CODE_MUL  = 4,
	CODE_DIV  = 5,
	CODE_MOD  = 6,
	CODE_INC  = 7,
	CODE_DEC  = 8,
	CODE_CMP  = 9,
	CODE_GOTO = 10,
	CODE_FUNC = 11,
	CODE_CASE = 12,
	CODE_PUSH = 13,
	CODE_POP  = 14,
};


VarMap::VarMap(void) // line 35 (ScriptLib/Interpreter.h)
{
	this->VarMap::Clear();
}


hook_method<void (VarMap::*)(void)> VarMap_Clear(SERVER, "VarMap::Clear");
void VarMap::Clear(void) // line 44-47 (ScriptLib/Interpreter.h)
{
	return (this->*VarMap_Clear)();

	this->data.clear();
	this->data["NULL"] = 0;
}


hook_method<void (VarMap::*)(const char* str, const struct TokenData& t)> VarMap_Set(SERVER, "VarMap::Set");
void VarMap::Set(const char* str, const struct TokenData& t) // line 50-52 (ScriptLib/Interpreter.h)
{
	return (this->*VarMap_Set)(str, t);

	this->data[str] = t;
}


hook_method<bool (VarMap::*)(const char* str, struct TokenData& t)> VarMap_Get(SERVER, "VarMap::Get");
bool VarMap::Get(const char* str, struct TokenData& t) // line 55-60 (ScriptLib/Interpreter.h)
{
	return (this->*VarMap_Get)(str, t);

	mystd::map<mystd::string,TokenData>::iterator it = this->data.find(str);
	if( it == this->data.end() )
		return false; // not found

	t = it->second;
	return true; // found
}


hook_method<bool (CInterpreter::*)(void)> CInterpreter::_Proc(SERVER, "CInterpreter::Proc");
bool CInterpreter::Proc(void) // line 30
{
	return (this->*_Proc)();

	TokenData temp;

	if( m_bin == NULL )
	{
		this->CInterpreter::Error("CInterpreter::Proc 스크립트 없음");
		return false;
	}

	if( m_pos == m_size )
		return false;

	if( m_pos < 0 || m_pos > m_size )
	{
		this->CInterpreter::Error("CInterpreter::Proc %x 는 주소 범위[0~%x]를 벗어난 위치입니다 %d", m_pos, m_size); //FIXME: missing stack arg
		return false;
	}

	int code;
	if( !this->CInterpreter::ReadCode(code) )
	{
		this->CInterpreter::Error("CInterpreter::Proc 코드 읽기 실패 pos%d", m_pos);
		return false;
	}

	switch( code )
	{
	case CODE_FUNC: return this->CodeFunc(temp);
	case CODE_GOTO: return this->CodeGoto();
	case CODE_MOV:  return this->CodeMov();
	case CODE_CMP:  return this->CodeCmp();
	case CODE_ADD:  return this->CodeAdd();
	case CODE_SUB:  return this->CodeSub();
	case CODE_MUL:  return this->CodeMul();
	case CODE_DIV:  return this->CodeDiv();
	case CODE_MOD:  return this->CodeMod();
	case CODE_INC:  return this->CodeInc();
	case CODE_DEC:  return this->CodeDec();
	case CODE_PUSH: return this->CodePush();
	case CODE_POP:  return this->CodePop();
	case CODE_CASE: return this->CodeCase();
	case CODE_END:  return false;
	default:
		this->CInterpreter::Error("CInterpreter::Proc 잘못된 코드 pos%d code[%s]", m_pos, code); //FIXME: wrong token type for 'code'
		return false;
	}
}


hook_method<int (CInterpreter::*)(void)> CInterpreter::_GetCurPos(SERVER, "CInterpreter::GetCurPos");
int CInterpreter::GetCurPos(void) // line 84 (InterpreterGet.cpp)
{
	return (this->*_GetCurPos)();

	//TODO
}


hook_method<bool (CInterpreter::*)(TokenData& ret)> CInterpreter::_CodeFunc(SERVER, "CInterpreter::CodeFunc");
bool CInterpreter::CodeFunc(TokenData& ret)
{
	return (this->*_CodeFunc)(ret);

	unsigned short func;
	if( !this->CInterpreter::GetWord(func) )
	{
		this->CInterpreter::Error("CodeFunc : 함수 코드 읽기 실패");
		return false;
	}

	mystd::deque<TokenData> parm;
	while( 1 )
	{
		unsigned char type;
		if( !this->CInterpreter::GetByte(type) )
		{
			this->CInterpreter::Error("CodeFunc : 함수 파라미터 타입 읽기 실패");
			return false;
		}

		if( type == ';' )
			break; // end of func

		if( !strchr("snfv?", type) )
		{
			this->CInterpreter::Error("CodeFunc: %c 는 사용할 수 있는 자료형이 아닙니다", type);
			return false;
		}

		TokenData data;
		if( !this->CInterpreter::ReadValue(data) )
		{
			this->CInterpreter::Error("CodeFunc: 파라미터값 읽기 실패");
			return false;
		}

		if( type == 'n' )
			data.TokenData::SetType(0);
		else
		if( type == 's' )
			data.TokenData::SetType(1);

		parm.push_back(data);
	}

	return m_handler->OnFunc(func, parm, ret);
}


hook_method<bool (CInterpreter::*)(void)> CInterpreter::_CodeMov(SERVER, "CInterpreter::CodeMov");
bool CInterpreter::CodeMov(void)
{
	return (this->*_CodeMov)();

	//TODO
}


hook_method<bool (CInterpreter::*)(void)> CInterpreter::_CodeAdd(SERVER, "CInterpreter::CodeAdd");
bool CInterpreter::CodeAdd(void)
{
	return (this->*_CodeAdd)();

	//TODO
}


hook_method<bool (CInterpreter::*)(void)> CInterpreter::_CodeSub(SERVER, "CInterpreter::CodeSub");
bool CInterpreter::CodeSub(void)
{
	return (this->*_CodeSub)();

	//TODO
}


hook_method<bool (CInterpreter::*)(void)> CInterpreter::_CodeMul(SERVER, "CInterpreter::CodeMul");
bool CInterpreter::CodeMul(void)
{
	return (this->*_CodeMul)();

	//TODO
}


hook_method<bool (CInterpreter::*)(void)> CInterpreter::_CodeDiv(SERVER, "CInterpreter::CodeDiv");
bool CInterpreter::CodeDiv(void)
{
	return (this->*_CodeDiv)();

	//TODO
}


hook_method<bool (CInterpreter::*)(void)> CInterpreter::_CodeMod(SERVER, "CInterpreter::CodeMod");
bool CInterpreter::CodeMod(void)
{
	return (this->*_CodeMod)();

	//TODO
}


hook_method<bool (CInterpreter::*)(void)> CInterpreter::_CodeInc(SERVER, "CInterpreter::CodeInc");
bool CInterpreter::CodeInc(void)
{
	return (this->*_CodeInc)();

	//TODO
}


hook_method<bool (CInterpreter::*)(void)> CInterpreter::_CodeDec(SERVER, "CInterpreter::CodeDec");
bool CInterpreter::CodeDec(void)
{
	return (this->*_CodeDec)();

	//TODO
}


hook_method<bool (CInterpreter::*)(void)> CInterpreter::_CodeCmp(SERVER, "CInterpreter::CodeCmp");
bool CInterpreter::CodeCmp(void)
{
	return (this->*_CodeCmp)();

	//TODO
}


hook_method<bool (CInterpreter::*)(void)> CInterpreter::_CodeGoto(SERVER, "CInterpreter::CodeGoto");
bool CInterpreter::CodeGoto(void)
{
	return (this->*_CodeGoto)();

	//TODO
}


hook_method<bool (CInterpreter::*)(void)> CInterpreter::_CodePush(SERVER, "CInterpreter::CodePush");
bool CInterpreter::CodePush(void)
{
	return (this->*_CodePush)();

	//TODO
}


hook_method<bool (CInterpreter::*)(void)> CInterpreter::_CodePop(SERVER, "CInterpreter::CodePop");
bool CInterpreter::CodePop(void)
{
	return (this->*_CodePop)();

	//TODO
}


hook_method<bool (CInterpreter::*)(void)> CInterpreter::_CodeCase(SERVER, "CInterpreter::CodeCase");
bool CInterpreter::CodeCase(void)
{
	return (this->*_CodeCase)();

	//TODO
}


hook_method<bool (CInterpreter::*)(int& c)> CInterpreter::_ReadCode(SERVER, "CInterpreter::ReadCode");
bool CInterpreter::ReadCode(int& c)
{
	return (this->*_ReadCode)(c);

	//TODO
}


hook_method<bool (CInterpreter::*)(TokenData& ret)> CInterpreter::_ReadValue(SERVER, "CInterpreter::ReadValue");
bool CInterpreter::ReadValue(TokenData& ret)
{
	return (this->*_ReadValue)(ret);

	//TODO
}


hook_method<void (CInterpreter::*)(char* str, ...)> CInterpreter::_Error(SERVER, "CInterpreter::Error");
void CInterpreter::Error(char* str, ...)
{
//	return (this->*_Error)(str);

	va_list va;
	va_start(va, str);

	if( m_handler != NULL )
	{
		char buf[1024];
		vsprintf(buf, str, va);
		m_handler->OnError(buf);
	}
}


hook_method<bool (CInterpreter::*)(unsigned char& data)> CInterpreter::_GetByte(SERVER, "CInterpreter::GetByte");
bool CInterpreter::GetByte(unsigned char& data)
{
	return (this->*_GetByte)(data);

	//TODO
}


hook_method<bool (CInterpreter::*)(unsigned short& data)> CInterpreter::_GetWord(SERVER, "CInterpreter::GetWord");
bool CInterpreter::GetWord(unsigned short& data)
{
	return (this->*_GetWord)(data);

	//TODO
}
