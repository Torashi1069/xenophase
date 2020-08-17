#pragma once
#include "globals.hpp"
#include "std/string"
class CAcceptHandler;
class CAsyncStream;


struct CAsyncOperation : public OVERLAPPED
{
	/* this+0x0    */ //OVERLAPPED
	/* this+0x14   */ WSABUF m_dataBuf;
	/* this+0x1C   */ char m_buffer[10240];
	/* this+0x281C */ int m_type;
	/* this+0x2820 */ unsigned int m_socket;
	/* this+0x2824 */ CAsyncStream* m_stream;

	enum
	{
		RECV = 0x0,
		SEND = 0x1,
	};
};


struct STRUCT_FRIEND
{
	/* this+0 */ unsigned long AID;
	/* this+4 */ unsigned long GID;
	/* this+8 */ char Name[24];
};


struct MAILTIME
{
	/* this+0x0 */ short Year;
	/* this+0x2 */ short Month;
	/* this+0x4 */ short Day;
	/* this+0x6 */ short Hour;
};


struct DBMAILINFO
{
	/* this+0x0   */ unsigned long MailID;
	/* this+0x4   */ unsigned long AID;
	/* this+0x8   */ unsigned long GID;
	/* this+0xC   */ char Header[40];
	/* this+0x34  */ int Reading;
	/* this+0x38  */ char ItemInfo[40];
	/* this+0x60  */ int ItemLen;
	/* this+0x64  */ unsigned long Money;
	/* this+0x68  */ char FromName[24];
	/* this+0x80  */ char Text[200];
	/* this+0x148 */ MAILTIME DeleteTime;
};


struct USER_STRING_MAP_DATA
{
	/* this+0x0   */ unsigned long AID;
	/* this+0x4   */ unsigned long GID;
	/* this+0x8   */ unsigned long ServerID;
	/* this+0xC   */ unsigned long GRID;
	/* this+0x10  */ int sex;
	/* this+0x14  */ short age;
	/* this+0x16  */ short level;
	/* this+0x18  */ short job;
	/* this+0x1A  */ short head;
	/* this+0x1C  */ short headpalette;
	/* this+0x1E  */ char accountName[24];
	/* this+0x36  */ char characterName[24];
	/* this+0x4E  */ char mapName[16];
	/* this+0x5E  */ struct STRUCT_FRIEND Friends[MAX_FRIENDS_LIST];
	/* this+0x55E */ int FriendNumber;
	/* this+0x562 */ int MailCounter;
	/* this+0x566 */ struct DBMAILINFO MailInfo[60];
};


struct _ACCEPT_PARM
{
	/* this+0x0  */ unsigned long ip;
	/* this+0x4  */ short port;
	/* this+0x8  */ int backlog;
	/* this+0xC  */ unsigned int ipLog;
	/* this+0x10 */ CAcceptHandler* handler;
};


struct _SERVERINFO
{
	/* this+0x0  */ int SID;
	/* this+0x4  */ int Type;
	/* this+0x8  */ unsigned long ip;
	/* this+0xC  */ mystd::string IPstr;
	/* this+0x28 */ int Port;
	/* this+0x2C */ int DestinationOneSID;
	/* this+0x30 */ int DestinationTwoSID;
	/* this+0x34 */ char Name[20];
	/* this+0x48 */ unsigned long PrivateIP;
	/* this+0x4C */ mystd::string PrivateIPstr;
	/* this+0x68 */ int PrivatePort;

	//public: void _SERVERINFO::_SERVERINFO();
	//public: void _SERVERINFO::~_SERVERINFO();
};


struct GUILDNOTICE
{
	/* this+0x0  */ int GDID;
	/* this+0x4  */ char Subject[60];
	/* this+0x40 */ char Notice[120];
};


struct GUILDMINFO
{ 
	/* this+  0 */ int GID;
	/* this+  4 */ char CharName[24];
	/* this+ 28 */ char AccountName[24];
	/* this+ 52 */ int Level;
	/* this+ 56 */ char Memo[50];
	/* this+106 */ int Service;
	/* this+110 */ int MemberExp;
	/* this+114 */ int GDID;
	/* this+118 */ int AID;
	/* this+122 */ int PositionID;
	/* this+126 */ short head;
	/* this+128 */ short headPalette;
	/* this+130 */ short sex;
	/* this+132 */ int job;
	/* this+136 */ int status;
};


struct GUILDALLYINFO
{
	/* this+0x0  */ int GDID;
	/* this+0x4  */ int OpponentGDID;
	/* this+0x8  */ char GuildName[24];
	/* this+0x20 */ int Relation;
};


struct GUILDBANISHINFO
{
	/* this+0x0  */ int GDID;
	/* this+0x4  */ char MemberName[24];
	/* this+0x1C */ char MemberAccount[24];
	/* this+0x34 */ char Reason[50];
	/* this+0x66 */ int GID;
	/* this+0x6A */ int AID;
};


struct GUILDMPOSITION
{
	/* this+0x0  */ int GDID;
	/* this+0x4  */ int Grade;
	/* this+0x8  */ char PosName[24];
	/* this+0x20 */ int JoinRight;
	/* this+0x24 */ int PenaltyRight;
	/* this+0x28 */ int PositionID;
	/* this+0x2C */ int Service;
};


struct GROUP_INFO
{
	/* this+0x0 */ unsigned long expOption;
	/* this+0x4 */ unsigned char ItemPickupRule;
	/* this+0x5 */ unsigned char ItemDivisionRule;
};


struct GROUPMEMBER_INFO
{
	/* this+ 0 */ unsigned long AID;
	/* this+ 4 */ char characterName[24];
	/* this+28 */ char mapName[16];
	/* this+44 */ unsigned char role;
	/* this+45 */ unsigned char state;
};


struct CHARINFO_IN_GROUP
{
	/* this+0x0  */ unsigned long AID;
	/* this+0x4  */ unsigned long GID;
	/* this+0x8  */ char charName[24];
	/* this+0x20 */ unsigned char Role;
	/* this+0x21 */ unsigned char curState;
};


struct MapInfo
{
	/* this+0x0  */ bool bPlayerEnter;
	/* this+0x4  */ int ZSID;
	/* this+0x8  */ int MapID;
	/* this+0xC  */ int type;
	/* this+0x10 */ char Name[24];

	//public: void MapInfo::MapInfo();
};
