struct PROTO_HC_ACCEPT_MAKECHAR
{
	short PacketType; // PROTOID_HC_ACCEPT_MAKECHAR

	struct CHARACTER_INFO
	{
		unsigned long GID;
		int exp;
		int money;
		int jobexp;
		int joblevel;
		int bodystate;
		int healthstate;
		int effectstate;
		int virtue;
		int honor;
		short jobpoint;
		int hp;
		int maxhp;
		short sp;
		short maxsp;
		short speed;
		short job;
		short head;
		short weapon;
		short level;
		short sppoint;
		short accessory;
		short shield;
		short accessory2;
		short accessory3;
		short headpalette;
		short bodypalette;
		unsigned char name[24];
		unsigned char Str;
		unsigned char Agi;
		unsigned char Vit;
		unsigned char Int;
		unsigned char Dex;
		unsigned char Luk;
		unsigned char CharNum;
		unsigned char haircolor;
		short bIsChangedCharName;
		int nRobe;
	}
	CharInfo;
};


struct PACKET_HC_ACCEPT_MAKECHAR
{
	/* this+0 */ short PacketType;
	/* this+2 */ struct CHARACTER_INFO
	             {
	             	/* this+  0 */ unsigned long GID;
	             	/* this+  4 */ int exp;
	             	/* this+  8 */ int money;
	             	/* this+ 12 */ int jobexp;
	             	/* this+ 16 */ int joblevel;
	             	/* this+ 20 */ int bodystate;
	             	/* this+ 24 */ int healthstate;
	             	/* this+ 28 */ int effectstate;
	             	/* this+ 32 */ int virtue;
	             	/* this+ 36 */ int honor;
	             	/* this+ 40 */ short jobpoint;
	             	/* this+ 42 */ short hp;
	             	/* this+ 44 */ short maxhp;
	             	/* this+ 46 */ short sp;
	             	/* this+ 48 */ short maxsp;
	             	/* this+ 50 */ short speed;
	             	/* this+ 52 */ short job;
	             	/* this+ 54 */ short head;
	             	/* this+ 56 */ short weapon;
	             	/* this+ 58 */ short level;
	             	/* this+ 60 */ short sppoint;
	             	/* this+ 62 */ short accessory;
	             	/* this+ 64 */ short shield;
	             	/* this+ 66 */ short accessory2;
	             	/* this+ 68 */ short accessory3;
	             	/* this+ 70 */ short headpalette;
	             	/* this+ 72 */ short bodypalette;
	             	/* this+ 74 */ unsigned char name[24];
	             	/* this+ 98 */ unsigned char Str;
	             	/* this+ 99 */ unsigned char Agi;
	             	/* this+100 */ unsigned char Vit;
	             	/* this+101 */ unsigned char Int;
	             	/* this+102 */ unsigned char Dex;
	             	/* this+103 */ unsigned char Luk;
	             	/* this+104 */ unsigned char CharNum;
	             	/* this+105 */ unsigned char haircolor;
	             }
	             CharInfo;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_HC_ACCEPT_MAKECHAR> in(p);
		TPacket<PROTO_HC_ACCEPT_MAKECHAR> out;

