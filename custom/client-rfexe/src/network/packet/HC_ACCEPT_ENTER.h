struct PROTO_HC_ACCEPT_ENTER
{
	short PacketType; // PROTOID_HC_ACCEPT_ENTER
	unsigned short PacketLength;

	unsigned char NormalSlotNum;
	unsigned char PremiumSlotNum;
	unsigned char BillingSlotNum;
	unsigned char ProducibleSlotNum;
	unsigned char ValidSlotNum;

	struct BILLING_INFO
	{
		char dummy1;
		unsigned long code;
		unsigned long time1;
		unsigned long time2;
		char dummy2[7];
	}
	m_extension;

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
	CharInfo[];
};


struct PACKET_HC_ACCEPT_ENTER
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ struct CHARACTER_INFO
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
	             CharInfo[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_HC_ACCEPT_ENTER,PACKET_HC_ACCEPT_ENTER::CHARACTER_INFO> in(p);
		TPacket<PROTO_HC_ACCEPT_ENTER,PROTO_HC_ACCEPT_ENTER::CHARACTER_INFO> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		const int MAX_CHARS = 15; //TODO: determine maximum for each client and server; use appropriate default value
		out->NormalSlotNum = MAX_CHARS; // adapt
		out->PremiumSlotNum = 0; // adapt
		out->BillingSlotNum = 0; // adapt
		out->ProducibleSlotNum = MAX_CHARS; // adapt
		out->ValidSlotNum = MAX_CHARS; // adapt

		memset(&out->m_extension, 0, sizeof(out->m_extension)); // adapt

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->CharInfo[i].GID = in->CharInfo[i].GID;
			out->CharInfo[i].exp = in->CharInfo[i].exp;
			out->CharInfo[i].money = in->CharInfo[i].money;
			out->CharInfo[i].jobexp = in->CharInfo[i].jobexp;
			out->CharInfo[i].joblevel = in->CharInfo[i].joblevel;
			out->CharInfo[i].bodystate = in->CharInfo[i].bodystate;
			out->CharInfo[i].healthstate = in->CharInfo[i].healthstate;
			out->CharInfo[i].effectstate = in->CharInfo[i].effectstate;
			out->CharInfo[i].virtue = in->CharInfo[i].virtue;
			out->CharInfo[i].honor = in->CharInfo[i].honor;
			out->CharInfo[i].jobpoint = in->CharInfo[i].jobpoint;
			out->CharInfo[i].hp = in->CharInfo[i].hp;
			out->CharInfo[i].maxhp = in->CharInfo[i].maxhp;
			out->CharInfo[i].sp = in->CharInfo[i].sp;
			out->CharInfo[i].maxsp = in->CharInfo[i].maxsp;
			out->CharInfo[i].speed = in->CharInfo[i].speed;
			out->CharInfo[i].job = in->CharInfo[i].job;
			out->CharInfo[i].head = in->CharInfo[i].head;
			out->CharInfo[i].weapon = in->CharInfo[i].weapon;
			out->CharInfo[i].level = in->CharInfo[i].level;
			out->CharInfo[i].sppoint = in->CharInfo[i].sppoint;
			out->CharInfo[i].accessory = in->CharInfo[i].accessory;
			out->CharInfo[i].shield = in->CharInfo[i].shield;
			out->CharInfo[i].accessory2 = in->CharInfo[i].accessory2;
			out->CharInfo[i].accessory3 = in->CharInfo[i].accessory3;
			out->CharInfo[i].headpalette = in->CharInfo[i].headpalette;
			out->CharInfo[i].bodypalette = in->CharInfo[i].bodypalette;
			memcpy(out->CharInfo[i].name, in->CharInfo[i].name, 24);
			out->CharInfo[i].Str = in->CharInfo[i].Str;
			out->CharInfo[i].Agi = in->CharInfo[i].Agi;
			out->CharInfo[i].Vit = in->CharInfo[i].Vit;
			out->CharInfo[i].Int = in->CharInfo[i].Int;
			out->CharInfo[i].Dex = in->CharInfo[i].Dex;
			out->CharInfo[i].Luk = in->CharInfo[i].Luk;
			out->CharInfo[i].CharNum = in->CharInfo[i].CharNum;
			out->CharInfo[i].haircolor = in->CharInfo[i].haircolor;
			out->CharInfo[i].bIsChangedCharName = 1; // adapt
			out->CharInfo[i].nRobe = 0; // adapt
		}

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_HC_ACCEPT_ENTER,PROTO_HC_ACCEPT_ENTER::CHARACTER_INFO> in(p);
		TPacket<PACKET_HC_ACCEPT_ENTER,PACKET_HC_ACCEPT_ENTER::CHARACTER_INFO> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->CharInfo[i].GID = in->CharInfo[i].GID;
			out->CharInfo[i].exp = in->CharInfo[i].exp;
			out->CharInfo[i].money = in->CharInfo[i].money;
			out->CharInfo[i].jobexp = in->CharInfo[i].jobexp;
			out->CharInfo[i].joblevel = in->CharInfo[i].joblevel;
			out->CharInfo[i].bodystate = in->CharInfo[i].bodystate;
			out->CharInfo[i].healthstate = in->CharInfo[i].healthstate;
			out->CharInfo[i].effectstate = in->CharInfo[i].effectstate;
			out->CharInfo[i].virtue = in->CharInfo[i].virtue;
			out->CharInfo[i].honor = in->CharInfo[i].honor;
			out->CharInfo[i].jobpoint = in->CharInfo[i].jobpoint;
			out->CharInfo[i].hp = min(in->CharInfo[i].hp, SHRT_MAX); // adapt
			out->CharInfo[i].maxhp = min(in->CharInfo[i].maxhp, SHRT_MAX); // adapt
			out->CharInfo[i].sp = in->CharInfo[i].sp;
			out->CharInfo[i].maxsp = in->CharInfo[i].maxsp;
			out->CharInfo[i].speed = in->CharInfo[i].speed;
			out->CharInfo[i].job = in->CharInfo[i].job;
			out->CharInfo[i].head = in->CharInfo[i].head;
			out->CharInfo[i].weapon = in->CharInfo[i].weapon;
			out->CharInfo[i].level = in->CharInfo[i].level;
			out->CharInfo[i].sppoint = in->CharInfo[i].sppoint;
			out->CharInfo[i].accessory = in->CharInfo[i].accessory;
			out->CharInfo[i].shield = in->CharInfo[i].shield;
			out->CharInfo[i].accessory2 = in->CharInfo[i].accessory2;
			out->CharInfo[i].accessory3 = in->CharInfo[i].accessory3;
			out->CharInfo[i].headpalette = in->CharInfo[i].headpalette;
			out->CharInfo[i].bodypalette = in->CharInfo[i].bodypalette;
			memcpy(out->CharInfo[i].name, in->CharInfo[i].name, 24);
			out->CharInfo[i].Str = in->CharInfo[i].Str;
			out->CharInfo[i].Agi = in->CharInfo[i].Agi;
			out->CharInfo[i].Vit = in->CharInfo[i].Vit;
			out->CharInfo[i].Int = in->CharInfo[i].Int;
			out->CharInfo[i].Dex = in->CharInfo[i].Dex;
			out->CharInfo[i].Luk = in->CharInfo[i].Luk;
			out->CharInfo[i].CharNum = in->CharInfo[i].CharNum;
			out->CharInfo[i].haircolor = in->CharInfo[i].haircolor;
