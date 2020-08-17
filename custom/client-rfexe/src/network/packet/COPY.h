struct PROTO_COPY
{
	short PacketType; // PROTOID_COPY
	BYTE Payload[]; // encapsulated packet
};


struct PACKET_COPY
{
	/* this+0 */ BYTE Payload[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_COPY,BYTE> in(p);
		TPacket<PROTO_COPY,BYTE> out(in.count());

		out->PacketType = PacketType;
		memcpy(out->Payload, in->Payload, out.count());

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_COPY,BYTE> in(p);
		TPacket<PACKET_COPY,BYTE> out(in.count());

//		out->PacketType = PacketType; // not applicable
		memcpy(out->Payload, in->Payload, out.count());

		return out;
	}
};
