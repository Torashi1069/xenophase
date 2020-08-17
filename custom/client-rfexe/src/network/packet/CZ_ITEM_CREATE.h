struct PROTO_CZ_ITEM_CREATE
{
	short PacketType;
	char itemName[24];
};


struct PACKET_CZ_ITEM_CREATE
{
	/* this+0 */ short PacketType;
	/* this+2 */ char itemName[24];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_ITEM_CREATE> in(p);
		TPacket<PROTO_CZ_ITEM_CREATE> out;

		out->PacketType = PacketType;
		memcpy(out->itemName, in->itemName, 24);

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_ITEM_CREATE> in(p);
		TPacket<PACKET_CZ_ITEM_CREATE> out;

		out->PacketType = PacketType;
		memcpy(out->itemName, in->itemName, 24);

		return out;
	}
};
