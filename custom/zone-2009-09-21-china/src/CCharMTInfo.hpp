#pragma once
#include "std/map"
#include "std/vector"


class CCharMTInfo
{
	/* this+0x0   */ public: // const CCharMTInfo::`vftable';
	/* this+0x4   */ private: int m_attackMTInfo[28][24];
	/* this+0xA84 */ private: int m_attackedMTInfo;
	/* this+0xA88 */ private: mystd::map<unsigned long,mystd::map<int,int> > m_attackMotionTime;
	/* this+0xA94 */ private: mystd::vector<int> m_itemClassList;

	public: CCharMTInfo::CCharMTInfo(void);
	public: virtual CCharMTInfo::~CCharMTInfo(void);
	public: void CCharMTInfo::Init(void);
	public: void CCharMTInfo::LoadAttackMTInfo(void);
	public: void CCharMTInfo::LoadAttackedMTInfo(void);
	public: int CCharMTInfo::GetAttackMT(unsigned long job, unsigned long itemType);
	public: int CCharMTInfo::GetAttackedMT(unsigned long job);
	//private: unsigned long CCharMTInfo::GetJobType(unsigned long);

private:
	static hook_method<void (CCharMTInfo::*)(void)> CCharMTInfo::_Init;
	static hook_method<void (CCharMTInfo::*)(void)> CCharMTInfo::_LoadAttackMTInfo;
	static hook_method<void (CCharMTInfo::*)(void)> CCharMTInfo::_LoadAttackedMTInfo;
	static hook_method<int (CCharMTInfo::*)(unsigned long job, unsigned long itemType)> CCharMTInfo::_GetAttackMT;
	static hook_method<int (CCharMTInfo::*)(unsigned long job)> CCharMTInfo::_GetAttackedMT;
};
