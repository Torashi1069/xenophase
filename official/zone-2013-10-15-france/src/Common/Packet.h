#pragma once
#include "Common/PacketClient.h"
#include "Common/PacketServer.h"
#pragma pack(push,1)


void EncodePosDir(int srcx, int srcy, int srcdir, BYTE* result);
void DecodePosDir(const unsigned char* packet, int& x, int& y, int& dir);
void EncodeSrcDst(int srcx, int srcy, int dstx, int dsty, int xcellpos, int ycellpos, BYTE* result);
void DecodeSrcDst(const unsigned char* packet, int& rsx, int& rsy, int& rdx, int& rdy, int& xcellpos, int& ycellpos);


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


#pragma pack(pop)


extern class CPacketLengthExMgr& g_packetLenMapEx;
