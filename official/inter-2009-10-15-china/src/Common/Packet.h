#pragma once
#include "structs.hpp"
#pragma pack(push,1)


bool __cdecl IsFixedPacket(int packetType);
int __cdecl GetPacketSize(int packetType);
void __cdecl InitPacketLen(void);
void __cdecl InitPacketLenWithClient(void);


struct PACKET
{// @custom
	short PacketType;
};


struct PACKETV
{// @custom
	short PacketType;
	unsigned short PacketLength;
};


struct PACKET_ZC_PARTY_JOIN_REQ_ACK
{// 0x2C5
	enum enumAnswer
	{
		ANSWER_ALREADY_OTHERGROUPM = 0,
		ANSWER_MEMBER_OVERSIZE     = 3,
		ANSWER_JOIN_ACCEPT         = 2,
		ANSWER_JOIN_REFUSE         = 1,
		ANSWER_DUPLICATE           = 4,
		ANSWER_JOINMSG_REFUSE      = 5,
		ANSWER_UNKNOWN_ERROR       = 6,
		ANSWER_UNKNOWN_CHARACTER   = 7,
		ANSWER_INVALID_MAPPROPERTY = 8,
	};

	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char characterName[24];
	/* this+26 */ enum PACKET_ZC_PARTY_JOIN_REQ_ACK::enumAnswer answer;
};


struct PACKET_ZC_MEMORIALDUNGEON_NOTIFY
{// 0x2CE
	enum enumTYPE
	{
		TYPE_NOTIFY = 0,
		TYPE_DESTROY_LIVE_TIMEOUT = 1,
		TYPE_DESTROY_ENTER_TIMEOUT = 2,
		TYPE_DESTROY_USER_REQUEST = 3,
		TYPE_CREATE_FAIL = 4,
	};

	/* this+0 */ short PacketType;
	/* this+2 */ enum PACKET_ZC_MEMORIALDUNGEON_NOTIFY::enumTYPE Type;
	/* this+6 */ unsigned long EnterLimitDate;
};


struct PACKET_CZ_MEMORIALDUNGEON_COMMAND
{// 0x2CF
	enum enumCOMMAND { COMMAND_SUBSCRIPTION_CANCEL, COMMAND_MEMORIALDUNGEON_DESTROY, COMMAND_MEMORIALDUNGEON_DESTROY_FORCE };

	/* this+0 */ short PacketType;
	/* this+2 */ enum PACKET_CZ_MEMORIALDUNGEON_COMMAND::enumCOMMAND Command;
};


struct PACKET_ZI_LOGON
{// 0x2916
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ int sex;
	/* this+14 */ short head;
	/* this+16 */ short headpalette;
	/* this+18 */ short level;
	/* this+20 */ short job;
	/* this+22 */ char accountName[24];
	/* this+46 */ char charName[24];
	/* this+70 */ char mapName[16];
};


struct PACKET_ZI_WHISPER
{// 0x2918
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short PacketLength;
	/* this+ 4 */ unsigned long senderAID;
	/* this+ 8 */ char sender[24];
	/* this+32 */ char receiver[24];
};


struct PACKET_ZI_BROADCAST
{// 0x291E
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ char Text[]; //dynamic
};


struct PACKET_IZ_BROADCAST
{// 0x291F
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ char Text[]; //dynamic
};


struct PACKET_ZI_MAKE_GROUP
{// 0x2920
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ char groupName[24];
};


struct PACKET_IZ_ACK_MAKE_GROUP
{// 0x2921
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GRID;
	/* this+10 */ char groupName[24];
	/* this+34 */ unsigned char result;
};


struct PACKET_IZ_GROUP_LIST
{// 0x2922
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short PacketLength;
	/* this+ 4 */ unsigned long AID;
	/* this+ 8 */ unsigned long expOption;
	/* this+12 */ char groupName[24];
	/* this+36 */ GROUPMEMBER_INFO Member[]; //dynamic
};


struct PACKET_ZI_REQ_JOIN_GROUP
{// 0x2923
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long senderAID;
	/* this+ 6 */ unsigned long receiverAID;
	/* this+10 */ unsigned long GRID;
};


