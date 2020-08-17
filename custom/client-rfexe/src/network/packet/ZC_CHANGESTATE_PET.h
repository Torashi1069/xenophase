struct PROTO_ZC_CHANGESTATE_PET
{
	short PacketType;
	char type;
	int GID;
	int data;
};


struct PACKET_ZC_CHANGESTATE_PET
{
	/* this+0 */ short PacketType;
	/* this+2 */ char type;
	/* this+3 */ int GID;
	/* this+7 */ int data;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_CHANGESTATE_PET> in(p);
		TPacket<PROTO_ZC_CHANGESTATE_PET> out;

		out->PacketType = PacketType;
		out->type = in->type;
		out->GID = in->GID;
		out->data = in->data;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_CHANGESTATE_PET> in(p);
		TPacket<PACKET_ZC_CHANGESTATE_PET> out;

		out->PacketType = PacketType;
		out->type = in->type;
		out->GID = in->GID;
		out->data = in->data;

		return out;
	}
};