//			out->CharInfo[i].bIsChangedCharName = in->CharInfo[i].bIsChangedCharName; // adapt
//			out->CharInfo[i].nRobe = in->CharInfo[i].nRobe; // adapt
		}

		return out;
	}
};


//TODO: determine/confirm real origin date
struct PACKET_HC_ACCEPT_ENTER_KRO20100413
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short PacketLength;
	/* this+ 4 */ unsigned char TotalSlotNum;
	/* this+ 5 */ unsigned char PremiumStartSlot;
	/* this+ 6 */ unsigned char PremiumEndSlot;
	/* this+ 7 */ struct BILLING_INFO
	              {
	              	/* this+ 0 */ char dummy1;
	              	/* this+ 1 */ unsigned long code;
	              	/* this+ 5 */ unsigned long time1;
	              	/* this+ 9 */ unsigned long time2;
	              	/* this+13 */ char dummy2[7];
	              }
	              m_extension;
	/* this+27 */ struct CHARACTER_INFO
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
	              CharInfo[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_HC_ACCEPT_ENTER_KRO20100413,PACKET_HC_ACCEPT_ENTER_KRO20100413::CHARACTER_INFO> in(p);
		TPacket<PROTO_HC_ACCEPT_ENTER,PROTO_HC_ACCEPT_ENTER::CHARACTER_INFO> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		out->NormalSlotNum = in->PremiumStartSlot; // adapt
		out->PremiumSlotNum = ( in->PremiumStartSlot < in->TotalSlotNum ) ? in->PremiumEndSlot - in->PremiumStartSlot + 1 : 0; // adapt
		out->BillingSlotNum = 0; // adapt
		out->ProducibleSlotNum = in->TotalSlotNum; // adapt
		out->ValidSlotNum = in->TotalSlotNum; // adapt

		memcpy(&out->m_extension, &in->m_extension, sizeof(out->m_extension));

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->CharInfo[i].GID = in->CharInfo[i].GID;
			out->CharInfo[i].exp = in->CharInfo[i].exp;
			out->CharInfo[i].money = in->CharInfo[i].money;
			out->CharInfo[i].jobexp = in->CharInfo[i].jobexp;
			out->CharInfo[i].joblevel = in->CharInfo[i].joblevel;
			out->CharInfo[i].bodystate = in->CharInfo[i].bodystate;
			out->CharInfo[i].healthstate = in->CharInfo[i].healthstate;
			out->CharInfo[i].effectstate = in->CharInfo[i].effectstate;
			out->CharInfo[i].virtue = in->CharInfo[i].virtue;
			out->CharInfo[i].honor = in->CharInfo[i].honor;
			out->CharInfo[i].jobpoint = in->CharInfo[i].jobpoint;
			out->CharInfo[i].hp = in->CharInfo[i].hp;
			out->CharInfo[i].maxhp = in->CharInfo[i].maxhp;
			out->CharInfo[i].sp = in->CharInfo[i].sp;
			out->CharInfo[i].maxsp = in->CharInfo[i].maxsp;
			out->CharInfo[i].speed = in->CharInfo[i].speed;
			out->CharInfo[i].job = in->CharInfo[i].job;
			out->CharInfo[i].head = in->CharInfo[i].head;
			out->CharInfo[i].weapon = in->CharInfo[i].weapon;
			out->CharInfo[i].level = in->CharInfo[i].level;
			out->CharInfo[i].sppoint = in->CharInfo[i].sppoint;
			out->CharInfo[i].accessory = in->CharInfo[i].accessory;
			out->CharInfo[i].shield = in->CharInfo[i].shield;
			out->CharInfo[i].accessory2 = in->CharInfo[i].accessory2;
			out->CharInfo[i].accessory3 = in->CharInfo[i].accessory3;
			out->CharInfo[i].headpalette = in->CharInfo[i].headpalette;
			out->CharInfo[i].bodypalette = in->CharInfo[i].bodypalette;
			memcpy(out->CharInfo[i].name, in->CharInfo[i].name, 24);
			out->CharInfo[i].Str = in->CharInfo[i].Str;
			out->CharInfo[i].Agi = in->CharInfo[i].Agi;
			out->CharInfo[i].Vit = in->CharInfo[i].Vit;
			out->CharInfo[i].Int = in->CharInfo[i].Int;
			out->CharInfo[i].Dex = in->CharInfo[i].Dex;
			out->CharInfo[i].Luk = in->CharInfo[i].Luk;
			out->CharInfo[i].CharNum = in->CharInfo[i].CharNum;
			out->CharInfo[i].haircolor = in->CharInfo[i].haircolor;
			out->CharInfo[i].bIsChangedCharName = in->CharInfo[i].bIsChangedCharName;
			out->CharInfo[i].nRobe = 0; // adapt
		}

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_HC_ACCEPT_ENTER,PROTO_HC_ACCEPT_ENTER::CHARACTER_INFO> in(p);
		TPacket<PACKET_HC_ACCEPT_ENTER_KRO20100413,PACKET_HC_ACCEPT_ENTER_KRO20100413::CHARACTER_INFO> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		out->TotalSlotNum = in->ValidSlotNum; // adapt
		out->PremiumStartSlot = in->NormalSlotNum; // adapt
		out->PremiumEndSlot = in->NormalSlotNum + (( in->PremiumSlotNum + in->BillingSlotNum != 0 ) ? in->PremiumSlotNum + in->BillingSlotNum - 1 : 0); // adapt

		memcpy(&out->m_extension, &in->m_extension, sizeof(out->m_extension));

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->CharInfo[i].GID = in->CharInfo[i].GID;
			out->CharInfo[i].exp = in->CharInfo[i].exp;
			out->CharInfo[i].money = in->CharInfo[i].money;
			out->CharInfo[i].jobexp = in->CharInfo[i].jobexp;
			out->CharInfo[i].joblevel = in->CharInfo[i].joblevel;
			out->CharInfo[i].bodystate = in->CharInfo[i].bodystate;
			out->CharInfo[i].healthstate = in->CharInfo[i].healthstate;
			out->CharInfo[i].effectstate = in->CharInfo[i].effectstate;
			out->CharInfo[i].virtue = in->CharInfo[i].virtue;
			out->CharInfo[i].honor = in->CharInfo[i].honor;
			out->CharInfo[i].jobpoint = in->CharInfo[i].jobpoint;
			out->CharInfo[i].hp = in->CharInfo[i].hp;
			out->CharInfo[i].maxhp = in->CharInfo[i].maxhp;
			out->CharInfo[i].sp = in->CharInfo[i].sp;
			out->CharInfo[i].maxsp = in->CharInfo[i].maxsp;
			out->CharInfo[i].speed = in->CharInfo[i].speed;
			out->CharInfo[i].job = in->CharInfo[i].job;
			out->CharInfo[i].head = in->CharInfo[i].head;
			out->CharInfo[i].weapon = in->CharInfo[i].weapon;
			out->CharInfo[i].level = in->CharInfo[i].level;
			out->CharInfo[i].sppoint = in->CharInfo[i].sppoint;
			out->CharInfo[i].accessory = in->CharInfo[i].accessory;
			out->CharInfo[i].shield = in->CharInfo[i].shield;
			out->CharInfo[i].accessory2 = in->CharInfo[i].accessory2;
			out->CharInfo[i].accessory3 = in->CharInfo[i].accessory3;
			out->CharInfo[i].headpalette = in->CharInfo[i].headpalette;
			out->CharInfo[i].bodypalette = in->CharInfo[i].bodypalette;
			memcpy(out->CharInfo[i].name, in->CharInfo[i].name, 24);
			out->CharInfo[i].Str = in->CharInfo[i].Str;
			out->CharInfo[i].Agi = in->CharInfo[i].Agi;
			out->CharInfo[i].Vit = in->CharInfo[i].Vit;
			out->CharInfo[i].Int = in->CharInfo[i].Int;
			out->CharInfo[i].Dex = in->CharInfo[i].Dex;
			out->CharInfo[i].Luk = in->CharInfo[i].Luk;
			out->CharInfo[i].CharNum = in->CharInfo[i].CharNum;
			out->CharInfo[i].haircolor = in->CharInfo[i].haircolor;
			out->CharInfo[i].bIsChangedCharName = in->CharInfo[i].bIsChangedCharName;
