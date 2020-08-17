#include "QVar.h"


CQVar::CQVar(void) // line 5
{
	m_str = "";
	m_num = 0;
	m_type = 0;
	m_dword = 0;
}


CQVar::CQVar(int num) // line 13
{
	m_num = num;
	m_dword = 0;
}


CQVar::CQVar(char* str) // line 19
{
	m_str = str;
	m_type = 1;
}


CQVar::CQVar(mystd::string str) // line 25
{
	m_str = str;
	m_type = 1;
}


CQVar::~CQVar(void) // line 37
{
	m_str = "";
	m_num = 0;
	m_type = 0;
	m_dword = 0;
}


hook_method<int (CQVar::*)(void)> CQVar::_o_num(SERVER, "CQVar::o_num");
int CQVar::o_num(void) // line ??
{
	return (this->*_o_num)();

	return m_num;
}


hook_method<char* (CQVar::*)(void)> CQVar::_o_str(SERVER, "CQVar::o_str");
char* CQVar::o_str(void) // line 79
{
	return (this->*_o_str)();

	return (char*)m_str.c_str();
}


hook_method<DWORD (CQVar::*)(void)> CQVar::_o_dword(SERVER, "CQVar::o_dword");
DWORD CQVar::o_dword(void) // line 95
{
	return (this->*_o_dword)();

	return ( m_dword != 0 ) ? m_dword : this->CQVar::o_num();
}


hook_method<int (CQVar::*)(void)> CQVar::_length(SERVER, "CQVar::length");
int CQVar::length(void) // line 84
{
	return (this->*_length)();

	return ( m_type == 0 ) ? sizeof(int)
	     : ( m_type == 1 ) ? m_str.size()
		 : ( m_type == 2 ) ? sizeof(DWORD)
		 :                   0;
}


hook_method<const CQVar& (CQVar::*)(const char* str)> CQVar::_operator_eq3(SERVER, "??4CQVar@@QAEABV0@PBD@Z");
const CQVar& CQVar::operator=(const char* str) // line 101
{
	return (this->*_operator_eq3)(str);

	if( str != NULL )
		m_str = str;
	m_type = 1;
	return *this;
}


