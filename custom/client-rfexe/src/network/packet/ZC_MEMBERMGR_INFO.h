struct PROTO_ZC_MEMBERMGR_INFO
{
	short PacketType;
	short PacketLength;
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
	Info[];
};


struct PACKET_ZC_MEMBERMGR_INFO
{
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ struct GUILD_MEMBER_INFO
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
	             Info[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_MEMBERMGR_INFO,PACKET_ZC_MEMBERMGR_INFO::GUILD_MEMBER_INFO> in(p);
		TPacket<PROTO_ZC_MEMBERMGR_INFO,PACKET_ZC_MEMBERMGR_INFO::GUILD_MEMBER_INFO> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Info[i].AID = in->Info[i].AID;
			out->Info[i].GID = in->Info[i].GID;
			out->Info[i].head = in->Info[i].head;
			out->Info[i].headPalette = in->Info[i].headPalette;
			out->Info[i].sex = in->Info[i].sex;
			out->Info[i].job = in->Info[i].job;
			out->Info[i].level = in->Info[i].level;
			out->Info[i].contributionExp = in->Info[i].contributionExp;
			out->Info[i].currentState = in->Info[i].currentState;
			out->Info[i].positionID = in->Info[i].positionID;
			memcpy(out->Info[i].intro, in->Info[i].intro, 50);
			memcpy(out->Info[i].charname, in->Info[i].charname, 24);
		}

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_MEMBERMGR_INFO,PROTO_ZC_MEMBERMGR_INFO::GUILD_MEMBER_INFO> in(p);
		TPacket<PACKET_ZC_MEMBERMGR_INFO,PACKET_ZC_MEMBERMGR_INFO::GUILD_MEMBER_INFO> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Info[i].AID = in->Info[i].AID;
			out->Info[i].GID = in->Info[i].GID;
			out->Info[i].head = in->Info[i].head;
			out->Info[i].headPalette = in->Info[i].headPalette;
			out->Info[i].sex = in->Info[i].sex;
			out->Info[i].job = in->Info[i].job;
			out->Info[i].level = in->Info[i].level;
			out->Info[i].contributionExp = in->Info[i].contributionExp;
			out->Info[i].currentState = in->Info[i].currentState;
			out->Info[i].positionID = in->Info[i].positionID;
			memcpy(out->Info[i].intro, in->Info[i].intro, 50);
			memcpy(out->Info[i].charname, in->Info[i].charname, 24);
		}

		return out;
	}
};
