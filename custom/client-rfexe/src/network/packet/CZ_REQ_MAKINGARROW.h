struct PROTO_CZ_REQ_MAKINGARROW
{
	short PacketType;
	unsigned short id;
};


struct PACKET_CZ_REQ_MAKINGARROW
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short id;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_REQ_MAKINGARROW> in(p);
		TPacket<PROTO_CZ_REQ_MAKINGARROW> out;

		out->PacketType = PacketType;
		out->id = in->id;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_REQ_MAKINGARROW> in(p);
		TPacket<PACKET_CZ_REQ_MAKINGARROW> out;

		out->PacketType = PacketType;
		out->id = in->id;

		return out;
	}
};
