struct PROTO_CZ_USE_SKILL_TOGROUND
{
	short PacketType;
	short selectedLevel;
	unsigned short SKID;
	short xPos;
	short yPos;
};


struct PACKET_CZ_USE_SKILL_TOGROUND
{
	/* this+0 */ short PacketType;
	/* this+2 */ short selectedLevel;
	/* this+4 */ unsigned short SKID;
	/* this+6 */ short xPos;
	/* this+8 */ short yPos;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_USE_SKILL_TOGROUND> in(p);
		TPacket<PROTO_CZ_USE_SKILL_TOGROUND> out;

		out->PacketType = PacketType;
		out->selectedLevel = in->selectedLevel;
		out->SKID = in->SKID;
		out->xPos = in->xPos;
		out->yPos = in->yPos;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_USE_SKILL_TOGROUND> in(p);
		TPacket<PACKET_CZ_USE_SKILL_TOGROUND> out;

		out->PacketType = PacketType;
		out->selectedLevel = in->selectedLevel;
		out->SKID = in->SKID;
		out->xPos = in->xPos;
		out->yPos = in->yPos;

		return out;
	}
};


// NOTE: sent by client-kro-2010-06-22aRagexeRE (0x5BCF8B)
struct PACKET_CZ_USE_SKILL_TOGROUND__PAD8_2_2_3
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char pad[8];
	/* this+10 */ short selectedLevel;
	/* this+12 */ char pad2[2];
	/* this+14 */ unsigned short SKID;
	/* this+16 */ char pad3[2];
	/* this+18 */ short xPos;
	/* this+20 */ char pad4[3];
	/* this+23 */ short yPos;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_USE_SKILL_TOGROUND__PAD8_2_2_3> in(p);
		TPacket<PROTO_CZ_USE_SKILL_TOGROUND> out;

		out->PacketType = PacketType;
		out->selectedLevel = in->selectedLevel;
		out->SKID = in->SKID;
		out->xPos = in->xPos;
		out->yPos = in->yPos;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_USE_SKILL_TOGROUND> in(p);
		TPacket<PACKET_CZ_USE_SKILL_TOGROUND__PAD8_2_2_3> out;

		out->PacketType = PacketType;
		out->selectedLevel = in->selectedLevel;
		out->SKID = in->SKID;
		out->xPos = in->xPos;
		out->yPos = in->yPos;
		memset(out->pad, 0, sizeof(out->pad)); // adapt //TODO: generate properly
		memset(out->pad2, 0, sizeof(out->pad2)); // adapt //TODO: generate properly
		memset(out->pad3, 0, sizeof(out->pad3)); // adapt //TODO: generate properly
		memset(out->pad4, 0, sizeof(out->pad4)); // adapt //TODO: generate properly

		return out;
	}
};


struct PACKET_CZ_USE_SKILL_TOGROUND2
{
	/* this+0 */ short PacketType;
	/* this+2 */ short selectedLevel;
	/* this+4 */ unsigned short SKID;
	/* this+6 */ short xPos;
	/* this+8 */ short yPos;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_USE_SKILL_TOGROUND2> in(p);
		TPacket<PROTO_CZ_USE_SKILL_TOGROUND> out;

		out->PacketType = PacketType;
		out->selectedLevel = in->selectedLevel;
		out->SKID = in->SKID;
		out->xPos = in->xPos;
		out->yPos = in->yPos;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_USE_SKILL_TOGROUND> in(p);
		TPacket<PACKET_CZ_USE_SKILL_TOGROUND2> out;

		out->PacketType = PacketType;
		out->selectedLevel = in->selectedLevel;
		out->SKID = in->SKID;
		out->xPos = in->xPos;
		out->yPos = in->yPos;

		return out;
	}
};
