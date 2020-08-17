struct PROTO_ZC_NOTIFY_ACT_POSITION
{
	short PacketType;
	unsigned long GID;
	unsigned long targetGID;
	unsigned long startTime;
	short xPos;
	short yPos;
	short damage;
	short count;
	unsigned char action;
};


struct PACKET_ZC_NOTIFY_ACT_POSITION
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GID;
	/* this+ 6 */ unsigned long targetGID;
	/* this+10 */ unsigned long startTime;
	/* this+14 */ short xPos;
	/* this+16 */ short yPos;
	/* this+18 */ short damage;
	/* this+20 */ short count;
	/* this+22 */ unsigned char action;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NOTIFY_ACT_POSITION> in(p);
		TPacket<PROTO_ZC_NOTIFY_ACT_POSITION> out;

		out->PacketType = PacketType;
		out->GID = in->GID;
		out->targetGID = in->targetGID;
		out->startTime = in->startTime;
		out->xPos = in->xPos;
		out->yPos = in->yPos;
		out->damage = in->damage;
		out->count = in->count;
		out->action = in->action;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_NOTIFY_ACT_POSITION> in(p);
		TPacket<PACKET_ZC_NOTIFY_ACT_POSITION> out;

		out->PacketType = PacketType;
		out->GID = in->GID;
		out->targetGID = in->targetGID;
		out->startTime = in->startTime;
		out->xPos = in->xPos;
		out->yPos = in->yPos;
		out->damage = in->damage;
		out->count = in->count;
		out->action = in->action;

		return out;
	}
};
