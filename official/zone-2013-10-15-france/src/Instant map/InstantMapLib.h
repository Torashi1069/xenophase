#pragma once
#include "Common/Packet.h"


namespace InstantMap
{

std::string GetPhysicalMapName(std::string in_NickName);
bool IsInstantMap(std::string in_MapName);
void SendPacket_ZI_INSTANTMAP_CREATE_RES(const unsigned int in_hRequestN2Obj, std::string in_MapName, const int in_MapID, const bool in_bSuccess);
void Send_PACKET_ZI_INSTANTMAP_ALLOW(const bool in_bAllow, PACKET_ZI_INSTANTMAP_ALLOW::enumWhy in_why);


}; // namespace
