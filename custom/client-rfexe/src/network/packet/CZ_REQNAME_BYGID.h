struct PROTO_CZ_REQNAME_BYGID
{
	short PacketType;
	unsigned long GID;
};


struct PACKET_CZ_REQNAME_BYGID
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GID;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_REQNAME_BYGID> in(p);
		TPacket<PROTO_CZ_REQNAME_BYGID> out;

		out->PacketType = PacketType;
		out->GID = in->GID;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_REQNAME_BYGID> in(p);
		TPacket<PACKET_CZ_REQNAME_BYGID> out;

		out->PacketType = PacketType;
		out->GID = in->GID;

		return out;
	}
};


// NOTE: sent by client-kro-2010-06-22aRagexeRE (0x5A42E3)
struct PACKET_CZ_REQNAME_BYGID__PAD8
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char pad[8];
	/* this+10 */ unsigned long GID;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_REQNAME_BYGID__PAD8> in(p);
		TPacket<PROTO_CZ_REQNAME_BYGID> out;

		out->PacketType = PacketType;
		out->GID = in->GID;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_REQNAME_BYGID> in(p);
		TPacket<PACKET_CZ_REQNAME_BYGID__PAD8> out;

		out->PacketType = PacketType;
		out->GID = in->GID;
		memset(out->pad, 0, sizeof(out->pad)); // adapt //TODO: generate properly

		return out;
	}
};


struct PACKET_CZ_REQNAME_BYGID2
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GID;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_REQNAME_BYGID2> in(p);
		TPacket<PROTO_CZ_REQNAME_BYGID> out;

		out->PacketType = PacketType;
		out->GID = in->GID;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_REQNAME_BYGID> in(p);
		TPacket<PACKET_CZ_REQNAME_BYGID2> out;

		out->PacketType = PacketType;
		out->GID = in->GID;

		return out;
	}
};