//			out->CharInfo[i].nRobe = in->CharInfo[i].nRobe; // adapt
		}

		return out;
	}
};


//TODO: determine/confirm real origin date
struct PACKET_HC_ACCEPT_ENTER_KRO20120207
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short PacketLength;
	/* this+ 4 */ unsigned char TotalSlotNum;
	/* this+ 5 */ unsigned char PremiumStartSlot;
	/* this+ 6 */ unsigned char PremiumEndSlot;
	/* this+ 7 */ struct BILLING_INFO
	              {
	              	/* this+ 0 */ char dummy1;
	              	/* this+ 1 */ unsigned long code;
	              	/* this+ 5 */ unsigned long time1;
	              	/* this+ 9 */ unsigned long time2;
	              	/* this+13 */ char dummy2[7];
	              }
	              m_extension;
	/* this+27 */ struct CHARACTER_INFO
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
	              CharInfo[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_HC_ACCEPT_ENTER_KRO20120207,PACKET_HC_ACCEPT_ENTER_KRO20120207::CHARACTER_INFO> in(p);
		TPacket<PROTO_HC_ACCEPT_ENTER,PROTO_HC_ACCEPT_ENTER::CHARACTER_INFO> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		out->NormalSlotNum = in->PremiumStartSlot; // adapt
		out->PremiumSlotNum = ( in->PremiumStartSlot < in->TotalSlotNum ) ? in->PremiumEndSlot - in->PremiumStartSlot + 1 : 0; // adapt
		out->BillingSlotNum = 0; // adapt
		out->ProducibleSlotNum = in->TotalSlotNum; // adapt
		out->ValidSlotNum = in->TotalSlotNum; // adapt

		memcpy(&out->m_extension, &in->m_extension, sizeof(out->m_extension));

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->CharInfo[i].GID = in->CharInfo[i].GID;
			out->CharInfo[i].exp = in->CharInfo[i].exp;
			out->CharInfo[i].money = in->CharInfo[i].money;
			out->CharInfo[i].jobexp = in->CharInfo[i].jobexp;
			out->CharInfo[i].joblevel = in->CharInfo[i].joblevel;
			out->CharInfo[i].bodystate = in->CharInfo[i].bodystate;
			out->CharInfo[i].healthstate = in->CharInfo[i].healthstate;
			out->CharInfo[i].effectstate = in->CharInfo[i].effectstate;
			out->CharInfo[i].virtue = in->CharInfo[i].virtue;
			out->CharInfo[i].honor = in->CharInfo[i].honor;
			out->CharInfo[i].jobpoint = in->CharInfo[i].jobpoint;
			out->CharInfo[i].hp = in->CharInfo[i].hp;
			out->CharInfo[i].maxhp = in->CharInfo[i].maxhp;
			out->CharInfo[i].sp = in->CharInfo[i].sp;
			out->CharInfo[i].maxsp = in->CharInfo[i].maxsp;
			out->CharInfo[i].speed = in->CharInfo[i].speed;
			out->CharInfo[i].job = in->CharInfo[i].job;
			out->CharInfo[i].head = in->CharInfo[i].head;
			out->CharInfo[i].weapon = in->CharInfo[i].weapon;
			out->CharInfo[i].level = in->CharInfo[i].level;
			out->CharInfo[i].sppoint = in->CharInfo[i].sppoint;
			out->CharInfo[i].accessory = in->CharInfo[i].accessory;
			out->CharInfo[i].shield = in->CharInfo[i].shield;
			out->CharInfo[i].accessory2 = in->CharInfo[i].accessory2;
			out->CharInfo[i].accessory3 = in->CharInfo[i].accessory3;
			out->CharInfo[i].headpalette = in->CharInfo[i].headpalette;
			out->CharInfo[i].bodypalette = in->CharInfo[i].bodypalette;
			memcpy(out->CharInfo[i].name, in->CharInfo[i].name, 24);
			out->CharInfo[i].Str = in->CharInfo[i].Str;
			out->CharInfo[i].Agi = in->CharInfo[i].Agi;
			out->CharInfo[i].Vit = in->CharInfo[i].Vit;
			out->CharInfo[i].Int = in->CharInfo[i].Int;
			out->CharInfo[i].Dex = in->CharInfo[i].Dex;
			out->CharInfo[i].Luk = in->CharInfo[i].Luk;
			out->CharInfo[i].CharNum = in->CharInfo[i].CharNum;
			out->CharInfo[i].haircolor = in->CharInfo[i].haircolor;
			out->CharInfo[i].bIsChangedCharName = in->CharInfo[i].bIsChangedCharName;
			out->CharInfo[i].nRobe = 0; // adapt
		}

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_HC_ACCEPT_ENTER,PROTO_HC_ACCEPT_ENTER::CHARACTER_INFO> in(p);
		TPacket<PACKET_HC_ACCEPT_ENTER_KRO20120207,PACKET_HC_ACCEPT_ENTER_KRO20120207::CHARACTER_INFO> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		out->TotalSlotNum = in->ValidSlotNum; // adapt
		out->PremiumStartSlot = in->NormalSlotNum; // adapt
		out->PremiumEndSlot = in->NormalSlotNum + (( in->PremiumSlotNum + in->BillingSlotNum != 0 ) ? in->PremiumSlotNum + in->BillingSlotNum - 1 : 0); // adapt

		memcpy(&out->m_extension, &in->m_extension, sizeof(out->m_extension));

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->CharInfo[i].GID = in->CharInfo[i].GID;
			out->CharInfo[i].exp = in->CharInfo[i].exp;
			out->CharInfo[i].money = in->CharInfo[i].money;
			out->CharInfo[i].jobexp = in->CharInfo[i].jobexp;
			out->CharInfo[i].joblevel = in->CharInfo[i].joblevel;
			out->CharInfo[i].bodystate = in->CharInfo[i].bodystate;
			out->CharInfo[i].healthstate = in->CharInfo[i].healthstate;
			out->CharInfo[i].effectstate = in->CharInfo[i].effectstate;
			out->CharInfo[i].virtue = in->CharInfo[i].virtue;
			out->CharInfo[i].honor = in->CharInfo[i].honor;
			out->CharInfo[i].jobpoint = in->CharInfo[i].jobpoint;
			out->CharInfo[i].hp = in->CharInfo[i].hp;
			out->CharInfo[i].maxhp = in->CharInfo[i].maxhp;
			out->CharInfo[i].sp = in->CharInfo[i].sp;
			out->CharInfo[i].maxsp = in->CharInfo[i].maxsp;
			out->CharInfo[i].speed = in->CharInfo[i].speed;
			out->CharInfo[i].job = in->CharInfo[i].job;
			out->CharInfo[i].head = in->CharInfo[i].head;
			out->CharInfo[i].weapon = in->CharInfo[i].weapon;
			out->CharInfo[i].level = in->CharInfo[i].level;
			out->CharInfo[i].sppoint = in->CharInfo[i].sppoint;
			out->CharInfo[i].accessory = in->CharInfo[i].accessory;
			out->CharInfo[i].shield = in->CharInfo[i].shield;
			out->CharInfo[i].accessory2 = in->CharInfo[i].accessory2;
			out->CharInfo[i].accessory3 = in->CharInfo[i].accessory3;
			out->CharInfo[i].headpalette = in->CharInfo[i].headpalette;
			out->CharInfo[i].bodypalette = in->CharInfo[i].bodypalette;
			memcpy(out->CharInfo[i].name, in->CharInfo[i].name, 24);
			out->CharInfo[i].Str = in->CharInfo[i].Str;
			out->CharInfo[i].Agi = in->CharInfo[i].Agi;
			out->CharInfo[i].Vit = in->CharInfo[i].Vit;
			out->CharInfo[i].Int = in->CharInfo[i].Int;
			out->CharInfo[i].Dex = in->CharInfo[i].Dex;
			out->CharInfo[i].Luk = in->CharInfo[i].Luk;
			out->CharInfo[i].CharNum = in->CharInfo[i].CharNum;
			out->CharInfo[i].haircolor = in->CharInfo[i].haircolor;
			out->CharInfo[i].bIsChangedCharName = in->CharInfo[i].bIsChangedCharName;
			memset(out->CharInfo[i].unknown, '\0', 16); //FIXME
			memset(out->CharInfo[i].unknown2, '\0', 16); //FIXME
