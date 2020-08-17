struct PROTO_CA_REPLY_PNGAMEROOM
{
	short PacketType;
	unsigned char Permission;
};


struct PACKET_CA_REPLY_PNGAMEROOM
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char Permission;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CA_REPLY_PNGAMEROOM> in(p);
		TPacket<PROTO_CA_REPLY_PNGAMEROOM> out;

		out->PacketType = PacketType;
		out->Permission = in->Permission;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CA_REPLY_PNGAMEROOM> in(p);
		TPacket<PACKET_CA_REPLY_PNGAMEROOM> out;

		out->PacketType = PacketType;
		out->Permission = in->Permission;

		return out;
	}
};
