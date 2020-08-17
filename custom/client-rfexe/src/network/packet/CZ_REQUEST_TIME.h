struct PROTO_CZ_REQUEST_TIME
{
	short PacketType;
	unsigned long clientTime;
};


struct PACKET_CZ_REQUEST_TIME
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long clientTime;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_REQUEST_TIME> in(p);
		TPacket<PROTO_CZ_REQUEST_TIME> out;

		out->PacketType = PacketType;
		out->clientTime = in->clientTime;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_REQUEST_TIME> in(p);
		TPacket<PACKET_CZ_REQUEST_TIME> out;

		out->PacketType = PacketType;
		out->clientTime = in->clientTime;

		return out;
	}
};


// NOTE: sent by client-kro-2010-06-22aRagexeRE (0x59CD7E)
struct PACKET_CZ_REQUEST_TIME__PAD5
{
	/* this+0 */ short PacketType;
	/* this+2 */ char pad[5];
	/* this+7 */ unsigned long clientTime;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_REQUEST_TIME__PAD5> in(p);
		TPacket<PROTO_CZ_REQUEST_TIME> out;

		out->PacketType = PacketType;
		out->clientTime = in->clientTime;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_REQUEST_TIME> in(p);
		TPacket<PACKET_CZ_REQUEST_TIME__PAD5> out;

		out->PacketType = PacketType;
		out->clientTime = in->clientTime;
		memset(out->pad, 0, sizeof(out->pad)); // adapt //TODO: generate properly

		return out;
	}
};


struct PACKET_CZ_REQUEST_TIME2
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long clientTime;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_REQUEST_TIME2> in(p);
		TPacket<PROTO_CZ_REQUEST_TIME> out;

		out->PacketType = PacketType;
		out->clientTime = in->clientTime;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_REQUEST_TIME> in(p);
		TPacket<PACKET_CZ_REQUEST_TIME2> out;

		out->PacketType = PacketType;
		out->clientTime = in->clientTime;

		return out;
	}
};
