struct PROTO_CA_PT_CARDPASS
{
	short PacketType;
	char m_cardPass[28];
};


struct PACKET_CA_PT_CARDPASS
{
	/* this+0 */ short PacketType;
	/* this+2 */ char m_cardPass[28];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CA_PT_CARDPASS> in(p);
		TPacket<PROTO_CA_PT_CARDPASS> out;

		out->PacketType = PacketType; // PROTOID_CA_PT_CARDPASS
		memcpy(out->m_cardPass, in->m_cardPass, 28);

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CA_PT_CARDPASS> in(p);
		TPacket<PACKET_CA_PT_CARDPASS> out;

		out->PacketType = PacketType; // HEADER_CA_ACK_LOGIN_CARDPASS
		memcpy(out->m_cardPass, in->m_cardPass, 28);

		return out;
	}
};
