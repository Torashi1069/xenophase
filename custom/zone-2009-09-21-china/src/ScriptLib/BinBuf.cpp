#include "ScriptLib/BinBuf.h"


hook_method<void (CBinBuf::*)(void)> CBinBuf::_CBinBuf(SERVER, "CBinBuf::CBinBuf");
CBinBuf::CBinBuf(void) // line 41
{
	m_buf = NULL;
	this->CBinBuf::Clear();
}


hook_method<void (CBinBuf::*)(void)> CBinBuf::__CBinBuf(SERVER, "CBinBuf::~CBinBuf");
CBinBuf::~CBinBuf(void) // line 48
{
	this->CBinBuf::Clear();
}


hook_method<void (CBinBuf::*)(void)> CBinBuf::_Clear(SERVER, "CBinBuf::Clear");
void CBinBuf::Clear(void) // line 16
{
	return (this->*_Clear)();

	if( m_buf != NULL )
	{
		delete[] m_buf;
		m_buf = NULL;
	}

	m_bufSize = 0;
}


hook_method<bool (CBinBuf::*)(const char* fName)> CBinBuf::_Load(SERVER, "CBinBuf::Load");
bool CBinBuf::Load(const char* fName) // line 27
{
	return (this->*_Load)(fName);

	FILE* fp = fopen(fName, "rb");
	if( fp == NULL )
		return false;

	fseek(fp, 0, SEEK_END);
	m_bufSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	m_buf = new char[m_bufSize];
	fread(m_buf, m_bufSize, 1, fp);

	fclose(fp);
	return true;
}


hook_method<char* (CBinBuf::*)(void)> CBinBuf::_GetBase(SERVER, "CBinBuf::GetBase");
char* CBinBuf::GetBase(void) // line ??
{
	return (this->*_GetBase)();

	return m_buf;
}


hook_method<int (CBinBuf::*)(void)> CBinBuf::_GetSize(SERVER, "CBinBuf::GetSize");
int CBinBuf::GetSize(void) // line ??
{
	return (this->*_GetSize)();

	return m_bufSize;
}
