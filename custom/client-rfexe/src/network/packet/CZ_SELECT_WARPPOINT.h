struct PROTO_CZ_SELECT_WARPPOINT
{
	short PacketType;
	unsigned short SKID;
	char mapName[16];
};


struct PACKET_CZ_SELECT_WARPPOINT
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short SKID;
	/* this+4 */ char mapName[16];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_SELECT_WARPPOINT> in(p);
		TPacket<PROTO_CZ_SELECT_WARPPOINT> out;

		out->PacketType = PacketType;
		out->SKID = in->SKID;
		memcpy(out->mapName, in->mapName, 16);

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_SELECT_WARPPOINT> in(p);
		TPacket<PACKET_CZ_SELECT_WARPPOINT> out;

		out->PacketType = PacketType;
		out->SKID = in->SKID;
		memcpy(out->mapName, in->mapName, 16);

		return out;
	}
};
