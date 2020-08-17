struct PROTO_ZC_UPDATE_MISSION_HUNT
{
	short PacketType;
	short PacketLength;
	short count;
	struct PACKET_MOB_HUNTING
	{
		unsigned long questID;
		unsigned long mobGID;
		short maxCount;
		short count;
	}
	huntInfo[];
};


struct PACKET_ZC_UPDATE_MISSION_HUNT_2009
{
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ short count;
	/* this+6 */ struct PACKET_MOB_HUNTING
	             {
	             	/* this+0 */ unsigned long questID;
	             	/* this+4 */ unsigned long mobGID;
	             	/* this+8 */ short count;
	             }
	             huntInfo[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_UPDATE_MISSION_HUNT_2009,PACKET_ZC_UPDATE_MISSION_HUNT_2009::PACKET_MOB_HUNTING> in(p);
		TPacket<PROTO_ZC_UPDATE_MISSION_HUNT,PROTO_ZC_UPDATE_MISSION_HUNT::PACKET_MOB_HUNTING> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->count = in->count;

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->huntInfo[i].questID = in->huntInfo[i].questID;
			out->huntInfo[i].mobGID = in->huntInfo[i].mobGID;
			out->huntInfo[i].maxCount = 0; // adapt //FIXME
			out->huntInfo[i].count = in->huntInfo[i].count;
		}

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_UPDATE_MISSION_HUNT,PROTO_ZC_UPDATE_MISSION_HUNT::PACKET_MOB_HUNTING> in(p);
		TPacket<PACKET_ZC_UPDATE_MISSION_HUNT_2009,PACKET_ZC_UPDATE_MISSION_HUNT_2009::PACKET_MOB_HUNTING> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->count = in->count;

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->huntInfo[i].questID = in->huntInfo[i].questID;
			out->huntInfo[i].mobGID = in->huntInfo[i].mobGID;
//			out->huntInfo[i].maxCount = in->huntInfo[i].maxCount; // adapt
			out->huntInfo[i].count = in->huntInfo[i].count;
		}

		return out;
	}
};


struct PACKET_ZC_UPDATE_MISSION_HUNT_2010
{
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ short count;
	/* this+6 */ struct PACKET_MOB_HUNTING
	             {
	             	/* this+ 0 */ unsigned long questID;
	             	/* this+ 4 */ unsigned long mobGID;
	             	/* this+ 8 */ short maxCount;
	             	/* this+10 */ short count;
	             }
	             huntInfo[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_UPDATE_MISSION_HUNT_2010,PACKET_ZC_UPDATE_MISSION_HUNT_2010::PACKET_MOB_HUNTING> in(p);
		TPacket<PROTO_ZC_UPDATE_MISSION_HUNT,PROTO_ZC_UPDATE_MISSION_HUNT::PACKET_MOB_HUNTING> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->count = in->count;

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->huntInfo[i].questID = in->huntInfo[i].questID;
			out->huntInfo[i].mobGID = in->huntInfo[i].mobGID;
			out->huntInfo[i].maxCount = in->huntInfo[i].maxCount;
			out->huntInfo[i].count = in->huntInfo[i].count;
		}

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_UPDATE_MISSION_HUNT,PROTO_ZC_UPDATE_MISSION_HUNT::PACKET_MOB_HUNTING> in(p);
		TPacket<PACKET_ZC_UPDATE_MISSION_HUNT_2010,PACKET_ZC_UPDATE_MISSION_HUNT_2010::PACKET_MOB_HUNTING> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->count = in->count;

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->huntInfo[i].questID = in->huntInfo[i].questID;
			out->huntInfo[i].mobGID = in->huntInfo[i].mobGID;
			out->huntInfo[i].maxCount = in->huntInfo[i].maxCount;
			out->huntInfo[i].count = in->huntInfo[i].count;
		}

		return out;
	}
};
