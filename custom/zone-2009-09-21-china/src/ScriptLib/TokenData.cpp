#include "ScriptLib/TokenData.h"


TokenData::TokenData() // line 88-92 (TokenData.h)
{
	this->str = "";
	this->num = 0;
	this->type = 0;
}


TokenData::TokenData(const TokenData& data) // line 95-99 (TokenData.h)
{
	this->str = data.str;
	this->num = data.num;
	this->type = data.type;
}


void TokenData::SetType(int t) // line 264-284
{
	if( this->type == t )
		return;

	switch( t )
	{
	case TokenData::STR:
		this->str = this->TokenData::GetStr();
		this->type = TokenData::STR;
	break;
	case TokenData::NUM:
		this->num = this->TokenData::GetNum();
		this->type = TokenData::NUM;
	break;
	case TokenData::FLOAT:
		this->TokenData::Set(this->TokenData::GetFloat());
		this->type = TokenData::FLOAT;
	break;
	case TokenData::DOUBLE:
		this->TokenData::Set(this->TokenData::GetDouble());
		this->type = TokenData::DOUBLE;
	break;
	default:
	break;
	};
}


void TokenData::Set(const char* s) // line 287-298
{
	if( s != NULL )
		this->str.assign(s);
	else
		this->str.assign("");

	this->type = TokenData::STR;
}


void TokenData::Set(const int n) // line 301-304
{
	this->num = n;
	this->type = TokenData::NUM;
}


void TokenData::Set(const float f) // line 307-312
{
	char temp[1024];
	sprintf(temp, "%f", f);

	this->str = temp;
	this->type = TokenData::NUM;
}


void TokenData::Set(const double d) // line 315-320
{
	char temp[1024];
	sprintf(temp, "%f", d);

	this->str = temp;
	this->type = TokenData::NUM;
}


char* TokenData::GetStr() // line 323-330
{
	if( this->type == TokenData::NUM )
	{
		char temp[1024];
		sprintf(temp, "%d", this->num);
		this->str = temp;
	}

	return (char*)this->str.c_str();
}


int TokenData::GetNum() // line 333-339
{
	if( this->type == TokenData::STR )
	{
		if( this->str.size() == 0 )
			return -1;

		if( this->str.c_str() == "" )
			return -1;

		this->num = atoi(this->str.c_str());
	}

	return this->num;
}


float TokenData::GetFloat() // line 342-348
{
	if( this->type != TokenData::NUM )
	{
		float f;
		sscanf(this->str.c_str(), "%f", &f);
		return f;
	}
	else
	{
		return (float)this->num;
	}
}


double TokenData::GetDouble() // line 351-357
{
	if( this->type != TokenData::NUM )
	{
		double f;
		sscanf(this->str.c_str(), "%f", &f);
		return f;
	}
	else
	{
		return (double)this->num;
	}
}


bool TokenData::IsStr() // line 366-369
{
	return ( this->type == TokenData::STR );
}


void TokenData::operator=(const int n) // line 100-101
{
	this->TokenData::Set(n);
}
