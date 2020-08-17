struct PROTO_ZC_MSG
{
	short PacketType;
	unsigned short msg; // enum MSGSTRINGID
};


struct PACKET_ZC_MSG
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short msg;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_MSG> in(p);
		TPacket<PROTO_ZC_MSG> out;

		out->PacketType = PacketType;
		out->msg = in->msg;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_MSG> in(p);
		TPacket<PACKET_ZC_MSG> out;

		out->PacketType = PacketType;
		out->msg = in->msg;

		return out;
	}
};
