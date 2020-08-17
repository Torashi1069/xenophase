#include "FTToken.h"


CFTToken::CFTToken()
{
	m_Type = CFTToken::NONE;
	m_Value = "";
	m_Line = 0;
	m_Col = 0;
}


CFTToken::CFTToken(const enumType in_Type, const std::string in_Value, const int in_Line, const int in_Col)
{
	m_Type = in_Type;
	m_Value = in_Value;
	m_Line = in_Line;
	m_Col = in_Col;
}


CFTToken::~CFTToken()
{
}


int CFTToken::GetLine() const
{
	return m_Line;
}


int CFTToken::GetCol() const
{
	return m_Col;
}


CFTToken::enumType CFTToken::GetType() const
{
	return m_Type;
}


int CFTToken::GetINT() const
{
	return atoi(m_Value.c_str());
}


bool CFTToken::GetBOOL() const
{
	return ( atoi(m_Value.c_str()) != 0 );
}


std::string CFTToken::GetSTRING() const
{
	return m_Value;
}
