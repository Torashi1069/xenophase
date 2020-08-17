struct PROTO_CZ_BLOCKING_PLAY_CANCEL
{
	short PacketType;
};


struct PACKET_CZ_BLOCKING_PLAY_CANCEL
{
	/* this+0 */ short PacketType;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_BLOCKING_PLAY_CANCEL> in(p);
		TPacket<PROTO_CZ_BLOCKING_PLAY_CANCEL> out;

		out->PacketType = PacketType;
		
		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_BLOCKING_PLAY_CANCEL> in(p);
		TPacket<PACKET_CZ_BLOCKING_PLAY_CANCEL> out;

		out->PacketType = PacketType;

		return out;
	}
};
