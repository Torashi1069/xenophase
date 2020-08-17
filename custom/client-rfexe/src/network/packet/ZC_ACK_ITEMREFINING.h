struct PROTO_ZC_ACK_ITEMREFINING
{
	short PacketType;
	short result;
	short itemIndex;
	short refiningLevel;
};


struct PACKET_ZC_ACK_ITEMREFINING
{
	/* this+0 */ short PacketType;
	/* this+2 */ short result;
	/* this+4 */ short itemIndex;
	/* this+6 */ short refiningLevel;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ACK_ITEMREFINING> in(p);
		TPacket<PROTO_ZC_ACK_ITEMREFINING> out;

		out->PacketType = PacketType;
		out->result = in->result;
		out->itemIndex = in->itemIndex;
		out->refiningLevel = in->refiningLevel;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_ACK_ITEMREFINING> in(p);
		TPacket<PACKET_ZC_ACK_ITEMREFINING> out;

		out->PacketType = PacketType;
		out->result = in->result;
		out->itemIndex = in->itemIndex;
		out->refiningLevel = in->refiningLevel;

		return out;
	}
};
