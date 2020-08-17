#pragma once
#include "ODBC.h"
#include "std/map"
#include "struct.hpp"


class CMVPInfo : public CODBC
{
public:
	/* this+0x0  */ //CODBC
	/* this+0x14 */ mystd::map<unsigned long,MVPINFO *> m_info;

	//public: void CMVPInfo::CMVPInfo(void);
	//public: void CMVPInfo::~CMVPInfo(void);
	public: void CMVPInfo::Reset(void);
	public: void CMVPInfo::LoadInfoFromDB(void);
	public: MVPINFO* CMVPInfo::GetInfo(unsigned long job);
	public: void CMVPInfo::Init(const char* DSN, const char* UID, const char* PASS, const char* DB, char type);
	private: void CMVPInfo::AddInfo(unsigned long job, MVPINFO* info);
private:
	static hook_method<void (CMVPInfo::*)(void)> CMVPInfo::_Reset;
	static hook_method<void (CMVPInfo::*)(void)> CMVPInfo::_LoadInfoFromDB;
	static hook_method<MVPINFO* (CMVPInfo::*)(unsigned long job)> CMVPInfo::_GetInfo;
	static hook_method<void (CMVPInfo::*)(const char* DSN, const char* UID, const char* PASS, const char* DB, char type)> CMVPInfo::_Init;
	static hook_method<void (CMVPInfo::*)(unsigned long job, MVPINFO* info)> CMVPInfo::_AddInfo;
};
