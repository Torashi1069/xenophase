struct PROTO_CZ_ACK_GAME_GUARD
{
	short PacketType;
	unsigned long AuthData[4];
};


struct PACKET_CZ_ACK_GAME_GUARD
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AuthData[4];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_ACK_GAME_GUARD> in(p);
		TPacket<PROTO_CZ_ACK_GAME_GUARD> out;

		out->PacketType = PacketType;
		memcpy(out->AuthData, in->AuthData, 4 * sizeof(unsigned long));

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_ACK_GAME_GUARD> in(p);
		TPacket<PACKET_CZ_ACK_GAME_GUARD> out;

		out->PacketType = PacketType;
		memcpy(out->AuthData, in->AuthData, 4 * sizeof(unsigned long));

		return out;
	}
};