		out->PacketType = PacketType;
		out->CharInfo.GID = in->CharInfo.GID;
		out->CharInfo.exp = in->CharInfo.exp;
		out->CharInfo.money = in->CharInfo.money;
		out->CharInfo.jobexp = in->CharInfo.jobexp;
		out->CharInfo.joblevel = in->CharInfo.joblevel;
		out->CharInfo.bodystate = in->CharInfo.bodystate;
		out->CharInfo.healthstate = in->CharInfo.healthstate;
		out->CharInfo.effectstate = in->CharInfo.effectstate;
		out->CharInfo.virtue = in->CharInfo.virtue;
		out->CharInfo.honor = in->CharInfo.honor;
		out->CharInfo.jobpoint = in->CharInfo.jobpoint;
		out->CharInfo.hp = in->CharInfo.hp;
		out->CharInfo.maxhp = in->CharInfo.maxhp;
		out->CharInfo.sp = in->CharInfo.sp;
		out->CharInfo.maxsp = in->CharInfo.maxsp;
		out->CharInfo.speed = in->CharInfo.speed;
		out->CharInfo.job = in->CharInfo.job;
		out->CharInfo.head = in->CharInfo.head;
		out->CharInfo.weapon = in->CharInfo.weapon;
		out->CharInfo.level = in->CharInfo.level;
		out->CharInfo.sppoint = in->CharInfo.sppoint;
		out->CharInfo.accessory = in->CharInfo.accessory;
		out->CharInfo.shield = in->CharInfo.shield;
		out->CharInfo.accessory2 = in->CharInfo.accessory2;
		out->CharInfo.accessory3 = in->CharInfo.accessory3;
		out->CharInfo.headpalette = in->CharInfo.headpalette;
		out->CharInfo.bodypalette = in->CharInfo.bodypalette;
		memcpy(out->CharInfo.name, in->CharInfo.name, 24);
		out->CharInfo.Str = in->CharInfo.Str;
		out->CharInfo.Agi = in->CharInfo.Agi;
		out->CharInfo.Vit = in->CharInfo.Vit;
		out->CharInfo.Int = in->CharInfo.Int;
		out->CharInfo.Dex = in->CharInfo.Dex;
		out->CharInfo.Luk = in->CharInfo.Luk;
		out->CharInfo.CharNum = in->CharInfo.CharNum;
		out->CharInfo.haircolor = in->CharInfo.haircolor;
		out->CharInfo.bIsChangedCharName = 1; // adapt
		out->CharInfo.nRobe = 0; // adapt

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_HC_ACCEPT_MAKECHAR> in(p);
		TPacket<PACKET_HC_ACCEPT_MAKECHAR> out;

		out->PacketType = PacketType;
		out->CharInfo.GID = in->CharInfo.GID;
		out->CharInfo.exp = in->CharInfo.exp;
		out->CharInfo.money = in->CharInfo.money;
		out->CharInfo.jobexp = in->CharInfo.jobexp;
		out->CharInfo.joblevel = in->CharInfo.joblevel;
		out->CharInfo.bodystate = in->CharInfo.bodystate;
		out->CharInfo.healthstate = in->CharInfo.healthstate;
		out->CharInfo.effectstate = in->CharInfo.effectstate;
		out->CharInfo.virtue = in->CharInfo.virtue;
		out->CharInfo.honor = in->CharInfo.honor;
		out->CharInfo.jobpoint = in->CharInfo.jobpoint;
		out->CharInfo.hp = min(in->CharInfo.hp, SHRT_MAX); // adapt
		out->CharInfo.maxhp = min(in->CharInfo.maxhp, SHRT_MAX); // adapt
		out->CharInfo.sp = in->CharInfo.sp;
		out->CharInfo.maxsp = in->CharInfo.maxsp;
		out->CharInfo.speed = in->CharInfo.speed;
		out->CharInfo.job = in->CharInfo.job;
		out->CharInfo.head = in->CharInfo.head;
		out->CharInfo.weapon = in->CharInfo.weapon;
		out->CharInfo.level = in->CharInfo.level;
		out->CharInfo.sppoint = in->CharInfo.sppoint;
		out->CharInfo.accessory = in->CharInfo.accessory;
		out->CharInfo.shield = in->CharInfo.shield;
		out->CharInfo.accessory2 = in->CharInfo.accessory2;
		out->CharInfo.accessory3 = in->CharInfo.accessory3;
		out->CharInfo.headpalette = in->CharInfo.headpalette;
		out->CharInfo.bodypalette = in->CharInfo.bodypalette;
		memcpy(out->CharInfo.name, in->CharInfo.name, 24);
		out->CharInfo.Str = in->CharInfo.Str;
		out->CharInfo.Agi = in->CharInfo.Agi;
		out->CharInfo.Vit = in->CharInfo.Vit;
		out->CharInfo.Int = in->CharInfo.Int;
		out->CharInfo.Dex = in->CharInfo.Dex;
		out->CharInfo.Luk = in->CharInfo.Luk;
		out->CharInfo.CharNum = in->CharInfo.CharNum;
		out->CharInfo.haircolor = in->CharInfo.haircolor;
//		out->CharInfo.bIsChangedCharName = in->CharInfo.bIsChangedCharName; // adapt
//		out->CharInfo.nRobe = in->CharInfo.nRobe; // adapt

