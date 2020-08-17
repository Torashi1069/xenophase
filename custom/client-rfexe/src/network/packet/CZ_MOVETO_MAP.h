struct PROTO_CZ_MOVETO_MAP
{
	short PacketType;
	char mapName[16];
	short xPos;
	short yPos;
};


struct PACKET_CZ_MOVETO_MAP
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char mapName[16];
	/* this+18 */ short xPos;
	/* this+20 */ short yPos;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_MOVETO_MAP> in(p);
		TPacket<PROTO_CZ_MOVETO_MAP> out;

		out->PacketType = PacketType;
		memcpy(out->mapName, in->mapName, 16);
		out->xPos = in->xPos;
		out->yPos = in->yPos;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_MOVETO_MAP> in(p);
		TPacket<PACKET_CZ_MOVETO_MAP> out;

		out->PacketType = PacketType;
		memcpy(out->mapName, in->mapName, 16);
		out->xPos = in->xPos;
		out->yPos = in->yPos;

		return out;
	}
};
