struct PROTO_CZ_REQ_CHANGECART
{
	short PacketType;
	short num;
};


struct PACKET_CZ_REQ_CHANGECART
{
	/* this+0 */ short PacketType;
	/* this+2 */ short num;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_REQ_CHANGECART> in(p);
		TPacket<PROTO_CZ_REQ_CHANGECART> out;

		out->PacketType = PacketType;
		out->num = in->num;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_REQ_CHANGECART> in(p);
		TPacket<PACKET_CZ_REQ_CHANGECART> out;

		out->PacketType = PacketType;
		out->num = in->num;

		return out;
	}
};
