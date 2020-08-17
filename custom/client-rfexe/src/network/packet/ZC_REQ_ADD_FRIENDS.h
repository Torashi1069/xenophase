struct PROTO_ZC_REQ_ADD_FRIENDS
{
	short PacketType;
	unsigned long ReqAID;
	unsigned long ReqGID;
	char Name[24];
};


struct PACKET_ZC_REQ_ADD_FRIENDS
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long ReqAID;
	/* this+ 6 */ unsigned long ReqGID;
	/* this+10 */ char Name[24];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_REQ_ADD_FRIENDS> in(p);
		TPacket<PROTO_ZC_REQ_ADD_FRIENDS> out;

		out->PacketType = PacketType;
		out->ReqAID = in->ReqAID;
		out->ReqGID = in->ReqGID;
		memcpy(out->Name, in->Name, 24);

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_REQ_ADD_FRIENDS> in(p);
		TPacket<PACKET_ZC_REQ_ADD_FRIENDS> out;

		out->PacketType = PacketType;
		out->ReqAID = in->ReqAID;
		out->ReqGID = in->ReqGID;
		memcpy(out->Name, in->Name, 24);

		return out;
	}
};
