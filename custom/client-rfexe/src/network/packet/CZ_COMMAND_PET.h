struct PROTO_CZ_COMMAND_PET
{
	short PacketType;
	char cSub;
};


struct PACKET_CZ_COMMAND_PET
{
	/* this+0 */ short PacketType;
	/* this+2 */ char cSub;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_COMMAND_PET> in(p);
		TPacket<PROTO_CZ_COMMAND_PET> out;

		out->PacketType = PacketType;
		out->cSub = in->cSub;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_COMMAND_PET> in(p);
		TPacket<PACKET_CZ_COMMAND_PET> out;

		out->PacketType = PacketType;
		out->cSub = in->cSub;

		return out;
	}
};
