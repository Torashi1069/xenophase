#pragma once


enum enumQVARTYPE
{
	NUM = 0,
	STR = 1,
	DW  = 2,
};


class CQVar
{
public:
	CQVar();
	CQVar(int num);
	CQVar(char* str);
	CQVar(std::string str);
	CQVar(DWORD dword);
	virtual ~CQVar();

	bool Set(const char* st);
	bool Set(const int num);
	bool Set(const DWORD dw);

	int o_num();
	char* o_str();
	int length();
	DWORD o_dword();

	operator char*();
	operator const char*();
	operator std::string();
	operator int();
	operator DWORD();

	const CQVar& operator=(const char* str);
	const CQVar& operator=(std::string str);
	const CQVar& operator=(const int num);
	const CQVar& operator=(const DWORD dw);

	int FindToken(const char& t);
	int FindToken(const char* str);
	int FindToken(int pos, const char* str);
	int Delete(int pos);
	int Delete(int stPos, int endPos);
	std::string SubStr(int pos);
	std::string SubStr(int startPos, int endPos);
	int Replace(const char* strOld, const char* strNew);
	std::string SpanExcluding(char* ptr);
	void Trim_Left();
	void Trim_Right();

protected:
	/* this+ 0 */ //const CQVar::`vftable';
	/* this+ 4 */ std::string m_str;
	/* this+32 */ int m_num;
	/* this+36 */ DWORD m_dword;
	/* this+40 */ DWORD m_type; // enumQVARTYPE
};
