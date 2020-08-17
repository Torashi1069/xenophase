struct PROTO_ZC_RESULT_STORE_PASSWORD
{
	short PacketType;
	short Result;
	short ErrorCount;
};


struct PACKET_ZC_RESULT_STORE_PASSWORD
{
	/* this+0 */ short PacketType;
	/* this+2 */ short Result;
	/* this+4 */ short ErrorCount;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_RESULT_STORE_PASSWORD> in(p);
		TPacket<PROTO_ZC_RESULT_STORE_PASSWORD> out;

		out->PacketType = PacketType;
		out->Result = in->Result;
		out->ErrorCount = in->ErrorCount;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_RESULT_STORE_PASSWORD> in(p);
		TPacket<PACKET_ZC_RESULT_STORE_PASSWORD> out;

		out->PacketType = PacketType;
		out->Result = in->Result;
		out->ErrorCount = in->ErrorCount;

		return out;
	}
};
