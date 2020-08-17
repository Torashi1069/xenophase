#include "ScriptLib/Interpreter.h"


enum enumCODETYPE
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


enum enumOPTYPE
{
	OP_END            = 0,
	OP_EQUAL          = 1,
	OP_NOTEQUAL       = 2,
	OP_LARGE          = 3,
	OP_SMALL          = 4,
	OP_AND            = 5,
	OP_OR             = 6,
	OP_ADD            = 7,
	OP_SUB            = 8,
	OP_MUL            = 9,
	OP_DIV            = 10,
	OP_MOD            = 11,
	OP_LARGE_OR_EQUAL = 12,
	OP_SMALL_OR_EQUAL = 13,
};


////////////////////////////////////////


void CInterpretHandler::SetVarMap(VarMap* varMap)
{
	m_varMap = varMap;
}


CInterpretHandler::CInterpretHandler()
{
}


CInterpretHandler::~CInterpretHandler()
{
}


////////////////////////////////////////


void CInterpreter::SetVar(const char* var, int value) // 23-27
{
	TokenData data;
	data.TokenData::Set(value);
	m_varMap.VarMap::Set(var, data);
}


bool CInterpreter::Proc() // 30-70
{
	if( m_bin == NULL )
	{
		this->CInterpreter::Error("CInterpreter::Proc 스크립트 없음");
		return false;
	}

	if( m_pos == m_size )
		return false;

	if( m_pos < 0 || m_pos > m_size )
	{
		this->CInterpreter::Error("CInterpreter::Proc %x 는 주소 범위[0~%x]를 벗어난 위치입니다 %d", m_pos, m_size);
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
	case CODE_FUNC:
	{
		TokenData temp;
		if( !this->CodeFunc(temp) )
			return false;
	}
	break;
	case CODE_GOTO:
	{
		if( !this->CodeGoto() )
			return false;
	}
	break;
	case CODE_MOV:
	{
		if( !this->CodeMov() )
			return false;
	}
	break;
	case CODE_CMP:
	{
		if( !this->CodeCmp() )
			return false;
	}
	break;
	case CODE_ADD:
	{
		if( !this->CodeAdd() )
			return false;
	}
	break;
	case CODE_SUB:
	{
		if( !this->CodeSub() )
			return false;
	}
	break;
	case CODE_MUL:
	{
		if( !this->CodeMul() )
			return false;
	}
	break;
	case CODE_DIV:
	{
		if( !this->CodeDiv() )
			return false;
	}
	break;
	case CODE_MOD:
	{
		if( !this->CodeMod() )
			return false;
	}
	break;
	case CODE_INC:
	{
		if( !this->CodeInc() )
			return false;
	}
	break;
	case CODE_DEC:
	{
		if( !this->CodeDec() )
			return false;
	}
	break;
	case CODE_PUSH:
	{
		if( !this->CodePush() )
			return false;
	}
	break;
	case CODE_POP:
	{
		if( !this->CodePop() )
			return false;
	}
	break;
	case CODE_CASE:
	{
		if( !this->CodeCase() )
			return false;
	}
	break;
	case CODE_END:
	{
		return false;
	}
	break;
	default:
	{
		this->CInterpreter::Error("CInterpreter::Proc 잘못된 코드 pos%d code[%s]", m_pos, code);
		return false;
	}
	break;
	};

	return true;
}


bool CInterpreter::Scan(CBinBuf* binBuf, int pos) // 73-80
{
	if( !this->CInterpreter::Run(binBuf, pos, false) )
		return false;

	m_scan = true;
	while( this->CInterpreter::Proc() )
		;
	m_scan = false;

	return true;
}


