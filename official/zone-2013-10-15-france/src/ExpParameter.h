#pragma once
#include "shared/ODBC.h"


class CExpParameter : public CODBC
{
public:
	CExpParameter();
	virtual ~CExpParameter();

public:
	void Init(const char* Script);
	void GetExpParameter();
	void GetNoviceExpParameter();
	void GetSecondExpParameter();
	void GetFirstJobExpParameter();
	int GetNextJobExp(short level, short job);
	void GetGuildExpParameter();
	int GetGuildNextExp(short level);
	int GetNextExp(const short in_level, const short in_job) const;
	void GetExpParameter2();
	void GetNoviceExpParameter2();
	void GetFirstJobExpParameter2();
	void Get_Ninja_Gunner_JobExpParameter();
	void GetSecondJobExpParameter2();
	void GetExpParameter3();
	void GetThirdJobExpParameter();

public:
	/* this+  0 */ //CODBC baseclass_0;
	/* this+ 20 */ std::map<short,int> m_expValue3;
	/* this+ 36 */ std::map<short,int> m_thirdJobExpValue;
	void InitExpTable_Homun(char* fileName);
	int GetNextExp_Homun(const short in_Level, const int in_OwnerJob);
	/* this+ 52 */ std::map<short,int> m_expValue;
	/* this+ 68 */ std::map<short,int> m_jobNoviceExpValue;
	/* this+ 84 */ std::map<short,int> m_jobFirstJobExpValue;
	/* this+100 */ std::map<short,int> m_jobSecondExpValue;
	/* this+116 */ std::map<short,int> m_guildexpValue;
	/* this+132 */ std::map<short,int> m_expValue2;
	/* this+148 */ std::map<short,int> m_jobNoviceExpValue2;
	/* this+164 */ std::map<short,int> m_jobFirstJobExpValue2;
	/* this+180 */ std::map<short,int> m_job_Ninja_Gunner_ExpValue;
	/* this+196 */ std::map<short,int> m_jobSecondExpValue2;
	/* this+212 */ std::map<short,int> m_expVal_Homun;
};
