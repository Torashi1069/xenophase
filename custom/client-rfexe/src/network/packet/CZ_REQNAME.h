struct PROTO_CZ_REQNAME
{
	short PacketType;
	unsigned long AID;
};


struct PACKET_CZ_REQNAME
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_REQNAME> in(p);
		TPacket<PROTO_CZ_REQNAME> out;

		out->PacketType = PacketType;
		out->AID = in->AID;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_REQNAME> in(p);
		TPacket<PACKET_CZ_REQNAME> out;

		out->PacketType = PacketType;
		out->AID = in->AID;

		return out;
	}
};


// NOTE: sent by client-kro-2010-06-22aRagexeRE (0x5A40BE)
struct PACKET_CZ_REQNAME__PAD8
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char pad[8];
	/* this+10 */ unsigned long AID;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_REQNAME__PAD8> in(p);
		TPacket<PROTO_CZ_REQNAME> out;

		out->PacketType = PacketType;
		out->AID = in->AID;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_REQNAME> in(p);
		TPacket<PACKET_CZ_REQNAME__PAD8> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		memset(out->pad, 0, sizeof(out->pad)); // adapt //TODO: generate properly

		return out;
	}
};


struct PACKET_CZ_REQNAME2
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_REQNAME2> in(p);
		TPacket<PROTO_CZ_REQNAME> out;

		out->PacketType = PacketType;
		out->AID = in->AID;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_REQNAME> in(p);
		TPacket<PACKET_CZ_REQNAME2> out;

		out->PacketType = PacketType;
		out->AID = in->AID;

		return out;
	}
};
