#pragma once
#pragma pack(push,1)
///////////////////////////////////////


enum
{
	HEADER_AW_REQ_CONNECT             = 161,
	HEADER_WA_ACK_CONNECT_SUCCESS     = 162,
	HEADER_WA_ACK_CONNECT_FAILED      = 175,
	HEADER_AW_SEND_ACC_SVR_USERCOUNT  = 163,
	HEADER_AW_SEND_CHAR_SVR_USERCOUNT = 177,
	HEADER_WA_RECV_COUNT_INFO_SUCCESS = 178,
	HEADER_AW_SEND_CHECK_LINE         = 250,
	HEADER_WA_RECV_CHECK_LINE         = 251,
	HEADER_AW_COMPLETE_CHECK          = 252,
};


struct PACKET_AW_REQ_CONNECT
{// 0x00A1 (161)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short dwPacketSize;
	/* this+ 4 */ unsigned long nCountryNUm;
	/* this+ 8 */ unsigned long nServerNum;
	/* this+12 */ unsigned long nCharSvrCount;
	/* this+16 */ char szAccountName[25];
};


struct PACKET_AW_SEND_ACC_SVR_USERCOUNT
{// 0x00A3 (163)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long dwUser;
	/* this+ 6 */ unsigned long nCharSvrCount;
	/* this+10 */ char szDate[9];
	/* this+19 */ char szTime[10];
};


struct PACKET_AW_SEND_CHAR_SVR_USERCOUNT
{// 0x00B1 (177)
	/* this+0 */ short PacketType;
	/* this+2 */ short dwPacketSize;
	/* this+4 */ DWORD nUserCount[];
};


struct PACKET_AW_SEND_CHECK_LINE
{// 0x00FA (250)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long packetNum;
	/* this+ 6 */ unsigned long dwSendTime;
	/* this+10 */ char dummy[1000];
};


struct PACKET_WA_RECV_CHECK_LINE
{// 0x00FB (251)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long packetNum;
	/* this+ 6 */ unsigned long dwRecvTime;
	/* this+10 */ unsigned long dwSendTime;
	/* this+14 */ char dummy[1000];
};


struct PACKET_AW_COMPLETE_CHECK
{// 0x00FC (252)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long packetNum;
	/* this+ 6 */ unsigned long allTime;
	/* this+10 */ unsigned long dwRecvTime;
};


///////////////////////////////////////
#pragma pack(pop)


extern void InitWUCSPacketLen();
extern std::map<int,int> g_WUCSpacketLenMap;
