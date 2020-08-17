struct PROTO_ZC_AID
{
	short PacketType; // PROTOID_ZC_AID
	unsigned long AID;
};


struct PACKET_ZC_AID
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_AID> in(p);
		TPacket<PROTO_ZC_AID> out;

		out->PacketType = PacketType;
		out->AID = in->AID;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_AID> in(p);
		TPacket<PACKET_ZC_AID> out;

		out->PacketType = PacketType;
		out->AID = in->AID;

		return out;
	}
};


struct PACKET_ZC_AID_RAW
{
	/* this+0 */ unsigned long AID;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		//FIXME: asymmetric handling - input from parser is actually in RO packet form
		TPacket<PACKET_ZC_AID> in(p);
		TPacket<PROTO_ZC_AID> out;

		out->PacketType = PacketType;
		out->AID = in->AID;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		//FIXME: asymmetric handling - output in raw packet form
		TPacket<PROTO_ZC_AID> in(p);
		TPacket<PACKET_ZC_AID_RAW> out;

		out->AID = in->AID;

		return out;
	}
};
