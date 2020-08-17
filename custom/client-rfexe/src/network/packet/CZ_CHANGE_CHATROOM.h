struct PROTO_CZ_CHANGE_CHATROOM
{
	short PacketType;
	short PacketLength;
	short size;
	unsigned char type;
	char passwd[8];
	char title[];
};


struct PACKET_CZ_CHANGE_CHATROOM
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short PacketLength;
	/* this+ 4 */ short size;
	/* this+ 6 */ unsigned char type;
	/* this+ 7 */ char passwd[8];
	/* this+15 */ char title[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_CHANGE_CHATROOM,char> in(p);
		TPacket<PROTO_CZ_CHANGE_CHATROOM,char> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->size = in->size;
		out->type = in->type;
		memcpy(out->passwd, in->passwd, 8);
		memcpy(out->title, in->title, out.count());

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_CHANGE_CHATROOM,char> in(p);
		TPacket<PACKET_CZ_CHANGE_CHATROOM,char> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->size = in->size;
		out->type = in->type;
		memcpy(out->passwd, in->passwd, 8);
		memcpy(out->title, in->title, out.count());

		return out;
	}
};
