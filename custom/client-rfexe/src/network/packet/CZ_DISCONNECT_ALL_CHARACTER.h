struct PROTO_CZ_DISCONNECT_ALL_CHARACTER
{
	short PacketType;
};


struct PACKET_CZ_DISCONNECT_ALL_CHARACTER
{
	/* this+0 */ short PacketType;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_DISCONNECT_ALL_CHARACTER> in(p);
		TPacket<PROTO_CZ_DISCONNECT_ALL_CHARACTER> out;

		out->PacketType = PacketType;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_DISCONNECT_ALL_CHARACTER> in(p);
		TPacket<PACKET_CZ_DISCONNECT_ALL_CHARACTER> out;

		out->PacketType = PacketType;

		return out;
	}
};
