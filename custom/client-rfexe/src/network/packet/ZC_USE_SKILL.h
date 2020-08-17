struct PROTO_ZC_USE_SKILL
{
	short PacketType;
	unsigned short SKID;
	short level;
	unsigned long targetAID;
	unsigned long srcAID;
	bool result;
};


struct PACKET_ZC_USE_SKILL
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short SKID;
	/* this+ 4 */ short level;
	/* this+ 6 */ unsigned long targetAID;
	/* this+10 */ unsigned long srcAID;
	/* this+14 */ bool result;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_USE_SKILL> in(p);
		TPacket<PROTO_ZC_USE_SKILL> out;

		out->PacketType = PacketType;
		out->SKID = in->SKID;
		out->level = in->level;
		out->targetAID = in->targetAID;
		out->srcAID = in->srcAID;
		out->result = in->result;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_USE_SKILL> in(p);
		TPacket<PACKET_ZC_USE_SKILL> out;

		out->PacketType = PacketType;
		out->SKID = in->SKID;
		out->level = in->level;
		out->targetAID = in->targetAID;
		out->srcAID = in->srcAID;
		out->result = in->result;

		return out;
	}
};
