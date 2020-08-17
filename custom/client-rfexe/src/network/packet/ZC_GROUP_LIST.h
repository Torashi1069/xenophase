struct PROTO_ZC_GROUP_LIST
{
	short PacketType;
	short PacketLength;
	char groupName[24];
	struct GROUPMEMBER_INFO
	{
		unsigned long AID;
		char characterName[24];
		char mapName[16];
		unsigned char Role;
		unsigned char State;
	}
	Info[];
};


struct PACKET_ZC_GROUP_LIST
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short PacketLength;
	/* this+ 4 */ char groupName[24];
	/* this+28 */ struct GROUPMEMBER_INFO
	              {
	              	/* this+ 0 */ unsigned long AID;
	              	/* this+ 4 */ char characterName[24];
	              	/* this+28 */ char mapName[16];
	              	/* this+44 */ unsigned char Role;
	              	/* this+45 */ unsigned char State;
	              }
	              Info[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_GROUP_LIST,PACKET_ZC_GROUP_LIST::GROUPMEMBER_INFO> in(p);
		TPacket<PROTO_ZC_GROUP_LIST,PROTO_ZC_GROUP_LIST::GROUPMEMBER_INFO> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		memcpy(out->groupName, in->groupName, 24);

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Info[i].AID = in->Info[i].AID;
			memcpy(out->Info[i].characterName, in->Info[i].characterName, 24);
			memcpy(out->Info[i].mapName, in->Info[i].mapName, 16);
			out->Info[i].Role = in->Info[i].Role;
			out->Info[i].State = in->Info[i].State;
		}

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_GROUP_LIST,PROTO_ZC_GROUP_LIST::GROUPMEMBER_INFO> in(p);
		TPacket<PACKET_ZC_GROUP_LIST,PACKET_ZC_GROUP_LIST::GROUPMEMBER_INFO> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		memcpy(out->groupName, in->groupName, 24);

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Info[i].AID = in->Info[i].AID;
			memcpy(out->Info[i].characterName, in->Info[i].characterName, 24);
			memcpy(out->Info[i].mapName, in->Info[i].mapName, 16);
			out->Info[i].Role = in->Info[i].Role;
			out->Info[i].State = in->Info[i].State;
		}

		return out;
	}
};
