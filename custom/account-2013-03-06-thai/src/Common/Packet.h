#pragma once
#include "Common/PacketClient.h"
#include "Common/PacketServer.h"
#pragma pack(push,1)


struct PACKET
{
	/* this+0 */ short PacketType;
	/* this+2 */ char Data[];
};


struct PACKETV
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ char Data[];
};


void InitPacketLen();
void InitPacketLenWithClient();
extern std::map<int,int> g_packetLenMap;


#pragma pack(pop)
