#pragma once
#pragma pack(push,1)


void EncodePosDir(int srcx, int srcy, int srcdir, BYTE* result);
void DecodePosDir(const unsigned char* packet, int& x, int& y, int& dir);
void EncodeSrcDst(int srcx, int srcy, int dstx, int dsty, int xcellpos, int ycellpos, BYTE* result);
void DecodeSrcDst(const unsigned char* packet, int& rsx, int& rsy, int& rdx, int& rdy, int& xcellpos, int& ycellpos);


enum ePacketType
{
	HEADER_ZC_SRPACKETR2_INIT                     = 703,
	HEADER_CZ_SRPACKETR2_START                    = 704,
};


struct PACKET_ZC_SRPACKETR2_INIT
{// 0x02BF (703)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short ProtectFactor;
	/* this+4 */ unsigned int DeformSeedFactor;
	/* this+8 */ unsigned int DeformAddFactor;
};


struct PACKET_CZ_SRPACKETR2_START
{// 0x02C0 (704)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short ProtectFactor;
};


#pragma pack(pop)
