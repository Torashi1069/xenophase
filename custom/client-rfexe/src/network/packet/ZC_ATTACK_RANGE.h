struct PROTO_ZC_ATTACK_RANGE
{
	short PacketType;
	short currentAttRange;
};


struct PACKET_ZC_ATTACK_RANGE
{
	/* this+0 */ short PacketType;
	/* this+2 */ short currentAttRange;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ATTACK_RANGE> in(p);
		TPacket<PROTO_ZC_ATTACK_RANGE> out;

		out->PacketType = PacketType;
		out->currentAttRange = in->currentAttRange;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_ATTACK_RANGE> in(p);
		TPacket<PACKET_ZC_ATTACK_RANGE> out;

		out->PacketType = PacketType;
		out->currentAttRange = in->currentAttRange;

		return out;
	}
};
