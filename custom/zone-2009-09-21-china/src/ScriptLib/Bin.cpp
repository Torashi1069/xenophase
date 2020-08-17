#include "ScriptLib/Bin.h"


hook_method<void (CBin::*)(void)> CBin::_CBin(SERVER, "CBin::CBin");
CBin::CBin(void) // line 71
{
	m_fp = NULL;
}


hook_method<void (CBin::*)(void)> CBin::__CBin(SERVER, "CBin::~CBin");
CBin::~CBin(void) // line ?
{
	this->CBin::Release();
}


hook_method<bool (CBin::*)(char* fName)> CBin::_Set(SERVER, "CBin::Set");
bool CBin::Set(char* fName) // line 11
{
	return (this->*_Set)(fName);

	if( m_fp != NULL )
		fclose(m_fp);

	m_fp = fopen(fName, "wb");
	return ( m_fp != NULL );
}


hook_method<void (CBin::*)(void)> CBin::_Release(SERVER, "CBin::Release");
void CBin::Release(void) // line ??
{
	return (this->*_Release)();

	if( m_fp != NULL )
		fclose(m_fp);
}


hook_method<int (CBin::*)(void)> CBin::_GetPos(SERVER, "CBin::GetPos");
int CBin::GetPos(void) // line 20
{
	return (this->*_GetPos)();

	return ( m_fp != NULL ) ? ftell(m_fp) : 0;
}


hook_method<void (CBin::*)(int pos)> CBin::_Seek(SERVER, "CBin::Seek");
void CBin::Seek(int pos) // line 7
{
	return (this->*_Seek)(pos);

	fseek(m_fp, pos, SEEK_SET);
}


hook_method<void (CBin::*)(int n)> CBin::_WriteByte(SERVER, "CBin::WriteByte");
void CBin::WriteByte(int n) // line 43
{
	return (this->*_WriteByte)(n);

	if( m_fp != NULL )
		fwrite((BYTE*)&n, sizeof(BYTE), 1, m_fp);
}


hook_method<void (CBin::*)(int n)> CBin::_WriteWord(SERVER, "CBin::WriteWord");
void CBin::WriteWord(int n) // line 51
{
	return (this->*_WriteWord)(n);

	if( m_fp != NULL )
		fwrite((WORD*)&n, sizeof(WORD), 1, m_fp);
}


//hook_method<void (CBin::*)(int n)> CBin::_WriteDword(SERVER, "CBin::WriteDword");
void CBin::WriteDword(int n) // line ??
{
//	return (this->*_WriteDword)(n);

	if( m_fp != NULL )
		fwrite((DWORD*)&n, sizeof(DWORD), 1, m_fp);
}


hook_method<void (CBin::*)(int n)> CBin::_WriteNum(SERVER, "CBin::WriteNum");
void CBin::WriteNum(int n) // line 27
{
	return (this->*_WriteNum)(n);

	if( m_fp != NULL )
		fwrite((int*)&n, sizeof(int), 1, m_fp);
}


hook_method<void (CBin::*)(char* str)> CBin::_WriteStr(SERVER, "CBin::WriteStr");
void CBin::WriteStr(char* str) // line 33
{
	return (this->*_WriteStr)(str);

	if( m_fp != NULL )
	{
		size_t len = strlen(str);
		this->CBin::WriteWord(len);
		fwrite(str, len, 1, m_fp);
	}
}
