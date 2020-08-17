struct PROTO_CH_SELECT_CHAR
{
	short PacketType;
	unsigned char CharNum;
};


struct PACKET_CH_SELECT_CHAR
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char CharNum;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CH_SELECT_CHAR> in(p);
		TPacket<PROTO_CH_SELECT_CHAR> out;

		out->PacketType = PacketType;
		out->CharNum = in->CharNum;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CH_SELECT_CHAR> in(p);
		TPacket<PACKET_CH_SELECT_CHAR> out;

		out->PacketType = PacketType;
		out->CharNum = in->CharNum;

		return out;
	}
};
