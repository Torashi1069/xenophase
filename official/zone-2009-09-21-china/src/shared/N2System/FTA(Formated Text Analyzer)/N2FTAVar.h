#pragma once
#include "std/string"


class N2FTAVar
{
public:
	enum enumType
	{
		TYPE_INT    = 0,
		TYPE_FLOAT  = 1,
		TYPE_STRING = 2,
	};

	enum
	{
		NUMBER_CONVERT_BUFFER_MAXBYTES = 30
	};

	/* this+0x0  */ //const N2FTAVar::`vftable'
	/* this+0x8  */ private: enum N2FTAVar::enumType m_Type;
	/* this+0xC  */ private: mystd::string m_strData;
	/* this+0x28 */ private: __int64 m_intData;
	/* this+0x30 */ private: double m_floatData;

	public: N2FTAVar::N2FTAVar(void);
	public: N2FTAVar::N2FTAVar(const mystd::string in_strData);
	public: N2FTAVar::N2FTAVar(const float in_floatData);
	public: N2FTAVar::N2FTAVar(const int in_intData);
	public: virtual N2FTAVar::~N2FTAVar(void);
	public: operator int(void);
	//public: float operator float();
	//public: mystd::string();
	//public: N2FTAVar& operator=(const N2FTAVar &);
	//public: void operator=(const mystd::string);
	//public: void operator=(const float);
	//public: void operator=(const int);
	public: bool N2FTAVar::operator==(const N2FTAVar& in_rhs);
	public: bool N2FTAVar::operator!=(const N2FTAVar& in_rhs);
	//public: N2FTAVar operator+(N2FTAVar &);
	//public: N2FTAVar operator-(N2FTAVar &);
	//public: N2FTAVar operator*(N2FTAVar &);
	//public: N2FTAVar operator/(N2FTAVar &);
	//public: N2FTAVar operator%(N2FTAVar &);
};