bool CInterpreter::Run(CBinBuf* binBuf, int pos, bool gotoLock) // 83-102
{
	m_scan = false;
	m_gotoLock = gotoLock;

	if( binBuf == NULL )
	{
		this->CInterpreter::Error("CInterpreter::Run 스크립트 없음");
		return false;
	}

	m_bin = binBuf->CBinBuf::GetBase();
	m_size = binBuf->CBinBuf::GetSize();
	m_pos = pos;

	if( m_pos < 0 || m_pos >= m_size )
	{
		this->CInterpreter::Error("CInterpreter::Run %d는 주소 범위[0~%d]를 벗어난 위치입니다", m_pos, m_size);
		return false;
	}

	m_varMap.VarMap::Clear();

	return true;
}


void CInterpreter::RegisterHandler(CInterpretHandler* handler) // 105-107 (105-107)
{
	m_handler = handler;
	handler->CInterpretHandler::SetVarMap(&m_varMap);
}


void CInterpreter::Error(char* str, ...) // 111-121 (111-121)
{
	if( m_handler == NULL )
		return;

	va_list va;
	va_start(va, str);

	char buf[1024];
	vsprintf(buf, str, va);

	m_handler->OnError(buf);
}


void CInterpreter::Clear() // 124-134 (124-133)
{
	m_scan = 0;
	m_gotoLock = 0;
	m_pos = 0;
	m_size = 0;
	m_handler = 0;
	m_bin = 0;
	m_varMap.VarMap::Clear();
}


CInterpreter::CInterpreter() // 137-139 (137-139)
{
	this->CInterpreter::Clear();
}


CInterpreter::~CInterpreter() // 142-143 (142-143)
{
}


bool CInterpreter::CodeMov() // 7-22 (InterpreterCode.cpp)
{
	char var[1024];
	if( !this->CInterpreter::ReadVar(var, sizeof(var)) )
	{
		this->CInterpreter::Error("CodeMov : 변수 읽기 실패");
		return false;
	}

	TokenData data;
	if( !this->CInterpreter::ReadValue(data) )
	{
		this->CInterpreter::Error("CodeMov : 데이터 읽기 실패");
		return false;
	}

	if( !m_scan )
	{// execute
		m_varMap.data[var] = data;
	}

	return true;
}


bool CInterpreter::CodeAdd() // 26-41 (InterpreterCode.cpp)
{
	char var[1024];
	if( !this->CInterpreter::ReadVar(var, sizeof(var)) )
	{
		this->CInterpreter::Error("CodeAdd : 변수 읽기 실패");
		return false;
	}

	TokenData data;
	if( !this->CInterpreter::ReadValue(data) )
	{
		this->CInterpreter::Error("CodeAdd : 데이터 읽기 실패");
		return false;
	}

	if( !m_scan )
	{// execute
		m_varMap.data[var] = data;
	}

	return true;
}


bool CInterpreter::CodeSub() // 45-60 (InterpreterCode.cpp)
{
	char var[1024];
	if( !this->CInterpreter::ReadVar(var, sizeof(var)) )
	{
		this->CInterpreter::Error("CodeSub : 변수 읽기 실패");
		return false;
	}

	TokenData data;
	if( !this->CInterpreter::ReadValue(data) )
	{
		this->CInterpreter::Error("CodeSub : 데이터 읽기 실패");
		return false;
	}

	if( !m_scan )
	{// execute
		m_varMap.data[var] = data;
	}

	return true;
}


bool CInterpreter::CodeMul() // 64-79 (InterpreterCode.cpp)
{
	char var[1024];
	if( !this->CInterpreter::ReadVar(var, sizeof(var)) )
	{
		this->CInterpreter::Error("CodeMul : 변수 읽기 실패");
		return false;
	}

	TokenData data;
	if( !this->CInterpreter::ReadValue(data) )
	{
		this->CInterpreter::Error("CodeMul : 데이터 읽기 실패");
		return false;
	}

	if( !m_scan )
	{// execute
		m_varMap.data[var] = data;
	}

	return true;
}


