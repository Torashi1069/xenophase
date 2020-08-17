struct PROTO_ZC_POSITION_INFO
{
	short PacketType;
	short PacketLength;
	struct GUILD_POSITION_INFO
	{
		int positionID;
		int right;
		int ranking;
		int payRate;
	}
	Info[];
};


struct PACKET_ZC_POSITION_INFO
{
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ struct GUILD_POSITION_INFO
	             {
	             	/* this+ 0 */ int positionID;
	             	/* this+ 4 */ int right;
	             	/* this+ 8 */ int ranking;
	             	/* this+12 */ int payRate;
	             }
	             Info[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_POSITION_INFO,PACKET_ZC_POSITION_INFO::GUILD_POSITION_INFO> in(p);
		TPacket<PROTO_ZC_POSITION_INFO,PROTO_ZC_POSITION_INFO::GUILD_POSITION_INFO> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Info[i].positionID = in->Info[i].positionID;
			out->Info[i].right = in->Info[i].right;
			out->Info[i].ranking = in->Info[i].ranking;
			out->Info[i].payRate = in->Info[i].payRate;
		}

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_POSITION_INFO,PROTO_ZC_POSITION_INFO::GUILD_POSITION_INFO> in(p);
		TPacket<PACKET_ZC_POSITION_INFO,PACKET_ZC_POSITION_INFO::GUILD_POSITION_INFO> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Info[i].positionID = in->Info[i].positionID;
			out->Info[i].right = in->Info[i].right;
			out->Info[i].ranking = in->Info[i].ranking;
			out->Info[i].payRate = in->Info[i].payRate;
		}

		return out;
	}
};
