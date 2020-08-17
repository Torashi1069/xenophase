struct PROTO_ZC_INFO_REMAINTIME
{
	short PacketType;
	int Type;
	int RemainTime;
};


struct PACKET_ZC_INFO_REMAINTIME
{
	/* this+0 */ short PacketType;
	/* this+2 */ int Type;
	/* this+6 */ int RemainTime;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_INFO_REMAINTIME> in(p);
		TPacket<PROTO_ZC_INFO_REMAINTIME> out;

		out->PacketType = PacketType;
		out->Type = in->Type;
		out->RemainTime = in->RemainTime;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_INFO_REMAINTIME> in(p);
		TPacket<PACKET_ZC_INFO_REMAINTIME> out;

		out->PacketType = PacketType;
		out->Type = in->Type;
		out->RemainTime = in->RemainTime;

		return out;
	}
};
