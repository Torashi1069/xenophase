struct PROTO_ZC_ITEM_FALL_ENTRY
{
	short PacketType;
	unsigned long ITAID;
	unsigned short ITID;
	bool IsIdentified;
	short xPos;
	short yPos;
	unsigned char subX;
	unsigned char subY;
	short count;
};


struct PACKET_ZC_ITEM_FALL_ENTRY
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long ITAID;
	/* this+ 6 */ unsigned short ITID;
	/* this+ 8 */ bool IsIdentified;
	/* this+ 9 */ short xPos;
	/* this+11 */ short yPos;
	/* this+13 */ unsigned char subX;
	/* this+14 */ unsigned char subY;
	/* this+15 */ short count;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ITEM_FALL_ENTRY> in(p);
		TPacket<PROTO_ZC_ITEM_FALL_ENTRY> out;

		out->PacketType = PacketType;
		out->ITAID = in->ITAID;
		out->ITID = in->ITID;
		out->IsIdentified = in->IsIdentified;
		out->xPos = in->xPos;
		out->yPos = in->yPos;
		out->subX = in->subX;
		out->subY = in->subY;
		out->count = in->count;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_ITEM_FALL_ENTRY> in(p);
		TPacket<PACKET_ZC_ITEM_FALL_ENTRY> out;

		out->PacketType = PacketType;
		out->ITAID = in->ITAID;
		out->ITID = in->ITID;
		out->IsIdentified = in->IsIdentified;
		out->xPos = in->xPos;
		out->yPos = in->yPos;
		out->subX = in->subX;
		out->subY = in->subY;
		out->count = in->count;

		return out;
	}
};


struct PACKET_ZC_ITEM_FALL_ENTRY2
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short PacketLength;
	/* this+ 4 */ unsigned long ITAID;
	/* this+ 8 */ unsigned short ITID;
	/* this+10 */ bool IsIdentified;
	/* this+11 */ short xPos;
	/* this+13 */ short yPos;
	/* this+15 */ unsigned char subX;
	/* this+16 */ unsigned char subY;
	/* this+17 */ short count;
	/* this+19 */ BYTE unknown[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ITEM_FALL_ENTRY2,BYTE> in(p);
		TPacket<PROTO_ZC_ITEM_FALL_ENTRY> out;

		// xor deobfuscation
		in[5] ^= in[13];
		in[7] ^= in[8];

		out->PacketType = PacketType;
		out->ITAID = in->ITAID;
		out->ITID = in->ITID;
		out->IsIdentified = in->IsIdentified;
		out->xPos = in->xPos;
		out->yPos = in->yPos;
		out->subX = in->subX;
		out->subY = in->subY;
		out->count = in->count;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_ITEM_FALL_ENTRY> in(p);
		TPacket<PACKET_ZC_ITEM_FALL_ENTRY2,BYTE> out((size_t)0);

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->ITAID = in->ITAID;
		out->ITID = in->ITID;
		out->IsIdentified = in->IsIdentified;
		out->xPos = in->xPos;
		out->yPos = in->yPos;
		out->subX = in->subX;
		out->subY = in->subY;
		out->count = in->count;

		// xor obfuscation
		out[5] ^= out[13];
		out[7] ^= out[8];

		return out;
	}
};


struct PACKET_ZC_ITEM_FALL_ENTRY3
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short PacketLength;
	/* this+ 4 */ unsigned long ITAID;
	/* this+ 8 */ unsigned short ITID;
	/* this+10 */ bool IsIdentified;
	/* this+11 */ short xPos;
	/* this+13 */ short yPos;
	/* this+15 */ unsigned char subX;
	/* this+16 */ unsigned char subY;
	/* this+17 */ short count;
	/* this+19 */ BYTE unknown[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ITEM_FALL_ENTRY3,BYTE> in(p);
		TPacket<PROTO_ZC_ITEM_FALL_ENTRY> out;

		// xor deobfuscation
		*(DWORD*)&in[4] ^= *(WORD*)&in[0] ^ (*(WORD*)&in[11] + (in[16] << 16));

		out->PacketType = PacketType;
		out->ITAID = in->ITAID;
		out->ITID = in->ITID;
		out->IsIdentified = in->IsIdentified;
		out->xPos = in->xPos;
		out->yPos = in->yPos;
		out->subX = in->subX;
		out->subY = in->subY;
		out->count = in->count;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_ITEM_FALL_ENTRY> in(p);
		TPacket<PACKET_ZC_ITEM_FALL_ENTRY3,BYTE> out((size_t)0);

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->ITAID = in->ITAID;
		out->ITID = in->ITID;
		out->IsIdentified = in->IsIdentified;
		out->xPos = in->xPos;
		out->yPos = in->yPos;
		out->subX = in->subX;
		out->subY = in->subY;
		out->count = in->count;

		// xor obfuscation
		*(DWORD*)&out[4] ^= *(WORD*)&out[0] ^ (*(WORD*)&out[11] + (out[16] << 16));

		return out;
	}
};
