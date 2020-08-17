#include "N2System/FTA(Formated Text Analyzer)/N2FTAToken.h"


N2FTAToken::N2FTAToken(const enum N2FTAToken::enumTYPE in_Type, N2FTAVar in_Value, const mystd::string in_SourceFileName, const int in_SourceFileLine, const int in_SourceFileCol)
{
	m_Type = in_Type;
	m_Value = in_Value;
	m_SourceFileLine = in_SourceFileLine;
	m_SourceFileCol = in_SourceFileCol;
	m_SourceFileName = in_SourceFileName;
}


N2FTAToken::N2FTAToken(void)
{
	m_Type = TYPE_NONE;
}


N2FTAToken::~N2FTAToken(void)
{
}


//hook_method<const int (N2FTAToken::*)(void)> N2FTAToken::_GetSourceFileCol(SERVER, "N2FTAToken::GetSourceFileCol");
const int N2FTAToken::GetSourceFileCol(void)
{
//	return (this->*_GetSourceFileCol)();

	return m_SourceFileCol;
}


//hook_method<const int (N2FTAToken::*)(void)> N2FTAToken::_GetSourceFileLine(SERVER, "N2FTAToken::GetSourceFileLine");
const int N2FTAToken::GetSourceFileLine(void)
{
//	return (this->*_GetSourceFileLine)();

	return m_SourceFileLine;
}


hook_method<const mystd::string (N2FTAToken::*)(void)> N2FTAToken::_GetSourceFileName(SERVER, "N2FTAToken::GetSourceFileName");
const mystd::string N2FTAToken::GetSourceFileName(void)
{
	return (this->*_GetSourceFileName)();

	return m_SourceFileName;
}


//hook_method<const enum N2FTAToken::enumTYPE (N2FTAToken::*)(void)> N2FTAToken::_GetType(SERVER, "N2FTAToken::GetType");
const enum N2FTAToken::enumTYPE N2FTAToken::GetType(void)
{
//	return (this->*_GetType)();

	return m_Type;
}


hook_method<N2FTAVar (N2FTAToken::*)(void)> N2FTAToken::_GetValue(SERVER, "N2FTAToken::GetValue");
N2FTAVar N2FTAToken::GetValue(void)
{
	return (this->*_GetValue)();

	return m_Value;
}
