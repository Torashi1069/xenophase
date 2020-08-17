#pragma once


class CPacketLengthExMgr
{
public:
	enum enumFixedPacketRet { VARIABLE = 0, FIXED = 1, UNKNOWN = -1 };

public:
	mystd::pair<CPacketLengthExMgr::enumFixedPacketRet,int> IsFixedPacket(const int in_Header) const;
	BOOL GetReplayFactor(const int in_Header) const;

private:
	void Add(int in_Header, int in_Length, int in_MinLength, int in_ReplayFactor);
	void InitPacketLenWithClient();

private:
	class CData
	{
	public:
		/* this+0 */ const int m_Len;            // total length (-1 for variable-length packets)
		/* this+4 */ const int m_Min;            // minimal length (same as total length for fixed-length packets)
		/* this+8 */ const BOOL m_ReplayFactor;  // ???

	public:
		CData(const int , const int ); //TODO
		CData(const int in_Len, const int in_Min, const int in_ReplayFactor) : m_Len(in_Len), m_Min(in_Min), m_ReplayFactor(in_ReplayFactor) { }
		~CData() { }
	};

private:
	typedef mystd::map<int,CData> LENGTHMAPEX;
	/* this+0 */ LENGTHMAPEX m_LengthMap;

public:
	CPacketLengthExMgr();
	~CPacketLengthExMgr();
};