bool CInterpreter::CodeMod() // 83-98 (InterpreterCode.cpp)
{
	char var[1024];
	if( !this->CInterpreter::ReadVar(var, sizeof(var)) )
	{
		this->CInterpreter::Error("CodeMod : 변수 읽기 실패");
		return false;
	}

	TokenData data;
	if( !this->CInterpreter::ReadValue(data) )
	{
		this->CInterpreter::Error("CodeMod : 데이터 읽기 실패");
		return false;
	}

	if( !m_scan )
	{// execute
		m_varMap.data[var] = data;
	}

	return true;
}


bool CInterpreter::CodeDiv() // 102-116 (InterpreterCode.cpp)
{
	char var[1024];
	if( !this->CInterpreter::ReadVar(var, sizeof(var)) )
	{
		this->CInterpreter::Error("CodeDiv : 변수 읽기 실패");
		return false;
	}

	TokenData data;
	if( !this->CInterpreter::ReadValue(data) )
	{
		this->CInterpreter::Error("CodeDiv : 데이터 읽기 실패");
		return false;
	}

	if( !m_scan )
	{// execute
		m_varMap.data[var] = data;
	}

	return true;
}


bool CInterpreter::CodeInc() // 120-130 (InterpreterCode.cpp)
{
	char var[1024];
	if( !this->CInterpreter::ReadVar(var, sizeof(var)) )
	{
		this->CInterpreter::Error("CodeInc : 변수 읽기 실패");
		return false;
	}

	if( !m_scan )
	{// execute
		m_varMap.data[var].TokenData::operator++(0);
	}

	return true;
}


bool CInterpreter::CodeDec() // 133-143 (InterpreterCode.cpp)
{
	char var[1024];
	if( !this->CInterpreter::ReadVar(var, sizeof(var)) )
	{
		this->CInterpreter::Error("CodeDec : 변수 읽기 실패");
		return false;
	}

	if( !m_scan )
	{// execute
		m_varMap.data[var].TokenData::operator--(0);
	}

	return true;
}


bool CInterpreter::CodeCmp() // 146-165 (InterpreterCode.cpp)
{
	TokenData data;
	if( !this->CInterpreter::ReadValue(data) )
	{
		this->CInterpreter::Error("CodeCmp : 값 읽기 실패");
		return false;
	}

	int addr;
	if( !this->CInterpreter::ReadNum(addr) )
	{
		this->CInterpreter::Error("CodeCmp : not goto 주소 읽기 실패");
		return false;
	}

	if( !m_scan )
	{// execute
		if( data.TokenData::GetNum() == 0 && !this->CInterpreter::Goto(addr) )
		{
			this->CInterpreter::Error("CodeCmp : goto addr: hex[%x] dec[%d] 실패", addr, addr);
			return false;
		}
	}

	return true;
}


bool CInterpreter::CodePush() // 169-181 (InterpreterCode.cpp)
{
	char var[1024];
	if( !this->CInterpreter::ReadVar(var, sizeof(var)) )
	{
		this->CInterpreter::Error("CodePop : 변수 읽기 실패"); //FIXME: copy-paste
		return false;
	}

	if( !m_scan )
	{// execute
		TokenData data;
		if( !m_varMap.VarMap::Get(var, data) )
			data.TokenData::operator=(0);

		m_tokenDataStack.push(data);
	}

	return true;
}


bool CInterpreter::CodePop() // 184-198 (InterpreterCode.cpp)
{
	char var[1024];
	if( !this->CInterpreter::ReadVar(var, sizeof(var)) )
	{
		this->CInterpreter::Error("CodePop : 변수 읽기 실패");
		return false;
	}

	if( !m_scan )
	{// execute		
		if( m_tokenDataStack.size() == 0 )
			return false;

		m_varMap.VarMap::Set(var, m_tokenDataStack.top());
		m_tokenDataStack.pop();
	}

	return true;
}


