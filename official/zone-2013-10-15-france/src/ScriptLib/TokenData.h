#pragma once


struct TokenData
{
	enum
	{
		NUM    = 0,
		STR    = 1,
		FLOAT  = 2,
		DOUBLE = 3,
	};

	/* this+ 0 */ std::string str;
	/* this+28 */ int num;
	/* this+32 */ char type;

	TokenData();
	TokenData(const TokenData& data);
	void SetType(int t);

	void Set(const char* s);
	void Set(const int n);
	void Set(const float f);
	void Set(const double d);

	char* GetStr();
	int GetNum();
	float GetFloat();
	double GetDouble();

	bool IsNum();
	bool IsStr();
	bool IsFloat(); //TODO

	operator char*();
	operator const char*();
	operator int();
	operator float();
	operator double();

	TokenData& operator+(TokenData& tokenData);
	TokenData& operator-(TokenData& tokenData);
	TokenData& operator*(TokenData& tokenData);
	TokenData& operator/(TokenData& tokenData);
	TokenData& operator%(TokenData& tokenData);

	TokenData& operator++(int);
	TokenData& operator++();
	TokenData& operator--(int);
	TokenData& operator--();

	void operator=(const int n);
	void operator=(const char* s);
	void operator=(const float f);
	void operator=(const double d);
	void operator=(std::string& s);
	void operator=(const TokenData& data);

	void operator+=(TokenData& tokenData);
	void operator-=(TokenData& tokenData);
	void operator*=(TokenData& tokenData);
	void operator/=(TokenData& tokenData);
	void operator%=(TokenData& tokenData);

	bool operator==(TokenData& tokenData);
	bool operator>=(TokenData& tokenData);
	bool operator<=(TokenData& tokenData);
	bool operator!=(TokenData& tokenData);
	bool operator> (TokenData& tokenData);
	bool operator< (TokenData& tokenData);
	bool operator&&(TokenData& tokenData);
	bool operator||(TokenData& tokenData);
};
