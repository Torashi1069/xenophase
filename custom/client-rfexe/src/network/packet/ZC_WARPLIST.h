struct PROTO_ZC_WARPLIST
{
	short PacketType;
	unsigned short SKID;
	char mapName[4][16];
};


struct PACKET_ZC_WARPLIST
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short SKID;
	/* this+4 */ char mapName[4][16];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_WARPLIST> in(p);
		TPacket<PROTO_ZC_WARPLIST> out;

		out->PacketType = PacketType;
		out->SKID = in->SKID;

		for( size_t i = 0; i < countof(out->mapName); ++i )
		{
			memcpy(out->mapName[i], in->mapName[i], 16);
		}

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_WARPLIST> in(p);
		TPacket<PACKET_ZC_WARPLIST> out;

		out->PacketType = PacketType;
		out->SKID = in->SKID;

		for( size_t i = 0; i < countof(out->mapName); ++i )
		{
			memcpy(out->mapName[i], in->mapName[i], 16);
		}

		return out;
	}
};
