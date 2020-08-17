struct PROTO_ZC_ACK_STATUS_GM
{
	short PacketType;
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


struct PACKET_ZC_ACK_STATUS_GM
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned char str;
	/* this+ 3 */ unsigned char standardStr;
	/* this+ 4 */ unsigned char agi;
	/* this+ 5 */ unsigned char standardAgi;
	/* this+ 6 */ unsigned char vit;
	/* this+ 7 */ unsigned char standardVit;
	/* this+ 8 */ unsigned char Int;
	/* this+ 9 */ unsigned char standardInt;
	/* this+10 */ unsigned char dex;
	/* this+11 */ unsigned char standardDex;
	/* this+12 */ unsigned char luk;
	/* this+13 */ unsigned char standardLuk;
	/* this+14 */ short attPower;
	/* this+16 */ short refiningPower;
	/* this+18 */ short max_mattPower;
	/* this+20 */ short min_mattPower;
	/* this+22 */ short itemdefPower;
	/* this+24 */ short plusdefPower;
	/* this+26 */ short mdefPower;
	/* this+28 */ short plusmdefPower;
	/* this+30 */ short hitSuccessValue;
	/* this+32 */ short avoidSuccessValue;
	/* this+34 */ short plusAvoidSuccessValue;
	/* this+36 */ short criticalSuccessValue;
	/* this+38 */ short ASPD;
	/* this+40 */ short plusASPD;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ACK_STATUS_GM> in(p);
		TPacket<PROTO_ZC_ACK_STATUS_GM> out;

		out->PacketType = PacketType;
		out->str = in->str;
		out->standardStr = in->standardStr;
		out->agi = in->agi;
		out->standardAgi = in->standardAgi;
		out->vit = in->vit;
		out->standardVit = in->standardVit;
		out->Int = in->Int;
		out->standardInt = in->standardInt;
		out->dex = in->dex;
		out->standardDex = in->standardDex;
		out->luk = in->luk;
		out->standardLuk = in->standardLuk;
		out->attPower = in->attPower;
		out->refiningPower = in->refiningPower;
		out->max_mattPower = in->max_mattPower;
		out->min_mattPower = in->min_mattPower;
		out->itemdefPower = in->itemdefPower;
		out->plusdefPower = in->plusdefPower;
		out->mdefPower = in->mdefPower;
		out->plusmdefPower = in->plusmdefPower;
		out->hitSuccessValue = in->hitSuccessValue;
		out->avoidSuccessValue = in->avoidSuccessValue;
		out->plusAvoidSuccessValue = in->plusAvoidSuccessValue;
		out->criticalSuccessValue = in->criticalSuccessValue;
		out->ASPD = in->ASPD;
		out->plusASPD = in->plusASPD;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_ACK_STATUS_GM> in(p);
		TPacket<PACKET_ZC_ACK_STATUS_GM> out;

		out->PacketType = PacketType;
		out->str = in->str;
		out->standardStr = in->standardStr;
		out->agi = in->agi;
		out->standardAgi = in->standardAgi;
		out->vit = in->vit;
		out->standardVit = in->standardVit;
		out->Int = in->Int;
		out->standardInt = in->standardInt;
		out->dex = in->dex;
		out->standardDex = in->standardDex;
		out->luk = in->luk;
		out->standardLuk = in->standardLuk;
		out->attPower = in->attPower;
		out->refiningPower = in->refiningPower;
		out->max_mattPower = in->max_mattPower;
		out->min_mattPower = in->min_mattPower;
		out->itemdefPower = in->itemdefPower;
		out->plusdefPower = in->plusdefPower;
		out->mdefPower = in->mdefPower;
		out->plusmdefPower = in->plusmdefPower;
		out->hitSuccessValue = in->hitSuccessValue;
		out->avoidSuccessValue = in->avoidSuccessValue;
		out->plusAvoidSuccessValue = in->plusAvoidSuccessValue;
		out->criticalSuccessValue = in->criticalSuccessValue;
		out->ASPD = in->ASPD;
		out->plusASPD = in->plusASPD;

		return out;
	}
};
