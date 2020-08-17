#pragma once
#include "ODBC.h"
#include "std/map"


class CExpParameter : public CODBC
{
public:
	/* this+0x0  */ //CODBC
	/* this+0x14 */ mystd::map<short,int> m_expValue;
	/* this+0x20 */ mystd::map<short,int> m_jobNoviceExpValue;
	/* this+0x2C */ mystd::map<short,int> m_jobFirstJobExpValue;
	/* this+0x38 */ mystd::map<short,int> m_jobSecondExpValue;
	/* this+0x44 */ mystd::map<short,int> m_guildexpValue;
	/* this+0x50 */ mystd::map<short,int> m_expValue2;
	/* this+0x5C */ mystd::map<short,int> m_jobNoviceExpValue2;
	/* this+0x68 */ mystd::map<short,int> m_jobFirstJobExpValue2;
	/* this+0x74 */ mystd::map<short,int> m_job_Ninja_Gunner_ExpValue;
	/* this+0x80 */ mystd::map<short,int> m_jobSecondExpValue2;
	/* this+0x8C */ mystd::map<short,int> m_expVal_Homun;

	public: CExpParameter::CExpParameter(void);
	public: virtual CExpParameter::~CExpParameter(void);
	public: void CExpParameter::Init(const char* Script);
	public: void CExpParameter::GetExpParameter(void);
	public: int CExpParameter::GetNextExp(short level, short job);
	public: int CExpParameter::GetNextExp(short level);
	public: void CExpParameter::GetNoviceExpParameter(void);
	public: void CExpParameter::GetSecondExpParameter(void);
	public: void CExpParameter::GetFirstJobExpParameter(void);
	public: int CExpParameter::GetNextJobExp(short level, short job);
	public: void CExpParameter::GetGuildExpParameter(void);
	public: int CExpParameter::GetGuildNextExp(short level);
	public: void CExpParameter::GetExpParameter2(void);
	public: void CExpParameter::GetNoviceExpParameter2(void);
	public: void CExpParameter::GetFirstJobExpParameter2(void);
	public: void CExpParameter::Get_Ninja_Gunner_JobExpParameter(void);
	public: void CExpParameter::GetSecondJobExpParameter2(void);
	public: void CExpParameter::InitExpTable_Homun(char* fileName);
	public: int CExpParameter::GetNextExp_Homun(short level);

private:
	static hook_method<void (CExpParameter::*)(const char* Script)> CExpParameter::_Init;
	static hook_method<void (CExpParameter::*)(void)> CExpParameter::_GetExpParameter;
	static hook_method<int (CExpParameter::*)(short level, short job)> CExpParameter::_GetNextExp;
	static hook_method<int (CExpParameter::*)(short level)> CExpParameter::_GetNextExp2;
	static hook_method<void (CExpParameter::*)(void)> CExpParameter::_GetNoviceExpParameter;
	static hook_method<void (CExpParameter::*)(void)> CExpParameter::_GetSecondExpParameter;
	static hook_method<void (CExpParameter::*)(void)> CExpParameter::_GetFirstJobExpParameter;
	static hook_method<int (CExpParameter::*)(short level, short job)> CExpParameter::_GetNextJobExp;
	static hook_method<void (CExpParameter::*)(void)> CExpParameter::_GetGuildExpParameter;
	static hook_method<int (CExpParameter::*)(short level)> CExpParameter::_GetGuildNextExp;
	static hook_method<void (CExpParameter::*)(void)> CExpParameter::_GetExpParameter2;
	static hook_method<void (CExpParameter::*)(void)> CExpParameter::_GetNoviceExpParameter2;
	static hook_method<void (CExpParameter::*)(void)> CExpParameter::_GetFirstJobExpParameter2;
	static hook_method<void (CExpParameter::*)(void)> CExpParameter::_Get_Ninja_Gunner_JobExpParameter;
	static hook_method<void (CExpParameter::*)(void)> CExpParameter::_GetSecondJobExpParameter2;
	static hook_method<void (CExpParameter::*)(char* fileName)> CExpParameter::_InitExpTable_Homun;
	static hook_method<int (CExpParameter::*)(short level)> CExpParameter::_GetNextExp_Homun;
};
