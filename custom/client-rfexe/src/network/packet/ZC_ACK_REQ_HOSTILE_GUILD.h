struct PROTO_ZC_ACK_REQ_HOSTILE_GUILD
{
	short PacketType;
	unsigned char result;
};


struct PACKET_ZC_ACK_REQ_HOSTILE_GUILD
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char result;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ACK_REQ_HOSTILE_GUILD> in(p);
		TPacket<PROTO_ZC_ACK_REQ_HOSTILE_GUILD> out;

		out->PacketType = PacketType;
		out->result = in->result;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_ACK_REQ_HOSTILE_GUILD> in(p);
		TPacket<PACKET_ZC_ACK_REQ_HOSTILE_GUILD> out;

		out->PacketType = PacketType;
		out->result = in->result;

		return out;
	}
};