bool CInterpreter::CodeCase() // 201-220 (InterpreterCode.cpp)
{
	TokenData data;
	if( !this->CInterpreter::ReadValue(data) )
	{
		this->CInterpreter::Error("CodeCase : 값 읽기 실패");
		return false;
	}

	int addr;
	if( this->CInterpreter::ReadNum(addr) )
	{
		this->CInterpreter::Error("CodeCmp : not goto 주소 읽기 실패"); //FIXME: copy-paste
		return false;
	}

	if( !m_scan )
	{// execute
		if( m_varMap.data["$case"] != data && !this->CInterpreter::Goto(addr) )
		{
			this->CInterpreter::Error("CodeCase : goto addr: hex[%x] dec[%d] 실패", addr, addr);
			return false;
		}
	}

	return true;
}


bool CInterpreter::CodeGoto() // 224-237 (InterpreterCode.cpp)
{
	int addr = 0;
	if( !this->CInterpreter::ReadNum(addr) )
	{
		this->CInterpreter::Error("CodeGoto : 주소 읽기 실패");
		return false;
	}

	if( !m_scan )
	{// execute	
		if( !this->CInterpreter::Goto(addr) )
		{
			this->CInterpreter::Error("CodeGoto : goto addr: hex[%x] dec[%d] 실패", addr, addr);
			return false;
		}
	}

	return true;
}


bool CInterpreter::Goto(int pos) // 240-252 (InterpreterCode.cpp)
{
	if( m_gotoLock )
		return true;

	if( pos < 0 || pos > m_size )
	{
		this->CInterpreter::Error("Goto : 범위를 벗어났습니다 %d", pos);
		return false;
	}

	m_pos = pos;
	return true;
}


bool CInterpreter::CodeFunc(TokenData& ret) // 255-294 (InterpreterCode.cpp)
{
	WORD func;
	if( !this->CInterpreter::GetWord(func) )
	{
		this->CInterpreter::Error("CodeFunc : 함수 코드 읽기 실패");
		return false;
	}

	std::deque<TokenData> parm;

	while( 1 )
	{
		BYTE type;
		if( !this->CInterpreter::GetByte(type) )
		{
			this->CInterpreter::Error("CodeFunc : 함수 파라미터 타입 읽기 실패");
			return false;
		}

		if( type == ';' )
		{
			return m_handler->OnFunc(func, parm, ret);
		}

		if( strchr("snfv?", type) == NULL )
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
			data.TokenData::SetType(TokenData::NUM);
		else
		if( type == 's' )
			data.TokenData::SetType(TokenData::STR);

		parm.push_back(data);
	}
}


bool CInterpreter::CheckType(char c) // 11-22 (InterpreterRead.cpp)
{
	BYTE chk;
	if( !this->CInterpreter::GetByte(chk) )
	{
		this->CInterpreter::Error("CheckType: 읽기 에러");
		return false;
	}

	if( c != chk )
	{
		this->CInterpreter::Error("CheckType: 원하는 타입 [%d][%c] != 읽은 타입 [%d][%c]", c, c, chk, chk);
		return false;
	}

	return true;
}


bool CInterpreter::ReadCode(int& c) // 25-38 (InterpreterRead.cpp)
{
	if( !this->CInterpreter::CheckType('c') )
	{
		this->CInterpreter::Error("ReadCode: 타입 에러");
		return false;
	}

	BYTE code;
	if( !this->CInterpreter::GetByte(code) )
	{
		this->CInterpreter::Error("ReadCode: 코드 읽기 실패");
		return false;
	}

	c = code;
	return true;
}


bool CInterpreter::ReadNum(int& num) // 41-51 (InterpreterRead.cpp)
{
	if( !this->CInterpreter::CheckType('n') )
	{
		this->CInterpreter::Error("ReadNum: 타입에러");
		return false;
	}

	if( !this->CInterpreter::GetNum(num) )
	{
		this->CInterpreter::Error("ReadNum: 수치 읽기 실패");
		return false;
	}

	return true;
}


