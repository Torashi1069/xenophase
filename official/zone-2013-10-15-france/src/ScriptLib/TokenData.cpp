#include "ScriptLib/TokenData.h"


TokenData::TokenData()
{
	this->str = "";
	this->num = 0;
	this->type = 0;
}


TokenData::TokenData(const TokenData& data)
{
	this->str = data.str;
	this->num = data.num;
	this->type = data.type;
}


void TokenData::operator=(const TokenData& data)
{
	this->str = data.str;
	this->num = data.num;
	this->type = data.type;
}


bool TokenData::operator&&(TokenData& tokenData)
{
	switch( this->type )
	{
	case TokenData::NUM:
		return ( this->TokenData::GetNum() != 0 && tokenData.TokenData::GetNum() != 0 );
	break;
	case TokenData::STR:
		return ( this->TokenData::GetStr()[0] != '\0' && tokenData.TokenData::GetStr()[0] != '\0' );
	break;
	case TokenData::FLOAT:
		return ( this->TokenData::GetFloat() != 0.0f && tokenData.TokenData::GetFloat() != 0.0f );
	break;
	case TokenData::DOUBLE:
		return ( this->TokenData::GetDouble() != 0.0L && tokenData.TokenData::GetDouble() != 0.0L );
	break;
	default:
		return false;
	break;
	};
}


bool TokenData::operator||(TokenData& tokenData)
{
	switch( this->type )
	{
	case TokenData::NUM:
		return ( this->TokenData::GetNum() != 0 || tokenData.TokenData::GetNum() != 0 );
	break;
	case TokenData::STR:
		return ( this->TokenData::GetStr()[0] != '\0' || tokenData.TokenData::GetStr()[0] != '\0' );
	break;
	case TokenData::FLOAT:
		return ( this->TokenData::GetFloat() != 0.0f || tokenData.TokenData::GetFloat() != 0.0f );
	break;
	case TokenData::DOUBLE:
		return ( this->TokenData::GetDouble() != 0.0L || tokenData.TokenData::GetDouble() != 0.0L );
	break;
	default:
		return false;
	break;
	};
}


bool TokenData::operator==(TokenData& tokenData)
{
	switch( this->type )
	{
	case TokenData::NUM:
		return ( this->TokenData::GetNum() == tokenData.TokenData::GetNum() );
	break;
	case TokenData::STR:
		return ( strcmp(this->TokenData::GetStr(), tokenData.TokenData::GetStr()) == 0 );
	break;
	case TokenData::FLOAT:
		return ( this->TokenData::GetFloat() == tokenData.TokenData::GetFloat() );
	break;
	case TokenData::DOUBLE:
		return ( this->TokenData::GetDouble() == tokenData.TokenData::GetDouble() );
	break;
	default:
		return false;
	break;
	};
}


bool TokenData::operator>=(TokenData& tokenData)
{
	switch( this->type )
	{
	case TokenData::NUM:
		return ( this->TokenData::GetNum() >= tokenData.TokenData::GetNum() );
	break;
	case TokenData::STR:
		return ( strcmp(this->TokenData::GetStr(), tokenData.TokenData::GetStr()) >= 0 );
	break;
	case TokenData::FLOAT:
		return ( this->TokenData::GetFloat() >= tokenData.TokenData::GetFloat() );
	break;
	case TokenData::DOUBLE:
		return ( this->TokenData::GetDouble() >= tokenData.TokenData::GetDouble() );
	break;
	default:
		return false;
	break;
	};
}


bool TokenData::operator<=(TokenData& tokenData)
{
	switch( this->type )
	{
	case TokenData::NUM:
		return ( this->TokenData::GetNum() <= tokenData.TokenData::GetNum() );
	break;
	case TokenData::STR:
		return ( strcmp(this->TokenData::GetStr(), tokenData.TokenData::GetStr()) <= 0 );
	break;
	case TokenData::FLOAT:
		return ( this->TokenData::GetFloat() <= tokenData.TokenData::GetFloat() );
	break;
	case TokenData::DOUBLE:
		return ( this->TokenData::GetDouble() <= tokenData.TokenData::GetDouble() );
	break;
	default:
		return false;
	break;
	};
}


bool TokenData::operator!=(TokenData& tokenData)
{
	switch( this->type )
	{
	case TokenData::NUM:
		return ( this->TokenData::GetNum() != tokenData.TokenData::GetNum() );
	break;
	case TokenData::STR:
		return ( strcmp(this->TokenData::GetStr(), tokenData.TokenData::GetStr()) != 0 );
	break;
	case TokenData::FLOAT:
		return ( this->TokenData::GetFloat() != tokenData.TokenData::GetFloat() );
	break;
	case TokenData::DOUBLE:
		return ( this->TokenData::GetDouble() != tokenData.TokenData::GetDouble() );
	break;
	default:
		return false;
	break;
	};
}


