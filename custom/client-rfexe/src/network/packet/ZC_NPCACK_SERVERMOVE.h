struct PROTO_ZC_NPCACK_SERVERMOVE
{
	short PacketType;
	char mapName[16];
	short xPos;
	short yPos;
	struct ZSERVER_ADDR
	{
		unsigned long ip;
		short port;
	}
	addr;
};


struct PACKET_ZC_NPCACK_SERVERMOVE
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char mapName[16];
	/* this+18 */ short xPos;
	/* this+20 */ short yPos;
	/* this+22 */ struct ZSERVER_ADDR
	              {
	              	/* this+0 */ unsigned long ip;
	              	/* this+4 */ short port;
	              }
	              addr;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NPCACK_SERVERMOVE> in(p);
		TPacket<PROTO_ZC_NPCACK_SERVERMOVE> out;

		out->PacketType = PacketType;
		memcpy(out->mapName, in->mapName, 16);
		out->xPos = in->xPos;
		out->yPos = in->yPos;
		out->addr.ip = in->addr.ip;
		out->addr.port = in->addr.port;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_NPCACK_SERVERMOVE> in(p);
		TPacket<PACKET_ZC_NPCACK_SERVERMOVE> out;

		out->PacketType = PacketType;
		memcpy(out->mapName, in->mapName, 16);
		out->xPos = in->xPos;
		out->yPos = in->yPos;
		out->addr.ip = in->addr.ip;
		out->addr.port = in->addr.port;

		return out;
	}
};
