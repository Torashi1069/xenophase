struct PROTO_CZ_REQMAKINGHOMUN
{
	short PacketType;
	bool result;
};


struct PACKET_CZ_REQMAKINGHOMUN
{
	/* this+0 */ short PacketType;
	/* this+2 */ bool result;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_REQMAKINGHOMUN> in(p);
		TPacket<PROTO_CZ_REQMAKINGHOMUN> out;

		out->PacketType = PacketType;
		out->result = in->result;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_REQMAKINGHOMUN> in(p);
		TPacket<PACKET_CZ_REQMAKINGHOMUN> out;

		out->PacketType = PacketType;
		out->result = in->result;

		return out;
	}
};
