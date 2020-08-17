struct PROTO_ZC_STATUS
{
	short PacketType;
	short point;
	unsigned char str;
	unsigned char standardStr;
	unsigned char agi;
	unsigned char standardAgi;
	unsigned char vit;
	unsigned char standardVit;
	unsigned char Int;
	unsigned char standardInt;
	unsigned char dex;
	unsigned char standardDex;
	unsigned char luk;
	unsigned char standardLuk;
	short attPower;
	short refiningPower;
	short max_mattPower;
	short min_mattPower;
	short itemdefPower;
	short plusdefPower;
	short mdefPower;
	short plusmdefPower;
	short hitSuccessValue;
	short avoidSuccessValue;
	short plusAvoidSuccessValue;
	short criticalSuccessValue;
	short ASPD;
	short plusASPD;
};


struct PACKET_ZC_STATUS
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short point;
	/* this+ 4 */ unsigned char str;
	/* this+ 5 */ unsigned char standardStr;
	/* this+ 6 */ unsigned char agi;
	/* this+ 7 */ unsigned char standardAgi;
	/* this+ 8 */ unsigned char vit;
	/* this+ 9 */ unsigned char standardVit;
	/* this+10 */ unsigned char Int;
	/* this+11 */ unsigned char standardInt;
	/* this+12 */ unsigned char dex;
	/* this+13 */ unsigned char standardDex;
	/* this+14 */ unsigned char luk;
	/* this+15 */ unsigned char standardLuk;
	/* this+16 */ short attPower;
	/* this+18 */ short refiningPower;
	/* this+20 */ short max_mattPower;
	/* this+22 */ short min_mattPower;
	/* this+24 */ short itemdefPower;
	/* this+26 */ short plusdefPower;
	/* this+28 */ short mdefPower;
	/* this+30 */ short plusmdefPower;
	/* this+32 */ short hitSuccessValue;
	/* this+34 */ short avoidSuccessValue;
	/* this+36 */ short plusAvoidSuccessValue;
	/* this+38 */ short criticalSuccessValue;
	/* this+40 */ short ASPD;
	/* this+42 */ short plusASPD;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_STATUS> in(p);
		TPacket<PROTO_ZC_STATUS> out;

		out->PacketType = PacketType;
		out->point                 = in->point;
		out->str                   = in->str;
		out->standardStr           = in->standardStr;
		out->agi                   = in->agi;
		out->standardAgi           = in->standardAgi;
		out->vit                   = in->vit;
		out->standardVit           = in->standardVit;
		out->Int                   = in->Int;
		out->standardInt           = in->standardInt;
		out->dex                   = in->dex;
		out->standardDex           = in->standardDex;
		out->luk                   = in->luk;
		out->standardLuk           = in->standardLuk;
		out->attPower              = in->attPower;
		out->refiningPower         = in->refiningPower;
		out->max_mattPower         = in->max_mattPower;
		out->min_mattPower         = in->min_mattPower;
		out->itemdefPower          = in->itemdefPower;
		out->plusdefPower          = in->plusdefPower;
		out->mdefPower             = in->mdefPower;
		out->plusmdefPower         = in->plusmdefPower;
		out->hitSuccessValue       = in->hitSuccessValue;
		out->avoidSuccessValue     = in->avoidSuccessValue;
		out->plusAvoidSuccessValue = in->plusAvoidSuccessValue;
		out->criticalSuccessValue  = in->criticalSuccessValue;
		out->ASPD                  = in->ASPD;
		out->plusASPD              = in->plusASPD;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_STATUS> in(p);
		TPacket<PACKET_ZC_STATUS> out;

		out->PacketType = PacketType;
		out->point                 = in->point;
		out->str                   = in->str;
		out->standardStr           = in->standardStr;
		out->agi                   = in->agi;
		out->standardAgi           = in->standardAgi;
		out->vit                   = in->vit;
		out->standardVit           = in->standardVit;
		out->Int                   = in->Int;
		out->standardInt           = in->standardInt;
		out->dex                   = in->dex;
		out->standardDex           = in->standardDex;
		out->luk                   = in->luk;
		out->standardLuk           = in->standardLuk;
		out->attPower              = in->attPower;
		out->refiningPower         = in->refiningPower;
		out->max_mattPower         = in->max_mattPower;
		out->min_mattPower         = in->min_mattPower;
		out->itemdefPower          = in->itemdefPower;
		out->plusdefPower          = in->plusdefPower;
		out->mdefPower             = in->mdefPower;
		out->plusmdefPower         = in->plusmdefPower;
		out->hitSuccessValue       = in->hitSuccessValue;
		out->avoidSuccessValue     = in->avoidSuccessValue;
		out->plusAvoidSuccessValue = in->plusAvoidSuccessValue;
		out->criticalSuccessValue  = in->criticalSuccessValue;
		out->ASPD                  = in->ASPD;
		out->plusASPD              = in->plusASPD;

		return out;
	}
};
