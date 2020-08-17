struct PROTO_ZC_ALL_QUEST_MISSION
{
	short PacketType;
	short PacketLength;
	int count;
	struct PACKET_ZC_QUEST_MISSION_INFO
	{
		unsigned long questID;
		long quest_svrTime;
		long quest_endTime;
		short count;
		struct PACKET_ZC_MISSION_HUNT
		{
			unsigned long mobGID;
			short huntCount;
			char mobName[24];
		}
		hunt[3];
	}
	misInfo[];
};


struct PACKET_ZC_ALL_QUEST_MISSION
{
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ int count;
	/* this+8 */ struct PACKET_ZC_QUEST_MISSION_INFO
	             {
	             	/* this+ 0 */ unsigned long questID;
	             	/* this+ 4 */ long quest_svrTime;
	             	/* this+ 8 */ long quest_endTime;
	             	/* this+12 */ short count;
	             	/* this+14 */ struct PACKET_ZC_MISSION_HUNT
	             	              {
	             	              	/* this+0 */ unsigned long mobGID;
	             	              	/* this+4 */ short huntCount;
	             	              	/* this+6 */ char mobName[24];
	             	              }
	             	              hunt[3];
	             }
	             misInfo[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ALL_QUEST_MISSION,PACKET_ZC_ALL_QUEST_MISSION::PACKET_ZC_QUEST_MISSION_INFO> in(p);
		TPacket<PROTO_ZC_ALL_QUEST_MISSION,PROTO_ZC_ALL_QUEST_MISSION::PACKET_ZC_QUEST_MISSION_INFO> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->count = in->count;

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->misInfo[i].questID = in->misInfo[i].questID;
			out->misInfo[i].quest_svrTime = in->misInfo[i].quest_svrTime;
			out->misInfo[i].quest_endTime = in->misInfo[i].quest_endTime;
			out->misInfo[i].count = in->misInfo[i].count;

			for( size_t j = 0; j < 3; ++j )
			{
				out->misInfo[i].hunt[j].mobGID = in->misInfo[i].hunt[j].mobGID;
				out->misInfo[i].hunt[j].huntCount = in->misInfo[i].hunt[j].huntCount;
				memcpy(out->misInfo[i].hunt[j].mobName, in->misInfo[i].hunt[j].mobName, 24);
			}
		}

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_ALL_QUEST_MISSION,PROTO_ZC_ALL_QUEST_MISSION::PACKET_ZC_QUEST_MISSION_INFO> in(p);
		TPacket<PACKET_ZC_ALL_QUEST_MISSION,PACKET_ZC_ALL_QUEST_MISSION::PACKET_ZC_QUEST_MISSION_INFO> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->count = in->count;

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->misInfo[i].questID = in->misInfo[i].questID;
			out->misInfo[i].quest_svrTime = in->misInfo[i].quest_svrTime;
			out->misInfo[i].quest_endTime = in->misInfo[i].quest_endTime;
			out->misInfo[i].count = in->misInfo[i].count;

			for( size_t j = 0; j < 3; ++j )
			{
				out->misInfo[i].hunt[j].mobGID = in->misInfo[i].hunt[j].mobGID;
				out->misInfo[i].hunt[j].huntCount = in->misInfo[i].hunt[j].huntCount;
				memcpy(out->misInfo[i].hunt[j].mobName, in->misInfo[i].hunt[j].mobName, 24);
			}
		}

		return out;
	}
};
