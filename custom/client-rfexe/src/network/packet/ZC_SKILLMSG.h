struct PROTO_ZC_SKILLMSG
{
	short PacketType;
	int MsgNo;
};


struct PACKET_ZC_SKILLMSG
{
	/* this+0 */ short PacketType;
	/* this+2 */ int MsgNo;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_SKILLMSG> in(p);
		TPacket<PROTO_ZC_SKILLMSG> out;

		out->PacketType = PacketType;
		out->MsgNo = in->MsgNo;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_SKILLMSG> in(p);
		TPacket<PACKET_ZC_SKILLMSG> out;

		out->PacketType = PacketType;
		out->MsgNo = in->MsgNo;

		return out;
	}
};
