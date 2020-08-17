struct PROTO_CZ_REQ_WEAR_EQUIP
{
	short PacketType;
	unsigned short index;
	unsigned short wearLocation;
};


struct PACKET_CZ_REQ_WEAR_EQUIP
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short index;
	/* this+4 */ unsigned short wearLocation;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_REQ_WEAR_EQUIP> in(p);
		TPacket<PROTO_CZ_REQ_WEAR_EQUIP> out;

		out->PacketType = PacketType;
		out->index = in->index;
		out->wearLocation = in->wearLocation;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_REQ_WEAR_EQUIP> in(p);
		TPacket<PACKET_CZ_REQ_WEAR_EQUIP> out;

		out->PacketType = PacketType;
		out->index = in->index;
		out->wearLocation = in->wearLocation;

		return out;
	}
};
