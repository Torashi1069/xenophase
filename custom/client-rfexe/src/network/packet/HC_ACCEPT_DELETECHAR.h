struct PROTO_HC_ACCEPT_DELETECHAR
{
	short PacketType;
};


struct PACKET_HC_ACCEPT_DELETECHAR
{
	/* this+0 */ short PacketType;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_HC_ACCEPT_DELETECHAR> in(p);
		TPacket<PROTO_HC_ACCEPT_DELETECHAR> out;

		out->PacketType = PacketType;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_HC_ACCEPT_DELETECHAR> in(p);
		TPacket<PACKET_HC_ACCEPT_DELETECHAR> out;

		out->PacketType = PacketType;

		return out;
	}
};
