struct PROTO_ZC_MSG_SKILL
{
	short PacketType;
	unsigned short SKID;
	int MSGID;
};


struct PACKET_ZC_MSG_SKILL
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short SKID;
	/* this+4 */ int MSGID;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_MSG_SKILL> in(p);
		TPacket<PROTO_ZC_MSG_SKILL> out;

		out->PacketType = PacketType;
		out->SKID = in->SKID;
		out->MSGID = in->MSGID;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_MSG_SKILL> in(p);
		TPacket<PACKET_ZC_MSG_SKILL> out;

		out->PacketType = PacketType;
		out->SKID = in->SKID;
		out->MSGID = in->MSGID;

		return out;
	}
};
