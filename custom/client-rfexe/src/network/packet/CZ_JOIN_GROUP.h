struct PROTO_CZ_PARTY_JOIN_REQ_ACK
{
	short PacketType;
	unsigned long GRID;
	bool bAccept;
};


struct PACKET_CZ_JOIN_GROUP
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GRID;
	/* this+6 */ int answer; // 0:refuse, 1:accept

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_JOIN_GROUP> in(p);
		TPacket<PROTO_CZ_PARTY_JOIN_REQ_ACK> out;

		out->PacketType = PacketType;
		out->GRID = in->GRID;
		out->bAccept = ( in->answer != 0 );

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_PARTY_JOIN_REQ_ACK> in(p);
		TPacket<PACKET_CZ_JOIN_GROUP> out;

		out->PacketType = PacketType;
		out->GRID = in->GRID;
		out->answer = ( in->bAccept ) ? 1 : 0;

		return out;
	}
};


struct PACKET_CZ_PARTY_JOIN_REQ_ACK
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GRID;
	/* this+6 */ bool bAccept;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_PARTY_JOIN_REQ_ACK> in(p);
		TPacket<PROTO_CZ_PARTY_JOIN_REQ_ACK> out;

		out->PacketType = PacketType;
		out->GRID = in->GRID;
		out->bAccept = in->bAccept;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_PARTY_JOIN_REQ_ACK> in(p);
		TPacket<PACKET_CZ_PARTY_JOIN_REQ_ACK> out;

		out->PacketType = PacketType;
		out->GRID = in->GRID;
		out->bAccept = in->bAccept;

		return out;
	}
};
