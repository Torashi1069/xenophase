#pragma once
#include "Common/PacketClient.h"
#include "Common/PacketServer.h"


void InitPacketLen();
void InitPacketLenWithClient();
extern std::map<int,int> g_packetLenMap;
