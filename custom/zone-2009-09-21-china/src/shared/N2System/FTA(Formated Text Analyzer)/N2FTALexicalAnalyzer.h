#pragma once
#include "N2System/FTA(Formated Text Analyzer)/N2FTAFile.h"
#include "N2System/FTA(Formated Text Analyzer)/N2FTAToken.h"
#include "std/list"
#include "std/string"


class N2FTALexicalAnalyzer
{
public:
	class FTARet
	{
	public:
		enum enumReturnCode
		{
			RETURNCODE_SUCCESS =  0x0,
			RETURNCODE_ERROR =  0x1,
		};

		/* this+0x0  */ private: enum N2FTALexicalAnalyzer::FTARet::enumReturnCode m_Code;
		/* this+0x8  */ private: N2FTAToken m_Token;
		/* this+0x78 */ private: int m_SourceFileLine;
		/* this+0x7C */ private: int m_SourceFileCol;
		/* this+0x80 */ private: mystd::string m_SourceFileName;

		public: N2FTALexicalAnalyzer::FTARet::FTARet(void);
		public: N2FTALexicalAnalyzer::FTARet::FTARet(const enum N2FTALexicalAnalyzer::FTARet::enumReturnCode in_Code, const mystd::string in_SourceFileName, const int in_SourceFileLine, const int in_SourceFileCol);
		public: N2FTALexicalAnalyzer::FTARet::FTARet(const enum N2FTALexicalAnalyzer::FTARet::enumReturnCode in_Code, N2FTAToken in_Token);
		public: N2FTALexicalAnalyzer::FTARet::~FTARet(void);
		public: const enum N2FTALexicalAnalyzer::FTARet::enumReturnCode N2FTALexicalAnalyzer::FTARet::GetResult(void);
		public: N2FTAToken N2FTALexicalAnalyzer::FTARet::GetToken(void);
		public: const mystd::string N2FTALexicalAnalyzer::FTARet::GetSourceFileName(void);
	};

	/* this+0x0 */ //const N2FTALexicalAnalyzer::`vftable'
	/* this+0x4 */ private: N2FTAFile& m_SourceFile;
	/* this+0x8 */ private: bool m_bOK;
	/* this+0xC */ private: mystd::list<N2FTALexicalAnalyzer::FTARet> m_Container;

	public: N2FTALexicalAnalyzer::N2FTALexicalAnalyzer(N2FTAFile& in_SourceFile);
	public: virtual N2FTALexicalAnalyzer::~N2FTALexicalAnalyzer(void);
	//private: int N2FTALexicalAnalyzer::isLetter(const char);
	//private: bool N2FTALexicalAnalyzer::isAlpha(const char);
	//private: bool N2FTALexicalAnalyzer::isDelimiter(const char);
	//private: bool N2FTALexicalAnalyzer::isNumeric(const char);
	//private: int N2FTALexicalAnalyzer::RemoveGarbage();
	//private: int N2FTALexicalAnalyzer::RemoveComment();
	private: N2FTALexicalAnalyzer::FTARet N2FTALexicalAnalyzer::Anaysis(void);
	//private: N2FTALexicalAnalyzer::FTARet N2FTALexicalAnalyzer::StringAnaysis();
	//private: N2FTALexicalAnalyzer::FTARet N2FTALexicalAnalyzer::SymbolAnaysis();
	//private: N2FTALexicalAnalyzer::FTARet N2FTALexicalAnalyzer::NumberAnaysis();
	public: const bool N2FTALexicalAnalyzer::isOK(void);
	//public: N2FTALexicalAnalyzer::FTARet N2FTALexicalAnalyzer::GetToken();
	public: N2FTALexicalAnalyzer::FTARet N2FTALexicalAnalyzer::ViewToken(void);
	//public: const int N2FTALexicalAnalyzer::GetLine();
	//public: const mystd::string N2FTALexicalAnalyzer::GetLineStr(const int);

private:
	static hook_method<N2FTALexicalAnalyzer::FTARet (N2FTALexicalAnalyzer::*)(void)> N2FTALexicalAnalyzer::_Anaysis;
	static hook_method<const bool (N2FTALexicalAnalyzer::*)(void)> N2FTALexicalAnalyzer::_isOK;
	static hook_method<N2FTALexicalAnalyzer::FTARet (N2FTALexicalAnalyzer::*)(void)> N2FTALexicalAnalyzer::_ViewToken;
};
