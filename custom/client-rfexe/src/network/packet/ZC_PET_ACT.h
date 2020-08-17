struct PROTO_ZC_PET_ACT
{
	short PacketType;
	int GID;
	int data;
};


struct PACKET_ZC_PET_ACT
{
	/* this+0 */ short PacketType;
	/* this+2 */ int GID;
	/* this+6 */ int data;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_PET_ACT> in(p);
		TPacket<PROTO_ZC_PET_ACT> out;

		out->PacketType = PacketType;
		out->GID = in->GID;
		out->data = in->data;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_PET_ACT> in(p);
		TPacket<PACKET_ZC_PET_ACT> out;

		out->PacketType = PacketType;
		out->GID = in->GID;
		out->data = in->data;

		return out;
	}
};