struct PACKET_IZ_ACK_REQ_JOIN_GROUP
{// 0x2924
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ char characterName[24];
	/* this+30 */ unsigned char answer;
};


struct PACKET_IZ_REQ_JOIN_GROUP
{// 0x2925
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GRID;
	/* this+10 */ char groupName[24];
};


struct PACKET_ZI_JOIN_GROUP
{// 0x2926
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long senderAID;
	/* this+ 6 */ unsigned long GRID;
	/* this+10 */ int answer;
};


struct PACKET_ZI_REQ_LEAVE_GROUP
{// 0x2927
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
	/* this+6 */ unsigned long GID;
};


struct PACKET_ZI_REQ_EXPEL_GROUP_MEMBER
{// 0x2928
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GRID;
	/* this+10 */ char characterName[24];
};


struct PACKET_IZ_ADD_MEMBER_TO_GROUP
{// 0x2929
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long receiverAID;
	/* this+ 6 */ unsigned long AID;
	/* this+10 */ unsigned long Role;
	/* this+14 */ unsigned char state;
	/* this+15 */ char groupName[24];
	/* this+39 */ char characterName[24];
	/* this+63 */ char mapName[16];
};


struct PACKET_IZ_DELETE_MEMBER_FROM_GROUP
{// 0x292A
  /* this+ 0 */ short PacketType;
  /* this+ 2 */ unsigned long receiverAID;
  /* this+ 6 */ unsigned long AID;
  /* this+10 */ char characterName[24];
  /* this+34 */ unsigned char result;
};


struct PACKET_ZI_MAPMOVE
{// 0x292B
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
	/* this+6 */ char mapName[16];
};


struct PACKET_ZI_GRID_UPDATE
{// 0x292C
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GRID;
	/* this+10 */ unsigned long expOption;
};


struct PACKET_ZI_CHAT_PARTY
{// 0x292D

	enum { //custom
		MAX_MESSAGE_SIZE = 512,
	};

	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short PacketLength;
	/* this+ 4 */ unsigned long AID;
	/* this+ 8 */ unsigned long GRID;
	/* this+12 */ char Message[]; //dynamic
};


struct PACKET_IZ_CHAT_PARTY
{// 0x292E
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ unsigned long receiverAID;
	/* this+8 */ unsigned long senderAID;
	/* this+12 */ char Message[]; //dynamic
};


struct PACKET_IZ_DISCONNECT_ALL
{// 0x292F
	/* this+0 */ short PacketType;
};


struct PACKET_ZI_DISCONNECT_ALL
{// 0x2930
	/* this+0 */ short PacketType;
};


struct PACKET_ZI_CHANGE_EXPOPTION
{// 0x2931 (0x2993)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GRID;
	/* this+ 6 */ unsigned long AID;
	/* this+10 */ unsigned long expOption;
};


struct PACKET_ZI_REQ_JOIN_GUILD
{// 0x2951
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long myGID;
	/* this+10 */ unsigned long myAID;
	/* this+14 */ unsigned long GID;
};


struct PACKET_IZ_REQ_JOIN_GUILD
{// 0x2952
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GDID;
	/* this+ 6 */ unsigned long AID;
	/* this+10 */ char guildName[24];
};


struct PACKET_ZI_JOIN_GUILD
{// 0x2953
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GDID;
	/* this+ 6 */ char Name[24];
	/* this+30 */ char AccountName[24];
	/* this+54 */ unsigned long AID;
	/* this+58 */ unsigned long GID;
	/* this+62 */ int answer;
};


struct PACKET_IZ_ACK_REQ_JOIN_GUILD
{// 0x2954
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long ReqAID;
	/* this+10 */ unsigned long GDID;
	/* this+14 */ unsigned char answer;
};


struct PACKET_IZ_GUILD_MEMBER_ADD
{// 0x2967
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GDID;
	/* this+6 */ GUILDMINFO Info;
};


struct PACKET_ZI_MOVE
{// 0x2988 (10632)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ int MoveType; // enum SPECIALMOVETYPE
	/* this+ 6 */ unsigned long SrcID;
	/* this+10 */ int DestX;
	/* this+14 */ int DestY;
	/* this+18 */ char DestName[24];
};


