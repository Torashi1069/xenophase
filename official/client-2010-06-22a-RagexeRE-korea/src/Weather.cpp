#include "Weather.h"


void CWeather::SetObjLight(bool bObjLight)
{
	m_bObjLight = bObjLight;
}


hook_func<void (CWeather::*)(mystd::string map, mystd::string weather)> CWeather::_AddScript("CWeather::AddScript");
void CWeather::AddScript(mystd::string map, mystd::string weather)
{
	return (this->*_AddScript)(map, weather);

	//TODO
}
