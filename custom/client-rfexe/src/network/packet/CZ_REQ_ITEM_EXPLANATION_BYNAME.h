struct PROTO_CZ_REQ_ITEM_EXPLANATION_BYNAME
{
	short PacketType;
	short unknown;
};


struct PACKET_CZ_REQ_ITEM_EXPLANATION_BYNAME
{
	/* this+0 */ short PacketType;
	/* this+2 */ short unknown;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_REQ_ITEM_EXPLANATION_BYNAME> in(p);
		TPacket<PROTO_CZ_REQ_ITEM_EXPLANATION_BYNAME> out;

		out->PacketType = PacketType;
		out->unknown = in->unknown;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_REQ_ITEM_EXPLANATION_BYNAME> in(p);
		TPacket<PACKET_CZ_REQ_ITEM_EXPLANATION_BYNAME> out;

		out->PacketType = PacketType;
		out->unknown = in->unknown;

		return out;
	}
};