struct PACKET_IZ_MOVE
{// 0x2989 (10633)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ int MoveType; // enum SPECIALMOVETYPE
	/* this+ 6 */ unsigned long SrcID;
	/* this+10 */ unsigned long DestID;
	/* this+14 */ int DestX;
	/* this+18 */ int DestY;
	/* this+22 */ char MapName[16];
	/* this+38 */ char CharName[24];
};


struct PACKET_ZI_MOVE_GID
{// 0x2990 (10640)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ int MoveType; // enum SPECIALMOVETYPE
	/* this+ 6 */ unsigned long SrcID;
	/* this+10 */ int DestX;
	/* this+14 */ int DestY;
	/* this+18 */ char DestName[24];
	/* this+42 */ unsigned long DestGID;
};


struct PACKET_ZI_MAKE_GROUP2
{// 0x298E
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ char groupName[24];
	/* this+34 */ unsigned char ItemPickupRule;
	/* this+35 */ unsigned char ItemDivisionRule;
};


struct PACKET_IZ_ADD_MEMBER_TO_GROUP2
{// 0x298F
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long receiverAID;
	/* this+ 6 */ unsigned long AID;
	/* this+10 */ unsigned long Role;
	/* this+14 */ unsigned char state;
	/* this+15 */ char groupName[24];
	/* this+39 */ char characterName[24];
	/* this+63 */ char mapName[16];
	/* this+79 */ unsigned char ItemPickupRule;
	/* this+80 */ unsigned char ItemDivisionRule;
};


struct PACKET_ZI_CHANGE_EXPOPTION2 : PACKET_ZI_CHANGE_EXPOPTION
{//custom 0x2993
};


struct PACKET_IZ_FRIENDS_LIST
{// 0x2999
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ unsigned long AID;
	/* this+8 */ STRUCT_FRIEND List[]; //dynamic
};


struct PACKET_IZ_FRIENDS_STATE
{// 0x299A
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long FriendAID;
	/* this+10 */ unsigned long FriendGID;
	/* this+14 */ bool State;
};


struct PACKET_IZ_ADD_FRIENDS
{// 0x299C
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short Result;
	/* this+ 4 */ unsigned long AID;
	/* this+ 8 */ unsigned long FriendAID;
	/* this+12 */ unsigned long FriendGID;
	/* this+16 */ char Name[24];
};


struct PACKET_IZ_DELETE_FRIENDS
{// 0x299E
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long FriendAID;
	/* this+10 */ unsigned long FriendGID;
};


struct PACKET_IZ_CHK_PROCESSTIME
{// 0x29AF
	/* this+0 */ short PacketType;
	/* this+2 */ time_t InterProcessTime;
};


struct PACKET_ZI_ACK_CHK_PROCESSTIME
{// 0x29B0
	/* this+0 */ short PacketType;
	/* this+2 */ time_t InterProcessTime;
	/* this+6 */ time_t ZoneProcessTime;
};


struct PACKET_IZ_DISCONNECT_CHARACTER
{// 0x29B1
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
};


struct PACKET_IZ_ACK_LOGON
{// 0x29B2
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long Type;
	/* this+6 */ unsigned long AID;
	/* this+10 */ unsigned long GID;
};


struct PACKET_ZI_MEMORIALDUNGEON_SUBSCRIPTION
{// 0x29BC
	/* this+  0 */ short PacketType;
	/* this+  2 */ char Name[60+1];
	/* this+ 63 */ char NickName[60+1];
	/* this+124 */ unsigned long GRID;
	/* this+128 */ unsigned long AID;
	/* this+132 */ unsigned long GID;
};


struct PACKET_ZI_INSTANTMAP_CREATE_RES
{// 0x29BF
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned int hRequestN2Obj;
	/* this+ 6 */ char mapName[16];
	/* this+22 */ int mapID;
	/* this+26 */ bool bSuccess;
};


struct PACKET_ZI_INSTANTMAP_ERROR
{// 0x29C4
	enum enumWhy { WHY_UNKNOWN = 0 };

	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned int hRequestN2Obj;
	/* this+ 6 */ int mapID;
	/* this+10 */ enum PACKET_ZI_INSTANTMAP_ERROR::enumWhy why;
};


