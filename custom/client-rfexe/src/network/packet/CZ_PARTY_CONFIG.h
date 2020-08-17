struct PROTO_CZ_PARTY_CONFIG
{
	short PacketType;
	bool bRefuseJoinMsg;
};


struct PACKET_CZ_PARTY_CONFIG
{
	/* this+0 */ short PacketType;
	/* this+2 */ bool bRefuseJoinMsg;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_PARTY_CONFIG> in(p);
		TPacket<PROTO_CZ_PARTY_CONFIG> out;

		out->PacketType = PacketType;
		out->bRefuseJoinMsg = in->bRefuseJoinMsg;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_PARTY_CONFIG> in(p);
		TPacket<PACKET_CZ_PARTY_CONFIG> out;

		out->PacketType = PacketType;
		out->bRefuseJoinMsg = in->bRefuseJoinMsg;

		return out;
	}
};
