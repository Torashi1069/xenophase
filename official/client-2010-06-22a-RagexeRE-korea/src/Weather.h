#pragma once
#include "std/string"


class CWeather
{
public:
	void SetObjLight(bool bObjLight);
	void AddScript(mystd::string map, mystd::string weather);

private:
	/* this+0 */ bool m_bNight;
	/* this+1 */ bool m_bObjLight;
	//TODO

private:
	static hook_func<void (CWeather::*)(mystd::string map, mystd::string weather)> CWeather::_AddScript;
};
