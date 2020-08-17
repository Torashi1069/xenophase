#pragma once
#include "shared/N2System/FTA(Formated Text Analyzer)/N2FTAVar.h"


class N2FTAToken
{
public:
	enum enumTYPE
	{
		TYPE_NONE              = 0,
		TYPE_EOF               = 1,
		TYPE_STRING            = 2,
		TYPE_SYMBOL            = 3,
		TYPE_NUMBER            = 4,
		TYPE_LEFT_BRACE        = 5,
		TYPE_RIGHT_BRACE       = 6,
		TYPE_COMMA             = 7,
		TYPE_SHARP             = 8,
		TYPE_COLON             = 9,
		TYPE_SEMICOLON         = 10,
		TYPE_LEFT_BRACKETS     = 11,
		TYPE_RIGHT_BRACKETS    = 12,
		TYPE_LEFT_PARENTHESIS  = 13,
		TYPE_RIGHT_PARENTHESIS = 14,
		TYPE_ADD               = 15,
		TYPE_SUB               = 16,
		TYPE_MUL               = 17,
		TYPE_DIV               = 18,
		TYPE_EQUAL             = 19,
		TYPE_NOT               = 20,
		TYPE_AND               = 21,
		TYPE_OR                = 22,
	};

private:
	/* this+ 0 */ //const N2FTAToken::`vftable';
	/* this+ 8 */ enumTYPE m_Type;
	/* this+16 */ N2FTAVar m_Value;
	/* this+72 */ int m_SourceFileLine;
	/* this+76 */ int m_SourceFileCol;
	/* this+80 */ std::string m_SourceFileName;

public:
	const int GetSourceFileCol() const;
	const int GetSourceFileLine() const;
	const std::string GetSourceFileName() const;
	const enumTYPE GetType() const;
	N2FTAVar GetValue();

public:
	N2FTAToken();
	N2FTAToken(const enumTYPE in_Type, N2FTAVar in_Value, const std::string in_SourceFileName, const int in_SourceFileLine, const int in_SourceFileCol);
	virtual ~N2FTAToken();
};
C_ASSERT( sizeof N2FTAToken == 112 );
