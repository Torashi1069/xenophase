struct PROTO_ZC_SKILL_ENTRY
{
	short PacketType;
	short PacketLength;
	unsigned long AID;
	unsigned long creatorAID;
	short xPos;
	short yPos;
	int job;
	char RadiusRange;
	bool isVisible;
	unsigned char level;
	char msg[];
};


struct PACKET_ZC_SKILL_ENTRY
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long creatorAID;
	/* this+10 */ short xPos;
	/* this+12 */ short yPos;
	/* this+14 */ unsigned char job;
	/* this+15 */ bool isVisible;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_SKILL_ENTRY> in(p);
		TPacket<PROTO_ZC_SKILL_ENTRY,char> out((size_t)0);

		out->PacketType = PacketType;
		out->PacketLength = out.size(); // adapt
		out->AID = in->AID;
		out->creatorAID = in->creatorAID;
		out->xPos = in->xPos;
		out->yPos = in->yPos;
		out->job = static_cast<int>(in->job); // adapt
		out->RadiusRange = 0; // adapt
		out->isVisible = in->isVisible;
		out->level = 0; // adapt
//		memset(out->msg, '\0', out.count()); // adapt

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_SKILL_ENTRY,char> in(p);
		TPacket<PACKET_ZC_SKILL_ENTRY> out;

		out->PacketType = PacketType;
//		out->PacketLength = out.size(); // adapt
		out->AID = in->AID;
		out->creatorAID = in->creatorAID;
		out->xPos = in->xPos;
		out->yPos = in->yPos;
		out->job = static_cast<unsigned char>(in->job); // adapt
//		out->RadiusRange = in->RadiusRange; // adapt
		out->isVisible = in->isVisible;
//		out->level = in->level; // adapt
//		memcpy(out->msg, in->msg, out.count()); // adapt

		return out;
	}
};


struct PACKET_ZC_SKILL_ENTRY2
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long creatorAID;
	/* this+10 */ short xPos;
	/* this+12 */ short yPos;
	/* this+14 */ unsigned char job;
	/* this+15 */ bool isVisible;
	/* this+16 */ bool isContens;
	/* this+17 */ char msg[80];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_SKILL_ENTRY2> in(p);
		size_t msglen = ( in->isContens ) ? strnlen(in->msg, countof(in->msg)-1) + 1 : 0;
		TPacket<PROTO_ZC_SKILL_ENTRY,char> out(msglen);

		out->PacketType = PacketType;
		out->PacketLength = out.size(); // adapt
		out->AID = in->AID;
		out->creatorAID = in->creatorAID;
		out->xPos = in->xPos;
		out->yPos = in->yPos;
		out->job = static_cast<int>(in->job); // adapt
		out->RadiusRange = 0; // adapt
		out->isVisible = in->isVisible;
		out->level = 0; // adapt
//		out->isContens = in->isContens; // adapt
		memset(out->msg, '\0', out.count()); memcpy(out->msg, in->msg, min(countof(in->msg), out.count())); // adapt

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_SKILL_ENTRY,char> in(p);
		TPacket<PACKET_ZC_SKILL_ENTRY2> out;

		out->PacketType = PacketType;
//		out->PacketLength = out.size(); // adapt
		out->AID = in->AID;
		out->creatorAID = in->creatorAID;
		out->xPos = in->xPos;
		out->yPos = in->yPos;
		out->job = static_cast<unsigned char>(in->job); // adapt
//		out->RadiusRange = in->RadiusRange; // adapt
		out->isVisible = in->isVisible;
//		out->level = in->level; // adapt
		out->isContens = ( in.count() > 0 ); // adapt
		memset(out->msg, '\0', countof(out->msg)); memcpy(out->msg, in->msg, min(countof(out->msg), in.count())); // adapt

		return out;
	}
};


