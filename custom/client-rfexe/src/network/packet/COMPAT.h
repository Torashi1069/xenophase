/// 
/// Rejects V2 status change end packets, hopefully downgrading them to V1.
/// Fixes equipwnd's 'off' button still being shown after cart-off in clients that use the new EFST_ON_PUSH_CART system,
///   but only have the full cartoff logic for the V1 packet, because that's what the zone sends on status change end.
/// 
struct PACKET_ZC_MSG_STATE_CHANGE2__COMPAT_DOWNGRADE_SC_END
{
	BYTE dummy[sizeof(PACKET_ZC_MSG_STATE_CHANGE2)];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		return PACKET_ZC_MSG_STATE_CHANGE2::ToProto(PacketType, p);
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_MSG_STATE_CHANGE> in(p);
		if( in->state == false ) return NULL;

		return PACKET_ZC_MSG_STATE_CHANGE2::FromProto(PacketType, p);
	}
};
