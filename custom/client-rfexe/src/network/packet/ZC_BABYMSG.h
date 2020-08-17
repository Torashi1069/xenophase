struct PROTO_ZC_BABYMSG
{
	short PacketType;
	int MsgNo;
};


struct PACKET_ZC_BABYMSG
{
	/* this+0 */ short PacketType;
	/* this+2 */ int MsgNo;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_BABYMSG> in(p);
		TPacket<PROTO_ZC_BABYMSG> out;

		out->PacketType = PacketType;
		out->MsgNo = in->MsgNo;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_BABYMSG> in(p);
		TPacket<PACKET_ZC_BABYMSG> out;

		out->PacketType = PacketType;
		out->MsgNo = in->MsgNo;

		return out;
	}
};
