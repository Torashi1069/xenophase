struct PROTO_CZ_REQ_TAKEOFF_EQUIP
{
	short PacketType;
	unsigned short index;
};


struct PACKET_CZ_REQ_TAKEOFF_EQUIP
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short index;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_REQ_TAKEOFF_EQUIP> in(p);
		TPacket<PROTO_CZ_REQ_TAKEOFF_EQUIP> out;

		out->PacketType = PacketType;
		out->index = in->index;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_REQ_TAKEOFF_EQUIP> in(p);
		TPacket<PACKET_CZ_REQ_TAKEOFF_EQUIP> out;

		out->PacketType = PacketType;
		out->index = in->index;

		return out;
	}
};