		return out;
	}
};


//TODO: determine/confirm real origin date
struct PACKET_HC_ACCEPT_MAKECHAR_KRO20061023
{
	/* this+0 */ short PacketType;
	/* this+2 */ struct CHARACTER_INFO_NEO_UNION
	             {
	              	/* this+  0 */ unsigned long GID;
	              	/* this+  4 */ int exp;
	              	/* this+  8 */ int money;
	              	/* this+ 12 */ int jobexp;
	              	/* this+ 16 */ int joblevel;
	              	/* this+ 20 */ int bodystate;
	              	/* this+ 24 */ int healthstate;
	              	/* this+ 28 */ int effectstate;
	              	/* this+ 32 */ int virtue;
	              	/* this+ 36 */ int honor;
	              	/* this+ 40 */ short jobpoint;
	              	/* this+ 42 */ int hp;
	              	/* this+ 46 */ int maxhp;
	              	/* this+ 50 */ short sp;
	              	/* this+ 52 */ short maxsp;
	              	/* this+ 54 */ short speed;
	              	/* this+ 56 */ short job;
	              	/* this+ 58 */ short head;
	              	/* this+ 60 */ short weapon;
	              	/* this+ 62 */ short level;
	              	/* this+ 64 */ short sppoint;
	              	/* this+ 66 */ short accessory;
	              	/* this+ 68 */ short shield;
	              	/* this+ 70 */ short accessory2;
	              	/* this+ 72 */ short accessory3;
	              	/* this+ 74 */ short headpalette;
	              	/* this+ 76 */ short bodypalette;
	              	/* this+ 78 */ unsigned char name[24];
	              	/* this+102 */ unsigned char Str;
	              	/* this+103 */ unsigned char Agi;
	              	/* this+104 */ unsigned char Vit;
	              	/* this+105 */ unsigned char Int;
	              	/* this+106 */ unsigned char Dex;
	              	/* this+107 */ unsigned char Luk;
	              	/* this+108 */ unsigned char CharNum;
	              	/* this+109 */ unsigned char haircolor;
	              	/* this+110 */ short bIsChangedCharName;
	             }
	             CharInfo;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_HC_ACCEPT_MAKECHAR_KRO20061023> in(p);
		TPacket<PROTO_HC_ACCEPT_MAKECHAR> out;

