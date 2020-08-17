struct PROTO_CA_PT_EKEY
{
	short PacketType;
	char m_SeedValue[9];
	char m_EKey[9];
};


struct PACKET_CA_PT_EKEY
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char m_SeedValue[9];
	/* this+11 */ char m_EKey[9];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CA_PT_EKEY> in(p);
		TPacket<PROTO_CA_PT_EKEY> out;

		out->PacketType = PacketType; // PROTOID_CA_PT_*EKEY
		memcpy(out->m_SeedValue, in->m_SeedValue, 9);
		memcpy(out->m_EKey, in->m_EKey, 9);

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CA_PT_EKEY> in(p);
		TPacket<PACKET_CA_PT_EKEY> out;

		out->PacketType = PacketType; // HEADER_CA_ACK_LOGIN_*EKEY
		memcpy(out->m_SeedValue, in->m_SeedValue, 9);
		memcpy(out->m_EKey, in->m_EKey, 9);

		return out;
	}
};
