struct PROTO_ZC_NOTIFY_SKILL_POSITION
{
	short PacketType;
	unsigned short SKID;
	unsigned long AID;
	unsigned long targetID;
	unsigned long startTime;
	int attackMT;
	int attackedMT;
	short xPos;
	short yPos;
	short damage;
	short level;
	short count;
	unsigned char action;
};


struct PACKET_ZC_NOTIFY_SKILL_POSITION
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short SKID;
	/* this+ 4 */ unsigned long AID;
	/* this+ 8 */ unsigned long targetID;
	/* this+12 */ unsigned long startTime;
	/* this+16 */ int attackMT;
	/* this+20 */ int attackedMT;
	/* this+24 */ short xPos;
	/* this+26 */ short yPos;
	/* this+28 */ short damage;
	/* this+30 */ short level;
	/* this+32 */ short count;
	/* this+34 */ unsigned char action;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NOTIFY_SKILL_POSITION> in(p);
		TPacket<PROTO_ZC_NOTIFY_SKILL_POSITION> out;

		out->PacketType = PacketType;
		out->SKID = in->SKID;
		out->AID = in->AID;
		out->targetID = in->targetID;
		out->startTime = in->startTime;
		out->attackMT = in->attackMT;
		out->attackedMT = in->attackedMT;
		out->xPos = in->xPos;
		out->yPos = in->yPos;
		out->damage = in->damage;
		out->level = in->level;
		out->count = in->count;
		out->action = in->action;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_NOTIFY_SKILL_POSITION> in(p);
		TPacket<PACKET_ZC_NOTIFY_SKILL_POSITION> out;

		out->PacketType = PacketType;
		out->SKID = in->SKID;
		out->AID = in->AID;
		out->targetID = in->targetID;
		out->startTime = in->startTime;
		out->attackMT = in->attackMT;
		out->attackedMT = in->attackedMT;
		out->xPos = in->xPos;
		out->yPos = in->yPos;
		out->damage = in->damage;
		out->level = in->level;
		out->count = in->count;
		out->action = in->action;

		return out;
	}
};
