struct PROTO_ZC_REQ_TAKEOFF_EQUIP_ACK
{
	short PacketType;
	unsigned short index;
	unsigned short wearLocation;
	bool result;
};


struct PACKET_ZC_REQ_TAKEOFF_EQUIP_ACK
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short index;
	/* this+4 */ unsigned short wearLocation;
	/* this+6 */ bool result;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_REQ_TAKEOFF_EQUIP_ACK> in(p);
		TPacket<PROTO_ZC_REQ_TAKEOFF_EQUIP_ACK> out;

		out->PacketType = PacketType;
		out->index = in->index;
		out->wearLocation = in->wearLocation;
		out->result = in->result;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_REQ_TAKEOFF_EQUIP_ACK> in(p);
		TPacket<PACKET_ZC_REQ_TAKEOFF_EQUIP_ACK> out;

		out->PacketType = PacketType;
		out->index = in->index;
		out->wearLocation = in->wearLocation;
		out->result = in->result;

		return out;
	}
};
