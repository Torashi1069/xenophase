#include "FuncExtraction.h"


CFuncExtraction::CFuncExtraction()
{
}


CFuncExtraction::~CFuncExtraction()
{
}


bool CFuncExtraction::SetData(const char* data)
{
	if( data == NULL )
		return false;

	m_data = data;
	return true;
}


bool CFuncExtraction::GetFuncValue(const char* func, std::vector<CQVar>& value)
{
	if( func == NULL )
		return false;

	value.clear();

	int pos = m_data.CQVar::FindToken(func);
	if( pos == -1 )
		return false;

	CQVar temp;
	if( pos > 0 )
	{
		temp = m_data.CQVar::SubStr(pos - 1, strlen(func) + 1);
		temp.CQVar::Trim_Left();
		if( strcmp(temp.CQVar::o_str(), func) != 0 )
			return true;
	}

	temp = m_data.CQVar::SubStr(pos + strlen(func), 1);
	if( strcmp(temp.CQVar::o_str(), "(") != 0
	 && strcmp(temp.CQVar::o_str(), " ") != 0
	 && strcmp(temp.CQVar::o_str(), "{") != 0 )
		return true;

	int endpos = m_data.CQVar::FindToken("\n"); //FIXME: unexpected value on multi-line data
	if( endpos == -1 )
		endpos = m_data.CQVar::length();
	CQVar data = m_data.CQVar::SubStr(pos, endpos - pos + 1); //FIXME: count may be negative

	int lp = data.CQVar::FindToken("(");
	int rp = data.CQVar::FindToken(")");
	CQVar val = data.CQVar::SubStr(lp + 1, rp - lp - 1);

	while( val.CQVar::length() != 0 )
	{
		CQVar temp = val.CQVar::SpanExcluding(",");
		if( temp.CQVar::length() < 1 )
			temp = val;

		val.CQVar::Delete(temp.CQVar::length() + 1);
		temp.CQVar::Trim_Left();
		temp.CQVar::Trim_Right();

		value.push_back(temp);
	}

	return true;
}
