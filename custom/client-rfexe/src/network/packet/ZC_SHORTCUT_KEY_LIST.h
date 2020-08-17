struct PROTO_ZC_SHORTCUT_KEY_LIST
{
	short PacketType;
	struct tagShortCutKey
	{
		char isSkill;
		unsigned long ID;
		short count;
	}
	ShortCutKey[38];
};


struct PACKET_ZC_SHORTCUT_KEY_LIST
{
	/* this+0 */ short PacketType;
	/* this+2 */ struct tagShortCutKey
	             {
	             	/* this+0 */ char isSkill;
	             	/* this+1 */ unsigned long ID;
	             	/* this+5 */ short count;
	             }
	             ShortCutKey[27];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_SHORTCUT_KEY_LIST> in(p);
		TPacket<PROTO_ZC_SHORTCUT_KEY_LIST> out;

		out->PacketType = PacketType;

		for( size_t i = 0; i < 27; ++i )
		{
			out->ShortCutKey[i].isSkill = in->ShortCutKey[i].isSkill;
			out->ShortCutKey[i].ID      = in->ShortCutKey[i].ID;
			out->ShortCutKey[i].count   = in->ShortCutKey[i].count;
		}

		for( size_t i = 27; i < 38; ++i ) // adapt
		{
			out->ShortCutKey[i].isSkill = 0; // adapt
			out->ShortCutKey[i].ID      = 0; // adapt
			out->ShortCutKey[i].count   = 0; // adapt
		}

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_SHORTCUT_KEY_LIST> in(p);
		TPacket<PACKET_ZC_SHORTCUT_KEY_LIST> out;

		out->PacketType = PacketType;

		for( size_t i = 0; i < 27; ++i ) // adapt
		{
			out->ShortCutKey[i].isSkill = in->ShortCutKey[i].isSkill;
			out->ShortCutKey[i].ID      = in->ShortCutKey[i].ID;
			out->ShortCutKey[i].count   = in->ShortCutKey[i].count;
		}

		return out;
	}
};


struct PACKET_ZC_SHORTCUT_KEY_LIST_V2
{
	/* this+0 */ short PacketType;
	/* this+2 */ struct tagShortCutKey
	             {
	             	/* this+0 */ char isSkill;
	             	/* this+1 */ unsigned long ID;
	             	/* this+5 */ short count;
	             }
	             ShortCutKey[38];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_SHORTCUT_KEY_LIST_V2> in(p);
		TPacket<PROTO_ZC_SHORTCUT_KEY_LIST> out;

		out->PacketType = PacketType;

		for( size_t i = 0; i < 38; ++i )
		{
			out->ShortCutKey[i].isSkill = in->ShortCutKey[i].isSkill;
			out->ShortCutKey[i].ID      = in->ShortCutKey[i].ID;
			out->ShortCutKey[i].count   = in->ShortCutKey[i].count;
		}

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_SHORTCUT_KEY_LIST> in(p);
		TPacket<PACKET_ZC_SHORTCUT_KEY_LIST_V2> out;

		out->PacketType = PacketType;

		for( size_t i = 0; i < 38; ++i )
		{
			out->ShortCutKey[i].isSkill = in->ShortCutKey[i].isSkill;
			out->ShortCutKey[i].ID      = in->ShortCutKey[i].ID;
			out->ShortCutKey[i].count   = in->ShortCutKey[i].count;
		}

		return out;
	}
};

