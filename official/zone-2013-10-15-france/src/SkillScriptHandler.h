#pragma once
#include "ScriptEventHandler.h"
class CSkillTypeInfo;
class CSkillTypeInfo2;


struct STRUCT_SK_EVENT
{
	/* this+0 */ std::map<unsigned long,void*> infoMap;
};


struct STRUCT_SK_SPLASH
{
	/* this+0 */ unsigned char shape;
	/* this+4 */ int range[20];
};


struct STRUCT_SK_HANDICAP
{
	/* this+ 0 */ unsigned char handicapType;
	/* this+ 4 */ int percent[10];
	/* this+44 */ int time[10];
};


struct STRUCT_SK_INTVALUE
{
	/* this+0 */ int value[10];
};


struct STRUCT_SK_STRINGVALUE
{
	/* this+0 */ std::string value[10];
};


class CSkillScriptHandler : public CScriptEventHandler
{
public:
	CSkillScriptHandler();

public:
	bool Run(CBinBuf* binBuf);
	virtual bool OnFunc(int func, std::deque<TokenData>& parm, TokenData& ret);
	void EventLog(char* str, ...);

private:
	bool IsDuplicate(int func);
	void* GetEventCase();
	bool FuncSetSkill(int SKID);
	bool FuncOnEvent(int event);
	bool FuncSkillSplash(std::deque<TokenData>& parm);
	bool FuncSkillCommonIntValue(int func, std::deque<TokenData>& parm);
	bool FuncSkillHandicap(std::deque<TokenData>& parm);
	bool FuncSkillKnockBack(std::deque<TokenData>& parm);
	bool FuncSkillNoDamage();
	bool FuncSkillResetHandicap(std::deque<TokenData>& parm);
	bool FuncSkillEventIntValue(int func, std::deque<TokenData>& parm, const char* errorMsg);
	bool FuncSkillSetInfo(std::deque<TokenData>& parm, void (CSkillTypeInfo::* func)(short skLevel, int time));
	bool FuncSkillStringValue(std::deque<TokenData>& parm);

private:
	/* this+120 */ CSkillTypeInfo2* m_skillTypeInfo;
	/* this+124 */ bool m_isError;
	/* this+128 */ int m_eventCase;
};
