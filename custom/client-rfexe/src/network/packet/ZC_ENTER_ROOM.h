struct PROTO_ZC_ENTER_ROOM
{
	short PacketType;
	short PacketLength;
	unsigned long roomID;
	struct ROOM_MEMBER_DATA
	{
		unsigned long role;
		char name[24];
	}
	Members[];
};


struct PACKET_ZC_ENTER_ROOM
{
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ unsigned long roomID;
	/* this+8 */ struct ROOM_MEMBER_DATA
	{
		/* this+0 */ unsigned long role;
		/* this+4 */ char name[24];
	}
	Members[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ENTER_ROOM,PACKET_ZC_ENTER_ROOM::ROOM_MEMBER_DATA> in(p);
		TPacket<PROTO_ZC_ENTER_ROOM,PROTO_ZC_ENTER_ROOM::ROOM_MEMBER_DATA> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->roomID = in->roomID;

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Members[i].role = in->Members[i].role;
			memcpy(out->Members[i].name, in->Members[i].name, 24);
		}

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_ENTER_ROOM,PROTO_ZC_ENTER_ROOM::ROOM_MEMBER_DATA> in(p);
		TPacket<PACKET_ZC_ENTER_ROOM,PACKET_ZC_ENTER_ROOM::ROOM_MEMBER_DATA> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->roomID = in->roomID;

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Members[i].role = in->Members[i].role;
			memcpy(out->Members[i].name, in->Members[i].name, 24);
		}

		return out;
	}
};
