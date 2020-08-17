#pragma once
#include "std/map"
#include "std/string"
#include "struct.hpp"


class CStatusPlusInfoByJLV
{
	/* this+ 0 */ public: //const CStatusPlusInfoByJLV::`vftable';
	/* this+ 4 */ private: mystd::map<unsigned long,mystd::map<int,int> > m_statusInfo;
	/* this+16 */ private: mystd::map<unsigned long,mystd::map<int,STATUS> > m_TotalStatusInfo;
	/* this+28 */ private: mystd::map<std::string,unsigned short> m_statID;

	public: CStatusPlusInfoByJLV::CStatusPlusInfoByJLV(void);
	public: virtual CStatusPlusInfoByJLV::~CStatusPlusInfoByJLV(void);
	public: void CStatusPlusInfoByJLV::Init(void);
	public: STATUS* CStatusPlusInfoByJLV::GetResultPlusStatusInfo(unsigned long job, unsigned char level);
	//private: void CStatusPlusInfoByJLV::LoadScript();
	//private: int CStatusPlusInfoByJLV::GetStatEnum(const char *);
	//private: void CStatusPlusInfoByJLV::CalculateResult();

private:
	static hook_method<void (CStatusPlusInfoByJLV::*)(void)> CStatusPlusInfoByJLV::_Init;
	static hook_method<STATUS* (CStatusPlusInfoByJLV::*)(unsigned long job, unsigned char level)> CStatusPlusInfoByJLV::_GetResultPlusStatusInfo;
};
