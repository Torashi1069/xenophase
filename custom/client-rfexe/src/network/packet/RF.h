#include "Version.h"


struct PACKET_CA_LOGIN_RF
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long Version;
	/* this+ 6 */ unsigned char ID[24];
	/* this+30 */ unsigned char Passwd[24];
	/* this+54 */ unsigned char clienttype;
	/* this+55 */ unsigned long exe_hash;
	/* this+59 */ unsigned long dll_hash;
	/* this+63 */ unsigned long server_ip;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		return NULL; // not implemented
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CA_LOGIN> in(p);
		TPacket<PACKET_CA_LOGIN_RF> out;

		out->PacketType = PacketType;
		out->Version = in->Version;
		memcpy(out->ID, in->ID, 24);
		memcpy(out->Passwd, in->Passwd, 24);
		out->clienttype = in->clienttype;
		out->exe_hash = EXEHASH();
		out->dll_hash = DLLHASH();
		out->server_ip = inet_addr("192.95.8.138"); // fake

		return out;
	}
};