struct PACKET_ZI_PING
{// 0x29C6
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned int UsedKBytesMemory;
	/* this+6 */ unsigned int NumTotalNPC;
};


struct PACKET_ZI_INSTANTMAP_ALLOW
{// 0x29C7
	enum enumWhy { WHY_ZSVR_SETTING, WHY_AGITWAR_START, WHY_AGITWAR_END };

	/* this+0 */ short PacketType;
	/* this+2 */ enum PACKET_ZI_INSTANTMAP_ALLOW::enumWhy why;
	/* this+6 */ bool bAllow;
};


struct PACKET_XX_CONNECT
{// 0x29C8
	/* this+0 */ short PacketType;
};


struct PACKET_XX_DISCONNECT
{// 0x29C9
	/* this+0 */ short PacketType;
};


struct PACKET_IZ_PARTY_BROADCAST
{// ????
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GID;
	/* this+6 */ unsigned long AID;
};


struct PACKET_IZ_MEMORIALDUNGEON_MSG : PACKET_IZ_PARTY_BROADCAST
{// 0x29CA
	enum enumNotify
	{
		MEMORIALDUNGEON_SUBSCRIPTION_ERROR_UNKNOWN = 0,
		MEMORIALDUNGEON_SUBSCRIPTION_ERROR_DUPLICATE = 1,
		MEMORIALDUNGEON_SUBSCRIPTION_ERROR_RIGHT = 2,
		MEMORIALDUNGEON_SUBSCRIPTION_ERROR_EXIST = 3,
		MEMORIALDUNGEON_SUBSCRIPTION_CANCEL_FAIL = 4,
		MEMORIALDUNGEON_SUBSCRIPTION_CANCEL_SUCCESS = 5,
		MEMORIALDUNGEON_CREATE_FAIL = 6,
		MEMORIALDUNGEON_SUBSCRIPTION_ERROR_CLOSE = 7,
	};

	/* this+ 0 */ public: //PACKET_IZ_PARTY_BROADCAST baseclass_0;
	/* this+10 */ public: enum PACKET_IZ_MEMORIALDUNGEON_MSG::enumNotify Notify;
	/* this+14 */ public: char MemorialDungeonName[61];
};


struct PACKET_ZI_PARTY_JOIN_REQ
{// 0x29CC
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long senderAID;
	/* this+ 6 */ unsigned long GRID;
	/* this+10 */ char TargetCharName[24];
};


struct PACKET_IZ_PARTY_JOIN_REQ_ACK
{// 0x29CD
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long requestAID;
	/* this+ 6 */ char characterName[24];
	/* this+30 */ enum PACKET_ZC_PARTY_JOIN_REQ_ACK::enumAnswer answer;
};


struct PACKET_IZ_PARTY_JOIN_REQ
{// 0x29CE
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long targetAID;
	/* this+ 6 */ unsigned long GRID;
	/* this+10 */ char groupName[24];
};


struct PACKET_ZI_PARTY_JOIN_REQ_ACK
{// 0x29CF
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long targetAID;
	/* this+ 6 */ unsigned long GRID;
	/* this+10 */ enum PACKET_ZC_PARTY_JOIN_REQ_ACK::enumAnswer answer;
};


struct PACKET_IZ_MEMORIALDUNGEON_SUBSCRIPTION_INFO : PACKET_IZ_PARTY_BROADCAST
{// 0x29D1
	/* this+ 0 */ //struct PACKET_IZ_PARTY_BROADCAST baseclass_0;
	/* this+10 */ char MemorialDungeonName[61];
	/* this+71 */ short PriorityOrderNum;
};


struct PACKET_IZ_MEMORIALDUNGEON_SUBSCRIPTION_NOTIFY : PACKET_IZ_PARTY_BROADCAST
{// 0x29D2
	/* this+ 0 */ //struct PACKET_IZ_PARTY_BROADCAST baseclass_0;
	/* this+10 */ short PriorityOrderNum;
};


