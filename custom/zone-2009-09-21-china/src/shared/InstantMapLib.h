#pragma once
#include "Common/Packet.h"
#include "std/string"


/// guessed
class InstantMap
{
	public: static int __cdecl InstantMap::GetInstantMapFactor(mystd::string in_InstantMapName);
	public: static mystd::string __cdecl InstantMap::GetInstantMapName(const int in_Factor, mystd::string in_PhysicalMapName);
	public: static mystd::string __cdecl InstantMap::GetPhysicalMapName(mystd::string in_NickName);
	public: static bool __cdecl InstantMap::IsInstantMap(mystd::string in_MapName);
	public: static void __cdecl InstantMap::SendPacket_ZI_INSTANTMAP_CREATE_RES(const unsigned int in_hRequestN2Obj, mystd::string in_MapName, const int in_MapID, const bool in_bSuccess);
	public: static void __cdecl InstantMap::SendPacket_ZI_INSTANTMAP_ERROR(const unsigned int in_hRequestN2Obj, const int in_mapID, enum PACKET_ZI_INSTANTMAP_ERROR::enumWhy in_Why);
	public: static void __cdecl InstantMap::Send_PACKET_ZI_INSTANTMAP_ALLOW(const bool in_bAllow, enum PACKET_ZI_INSTANTMAP_ALLOW::enumWhy in_why);

private:
	static hook_method<static int (__cdecl *)(mystd::string in_InstantMapName)> InstantMap::_GetInstantMapFactor;
	static hook_method<static mystd::string (__cdecl *)(const int in_Factor, mystd::string in_PhysicalMapName)> InstantMap::_GetInstantMapName;
	static hook_method<static mystd::string (__cdecl *)(mystd::string in_NickName)> InstantMap::_GetPhysicalMapName;
	static hook_method<static bool (__cdecl *)(mystd::string in_MapName)> InstantMap::_IsInstantMap;
	static hook_method<static void (__cdecl *)(const unsigned int in_hRequestN2Obj, mystd::string in_MapName, const int in_MapID, const bool in_bSuccess)> InstantMap::_SendPacket_ZI_INSTANTMAP_CREATE_RES;
	static hook_method<static void (__cdecl *)(const unsigned int in_hRequestN2Obj, const int in_mapID, enum PACKET_ZI_INSTANTMAP_ERROR::enumWhy in_Why)> InstantMap::_SendPacket_ZI_INSTANTMAP_ERROR;
	static hook_method<static void (__cdecl *)(const bool in_bAllow, enum PACKET_ZI_INSTANTMAP_ALLOW::enumWhy in_why)> InstantMap::_Send_PACKET_ZI_INSTANTMAP_ALLOW;
};
