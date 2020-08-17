struct PROTO_ZC_ACK_REQ_ALLY_GUILD
{
	short PacketType;
	unsigned char answer;
};


struct PACKET_ZC_ACK_REQ_ALLY_GUILD
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char answer;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ACK_REQ_ALLY_GUILD> in(p);
		TPacket<PROTO_ZC_ACK_REQ_ALLY_GUILD> out;

		out->PacketType = PacketType;
		out->answer = in->answer;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_ACK_REQ_ALLY_GUILD> in(p);
		TPacket<PACKET_ZC_ACK_REQ_ALLY_GUILD> out;

		out->PacketType = PacketType;
		out->answer = in->answer;

		return out;
	}
};