		out->PacketType = PacketType;
		out->CharInfo.GID = in->CharInfo.GID;
		out->CharInfo.exp = in->CharInfo.exp;
		out->CharInfo.money = in->CharInfo.money;
		out->CharInfo.jobexp = in->CharInfo.jobexp;
		out->CharInfo.joblevel = in->CharInfo.joblevel;
		out->CharInfo.bodystate = in->CharInfo.bodystate;
		out->CharInfo.healthstate = in->CharInfo.healthstate;
		out->CharInfo.effectstate = in->CharInfo.effectstate;
		out->CharInfo.virtue = in->CharInfo.virtue;
		out->CharInfo.honor = in->CharInfo.honor;
		out->CharInfo.jobpoint = in->CharInfo.jobpoint;
		out->CharInfo.hp = in->CharInfo.hp;
		out->CharInfo.maxhp = in->CharInfo.maxhp;
		out->CharInfo.sp = in->CharInfo.sp;
		out->CharInfo.maxsp = in->CharInfo.maxsp;
		out->CharInfo.speed = in->CharInfo.speed;
		out->CharInfo.job = in->CharInfo.job;
		out->CharInfo.head = in->CharInfo.head;
		out->CharInfo.weapon = in->CharInfo.weapon;
		out->CharInfo.level = in->CharInfo.level;
		out->CharInfo.sppoint = in->CharInfo.sppoint;
		out->CharInfo.accessory = in->CharInfo.accessory;
		out->CharInfo.shield = in->CharInfo.shield;
		out->CharInfo.accessory2 = in->CharInfo.accessory2;
		out->CharInfo.accessory3 = in->CharInfo.accessory3;
		out->CharInfo.headpalette = in->CharInfo.headpalette;
		out->CharInfo.bodypalette = in->CharInfo.bodypalette;
		memcpy(out->CharInfo.name, in->CharInfo.name, 24);
		out->CharInfo.Str = in->CharInfo.Str;
		out->CharInfo.Agi = in->CharInfo.Agi;
		out->CharInfo.Vit = in->CharInfo.Vit;
		out->CharInfo.Int = in->CharInfo.Int;
		out->CharInfo.Dex = in->CharInfo.Dex;
		out->CharInfo.Luk = in->CharInfo.Luk;
		out->CharInfo.CharNum = in->CharInfo.CharNum;
		out->CharInfo.haircolor = in->CharInfo.haircolor;
		out->CharInfo.bIsChangedCharName = in->CharInfo.bIsChangedCharName;
		out->CharInfo.nRobe = 0; // adapt

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_HC_ACCEPT_MAKECHAR> in(p);
		TPacket<PACKET_HC_ACCEPT_MAKECHAR_KRO20061023> out;

		out->PacketType = PacketType;
		out->CharInfo.GID = in->CharInfo.GID;
		out->CharInfo.exp = in->CharInfo.exp;
		out->CharInfo.money = in->CharInfo.money;
		out->CharInfo.jobexp = in->CharInfo.jobexp;
		out->CharInfo.joblevel = in->CharInfo.joblevel;
		out->CharInfo.bodystate = in->CharInfo.bodystate;
		out->CharInfo.healthstate = in->CharInfo.healthstate;
		out->CharInfo.effectstate = in->CharInfo.effectstate;
		out->CharInfo.virtue = in->CharInfo.virtue;
		out->CharInfo.honor = in->CharInfo.honor;
		out->CharInfo.jobpoint = in->CharInfo.jobpoint;
		out->CharInfo.hp = in->CharInfo.hp;
		out->CharInfo.maxhp = in->CharInfo.maxhp;
		out->CharInfo.sp = in->CharInfo.sp;
		out->CharInfo.maxsp = in->CharInfo.maxsp;
		out->CharInfo.speed = in->CharInfo.speed;
		out->CharInfo.job = in->CharInfo.job;
		out->CharInfo.head = in->CharInfo.head;
		out->CharInfo.weapon = in->CharInfo.weapon;
		out->CharInfo.level = in->CharInfo.level;
		out->CharInfo.sppoint = in->CharInfo.sppoint;
		out->CharInfo.accessory = in->CharInfo.accessory;
		out->CharInfo.shield = in->CharInfo.shield;
		out->CharInfo.accessory2 = in->CharInfo.accessory2;
		out->CharInfo.accessory3 = in->CharInfo.accessory3;
		out->CharInfo.headpalette = in->CharInfo.headpalette;
		out->CharInfo.bodypalette = in->CharInfo.bodypalette;
		memcpy(out->CharInfo.name, in->CharInfo.name, 24);
		out->CharInfo.Str = in->CharInfo.Str;
		out->CharInfo.Agi = in->CharInfo.Agi;
		out->CharInfo.Vit = in->CharInfo.Vit;
		out->CharInfo.Int = in->CharInfo.Int;
		out->CharInfo.Dex = in->CharInfo.Dex;
		out->CharInfo.Luk = in->CharInfo.Luk;
		out->CharInfo.CharNum = in->CharInfo.CharNum;
		out->CharInfo.haircolor = in->CharInfo.haircolor;
		out->CharInfo.bIsChangedCharName = in->CharInfo.bIsChangedCharName;
//		out->CharInfo.nRobe = in->CharInfo.nRobe; // adapt

