struct PROTO_AC_ACK_HASH
{
	short PacketType;
	short PacketLength;
	char RandStr[];
};


struct PACKET_AC_ACK_HASH
{
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ char RandStr[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_AC_ACK_HASH,char> in(p);
		TPacket<PROTO_AC_ACK_HASH,char> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		memcpy(out->RandStr, in->RandStr, out.count());

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_AC_ACK_HASH,char> in(p);
		TPacket<PACKET_AC_ACK_HASH,char> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		memcpy(out->RandStr, in->RandStr, out.count());

		return out;
	}
};
