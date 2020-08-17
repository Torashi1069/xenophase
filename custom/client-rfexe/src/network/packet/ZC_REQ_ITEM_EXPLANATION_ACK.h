struct PROTO_ZC_REQ_ITEM_EXPLANATION_ACK
{
	short PacketType;
	unsigned short PacketLength;
	BYTE unknown[];
};


struct PACKET_ZC_REQ_ITEM_EXPLANATION_ACK
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ BYTE unknown[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_REQ_ITEM_EXPLANATION_ACK,BYTE> in(p);
		TPacket<PROTO_ZC_REQ_ITEM_EXPLANATION_ACK,BYTE> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		memcpy(out->unknown, in->unknown, out.count());

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_REQ_ITEM_EXPLANATION_ACK,BYTE> in(p);
		TPacket<PACKET_ZC_REQ_ITEM_EXPLANATION_ACK,BYTE> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		memcpy(out->unknown, in->unknown, out.count());

		return out;
	}
};
