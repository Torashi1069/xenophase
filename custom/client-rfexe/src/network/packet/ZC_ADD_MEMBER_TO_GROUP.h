struct PROTO_ZC_ADD_MEMBER_TO_GROUP
{
	short PacketType;
	int PacketVersion; // 1:basic, 2:w/itemshare
	unsigned long AID;
	unsigned long Role;
	short xPos;
	short yPos;
	unsigned char state;
	char groupName[24];
	char characterName[24];
	char mapName[16];
	unsigned char ItemPickupRule;
	unsigned char ItemDivisionRule;
};


struct PACKET_ZC_ADD_MEMBER_TO_GROUP
{
	/* this +0 */ short PacketType;
	/* this +2 */ unsigned long AID;
	/* this +6 */ unsigned long Role;
	/* this+10 */ short xPos;
	/* this+12 */ short yPos;
	/* this+14 */ unsigned char state;
	/* this+15 */ char groupName[24];
	/* this+39 */ char characterName[24];
	/* this+63 */ char mapName[16];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ADD_MEMBER_TO_GROUP> in(p);
		TPacket<PROTO_ZC_ADD_MEMBER_TO_GROUP> out;

		out->PacketType = PacketType;
		out->PacketVersion = 1;
		out->AID = in->AID;
		out->Role = in->Role;
		out->xPos = in->xPos;
		out->yPos = in->yPos;
		out->state = in->state;
		memcpy(out->groupName, in->groupName, 24);
		memcpy(out->characterName, in->characterName, 24);
		memcpy(out->mapName, in->mapName, 16);
		out->ItemPickupRule = 0; // adapt // broken
		out->ItemDivisionRule = 0; // adapt // broken

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_ADD_MEMBER_TO_GROUP> in(p);
		TPacket<PACKET_ZC_ADD_MEMBER_TO_GROUP> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->Role = in->Role;
		out->xPos = in->xPos;
		out->yPos = in->yPos;
		out->state = in->state;
		memcpy(out->groupName, in->groupName, 24);
		memcpy(out->characterName, in->characterName, 24);
		memcpy(out->mapName, in->mapName, 16);
//		out->ItemPickupRule = in->ItemPickupRule; // adapt
//		out->ItemDivisionRule = in->ItemDivisionRule; // adapt

		return out;
	}
};


struct PACKET_ZC_ADD_MEMBER_TO_GROUP2
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long Role;
	/* this+10 */ short xPos;
	/* this+12 */ short yPos;
	/* this+14 */ unsigned char state;
	/* this+15 */ char groupName[24];
	/* this+39 */ char characterName[24];
	/* this+63 */ char mapName[16];
	/* this+79 */ unsigned char ItemPickupRule;
	/* this+80 */ unsigned char ItemDivisionRule;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ADD_MEMBER_TO_GROUP2> in(p);
		TPacket<PROTO_ZC_ADD_MEMBER_TO_GROUP> out;

		out->PacketType = PacketType;
		out->PacketVersion = 2;
		out->AID = in->AID;
		out->Role = in->Role;
		out->xPos = in->xPos;
		out->yPos = in->yPos;
		out->state = in->state;
		memcpy(out->groupName, in->groupName, 24);
		memcpy(out->characterName, in->characterName, 24);
		memcpy(out->mapName, in->mapName, 16);
		out->ItemPickupRule = in->ItemPickupRule;
		out->ItemDivisionRule = in->ItemDivisionRule;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_ADD_MEMBER_TO_GROUP> in(p);
		if( in->PacketVersion < 2 ) return NULL;
		TPacket<PACKET_ZC_ADD_MEMBER_TO_GROUP2> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->Role = in->Role;
		out->xPos = in->xPos;
		out->yPos = in->yPos;
		out->state = in->state;
		memcpy(out->groupName, in->groupName, 24);
		memcpy(out->characterName, in->characterName, 24);
		memcpy(out->mapName, in->mapName, 16);
		out->ItemPickupRule = in->ItemPickupRule;
		out->ItemDivisionRule = in->ItemDivisionRule;

		return out;
	}
};
