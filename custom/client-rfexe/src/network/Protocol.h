#pragma once
#include "Packet.hpp"
#include "packet/COPY.h"
#include "ProtocolID.h" // enum PROTOID
#include <map>


// Basic packet layout (fixed-length).
struct PACKET
{
	/* this+0 */ short PacketType;
	/* this+2 */ BYTE Data[];
};


// Basic packet layout (variable-length).
struct PACKETV
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ BYTE Data[];
};


/// Packet adapter function prototype.
typedef Packet* (AdapterFunc)(short PacketType, Packet* p);


struct PacketInfo
{
	short PacketType;       // protocol-specific type
	PROTOID ProtoID;        // universal type
	unsigned short Len;     // length (total/minimal)
	bool isVariable;        // type (fixed/variable)
	AdapterFunc* ToProto;   // input -> proto
	AdapterFunc* FromProto; // proto -> output
};


class Protocol
{
public:
	Protocol(const char* name);
	void Init();

	// Info on specific packets.
	const PacketInfo* GetInfo(short PacketType) const;

	// Info on initial raw packet sent.
	const PacketInfo* GetFirstRawPacketInfo() const;
	void SetFirstRawPacketInfo(short PacketType);

	// Packet adapter operations.
	Packet* ToProto(Packet* p) const;
	Packet* FromProto(Packet* p) const;

protected:
	// Packet registration.
	void Register(short PacketType, PROTOID ProtoID, unsigned short Len, bool isVariable, AdapterFunc* ToProto, AdapterFunc* FromProto);

	// Instance-specific initialization callback.
	virtual void InitInstance();

private:
	std::map<short,PacketInfo> m_map;           // packet info storage
	std::multimap<PROTOID,PacketInfo*> m_proto; // reverse lookup
	const PacketInfo* m_rawpacket;              // first raw packet info
	const char* m_name;                         // for debugging purposes
	bool m_initialized;                         // only initialize once
};


/// Forward declared template for individual protocol instances.
namespace {
class ProtocolImpl : public Protocol
{
public:
	ProtocolImpl(const char* name) : Protocol(name) { };
	virtual void InitInstance();
};
}; // namespace


// Convenient macros for packet registration
#define REG0(P) { Register(0, P, 0, false, NULL, NULL); }
#define REGN_2(id,len) { Register(id, PROTOID_COPY, len, false, &PACKET_COPY::ToProto, &PACKET_COPY::FromProto); }
#define REGV_2(id,len) { Register(id, PROTOID_COPY, len, true,  &PACKET_COPY::ToProto, &PACKET_COPY::FromProto); }
#define REGN_3(id,len,H) { Register(id, PROTOID_COPY, len, false, &PACKET_COPY::ToProto, &PACKET_COPY::FromProto); }
#define REGV_3(id,len,H) { Register(id, PROTOID_COPY, len, true,  &PACKET_COPY::ToProto, &PACKET_COPY::FromProto); }
#define REGN_5(id,len,H,P,T) { Register(id, P, len, false, &T::ToProto, &T::FromProto); C_ASSERT(len == sizeof(T)); }
#define REGV_5(id,len,H,P,T) { Register(id, P, len, true,  &T::ToProto, &T::FromProto); C_ASSERT(len == -1 || len == sizeof(T)); }

// Nasty hack wrapper to do macro overloading.
#define N_ARGS_IMPL(_1, _2, _3, _4, _5, _N, ...) _N
#define N_ARGS_GLUE(args) N_ARGS_IMPL args
#define N_ARGS(...) N_ARGS_GLUE((__VA_ARGS__, 5, 4, 3, 2, 1, 0))

#define CHOOSER2(F,N) F##N
#define CHOOSER1(F,N) CHOOSER2(F,N)
#define CHOOSER(F,N)  CHOOSER1(F,N)

#define REG_GLUE(x, y) x y
#define REGN(...) REG_GLUE(CHOOSER(REGN_,N_ARGS(__VA_ARGS__)), (__VA_ARGS__))
#define REGV(...) REG_GLUE(CHOOSER(REGV_,N_ARGS(__VA_ARGS__)), (__VA_ARGS__))
//
