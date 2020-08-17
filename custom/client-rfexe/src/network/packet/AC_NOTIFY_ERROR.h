struct PROTO_AC_NOTIFY_ERROR
{
	short PacketType;
	unsigned short PacketLength;
	char Text[];
};


struct PACKET_AC_NOTIFY_ERROR
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ char Text[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_AC_NOTIFY_ERROR,char> in(p);
		TPacket<PROTO_AC_NOTIFY_ERROR,char> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		memcpy(out->Text, in->Text, out.count());

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_AC_NOTIFY_ERROR,char> in(p);
		TPacket<PACKET_AC_NOTIFY_ERROR,char> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		memcpy(out->Text, in->Text, out.count());

		return out;
	}
};
