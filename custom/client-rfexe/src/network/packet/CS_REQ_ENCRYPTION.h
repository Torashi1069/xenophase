struct PROTO_CS_REQ_ENCRYPTION
{
	short PacketType; // PROTOID_CS_REQ_ENCRYPTION
	char encCount;
	char decCount;
};


struct PACKET_CS_REQ_ENCRYPTION
{
	/* this+0 */ short PacketType;
	/* this+2 */ char encCount;
	/* this+3 */ char decCount;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CS_REQ_ENCRYPTION> in(p);
		TPacket<PROTO_CS_REQ_ENCRYPTION> out;

		out->PacketType = PacketType;
		out->encCount = in->encCount;
		out->decCount = in->decCount;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CS_REQ_ENCRYPTION> in(p);
		TPacket<PACKET_CS_REQ_ENCRYPTION> out;

		out->PacketType = PacketType;
		out->encCount = in->encCount;
		out->decCount = in->decCount;

		return out;
	}
};
