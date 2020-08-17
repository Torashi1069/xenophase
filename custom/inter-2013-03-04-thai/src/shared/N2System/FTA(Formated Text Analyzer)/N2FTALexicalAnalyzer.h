#pragma once
#include "shared/N2System/FTA(Formated Text Analyzer)/N2FTAFile.h"
#include "shared/N2System/FTA(Formated Text Analyzer)/N2FTAToken.h"


class N2FTALexicalAnalyzer
{
public:
	class FTARet
	{
	public:
		enum enumReturnCode
		{
			RETURNCODE_SUCCESS = 0,
			RETURNCODE_ERROR   = 1,
		};

	private:
		/* this+  0 */ enumReturnCode m_Code;
		/* this+  8 */ N2FTAToken m_Token;
		/* this+120 */ int m_SourceFileLine;
		/* this+124 */ int m_SourceFileCol;
		/* this+128 */ std::string m_SourceFileName;

	public:
		const enumReturnCode GetResult();
		N2FTAToken GetToken();
		const std::string GetSourceFileName();

	public:
		FTARet(const enumReturnCode in_Code, N2FTAToken in_Token);
		FTARet(const enumReturnCode in_Code, const std::string in_SourceFileName, const int in_SourceFileLine, const int in_SourceFileCol);
		FTARet();
	};

private:
	/* this+ 0 */ //const N2FTALexicalAnalyzer::`vftable';
	/* this+ 4 */ N2FTAFile& m_SourceFile;
	/* this+ 8 */ bool m_bOK;
	typedef std::list<FTARet> FTARetCONTAINER;
	/* this+12 */ FTARetCONTAINER m_Container;

private:
	int isLetter(const char in_ch);
	bool isAlpha(const char in_ch);
	bool isDelimiter(const char in_ch);
	bool isNumeric(const char in_ch);
	int RemoveGarbage();
	int RemoveComment();
	FTARet Anaysis();
	FTARet StringAnaysis();
	FTARet SymbolAnaysis();
	FTARet NumberAnaysis();

public:
	const bool isOK() const;
	FTARet GetToken();
	FTARet ViewToken();
	const int GetLine();
	const std::string GetLineStr(const int in_Line);

public:
	N2FTALexicalAnalyzer(N2FTAFile& in_SourceFile);
	virtual ~N2FTALexicalAnalyzer();
};
