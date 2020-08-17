struct PROTO_CZ_REQ_ENTER_ROOM
{
	short PacketType;
	unsigned long roomID;
	char passwd[8];
};


struct PACKET_CZ_REQ_ENTER_ROOM
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long roomID;
	/* this+6 */ char passwd[8];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_REQ_ENTER_ROOM> in(p);
		TPacket<PROTO_CZ_REQ_ENTER_ROOM> out;

		out->PacketType = PacketType;
		out->roomID = in->roomID;
		memcpy(out->passwd, in->passwd, 8);

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_REQ_ENTER_ROOM> in(p);
		TPacket<PACKET_CZ_REQ_ENTER_ROOM> out;

		out->PacketType = PacketType;
		out->roomID = in->roomID;
		memcpy(out->passwd, in->passwd, 8);

		return out;
	}
};
