struct PROTO_CA_CONNECT_INFO_CHANGED
{
	short PacketType;
	unsigned char ID[24];
};


struct PACKET_CA_CONNECT_INFO_CHANGED
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char ID[24];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CA_CONNECT_INFO_CHANGED> in(p);
		TPacket<PROTO_CA_CONNECT_INFO_CHANGED> out;

		out->PacketType = PacketType;
		memcpy(out->ID, in->ID, 24);

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CA_CONNECT_INFO_CHANGED> in(p);
		TPacket<PACKET_CA_CONNECT_INFO_CHANGED> out;

		out->PacketType = PacketType;
		memcpy(out->ID, in->ID, 24);

		return out;
	}
};