hook_method<const CQVar& (CQVar::*)(mystd::string str)> CQVar::_operator_eq2(SERVER, "??4CQVar@@QAEABV0@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
const CQVar& CQVar::operator=(mystd::string str) // line 108
{
	return (this->*_operator_eq2)(str);

	if( str != "" )
		m_str = str;
	m_type = 1;
	return *this;

}


hook_method<const CQVar& (CQVar::*)(const int num)> CQVar::_operator_eq(SERVER, "??4CQVar@@QAEABV0@H@Z");
const CQVar& CQVar::operator=(const int num) // line 116
{
	return (this->*_operator_eq)(num);

	m_num = num;
	m_dword = 0;
	m_type = 0;
	return *this;
}


hook_method<int (CQVar::*)(const char& t)> CQVar::_FindToken3(SERVER, "?FindToken@CQVar@@QAEHABD@Z");
int CQVar::FindToken(const char& t) // line 135
{
	return (this->*_FindToken3)(t);

	return ( m_type == 1 ) ? m_str.find(&t, 0, 1) : -1;
}


hook_method<int (CQVar::*)(const char* str)> CQVar::_FindToken2(SERVER, "?FindToken@CQVar@@QAEHPBD@Z");
int CQVar::FindToken(const char* str) // lne 142
{
	return (this->*_FindToken2)(str);

	return ( m_type == 1 ) ? m_str.find(str) : -1;
}


hook_method<int (CQVar::*)(int pos, const char* str)> CQVar::_FindToken(SERVER, "?FindToken@CQVar@@QAEHHPBD@Z");
int CQVar::FindToken(int pos, const char* str) // line 149
{
	return (this->*_FindToken)(pos, str);

	return ( m_type == 1 ) ? m_str.find(str, pos) : -1;
}


hook_method<int (CQVar::*)(int pos)> CQVar::_Delete2(SERVER, "?Delete@CQVar@@QAEHH@Z");
int CQVar::Delete(int pos) // line 156
{
	return (this->*_Delete2)(pos);

	if( m_type == 1 )
	{
		m_str.erase(0, pos);
		return m_str.size();
	}
	else
	{
		return -1;
	}
}


hook_method<int (CQVar::*)(int stPos, int endPos)> CQVar::_Delete(SERVER, "?Delete@CQVar@@QAEHHH@Z");
int CQVar::Delete(int stPos, int endPos) // line 165
{
	return (this->*_Delete)(stPos, endPos);

	if( m_type == 1 )
	{
		m_str.erase(stPos, endPos);
		return m_str.size();
	}
	else
	{
		return -1;
	}
}


hook_method<mystd::string (CQVar::*)(int startPos, int endPos)> CQVar::_SubStr(SERVER, "?SubStr@CQVar@@QAE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@HH@Z");
mystd::string CQVar::SubStr(int startPos, int endPos) // line 175
{
	return (this->*_SubStr)(startPos, endPos);

	return ( m_type == 1 ) ? m_str.substr(startPos, endPos) : "";
}


hook_method<mystd::string (CQVar::*)(int pos)> CQVar::_SubStr2(SERVER, "?SubStr@CQVar@@QAE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@H@Z");
mystd::string CQVar::SubStr(int pos) // line 183
{
	return (this->*_SubStr2)(pos);

	return ( m_type == 1 ) ? m_str.substr(0, pos): "";
}


hook_method<int (CQVar::*)(const char* strOld, const char* strNew)> CQVar::_Replace(SERVER, "CQVar::Replace");
int CQVar::Replace(const char* strOld, const char* strNew) // line 191
{
	return (this->*_Replace)(strOld, strNew);

	if( m_type == 1 )
	{
		int pos;
		size_t len = strlen(strOld);

		while( (pos = this->CQVar::FindToken(strOld)) != -1 )
		{
			m_str.insert(pos + len, strNew);
			m_str.erase(pos, len);
		}
	}

	return -1;
}


hook_method<mystd::string (CQVar::*)(char* ptr)> CQVar::_SpanExcluding(SERVER, "CQVar::SpanExcluding");
mystd::string CQVar::SpanExcluding(char* ptr) // line 209
{
	return (this->*_SpanExcluding)(ptr);

	int pos = this->CQVar::FindToken(ptr);
	return ( pos >= 1 ) ? this->CQVar::SubStr(0, pos) : "";
}


hook_method<void (CQVar::*)(void)> CQVar::_Trim_Left(SERVER, "CQVar::Trim_Left");
void CQVar::Trim_Left(void) // line 217
{
	return (this->*_Trim_Left)();

	while( 1 )
	{
		mystd::string ptr = this->CQVar::SubStr(0, 1);

		if( ptr.size() < 1 )
			break;

		if( strcmp(ptr.c_str(), " ") != 0
		&&  strcmp(ptr.c_str(), "\n") != 0
		&&  strcmp(ptr.c_str(), "\t") != 0
		&&  strcmp(ptr.c_str(), "\r") != 0 )
			break;

		this->CQVar::Delete(0, 1);
	}
}


hook_method<void (CQVar::*)(void)> CQVar::_Trim_Right(SERVER, "CQVar::Trim_Right");
void CQVar::Trim_Right(void) // line 230
{
	return (this->*_Trim_Right)();

	while( 1 )
	{
		if( this->CQVar::length() < 1 )
			break;

		mystd::string ptr = this->CQVar::SubStr(this->CQVar::length() - 1, 1);

		if( ptr.size() < 1 )
			break;

		if( strcmp(ptr.c_str(), " ") != 0
		&&  strcmp(ptr.c_str(), "\n") != 0
		&&  strcmp(ptr.c_str(), "\t") != 0
		&&  strcmp(ptr.c_str(), "\r") != 0 )
			break;

		this->CQVar::Delete(this->CQVar::length() - 1, 1);
	}
}
