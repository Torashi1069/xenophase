struct PROTO_ZC_NOTIFY_SKILL
{
	short PacketType;
	unsigned short SKID;
	unsigned long AID;
	unsigned long targetID;
	unsigned long startTime;
	int attackMT;
	int attackedMT;
	int damage;
	short level;
	short count;
	unsigned char action;
};


struct PACKET_ZC_NOTIFY_SKILL
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short SKID;
	/* this+ 4 */ unsigned long AID;
	/* this+ 8 */ unsigned long targetID;
	/* this+12 */ unsigned long startTime;
	/* this+16 */ int attackMT;
	/* this+20 */ int attackedMT;
	/* this+24 */ short damage;
	/* this+26 */ short level;
	/* this+28 */ short count;
	/* this+30 */ unsigned char action;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NOTIFY_SKILL> in(p);
		TPacket<PROTO_ZC_NOTIFY_SKILL> out;

		out->PacketType = PacketType;
		out->SKID = in->SKID;
		out->AID = in->AID;
		out->targetID = in->targetID;
		out->startTime = in->startTime;
		out->attackMT = in->attackMT;
		out->attackedMT = in->attackedMT;
		out->damage = in->damage; // adapt
		out->level = in->level;
		out->count = in->count;
		out->action = in->action;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_NOTIFY_SKILL> in(p);
		TPacket<PACKET_ZC_NOTIFY_SKILL> out;

		out->PacketType = PacketType;
		out->SKID = in->SKID;
		out->AID = in->AID;
		out->targetID = in->targetID;
		out->startTime = in->startTime;
		out->attackMT = in->attackMT;
		out->attackedMT = in->attackedMT;
		out->damage = min(in->damage, SHRT_MAX); // adapt
		out->level = in->level;
		out->count = in->count;
		out->action = in->action;

		return out;
	}
};


struct PACKET_ZC_NOTIFY_SKILL2
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short SKID;
	/* this+ 4 */ unsigned long AID;
	/* this+ 8 */ unsigned long targetID;
	/* this+12 */ unsigned long startTime;
	/* this+16 */ int attackMT;
	/* this+20 */ int attackedMT;
	/* this+24 */ int damage;
	/* this+28 */ short level;
	/* this+30 */ short count;
	/* this+32 */ unsigned char action;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NOTIFY_SKILL2> in(p);
		TPacket<PROTO_ZC_NOTIFY_SKILL> out;

		out->PacketType = PacketType;
		out->SKID = in->SKID;
		out->AID = in->AID;
		out->targetID = in->targetID;
		out->startTime = in->startTime;
		out->attackMT = in->attackMT;
		out->attackedMT = in->attackedMT;
		out->damage = in->damage;
		out->level = in->level;
		out->count = in->count;
		out->action = in->action;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_NOTIFY_SKILL> in(p);
		TPacket<PACKET_ZC_NOTIFY_SKILL2> out;

		out->PacketType = PacketType;
		out->SKID = in->SKID;
		out->AID = in->AID;
		out->targetID = in->targetID;
		out->startTime = in->startTime;
		out->attackMT = in->attackMT;
		out->attackedMT = in->attackedMT;
		out->damage = in->damage;
		out->level = in->level;
		out->count = in->count;
		out->action = in->action;

		return out;
	}
};
