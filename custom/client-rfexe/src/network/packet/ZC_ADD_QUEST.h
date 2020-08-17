struct PROTO_ZC_ADD_QUEST
{
	short PacketType;
	unsigned long questID;
	bool active;
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
};


struct PACKET_ZC_ADD_QUEST
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long questID;
	/* this+ 6 */ bool active;
	/* this+ 7 */ long quest_svrTime;
	/* this+11 */ long quest_endTime;
	/* this+15 */ short count;
	/* this+17 */ struct PACKET_ZC_MISSION_HUNT
	              {
	              	/* this+0 */ unsigned long mobGID;
	              	/* this+4 */ short huntCount;
	              	/* this+6 */ char mobName[24];
	              }
	              hunt[3];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ADD_QUEST> in(p);
		TPacket<PROTO_ZC_ADD_QUEST> out;

		out->PacketType = PacketType;
		out->questID = in->questID;
		out->active = in->active;
		out->quest_svrTime = in->quest_svrTime;
		out->quest_endTime = in->quest_endTime;
		out->count = in->count;
		for( size_t i = 0; i < 3; ++i )
		{
			out->hunt[i].mobGID = in->hunt[i].mobGID;
			out->hunt[i].huntCount = in->hunt[i].huntCount;
			memcpy(out->hunt[i].mobName, in->hunt[i].mobName, 24);
		}

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_ADD_QUEST> in(p);
		TPacket<PACKET_ZC_ADD_QUEST> out;

		out->PacketType = PacketType;
		out->questID = in->questID;
		out->active = in->active;
		out->quest_svrTime = in->quest_svrTime;
		out->quest_endTime = in->quest_endTime;
		out->count = in->count;
		for( size_t i = 0; i < 3; ++i )
		{
			out->hunt[i].mobGID = in->hunt[i].mobGID;
			out->hunt[i].huntCount = in->hunt[i].huntCount;
			memcpy(out->hunt[i].mobName, in->hunt[i].mobName, 24);
		}

		return out;
	}
};
