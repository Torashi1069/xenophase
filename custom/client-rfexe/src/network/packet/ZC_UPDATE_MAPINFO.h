struct PROTO_ZC_UPDATE_MAPINFO
{
	short PacketType;
	short xPos;
	short yPos;
	short type;
	char mapName[16];
};


struct PACKET_ZC_UPDATE_MAPINFO
{
	/* this+0 */ short PacketType;
	/* this+2 */ short xPos;
	/* this+4 */ short yPos;
	/* this+6 */ short type;
	/* this+8 */ char mapName[16];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_UPDATE_MAPINFO> in(p);
		TPacket<PROTO_ZC_UPDATE_MAPINFO> out;

		out->PacketType = PacketType;
		out->xPos = in->xPos;
		out->yPos = in->yPos;
		out->type = in->type;
		memcpy(out->mapName, in->mapName, 16);

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_UPDATE_MAPINFO> in(p);
		TPacket<PACKET_ZC_UPDATE_MAPINFO> out;

		out->PacketType = PacketType;
		out->xPos = in->xPos;
		out->yPos = in->yPos;
		out->type = in->type;
		memcpy(out->mapName, in->mapName, 16);

		return out;
	}
};
