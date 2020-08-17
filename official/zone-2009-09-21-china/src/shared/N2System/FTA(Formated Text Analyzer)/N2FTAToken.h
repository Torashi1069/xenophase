#pragma once
#include "N2System/FTA(Formated Text Analyzer)/N2FTAVar.h"
#include "std/string"


class N2FTAToken
{
public:
	enum enumTYPE
	{
		TYPE_NONE = 0,
		TYPE_EOF  = 1,
		TYPE_STRING = 2,
		TYPE_SYMBOL = 3,
		TYPE_NUMBER = 4,
		TYPE_LEFT_BRACE = 5,
		TYPE_RIGHT_BRACE = 6,
		TYPE_COMMA = 7,
		TYPE_SHARP = 8,
		TYPE_COLON = 9,
		TYPE_SEMICOLON = 10,
		TYPE_LEFT_BRACKETS = 11,
		TYPE_RIGHT_BRACKETS = 12,
		TYPE_LEFT_PARENTHESIS = 13,
		TYPE_RIGHT_PARENTHESIS = 14,
		TYPE_ADD = 15,
		TYPE_SUB = 16,
		TYPE_MUL = 17,
		TYPE_DIV = 18,
		TYPE_EQUAL = 19,
		TYPE_NOT = 20,
		TYPE_AND = 21,
		TYPE_OR = 22,
	};

	/* this+0x0  */ //const N2FTAToken::`vftable'
	/* this+0x8  */ private: enum N2FTAToken::enumTYPE m_Type;
	/* this+0x10 */ private: N2FTAVar m_Value;
	/* this+0x48 */ private: int m_SourceFileLine;
	/* this+0x4C */ private: int m_SourceFileCol;
	/* this+0x50 */ private: mystd::string m_SourceFileName;

	public: N2FTAToken::N2FTAToken(const enum N2FTAToken::enumTYPE in_Type, N2FTAVar in_Value, const mystd::string in_SourceFileName, const int in_SourceFileLine, const int in_SourceFileCol);
	public: N2FTAToken::N2FTAToken(void);
	public: virtual N2FTAToken::~N2FTAToken(void);
	public: const int N2FTAToken::GetSourceFileCol(void);
	public: const int N2FTAToken::GetSourceFileLine(void);
	public: const mystd::string N2FTAToken::GetSourceFileName(void);
	public: const enum N2FTAToken::enumTYPE N2FTAToken::GetType(void);
	public: N2FTAVar N2FTAToken::GetValue(void);

private:
	static hook_method<const int (N2FTAToken::*)(void)> N2FTAToken::_GetSourceFileCol;
	static hook_method<const int (N2FTAToken::*)(void)> N2FTAToken::_GetSourceFileLine;
	static hook_method<const mystd::string (N2FTAToken::*)(void)> N2FTAToken::_GetSourceFileName;
	static hook_method<const enum N2FTAToken::enumTYPE (N2FTAToken::*)(void)> N2FTAToken::_GetType;
	static hook_method<N2FTAVar (N2FTAToken::*)(void)> N2FTAToken::_GetValue;
};