struct PACKET_ZC_SKILL_ENTRY3
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short PacketLength;
	/* this+ 4 */ unsigned long AID;
	/* this+ 8 */ unsigned long creatorAID;
	/* this+12 */ short xPos;
	/* this+14 */ short yPos;
	/* this+16 */ unsigned char job;
	/* this+17 */ char RadiusRange;
	/* this+18 */ bool isVisible;
	/* this+19 */ char msg[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_SKILL_ENTRY3,char> in(p);
		TPacket<PROTO_ZC_SKILL_ENTRY,char> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->AID = in->AID;
		out->creatorAID = in->creatorAID;
		out->xPos = in->xPos;
		out->yPos = in->yPos;
		out->job = static_cast<int>(in->job); // adapt
		out->RadiusRange = in->RadiusRange;
		out->isVisible = in->isVisible;
		out->level = 0; // adapt
		memcpy(out->msg, in->msg, out.count());

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_SKILL_ENTRY,char> in(p);
		TPacket<PACKET_ZC_SKILL_ENTRY3,char> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->AID = in->AID;
		out->creatorAID = in->creatorAID;
		out->xPos = in->xPos;
		out->yPos = in->yPos;
		out->job = static_cast<unsigned char>(in->job); // adapt
		out->RadiusRange = in->RadiusRange;
		out->isVisible = in->isVisible;
//		out->level = in->level; // adapt
		memcpy(out->msg, in->msg, out.count());

		return out;
	}
};


struct PACKET_ZC_SKILL_ENTRY4
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short PacketLength;
	/* this+ 4 */ unsigned long AID;
	/* this+ 8 */ unsigned long creatorAID;
	/* this+12 */ short xPos;
	/* this+14 */ short yPos;
	/* this+16 */ int job;
	/* this+20 */ char RadiusRange;
	/* this+21 */ bool isVisible;
	/* this+22 */ char msg[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_SKILL_ENTRY4,char> in(p);
		TPacket<PROTO_ZC_SKILL_ENTRY,char> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->AID = in->AID;
		out->creatorAID = in->creatorAID;
		out->xPos = in->xPos;
		out->yPos = in->yPos;
		out->job = in->job;
		out->RadiusRange = in->RadiusRange;
		out->isVisible = in->isVisible;
		out->level = 0; // adapt
		memcpy(out->msg, in->msg, out.count());

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_SKILL_ENTRY,char> in(p);
		TPacket<PACKET_ZC_SKILL_ENTRY4,char> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->AID = in->AID;
		out->creatorAID = in->creatorAID;
		out->xPos = in->xPos;
		out->yPos = in->yPos;
		out->job = in->job;
		out->RadiusRange = in->RadiusRange;
		out->isVisible = in->isVisible;
//		out->level = in->level; // adapt
		memcpy(out->msg, in->msg, out.count());

		return out;
	}
};


struct PACKET_ZC_SKILL_ENTRY5
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short PacketLength;
	/* this+ 4 */ unsigned long AID;
	/* this+ 8 */ unsigned long creatorAID;
	/* this+12 */ short xPos;
	/* this+14 */ short yPos;
	/* this+16 */ int job;
	/* this+20 */ char RadiusRange;
	/* this+21 */ bool isVisible;
	/* this+22 */ unsigned char level;
	/* this+23 */ char msg[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_SKILL_ENTRY5,char> in(p);
		TPacket<PROTO_ZC_SKILL_ENTRY,char> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->AID = in->AID;
		out->creatorAID = in->creatorAID;
		out->xPos = in->xPos;
		out->yPos = in->yPos;
		out->job = in->job;
		out->RadiusRange = in->RadiusRange;
		out->isVisible = in->isVisible;
		out->level = in->level;
		memcpy(out->msg, in->msg, out.count());

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_SKILL_ENTRY,char> in(p);
		TPacket<PACKET_ZC_SKILL_ENTRY5,char> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->AID = in->AID;
		out->creatorAID = in->creatorAID;
		out->xPos = in->xPos;
		out->yPos = in->yPos;
		out->job = in->job;
		out->RadiusRange = in->RadiusRange;
		out->isVisible = in->isVisible;
		out->level = in->level;
		memcpy(out->msg, in->msg, out.count());

		return out;
	}
};