		return out;
	}
};


struct PACKET_HC_ACCEPT_MAKECHAR_KRO20120207
{
	/* this+0 */ short PacketType;
	/* this+2 */ struct CHARACTER_INFO
	             {
	              	/* this+  0 */ unsigned long GID;
	              	/* this+  4 */ int exp;
	              	/* this+  8 */ int money;
	              	/* this+ 12 */ int jobexp;
	              	/* this+ 16 */ int joblevel;
	              	/* this+ 20 */ int bodystate;
	              	/* this+ 24 */ int healthstate;
	              	/* this+ 28 */ int effectstate;
	              	/* this+ 32 */ int virtue;
	              	/* this+ 36 */ int honor;
	              	/* this+ 40 */ short jobpoint;
	              	/* this+ 42 */ int hp;
	              	/* this+ 46 */ int maxhp;
	              	/* this+ 50 */ short sp;
	              	/* this+ 52 */ short maxsp;
	              	/* this+ 54 */ short speed;
	              	/* this+ 56 */ short job;
	              	/* this+ 58 */ short head;
	              	/* this+ 60 */ short weapon;
	              	/* this+ 62 */ short level;
	              	/* this+ 64 */ short sppoint;
	              	/* this+ 66 */ short accessory;
	              	/* this+ 68 */ short shield;
	              	/* this+ 70 */ short accessory2;
	              	/* this+ 72 */ short accessory3;
	              	/* this+ 74 */ short headpalette;
	              	/* this+ 76 */ short bodypalette;
	              	/* this+ 78 */ unsigned char name[24];
	              	/* this+102 */ unsigned char Str;
	              	/* this+103 */ unsigned char Agi;
	              	/* this+104 */ unsigned char Vit;
	              	/* this+105 */ unsigned char Int;
	              	/* this+106 */ unsigned char Dex;
	              	/* this+107 */ unsigned char Luk;
	              	/* this+108 */ unsigned char CharNum;
	              	/* this+109 */ unsigned char haircolor;
	              	/* this+110 */ short bIsChangedCharName;
	                /* this+112 */ char unknown[16]; //TODO
	                /* this+128 */ char unknown2[16]; //TODO
	             }
	             CharInfo;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_HC_ACCEPT_MAKECHAR_KRO20120207> in(p);
		TPacket<PROTO_HC_ACCEPT_MAKECHAR> out;

