#pragma once


class N2FTAVar
{
private:
	enum enumType
	{
		TYPE_INT    = 0,
		TYPE_FLOAT  = 1,
		TYPE_STRING = 2,
	};

	enum { NUMBER_CONVERT_BUFFER_MAXBYTES = 30 };

private:
	/* this+ 0 */ //const N2FTAVar::`vftable';
	/* this+ 8 */ enumType m_Type;
	/* this+12 */ std::string m_strData;
	/* this+40 */ __int64 m_intData;
	/* this+48 */ double m_floatData;

public:
	operator int();
	operator float();
	operator std::string();
	void operator=(const int in_intData);
	void operator=(const float in_floatData);
	void operator=(const std::string in_strData);
	bool operator==(const N2FTAVar& in_rhs);
	bool operator!=(const N2FTAVar& in_rhs);
	N2FTAVar operator+(N2FTAVar& in_Var) const;
	N2FTAVar operator-(N2FTAVar& in_Var) const;
	N2FTAVar operator*(N2FTAVar& in_Var) const;
	N2FTAVar operator/(N2FTAVar& in_Var) const;
	N2FTAVar operator%(N2FTAVar& in_Var) const;

public:
	N2FTAVar();
	N2FTAVar(const int in_intData);
	N2FTAVar(const float in_floatData);
	N2FTAVar(const std::string in_strData);
	virtual ~N2FTAVar();
};
