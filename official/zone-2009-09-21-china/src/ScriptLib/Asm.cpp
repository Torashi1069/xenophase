#include "ScriptLib/Asm.h"


hook_method<void (CAsm::*)(void)> CAsm::_CAsm(SERVER, "CAsm::CAsm");
CAsm::CAsm(void) // line ??
{
	m_fp = NULL;
}


hook_method<void (CAsm::*)(void)> CAsm::__CAsm(SERVER, "CAsm::~CAsm");
CAsm::~CAsm(void) // line 91
{
	this->CAsm::Release();
}


hook_method<bool (CAsm::*)(char* fName)> CAsm::_Set(SERVER, "CAsm::Set");
bool CAsm::Set(char* fName) // line 72
{
	return (this->*_Set)(fName);

	if( m_fp != NULL )
		fclose(m_fp);

	m_fp = fopen(fName, "w");
	return ( m_fp != NULL );
}


hook_method<void (CAsm::*)(void)> CAsm::_Release(SERVER, "CAsm::Release");
void CAsm::Release(void) // line 81
{
	return (this->*_Release)();

	if( m_fp != NULL )
		fclose(m_fp);
}


hook_method<void (CAsm::*)(int addr)> CAsm::_Line(SERVER, "CAsm::Line");
void CAsm::Line(int addr) // line 9
{
	return (this->*_Line)(addr);

	this->CAsm::Putf("\n%.8x: ", addr);
}


hook_method<void (CAsm::*)(char* str)> CAsm::_Put(SERVER, "CAsm::Put");
void CAsm::Put(char* str) // line 14
{
	return (this->*_Put)(str);

	fprintf(m_fp, "%s", str);
}


hook_method<void (CAsm::*)(char* str, ...)> CAsm::_Putf(SERVER, "CAsm::Putf");
void CAsm::Putf(char* str, ...) // line 18
{
//	return (this->*_Putf)(str, ...);

	va_list va;
	va_start(va, str);

	if( m_fp != NULL )
	{
		char buf[1024];
		vsprintf(buf, str, va);
		this->CAsm::Put(buf);
	}
}


hook_method<void (CAsm::*)(char* str)> CAsm::_Error(SERVER, "CAsm::Error");
void CAsm::Error(char* str) // line 32
{
	return (this->*_Error)(str);

	this->CAsm::Put("\n// Error: ");
	this->CAsm::Put(str);
}


//hook_method<void (CAsm::*)(char* str, ...)> CAsm::_Errorf(SERVER, "CAsm::Errorf");
void CAsm::Errorf(char* str, ...) // line ??
{
//	return (this->*_Errorf)(str, ...);

	va_list va;
	va_start(va, str);

	if( m_fp != NULL )
	{
		char buf[1024];
		vsprintf(buf, str, va);
		this->CAsm::Error(buf);
	}
}


hook_method<void (CAsm::*)(char* str)> CAsm::_Comment(SERVER, "CAsm::Comment");
void CAsm::Comment(char* str) // line 52
{
	return (this->*_Comment)(str);

	this->CAsm::Put("\n// ");
	this->CAsm::Put(str);
}


hook_method<void (CAsm::*)(char* str, ...)> CAsm::_Commentf(SERVER, "CAsm::Commentf");
void CAsm::Commentf(char* str, ...) // line 58
{
//	return (this->*_Commentf)(str, ...);

	va_list va;
	va_start(va, str);

	if( m_fp != NULL )
	{
		char buf[1024];
		vsprintf(buf, str, va);
		this->CAsm::Comment(buf);
	}
}
