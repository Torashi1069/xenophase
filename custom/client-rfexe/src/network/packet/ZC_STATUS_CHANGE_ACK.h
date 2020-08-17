struct PROTO_ZC_STATUS_CHANGE_ACK
{
	short PacketType;
	unsigned short statusID;
	bool result;
	unsigned char value;
};


struct PACKET_ZC_STATUS_CHANGE_ACK
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short statusID;
	/* this+4 */ bool result;
	/* this+5 */ unsigned char value;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_STATUS_CHANGE_ACK> in(p);
		TPacket<PROTO_ZC_STATUS_CHANGE_ACK> out;

		out->PacketType = PacketType;
		out->statusID = in->statusID;
		out->result = in->result;
		out->value = in->value;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_STATUS_CHANGE_ACK> in(p);
		TPacket<PACKET_ZC_STATUS_CHANGE_ACK> out;

		out->PacketType = PacketType;
		out->statusID = in->statusID;
		out->result = in->result;
		out->value = in->value;

		return out;
	}
};
