struct PROTO_ZC_ACK_OPEN_MEMBER_INFO
{
	short PacketType;
};


struct PACKET_ZC_ACK_OPEN_MEMBER_INFO
{
	/* this+0 */ short PacketType;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ACK_OPEN_MEMBER_INFO> in(p);
		TPacket<PROTO_ZC_ACK_OPEN_MEMBER_INFO> out;

		out->PacketType = PacketType;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_ACK_OPEN_MEMBER_INFO> in(p);
		TPacket<PACKET_ZC_ACK_OPEN_MEMBER_INFO> out;

		out->PacketType = PacketType;

		return out;
	}
};
