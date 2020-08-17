struct PROTO_ZC_REQ_CASH_PASSWORD
{
	short PacketType;
	short Info;
};


struct PACKET_ZC_REQ_CASH_PASSWORD
{
	/* this+0 */ short PacketType;
	/* this+2 */ short Info;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_REQ_CASH_PASSWORD> in(p);
		TPacket<PROTO_ZC_REQ_CASH_PASSWORD> out;

		out->PacketType = PacketType;
		out->Info = in->Info;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_REQ_CASH_PASSWORD> in(p);
		TPacket<PACKET_ZC_REQ_CASH_PASSWORD> out;

		out->PacketType = PacketType;
		out->Info = in->Info;

		return out;
	}
};
