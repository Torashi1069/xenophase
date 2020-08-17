struct PROTO_CZ_USE_SKILL
{
	short PacketType;
	short selectedLevel;
	unsigned short SKID;
	unsigned long targetID;
};


struct PACKET_CZ_USE_SKILL
{
	/* this+0 */ short PacketType;
	/* this+2 */ short selectedLevel;
	/* this+4 */ unsigned short SKID;
	/* this+6 */ unsigned long targetID;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_USE_SKILL> in(p);
		TPacket<PROTO_CZ_USE_SKILL> out;

		out->PacketType = PacketType;
		out->selectedLevel = in->selectedLevel;
		out->SKID = in->SKID;
		out->targetID = in->targetID;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_USE_SKILL> in(p);
		TPacket<PACKET_CZ_USE_SKILL> out;

		out->PacketType = PacketType;
		out->selectedLevel = in->selectedLevel;
		out->SKID = in->SKID;
		out->targetID = in->targetID;

		return out;
	}
};


struct PACKET_CZ_USE_SKILL2
{
	/* this+0 */ short PacketType;
	/* this+2 */ short selectedLevel;
	/* this+4 */ unsigned short SKID;
	/* this+6 */ unsigned long targetID;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_USE_SKILL2> in(p);
		TPacket<PROTO_CZ_USE_SKILL> out;

		out->PacketType = PacketType;
		out->selectedLevel = in->selectedLevel;
		out->SKID = in->SKID;
		out->targetID = in->targetID;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_USE_SKILL> in(p);
		TPacket<PACKET_CZ_USE_SKILL2> out;

		out->PacketType = PacketType;
		out->selectedLevel = in->selectedLevel;
		out->SKID = in->SKID;
		out->targetID = in->targetID;

		return out;
	}
};
