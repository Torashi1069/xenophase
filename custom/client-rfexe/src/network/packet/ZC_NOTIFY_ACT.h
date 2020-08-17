struct PROTO_ZC_NOTIFY_ACT
{
	short PacketType;
	unsigned long GID;
	unsigned long targetGID;
	unsigned long startTime;
	int attackMT;
	int attackedMT;
	int damage;
	unsigned char IsSPDamage;
	short count;
	unsigned char action;
	int leftDamage;
};


struct PACKET_ZC_NOTIFY_ACT
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GID;
	/* this+ 6 */ unsigned long targetGID;
	/* this+10 */ unsigned long startTime;
	/* this+14 */ int attackMT;
	/* this+18 */ int attackedMT;
	/* this+22 */ short damage;
	/* this+24 */ short count;
	/* this+26 */ unsigned char action;
	/* this+27 */ short leftDamage;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NOTIFY_ACT> in(p);
		TPacket<PROTO_ZC_NOTIFY_ACT> out;

		out->PacketType = PacketType;
		out->GID = in->GID;
		out->targetGID = in->targetGID;
		out->startTime = in->startTime;
		out->attackMT = in->attackMT;
		out->attackedMT = in->attackedMT;
		out->damage = in->damage; // adapt
		out->IsSPDamage = 0; // adapt
		out->count = in->count;
		out->action = in->action;
		out->leftDamage = in->leftDamage; // adapt

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_NOTIFY_ACT> in(p);
		TPacket<PACKET_ZC_NOTIFY_ACT> out;

		out->PacketType = PacketType;
		out->GID = in->GID;
		out->targetGID = in->targetGID;
		out->startTime = in->startTime;
		out->attackMT = in->attackMT;
		out->attackedMT = in->attackedMT;
		out->damage = min(in->damage, SHRT_MAX); // adapt
//		out->IsSPDamage = in->IsSPDamage; // adapt
		out->count = in->count;
		out->action = in->action;
		out->leftDamage = min(in->leftDamage, SHRT_MAX); // adapt

		return out;
	}
};


struct PACKET_ZC_NOTIFY_ACT2
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GID;
	/* this+ 6 */ unsigned long targetGID;
	/* this+10 */ unsigned long startTime;
	/* this+14 */ int attackMT;
	/* this+18 */ int attackedMT;
	/* this+22 */ int damage;
	/* this+26 */ short count;
	/* this+28 */ unsigned char action;
	/* this+29 */ int leftDamage;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NOTIFY_ACT2> in(p);
		TPacket<PROTO_ZC_NOTIFY_ACT> out;

		out->PacketType = PacketType;
		out->GID = in->GID;
		out->targetGID = in->targetGID;
		out->startTime = in->startTime;
		out->attackMT = in->attackMT;
		out->attackedMT = in->attackedMT;
		out->damage = in->damage;
		out->IsSPDamage = 0; // adapt
		out->count = in->count;
		out->action = in->action;
		out->leftDamage = in->leftDamage;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_NOTIFY_ACT> in(p);
		TPacket<PACKET_ZC_NOTIFY_ACT2> out;

		out->PacketType = PacketType;
		out->GID = in->GID;
		out->targetGID = in->targetGID;
		out->startTime = in->startTime;
		out->attackMT = in->attackMT;
		out->attackedMT = in->attackedMT;
		out->damage = in->damage;
//		out->IsSPDamage = in->IsSPDamage; // adapt
		out->count = in->count;
		out->action = in->action;
		out->leftDamage = in->leftDamage;

		return out;
	}
};


struct PACKET_ZC_NOTIFY_ACT3__MXX
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short PacketLength;
	/* this+ 4 */ unsigned long GID;
	/* this+ 8 */ unsigned long targetGID;
	/* this+12 */ unsigned long startTime;
	/* this+16 */ int attackMT;
	/* this+20 */ int attackedMT;
	/* this+24 */ int damage;
	/* this+28 */ short count;
	/* this+30 */ unsigned char action;
	/* this+31 */ int leftDamage;
	/* this+35 */ BYTE unknown[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NOTIFY_ACT3__MXX,BYTE> in(p);
		TPacket<PROTO_ZC_NOTIFY_ACT> out;

		// xor deobfuscation
		*(DWORD*)&in[4] ^= *(WORD*)in[0] ^ (*(WORD*)&in[24] + (*(WORD*)&in[12] << 16));
		*(DWORD*)&in[8] ^= *(DWORD*)&in[12] + (*(WORD*)&in[0] << 16);

		out->PacketType = PacketType;
		out->GID = in->GID;
		out->targetGID = in->targetGID;
		out->startTime = in->startTime;
		out->attackMT = in->attackMT;
		out->attackedMT = in->attackedMT;
		out->damage = in->damage;
		out->IsSPDamage = 0; // adapt
		out->count = in->count;
		out->action = in->action;
		out->leftDamage = in->leftDamage;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_NOTIFY_ACT> in(p);
		TPacket<PACKET_ZC_NOTIFY_ACT3__MXX,BYTE> out((size_t)0);

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->GID = in->GID;
		out->targetGID = in->targetGID;
		out->startTime = in->startTime;
		out->attackMT = in->attackMT;
		out->attackedMT = in->attackedMT;
		out->damage = in->damage;
//		out->IsSPDamage = in->IsSPDamage; // adapt
		out->count = in->count;
		out->action = in->action;
		out->leftDamage = in->leftDamage;

		// xor obfuscation
		*(DWORD*)&out[4] ^= *(WORD*)out[0] ^ (*(WORD*)&out[24] + (*(WORD*)&out[12] << 16));
		*(DWORD*)&out[8] ^= *(DWORD*)&out[12] + (*(WORD*)&out[0] << 16);

		return out;
	}
};


struct PACKET_ZC_NOTIFY_ACT3
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GID;
	/* this+ 6 */ unsigned long targetGID;
	/* this+10 */ unsigned long startTime;
	/* this+14 */ int attackMT;
	/* this+18 */ int attackedMT;
	/* this+22 */ int damage;
	/* this+26 */ unsigned char IsSPDamage;
	/* this+27 */ short count;
	/* this+29 */ unsigned char action;
	/* this+30 */ int leftDamage;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NOTIFY_ACT3> in(p);
		TPacket<PROTO_ZC_NOTIFY_ACT> out;

		out->PacketType = PacketType;
		out->GID = in->GID;
		out->targetGID = in->targetGID;
		out->startTime = in->startTime;
		out->attackMT = in->attackMT;
		out->attackedMT = in->attackedMT;
		out->damage = in->damage;
		out->IsSPDamage = in->IsSPDamage;
		out->count = in->count;
		out->action = in->action;
		out->leftDamage = in->leftDamage;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_NOTIFY_ACT> in(p);
		TPacket<PACKET_ZC_NOTIFY_ACT3> out;

		out->PacketType = PacketType;
		out->GID = in->GID;
		out->targetGID = in->targetGID;
		out->startTime = in->startTime;
		out->attackMT = in->attackMT;
		out->attackedMT = in->attackedMT;
		out->damage = in->damage;
		out->IsSPDamage = in->IsSPDamage;
		out->count = in->count;
		out->action = in->action;
		out->leftDamage = in->leftDamage;

		return out;
	}
};
