struct PROTO_ZC_MAPPROPERTY
{
	short PacketType;
	unsigned short PacketLength;
	short type;
	unsigned char array[];
};


struct PACKET_ZC_MAPPROPERTY
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ short type;
	/* this+6 */ unsigned char array[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_MAPPROPERTY,unsigned char> in(p);
		TPacket<PROTO_ZC_MAPPROPERTY,unsigned char> out(in.count());
		
		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->type = in->type;
		memcpy(out->array, in->array, out.count() * sizeof(unsigned char));

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_MAPPROPERTY,unsigned char> in(p);
		TPacket<PACKET_ZC_MAPPROPERTY,unsigned char> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->type = in->type;
		memcpy(out->array, in->array, out.count() * sizeof(unsigned char));

		return out;
	}
};
