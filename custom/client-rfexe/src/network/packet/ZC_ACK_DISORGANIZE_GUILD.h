struct PROTO_ZC_ACK_DISORGANIZE_GUILD
{
	short PacketType;
	char reasonDesc[40];
};


struct PACKET_ZC_ACK_DISORGANIZE_GUILD
{
	/* this+0 */ short PacketType;
	/* this+2 */ char reasonDesc[40];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ACK_DISORGANIZE_GUILD> in(p);
		TPacket<PROTO_ZC_ACK_DISORGANIZE_GUILD> out;

		out->PacketType = PacketType;
		memcpy(out->reasonDesc, in->reasonDesc, 40);

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_ACK_DISORGANIZE_GUILD> in(p);
		TPacket<PACKET_ZC_ACK_DISORGANIZE_GUILD> out;

		out->PacketType = PacketType;
		memcpy(out->reasonDesc, in->reasonDesc, 40);

		return out;
	}
};
