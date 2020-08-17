struct PROTO_ZC_NOTIFY_EXP
{
	enum
	{
		EXP_FROM_BATTLE = 0,
		EXP_FROM_QUEST  = 1,
	};

	short PacketType;
	unsigned long AID;
	int amount;
	unsigned short varID;
	short expType;
};


struct PACKET_ZC_NOTIFY_EXP
{
	enum
	{
		EXP_FROM_BATTLE = 0,
		EXP_FROM_QUEST  = 1,
	};

	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ int amount;
	/* this+10 */ unsigned short varID;
	/* this+12 */ short expType;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NOTIFY_EXP> in(p);
		TPacket<PROTO_ZC_NOTIFY_EXP> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->amount = in->amount;
		out->varID = in->varID;
		out->expType = in->expType;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_NOTIFY_EXP> in(p);
		TPacket<PACKET_ZC_NOTIFY_EXP> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->amount = in->amount;
		out->varID = in->varID;
		out->expType = in->expType;

		return out;
	}
};
