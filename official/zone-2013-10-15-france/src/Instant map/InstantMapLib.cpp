#include "Client/InterServerClient/C2InterServerClient.h"
#include "Instant map/InstantMapLib.h"


namespace InstantMap
{


std::string GetPhysicalMapName(std::string in_NickName) // 10-14 (shared/InstantMapLib.cpp)
{
	return ( in_NickName.size() >= 9 && in_NickName[4] == '@' ) ? in_NickName.substr(3, in_NickName.size() - 3) : "";
}


bool IsInstantMap(std::string in_MapName) // 57-61 (shared/InstantMapLib.cpp)
{
	return ( in_MapName.size() >= 9 && in_MapName[4] == '@' );
}


void SendPacket_ZI_INSTANTMAP_CREATE_RES(const unsigned int in_hRequestN2Obj, std::string in_MapName, const int in_MapID, const bool in_bSuccess) // 190-199 (Instant map/InstantMapMgr.cpp)
{
	PACKET_ZI_INSTANTMAP_CREATE_RES packet;
	packet.PacketType = HEADER_ZI_INSTANTMAP_CREATE_RES;
	packet.hRequestN2Obj = in_hRequestN2Obj;
	strncpy(packet.mapName, in_MapName.c_str(), countof(packet.mapName));
	C2InterServerClient::GetObj()->C2InterServerClient::Send(sizeof(packet), (char*)&packet);
}


void Send_PACKET_ZI_INSTANTMAP_ALLOW(const bool in_bAllow, PACKET_ZI_INSTANTMAP_ALLOW::enumWhy in_why) // 352-358 (CISvrIOPacketHandler.cpp)
{
	PACKET_ZI_INSTANTMAP_ALLOW packet;
	packet.PacketType = HEADER_ZI_INSTANTMAP_ALLOW;
	packet.bAllow = in_bAllow;
	packet.why = in_why;
	C2InterServerClient::GetObj()->C2InterServerClient::Send(sizeof(packet), (char*)&packet);
}


}; // namespace
