struct PROTO_CZ_REMOVE_AID
{
	short PacketType;
	char AccountName[24];
};


struct PACKET_CZ_REMOVE_AID
{
	/* this+0 */ short PacketType;
	/* this+2 */ char AccountName[24];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_REMOVE_AID> in(p);
		TPacket<PROTO_CZ_REMOVE_AID> out;

		out->PacketType = PacketType;
		memcpy(out->AccountName, in->AccountName, 24);

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_REMOVE_AID> in(p);
		TPacket<PACKET_CZ_REMOVE_AID> out;

		out->PacketType = PacketType;
		memcpy(out->AccountName, in->AccountName, 24);

		return out;
	}
};
