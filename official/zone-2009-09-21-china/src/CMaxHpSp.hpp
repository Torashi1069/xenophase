#pragma once
#include "std/map"


class CMaxHpSp
{
	/* this+0x0    */ public: //const CMaxHpSp::`vftable';
	/* this+0x4    */ private: int m_maxSp[101][21];
	/* this+0x2128 */ private: int m_maxHp[101][21];
	/* this+0x424C */ private: mystd::map<unsigned long,mystd::map<int,int> > m_maxSPValue;
	/* this+0x4258 */ private: mystd::map<unsigned long,mystd::map<int,int> > m_maxHPValue;

	public: CMaxHpSp::CMaxHpSp(void);
	public: virtual CMaxHpSp::~CMaxHpSp(void);
	public: void CMaxHpSp::Init(void);
	public: int CMaxHpSp::LoadSp(void);
	public: int CMaxHpSp::LoadHp(void);
	public: int CMaxHpSp::GetSp(int nJob, int nLevel);
	public: int CMaxHpSp::GetHp(int nJob, int nLevel);
	public: int CMaxHpSp::LoadMaxHPSP(void);
	public: int CMaxHpSp::LoadSp2(void);
	public: int CMaxHpSp::LoadHp2(void);
	public: int CMaxHpSp::GetSp2(int nJob, int nLevel);
	public: int CMaxHpSp::GetHp2(int nJob, int nLevel);

private:
	static hook_method<void (CMaxHpSp::*)(void)> CMaxHpSp::_Init;
	static hook_method<int (CMaxHpSp::*)(void)> CMaxHpSp::_LoadSp;
	static hook_method<int (CMaxHpSp::*)(void)> CMaxHpSp::_LoadHp;
	static hook_method<int (CMaxHpSp::*)(int nJob, int nLevel)> CMaxHpSp::_GetSp;
	static hook_method<int (CMaxHpSp::*)(int nJob, int nLevel)> CMaxHpSp::_GetHp;
	static hook_method<int (CMaxHpSp::*)(void)> CMaxHpSp::_LoadMaxHPSP;
	static hook_method<int (CMaxHpSp::*)(void)> CMaxHpSp::_LoadSp2;
	static hook_method<int (CMaxHpSp::*)(void)> CMaxHpSp::_LoadHp2;
	static hook_method<int (CMaxHpSp::*)(int nJob, int nLevel)> CMaxHpSp::_GetSp2;
	static hook_method<int (CMaxHpSp::*)(int nJob, int nLevel)> CMaxHpSp::_GetHp2;
};
