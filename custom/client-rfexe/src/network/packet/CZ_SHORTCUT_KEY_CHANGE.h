struct PROTO_CZ_SHORTCUT_KEY_CHANGE
{
	short PacketType;
	unsigned short Index;
	struct tagShortCutKey
	{
		char isSkill;
		unsigned long ID;
		short count;
	}
	ShortCutKey;
};


struct PACKET_CZ_SHORTCUT_KEY_CHANGE
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short Index;
	/* this+4 */ struct tagShortCutKey
	             {
	             	/* this+0 */ char isSkill;
	             	/* this+1 */ unsigned long ID;
	             	/* this+5 */ short count;
	             }
	             ShortCutKey;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_SHORTCUT_KEY_CHANGE> in(p);
		TPacket<PROTO_CZ_SHORTCUT_KEY_CHANGE> out;

		out->PacketType = PacketType;
		out->Index = in->Index;
		out->ShortCutKey.isSkill = in->ShortCutKey.isSkill;
		out->ShortCutKey.ID = in->ShortCutKey.ID;
		out->ShortCutKey.count = in->ShortCutKey.count;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_SHORTCUT_KEY_CHANGE> in(p);
		TPacket<PACKET_CZ_SHORTCUT_KEY_CHANGE> out;

		out->PacketType = PacketType;
		out->Index = in->Index;
		out->ShortCutKey.isSkill = in->ShortCutKey.isSkill;
		out->ShortCutKey.ID = in->ShortCutKey.ID;
		out->ShortCutKey.count = in->ShortCutKey.count;

		return out;
	}
};
