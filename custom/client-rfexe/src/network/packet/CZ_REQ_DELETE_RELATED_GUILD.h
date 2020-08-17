struct PROTO_CZ_REQ_DELETE_RELATED_GUILD
{
	short PacketType;
	unsigned long OpponentGDID;
	int Relation; // enum RELATED_GUILD_TYPE_*
};


struct PACKET_CZ_REQ_DELETE_RELATED_GUILD
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long OpponentGDID;
	/* this+6 */ int Relation;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_REQ_DELETE_RELATED_GUILD> in(p);
		TPacket<PROTO_CZ_REQ_DELETE_RELATED_GUILD> out;

		out->PacketType = PacketType;
		out->OpponentGDID = in->OpponentGDID;
		out->Relation = in->Relation;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_REQ_DELETE_RELATED_GUILD> in(p);
		TPacket<PACKET_CZ_REQ_DELETE_RELATED_GUILD> out;

		out->PacketType = PacketType;
		out->OpponentGDID = in->OpponentGDID;
		out->Relation = in->Relation;

		return out;
	}
};
