struct PROTO_CH_MAKE_CHAR
{
	short PacketType;
	unsigned char name[24];
	unsigned char Str;
	unsigned char Agi;
	unsigned char Vit;
	unsigned char Int;
	unsigned char Dex;
	unsigned char Luk;
	unsigned char CharNum;
	short headPal;
	short head;
};


struct PACKET_CH_MAKE_CHAR
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned char name[24];
	/* this+26 */ unsigned char Str;
	/* this+27 */ unsigned char Agi;
	/* this+28 */ unsigned char Vit;
	/* this+29 */ unsigned char Int;
	/* this+30 */ unsigned char Dex;
	/* this+31 */ unsigned char Luk;
	/* this+32 */ unsigned char CharNum;
	/* this+33 */ short headPal;
	/* this+35 */ short head;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CH_MAKE_CHAR> in(p);
		TPacket<PROTO_CH_MAKE_CHAR> out;

		out->PacketType = PacketType;
		memcpy(out->name, in->name, 24);
		out->Str = in->Str;
		out->Agi = in->Agi;
		out->Vit = in->Vit;
		out->Int = in->Int;
		out->Dex = in->Dex;
		out->Luk = in->Luk;
		out->CharNum = in->CharNum;
		out->headPal = in->headPal;
		out->head = in->head;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CH_MAKE_CHAR> in(p);
		TPacket<PACKET_CH_MAKE_CHAR> out;

		out->PacketType = PacketType;
		memcpy(out->name, in->name, 24);
		out->Str = in->Str;
		out->Agi = in->Agi;
		out->Vit = in->Vit;
		out->Int = in->Int;
		out->Dex = in->Dex;
		out->Luk = in->Luk;
		out->CharNum = in->CharNum;
		out->headPal = in->headPal;
		out->head = in->head;

		return out;
	}
};
