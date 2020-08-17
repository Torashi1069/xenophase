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
	void InitPacketLenWithClient();
	void InitPacketLenWithClientSecure();
	void InitPacketLen();

private:
	class CData
	{
	public:
		/* this+0 */ const int m_Len;
		/* this+4 */ const int m_Min;
		/* this+8 */ const int m_ReplayFactor;

	public:
		CData(const int, const int); //TODO
		CData(const int in_Len, const int in_Min, const int in_ReplayFactor) : m_Len(in_Len), m_Min(in_Min), m_ReplayFactor(in_ReplayFactor) { }
	};

private:
	typedef std::map<int,CPacketLengthExMgr::CData> LENGTHMAPEX;
	/* this+0 */ LENGTHMAPEX m_LengthMap;

public:
	CPacketLengthExMgr();
	~CPacketLengthExMgr();
};
