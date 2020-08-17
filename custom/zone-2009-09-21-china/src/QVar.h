#pragma once
#include "std/string"


class CQVar
{
	/* this+ 0 */ public: //const CQVar::`vftable';
	/* this+ 4 */ protected: mystd::string m_str;
	/* this+32 */ protected: int m_num;
	/* this+36 */ protected: DWORD m_dword;
	/* this+40 */ protected: DWORD m_type;

	//public: CQVar::CQVar(DWORD dword);
	public: CQVar::CQVar(mystd::string str);
	public: CQVar::CQVar(char* str);
	public: CQVar::CQVar(int num);
	public: CQVar::CQVar(void);
	public: virtual CQVar::~CQVar(void);
	//public: bool CQVar::Set(const DWORD);
	//public: bool CQVar::Set(const int);
	//public: bool CQVar::Set(const char *);
	public: int CQVar::o_num(void);
	public: char* CQVar::o_str(void);
	public: DWORD CQVar::o_dword(void);
	public: int CQVar::length(void);
	//public: char* operator char *();
	//public: const char* operator const char *();
	//public: mystd::string operator mystd::string();
	//public: int operator int();
	//public: unsigned long operator unsigned long();
	//public: const CQVar& CQVar::operator=(const DWORD);
	public: const CQVar& CQVar::operator=(const char* str);
	public: const CQVar& CQVar::operator=(mystd::string str);
	public: const CQVar& CQVar::operator=(const int num);
	public: int CQVar::FindToken(const char& t);
	public: int CQVar::FindToken(const char* str);
	public: int CQVar::FindToken(int pos, const char* str);
	public: int CQVar::Delete(int pos);
	public: int CQVar::Delete(int stPos, int endPos);
	public: mystd::string CQVar::SubStr(int startPos, int endPos);
	public: mystd::string CQVar::SubStr(int pos);
	public: int CQVar::Replace(const char* strOld, const char* strNew);
	public: mystd::string CQVar::SpanExcluding(char* ptr);
	public: void CQVar::Trim_Left(void);
	public: void CQVar::Trim_Right(void);

private:
	static hook_method<int (CQVar::*)(void)> CQVar::_o_num;
	static hook_method<char* (CQVar::*)(void)> CQVar::_o_str;
	static hook_method<DWORD (CQVar::*)(void)> CQVar::_o_dword;
	static hook_method<int (CQVar::*)(void)> CQVar::_length;
	static hook_method<const CQVar& (CQVar::*)(const char* str)> CQVar::_operator_eq3;
	static hook_method<const CQVar& (CQVar::*)(mystd::string str)> CQVar::_operator_eq2;
	static hook_method<const CQVar& (CQVar::*)(const int num)> CQVar::_operator_eq;
	static hook_method<int (CQVar::*)(const char& t)> CQVar::_FindToken3;
	static hook_method<int (CQVar::*)(const char* str)> CQVar::_FindToken2;
	static hook_method<int (CQVar::*)(int pos, const char* str)> CQVar::_FindToken;
	static hook_method<int (CQVar::*)(int pos)> CQVar::_Delete2;
	static hook_method<int (CQVar::*)(int stPos, int endPos)> CQVar::_Delete;
	static hook_method<mystd::string (CQVar::*)(int startPos, int endPos)> CQVar::_SubStr;
	static hook_method<mystd::string (CQVar::*)(int pos)> CQVar::_SubStr2;
	static hook_method<int (CQVar::*)(const char* strOld, const char* strNew)> CQVar::_Replace;
	static hook_method<mystd::string (CQVar::*)(char* ptr)> CQVar::_SpanExcluding;
	static hook_method<void (CQVar::*)(void)> CQVar::_Trim_Left;
	static hook_method<void (CQVar::*)(void)> CQVar::_Trim_Right;
};