bool CInterpreter::ReadVar(char* var, const int in_nMaxBufSize) // 54-64 (InterpreterRead.cpp)
{
	if( !this->CInterpreter::CheckType('v') )
	{
		this->CInterpreter::Error("ReadVar: 타입 에러");
		return false;
	}

	if( !this->CInterpreter::GetStr(var, in_nMaxBufSize) )
	{
		this->CInterpreter::Error("ReadVar: 변수 읽기 실패");
		return false;
	}

	return true;
}


bool CInterpreter::ReadStr(char* str, const int in_nMaxBufSize) // 67-77 (InterpreterRead.cpp)
{
	if( !this->CInterpreter::CheckType('s') )
	{
		this->CInterpreter::Error("ReadStr: 타입 에러");
		return false;
	}

	if( !this->CInterpreter::GetStr(str, in_nMaxBufSize) )
	{
		this->CInterpreter::Error("ReadStr: 문자열 읽기 실패");
		return false;
	}

	return true;
}


bool CInterpreter::ReadValue(TokenData& ret) // 80-195 (InterpreterRead.cpp)
{
	std::deque<BYTE> opQ;
	std::deque<TokenData> dataQ;
	TokenData data;

	while( 1 )
	{
		BYTE type;
		if( !this->CInterpreter::PeekByte(type) )
		{
			this->CInterpreter::Error("ReadValue: 타입 읽기 실패");
			return false;
		}

		switch( type )
		{
		case 'f':
		{
			this->CInterpreter::GetByte(type); // consume 'f' byte

			int code;
			if( !this->CInterpreter::ReadCode(code) )
			{
				this->CInterpreter::Error("ReadValue: 함수 실행 코드 읽기 실패");
				return false;
			}

			if( code != CODE_FUNC )
			{
				this->CInterpreter::Error("ReadValue: 잘못된 함수 코드 %d", code);
				return false;
			}

			if( !this->CodeFunc(data) )
			{
				this->CInterpreter::Error("ReadValue: 함수 실행 에러");
				return false;
			}
		}
		break;
		case 'n':
		{
			int num;
			if( !this->CInterpreter::ReadNum(num) )
			{
				this->CInterpreter::Error("ReadValue: 수치 읽기 실패");
				return false;
			}

			data.TokenData::Set(num);
		}
		break;
		case 's':
		{
			char str[1024];
			if( !this->CInterpreter::ReadStr(str, sizeof(str)) )
			{
				this->CInterpreter::Error("ReadValue: 문자열 읽기 실패");
				return false;
			}

			data.TokenData::Set(str);
		}
		break;
		case 'v':
		{
			char str[1024];
			if( !this->CInterpreter::ReadVar(str, sizeof(str)) )
			{
				this->CInterpreter::Error("ReadValue: 변수 읽기 실패");
				return false;
			}

			if( !m_varMap.VarMap::Get(str, data) )
				data.TokenData::operator=(0);
		}
		break;
		default:
		{
			this->CInterpreter::Error("ReadValue: 알수 없는 타입 c[%c] d[%d] h[%x] ", type, type, type);
			return false;
		}
		break;
		};

		dataQ.push_back(data);

		BYTE op;
		if( !this->CInterpreter::GetByte(op) )
		{
			this->CInterpreter::Error("ReadValue: 오퍼레이터 읽기 실패 %c", type);
			return false;
		}

		if( op == OP_END )
			break;

		opQ.push_back(op);
	};

	size_t count = opQ.size();
	for( size_t i = 0; i < count; ++i )
	{
		if( opQ[i] == OP_MUL )
		{
			dataQ[i + 1] = dataQ[i + 0] * dataQ[i + 1];
			dataQ[i + 0] = 0;
			opQ[i] = OP_ADD;
		}
		else
		if( opQ[i] == OP_DIV )
		{
			dataQ[i + 1] = dataQ[i + 0] / dataQ[i + 1];
			dataQ[i + 0] = 0;
			opQ[i] = OP_ADD;
		}
	}

	while( opQ.size() != 0 )
	{
		TokenData d1(dataQ.front());
		dataQ.pop_front();

		TokenData d2(dataQ.front());
		dataQ.pop_front();

		TokenData result;
		switch( opQ.front() )
		{
		case OP_ADD:            result = d1 +  d2; break;
		case OP_SUB:            result = d1 -  d2; break;
		case OP_MOD:            result = d1 %  d2; break;
		case OP_EQUAL:          result = d1 == d2; break;
		case OP_NOTEQUAL:       result = d1 != d2; break;
		case OP_LARGE:          result = d1 >  d2; break;
		case OP_SMALL:          result = d1 <  d2; break;
		case OP_LARGE_OR_EQUAL: result = d1 >= d2; break;
		case OP_SMALL_OR_EQUAL: result = d1 <= d2; break;
		case OP_AND:            result = d1 && d2; break;
		case OP_OR:             result = d1 || d2; break;
		default:                result = 0;        break;
		};

		dataQ.push_back(result);
		dataQ.pop_front();
	}

	ret = dataQ.front();
	return true;
}


