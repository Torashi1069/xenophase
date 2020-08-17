struct PROTO_ZC_SKILLINFO_LIST
{
	short PacketType;
	unsigned short PacketLength;
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
	SkillInfo[];
};


struct PACKET_ZC_SKILLINFO_LIST
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ struct SKILLINFO
	             {
	             	/* this+ 0 */ unsigned short SKID;
	             	/* this+ 2 */ int type;
	             	/* this+ 6 */ short level;
	             	/* this+ 8 */ short spcost;
	             	/* this+10 */ short attackRange;
	             	/* this+12 */ char skillName[24];
	             	/* this+36 */ bool upgradable;
	             }
	             SkillInfo[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_SKILLINFO_LIST,PACKET_ZC_SKILLINFO_LIST::SKILLINFO> in(p);
		TPacket<PROTO_ZC_SKILLINFO_LIST,PROTO_ZC_SKILLINFO_LIST::SKILLINFO> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->SkillInfo[i].SKID = in->SkillInfo[i].SKID;
			out->SkillInfo[i].type = in->SkillInfo[i].type;
			out->SkillInfo[i].level = in->SkillInfo[i].level;
			out->SkillInfo[i].spcost = in->SkillInfo[i].spcost;
			out->SkillInfo[i].attackRange = in->SkillInfo[i].attackRange;
			memcpy(out->SkillInfo[i].skillName, in->SkillInfo[i].skillName, 24);
			out->SkillInfo[i].upgradable = in->SkillInfo[i].upgradable;
		}

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_SKILLINFO_LIST,PROTO_ZC_SKILLINFO_LIST::SKILLINFO> in(p);
		TPacket<PROTO_ZC_SKILLINFO_LIST,PROTO_ZC_SKILLINFO_LIST::SKILLINFO> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->SkillInfo[i].SKID = in->SkillInfo[i].SKID;
			out->SkillInfo[i].type = in->SkillInfo[i].type;
			out->SkillInfo[i].level = in->SkillInfo[i].level;
			out->SkillInfo[i].spcost = in->SkillInfo[i].spcost;
			out->SkillInfo[i].attackRange = in->SkillInfo[i].attackRange;
			memcpy(out->SkillInfo[i].skillName, in->SkillInfo[i].skillName, 24);
			out->SkillInfo[i].upgradable = in->SkillInfo[i].upgradable;
		}

		return out;
	}
};
