struct PROTO_CZ_CHANGE_MAPTYPE
{
	short PacketType;
	short xPos;
	short yPos;
	short type;
};


struct PACKET_CZ_CHANGE_MAPTYPE
{
	/* this+0 */ short PacketType;
	/* this+2 */ short xPos;
	/* this+4 */ short yPos;
	/* this+6 */ short type;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_CHANGE_MAPTYPE> in(p);
		TPacket<PROTO_CZ_CHANGE_MAPTYPE> out;

		out->PacketType = PacketType;
		out->xPos = in->xPos;
		out->yPos = in->yPos;
		out->type = in->type;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_CHANGE_MAPTYPE> in(p);
		TPacket<PACKET_CZ_CHANGE_MAPTYPE> out;

		out->PacketType = PacketType;
		out->xPos = in->xPos;
		out->yPos = in->yPos;
		out->type = in->type;

		return out;
	}
};