		out->PacketType = PacketType;
		out->CharInfo.GID = in->CharInfo.GID;
		out->CharInfo.exp = in->CharInfo.exp;
		out->CharInfo.money = in->CharInfo.money;
		out->CharInfo.jobexp = in->CharInfo.jobexp;
		out->CharInfo.joblevel = in->CharInfo.joblevel;
		out->CharInfo.bodystate = in->CharInfo.bodystate;
		out->CharInfo.healthstate = in->CharInfo.healthstate;
		out->CharInfo.effectstate = in->CharInfo.effectstate;
		out->CharInfo.virtue = in->CharInfo.virtue;
		out->CharInfo.honor = in->CharInfo.honor;
		out->CharInfo.jobpoint = in->CharInfo.jobpoint;
		out->CharInfo.hp = in->CharInfo.hp;
		out->CharInfo.maxhp = in->CharInfo.maxhp;
		out->CharInfo.sp = in->CharInfo.sp;
		out->CharInfo.maxsp = in->CharInfo.maxsp;
		out->CharInfo.speed = in->CharInfo.speed;
		out->CharInfo.job = in->CharInfo.job;
		out->CharInfo.head = in->CharInfo.head;
		out->CharInfo.weapon = in->CharInfo.weapon;
		out->CharInfo.level = in->CharInfo.level;
		out->CharInfo.sppoint = in->CharInfo.sppoint;
		out->CharInfo.accessory = in->CharInfo.accessory;
		out->CharInfo.shield = in->CharInfo.shield;
		out->CharInfo.accessory2 = in->CharInfo.accessory2;
		out->CharInfo.accessory3 = in->CharInfo.accessory3;
		out->CharInfo.headpalette = in->CharInfo.headpalette;
		out->CharInfo.bodypalette = in->CharInfo.bodypalette;
		memcpy(out->CharInfo.name, in->CharInfo.name, 24);
		out->CharInfo.Str = in->CharInfo.Str;
		out->CharInfo.Agi = in->CharInfo.Agi;
		out->CharInfo.Vit = in->CharInfo.Vit;
		out->CharInfo.Int = in->CharInfo.Int;
		out->CharInfo.Dex = in->CharInfo.Dex;
		out->CharInfo.Luk = in->CharInfo.Luk;
		out->CharInfo.CharNum = in->CharInfo.CharNum;
		out->CharInfo.haircolor = in->CharInfo.haircolor;
		out->CharInfo.bIsChangedCharName = in->CharInfo.bIsChangedCharName;
		out->CharInfo.nRobe = 0; // adapt

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_HC_ACCEPT_MAKECHAR> in(p);
		TPacket<PACKET_HC_ACCEPT_MAKECHAR_KRO20120207> out;

		out->PacketType = PacketType;
		out->CharInfo.GID = in->CharInfo.GID;
		out->CharInfo.exp = in->CharInfo.exp;
		out->CharInfo.money = in->CharInfo.money;
		out->CharInfo.jobexp = in->CharInfo.jobexp;
		out->CharInfo.joblevel = in->CharInfo.joblevel;
		out->CharInfo.bodystate = in->CharInfo.bodystate;
		out->CharInfo.healthstate = in->CharInfo.healthstate;
		out->CharInfo.effectstate = in->CharInfo.effectstate;
		out->CharInfo.virtue = in->CharInfo.virtue;
		out->CharInfo.honor = in->CharInfo.honor;
		out->CharInfo.jobpoint = in->CharInfo.jobpoint;
		out->CharInfo.hp = in->CharInfo.hp;
		out->CharInfo.maxhp = in->CharInfo.maxhp;
		out->CharInfo.sp = in->CharInfo.sp;
		out->CharInfo.maxsp = in->CharInfo.maxsp;
		out->CharInfo.speed = in->CharInfo.speed;
		out->CharInfo.job = in->CharInfo.job;
		out->CharInfo.head = in->CharInfo.head;
		out->CharInfo.weapon = in->CharInfo.weapon;
		out->CharInfo.level = in->CharInfo.level;
		out->CharInfo.sppoint = in->CharInfo.sppoint;
		out->CharInfo.accessory = in->CharInfo.accessory;
		out->CharInfo.shield = in->CharInfo.shield;
		out->CharInfo.accessory2 = in->CharInfo.accessory2;
		out->CharInfo.accessory3 = in->CharInfo.accessory3;
		out->CharInfo.headpalette = in->CharInfo.headpalette;
		out->CharInfo.bodypalette = in->CharInfo.bodypalette;
		memcpy(out->CharInfo.name, in->CharInfo.name, 24);
		out->CharInfo.Str = in->CharInfo.Str;
		out->CharInfo.Agi = in->CharInfo.Agi;
		out->CharInfo.Vit = in->CharInfo.Vit;
		out->CharInfo.Int = in->CharInfo.Int;
		out->CharInfo.Dex = in->CharInfo.Dex;
		out->CharInfo.Luk = in->CharInfo.Luk;
		out->CharInfo.CharNum = in->CharInfo.CharNum;
		out->CharInfo.haircolor = in->CharInfo.haircolor;
		out->CharInfo.bIsChangedCharName = in->CharInfo.bIsChangedCharName;
		memset(out->CharInfo.unknown, '\0', 16); //FIXME
		memset(out->CharInfo.unknown2, '\0', 16); //FIXME
//		out->CharInfo.nRobe = in->CharInfo.nRobe; // adapt

