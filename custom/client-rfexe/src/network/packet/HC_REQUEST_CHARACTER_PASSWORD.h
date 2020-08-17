struct PROTO_HC_REQUEST_CHARACTER_PASSWORD
{
	short PacketType;
	short Result;
	DWORD dwSeed;
};


struct PACKET_HC_REQUEST_CHARACTER_PASSWORD
{
	/* this+0 */ short PacketType;
	/* this+2 */ short Result;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_HC_REQUEST_CHARACTER_PASSWORD> in(p);
		TPacket<PROTO_HC_REQUEST_CHARACTER_PASSWORD> out;

		out->PacketType = PacketType;
		out->Result = in->Result;
		out->dwSeed = 0; // adapt

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_HC_REQUEST_CHARACTER_PASSWORD> in(p);
		TPacket<PACKET_HC_REQUEST_CHARACTER_PASSWORD> out;

		out->PacketType = PacketType;
		out->Result = in->Result;
//		out->dwSeed = in->dwSeed; // adapt

		return out;
	}
};


struct PACKET_HC_REQUEST_CHARACTER_PASSWORD__2007
{
	/* this+0 */ short PacketType;
	/* this+2 */ short Result;
	/* this+4 */ DWORD dwSeed;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_HC_REQUEST_CHARACTER_PASSWORD__2007> in(p);
		TPacket<PROTO_HC_REQUEST_CHARACTER_PASSWORD> out;

		out->PacketType = PacketType;
		out->Result = in->Result;
		out->dwSeed = in->dwSeed;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_HC_REQUEST_CHARACTER_PASSWORD> in(p);
		TPacket<PACKET_HC_REQUEST_CHARACTER_PASSWORD__2007> out;

		out->PacketType = PacketType;
		out->Result = in->Result;
		out->dwSeed = in->dwSeed;

		return out;
	}
};


struct PACKET_HC_REQUEST_CHARACTER_PASSWORD__2009
{
	/* this+0 */ short PacketType;
	/* this+2 */ short Result;
	/* this+4 */ DWORD dummyValue;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_HC_REQUEST_CHARACTER_PASSWORD__2009> in(p);
		TPacket<PROTO_HC_REQUEST_CHARACTER_PASSWORD> out;

		out->PacketType = PacketType;
		out->Result = in->Result;
		out->dwSeed = in->dummyValue; // adapt?

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_HC_REQUEST_CHARACTER_PASSWORD> in(p);
		TPacket<PACKET_HC_REQUEST_CHARACTER_PASSWORD__2009> out;

		out->PacketType = PacketType;
		out->Result = in->Result;
		out->dummyValue = in->dwSeed; // adapt?

		return out;
	}
};
