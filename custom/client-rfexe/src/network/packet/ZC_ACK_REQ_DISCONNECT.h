struct PROTO_ZC_ACK_REQ_DISCONNECT
{
	short PacketType;
	short result;
};


struct PACKET_ZC_ACK_REQ_DISCONNECT
{
	/* this+0 */ short PacketType;
	/* this+2 */ short result;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ACK_REQ_DISCONNECT> in(p);
		TPacket<PROTO_ZC_ACK_REQ_DISCONNECT> out;

		out->PacketType = PacketType;
		out->result = in->result;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_ACK_REQ_DISCONNECT> in(p);
		TPacket<PACKET_ZC_ACK_REQ_DISCONNECT> out;

		out->PacketType = PacketType;
		out->result = in->result;

		return out;
	}
};
