#pragma once


class CBin
{
	/* this+0 */ private: FILE* m_fp;

	public: CBin::CBin(void);
	public: CBin::~CBin(void);
	public: bool CBin::Set(char* fName);
	public: void CBin::Release(void);
	public: int CBin::GetPos(void);
	public: void CBin::Seek(int pos);
	public: void CBin::WriteByte(int n);
	public: void CBin::WriteWord(int n);
	public: void CBin::WriteDword(int n);
	public: void CBin::WriteNum(int n);
	public: void CBin::WriteStr(char* str);

private:
	static hook_method<void (CBin::*)(void)> CBin::_CBin;
	static hook_method<void (CBin::*)(void)> CBin::__CBin;
	static hook_method<bool (CBin::*)(char* fName)> CBin::_Set;
	static hook_method<void (CBin::*)(void)> CBin::_Release;
	static hook_method<int (CBin::*)(void)> CBin::_GetPos;
	static hook_method<void (CBin::*)(int pos)> CBin::_Seek;
	static hook_method<void (CBin::*)(int n)> CBin::_WriteByte;
	static hook_method<void (CBin::*)(int n)> CBin::_WriteWord;
	static hook_method<void (CBin::*)(int n)> CBin::_WriteDword;
	static hook_method<void (CBin::*)(int n)> CBin::_WriteNum;
	static hook_method<void (CBin::*)(char* str)> CBin::_WriteStr;
};
