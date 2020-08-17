struct PROTO_ZC_MONSTER_INFO
{
	short PacketType;
	short job;
	short level;
	short size;
	int hp;
	short def;
	short raceType;
	short mdefPower;
	short property;
	struct
	{
		unsigned char water;
		unsigned char earth;
		unsigned char fire;
		unsigned char wind;
		unsigned char poison;
		unsigned char saint;
		unsigned char dark;
		unsigned char mental;
		unsigned char undead;
	}
	propertyTable;
};


struct PACKET_ZC_MONSTER_INFO
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short job;
	/* this+ 4 */ short level;
	/* this+ 6 */ short size;
	/* this+ 8 */ int hp;
	/* this+12 */ short def;
	/* this+14 */ short raceType;
	/* this+16 */ short mdefPower;
	/* this+18 */ short property;
	/* this+20 */ struct
	              {
	              	/* this+0 */ unsigned char water;
	              	/* this+1 */ unsigned char earth;
	              	/* this+2 */ unsigned char fire;
	              	/* this+3 */ unsigned char wind;
	              	/* this+4 */ unsigned char poison;
	              	/* this+5 */ unsigned char saint;
	              	/* this+6 */ unsigned char dark;
	              	/* this+7 */ unsigned char mental;
	              	/* this+8 */ unsigned char undead;
	              }
	              propertyTable;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_MONSTER_INFO> in(p);
		TPacket<PROTO_ZC_MONSTER_INFO> out;

		out->PacketType = PacketType;
		out->job = in->job;
		out->level = in->level;
		out->size = in->size;
		out->hp = in->hp;
		out->def = in->def;
		out->raceType = in->raceType;
		out->mdefPower = in->mdefPower;
		out->property = in->property;
		out->propertyTable.water = in->propertyTable.water;
		out->propertyTable.earth = in->propertyTable.earth;
		out->propertyTable.fire = in->propertyTable.fire;
		out->propertyTable.wind = in->propertyTable.wind;
		out->propertyTable.poison = in->propertyTable.poison;
		out->propertyTable.saint = in->propertyTable.saint;
		out->propertyTable.dark = in->propertyTable.dark;
		out->propertyTable.mental = in->propertyTable.mental;
		out->propertyTable.undead = in->propertyTable.undead;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_MONSTER_INFO> in(p);
		TPacket<PACKET_ZC_MONSTER_INFO> out;

		out->PacketType = PacketType;
		out->job = in->job;
		out->level = in->level;
		out->size = in->size;
		out->hp = in->hp;
		out->def = in->def;
		out->raceType = in->raceType;
		out->mdefPower = in->mdefPower;
		out->property = in->property;
		out->propertyTable.water = in->propertyTable.water;
		out->propertyTable.earth = in->propertyTable.earth;
		out->propertyTable.fire = in->propertyTable.fire;
		out->propertyTable.wind = in->propertyTable.wind;
		out->propertyTable.poison = in->propertyTable.poison;
		out->propertyTable.saint = in->propertyTable.saint;
		out->propertyTable.dark = in->propertyTable.dark;
		out->propertyTable.mental = in->propertyTable.mental;
		out->propertyTable.undead = in->propertyTable.undead;

		return out;
	}
};
