struct PROTO_ZC_WHISPER_LIST
{
	short PacketType;
	short PacketLength;
	char List[][24];
};


struct PACKET_ZC_WHISPER_LIST
{
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ char List[][24];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_WHISPER_LIST,char[24]> in(p);
		TPacket<PROTO_ZC_WHISPER_LIST,char[24]> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		for( size_t i = 0; i < out.count(); ++i )
		{
			memcpy(out->List[i], in->List[i], 24);
		}

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_WHISPER_LIST,char[24]> in(p);
		TPacket<PACKET_ZC_WHISPER_LIST,char[24]> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		for( size_t i = 0; i < out.count(); ++i )
		{
			memcpy(out->List[i], in->List[i], 24);
		}

		return out;
	}
};
