#pragma once
#include "std/string"


struct TokenData
{
	enum
	{
		NUM    = 0,
		STR    = 1,
		FLOAT  = 2,
		DOUBLE = 3,
	};

	/* this+ 0 */ mystd::string str;
	/* this+28 */ int num;
	/* this+32 */ char type;

	TokenData(); // line 88-92
	TokenData(const TokenData& data); // line 95-99
	void SetType(int t);
	void Set(const char* s);
	void Set(const int n);
	void Set(const float f);
	void Set(const double d);
	char* GetStr();
	int TokenData::GetNum();
	float GetFloat();
	double GetDouble();
	//bool IsNum();
	public: bool IsStr();
	//bool IsFloat();
	//operator char*();
	//operator const char*();
	//operator int();
	//operator float();
	//operator double();
	//TokenData& operator+(TokenData&);
	//TokenData& operator-(TokenData&);
	//TokenData& operator*(TokenData&);
	//TokenData& operator/(TokenData&);
	//TokenData& operator%(TokenData&);
	//TokenData& operator++();
	//TokenData& operator++(int);
	//TokenData& operator--();
	//TokenData& operator--(int);
	void operator=(const int n);
	//void operator=(const char*);
	//void operator=(const float);
	//void operator=(const double);
	//void operator=(mystd::string&);
	//void operator=(const TokenData&);
	//void operator+=(TokenData&);
	//void operator-=(TokenData&);
	//void operator*=(TokenData&);
	//void operator/=(TokenData&);
	//void operator%=(TokenData&);
	//bool operator==(TokenData&);
	//bool operator>=(TokenData&);
	//bool operator<=(TokenData&);
	//bool operator!=(TokenData&);
	//bool operator>(TokenData&);
	//bool operator<(TokenData&);
	//bool operator&&(TokenData&);
	//bool operator||(TokenData&);
};
