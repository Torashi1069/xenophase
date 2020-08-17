#pragma once
#pragma pack(push,1)
///////////////////////////////////////


struct PACKET_MI_ENTER
{// 11000
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char ID[24];
	/* this+26 */ char Password[24];
};


struct PACKET_MI_REQ_SERVERSTATE
{// 11001
	/* this+0 */ short PacketType;
	/* this+2 */ int serverID;
	/* this+6 */ int packetNumber;
};


struct PACKET_MI_MSG
{// 11002
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ unsigned long type;
	/* this+8 */ char Text[];
};


struct PACKET_MI_SHOTDOWN
{// 11003
	/* this+0 */ short PacketType;
	/* this+2 */ int serverID;
	/* this+6 */ char password[24];
};


struct PACKET_IM_CONTROLFAIL
{// 11004
	/* this+0 */ short PacketType;
	/* this+2 */ int errorCode;
};


struct PACKET_IM_SERVERLIST
{// 11005
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ int ZSID[];
};


struct IM_SERVER_STATE
{
	/* this+ 0 */ int serverID;
	/* this+ 4 */ int packetNumber;
	/* this+ 8 */ int userCounter;
	/* this+12 */ int loopcountPerSec;
};


struct PACKET_IM_SERVERSTATE
{// 11006
	/* this+0 */ short PacketType;
	/* this+2 */ IM_SERVER_STATE serverState;
};


//struct PACKET_IM_ACKMSG
//{// 11007
//	//...
//};


//struct PACKET_NOT_USE01
//{// 11008
//	//...
//};


struct PACKET_MI_GET_GUILD_INFO
{// 11009
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GuildID;
};


struct PACKET_IM_REQ_GUILD_INFO
{// 11010
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GuildID;
	/* this+ 6 */ char GuildName[24];
	/* this+30 */ char GuildLevel;
	/* this+31 */ int GuildExp;
};


struct PACKET_MI_GUILD_INFO_INIT
{// 11011
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GuildID;
};


struct PACKET_IM_RESULT_GUILD_INFO_INIT
{// 11012
	/* this+0 */ short PacketType;
	/* this+2 */ char Result;
};


struct PACKET_MI_ALLY_GUILD_INIT
{// 11013
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GuildID;
};


struct PACKET_IM_REQ_ALLY_GUILD_INIT
{// 11014
	/* this+0 */ short PacketType;
	/* this+2 */ char Result;
};


struct IM_SERVER_STATE_HAN_GAME
{
	/* this+ 0 */ int serverID;
	/* this+ 4 */ int packetNumber;
	/* this+ 8 */ int userCounter;
	/* this+12 */ int loopcountPerSec;
	/* this+16 */ int hangameUserCounter;
};


struct PACKET_IM_SERVERSTATE_HAN_GAME
{// 11015 (0x2B07)
	/* this+0 */ short PacketType;
	/* this+2 */ IM_SERVER_STATE_HAN_GAME serverState;
};


struct IM_SERVER_STATE_CHANNELING
{
	/* this+ 0 */ int serverID;
	/* this+ 4 */ int packetNumber;
	/* this+ 8 */ int userCounter;
	/* this+12 */ int loopcountPerSec;
	/* this+16 */ short Channeling_UserCounter[10];
};


struct PACKET_IM_SERVERSTATE_CHANNELING
{// 11016 (0x2B08)
	/* this+0 */ short PacketType;
	/* this+2 */ IM_SERVER_STATE_CHANNELING serverState;
};


struct PACKET_MI_REQ_EDIT_EXP
{// 11017
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char ID[24];
	/* this+26 */ char Passwd[24];
	/* this+50 */ int Exp;
	/* this+54 */ int Death;
	/* this+58 */ int Drop;
};


struct PACKET_IM_ACK_EDIT_EXP
{// 11018
	enum
	{
		RESULT_SUCCESS       = 0,
		RESULT_FAIL_UNKNOWN  = 1,
		RESULT_FAIL_AUTH     = 2,
		RESULT_FAIL_RESTRICT = 3,
	};

	/* this+ 0 */ short PacketType;
	/* this+ 2 */ int Result;
	/* this+ 6 */ int Exp;
	/* this+10 */ int Death;
	/* this+14 */ int Drop;
};


///////////////////////////////////////
#pragma pack(pop)
