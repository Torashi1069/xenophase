struct PROTO_CZ_REQ_OPENSTORE
{
	short PacketType;
	short PacketLength;
	char storeName[80];
	bool result; // true:open, false:cancelled
	struct PRODUCTINFO_INSTORE // guessed
	{
		short index;
		short count;
		int price;
	}
	Item[];
};


struct PACKET_CZ_REQ_OPENSTORE
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short PacketLength;
	/* this+ 4 */ char storeName[80];
	/* this+84 */ struct PRODUCTINFO_INSTORE
	              {
	              	/* this+0 */ short index;
	              	/* this+2 */ short count;
	              	/* this+4 */ int price;
	              }
	              Item[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_REQ_OPENSTORE,PACKET_CZ_REQ_OPENSTORE::PRODUCTINFO_INSTORE> in(p);
		TPacket<PROTO_CZ_REQ_OPENSTORE,PROTO_CZ_REQ_OPENSTORE::PRODUCTINFO_INSTORE> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		memcpy(out->storeName, in->storeName, 80);
		out->result = true; // adapt

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Item[i].index = in->Item[i].index;
			out->Item[i].count = in->Item[i].count;
			out->Item[i].price = in->Item[i].price;
		}

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_REQ_OPENSTORE,PROTO_CZ_REQ_OPENSTORE::PRODUCTINFO_INSTORE> in(p);
		TPacket<PACKET_CZ_REQ_OPENSTORE,PACKET_CZ_REQ_OPENSTORE::PRODUCTINFO_INSTORE> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		memcpy(out->storeName, in->storeName, 80);
//		out->result = in->result; // adapt

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Item[i].index = in->Item[i].index;
			out->Item[i].count = in->Item[i].count;
			out->Item[i].price = in->Item[i].price;
		}

		return out;
	}
};


struct PACKET_CZ_REQ_OPENSTORE2
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short PacketLength;
	/* this+ 4 */ char storeName[80];
	/* this+84 */ bool result;
	/* this+85 */ struct PRODUCTINFO_INSTORE
	              {
	              	/* this+0 */ short index;
	              	/* this+2 */ short count;
	              	/* this+4 */ int price;
	              }
	              Item[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_REQ_OPENSTORE2,PACKET_CZ_REQ_OPENSTORE2::PRODUCTINFO_INSTORE> in(p);
		TPacket<PROTO_CZ_REQ_OPENSTORE,PROTO_CZ_REQ_OPENSTORE::PRODUCTINFO_INSTORE> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		memcpy(out->storeName, in->storeName, 80);
		out->result = in->result;

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Item[i].index = in->Item[i].index;
			out->Item[i].count = in->Item[i].count;
			out->Item[i].price = in->Item[i].price;
		}

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_REQ_OPENSTORE,PROTO_CZ_REQ_OPENSTORE::PRODUCTINFO_INSTORE> in(p);
		TPacket<PACKET_CZ_REQ_OPENSTORE2,PACKET_CZ_REQ_OPENSTORE2::PRODUCTINFO_INSTORE> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		memcpy(out->storeName, in->storeName, 80);
		out->result = in->result;

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Item[i].index = in->Item[i].index;
			out->Item[i].count = in->Item[i].count;
			out->Item[i].price = in->Item[i].price;
		}

		return out;
	}
};