		return out;
	}
};


struct PACKET_HC_ACCEPT_MAKECHAR_THAI20130312
{
	/* this+0 */ short PacketType;
	/* this+2 */ struct CHARACTER_INFO
	             {
	              	/* this+  0 */ unsigned long GID;
	              	/* this+  4 */ int exp;
	              	/* this+  8 */ int money;
	              	/* this+ 12 */ int jobexp;
	              	/* this+ 16 */ int joblevel;
	              	/* this+ 20 */ int bodystate;
	              	/* this+ 24 */ int healthstate;
	              	/* this+ 28 */ int effectstate;
	              	/* this+ 32 */ int virtue;
	              	/* this+ 36 */ int honor;
	              	/* this+ 40 */ short jobpoint;
	              	/* this+ 42 */ int hp;
	              	/* this+ 46 */ int maxhp;
	              	/* this+ 50 */ short sp;
	              	/* this+ 52 */ short maxsp;
	              	/* this+ 54 */ short speed;
	              	/* this+ 56 */ short job;
	              	/* this+ 58 */ short head;
	              	/* this+ 60 */ short weapon;
	              	/* this+ 62 */ short level;
	              	/* this+ 64 */ short sppoint;
	              	/* this+ 66 */ short accessory;
	              	/* this+ 68 */ short shield;
	              	/* this+ 70 */ short accessory2;
	              	/* this+ 72 */ short accessory3;
	              	/* this+ 74 */ short headpalette;
	              	/* this+ 76 */ short bodypalette;
	              	/* this+ 78 */ unsigned char name[24];
	              	/* this+102 */ unsigned char Str;
	              	/* this+103 */ unsigned char Agi;
	              	/* this+104 */ unsigned char Vit;
	              	/* this+105 */ unsigned char Int;
	              	/* this+106 */ unsigned char Dex;
	              	/* this+107 */ unsigned char Luk;
	              	/* this+108 */ unsigned char CharNum;
	              	/* this+109 */ unsigned char haircolor;
	              	/* this+110 */ short bIsChangedCharName;
	              	/* this+112 */ int nRobe;
	             }
	             CharInfo;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_HC_ACCEPT_MAKECHAR_THAI20130312> in(p);
		TPacket<PROTO_HC_ACCEPT_MAKECHAR> out;

		out->PacketType = PacketType;
		out->CharInfo.GID = in->CharInfo.GID;
		out->CharInfo.exp = in->CharInfo.exp;
		out->CharInfo.money = in->CharInfo.money;
		out->CharInfo.jobexp = in->CharInfo.jobexp;
		out->CharInfo.joblevel = in->CharInfo.joblevel;
		out->CharInfo.bodystate = in->CharInfo.bodystate;
		out->CharInfo.healthstate = in->CharInfo.healthstate;
		out->CharInfo.effectstate = in->CharInfo.effectstate;
		out->CharInfo.virtue = in->CharInfo.virtue;
		out->CharInfo.honor = in->CharInfo.honor;
		out->CharInfo.jobpoint = in->CharInfo.jobpoint;
		out->CharInfo.hp = in->CharInfo.hp;
		out->CharInfo.maxhp = in->CharInfo.maxhp;
		out->CharInfo.sp = in->CharInfo.sp;
		out->CharInfo.maxsp = in->CharInfo.maxsp;
		out->CharInfo.speed = in->CharInfo.speed;
		out->CharInfo.job = in->CharInfo.job;
		out->CharInfo.head = in->CharInfo.head;
		out->CharInfo.weapon = in->CharInfo.weapon;
		out->CharInfo.level = in->CharInfo.level;
		out->CharInfo.sppoint = in->CharInfo.sppoint;
		out->CharInfo.accessory = in->CharInfo.accessory;
		out->CharInfo.shield = in->CharInfo.shield;
		out->CharInfo.accessory2 = in->CharInfo.accessory2;
		out->CharInfo.accessory3 = in->CharInfo.accessory3;
		out->CharInfo.headpalette = in->CharInfo.headpalette;
		out->CharInfo.bodypalette = in->CharInfo.bodypalette;
		memcpy(out->CharInfo.name, in->CharInfo.name, 24);
		out->CharInfo.Str = in->CharInfo.Str;
		out->CharInfo.Agi = in->CharInfo.Agi;
		out->CharInfo.Vit = in->CharInfo.Vit;
		out->CharInfo.Int = in->CharInfo.Int;
		out->CharInfo.Dex = in->CharInfo.Dex;
		out->CharInfo.Luk = in->CharInfo.Luk;
		out->CharInfo.CharNum = in->CharInfo.CharNum;
		out->CharInfo.haircolor = in->CharInfo.haircolor;
		out->CharInfo.bIsChangedCharName = in->CharInfo.bIsChangedCharName;
		out->CharInfo.nRobe = in->CharInfo.nRobe;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_HC_ACCEPT_MAKECHAR> in(p);
		TPacket<PACKET_HC_ACCEPT_MAKECHAR_THAI20130312> out;

