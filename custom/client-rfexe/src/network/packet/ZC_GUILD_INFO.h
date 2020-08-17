struct PROTO_ZC_GUILD_INFO
{
	short PacketType;
	int GDID;
	int level;
	int userNum;
	int maxUserNum;
	int userAverageLevel;
	int exp;
	int maxExp;
	int point;
	int honor;
	int virtue;
	int emblemVersion;
	char guildname[24];
	char masterName[24];
	char manageLand[16];
	int zeny;
};


struct PACKET_ZC_GUILD_INFO
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ int GDID;
	/* this+ 6 */ int level;
	/* this+10 */ int userNum;
	/* this+14 */ int maxUserNum;
	/* this+18 */ int userAverageLevel;
	/* this+22 */ int exp;
	/* this+26 */ int maxExp;
	/* this+30 */ int point;
	/* this+34 */ int honor;
	/* this+38 */ int virtue;
	/* this+42 */ int emblemVersion;
	/* this+46 */ char guildname[24];
	/* this+70 */ char masterName[24];
	/* this+94 */ char manageLand[16];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_GUILD_INFO> in(p);
		TPacket<PROTO_ZC_GUILD_INFO> out;

		out->PacketType = PacketType;
		out->GDID = in->GDID;
		out->level = in->level;
		out->userNum = in->userNum;
		out->maxUserNum = in->maxUserNum;
		out->userAverageLevel = in->userAverageLevel;
		out->exp = in->exp;
		out->maxExp = in->maxExp;
		out->point = in->point;
		out->honor = in->honor;
		out->virtue = in->virtue;
		out->emblemVersion = in->emblemVersion;
		memcpy(out->guildname, in->guildname, 24);
		memcpy(out->masterName, in->masterName, 24);
		memcpy(out->manageLand, in->manageLand, 16);
		out->zeny = 0; // adapt

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_GUILD_INFO> in(p);
		TPacket<PACKET_ZC_GUILD_INFO> out;

		out->PacketType = PacketType;
		out->GDID = in->GDID;
		out->level = in->level;
		out->userNum = in->userNum;
		out->maxUserNum = in->maxUserNum;
		out->userAverageLevel = in->userAverageLevel;
		out->exp = in->exp;
		out->maxExp = in->maxExp;
		out->point = in->point;
		out->honor = in->honor;
		out->virtue = in->virtue;
		out->emblemVersion = in->emblemVersion;
		memcpy(out->guildname, in->guildname, 24);
		memcpy(out->masterName, in->masterName, 24);
		memcpy(out->manageLand, in->manageLand, 16);
//		out->zeny = in->zeny; // adapt

		return out;
	}
};


struct PACKET_ZC_GUILD_INFO2
{
	/* this+  0 */ short PacketType;
	/* this+  2 */ int GDID;
	/* this+  6 */ int level;
	/* this+ 10 */ int userNum;
	/* this+ 14 */ int maxUserNum;
	/* this+ 18 */ int userAverageLevel;
	/* this+ 22 */ int exp;
	/* this+ 26 */ int maxExp;
	/* this+ 30 */ int point;
	/* this+ 34 */ int honor;
	/* this+ 38 */ int virtue;
	/* this+ 42 */ int emblemVersion;
	/* this+ 46 */ char guildname[24];
	/* this+ 70 */ char masterName[24];
	/* this+ 94 */ char manageLand[16];
	/* this+110 */ int zeny;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_GUILD_INFO2> in(p);
		TPacket<PROTO_ZC_GUILD_INFO> out;

		out->PacketType = PacketType;
		out->GDID = in->GDID;
		out->level = in->level;
		out->userNum = in->userNum;
		out->maxUserNum = in->maxUserNum;
		out->userAverageLevel = in->userAverageLevel;
		out->exp = in->exp;
		out->maxExp = in->maxExp;
		out->point = in->point;
		out->honor = in->honor;
		out->virtue = in->virtue;
		out->emblemVersion = in->emblemVersion;
		memcpy(out->guildname, in->guildname, 24);
		memcpy(out->masterName, in->masterName, 24);
		memcpy(out->manageLand, in->manageLand, 16);
		out->zeny = in->zeny;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_GUILD_INFO> in(p);
		TPacket<PACKET_ZC_GUILD_INFO2> out;

		out->PacketType = PacketType;
		out->GDID = in->GDID;
		out->level = in->level;
		out->userNum = in->userNum;
		out->maxUserNum = in->maxUserNum;
		out->userAverageLevel = in->userAverageLevel;
		out->exp = in->exp;
		out->maxExp = in->maxExp;
		out->point = in->point;
		out->honor = in->honor;
		out->virtue = in->virtue;
		out->emblemVersion = in->emblemVersion;
		memcpy(out->guildname, in->guildname, 24);
		memcpy(out->masterName, in->masterName, 24);
		memcpy(out->manageLand, in->manageLand, 16);
		out->zeny = in->zeny;

		return out;
	}
};
