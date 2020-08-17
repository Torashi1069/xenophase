struct PROTO_ZC_SKILL_POSTDELAY
{
	short PacketType;
	unsigned short SKID;
	unsigned long DelayTM;
};


struct PACKET_ZC_SKILL_POSTDELAY
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short SKID;
	/* this+4 */ unsigned long DelayTM;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_SKILL_POSTDELAY> in(p);
		TPacket<PROTO_ZC_SKILL_POSTDELAY> out;

		out->PacketType = PacketType;
		out->SKID = in->SKID;
		out->DelayTM = in->DelayTM;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_SKILL_POSTDELAY> in(p);
		TPacket<PACKET_ZC_SKILL_POSTDELAY> out;

		out->PacketType = PacketType;
		out->SKID = in->SKID;
		out->DelayTM = in->DelayTM;

		return out;
	}
};
