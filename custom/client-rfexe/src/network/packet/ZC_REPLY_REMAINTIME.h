struct PROTO_ZC_REPLY_REMAINTIME
{
	short PacketType;
	int Result;
	int ExpirationDate;
	int RemainTime;
};


struct PACKET_ZC_REPLY_REMAINTIME
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ int Result;
	/* this+ 6 */ int ExpirationDate;
	/* this+10 */ int RemainTime;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_REPLY_REMAINTIME> in(p);
		TPacket<PROTO_ZC_REPLY_REMAINTIME> out;

		out->PacketType = PacketType;
		out->Result = in->Result;
		out->ExpirationDate = in->ExpirationDate;
		out->RemainTime = in->RemainTime;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_REPLY_REMAINTIME> in(p);
		TPacket<PACKET_ZC_REPLY_REMAINTIME> out;

		out->PacketType = PacketType;
		out->Result = in->Result;
		out->ExpirationDate = in->ExpirationDate;
		out->RemainTime = in->RemainTime;

		return out;
	}
};
