#include "shared/N2System/FTA(Formated Text Analyzer)/N2FTAVar.h"


N2FTAVar::N2FTAVar()
: m_Type(TYPE_INT), m_strData(""), m_intData(0), m_floatData(0)
{
}


N2FTAVar::N2FTAVar(const int in_intData)
: m_Type(TYPE_INT), m_strData(""), m_intData(in_intData), m_floatData(0)
{
}


N2FTAVar::N2FTAVar(const float in_floatData)
: m_Type(TYPE_FLOAT), m_strData(""), m_intData(0), m_floatData(in_floatData)
{
}


N2FTAVar::N2FTAVar(const std::string in_strData)
: m_Type(TYPE_STRING), m_strData(in_strData), m_intData(0), m_floatData(0)
{
}


N2FTAVar::~N2FTAVar()
{
}


N2FTAVar::operator int()
{
	switch( m_Type )
	{
	case TYPE_INT   : return (int)m_intData;
	case TYPE_FLOAT : return (int)m_floatData;
	case TYPE_STRING: return (int)atof(m_strData.c_str());
	default         : return (int)0;
	};
}


N2FTAVar::operator float()
{
	switch( m_Type )
	{
	case TYPE_INT   : return (float)m_intData;
	case TYPE_FLOAT : return (float)m_floatData;
	case TYPE_STRING: return (float)atof(m_strData.c_str());
	default         : return (float)0;
	};
}


N2FTAVar::operator std::string()
{
	char buffer[NUMBER_CONVERT_BUFFER_MAXBYTES] = {};

	switch( m_Type )
	{
	case TYPE_INT   : _snprintf(buffer, countof(buffer), "%I64d", m_intData); return buffer;
	case TYPE_FLOAT : _snprintf(buffer, countof(buffer), "%lf", m_floatData); return buffer;
	case TYPE_STRING: return m_strData;
	default         : return "";
	};
}


void N2FTAVar::operator=(const int in_intData)
{
	m_Type = TYPE_INT;
	m_intData = in_intData;
}


void N2FTAVar::operator=(const float in_floatData)
{
	m_Type = TYPE_FLOAT;
	m_floatData = in_floatData;
}


void N2FTAVar::operator=(const std::string in_strData)
{
	m_Type = TYPE_STRING;
	m_strData = in_strData;
}


N2FTAVar N2FTAVar::operator+(N2FTAVar& in_Var) const
{
	N2FTAVar result = *const_cast<N2FTAVar*>(this);

	switch( m_Type )
	{
	case TYPE_INT   : result.m_intData += static_cast<int>(in_Var); break;
	case TYPE_FLOAT : result.m_floatData += static_cast<float>(in_Var); break;
	case TYPE_STRING: result.m_strData += static_cast<std::string>(in_Var); break;
	};

	return result;
}


N2FTAVar N2FTAVar::operator-(N2FTAVar& in_Var) const
{
	N2FTAVar result = *const_cast<N2FTAVar*>(this);

	switch( m_Type )
	{
	case TYPE_INT  : result.m_intData -= static_cast<int>(in_Var); break;
	case TYPE_FLOAT: result.m_floatData -= static_cast<float>(in_Var); break;
	};
		
	return result;
}


N2FTAVar N2FTAVar::operator*(N2FTAVar& in_Var) const
{
	N2FTAVar result = *const_cast<N2FTAVar*>(this);

	switch( m_Type )
	{
	case TYPE_INT  : result.m_intData *= static_cast<int>(in_Var); break;
	case TYPE_FLOAT: result.m_floatData *= static_cast<float>(in_Var); break;
	};

	return result;
}


N2FTAVar N2FTAVar::operator/(N2FTAVar& in_Var) const
{
	N2FTAVar result = *const_cast<N2FTAVar*>(this);

	switch( m_Type )
	{
	case TYPE_INT  : result.m_intData /= static_cast<int>(in_Var); break;
	case TYPE_FLOAT: result.m_floatData /= static_cast<float>(in_Var); break;
	};

	return result;
}


N2FTAVar N2FTAVar::operator%(N2FTAVar& in_Var) const
{
	N2FTAVar result = *const_cast<N2FTAVar*>(this);

	switch( m_Type )
	{
	case TYPE_INT: result.m_intData %= static_cast<int>(in_Var); break;
	};

	return result;
}


bool N2FTAVar::operator==(const N2FTAVar& in_rhs)
{
	if( m_Type != in_rhs.m_Type )
		return false;

	switch( m_Type )
	{
	case TYPE_INT   : return ( m_intData == in_rhs.m_intData );
	case TYPE_FLOAT : return ( m_floatData == in_rhs.m_floatData );
	case TYPE_STRING: return ( m_strData == in_rhs.m_strData );
	default         : return false;
	};
}


bool N2FTAVar::operator!=(const N2FTAVar& in_rhs)
{
	if( m_Type != in_rhs.m_Type )
		return true;

	switch( m_Type )
	{
	case TYPE_INT   : return ( m_intData != in_rhs.m_intData );
	case TYPE_FLOAT : return ( m_floatData != in_rhs.m_floatData );
	case TYPE_STRING: return ( m_strData != in_rhs.m_strData );
	default         : return true;
	};
}
