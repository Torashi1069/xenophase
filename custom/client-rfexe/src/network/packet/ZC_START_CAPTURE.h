struct PROTO_ZC_START_CAPTURE
{
	short PacketType;
};


struct PACKET_ZC_START_CAPTURE
{
	/* this+0 */ public: short PacketType;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_START_CAPTURE> in(p);
		TPacket<PROTO_ZC_START_CAPTURE> out;

		out->PacketType = PacketType;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_START_CAPTURE> in(p);
		TPacket<PACKET_ZC_START_CAPTURE> out;

		out->PacketType = PacketType;

		return out;
	}
};
