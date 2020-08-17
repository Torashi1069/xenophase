struct PROTO_ZC_SKILLINFO_UPDATE
{
	short PacketType;
	int PacketVersion; // 1:basic, 2:w/skilltype
	unsigned short SKID;
	int type; // enum SKILLTYPE_*
	short level;
	short spcost;
	short attackRange;
	bool upgradable;
};


struct PACKET_ZC_SKILLINFO_UPDATE
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short SKID;
	/* this+ 4 */ short level;
	/* this+ 6 */ short spcost;
	/* this+ 8 */ short attackRange;
	/* this+10 */ bool upgradable;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_SKILLINFO_UPDATE> in(p);
		TPacket<PROTO_ZC_SKILLINFO_UPDATE> out;

		out->PacketType = PacketType;
		out->PacketVersion = 1;
		out->SKID = in->SKID;
		out->type = 0; // SKILLTYPE_PASSIVE // adapt // broken
		out->level = in->level;
		out->spcost = in->spcost;
		out->attackRange = in->attackRange;
		out->upgradable = in->upgradable;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_SKILLINFO_UPDATE> in(p);
		TPacket<PACKET_ZC_SKILLINFO_UPDATE> out;

		out->PacketType = PacketType;
		out->SKID = in->SKID;
//		out->type = in->type; // adapt
		out->level = in->level;
		out->spcost = in->spcost;
		out->attackRange = in->attackRange;
		out->upgradable = in->upgradable;

		return out;
	}
};


struct PACKET_ZC_SKILLINFO_UPDATE2
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short SKID;
	/* this+ 4 */ int type;
	/* this+ 8 */ short level;
	/* this+10 */ short spcost;
	/* this+12 */ short attackRange;
	/* this+14 */ bool upgradable;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_SKILLINFO_UPDATE2> in(p);
		TPacket<PROTO_ZC_SKILLINFO_UPDATE> out;

		out->PacketType = PacketType;
		out->PacketVersion = 2;
		out->SKID = in->SKID;
		out->type = in->type;
		out->level = in->level;
		out->spcost = in->spcost;
		out->attackRange = in->attackRange;
		out->upgradable = in->upgradable;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_SKILLINFO_UPDATE> in(p);
		if( in->PacketVersion < 2 ) return NULL;
		TPacket<PACKET_ZC_SKILLINFO_UPDATE2> out;

		out->PacketType = PacketType;
		out->SKID = in->SKID;
		out->type = in->type;
		out->level = in->level;
		out->spcost = in->spcost;
		out->attackRange = in->attackRange;
		out->upgradable = in->upgradable;

		return out;
	}
};
