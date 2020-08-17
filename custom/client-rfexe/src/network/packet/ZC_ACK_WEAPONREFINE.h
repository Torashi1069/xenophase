struct PROTO_ZC_ACK_WEAPONREFINE
{
	short PacketType;
	int msg;
	unsigned short ITID;
};


struct PACKET_ZC_ACK_WEAPONREFINE
{
	/* this+0 */ short PacketType;
	/* this+2 */ int msg;
	/* this+6 */ unsigned short ITID;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ACK_WEAPONREFINE> in(p);
		TPacket<PROTO_ZC_ACK_WEAPONREFINE> out;

		out->PacketType = PacketType;
		out->msg = in->msg;
		out->ITID = in->ITID;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_ACK_WEAPONREFINE> in(p);
		TPacket<PACKET_ZC_ACK_WEAPONREFINE> out;

		out->PacketType = PacketType;
		out->msg = in->msg;
		out->ITID = in->ITID;

		return out;
	}
};
