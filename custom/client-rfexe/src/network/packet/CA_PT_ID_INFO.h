struct PROTO_CA_PT_ID_INFO
{
	short PacketType;
	char szPTID[21];
	char szPTNumID[21];
};


struct PACKET_CA_PT_ID_INFO
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char szPTID[21];
	/* this+23 */ char szPTNumID[21];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CA_PT_ID_INFO> in(p);
		TPacket<PROTO_CA_PT_ID_INFO> out;

		out->PacketType = PacketType; // PROTOID_CA_PT_ID_INFO
		memcpy(out->szPTID, in->szPTID, 21);
		memcpy(out->szPTNumID, in->szPTNumID, 21);

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CA_PT_ID_INFO> in(p);
		TPacket<PACKET_CA_PT_ID_INFO> out;

		out->PacketType = PacketType; // HEADER_AC_ACK_PT_ID_INFO
		memcpy(out->szPTID, in->szPTID, 21);
		memcpy(out->szPTNumID, in->szPTNumID, 21);

		return out;
	}
};
