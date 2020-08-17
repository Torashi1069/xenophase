#pragma once
#include "shared/ODBC.h"


class CExpParameter : public CODBC
{
public:
	CExpParameter();
	virtual ~CExpParameter();

public:
	void Init(const char* script, const char* dbPassword);
	void GetGuildExpParameter();
	int GetGuildNextExp(short level);

public:
	/* this  0 */ //CODBC baseclass_0;
	/* this+20 */ std::map<short,int> m_guildexpValue;
};
