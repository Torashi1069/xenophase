struct PROTO_ZC_ALL_QUEST_LIST
{
	short PacketType;
	short PacketLength;
	int questCount;
	struct PACKET_ZC_QUEST_INFO
	{
		unsigned long questID;
		bool active;
	}
	questInfo[];
};


struct PACKET_ZC_ALL_QUEST_LIST
{
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ int questCount;
	/* this+8 */ struct PACKET_ZC_QUEST_INFO
	             {
	             	/* this+0 */ unsigned long questID;
	             	/* this+4 */ bool active;
	             }
	             questInfo[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ALL_QUEST_LIST,PACKET_ZC_ALL_QUEST_LIST::PACKET_ZC_QUEST_INFO> in(p);
		TPacket<PROTO_ZC_ALL_QUEST_LIST,PROTO_ZC_ALL_QUEST_LIST::PACKET_ZC_QUEST_INFO> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->questCount = in->questCount;

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->questInfo[i].questID = in->questInfo[i].questID;
			out->questInfo[i].active = in->questInfo[i].active;
		}

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_ALL_QUEST_LIST,PROTO_ZC_ALL_QUEST_LIST::PACKET_ZC_QUEST_INFO> in(p);
		TPacket<PACKET_ZC_ALL_QUEST_LIST,PACKET_ZC_ALL_QUEST_LIST::PACKET_ZC_QUEST_INFO> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->questCount = in->questCount;

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->questInfo[i].questID = in->questInfo[i].questID;
			out->questInfo[i].active = in->questInfo[i].active;
		}

		return out;
	}
};
