struct PROTO_HC_BLOCK_CHARACTER
{
	short PacketType;
	unsigned short PacketLength;
	struct TAG_CHARACTER_BLOCK_INFO
	{
		unsigned long GID;
		char szExpireDate[20];
	}
	Info[];
};


struct PACKET_HC_BLOCK_CHARACTER
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ struct TAG_CHARACTER_BLOCK_INFO
	             {
	             	/* this+0 */ unsigned long GID;
	             	/* this+4 */ char szExpireDate[20];
	             }
	             Info[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_HC_BLOCK_CHARACTER,PACKET_HC_BLOCK_CHARACTER::TAG_CHARACTER_BLOCK_INFO> in(p);
		TPacket<PROTO_HC_BLOCK_CHARACTER,PROTO_HC_BLOCK_CHARACTER::TAG_CHARACTER_BLOCK_INFO> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Info[i].GID = in->Info[i].GID;
			memcpy(out->Info[i].szExpireDate, in->Info[i].szExpireDate, 20);
		}

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_HC_BLOCK_CHARACTER,PROTO_HC_BLOCK_CHARACTER::TAG_CHARACTER_BLOCK_INFO> in(p);
		TPacket<PACKET_HC_BLOCK_CHARACTER,PACKET_HC_BLOCK_CHARACTER::TAG_CHARACTER_BLOCK_INFO> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Info[i].GID = in->Info[i].GID;
			memcpy(out->Info[i].szExpireDate, in->Info[i].szExpireDate, 20);
		}

		return out;
	}
};
