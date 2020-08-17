struct PROTO_ZC_ACK_DISCONNECT_CHARACTER
{
	short PacketType;
	unsigned char result;
};


struct PACKET_ZC_ACK_DISCONNECT_CHARACTER
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char result;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ACK_DISCONNECT_CHARACTER> in(p);
		TPacket<PROTO_ZC_ACK_DISCONNECT_CHARACTER> out;

		out->PacketType = PacketType;
		out->result = in->result;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_ACK_DISCONNECT_CHARACTER> in(p);
		TPacket<PACKET_ZC_ACK_DISCONNECT_CHARACTER> out;

		out->PacketType = PacketType;
		out->result = in->result;

		return out;
	}
};
