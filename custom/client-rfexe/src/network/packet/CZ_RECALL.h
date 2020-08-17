struct PROTO_CZ_RECALL
{
	short PacketType;
	char AccountName[24];
};


struct PACKET_CZ_RECALL
{
	/* this+0 */ short PacketType;
	/* this+2 */ char AccountName[24];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_RECALL> in(p);
		TPacket<PROTO_CZ_RECALL> out;

		out->PacketType = PacketType;
		memcpy(out->AccountName, in->AccountName, 24);

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_RECALL> in(p);
		TPacket<PACKET_CZ_RECALL> out;

		out->PacketType = PacketType;
		memcpy(out->AccountName, in->AccountName, 24);

		return out;
	}
};
