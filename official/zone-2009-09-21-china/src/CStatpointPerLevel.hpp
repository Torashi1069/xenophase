#pragma once


class CStatpointPerLevel
{
	/* this+0 */ private: //const CStatpointPerLevel::`vftable';
	/* this+4 */ private: int m_statpointPerLevel[101];
	/* static */ private: static hook_ptr<const char *> m_szpLoadFileName;

	public: CStatpointPerLevel::CStatpointPerLevel(void);
	public: virtual CStatpointPerLevel::~CStatpointPerLevel(void);
	public: void CStatpointPerLevel::Init(void);
	public: int CStatpointPerLevel::LoadStatpointPerLevel(void);
	public: int CStatpointPerLevel::GetStatpointPerLevel(int nLevel);

private:
	static hook_method<void (CStatpointPerLevel::*)(void)> CStatpointPerLevel::_Init;
	static hook_method<int (CStatpointPerLevel::*)(void)> CStatpointPerLevel::_LoadStatpointPerLevel;
	static hook_method<int (CStatpointPerLevel::*)(int nLevel)> CStatpointPerLevel::_GetStatpointPerLevel;
};
