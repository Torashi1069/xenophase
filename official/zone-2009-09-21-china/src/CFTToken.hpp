#pragma once
#include "std/string"


class CFTToken
{
public:
	enum enumType
	{
		NONE        = 0,
		STRING      = 1,
		NUMBER      = 2,
		SYMBOL      = 3,
		LEFT_BRACE  = 4,
		RIGHT_BRACE = 5,
		COMMA       = 6,
		EOF_        = 7,
	};

	/* this+ 0 */ //const CFTToken::`vftable';
	/* this+ 4 */ enum CFTToken::enumType m_Type;
	/* this+ 8 */ mystd::string m_Value;
	/* this+36 */ int m_Line;
	/* this+40 */ int m_Col;

	public: CFTToken::CFTToken(const CFTToken& __that);
	public: CFTToken::CFTToken(const enum CFTToken::enumType in_Type, const mystd::string in_Value, const int in_Line, const int in_Col);
	public: CFTToken::CFTToken(void);
	public: virtual CFTToken::~CFTToken(void);
	public: enum CFTToken::enumType CFTToken::GetType(void);
	public: int CFTToken::GetINT(void);
	public: mystd::string CFTToken::GetSTRING(void);
	public: int CFTToken::GetLine(void);
	public: int CFTToken::GetCol(void);
private:
	static hook_method<enum CFTToken::enumType (CFTToken::*)(void)> CFTToken::_GetType;
	static hook_method<int (CFTToken::*)(void)> CFTToken::_GetINT;
	static hook_method<mystd::string (CFTToken::*)(void)> CFTToken::_GetSTRING;
	static hook_method<int (CFTToken::*)(void)> CFTToken::_GetLine;
	static hook_method<int (CFTToken::*)(void)> CFTToken::_GetCol;
};
