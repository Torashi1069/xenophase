#include "N2System/FTA(Formated Text Analyzer)/N2FTALexicalAnalyzer.h"


N2FTALexicalAnalyzer::FTARet::FTARet(void)
{
	m_Code = RETURNCODE_ERROR;
	m_SourceFileLine = 0;
	m_SourceFileCol = 0;
	m_SourceFileName = "";
}


N2FTALexicalAnalyzer::FTARet::FTARet(const enum N2FTALexicalAnalyzer::FTARet::enumReturnCode in_Code, const mystd::string in_SourceFileName, const int in_SourceFileLine, const int in_SourceFileCol)
{
	m_Code = in_Code;
	m_SourceFileLine = in_SourceFileLine;
	m_SourceFileCol = in_SourceFileCol;
	m_SourceFileName = in_SourceFileName;
}


N2FTALexicalAnalyzer::FTARet::FTARet(const enum N2FTALexicalAnalyzer::FTARet::enumReturnCode in_Code, N2FTAToken in_Token) : m_Code(in_Code), m_Token(in_Token)
{
	m_SourceFileCol = m_Token.N2FTAToken::GetSourceFileCol();
	m_SourceFileLine = m_Token.N2FTAToken::GetSourceFileLine();
	m_SourceFileName = m_Token.N2FTAToken::GetSourceFileName();
}


N2FTALexicalAnalyzer::FTARet::~FTARet(void)
{
}


const enum N2FTALexicalAnalyzer::FTARet::enumReturnCode N2FTALexicalAnalyzer::FTARet::GetResult(void)
{
	return m_Code;
}


N2FTAToken N2FTALexicalAnalyzer::FTARet::GetToken(void)
{
	return m_Token;
}


const mystd::string N2FTALexicalAnalyzer::FTARet::GetSourceFileName(void)
{
	return m_SourceFileName;
}


N2FTALexicalAnalyzer::N2FTALexicalAnalyzer(N2FTAFile& in_SourceFile) : m_SourceFile(in_SourceFile)
{
	m_bOK = true;
}


N2FTALexicalAnalyzer::~N2FTALexicalAnalyzer(void)
{
}


hook_method<N2FTALexicalAnalyzer::FTARet (N2FTALexicalAnalyzer::*)(void)> N2FTALexicalAnalyzer::_Anaysis(SERVER, "N2FTALexicalAnalyzer::Anaysis");
N2FTALexicalAnalyzer::FTARet N2FTALexicalAnalyzer::Anaysis(void)
{
	return (this->*_Anaysis)();

	//TODO
}


hook_method<const bool (N2FTALexicalAnalyzer::*)(void)> N2FTALexicalAnalyzer::_isOK(SERVER, "N2FTALexicalAnalyzer::isOK");
const bool N2FTALexicalAnalyzer::isOK(void)
{
	return (this->*_isOK)();

	return m_bOK;
}


hook_method<N2FTALexicalAnalyzer::FTARet (N2FTALexicalAnalyzer::*)(void)> N2FTALexicalAnalyzer::_ViewToken(SERVER, "N2FTALexicalAnalyzer::ViewToken");
N2FTALexicalAnalyzer::FTARet N2FTALexicalAnalyzer::ViewToken(void)
{
	return (this->*_ViewToken)();

	if( m_Container.size() == 0 )
		m_Container.push_back(this->N2FTALexicalAnalyzer::Anaysis());

	return m_Container.front();
}
