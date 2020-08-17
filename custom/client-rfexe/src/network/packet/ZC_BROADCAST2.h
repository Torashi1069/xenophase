struct PROTO_ZC_BROADCAST2
{
	short PacketType;
	unsigned short PacketLength;
	COLORREF fontColor;
	short fontType;
	short fontSize;
	short fontAlign;
	short fontY;
	char Text[];
};


struct PACKET_ZC_BROADCAST2
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short PacketLength;
	/* this+ 4 */ COLORREF fontColor;
	/* this+ 8 */ short fontType;
	/* this+10 */ short fontSize;
	/* this+12 */ short fontAlign;
	/* this+14 */ short fontY;
	/* this+16 */ char Text[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_BROADCAST2,char> in(p);
		TPacket<PROTO_ZC_BROADCAST2,char> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->fontColor = in->fontColor;
		out->fontType = in->fontType;
		out->fontSize = in->fontSize;
		out->fontAlign = in->fontAlign;
		out->fontY = in->fontY;
		memcpy(out->Text, in->Text, out.count());

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_BROADCAST2,char> in(p);
		TPacket<PACKET_ZC_BROADCAST2,char> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->fontColor = in->fontColor;
		out->fontType = in->fontType;
		out->fontSize = in->fontSize;
		out->fontAlign = in->fontAlign;
		out->fontY = in->fontY;
		memcpy(out->Text, in->Text, out.count());

		return out;
	}
};


struct PACKET_ZC_BROADCAST3
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short PacketLength;
	/* this+ 4 */ COLORREF fontColor;
	/* this+ 8 */ short fontType;
	/* this+10 */ short fontSize;
	/* this+12 */ short fontAlign;
	/* this+14 */ short fontY;
	/* this+16 */ char Text[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_BROADCAST3,char> in(p);
		TPacket<PROTO_ZC_BROADCAST2,char> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->fontColor = in->fontColor;
		out->fontType = in->fontType;
		out->fontSize = in->fontSize;
		out->fontAlign = in->fontAlign;
		out->fontY = in->fontY;
		memcpy(out->Text, in->Text, out.count());

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_BROADCAST2,char> in(p);
		TPacket<PACKET_ZC_BROADCAST3,char> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->fontColor = in->fontColor;
		out->fontType = in->fontType;
		out->fontSize = in->fontSize;
		out->fontAlign = in->fontAlign;
		out->fontY = in->fontY;
		memcpy(out->Text, in->Text, out.count());

		return out;
	}
};
