struct PROTO_CZ_CANCEL_LOCKON
{
	short PacketType;
};


struct PACKET_CZ_CANCEL_LOCKON
{
	/* this+0 */ short PacketType;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_CANCEL_LOCKON> in(p);
		TPacket<PROTO_CZ_CANCEL_LOCKON> out;

		out->PacketType = PacketType;
		
		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_CANCEL_LOCKON> in(p);
		TPacket<PACKET_CZ_CANCEL_LOCKON> out;

		out->PacketType = PacketType;

		return out;
	}
};
