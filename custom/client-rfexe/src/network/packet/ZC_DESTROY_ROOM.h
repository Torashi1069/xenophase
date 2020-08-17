struct PROTO_ZC_DESTROY_ROOM
{
	short PacketType;
	unsigned long roomID;
};


struct PACKET_ZC_DESTROY_ROOM
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long roomID;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_DESTROY_ROOM> in(p);
		TPacket<PROTO_ZC_DESTROY_ROOM> out;

		out->PacketType = PacketType;
		out->roomID = in->roomID;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_DESTROY_ROOM> in(p);
		TPacket<PACKET_ZC_DESTROY_ROOM> out;

		out->PacketType = PacketType;
		out->roomID = in->roomID;

		return out;
	}
};
