struct PROTO_ZC_FORMATSTRING_MSG
{
	short PacketType;
	unsigned short PacketLength;
	unsigned short msg; // enum MSGSTRINGID
	BYTE args[];

	//NOTE: the actual format is
	// struct {
	//   char szArg[];
	//   BYTE unknown[6];
	// } args[];
};


struct PACKET_ZC_FORMATSTRING_MSG
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ unsigned short msg;
	/* this+6 */ BYTE args[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_FORMATSTRING_MSG,BYTE> in(p);
		TPacket<PROTO_ZC_FORMATSTRING_MSG,BYTE> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->msg = in->msg;
		memcpy(out->args, in->args, out.count());

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_FORMATSTRING_MSG,BYTE> in(p);
		TPacket<PACKET_ZC_FORMATSTRING_MSG,BYTE> out;

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->msg = in->msg;
		memcpy(out->args, in->args, out.count());

		return out;
	}
};
