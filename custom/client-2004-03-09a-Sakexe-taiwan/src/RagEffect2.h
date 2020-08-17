#pragma once
#include "3dLib/Prim.h" // vector3d
class CPlayer;
class CRagEffect;


class CWeather
{
	/* this+ 0 */ private: int m_nRainCnt;
	/* this+ 4 */ private: int m_nSnowCnt;
	/* this+ 8 */ private: bool m_bNight;
	/* this+ 9 */ private: bool m_bRain;
	/* this+10 */ private: bool m_bSnow;
	/* this+11 */ private: bool m_bSakura;
	/* this+12 */ private: bool m_bMaple;
	/* this+13 */ private: bool m_bObjLight;
	/* this+14 */ private: bool m_bActWeather;
	/* this+16 */ private: CPlayer* m_pPlayer;
	/* this+20 */ private: vector3d m_Diffuse;
	/* this+32 */ private: vector3d m_MaxDiffuse;
	/* this+44 */ private: vector3d m_Ambient;
	/* this+56 */ private: vector3d m_EnvDiff;
	/* this+68 */ private: CRagEffect* m_Effect;
	/* this+72 */ private: SYSTEMTIME m_st;
	/* this+88 */ private: int m_nDayCount;

	//public: CWeather::CWeather(void);
	//public: CWeather::~CWeather(void);
	//public: int GetRainCnt(void);
	//public: int GetSnowCnt(void);
	//public: vector3d GetEnvDiff(void);
	public: vector3d CWeather::GetAmbient(void);
	public: void CWeather::SetAmbient(vector3d v);
	public: void CWeather::SetDiffuse(vector3d v);
	public: void CWeather::SetMaxDiffuse(vector3d v);
	public: void CWeather::SetNight(bool bNight);
	public: void CWeather::SetObjLight(bool bObjLight);
	public: void CWeather::SetNightDegree(void);
	//public: void ActWeather(unsigned char);
	//public: bool IsNight(void);
	//public: bool IsRain(void);
	//public: bool IsSnow(void);
	//public: bool IsObjLight(void);
	//public: bool IsWeather(void);
	public: void CWeather::Process(void);
	public: void CWeather::LaunchRain(void);
	public: void CWeather::LaunchSnow(void);
	public: void CWeather::LaunchSakura(void);
	public: void CWeather::LaunchMaple(void);
	public: void CWeather::LaunchCloud(char map);
	public: void CWeather::LaunchPokJuk(void);
	public: void CWeather::StopRain(void);
	public: void CWeather::StopSnow(void);
	public: void CWeather::StopSakura(void);
	public: void CWeather::StopMaple(void);
	public: void CWeather::Reset(void);
	public: vector3d CWeather::GetSunWorldLoc(void);

private:
	static hook_method<vector3d (CWeather::*)(void)> CWeather::_GetAmbient;
	static hook_method<void (CWeather::*)(vector3d v)> CWeather::_SetAmbient;
	static hook_method<void (CWeather::*)(vector3d v)> CWeather::_SetDiffuse;
	static hook_method<void (CWeather::*)(vector3d v)> CWeather::_SetMaxDiffuse;
	static hook_method<void (CWeather::*)(bool bNight)> CWeather::_SetNight;
	static hook_method<void (CWeather::*)(bool bObjLight)> CWeather::_SetObjLight;
	static hook_method<void (CWeather::*)(void)> CWeather::_SetNightDegree;
	static hook_method<void (CWeather::*)(void)> CWeather::_Process;
	static hook_method<void (CWeather::*)(void)> CWeather::_LaunchRain;
	static hook_method<void (CWeather::*)(void)> CWeather::_LaunchSnow;
	static hook_method<void (CWeather::*)(void)> CWeather::_LaunchSakura;
	static hook_method<void (CWeather::*)(void)> CWeather::_LaunchMaple;
	static hook_method<void (CWeather::*)(char map)> CWeather::_LaunchCloud;
	static hook_method<void (CWeather::*)(void)> CWeather::_LaunchPokJuk;
	static hook_method<void (CWeather::*)(void)> CWeather::_StopRain;
	static hook_method<void (CWeather::*)(void)> CWeather::_StopSnow;
	static hook_method<void (CWeather::*)(void)> CWeather::_StopSakura;
	static hook_method<void (CWeather::*)(void)> CWeather::_StopMaple;
	static hook_method<void (CWeather::*)(void)> CWeather::_Reset;
	static hook_method<vector3d (CWeather::*)(void)> CWeather::_GetSunWorldLoc;
};
