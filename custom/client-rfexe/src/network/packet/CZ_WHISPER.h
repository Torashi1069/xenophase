struct PROTO_CZ_WHISPER
{
	short PacketType;
	unsigned short PacketLength;
	char receiver[24];
	char Text[];
};


struct PACKET_CZ_WHISPER
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short PacketLength;
	/* this+ 4 */ char receiver[24];
	/* this+28 */ char Text[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_WHISPER,char> in(p);
		TPacket<PROTO_CZ_WHISPER,char> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		memcpy(out->receiver, in->receiver, 24);
		memcpy(out->Text, in->Text, out.count());

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_WHISPER,char> in(p);
		TPacket<PACKET_CZ_WHISPER,char> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		memcpy(out->receiver, in->receiver, 24);
		memcpy(out->Text, in->Text, out.count());

		return out;
	}
};
