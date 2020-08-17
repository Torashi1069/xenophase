struct PROTO_ZC_PETEGG_LIST
{
	short PacketType;
	short PacketLength;
	short List[]; // of itemIndex
};


struct PACKET_ZC_PETEGG_LIST
{
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ short List[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_PETEGG_LIST,short> in(p);
		TPacket<PROTO_ZC_PETEGG_LIST,short> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->List[i] = in->List[i];
		}

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_PETEGG_LIST,short> in(p);
		TPacket<PACKET_ZC_PETEGG_LIST,short> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->List[i] = in->List[i];
		}

		return out;
	}
};
