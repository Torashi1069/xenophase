#pragma once
#include "ODBC.h"
#include "std/map"


class CExpParameter : public CODBC
{
	/* this+0x0  */ //CODBC
	/* this+0x14 */ public: mystd::map<short,int> m_guildexpValue;

	//public: void CExpParameter::CExpParameter();
	//public: void CExpParameter::~CExpParameter();
	public: void CExpParameter::Init(const char* script, const char* dbPassword);
	//public: void CExpParameter::GetGuildExpParameter();
	//public: int CExpParameter::GetGuildNextExp(short);

private:
	static hook_method<void (CExpParameter::*)(const char* script, const char* dbPassword)> CExpParameter::_Init;
};
