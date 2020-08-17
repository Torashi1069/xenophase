struct PROTO_CZ_ENTER
{
	short PacketType;
	unsigned long AID;
	unsigned long GID;
	int AuthCode;
	unsigned long clientTime;
	unsigned char Sex;
};


struct PACKET_CZ_ENTER
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ int AuthCode;
	/* this+14 */ unsigned long clientTime;
	/* this+18 */ unsigned char Sex;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_ENTER> in(p);
		TPacket<PROTO_CZ_ENTER> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->GID = in->GID;
		out->AuthCode = in->AuthCode;
		out->clientTime = in->clientTime;
		out->Sex = in->Sex;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_ENTER> in(p);
		TPacket<PACKET_CZ_ENTER> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->GID = in->GID;
		out->AuthCode = in->AuthCode;
		out->clientTime = in->clientTime;
		out->Sex = in->Sex;

		return out;
	}
};


struct PACKET_CZ_ENTER2
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ int AuthCode;
	/* this+14 */ unsigned long clientTime;
	/* this+18 */ unsigned char Sex;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_ENTER2> in(p);
		TPacket<PROTO_CZ_ENTER> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->GID = in->GID;
		out->AuthCode = in->AuthCode;
		out->clientTime = in->clientTime;
		out->Sex = in->Sex;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_ENTER> in(p);
		TPacket<PACKET_CZ_ENTER2> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->GID = in->GID;
		out->AuthCode = in->AuthCode;
		out->clientTime = in->clientTime;
		out->Sex = in->Sex;

		return out;
	}
};
