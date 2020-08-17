struct PROTO_ZC_ACK_CHANGE_GUILD_POSITIONINFO
{
	short PacketType;
	short PacketLength;
	struct GUILD_REG_POSITION_INFO
	{
		int positionID;
		int right;
		int ranking;
		int payRate;
		char posName[24];
	}
	Info[];
};


struct PACKET_ZC_ACK_CHANGE_GUILD_POSITIONINFO
{
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ struct GUILD_REG_POSITION_INFO
	             {
	             	/* this+ 0 */ int positionID;
	             	/* this+ 4 */ int right;
	             	/* this+ 8 */ int ranking;
	             	/* this+12 */ int payRate;
	             	/* this+16 */ char posName[24];
	             }
	             Info[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ACK_CHANGE_GUILD_POSITIONINFO,PACKET_ZC_ACK_CHANGE_GUILD_POSITIONINFO::GUILD_REG_POSITION_INFO> in(p);
		TPacket<PROTO_ZC_ACK_CHANGE_GUILD_POSITIONINFO,PROTO_ZC_ACK_CHANGE_GUILD_POSITIONINFO::GUILD_REG_POSITION_INFO> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Info[i].positionID = in->Info[i].positionID;
			out->Info[i].right = in->Info[i].right;
			out->Info[i].ranking = in->Info[i].ranking;
			out->Info[i].payRate = in->Info[i].payRate;
			memcpy(out->Info[i].posName, in->Info[i].posName, 24);
		}

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_ACK_CHANGE_GUILD_POSITIONINFO,PROTO_ZC_ACK_CHANGE_GUILD_POSITIONINFO::GUILD_REG_POSITION_INFO> in(p);
		TPacket<PACKET_ZC_ACK_CHANGE_GUILD_POSITIONINFO,PACKET_ZC_ACK_CHANGE_GUILD_POSITIONINFO::GUILD_REG_POSITION_INFO> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Info[i].positionID = in->Info[i].positionID;
			out->Info[i].right = in->Info[i].right;
			out->Info[i].ranking = in->Info[i].ranking;
			out->Info[i].payRate = in->Info[i].payRate;
			memcpy(out->Info[i].posName, in->Info[i].posName, 24);
		}

		return out;
	}
};
