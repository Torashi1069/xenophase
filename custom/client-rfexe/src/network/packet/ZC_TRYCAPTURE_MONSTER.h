struct PROTO_ZC_TRYCAPTURE_MONSTER
{
	short PacketType;
	unsigned char result;
};


struct PACKET_ZC_TRYCAPTURE_MONSTER
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char result;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_TRYCAPTURE_MONSTER> in(p);
		TPacket<PROTO_ZC_TRYCAPTURE_MONSTER> out;

		out->PacketType = PacketType;
		out->result = in->result;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_TRYCAPTURE_MONSTER> in(p);
		TPacket<PACKET_ZC_TRYCAPTURE_MONSTER> out;

		out->PacketType = PacketType;
		out->result = in->result;

		return out;
	}
};
