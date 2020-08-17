struct PROTO_ZC_SKILL_POSTDELAY_LIST
{
	short PacketType;
	short PacketLength;
	struct tagSkillPostDelay
	{
		unsigned short SKID;
		unsigned long DelayTM;
	}
	List[];
};


struct PACKET_ZC_SKILL_POSTDELAY_LIST
{
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ struct tagSkillPostDelay
	             {
	             	/* this+0 */ unsigned short SKID;
	             	/* this+2 */ unsigned long DelayTM;
	             }
	             List[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_SKILL_POSTDELAY_LIST,PACKET_ZC_SKILL_POSTDELAY_LIST::tagSkillPostDelay> in(p);
		TPacket<PROTO_ZC_SKILL_POSTDELAY_LIST,PROTO_ZC_SKILL_POSTDELAY_LIST::tagSkillPostDelay> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->List[i].SKID = in->List[i].SKID;
			out->List[i].DelayTM = in->List[i].DelayTM;
		}

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_SKILL_POSTDELAY_LIST,PROTO_ZC_SKILL_POSTDELAY_LIST::tagSkillPostDelay> in(p);
		TPacket<PACKET_ZC_SKILL_POSTDELAY_LIST,PACKET_ZC_SKILL_POSTDELAY_LIST::tagSkillPostDelay> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->List[i].SKID = in->List[i].SKID;
			out->List[i].DelayTM = in->List[i].DelayTM;
		}

		return out;
	}
};
