#include "RagEffect2.h"


//hook_method<vector3d (CWeather::*)(void)> CWeather::_GetAmbient(SAKEXE, "CWeather::GetAmbient");
vector3d CWeather::GetAmbient(void)
{
//	return (this->*_GetAmbient)();

	return m_Ambient;
}


//hook_method<void (CWeather::*)(vector3d v)> CWeather::_SetAmbient(SAKEXE, "CWeather::SetAmbient");
void CWeather::SetAmbient(vector3d v)
{
//	return (this->*_SetAmbient)(v);

	m_Ambient = v;
}


//hook_method<void (CWeather::*)(vector3d v)> CWeather::_SetDiffuse(SAKEXE, "CWeather::SetDiffuse");
void CWeather::SetDiffuse(vector3d v)
{
//	return (this->*_SetDiffuse)(v);

	m_Diffuse = v;
}


//hook_method<void (CWeather::*)(vector3d v)> CWeather::_SetMaxDiffuse(SAKEXE, "CWeather::SetMaxDiffuse");
void CWeather::SetMaxDiffuse(vector3d v)
{
//	return (this->*_SetMaxDiffuse)(v);

	m_MaxDiffuse = v;
}


//hook_method<void (CWeather::*)(bool bNight)> CWeather::_SetNight(SAKEXE, "CWeather::SetNight");
void CWeather::SetNight(bool bNight)
{
//	return (this->*_SetNight)(bNight);

	m_bNight = bNight;
}


//hook_method<void (CWeather::*)(bool bObjLight)> CWeather::_SetObjLight(SAKEXE, "CWeather::SetObjLight");
void CWeather::SetObjLight(bool bObjLight)
{
//	return (this->*_SetObjLight)(bObjLight);

	m_bObjLight = bObjLight;
}


hook_method<void (CWeather::*)(void)> CWeather::_SetNightDegree(SAKEXE, "CWeather::SetNightDegree");
void CWeather::SetNightDegree(void) // line 3121 (RagEffectPrim.h)
{
	return (this->*_SetNightDegree)();

	;
}


hook_method<void (CWeather::*)(void)> CWeather::_Process(SAKEXE, "CWeather::Process");
void CWeather::Process(void) // line 3037 (RagEffectPrim.cpp)
{
	return (this->*_Process)();

	//TODO
}


hook_method<void (CWeather::*)(void)> CWeather::_LaunchRain(SAKEXE, "CWeather::LaunchRain");
void CWeather::LaunchRain(void) // line 3124 (RagEffectPrim.cpp)
{
	return (this->*_LaunchRain)();

	//TODO
}


hook_method<void (CWeather::*)(void)> CWeather::_LaunchSnow(SAKEXE, "CWeather::LaunchSnow");
void CWeather::LaunchSnow(void) // line 3137 (RagEffectPrim.cpp)
{
	return (this->*_LaunchSnow)();

	//TODO
}


hook_method<void (CWeather::*)(void)> CWeather::_LaunchSakura(SAKEXE, "CWeather::LaunchSakura");
void CWeather::LaunchSakura(void) // line 4921
{
	return (this->*_LaunchSakura)();

	//TODO
}


hook_method<void (CWeather::*)(void)> CWeather::_LaunchMaple(SAKEXE, "CWeather::LaunchMaple");
void CWeather::LaunchMaple(void) // line 4934
{
	return (this->*_LaunchMaple)();

	//TODO
}


hook_method<void (CWeather::*)(char map)> CWeather::_LaunchCloud(SAKEXE, "CWeather::LaunchCloud");
void CWeather::LaunchCloud(char map) // line 4964
{
	return (this->*_LaunchCloud)(map);

	//TODO
}


hook_method<void (CWeather::*)(void)> CWeather::_LaunchPokJuk(SAKEXE, "CWeather::LaunchPokJuk");
void CWeather::LaunchPokJuk(void) // line 4983
{
	return (this->*_LaunchPokJuk)();

	//TODO
}


hook_method<void (CWeather::*)(void)> CWeather::_StopRain(SAKEXE, "CWeather::StopRain");
void CWeather::StopRain(void) // line 3152 (RagEffectPrim.cpp)
{
	return (this->*_StopRain)();

	//TODO
}


hook_method<void (CWeather::*)(void)> CWeather::_StopSnow(SAKEXE, "CWeather::StopSnow");
void CWeather::StopSnow(void) // line 3160 (RagEffectPrim.cpp)
{
	return (this->*_StopSnow)();

	//TODO
}


hook_method<void (CWeather::*)(void)> CWeather::_StopSakura(SAKEXE, "CWeather::StopSakura");
void CWeather::StopSakura(void) // line 4948
{
	return (this->*_StopSakura)();

	//TODO
}


hook_method<void (CWeather::*)(void)> CWeather::_StopMaple(SAKEXE, "CWeather::StopMaple");
void CWeather::StopMaple(void) // line 4957
{
	return (this->*_StopMaple)();

	//TODO
}


hook_method<void (CWeather::*)(void)> CWeather::_Reset(SAKEXE, "CWeather::Reset");
void CWeather::Reset(void) // line 3169 (RagEffectPrim.cpp)
{
	return (this->*_Reset)();

	//TODO
}


hook_method<vector3d (CWeather::*)(void)> CWeather::_GetSunWorldLoc(SAKEXE, "CWeather::GetSunWorldLoc");
vector3d CWeather::GetSunWorldLoc(void) // line 3173 (RagEffectPrim.h)
{
	return (this->*_GetSunWorldLoc)();

	vector3d result;

	float sinDeg = GetSin(m_nDayCount / 8 + 90);
	float cosDeg = GetCos(m_nDayCount / 8 + 90);
	result.x = float(cosDeg * 1000.0 + sinDeg * 0.0);
	result.y = float(cosDeg * 0.0 - sinDeg * 1000.0);
	result.z = 0.0;

	return result;
}
