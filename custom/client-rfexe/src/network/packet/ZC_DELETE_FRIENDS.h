struct PROTO_ZC_DELETE_FRIENDS
{
	short PacketType;
	unsigned long AID;
	unsigned long GID;
};


struct PACKET_ZC_DELETE_FRIENDS
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
	/* this+6 */ unsigned long GID;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_DELETE_FRIENDS> in(p);
		TPacket<PROTO_ZC_DELETE_FRIENDS> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->GID = in->GID;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_DELETE_FRIENDS> in(p);
		TPacket<PACKET_ZC_DELETE_FRIENDS> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->GID = in->GID;

		return out;
	}
};
