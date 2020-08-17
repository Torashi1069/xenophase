struct PROTO_CA_LOGIN
{
	short PacketType; // PROTOID_CA_LOGIN
	unsigned long Version; // g_version == g_nVersion[clienttype]
	char ID[24];
	char Passwd[24];
	unsigned char clienttype; // enum CLIENTTYPE_*
	char IP[15+1];
	char MacAdress[12+1];
};


struct PACKET_CA_LOGIN
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long Version;
	/* this+ 6 */ unsigned char ID[24];
	/* this+30 */ unsigned char Passwd[24];
	/* this+54 */ unsigned char clienttype;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CA_LOGIN> in(p);
		TPacket<PROTO_CA_LOGIN> out;

		out->PacketType = PacketType;
		out->Version = in->Version;
		memcpy(out->ID, in->ID, 24);
		memcpy(out->Passwd, in->Passwd, 24);
		out->clienttype = in->clienttype;
		memcpy(out->IP, "111.111.111.111", 15+1); // adapt
		memcpy(out->MacAdress, "111111111111", 12+1); // adapt

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CA_LOGIN> in(p);
		TPacket<PACKET_CA_LOGIN> out;

		out->PacketType = PacketType;
		out->Version = in->Version;
		memcpy(out->ID, in->ID, 24);
		memcpy(out->Passwd, in->Passwd, 24);
		out->clienttype = in->clienttype;
//		memcpy(out->IP, in->IP, 15+1); // adapt
//		memcpy(out->MacAdress, in->MacAdress, 12+1); // adapt

		return out;
	}
};


struct PACKET_CA_LOGIN_PCBANG
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long Version;
	/* this+ 6 */ unsigned char ID[24];
	/* this+30 */ unsigned char Passwd[24];
	/* this+54 */ unsigned char clienttype;
	/* this+55 */ char IP[15+1];
	/* this+71 */ unsigned char MacAdress[12+1];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CA_LOGIN_PCBANG> in(p);
		TPacket<PROTO_CA_LOGIN> out;

		out->PacketType = PacketType;
		out->Version = in->Version;
		memcpy(out->ID, in->ID, 24);
		memcpy(out->Passwd, in->Passwd, 24);
		out->clienttype = in->clienttype;
		memcpy(out->IP, in->IP, 15+1);
		memcpy(out->MacAdress, in->MacAdress, 12+1);

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CA_LOGIN> in(p);
		TPacket<PACKET_CA_LOGIN_PCBANG> out;

		out->PacketType = PacketType;
		out->Version = in->Version;
		memcpy(out->ID, in->ID, 24);
		memcpy(out->Passwd, in->Passwd, 24);
		out->clienttype = in->clienttype;
		memcpy(out->IP, in->IP, 15+1);
		memcpy(out->MacAdress, in->MacAdress, 12+1);

		return out;
	}
};


//TODO
struct PACKET_CA_LOGIN_HAN
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long Version;
	/* this+ 6 */ unsigned char ID[24];
	/* this+30 */ unsigned char Passwd[24];
	/* this+54 */ unsigned char clienttype;
	/* this+55 */ char m_szIP[15+1];
	/* this+71 */ unsigned char m_szMacAddr[12+1];
	/* this+84 */ unsigned char isHanGameUser; // unknown
};


struct PACKET_CA_LOGIN_CHANNEL
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long Version;
	/* this+ 6 */ unsigned char ID[24];
	/* this+30 */ unsigned char Passwd[24];
	/* this+54 */ unsigned char clienttype;
	/* this+55 */ char m_szIP[15+1];
	/* this+71 */ unsigned char m_szMacAddr[12+1];
	/* this+84 */ unsigned char Channeling_Corp;  // unknown

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CA_LOGIN_CHANNEL> in(p);
		TPacket<PROTO_CA_LOGIN> out;

		out->PacketType = PacketType;
		out->Version = in->Version;
		memcpy(out->ID, in->ID, 24);
		memcpy(out->Passwd, in->Passwd, 24);
		out->clienttype = in->clienttype;
		memcpy(out->IP, in->m_szIP, 15+1);
		memcpy(out->MacAdress, in->m_szMacAddr, 12+1);

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CA_LOGIN> in(p);
		TPacket<PACKET_CA_LOGIN_CHANNEL> out;

		out->PacketType = PacketType;
		out->Version = in->Version;
		memcpy(out->ID, in->ID, 24);
		memcpy(out->Passwd, in->Passwd, 24);
		out->clienttype = in->clienttype;
		memcpy(out->m_szIP, in->IP, 15+1);
		memcpy(out->m_szMacAddr, in->MacAdress, 12+1);
		out->Channeling_Corp = 0; // FIXME

		return out;
	}
};
