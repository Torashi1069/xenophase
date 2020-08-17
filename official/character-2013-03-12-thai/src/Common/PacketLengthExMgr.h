#pragma once


class CPacketLengthExMgr
{
public:
	enum enumFixedPacketRet { VARIABLE = 0, FIXED = 1, UNKNOWN = -1 };

public:
	std::pair<CPacketLengthExMgr::enumFixedPacketRet,int> IsFixedPacket(const int in_Header) const;
	int GetReplayFactor(const int in_Header) const;

private:
	void Add(const int in_Header, const int in_Length, const int in_MinLength, const int in_ReplayFactor);
	void InitPacketLen();
	void InitPacketLenWithClient();
	void InitPacketLenWithClientSecure();

private:
	class CData
	{
	public:
		/* this+0 */ const int m_Len;
		/* this+4 */ const int m_Min;
		/* this+8 */ const int m_ReplayFactor;

	public:
//		CData(const int, const int);
		CData(const int in_Len, const int in_Min, const int in_ReplayFactor) : m_Len(in_Len), m_Min(in_Min), m_ReplayFactor(in_ReplayFactor) {}
	};

private:
	/* this+0 */ std::map<int,CData> m_LengthMap;

public:
	CPacketLengthExMgr();
	~CPacketLengthExMgr();
};


extern CPacketLengthExMgr g_packetLenMapEx;
