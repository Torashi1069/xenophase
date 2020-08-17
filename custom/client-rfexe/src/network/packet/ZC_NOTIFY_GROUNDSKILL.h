struct PROTO_ZC_NOTIFY_GROUNDSKILL
{
	short PacketType;
	unsigned short SKID;
	unsigned long AID;
	short level;
	short xPos;
	short yPos;
	unsigned long startTime;
};


struct PACKET_ZC_NOTIFY_GROUNDSKILL
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short SKID;
	/* this+ 4 */ unsigned long AID;
	/* this+ 8 */ short level;
	/* this+10 */ short xPos;
	/* this+12 */ short yPos;
	/* this+14 */ unsigned long startTime;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NOTIFY_GROUNDSKILL> in(p);
		TPacket<PROTO_ZC_NOTIFY_GROUNDSKILL> out;

		out->PacketType = PacketType;
		out->SKID = in->SKID;
		out->AID = in->AID;
		out->level = in->level;
		out->xPos = in->xPos;
		out->yPos = in->yPos;
		out->startTime = in->startTime;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_NOTIFY_GROUNDSKILL> in(p);
		TPacket<PACKET_ZC_NOTIFY_GROUNDSKILL> out;

		out->PacketType = PacketType;
		out->SKID = in->SKID;
		out->AID = in->AID;
		out->level = in->level;
		out->xPos = in->xPos;
		out->yPos = in->yPos;
		out->startTime = in->startTime;

		return out;
	}
};
