struct PROTO_ZC_ADD_FRIENDS_LIST
{
	short PacketType;
	short Result;
	unsigned long AID;
	unsigned long GID;
	char Name[24];
};


struct PACKET_ZC_ADD_FRIENDS_LIST
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short Result;
	/* this+ 4 */ unsigned long AID;
	/* this+ 8 */ unsigned long GID;
	/* this+12 */ char Name[24];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ADD_FRIENDS_LIST> in(p);
		TPacket<PROTO_ZC_ADD_FRIENDS_LIST> out;

		out->PacketType = PacketType;
		out->Result = in->Result;
		out->AID = in->AID;
		out->GID = in->GID;
		memcpy(out->Name, in->Name, 24);

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_ADD_FRIENDS_LIST> in(p);
		TPacket<PACKET_ZC_ADD_FRIENDS_LIST> out;

		out->PacketType = PacketType;
		out->Result = in->Result;
		out->AID = in->AID;
		out->GID = in->GID;
		memcpy(out->Name, in->Name, 24);

		return out;
	}
};
