#include "Packet.h"


void EncodePosDir(int srcx, int srcy, int srcdir, BYTE* result)
{
	///  [    BYTE0    ] [    BYTE1    ] [    BYTE2    ] 
	///  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 
	/// +-------------------+-------------------+-------+
	/// |       srcx        |       srcy        |  dir  |
	/// +-------------------+-------------------+-------+
	result[0] =                        ((srcx >> 2) & 0xFF);
	result[1] = ((srcx << 6) & 0xC0) | ((srcy >> 4) & 0x3F);
	result[2] = ((srcy << 4) & 0xF0) | ((srcdir >> 0) & 0x0F);
}


void DecodePosDir(const unsigned char* packet, int& x, int& y, int& dir)
{
	x = ((packet[0] & 0xFF) << 2) | ((packet[1] & 0xC0) >> 6); // 10 bits
	y = ((packet[1] & 0x3F) << 4) | ((packet[2] & 0xF0) >> 4); // 10 bits
	dir = ((packet[2] & 0x0F) >> 0);                           //  4 bits
}


void EncodeSrcDst(int srcx, int srcy, int dstx, int dsty, int xcellpos, int ycellpos, BYTE* result)
{
	///  [    BYTE0    ] [    BYTE1    ] [    BYTE2    ] [    BYTE3    ] [    BYTE4    ] [    BYTE5    ]
	///  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 
	/// +-------------------+-------------------+-------------------+-------------------+-------+-------+
	/// |       srcx        |       srcy        |       dstx        |       dsty        | xcell | ycell |
	/// +-------------------+-------------------+-------------------+-------------------+-------+-------+
	result[0] =                        ((srcx >> 2) & 0xFF);
	result[1] = ((srcx << 6) & 0xC0) | ((srcy >> 4) & 0x3F);
	result[2] = ((srcy << 4) & 0xF0) | ((dstx >> 6) & 0x0F);
	result[3] = ((dstx << 2) & 0xFC) | ((dsty >> 8) & 0x03);
	result[4] = ((dsty << 0) & 0xFF)                       ;
	result[5] = ((xcellpos << 4) & 0xF0) | ((ycellpos >> 0) & 0x0F);
}


void DecodeSrcDst(const unsigned char* packet, int& rsx, int& rsy, int& rdx, int& rdy, int& xcellpos, int& ycellpos)
{
	rsx = ((packet[0] & 0xFF) << 2) | ((packet[1] & 0xC0) >> 6); // 10 bits
	rsy = ((packet[1] & 0x3F) << 4) | ((packet[2] & 0xF0) >> 4); // 10 bits
	rdx = ((packet[2] & 0x0F) << 6) | ((packet[3] & 0xFC) >> 2); // 10 bits
	rdy = ((packet[3] & 0x03) << 8) | ((packet[4] & 0xFF) >> 0); // 10 bits
	xcellpos = ((packet[5] & 0xF0) >> 4);                        //  4 bits
	ycellpos = ((packet[5] & 0x0F) >> 0);                        //  4 bits
}
