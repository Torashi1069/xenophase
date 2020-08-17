#include "N2System/FTA(Formated Text Analyzer)/N2FTAVar.h"


N2FTAVar::N2FTAVar(void)
{
	m_Type = TYPE_INT;
	m_strData = "";
	m_intData = 0;
	m_floatData = 0.0;
}


N2FTAVar::N2FTAVar(const mystd::string in_strData)
{
	m_Type = TYPE_STRING;
	m_strData = in_strData;
	m_intData = 0;
	m_floatData = 0.0;
}


N2FTAVar::N2FTAVar(const float in_floatData)
{
	m_Type = TYPE_FLOAT;
	m_strData = "";
	m_intData = 0;
	m_floatData = in_floatData;
}


N2FTAVar::N2FTAVar(const int in_intData)
{
	m_Type = TYPE_INT;
	m_strData = "";
	m_intData = in_intData;
	m_floatData = 0.0;
}


N2FTAVar::~N2FTAVar(void)
{
}


N2FTAVar::operator int(void)
{
	switch( m_Type )
	{
	case TYPE_INT   : return (int)m_intData;
	case TYPE_FLOAT : return (int)m_floatData;
	case TYPE_STRING: return (int)atof(m_strData.c_str());
	default         : return (int)0;
	};
}


bool N2FTAVar::operator==(const N2FTAVar& in_rhs)
{
	if( m_Type != in_rhs.m_Type )
		return false;

	switch( m_Type )
	{
	case TYPE_INT   : return( this->m_intData   == in_rhs.m_intData   );
	case TYPE_FLOAT : return( this->m_floatData == in_rhs.m_floatData );
	case TYPE_STRING: return( this->m_strData   == in_rhs.m_strData   );
	default         : return false;
	};
}


bool N2FTAVar::operator!=(const N2FTAVar& in_rhs)
{
	if( m_Type != in_rhs.m_Type )
		return true;

	switch( m_Type )
	{
	case TYPE_INT   : return( this->m_intData   != in_rhs.m_intData   );
	case TYPE_FLOAT : return( this->m_floatData != in_rhs.m_floatData );
	case TYPE_STRING: return( this->m_strData   != in_rhs.m_strData   );
	default         : return true;
	};
}
