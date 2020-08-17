struct PROTO_ZC_WHISPER
{
	short PacketType;
	unsigned short PacketLength;
	char sender[24];
	BOOL isAdmin;
	char Text[];
};


struct PACKET_ZC_WHISPER
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short PacketLength;
	/* this+ 4 */ char sender[24];
	/* this+28 */ char Text[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_WHISPER,char> in(p);
		TPacket<PROTO_ZC_WHISPER,char> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		memcpy(out->sender, in->sender, 24);
		out->isAdmin = FALSE; // adapt
		memcpy(out->Text, in->Text, out.count());

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_WHISPER,char> in(p);
		TPacket<PACKET_ZC_WHISPER,char> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		memcpy(out->sender, in->sender, 24);
//		out->isAdmin = in->isAdmin; // adapt
		memcpy(out->Text, in->Text, out.count());

		return out;
	}
};


struct PACKET_ZC_WHISPER__KRO20061023
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short PacketLength;
	/* this+ 4 */ char sender[24];
	/* this+28 */ BOOL isAdmin;
	/* this+32 */ char Text[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_WHISPER__KRO20061023,char> in(p);
		TPacket<PROTO_ZC_WHISPER,char> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		memcpy(out->sender, in->sender, 24);
		out->isAdmin = in->isAdmin;
		memcpy(out->Text, in->Text, out.count());

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_WHISPER,char> in(p);
		TPacket<PACKET_ZC_WHISPER__KRO20061023,char> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		memcpy(out->sender, in->sender, 24);
		out->isAdmin = in->isAdmin;
		memcpy(out->Text, in->Text, out.count());

		return out;
	}
};
