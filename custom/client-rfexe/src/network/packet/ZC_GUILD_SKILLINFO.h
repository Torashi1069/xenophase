struct PROTO_ZC_GUILD_SKILLINFO
{
	short PacketType;
	short PacketLength;
	short skillPoint;
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
	Info[];
};


struct PACKET_ZC_GUILD_SKILLINFO
{
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ short skillPoint;
	/* this+6 */ struct SKILLINFO
	             {
	             	/* this+ 0 */ unsigned short SKID;
	             	/* this+ 2 */ int type;
	             	/* this+ 6 */ short level;
	             	/* this+ 8 */ short spcost;
	             	/* this+10 */ short attackRange;
	             	/* this+12 */ char skillName[24];
	             	/* this+36 */ bool upgradable;
	             }
	             Info[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_GUILD_SKILLINFO,PACKET_ZC_GUILD_SKILLINFO::SKILLINFO> in(p);
		TPacket<PROTO_ZC_GUILD_SKILLINFO,PACKET_ZC_GUILD_SKILLINFO::SKILLINFO> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->skillPoint = in->skillPoint;

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Info[i].SKID = in->Info[i].SKID;
			out->Info[i].type = in->Info[i].type;
			out->Info[i].level = in->Info[i].level;
			out->Info[i].spcost = in->Info[i].spcost;
			out->Info[i].attackRange = in->Info[i].attackRange;
			memcpy(out->Info[i].skillName, in->Info[i].skillName, 24);
			out->Info[i].upgradable = in->Info[i].upgradable;
		}

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_GUILD_SKILLINFO,PROTO_ZC_GUILD_SKILLINFO::SKILLINFO> in(p);
		TPacket<PACKET_ZC_GUILD_SKILLINFO,PACKET_ZC_GUILD_SKILLINFO::SKILLINFO> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->skillPoint = in->skillPoint;

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Info[i].SKID = in->Info[i].SKID;
			out->Info[i].type = in->Info[i].type;
			out->Info[i].level = in->Info[i].level;
			out->Info[i].spcost = in->Info[i].spcost;
			out->Info[i].attackRange = in->Info[i].attackRange;
			memcpy(out->Info[i].skillName, in->Info[i].skillName, 24);
			out->Info[i].upgradable = in->Info[i].upgradable;
		}

		return out;
	}
};
