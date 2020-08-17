struct PROTO_CZ_PET_ACT
{
	short PacketType;
	int data;
};


struct PACKET_CZ_PET_ACT
{
	/* this+0 */ short PacketType;
	/* this+2 */ int data;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_PET_ACT> in(p);
		TPacket<PROTO_CZ_PET_ACT> out;

		out->PacketType = PacketType;
		out->data = in->data;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_PET_ACT> in(p);
		TPacket<PACKET_CZ_PET_ACT> out;

		out->PacketType = PacketType;
		out->data = in->data;

		return out;
	}
};
