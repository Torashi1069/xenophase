struct PROTO_ZC_ACK_EXCHANGE_ITEM
{
	short PacketType;
	unsigned char result;
	unsigned long GID;
	short level;
};


struct PACKET_ZC_ACK_EXCHANGE_ITEM
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char result;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ACK_EXCHANGE_ITEM> in(p);
		TPacket<PROTO_ZC_ACK_EXCHANGE_ITEM> out;

		out->PacketType = PacketType;
		out->result = in->result;
		out->GID = 0; // adapt
		out->level = 0; // adapt

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_ACK_EXCHANGE_ITEM> in(p);
		TPacket<PACKET_ZC_ACK_EXCHANGE_ITEM> out;

		out->PacketType = PacketType;
		out->result = in->result;
//		out->GID = in->GID; // adapt
//		out->level = in->level; // adapt

		return out;
	}
};


struct PACKET_ZC_ACK_EXCHANGE_ITEM2
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char result;
	/* this+3 */ unsigned long GID;
	/* this+7 */ short level;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ACK_EXCHANGE_ITEM2> in(p);
		TPacket<PROTO_ZC_ACK_EXCHANGE_ITEM> out;

		out->PacketType = PacketType;
		out->result = in->result;
		out->GID = in->GID;
		out->level = in->level;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_ACK_EXCHANGE_ITEM> in(p);
		TPacket<PACKET_ZC_ACK_EXCHANGE_ITEM2> out;

		out->PacketType = PacketType;
		out->result = in->result;
		out->GID = in->GID;
		out->level = in->level;

		return out;
	}
};
