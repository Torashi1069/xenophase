struct PROTO_CZ_ADD_FRIENDS
{
	short PacketType;
	char name[24];
};


struct PACKET_CZ_ADD_FRIENDS
{
	/* this+0 */ short PacketType;
	/* this+2 */ char name[24];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_ADD_FRIENDS> in(p);
		TPacket<PROTO_CZ_ADD_FRIENDS> out;

		out->PacketType = PacketType;
		memcpy(out->name, in->name, 24);

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_ADD_FRIENDS> in(p);
		TPacket<PACKET_CZ_ADD_FRIENDS> out;

		out->PacketType = PacketType;
		memcpy(out->name, in->name, 24);

		return out;
	}
};
