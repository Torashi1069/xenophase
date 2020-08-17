#include "CFTToken.hpp"


CFTToken::CFTToken(const CFTToken& __that)
{
	m_Type = __that.m_Type;
	m_Value = __that.m_Value;
	m_Line = __that.m_Line;
	m_Col = __that.m_Col;
}


CFTToken::CFTToken(const enum CFTToken::enumType in_Type, const mystd::string in_Value, const int in_Line, const int in_Col)
{
	m_Type = in_Type;
	m_Value = in_Value;
	m_Line = in_Line;
	m_Col = in_Col;
}


CFTToken::CFTToken(void)
{
	m_Type = NONE;
	m_Value = "";
	m_Line = 0;
	m_Col = 0;
}


CFTToken::~CFTToken(void)
{
}


hook_method<enum CFTToken::enumType (CFTToken::*)(void)> CFTToken::_GetType(SERVER, "CFTToken::GetType");
enum CFTToken::enumType CFTToken::GetType(void)
{
	return (this->*_GetType)();

	//TODO
}


hook_method<int (CFTToken::*)(void)> CFTToken::_GetINT(SERVER, "CFTToken::GetINT");
int CFTToken::GetINT(void)
{
	return (this->*_GetINT)();

	//TODO
}


hook_method<mystd::string (CFTToken::*)(void)> CFTToken::_GetSTRING(SERVER, "CFTToken::GetSTRING");
mystd::string CFTToken::GetSTRING(void)
{
	return (this->*_GetSTRING)();

	//TODO
}


hook_method<int (CFTToken::*)(void)> CFTToken::_GetLine(SERVER, "CFTToken::GetLine");
int CFTToken::GetLine(void)
{
	return (this->*_GetLine)();

	//TODO
}


hook_method<int (CFTToken::*)(void)> CFTToken::_GetCol(SERVER, "CFTToken::GetCol");
int CFTToken::GetCol(void)
{
	return (this->*_GetCol)();

	//TODO
}