bool TokenData::operator>(TokenData& tokenData)
{
	switch( this->type )
	{
	case TokenData::NUM:
		return ( this->TokenData::GetNum() > tokenData.TokenData::GetNum() );
	break;
	case TokenData::STR:
		return ( strcmp(this->TokenData::GetStr(), tokenData.TokenData::GetStr()) > 0 );
	break;
	case TokenData::FLOAT:
		return ( this->TokenData::GetFloat() > tokenData.TokenData::GetFloat() );
	break;
	case TokenData::DOUBLE:
		return ( this->TokenData::GetDouble() > tokenData.TokenData::GetDouble() );
	break;
	default:
		return false;
	break;
	};
}


bool TokenData::operator<(TokenData& tokenData)
{
	switch( this->type )
	{
	case TokenData::NUM:
		return ( this->TokenData::GetNum() < tokenData.TokenData::GetNum() );
	break;
	case TokenData::STR:
		return ( strcmp(this->TokenData::GetStr(), tokenData.TokenData::GetStr()) < 0 );
	break;
	case TokenData::FLOAT:
		return ( this->TokenData::GetFloat() < tokenData.TokenData::GetFloat() );
	break;
	case TokenData::DOUBLE:
		return ( this->TokenData::GetDouble() < tokenData.TokenData::GetDouble() );
	break;
	default:
		return false;
	break;
	};
}


void TokenData::operator=(const int n)
{
	this->TokenData::Set(n);
}


void TokenData::operator=(const char* s)
{
	this->TokenData::Set(s);
}

	
void TokenData::operator=(std::string& s)
{
	this->TokenData::Set(s.c_str());
}


void TokenData::operator=(const float f)
{
	this->TokenData::Set(f);
}


void TokenData::operator=(const double d)
{
	this->TokenData::Set(d);
}


void TokenData::operator+=(TokenData& tokenData)
{
	this->TokenData::operator=(this->TokenData::operator+(tokenData));
}


void TokenData::operator-=(TokenData& tokenData)
{
	this->TokenData::operator=(this->TokenData::operator-(tokenData));
}


void TokenData::operator*=(TokenData& tokenData)
{
	this->TokenData::operator=(this->TokenData::operator*(tokenData));
}


void TokenData::operator/=(TokenData& tokenData)
{
	this->TokenData::operator=(this->TokenData::operator/(tokenData));
}


void TokenData::operator%=(TokenData& tokenData)
{
	this->TokenData::operator=(this->TokenData::operator%(tokenData));
}


TokenData& TokenData::operator%(TokenData& tokenData)
{
	switch( this->type )
	{
	case TokenData::NUM:
		this->num %= tokenData.TokenData::GetNum();
	break;
	case TokenData::STR:
		// not applicable
	break;
	case TokenData::FLOAT:
		// not implemented
	break;
	case TokenData::DOUBLE:
		// not implemented
	break;
	};

	return *this;
}


TokenData& TokenData::operator+(TokenData& tokenData)
{
	switch( this->type )
	{
	case TokenData::NUM:
		this->num += tokenData.TokenData::GetNum();
	break;
	case TokenData::STR:
		this->str += tokenData.TokenData::GetStr();
	break;
	case TokenData::FLOAT:
		this->TokenData::Set(this->TokenData::GetFloat() + tokenData.TokenData::GetFloat());
	break;
	case TokenData::DOUBLE:
		this->TokenData::Set(this->TokenData::GetDouble() + tokenData.TokenData::GetDouble());
	break;
	}

	return *this;
}


TokenData& TokenData::operator-(TokenData& tokenData)
{
	switch( this->type )
	{
	case TokenData::NUM:
		this->num -= tokenData.TokenData::GetNum();
	break;
	case TokenData::STR:
		// not applicable
	break;
	case TokenData::FLOAT:
		this->TokenData::Set(this->TokenData::GetFloat() - tokenData.TokenData::GetFloat());
	break;
	case TokenData::DOUBLE:
		this->TokenData::Set(this->TokenData::GetDouble() - tokenData.TokenData::GetDouble());
	break;
	};

	return *this;
}


