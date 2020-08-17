struct PROTO_AC_PT_LOGIN_INFO
{
	short PacketType;
	char m_SeedValue[9];
};


struct PACKET_AC_PT_LOGIN_INFO
{
	/* this+0 */ short PacketType;
	/* this+2 */ char m_SeedValue[9];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_AC_PT_LOGIN_INFO> in(p);
		TPacket<PROTO_AC_PT_LOGIN_INFO> out;

		out->PacketType = PacketType; // PROTOID_AC_PT_*KEY
		memcpy(out->m_SeedValue, in->m_SeedValue, 9);

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_AC_PT_LOGIN_INFO> in(p);
		TPacket<PACKET_AC_PT_LOGIN_INFO> out;

		out->PacketType = PacketType; // HEADER_AC_REQ_LOGIN_*EKEY
		memcpy(out->m_SeedValue, in->m_SeedValue, 9);

		return out;
	}
};
