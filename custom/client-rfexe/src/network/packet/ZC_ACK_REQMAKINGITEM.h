struct PROTO_ZC_ACK_REQMAKINGITEM
{
	short PacketType;
	short result;
	unsigned short ITID;
};


struct PACKET_ZC_ACK_REQMAKINGITEM
{
	/* this+0 */ short PacketType;
	/* this+2 */ short result;
	/* this+4 */ unsigned short ITID;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ACK_REQMAKINGITEM> in(p);
		TPacket<PROTO_ZC_ACK_REQMAKINGITEM> out;

		out->PacketType = PacketType;
		out->result = in->result;
		out->ITID = in->ITID;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_ACK_REQMAKINGITEM> in(p);
		TPacket<PACKET_ZC_ACK_REQMAKINGITEM> out;

		out->PacketType = PacketType;
		out->result = in->result;
		out->ITID = in->ITID;

		return out;
	}
};