TokenData& TokenData::operator*(TokenData& tokenData)
{
	switch( this->type )
	{
	case TokenData::NUM:
		this->num *= tokenData.TokenData::GetNum();
	break;
	case TokenData::STR:
		// not applicable
	break;
	case TokenData::FLOAT:
		this->TokenData::Set(this->TokenData::GetFloat() * tokenData.TokenData::GetFloat());
	break;
	case TokenData::DOUBLE:
		this->TokenData::Set(this->TokenData::GetDouble() * tokenData.TokenData::GetDouble());
	break;
	};

	return *this;
}


TokenData& TokenData::operator/(TokenData& tokenData)
{
	switch( this->type )
	{
	case TokenData::NUM:
	{
		int n = tokenData.TokenData::GetNum();
		if( n != 0 )
			this->num /= n;
	}
	break;
	case TokenData::STR:
	{
		// not applicable
	}
	break;
	case TokenData::FLOAT:
	{
		float f = tokenData.TokenData::GetFloat();
		if( f != 0.0f )
			this->TokenData::Set(this->TokenData::GetFloat() / f);
	}
	break;
	case TokenData::DOUBLE:
	{
		double d = tokenData.TokenData::GetDouble();
		if( d != 0.0L )
			this->TokenData::Set(this->TokenData::GetDouble() / d);
	}
	break;
	};

	return *this;
}


TokenData& TokenData::operator++(int)
{
	if( this->type == TokenData::NUM )
		++this->num;

	return *this;
}


TokenData& TokenData::operator++()
{
	if( this->type == TokenData::NUM )
		++this->num;

	return *this;
}


TokenData& TokenData::operator--(int)
{
	if( this->type == TokenData::NUM )
		--this->num;

	return *this;
}


TokenData& TokenData::operator--()
{
	if( this->type == TokenData::NUM )
		--this->num;

	return *this;
}


void TokenData::SetType(int t)
{
	if( this->type == t )
		return; // no change

	switch( t )
	{
	case TokenData::NUM:
		this->num = this->TokenData::GetNum();
		this->type = TokenData::NUM;
	break;
	case TokenData::STR:
		this->str = this->TokenData::GetStr();
		this->type = TokenData::STR;
	break;
	case TokenData::FLOAT:
		this->TokenData::Set(this->TokenData::GetFloat());
		this->type = TokenData::FLOAT;
	break;
	case TokenData::DOUBLE:
		this->TokenData::Set(this->TokenData::GetDouble());
		this->type = TokenData::DOUBLE;
	break;
	};
}


void TokenData::Set(const char* s)
{
	if( s == NULL )
		s = "";

	this->str = s;
	this->type = TokenData::STR;
}


void TokenData::Set(const int n)
{
	this->num = n;
	this->type = TokenData::NUM;
}


void TokenData::Set(const float f)
{
	char temp[1024];
	sprintf_s(temp, countof(temp), "%f", f);

	this->str = temp;
	this->type = TokenData::NUM;
}


void TokenData::Set(const double d)
{
	char temp[1024];
	sprintf_s(temp, countof(temp), "%f", d);

	this->str = temp;
	this->type = TokenData::NUM;
}


char* TokenData::GetStr()
{
	if( this->type == TokenData::NUM )
	{
		char temp[1024];
		sprintf_s(temp, countof(temp), "%d", this->num);
		this->str = temp;
	}

	return const_cast<char*>(this->str.c_str());
}


int TokenData::GetNum()
{
	if( this->type == TokenData::STR )
	{
		if( this->str.c_str() == NULL || this->str.c_str() == "" )
			return -1;

		this->num = atoi(this->str.c_str());
	}

	return this->num;
}


float TokenData::GetFloat()
{
	if( this->type != TokenData::NUM )
	{
		float f;
		sscanf(this->str.c_str(), "%f", &f);
		return f;
	}
	else
	{
		return static_cast<float>(this->num);
	}
}


double TokenData::GetDouble()
{
	if( this->type != TokenData::NUM )
	{
		double f;
		sscanf(this->str.c_str(), "%f", &f);
		return f;
	}
	else
	{
		return static_cast<double>(this->num);
	}
}


bool TokenData::IsNum()
{
	return ( this->type == TokenData::NUM );
}


bool TokenData::IsStr()
{
	return ( this->type == TokenData::STR );
}


TokenData::operator char*()
{
	return this->TokenData::GetStr();
}


TokenData::operator const char*()
{
	return this->TokenData::GetStr();
}


TokenData::operator int()
{
	return this->TokenData::GetNum();
}


TokenData::operator float()
{
	return this->TokenData::GetFloat();
}


TokenData::operator double()
{
	return this->TokenData::GetDouble();
}
