struct PROTO_ZC_AUTORUN_SKILL
{
	short PacketType;
	struct SKILLINFO
	{
		unsigned short SKID;
		int type;
		short level;
		short spcost;
		short attackRange;
		char skillName[24];
		bool upgradable;
	}
	data;
};


struct PACKET_ZC_AUTORUN_SKILL
{
	/* this+0 */ short PacketType;
	/* this+2 */ struct SKILLINFO
	             {
	             	/* this+ 0 */ unsigned short SKID;
	             	/* this+ 2 */ int type;
	             	/* this+ 6 */ short level;
	             	/* this+ 8 */ short spcost;
	             	/* this+10 */ short attackRange;
	             	/* this+12 */ char skillName[24];
	             	/* this+36 */ bool upgradable;
	             }
	             data;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_AUTORUN_SKILL> in(p);
		TPacket<PROTO_ZC_AUTORUN_SKILL> out;

		out->PacketType = PacketType;
		out->data.SKID = in->data.SKID;
		out->data.type = in->data.type;
		out->data.level = in->data.level;
		out->data.spcost = in->data.spcost;
		out->data.attackRange = in->data.attackRange;
		memcpy(out->data.skillName, in->data.skillName, 24);
		out->data.upgradable = in->data.upgradable;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_AUTORUN_SKILL> in(p);
		TPacket<PACKET_ZC_AUTORUN_SKILL> out;

		out->PacketType = PacketType;
		out->data.SKID = in->data.SKID;
		out->data.type = in->data.type;
		out->data.level = in->data.level;
		out->data.spcost = in->data.spcost;
		out->data.attackRange = in->data.attackRange;
		memcpy(out->data.skillName, in->data.skillName, 24);
		out->data.upgradable = in->data.upgradable;

		return out;
	}
};
