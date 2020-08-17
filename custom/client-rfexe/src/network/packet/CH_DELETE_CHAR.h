struct PROTO_CH_DELETE_CHAR
{
	short PacketType;
	unsigned long GID;
	char key[50];
};


struct PACKET_CH_DELETE_CHAR
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GID;
	/* this+6 */ char key[40];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CH_DELETE_CHAR> in(p);
		TPacket<PROTO_CH_DELETE_CHAR> out;

		out->PacketType = PacketType;
		out->GID = in->GID;
		memcpy(out->key, in->key, 40); // adapt //FIXME: check if null-termination is needed

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CH_DELETE_CHAR> in(p);
		TPacket<PACKET_CH_DELETE_CHAR> out;

		out->PacketType = PacketType;
		out->GID = in->GID;
		memcpy(out->key, in->key, 40); // adapt //FIXME: check if null-termination is needed

		return out;
	}
};


struct PACKET_CH_DELETE_CHAR2
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GID;
	/* this+6 */ char key[50];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CH_DELETE_CHAR2> in(p);
		TPacket<PROTO_CH_DELETE_CHAR> out;

		out->PacketType = PacketType;
		out->GID = in->GID;
		memcpy(out->key, in->key, 50);

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CH_DELETE_CHAR> in(p);
		TPacket<PACKET_CH_DELETE_CHAR2> out;

		out->PacketType = PacketType;
		out->GID = in->GID;
		memcpy(out->key, in->key, 50);

		return out;
	}
};
