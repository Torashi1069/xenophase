struct PROTO_ZC_NOTIFY_HP_TO_GROUPM
{
	short PacketType;
	unsigned long AID;
	int hp;
	int maxhp;
};


struct PACKET_ZC_NOTIFY_HP_TO_GROUPM
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
	/* this+6 */ short hp;
	/* this+8 */ short maxhp;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NOTIFY_HP_TO_GROUPM> in(p);
		TPacket<PROTO_ZC_NOTIFY_HP_TO_GROUPM> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->hp = static_cast<int>(in->hp); // adapt
		out->maxhp = static_cast<int>(in->maxhp); // adapt

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_NOTIFY_HP_TO_GROUPM> in(p);
		TPacket<PACKET_ZC_NOTIFY_HP_TO_GROUPM> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->hp = static_cast<short>(in->hp); // adapt
		out->maxhp = static_cast<short>(in->maxhp); // adapt

		return out;
	}
};


struct PACKET_ZC_NOTIFY_HP_TO_GROUPM_R2
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ int hp;
	/* this+10 */ int maxhp;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NOTIFY_HP_TO_GROUPM_R2> in(p);
		TPacket<PROTO_ZC_NOTIFY_HP_TO_GROUPM> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->hp = in->hp;
		out->maxhp = in->maxhp;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_NOTIFY_HP_TO_GROUPM> in(p);
		TPacket<PACKET_ZC_NOTIFY_HP_TO_GROUPM_R2> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->hp = in->hp;
		out->maxhp = in->maxhp;

		return out;
	}
};
