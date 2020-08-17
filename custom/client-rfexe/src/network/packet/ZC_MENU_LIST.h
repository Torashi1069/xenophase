struct PROTO_ZC_MENU_LIST
{
	short PacketType;
	unsigned short PacketLength;
	unsigned long NAID;
	char MenuListStr[];
};


struct PACKET_ZC_MENU_LIST
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ unsigned long NAID;
	/* this+8 */ char MenuListStr[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_MENU_LIST,char> in(p);
		TPacket<PROTO_ZC_MENU_LIST,char> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->NAID = in->NAID;
		memcpy(out->MenuListStr, in->MenuListStr, out.count());

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_MENU_LIST,char> in(p);
		TPacket<PACKET_ZC_MENU_LIST,char> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->NAID = in->NAID;
		memcpy(out->MenuListStr, in->MenuListStr, out.count());

		return out;
	}
};
