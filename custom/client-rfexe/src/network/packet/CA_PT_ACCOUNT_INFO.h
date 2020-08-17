struct PROTO_CA_PT_ACCOUNT_INFO
{
	short PacketType;
	short sex;
	short bPoint;
	char E_mail[34];
};


struct PACKET_CA_PT_ACCOUNT_INFO
{
	/* this+0 */ short PacketType;
	/* this+2 */ short sex;
	/* this+4 */ short bPoint;
	/* this+6 */ char E_mail[34];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CA_PT_ACCOUNT_INFO> in(p);
		TPacket<PROTO_CA_PT_ACCOUNT_INFO> out;

		out->PacketType = PacketType; // PROTOID_CA_PT_ACCOUNT_INFO
		out->sex = in->sex;
		out->bPoint = in->bPoint;
		memcpy(out->E_mail, in->E_mail, 34);

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CA_PT_ACCOUNT_INFO> in(p);
		TPacket<PACKET_CA_PT_ACCOUNT_INFO> out;

		out->PacketType = PacketType; // HEADER_CA_ACK_LOGIN_ACCOUNT_INFO
		out->sex = in->sex;
		out->bPoint = in->bPoint;
		memcpy(out->E_mail, in->E_mail, 34);

		return out;
	}
};
