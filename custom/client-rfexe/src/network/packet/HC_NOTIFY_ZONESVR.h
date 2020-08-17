struct PROTO_HC_NOTIFY_ZONESVR
{
	short PacketType;
	unsigned long GID;
	unsigned char mapName[16];
	struct ZSERVER_ADDR
	{
		unsigned long ip;
		short port;
	}
	addr;
};


struct PACKET_HC_NOTIFY_ZONESVR
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GID;
	/* this+ 6 */ unsigned char mapName[16];
	/* this+22 */ struct ZSERVER_ADDR
	              {
	              	/* this+0 */ unsigned long ip;
	              	/* this+4 */ short port;
	              }
	              addr;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_HC_NOTIFY_ZONESVR> in(p);
		TPacket<PROTO_HC_NOTIFY_ZONESVR> out;

		out->PacketType = PacketType;
		out->GID = in->GID;
		memcpy(out->mapName, in->mapName, 16);
		out->addr.ip = in->addr.ip;
		out->addr.port = in->addr.port;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_HC_NOTIFY_ZONESVR> in(p);
		TPacket<PACKET_HC_NOTIFY_ZONESVR> out;

		out->PacketType = PacketType;
		out->GID = in->GID;
		memcpy(out->mapName, in->mapName, 16);
		out->addr.ip = in->addr.ip;
		out->addr.port = in->addr.port;

		return out;
	}
};