//			out->CharInfo[i].nRobe = in->CharInfo[i].nRobe; // adapt
		}

		return out;
	}
};


struct PACKET_HC_ACCEPT_ENTER_THAI20130312
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short PacketLength;
	/* this+ 4 */ unsigned char TotalSlotNum;
	/* this+ 5 */ unsigned char PremiumStartSlot;
	/* this+ 6 */ unsigned char PremiumEndSlot;
	/* this+ 7 */ struct CHARACTER_INFO
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
	              CharInfo[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_HC_ACCEPT_ENTER_THAI20130312,PACKET_HC_ACCEPT_ENTER_THAI20130312::CHARACTER_INFO> in(p);
		TPacket<PROTO_HC_ACCEPT_ENTER,PROTO_HC_ACCEPT_ENTER::CHARACTER_INFO> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		out->NormalSlotNum = in->PremiumStartSlot; // adapt
		out->PremiumSlotNum = ( in->PremiumStartSlot < in->TotalSlotNum ) ? in->PremiumEndSlot - in->PremiumStartSlot + 1 : 0; // adapt
		out->BillingSlotNum = 0; // adapt
		out->ProducibleSlotNum = in->TotalSlotNum; // adapt
		out->ValidSlotNum = in->TotalSlotNum; // adapt

		memset(&out->m_extension, 0, sizeof(out->m_extension)); // adapt

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->CharInfo[i].GID = in->CharInfo[i].GID;
			out->CharInfo[i].exp = in->CharInfo[i].exp;
			out->CharInfo[i].money = in->CharInfo[i].money;
			out->CharInfo[i].jobexp = in->CharInfo[i].jobexp;
			out->CharInfo[i].joblevel = in->CharInfo[i].joblevel;
			out->CharInfo[i].bodystate = in->CharInfo[i].bodystate;
			out->CharInfo[i].healthstate = in->CharInfo[i].healthstate;
			out->CharInfo[i].effectstate = in->CharInfo[i].effectstate;
			out->CharInfo[i].virtue = in->CharInfo[i].virtue;
			out->CharInfo[i].honor = in->CharInfo[i].honor;
			out->CharInfo[i].jobpoint = in->CharInfo[i].jobpoint;
			out->CharInfo[i].hp = in->CharInfo[i].hp;
			out->CharInfo[i].maxhp = in->CharInfo[i].maxhp;
			out->CharInfo[i].sp = in->CharInfo[i].sp;
			out->CharInfo[i].maxsp = in->CharInfo[i].maxsp;
			out->CharInfo[i].speed = in->CharInfo[i].speed;
			out->CharInfo[i].job = in->CharInfo[i].job;
			out->CharInfo[i].head = in->CharInfo[i].head;
			out->CharInfo[i].weapon = in->CharInfo[i].weapon;
			out->CharInfo[i].level = in->CharInfo[i].level;
			out->CharInfo[i].sppoint = in->CharInfo[i].sppoint;
			out->CharInfo[i].accessory = in->CharInfo[i].accessory;
			out->CharInfo[i].shield = in->CharInfo[i].shield;
			out->CharInfo[i].accessory2 = in->CharInfo[i].accessory2;
			out->CharInfo[i].accessory3 = in->CharInfo[i].accessory3;
			out->CharInfo[i].headpalette = in->CharInfo[i].headpalette;
			out->CharInfo[i].bodypalette = in->CharInfo[i].bodypalette;
			memcpy(out->CharInfo[i].name, in->CharInfo[i].name, 24);
			out->CharInfo[i].Str = in->CharInfo[i].Str;
			out->CharInfo[i].Agi = in->CharInfo[i].Agi;
			out->CharInfo[i].Vit = in->CharInfo[i].Vit;
			out->CharInfo[i].Int = in->CharInfo[i].Int;
			out->CharInfo[i].Dex = in->CharInfo[i].Dex;
			out->CharInfo[i].Luk = in->CharInfo[i].Luk;
			out->CharInfo[i].CharNum = in->CharInfo[i].CharNum;
			out->CharInfo[i].haircolor = in->CharInfo[i].haircolor;
			out->CharInfo[i].bIsChangedCharName = in->CharInfo[i].bIsChangedCharName;
			out->CharInfo[i].nRobe = in->CharInfo[i].nRobe;
		}

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_HC_ACCEPT_ENTER,PROTO_HC_ACCEPT_ENTER::CHARACTER_INFO> in(p);
		TPacket<PACKET_HC_ACCEPT_ENTER_THAI20130312,PACKET_HC_ACCEPT_ENTER_THAI20130312::CHARACTER_INFO> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		out->TotalSlotNum = in->ValidSlotNum; // adapt
		out->PremiumStartSlot = in->NormalSlotNum; // adapt
		out->PremiumEndSlot = in->NormalSlotNum + (( in->PremiumSlotNum + in->BillingSlotNum != 0 ) ? in->PremiumSlotNum + in->BillingSlotNum - 1 : 0); // adapt

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->CharInfo[i].GID = in->CharInfo[i].GID;
			out->CharInfo[i].exp = in->CharInfo[i].exp;
			out->CharInfo[i].money = in->CharInfo[i].money;
			out->CharInfo[i].jobexp = in->CharInfo[i].jobexp;
			out->CharInfo[i].joblevel = in->CharInfo[i].joblevel;
			out->CharInfo[i].bodystate = in->CharInfo[i].bodystate;
			out->CharInfo[i].healthstate = in->CharInfo[i].healthstate;
			out->CharInfo[i].effectstate = in->CharInfo[i].effectstate;
			out->CharInfo[i].virtue = in->CharInfo[i].virtue;
			out->CharInfo[i].honor = in->CharInfo[i].honor;
			out->CharInfo[i].jobpoint = in->CharInfo[i].jobpoint;
			out->CharInfo[i].hp = in->CharInfo[i].hp;
			out->CharInfo[i].maxhp = in->CharInfo[i].maxhp;
			out->CharInfo[i].sp = in->CharInfo[i].sp;
			out->CharInfo[i].maxsp = in->CharInfo[i].maxsp;
			out->CharInfo[i].speed = in->CharInfo[i].speed;
			out->CharInfo[i].job = in->CharInfo[i].job;
			out->CharInfo[i].head = in->CharInfo[i].head;
			out->CharInfo[i].weapon = in->CharInfo[i].weapon;
			out->CharInfo[i].level = in->CharInfo[i].level;
			out->CharInfo[i].sppoint = in->CharInfo[i].sppoint;
			out->CharInfo[i].accessory = in->CharInfo[i].accessory;
			out->CharInfo[i].shield = in->CharInfo[i].shield;
			out->CharInfo[i].accessory2 = in->CharInfo[i].accessory2;
			out->CharInfo[i].accessory3 = in->CharInfo[i].accessory3;
			out->CharInfo[i].headpalette = in->CharInfo[i].headpalette;
			out->CharInfo[i].bodypalette = in->CharInfo[i].bodypalette;
			memcpy(out->CharInfo[i].name, in->CharInfo[i].name, 24);
			out->CharInfo[i].Str = in->CharInfo[i].Str;
			out->CharInfo[i].Agi = in->CharInfo[i].Agi;
			out->CharInfo[i].Vit = in->CharInfo[i].Vit;
			out->CharInfo[i].Int = in->CharInfo[i].Int;
			out->CharInfo[i].Dex = in->CharInfo[i].Dex;
			out->CharInfo[i].Luk = in->CharInfo[i].Luk;
			out->CharInfo[i].CharNum = in->CharInfo[i].CharNum;
			out->CharInfo[i].haircolor = in->CharInfo[i].haircolor;
			out->CharInfo[i].bIsChangedCharName = in->CharInfo[i].bIsChangedCharName;
			out->CharInfo[i].nRobe = in->CharInfo[i].nRobe;
		}

		return out;
	}
};


