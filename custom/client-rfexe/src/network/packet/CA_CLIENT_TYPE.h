struct PROTO_CA_CLIENT_TYPE
{
	short PacketType;
	short ClientType;
	int nVer;
};


struct PACKET_CA_CLIENT_TYPE
{
	/* this+0 */ short PacketType;
	/* this+2 */ short ClientType;
	/* this+4 */ int nVer;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CA_CLIENT_TYPE> in(p);
		TPacket<PROTO_CA_CLIENT_TYPE> out;

		out->PacketType = PacketType;
		out->ClientType = in->ClientType;
		out->nVer = in->nVer;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CA_CLIENT_TYPE> in(p);
		TPacket<PACKET_CA_CLIENT_TYPE> out;

		out->PacketType = PacketType;
		out->ClientType = in->ClientType;
		out->nVer = in->nVer;

		return out;
	}
};
