#pragma once


class CAsm
{
	/* this+0 */ private: FILE* m_fp;
	/* this+4 */ private: int m_linePos;

	public: CAsm::CAsm(void);
	public: CAsm::~CAsm(void);
	public: bool CAsm::Set(char* fName);
	public: void CAsm::Release(void);
	public: void CAsm::Line(int addr);
	public: void CAsm::Put(char* str);
	public: void CAsm::Putf(char* str, ...);
	public: void CAsm::Error(char* str);
	public: void CAsm::Errorf(char* str, ...);
	public: void CAsm::Comment(char* str);
	public: void CAsm::Commentf(char* str, ...);

private:
	static hook_method<void (CAsm::*)(void)> CAsm::_CAsm;
	static hook_method<void (CAsm::*)(void)> CAsm::__CAsm;
	static hook_method<bool (CAsm::*)(char* fName)> CAsm::_Set;
	static hook_method<void (CAsm::*)(void)> CAsm::_Release;
	static hook_method<void (CAsm::*)(int addr)> CAsm::_Line;
	static hook_method<void (CAsm::*)(char* str)> CAsm::_Put;
	static hook_method<void (CAsm::*)(char* str, ...)> CAsm::_Putf;
	static hook_method<void (CAsm::*)(char* str)> CAsm::_Error;
	static hook_method<void (CAsm::*)(char* str, ...)> CAsm::_Errorf;
	static hook_method<void (CAsm::*)(char* str)> CAsm::_Comment;
	static hook_method<void (CAsm::*)(char* str, ...)> CAsm::_Commentf;
};
