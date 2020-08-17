#include "Instant Map/InstantMapLib.h"
#include "shared/N2System/N2IDGenerator36.h"


namespace InstantMap
{


std::string InstantMap::GetInstantMapName(const int in_Factor, std::string in_PhysicalMapName)
{
	std::string ID = N2IDGenerator36::GetObj()->N2IDGenerator36::Generate36(in_Factor);
	char buffer[260];

	if( ID.size() >= 3 )
	{
		_snprintf_s(buffer, countof(buffer), _TRUNCATE, "%s", ID.c_str());
	}
	else
	if( ID.size() >= 2 )
	{
		_snprintf_s(buffer, countof(buffer), _TRUNCATE, "0");
		_snprintf_s(buffer + 1, countof(buffer) - 1, _TRUNCATE, "%s", ID.c_str());
	}
	else // ( ID.size() <= 1 )
	{
		_snprintf_s(buffer, countof(buffer), _TRUNCATE, "00");
		_snprintf_s(buffer + 2, countof(buffer) - 2, _TRUNCATE, "%s", ID.c_str());
	}

	return buffer + in_PhysicalMapName;
}


int InstantMap::GetInstantMapFactor(std::string in_InstantMapName)
{
	if( in_InstantMapName.size() < 9 )
		return 0;

	if( in_InstantMapName[4] != '@' )
		return 0;

	char buffer[4];
	buffer[0] = in_InstantMapName[0];
	buffer[1] = in_InstantMapName[1];
	buffer[2] = in_InstantMapName[2];
	buffer[3] = '\0';

	return N2IDGenerator36::GetObj()->N2IDGenerator36::ReverseDecimal(buffer);
}


}; // namespace
