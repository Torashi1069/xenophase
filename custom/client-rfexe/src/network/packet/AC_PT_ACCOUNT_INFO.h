struct PROTO_AC_PT_ACCOUNT_INFO
{
	short PacketType;
};


struct PACKET_AC_PT_ACCOUNT_INFO
{
	/* this+0 */ short PacketType;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_AC_PT_ACCOUNT_INFO> in(p);
		TPacket<PROTO_AC_PT_ACCOUNT_INFO> out;

		out->PacketType = PacketType; // PROTOID_AC_PT_ACCOUNT_INFO

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_AC_PT_ACCOUNT_INFO> in(p);
		TPacket<PACKET_AC_PT_ACCOUNT_INFO> out;

		out->PacketType = PacketType; // HEADER_AC_REQ_LOGIN_ACCOUNT_INFO

		return out;
	}
};
