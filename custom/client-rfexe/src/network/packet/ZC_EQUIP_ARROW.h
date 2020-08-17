struct PROTO_ZC_EQUIP_ARROW
{
	short PacketType;
	short index;
};


struct PACKET_ZC_EQUIP_ARROW
{
	/* this+0 */ short PacketType;
	/* this+2 */ short index;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_EQUIP_ARROW> in(p);
		TPacket<PROTO_ZC_EQUIP_ARROW> out;

		out->PacketType = PacketType;
		out->index = in->index;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_EQUIP_ARROW> in(p);
		TPacket<PACKET_ZC_EQUIP_ARROW> out;

		out->PacketType = PacketType;
		out->index = in->index;

		return out;
	}
};
