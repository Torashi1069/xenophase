struct PROTO_ZC_STATE_CHANGE
{
	short PacketType;
	unsigned long AID;
	short bodyState;
	short healthState;
	int effectState;
	bool isPKModeON;
};


struct PACKET_ZC_STATE_CHANGE
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ short bodyState;
	/* this+ 8 */ short healthState;
	/* this+10 */ short effectState;
	/* this+12 */ bool isPKModeON;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_STATE_CHANGE> in(p);
		TPacket<PROTO_ZC_STATE_CHANGE> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->bodyState = in->bodyState;
		out->healthState = in->healthState;
		out->effectState = static_cast<int>(in->effectState);
		out->isPKModeON = in->isPKModeON;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_STATE_CHANGE> in(p);
		TPacket<PACKET_ZC_STATE_CHANGE> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->bodyState = in->bodyState;
		out->healthState = in->healthState;
		out->effectState = static_cast<short>(in->effectState);
		out->isPKModeON = in->isPKModeON;

		return out;
	}
};


struct PACKET_ZC_STATE_CHANGE3
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ short bodyState;
	/* this+ 8 */ short healthState;
	/* this+10 */ int effectState;
	/* this+14 */ bool isPKModeON;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_STATE_CHANGE3> in(p);
		TPacket<PROTO_ZC_STATE_CHANGE> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->bodyState = in->bodyState;
		out->healthState = in->healthState;
		out->effectState = in->effectState;
		out->isPKModeON = in->isPKModeON;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_STATE_CHANGE> in(p);
		TPacket<PACKET_ZC_STATE_CHANGE3> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->bodyState = in->bodyState;
		out->healthState = in->healthState;
		out->effectState = in->effectState;
		out->isPKModeON = in->isPKModeON;

		return out;
	}
};
