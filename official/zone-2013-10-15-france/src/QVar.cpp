#include "QVar.h"


CQVar::CQVar()
{
	m_str = "";
	m_num = 0;
	m_type = NUM;
	m_dword = 0;
}


CQVar::CQVar(int num)
{
	m_num = num;
	m_dword = 0;
}


CQVar::CQVar(char* str)
{
	m_str = str;
	m_type = STR;
}


CQVar::CQVar(std::string str)
{
	m_str = str;
	m_type = STR;
}


CQVar::CQVar(DWORD dword)
{
	m_dword = dword;
	m_num = 0;
}


CQVar::~CQVar()
{
	m_str = "";
	m_num = 0;
	m_type = NUM;
	m_dword = 0;
}


bool CQVar::Set(const char* st)
{
	if( st == NULL )
		return false;

	m_str = st;
	m_type = STR;
	return true;
}


bool CQVar::Set(const int num)
{
	m_num = num;
	m_dword = 0;
	m_type = NUM;
	return true;
}


bool CQVar::Set(const DWORD dw)
{
	m_dword = dw;
	m_num = 0;
	m_type = DW;
	return true;
}


int CQVar::o_num()
{
	return m_num;
}


char* CQVar::o_str()
{
	return const_cast<char*>(m_str.c_str());
}


int CQVar::length()
{
	switch( m_type )
	{
	case NUM: return sizeof(m_num);
	case STR: return m_str.size();
	case DW : return sizeof(m_dword);
	default : return 0;
	};
}


DWORD CQVar::o_dword()
{
	return ( m_dword != 0 ) ? m_dword : this->CQVar::o_num();
}


CQVar::operator char*()
{
	return this->CQVar::o_str();
}


CQVar::operator const char*()
{
	return this->CQVar::o_str();
}


CQVar::operator std::string()
{
	return this->CQVar::o_str();
}


CQVar::operator int()
{
	return this->CQVar::o_num();
}


CQVar::operator DWORD()
{
	return this->CQVar::o_dword();
}


const CQVar& CQVar::operator=(const char* str)
{
	if( str != NULL )
		m_str = str;
	m_type = STR;
	return *this;
}


const CQVar& CQVar::operator=(std::string str)
{
	if( str.c_str() != "" && str.size() > 0 ) //FIXME: direct pointer comparison
		m_str = str;
	m_type = STR;
	return *this;
}


const CQVar& CQVar::operator=(const int num)
{
	m_dword = 0;
	m_num = num;
	m_type = NUM;
	return *this;
}


const CQVar& CQVar::operator=(const DWORD dw)
{
	m_dword = dw;
	m_num = 0;
	m_type = DW;
	return *this;
}


int CQVar::FindToken(const char& t)
{
	if( m_type != STR )
		return -1;

	return m_str.find(t);
}


int CQVar::FindToken(const char* str)
{
	if( m_type != STR )
		return -1;

	return m_str.find(str);
}


int CQVar::FindToken(int pos, const char* str)
{
	if( m_type != STR )
		return -1;

	return m_str.find(str, pos);
}


int CQVar::Delete(int pos)
{
	if( m_type != STR )
		return -1;

	m_str.erase(0, pos);
	return (int)m_str.size();
}


int CQVar::Delete(int stPos, int endPos)
{
	if( m_type != STR )
		return -1;

	m_str.erase(stPos, endPos);
	return (int)m_str.size();
}


std::string CQVar::SubStr(int startPos, int endPos)
{
	if( m_type != STR )
		return "";

	return m_str.substr(startPos, endPos); //FIXME: 'endPos' misnamed, used as 'count' parameter
}


std::string CQVar::SubStr(int pos)
{
	if( m_type != STR )
		return "";

	return m_str.substr(0, pos);
}


int CQVar::Replace(const char* strOld, const char* strNew)
{
	if( m_type != STR )
		return -1;

	size_t strOldLen = strlen(strOld);
	for( ; ; )
	{
		int pos = this->CQVar::FindToken(strOld);
		if( pos == -1 )
			break;

		m_str.insert(pos + strOldLen, strNew);
		m_str.erase(pos + 0, strOldLen);
	}

	return -1; // pos?
}


std::string CQVar::SpanExcluding(char* ptr)
{
	int pos = this->CQVar::FindToken(ptr);
	if( pos < 1 )
		return "";

	return this->CQVar::SubStr(0, pos);
}


void CQVar::Trim_Left()
{
	for( ; ; )
	{
		std::string ptr = this->CQVar::SubStr(0, 1);
		if( ptr.size() < 1 )
			break;

		if( strcmp(ptr.c_str(), " ") != 0
		 && strcmp(ptr.c_str(), "\n") != 0
		 && strcmp(ptr.c_str(), "\t") != 0
		 && strcmp(ptr.c_str(), "\r") != 0 )
			break;

		this->CQVar::Delete(0, 1);
	}
}


void CQVar::Trim_Right()
{
	for( ; ; )
	{
		if( this->CQVar::length() < 1 )
			break;

		std::string ptr = this->CQVar::SubStr(this->CQVar::length() - 1, 1);
		if( ptr.size() < 1 )
			break;

		if( strcmp(ptr.c_str(), " ") != 0
		 && strcmp(ptr.c_str(), "\n") != 0
		 && strcmp(ptr.c_str(), "\t") != 0
		 && strcmp(ptr.c_str(), "\r") != 0 )
			break;

		this->CQVar::Delete(this->CQVar::length() - 1, 1);
	}
}
