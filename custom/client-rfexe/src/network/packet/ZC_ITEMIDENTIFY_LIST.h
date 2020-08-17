struct PROTO_ZC_ITEMIDENTIFY_LIST
{
	short PacketType;
	unsigned short PacketLength;
	short Index[];
};


struct PACKET_ZC_ITEMIDENTIFY_LIST
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ short Index[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ITEMIDENTIFY_LIST,short> in(p);
		TPacket<PROTO_ZC_ITEMIDENTIFY_LIST,short> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Index[i] = in->Index[i];
		}

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_ITEMIDENTIFY_LIST,short> in(p);
		TPacket<PACKET_ZC_ITEMIDENTIFY_LIST,short> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Index[i] = in->Index[i];
		}

		return out;
	}
};
