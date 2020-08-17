#include "shared/N2System/FTA(Formated Text Analyzer)/N2FTAToken.h"


N2FTAToken::N2FTAToken()
: m_Type(TYPE_NONE)
{
}


N2FTAToken::~N2FTAToken()
{
}


N2FTAToken::N2FTAToken(const enumTYPE in_Type, N2FTAVar in_Value, const std::string in_SourceFileName, const int in_SourceFileLine, const int in_SourceFileCol)
: m_Type(in_Type)
{
	m_Value = in_Value;
	m_SourceFileLine = in_SourceFileLine;
	m_SourceFileCol = in_SourceFileCol;
	m_SourceFileName = in_SourceFileName;
}


const int N2FTAToken::GetSourceFileCol() const
{
	return m_SourceFileCol;
}


const int N2FTAToken::GetSourceFileLine() const
{
	return m_SourceFileLine;
}


const std::string N2FTAToken::GetSourceFileName() const
{
	return m_SourceFileName;
}


const N2FTAToken::enumTYPE N2FTAToken::GetType() const
{
	return m_Type;
}


N2FTAVar N2FTAToken::GetValue()
{
	return m_Value;
}
