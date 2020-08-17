struct PROTO_ZC_FRIENDS_STATE
{
	short PacketType;
	unsigned long AID;
	unsigned long GID;
	bool State;
};


struct PACKET_ZC_FRIENDS_STATE
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ bool State;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_FRIENDS_STATE> in(p);
		TPacket<PROTO_ZC_FRIENDS_STATE> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->GID = in->GID;
		out->State = in->State;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_FRIENDS_STATE> in(p);
		TPacket<PACKET_ZC_FRIENDS_STATE> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->GID = in->GID;
		out->State = in->State;

		return out;
	}
};