bool CInterpreter::PeekByte(BYTE& data) // 6-15 (InterpreterGet.cpp)
{
	if( m_pos + (int)sizeof(BYTE) > m_size )
	{
		this->CInterpreter::Error("PeekByte 범위초과 %d + %d/%d", m_pos, sizeof(BYTE), m_size);
		return false;
	}

	data = *reinterpret_cast<BYTE*>(m_bin[m_pos]);

	return true;
}


bool CInterpreter::GetByte(BYTE& data) // 18-28 (InterpreterGet.cpp)
{
	if( m_pos + (int)sizeof(BYTE) > m_size )
	{
		this->CInterpreter::Error("GetByte 범위초과 %d + %d/%d", m_pos, sizeof(BYTE), m_size);
		return false;
	}

	data = *reinterpret_cast<BYTE*>(m_bin[m_pos]);
	m_pos += (int)sizeof(BYTE);

	return true;
}


bool CInterpreter::GetWord(WORD& data) // 31-41 (InterpreterGet.cpp)
{
	if( m_pos + (int)sizeof(WORD) > m_size )
	{
		this->CInterpreter::Error("GetWord 범위초과 %d + %d/%d", m_pos, sizeof(WORD), m_size);
		return false;
	}

	data = *reinterpret_cast<WORD*>(&m_bin[m_pos]);
	m_pos += (int)sizeof(WORD);

	return true;
}


bool CInterpreter::GetDword(DWORD& data) // 44-54 (InterpreterGet.cpp)
{
	if( m_pos + (int)sizeof(DWORD) > m_size )
	{
		this->CInterpreter::Error("GetWord 범위초과 %d + %d/%d", m_pos, sizeof(DWORD), m_size);
		return false;
	}

	data = *reinterpret_cast<DWORD*>(&m_bin[m_pos]);
	m_pos += (int)sizeof(DWORD);

	return true;
}


bool CInterpreter::GetNum(int& data) // 57-67 (InterpreterGet.cpp)
{
	if( m_pos + (int)sizeof(int) > m_size )
	{
		this->CInterpreter::Error("GetNum 범위초과 %d + %d/%d", m_pos, sizeof(int), m_size);
		return false;
	}

	data = *reinterpret_cast<int*>(&m_bin[m_pos]);
	m_pos += (int)sizeof(int);

	return true;
}


bool CInterpreter::GetStr(char* str, const int in_nMaxBufSize) // 70-80 (InterpreterGet.cpp)
{
	WORD size;
	if( !this->CInterpreter::GetWord(size) )
	{
		this->CInterpreter::Error("GetNum 범위초과 %d + %d/%d", m_pos, size, m_size); //FIXME: copy-paste
		return false;
	}

	if( m_pos + size > m_size )
		return false;

	memcpy_s(str, in_nMaxBufSize, &m_bin[m_pos], size);
	m_pos += size;

	return true;
}


int CInterpreter::GetCurPos() // 83-85 (InterpreterGet.cpp)
{
	return m_pos;
}
