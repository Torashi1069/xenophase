#include "InstantMapLib.h"


//hook_method<static int (__cdecl *)(mystd::string in_InstantMapName)> InstantMap::_GetInstantMapFactor(SERVER, "InstantMap::GetInstantMapFactor");
int __cdecl InstantMap::GetInstantMapFactor(mystd::string in_InstantMapName) // line ??
{
//	return (InstantMap::_GetInstantMapFactor)(in_InstantMapName);

	if( in_InstantMapName.size() < 9 || in_InstantMapName[4] != '@' )
		return 0;

	char buffer[4];
	buffer[0] = in_InstantMapName[0];
	buffer[1] = in_InstantMapName[1];
	buffer[2] = in_InstantMapName[2];
	buffer[3] = 0;

	return atoi(buffer);
}


//hook_method<static mystd::string (__cdecl *)(const int in_Factor, mystd::string in_PhysicalMapName)> InstantMap::_GetInstantMapName(SERVER, "InstantMap::GetInstantMapName");
mystd::string __cdecl InstantMap::GetInstantMapName(const int in_Factor, mystd::string in_PhysicalMapName) // line ??
{
//	return (InstantMap::_GetInstantMapName)(in_Factor, in_PhysicalMapName);

	char buffer[260];
	_snprintf(buffer, sizeof(buffer), "%03d", in_Factor);
	buffer[sizeof(buffer)-1] = '\0';

	return mystd::string(buffer) + in_PhysicalMapName;
}


hook_method<static mystd::string (__cdecl *)(mystd::string in_NickName)> InstantMap::_GetPhysicalMapName(SERVER, "InstantMap::GetPhysicalMapName");
mystd::string __cdecl InstantMap::GetPhysicalMapName(mystd::string in_NickName) // line 10
{
	return (InstantMap::_GetPhysicalMapName)(in_NickName);

	return ( in_NickName.size() >= 9 && in_NickName[4] == '@' ) ? in_NickName.substr(3, in_NickName.size() - 3) : "";
}


hook_method<static bool (__cdecl *)(mystd::string in_MapName)> InstantMap::_IsInstantMap(SERVER, "InstantMap::IsInstantMap");
bool __cdecl InstantMap::IsInstantMap(mystd::string in_MapName) // line 34
{
	return (InstantMap::_IsInstantMap)(in_MapName);

	return ( in_MapName.size() >= 9 && in_MapName[4] == '@' );
}


hook_method<static void (__cdecl *)(const unsigned int in_hRequestN2Obj, mystd::string in_MapName, int in_MapID, bool in_bSuccess)> InstantMap::_SendPacket_ZI_INSTANTMAP_CREATE_RES(SERVER, "InstantMap::SendPacket_ZI_INSTANTMAP_CREATE_RES");
void __cdecl InstantMap::SendPacket_ZI_INSTANTMAP_CREATE_RES(const unsigned int in_hRequestN2Obj, mystd::string in_MapName, int in_MapID, bool in_bSuccess) // line 156 (Instant Map/InstantMapMgr.cpp)
{
	return (InstantMap::_SendPacket_ZI_INSTANTMAP_CREATE_RES)(in_hRequestN2Obj, in_MapName, in_MapID, in_bSuccess);

	//TODO
}


hook_method<static void (__cdecl *)(const unsigned int in_hRequestN2Obj, const int in_mapID, enum PACKET_ZI_INSTANTMAP_ERROR::enumWhy in_Why)> InstantMap::_SendPacket_ZI_INSTANTMAP_ERROR(SERVER, "InstantMap::SendPacket_ZI_INSTANTMAP_ERROR");
void __cdecl InstantMap::SendPacket_ZI_INSTANTMAP_ERROR(const unsigned int in_hRequestN2Obj, const int in_mapID, enum PACKET_ZI_INSTANTMAP_ERROR::enumWhy in_Why) // line 139 (Instant Map/InstantMapMgr.cpp)
{
	return (InstantMap::_SendPacket_ZI_INSTANTMAP_ERROR)(in_hRequestN2Obj, in_mapID, in_Why);

	//TODO
}


hook_method<static void (__cdecl *)(const bool in_bAllow, enum PACKET_ZI_INSTANTMAP_ALLOW::enumWhy in_why)> InstantMap::_Send_PACKET_ZI_INSTANTMAP_ALLOW(SERVER, "InstantMap::Send_PACKET_ZI_INSTANTMAP_ALLOW");
void __cdecl InstantMap::Send_PACKET_ZI_INSTANTMAP_ALLOW(const bool in_bAllow, enum PACKET_ZI_INSTANTMAP_ALLOW::enumWhy in_why) // line 207 (CISvrIOPacketHandler.h)
{
	return (InstantMap::_Send_PACKET_ZI_INSTANTMAP_ALLOW)(in_bAllow, in_why);

	//TODO
}
