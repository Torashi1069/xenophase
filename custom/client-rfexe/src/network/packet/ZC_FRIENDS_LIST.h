struct PROTO_ZC_FRIENDS_LIST
{
	short PacketType;
	unsigned short PacketLength;
	struct STRUCT_FRIEND
	{
		unsigned long AID;
		unsigned long GID;
		char Name[24];
	}
	List[];
};


struct PACKET_ZC_FRIENDS_LIST
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ struct STRUCT_FRIEND
	             {
	             	/* this+0 */ unsigned long AID;
	             	/* this+4 */ unsigned long GID;
	             	/* this+8 */ char Name[24];
	             }
	             List[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_FRIENDS_LIST,PACKET_ZC_FRIENDS_LIST::STRUCT_FRIEND> in(p);
		TPacket<PROTO_ZC_FRIENDS_LIST,PROTO_ZC_FRIENDS_LIST::STRUCT_FRIEND> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->List[i].AID = in->List[i].AID;
			out->List[i].GID = in->List[i].GID;
			memcpy(out->List[i].Name, in->List[i].Name, 24);
		}

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_FRIENDS_LIST,PROTO_ZC_FRIENDS_LIST::STRUCT_FRIEND> in(p);
		TPacket<PACKET_ZC_FRIENDS_LIST,PACKET_ZC_FRIENDS_LIST::STRUCT_FRIEND> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->List[i].AID = in->List[i].AID;
			out->List[i].GID = in->List[i].GID;
			memcpy(out->List[i].Name, in->List[i].Name, 24);
		}

		return out;
	}
};