struct PACKET_IZ_MEMORIALDUNGEON_INFO : PACKET_IZ_PARTY_BROADCAST
{// 0x29D3
	/* this+0 */ //struct PACKET_IZ_PARTY_BROADCAST baseclass_0;
	/* this+10 */ char MemorialDungeonName[61];
	/* this+71 */ unsigned long DestroyDate;
	/* this+75 */ unsigned long EnterTimeOutDate;
};


struct PACKET_IZ_MEMORIALDUNGEON_NOTIFY : PACKET_IZ_PARTY_BROADCAST
{// 0x29D4
	/* this+ 0 */ //struct PACKET_IZ_PARTY_BROADCAST baseclass_0;
	/* this+10 */ enum PACKET_ZC_MEMORIALDUNGEON_NOTIFY::enumTYPE Type;
	/* this+14 */ unsigned long EnterLimitDate;
};


struct PACKET_ZI_MEMORIALDUNGEON_COMMAND
{// 0x29D5
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GID;
	/* this+ 6 */ unsigned long AID;
	/* this+10 */ char partyName[24];
	/* this+34 */ enum PACKET_CZ_MEMORIALDUNGEON_COMMAND::enumCOMMAND Command;
};


struct PACKET_ZI_MEMORIALDUNGEON_VISA
{// 0x29D7
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GID;
	/* this+6 */ unsigned long AID;
};


struct PACKET_IZ_LEAVE_GROUP
{// 0x29DB
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
	/* this+6 */ unsigned long GID;
};


struct PACKET_ZI_MEMORIALDUNGEON_OPENSTATE
{// 0x29DC
	enum enumRequest { REQUEST_OPEN, REQUEST_CLOSE, REQUEST_UPDATE };

	/* this+ 0 */ short PacketType;
	/* this+ 2 */ enum PACKET_ZI_MEMORIALDUNGEON_OPENSTATE::enumRequest Request;
	/* this+ 6 */ unsigned long RequestGID;
	/* this+10 */ unsigned long RequestAID;
};


struct PACKET_ZI_GROUPINFO_CHANGE_V2
{// 0x29E8
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GRID;
	/* this+ 6 */ unsigned long MasterAID;
	/* this+10 */ int FamilyGroup;
	/* this+14 */ unsigned long expOption;
	/* this+18 */ unsigned char ItemPickupRule;
	/* this+19 */ unsigned char ItemDivisionRule;
};


struct PACKET_IZ_REQ_GROUPINFO_CHANGE_V2
{// 0x29E9
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GRID;
	/* this+10 */ unsigned long expOption;
	/* this+14 */ unsigned char ItemPickupRule;
	/* this+15 */ unsigned char ItemDivisionRule;
};


struct PACKET_ZI_CHANGE_GROUP_MASTER
{// 0x29EA
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GRID;
	/* this+ 6 */ unsigned long MasterAID;
	/* this+10 */ unsigned long AID;
};


struct PACKET_ZI_SEEK_PARTY
{// 0x29EE
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char Name[24];
	/* this+26 */ unsigned long Job;
	/* this+30 */ unsigned long Level;
	/* this+34 */ char mapName[16];
	/* this+50 */ unsigned long Option;
};


struct PACKET_IZ_SEEK_PARTY
{// 0x29EF
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char Name[24];
	/* this+26 */ unsigned long Job;
	/* this+30 */ unsigned long Level;
	/* this+34 */ char mapName[16];
	/* this+50 */ unsigned long Option;
};


struct PACKET_ZI_SEEK_PARTY_MEMBER
{// 0x29F0
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char Name[24];
	/* this+26 */ unsigned long Job;
	/* this+30 */ unsigned long Level;
	/* this+34 */ char mapName[16];
	/* this+50 */ unsigned long Option;
};


struct PACKET_IZ_SEEK_PARTY_MEMBER
{// 0x29F1
	/* this+ 0 */ public: short PacketType;
	/* this+ 2 */ public: char Name[24];
	/* this+26 */ public: unsigned long Job;
	/* this+30 */ public: unsigned long Level;
	/* this+34 */ public: char mapName[16];
	/* this+50 */ public: unsigned long Option;
};


#pragma pack(pop)
