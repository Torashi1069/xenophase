struct PROTO_CZ_REQUEST_CHAT
{
	short PacketType;
	unsigned short PacketLength;
	char Text[];
};


struct PACKET_CZ_REQUEST_CHAT
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ char Text[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_REQUEST_CHAT,char> in(p);
		TPacket<PROTO_CZ_REQUEST_CHAT,char> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		memcpy(out->Text, in->Text, out.count() * sizeof(char));

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_REQUEST_CHAT,char> in(p);
		TPacket<PACKET_CZ_REQUEST_CHAT,char> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		memcpy(out->Text, in->Text, out.count() * sizeof(char));

		return out;
	}
};
