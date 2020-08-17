struct PROTO_ZC_ACK_TOUSESKILL
{
	short PacketType;
	unsigned short SKID;
	unsigned long NUM;
	bool result;
	unsigned char cause;
};


struct PACKET_ZC_ACK_TOUSESKILL
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short SKID;
	/* this+4 */ unsigned long NUM;
	/* this+8 */ bool result;
	/* this+9 */ unsigned char cause;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ACK_TOUSESKILL> in(p);
		TPacket<PROTO_ZC_ACK_TOUSESKILL> out;

		out->PacketType = PacketType;
		out->SKID = in->SKID;
		out->NUM = in->NUM;
		out->result = in->result;
		out->cause = in->cause;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_ACK_TOUSESKILL> in(p);
		TPacket<PACKET_ZC_ACK_TOUSESKILL> out;

		out->PacketType = PacketType;
		out->SKID = in->SKID;
		out->NUM = in->NUM;
		out->result = in->result;
		out->cause = in->cause;

		return out;
	}
};