struct PACKET_HC_ACCEPT_ENTER2
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short PacketLength;
	/* this+ 4 */ unsigned char NormalSlotNum;
	/* this+ 5 */ unsigned char PremiumSlotNum;
	/* this+ 6 */ unsigned char BillingSlotNum;
	/* this+ 7 */ unsigned char ProducibleSlotNum;
	/* this+ 8 */ unsigned char ValidSlotNum;
	/* this+ 9 */ struct BILLING_INFO
	              {
	              	/* this+ 0 */ char dummy1;
	              	/* this+ 1 */ unsigned long code;
	              	/* this+ 5 */ unsigned long time1;
	              	/* this+ 9 */ unsigned long time2;
	              	/* this+13 */ char dummy2[7];
	              }
	              m_extension;
	/* this+29 */ struct CHARACTER_INFO
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
	              CharInfo[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_HC_ACCEPT_ENTER2,PACKET_HC_ACCEPT_ENTER2::CHARACTER_INFO> in(p);
		TPacket<PROTO_HC_ACCEPT_ENTER,PROTO_HC_ACCEPT_ENTER::CHARACTER_INFO> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		out->NormalSlotNum = in->NormalSlotNum;
		out->PremiumSlotNum = in->PremiumSlotNum;
		out->BillingSlotNum = in->BillingSlotNum;
		out->ProducibleSlotNum = in->ProducibleSlotNum;
		out->ValidSlotNum = in->ValidSlotNum;

		memcpy(&out->m_extension, &in->m_extension, sizeof(out->m_extension));

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->CharInfo[i].GID = in->CharInfo[i].GID;
			out->CharInfo[i].exp = in->CharInfo[i].exp;
			out->CharInfo[i].money = in->CharInfo[i].money;
			out->CharInfo[i].jobexp = in->CharInfo[i].jobexp;
			out->CharInfo[i].joblevel = in->CharInfo[i].joblevel;
			out->CharInfo[i].bodystate = in->CharInfo[i].bodystate;
			out->CharInfo[i].healthstate = in->CharInfo[i].healthstate;
			out->CharInfo[i].effectstate = in->CharInfo[i].effectstate;
			out->CharInfo[i].virtue = in->CharInfo[i].virtue;
			out->CharInfo[i].honor = in->CharInfo[i].honor;
			out->CharInfo[i].jobpoint = in->CharInfo[i].jobpoint;
			out->CharInfo[i].hp = in->CharInfo[i].hp;
			out->CharInfo[i].maxhp = in->CharInfo[i].maxhp;
			out->CharInfo[i].sp = in->CharInfo[i].sp;
			out->CharInfo[i].maxsp = in->CharInfo[i].maxsp;
			out->CharInfo[i].speed = in->CharInfo[i].speed;
			out->CharInfo[i].job = in->CharInfo[i].job;
			out->CharInfo[i].head = in->CharInfo[i].head;
			out->CharInfo[i].weapon = in->CharInfo[i].weapon;
			out->CharInfo[i].level = in->CharInfo[i].level;
			out->CharInfo[i].sppoint = in->CharInfo[i].sppoint;
			out->CharInfo[i].accessory = in->CharInfo[i].accessory;
			out->CharInfo[i].shield = in->CharInfo[i].shield;
			out->CharInfo[i].accessory2 = in->CharInfo[i].accessory2;
			out->CharInfo[i].accessory3 = in->CharInfo[i].accessory3;
			out->CharInfo[i].headpalette = in->CharInfo[i].headpalette;
			out->CharInfo[i].bodypalette = in->CharInfo[i].bodypalette;
			memcpy(out->CharInfo[i].name, in->CharInfo[i].name, 24);
			out->CharInfo[i].Str = in->CharInfo[i].Str;
			out->CharInfo[i].Agi = in->CharInfo[i].Agi;
			out->CharInfo[i].Vit = in->CharInfo[i].Vit;
			out->CharInfo[i].Int = in->CharInfo[i].Int;
			out->CharInfo[i].Dex = in->CharInfo[i].Dex;
			out->CharInfo[i].Luk = in->CharInfo[i].Luk;
			out->CharInfo[i].CharNum = in->CharInfo[i].CharNum;
			out->CharInfo[i].haircolor = in->CharInfo[i].haircolor;
			out->CharInfo[i].bIsChangedCharName = in->CharInfo[i].bIsChangedCharName;
			out->CharInfo[i].nRobe = in->CharInfo[i].nRobe;
		}

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_HC_ACCEPT_ENTER,PROTO_HC_ACCEPT_ENTER::CHARACTER_INFO> in(p);
		TPacket<PACKET_HC_ACCEPT_ENTER2,PACKET_HC_ACCEPT_ENTER2::CHARACTER_INFO> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		out->NormalSlotNum = in->NormalSlotNum;
		out->PremiumSlotNum = in->PremiumSlotNum;
		out->BillingSlotNum = in->BillingSlotNum;
		out->ProducibleSlotNum = in->ProducibleSlotNum;
		out->ValidSlotNum = in->ValidSlotNum;

		memcpy(&out->m_extension, &in->m_extension, sizeof(out->m_extension));

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->CharInfo[i].GID = in->CharInfo[i].GID;
			out->CharInfo[i].exp = in->CharInfo[i].exp;
			out->CharInfo[i].money = in->CharInfo[i].money;
			out->CharInfo[i].jobexp = in->CharInfo[i].jobexp;
			out->CharInfo[i].joblevel = in->CharInfo[i].joblevel;
			out->CharInfo[i].bodystate = in->CharInfo[i].bodystate;
			out->CharInfo[i].healthstate = in->CharInfo[i].healthstate;
			out->CharInfo[i].effectstate = in->CharInfo[i].effectstate;
			out->CharInfo[i].virtue = in->CharInfo[i].virtue;
			out->CharInfo[i].honor = in->CharInfo[i].honor;
			out->CharInfo[i].jobpoint = in->CharInfo[i].jobpoint;
			out->CharInfo[i].hp = in->CharInfo[i].hp;
			out->CharInfo[i].maxhp = in->CharInfo[i].maxhp;
			out->CharInfo[i].sp = in->CharInfo[i].sp;
			out->CharInfo[i].maxsp = in->CharInfo[i].maxsp;
			out->CharInfo[i].speed = in->CharInfo[i].speed;
			out->CharInfo[i].job = in->CharInfo[i].job;
			out->CharInfo[i].head = in->CharInfo[i].head;
			out->CharInfo[i].weapon = in->CharInfo[i].weapon;
			out->CharInfo[i].level = in->CharInfo[i].level;
			out->CharInfo[i].sppoint = in->CharInfo[i].sppoint;
			out->CharInfo[i].accessory = in->CharInfo[i].accessory;
			out->CharInfo[i].shield = in->CharInfo[i].shield;
			out->CharInfo[i].accessory2 = in->CharInfo[i].accessory2;
			out->CharInfo[i].accessory3 = in->CharInfo[i].accessory3;
			out->CharInfo[i].headpalette = in->CharInfo[i].headpalette;
			out->CharInfo[i].bodypalette = in->CharInfo[i].bodypalette;
			memcpy(out->CharInfo[i].name, in->CharInfo[i].name, 24);
			out->CharInfo[i].Str = in->CharInfo[i].Str;
			out->CharInfo[i].Agi = in->CharInfo[i].Agi;
			out->CharInfo[i].Vit = in->CharInfo[i].Vit;
			out->CharInfo[i].Int = in->CharInfo[i].Int;
			out->CharInfo[i].Dex = in->CharInfo[i].Dex;
			out->CharInfo[i].Luk = in->CharInfo[i].Luk;
			out->CharInfo[i].CharNum = in->CharInfo[i].CharNum;
			out->CharInfo[i].haircolor = in->CharInfo[i].haircolor;
			out->CharInfo[i].bIsChangedCharName = in->CharInfo[i].bIsChangedCharName;
			out->CharInfo[i].nRobe = in->CharInfo[i].nRobe;
		}

		return out;
	}
};
