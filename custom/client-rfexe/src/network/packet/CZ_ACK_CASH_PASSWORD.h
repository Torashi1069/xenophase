struct PROTO_CZ_ACK_CASH_PASSWORD
{
	short PacketType;
	short Type;
	unsigned char Password[16];
	unsigned char NewPassword[16];
};


struct PACKET_CZ_ACK_CASH_PASSWORD
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short Type;
	/* this+ 4 */ unsigned char Password[16];
	/* this+20 */ unsigned char NewPassword[16];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_ACK_CASH_PASSWORD> in(p);
		TPacket<PROTO_CZ_ACK_CASH_PASSWORD> out;

		out->PacketType = PacketType;
		out->Type = in->Type;
		memcpy(out->Password, in->Password, 16);
		memcpy(out->NewPassword, in->NewPassword, 16);

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_ACK_CASH_PASSWORD> in(p);
		TPacket<PACKET_CZ_ACK_CASH_PASSWORD> out;

		out->PacketType = PacketType;
		out->Type = in->Type;
		memcpy(out->Password, in->Password, 16);
		memcpy(out->NewPassword, in->NewPassword, 16);

		return out;
	}
};
