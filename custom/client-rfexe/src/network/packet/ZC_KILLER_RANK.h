struct PROTO_ZC_KILLER_RANK
{
	short PacketType;
	char Name[10][24];
	int Point[10];
};


struct PACKET_ZC_KILLER_RANK
{
	/* this+  0 */ short PacketType;
	/* this+  2 */ char Name[10][24];
	/* this+242 */ int Point[10];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_KILLER_RANK> in(p);
		TPacket<PROTO_ZC_KILLER_RANK> out;

		out->PacketType = PacketType;

		for( size_t i = 0; i < 10; ++i )
		{
			memcpy(out->Name[i], in->Name[i], 24);
			out->Point[i] = in->Point[i];
		}

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_KILLER_RANK> in(p);
		TPacket<PACKET_ZC_KILLER_RANK> out;

		out->PacketType = PacketType;

		for( size_t i = 0; i < 10; ++i )
		{
			memcpy(out->Name[i], in->Name[i], 24);
			out->Point[i] = in->Point[i];
		}

		return out;
	}
};
