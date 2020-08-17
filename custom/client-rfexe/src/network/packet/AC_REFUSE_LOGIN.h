struct PROTO_AC_REFUSE_LOGIN
{
	short PacketType; // PROTOID_AC_REFUSE_LOGIN
	unsigned char ErrorCode; // enum REFUSETYPE
	char blockDate[20];
};


struct PACKET_AC_REFUSE_LOGIN
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char ErrorCode;
	/* this+3 */ char blockDate[20];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_AC_REFUSE_LOGIN> in(p);
		TPacket<PROTO_AC_REFUSE_LOGIN> out;

		out->PacketType = PacketType;
		out->ErrorCode = in->ErrorCode;
		memcpy(out->blockDate, in->blockDate, 20);

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_AC_REFUSE_LOGIN> in(p);
		TPacket<PACKET_AC_REFUSE_LOGIN> out;

		out->PacketType = PacketType;
		out->ErrorCode = in->ErrorCode;
		memcpy(out->blockDate, in->blockDate, 20);

		return out;
	}
};
