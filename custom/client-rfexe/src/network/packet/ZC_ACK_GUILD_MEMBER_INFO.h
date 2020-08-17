struct PROTO_ZC_ACK_GUILD_MEMBER_INFO
{
	short PacketType;
	struct GUILD_MEMBER_INFO
	{
		int AID;
		int GID;
		short head;
		short headPalette;
		short sex;
		short job;
		short level;
		int contributionExp;
		int currentState;
		int positionID;
		char intro[50];
		char charname[24];
	}
	Info;
};


struct PACKET_ZC_ACK_GUILD_MEMBER_INFO
{
	/* this+0 */ short PacketType;
	/* this+2 */ struct GUILD_MEMBER_INFO
	             {
	             	/* this+ 0 */ int AID;
	             	/* this+ 4 */ int GID;
	             	/* this+ 8 */ short head;
	             	/* this+10 */ short headPalette;
	             	/* this+12 */ short sex;
	             	/* this+14 */ short job;
	             	/* this+16 */ short level;
	             	/* this+18 */ int contributionExp;
	             	/* this+22 */ int currentState;
	             	/* this+26 */ int positionID;
	             	/* this+30 */ char intro[50];
	             	/* this+80 */ char charname[24];
	             }
	             Info;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ACK_GUILD_MEMBER_INFO> in(p);
		TPacket<PROTO_ZC_ACK_GUILD_MEMBER_INFO> out;

		out->PacketType = PacketType;
		out->Info.AID = in->Info.AID;
		out->Info.GID = in->Info.GID;
		out->Info.head = in->Info.head;
		out->Info.headPalette = in->Info.headPalette;
		out->Info.sex = in->Info.sex;
		out->Info.job = in->Info.job;
		out->Info.level = in->Info.level;
		out->Info.contributionExp = in->Info.contributionExp;
		out->Info.currentState = in->Info.currentState;
		out->Info.positionID = in->Info.positionID;
		memcpy(out->Info.intro, in->Info.intro, 50);
		memcpy(out->Info.charname, in->Info.charname, 24);

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_ACK_GUILD_MEMBER_INFO> in(p);
		TPacket<PACKET_ZC_ACK_GUILD_MEMBER_INFO> out;

		out->PacketType = PacketType;
		out->Info.AID = in->Info.AID;
		out->Info.GID = in->Info.GID;
		out->Info.head = in->Info.head;
		out->Info.headPalette = in->Info.headPalette;
		out->Info.sex = in->Info.sex;
		out->Info.job = in->Info.job;
		out->Info.level = in->Info.level;
		out->Info.contributionExp = in->Info.contributionExp;
		out->Info.currentState = in->Info.currentState;
		out->Info.positionID = in->Info.positionID;
		memcpy(out->Info.intro, in->Info.intro, 50);
		memcpy(out->Info.charname, in->Info.charname, 24);

		return out;
	}
};
