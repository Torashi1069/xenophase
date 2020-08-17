struct PROTO_CA_PT_EKEY_FAIL
{
	short PacketType;
	short errorCode;
};


struct PACKET_CA_PT_EKEY_FAIL
{
	/* this+0 */ short PacketType;
	/* this+2 */ short errorCode;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CA_PT_EKEY_FAIL> in(p);
		TPacket<PROTO_CA_PT_EKEY_FAIL> out;

		out->PacketType = PacketType; // PROTOID_CA_PT_EKEY_FAIL_*
		out->errorCode = in->errorCode;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CA_PT_EKEY_FAIL> in(p);
		TPacket<PACKET_CA_PT_EKEY_FAIL> out;

		out->PacketType = PacketType; // HEADER_AC_ACK_*KEY_FAIL_*
		out->errorCode = in->errorCode;

		return out;
	}
};
