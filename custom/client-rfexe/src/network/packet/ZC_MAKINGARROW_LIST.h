struct PROTO_ZC_MAKINGARROW_LIST
{
	short PacketType;
	unsigned short PacketLength;
	unsigned short ITID[];
};


struct PACKET_ZC_MAKINGARROW_LIST
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ unsigned short ITID[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_MAKINGARROW_LIST,unsigned short> in(p);
		TPacket<PROTO_ZC_MAKINGARROW_LIST,unsigned short> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->ITID[i] = in->ITID[i];
		}

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_MAKINGARROW_LIST,unsigned short> in(p);
		TPacket<PACKET_ZC_MAKINGARROW_LIST,unsigned short> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->ITID[i] = in->ITID[i];
		}

		return out;
	}
};
