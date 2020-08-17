#include "shared/N2System/FTA(Formated Text Analyzer)/N2FTAVar.h"


N2FTAVar::N2FTAVar()
: m_Type(TYPE_INT)
{
	m_strData = "";
	m_intData = 0;
	m_floatData = 0.0;
}


N2FTAVar::N2FTAVar(const int in_intData)
{
	m_Type = TYPE_INT;
	m_strData = "";
	m_intData = in_intData;
	m_floatData = 0.0;
}


N2FTAVar::N2FTAVar(const float in_floatData)
{

	m_Type = TYPE_FLOAT;
	m_strData = "";
	m_intData = 0;
	m_floatData = in_floatData;
}


N2FTAVar::N2FTAVar(const std::string in_strData)
{
	m_Type = TYPE_STRING;
	m_strData = in_strData;
	m_intData = 0;
	m_floatData = 0.0;
}


N2FTAVar::~N2FTAVar()
{
}


N2FTAVar::operator int()
{
	switch( m_Type )
	{
	case TYPE_INT:
		return static_cast<int>(m_intData);
	break;
	case TYPE_FLOAT:
		return static_cast<int>(m_floatData);
	break;
	case TYPE_STRING:
		return static_cast<int>(atof(m_strData.c_str()));
	break;
	default:
		return 0;
	break;
	};
}


N2FTAVar::operator float()
{
	switch( m_Type )
	{
	case TYPE_INT:
		return static_cast<float>(m_intData);
	break;
	case TYPE_FLOAT:
		return static_cast<float>(m_floatData);
	break;
	case TYPE_STRING:
		return static_cast<float>(atof(m_strData.c_str()));
	break;
	default:
		return 0.0;
	break;
	};
}


N2FTAVar::operator std::string()
{
	char buffer[30] = {};

	switch( m_Type )
	{
	case TYPE_INT:
		_snprintf(buffer, countof(buffer), "%I64d", m_intData);
		return buffer;
	break;
	case TYPE_FLOAT:
		_snprintf(buffer, countof(buffer), "%lf", m_floatData);
		return buffer;
	break;
	case TYPE_STRING:
		return m_strData;
	break;
	default:
		return "";
	break;
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

	switch( result.m_Type )
	{
	case TYPE_INT:
		result.m_intData += static_cast<int>(in_Var);
	break;
	case TYPE_FLOAT:
		result.m_floatData += static_cast<float>(in_Var);
	break;
	case TYPE_STRING:
		result.m_strData += static_cast<std::string>(in_Var);
	break;
	};

	return result;
}


N2FTAVar N2FTAVar::operator-(N2FTAVar& in_Var) const
{
	N2FTAVar result = *const_cast<N2FTAVar*>(this);

	switch( result.m_Type )
	{
	case TYPE_INT:
		result.m_intData -= static_cast<int>(in_Var);
	break;
	case TYPE_FLOAT:
		result.m_floatData -= static_cast<float>(in_Var);
	break;
	default:
		;
	break;
	};

	return result;
}


N2FTAVar N2FTAVar::operator*(N2FTAVar& in_Var) const
{
	N2FTAVar result = *const_cast<N2FTAVar*>(this);

	switch( result.m_Type )
	{
	case TYPE_INT:
		result.m_intData *= static_cast<int>(in_Var);
	break;
	case TYPE_FLOAT:
		result.m_floatData *= static_cast<float>(in_Var);
	break;
	};

	return result;
}


N2FTAVar N2FTAVar::operator/(N2FTAVar& in_Var) const
{
	N2FTAVar result = *const_cast<N2FTAVar*>(this);

	switch( result.m_Type )
	{
	case TYPE_INT:
		result.m_intData /= static_cast<int>(in_Var);
	break;
	case TYPE_FLOAT:
		result.m_floatData /= static_cast<float>(in_Var);
	break;
	};

	return result;
}


N2FTAVar N2FTAVar::operator%(N2FTAVar& in_Var) const
{
	N2FTAVar result = *const_cast<N2FTAVar*>(this);

	switch( result.m_Type )
	{
	case TYPE_INT:
		result.m_intData %= static_cast<int>(in_Var);
	break;
	};

	return result;
}


bool N2FTAVar::operator==(const N2FTAVar& in_rhs)
{
	if( m_Type != in_rhs.m_Type )
		return false;

	switch( m_Type )
	{
	case TYPE_INT:
		return ( m_intData == in_rhs.m_intData );
	break;
	case TYPE_FLOAT:
		return ( m_floatData == in_rhs.m_floatData );
	break;
	case TYPE_STRING:
		return ( m_strData == in_rhs.m_strData );
	break;
	default:
		return false;
	break;
	};
}


bool N2FTAVar::operator!=(const N2FTAVar& in_rhs)
{
	if( m_Type != in_rhs.m_Type )
		return true;

	switch( m_Type )
	{
	case TYPE_INT:
		return ( m_intData != in_rhs.m_intData );
	break;
	case TYPE_FLOAT:
		return ( m_floatData != in_rhs.m_floatData );
	break;
	case TYPE_STRING:
		return ( m_strData != in_rhs.m_strData );
	break;
	default:
		return true;
	break;
	};
}
