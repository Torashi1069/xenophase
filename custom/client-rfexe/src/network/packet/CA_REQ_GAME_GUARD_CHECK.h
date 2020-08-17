struct PROTO_CA_REQ_GAME_GUARD_CHECK
{
	short PacketType;
};


struct PACKET_CA_REQ_GAME_GUARD_CHECK
{
	/* this+0 */ short PacketType;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CA_REQ_GAME_GUARD_CHECK> in(p);
		TPacket<PROTO_CA_REQ_GAME_GUARD_CHECK> out;

		out->PacketType = PacketType;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CA_REQ_GAME_GUARD_CHECK> in(p);
		TPacket<PACKET_CA_REQ_GAME_GUARD_CHECK> out;

		out->PacketType = PacketType;

		return out;
	}
};