		out->PacketType = PacketType;
		out->CharInfo.GID = in->CharInfo.GID;
		out->CharInfo.exp = in->CharInfo.exp;
		out->CharInfo.money = in->CharInfo.money;
		out->CharInfo.jobexp = in->CharInfo.jobexp;
		out->CharInfo.joblevel = in->CharInfo.joblevel;
		out->CharInfo.bodystate = in->CharInfo.bodystate;
		out->CharInfo.healthstate = in->CharInfo.healthstate;
		out->CharInfo.effectstate = in->CharInfo.effectstate;
		out->CharInfo.virtue = in->CharInfo.virtue;
		out->CharInfo.honor = in->CharInfo.honor;
		out->CharInfo.jobpoint = in->CharInfo.jobpoint;
		out->CharInfo.hp = in->CharInfo.hp;
		out->CharInfo.maxhp = in->CharInfo.maxhp;
		out->CharInfo.sp = in->CharInfo.sp;
		out->CharInfo.maxsp = in->CharInfo.maxsp;
		out->CharInfo.speed = in->CharInfo.speed;
		out->CharInfo.job = in->CharInfo.job;
		out->CharInfo.head = in->CharInfo.head;
		out->CharInfo.weapon = in->CharInfo.weapon;
		out->CharInfo.level = in->CharInfo.level;
		out->CharInfo.sppoint = in->CharInfo.sppoint;
		out->CharInfo.accessory = in->CharInfo.accessory;
		out->CharInfo.shield = in->CharInfo.shield;
		out->CharInfo.accessory2 = in->CharInfo.accessory2;
		out->CharInfo.accessory3 = in->CharInfo.accessory3;
		out->CharInfo.headpalette = in->CharInfo.headpalette;
		out->CharInfo.bodypalette = in->CharInfo.bodypalette;
		memcpy(out->CharInfo.name, in->CharInfo.name, 24);
		out->CharInfo.Str = in->CharInfo.Str;
		out->CharInfo.Agi = in->CharInfo.Agi;
		out->CharInfo.Vit = in->CharInfo.Vit;
		out->CharInfo.Int = in->CharInfo.Int;
		out->CharInfo.Dex = in->CharInfo.Dex;
		out->CharInfo.Luk = in->CharInfo.Luk;
		out->CharInfo.CharNum = in->CharInfo.CharNum;
		out->CharInfo.haircolor = in->CharInfo.haircolor;
		out->CharInfo.bIsChangedCharName = in->CharInfo.bIsChangedCharName;
		out->CharInfo.nRobe = in->CharInfo.nRobe;

		return out;
	}
};
