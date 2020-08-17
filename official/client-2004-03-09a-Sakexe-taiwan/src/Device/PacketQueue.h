#pragma once


class CPacketQueue
{
public:
	CPacketQueue();
	CPacketQueue(int capacity);
	~CPacketQueue();

public:
	void Init(int capacity);
	int GetSize() const;
	void InsertData(int len, const char* src);
	bool GetData(int len, char* dst);
	bool PeekData(int len, char* dst) const;
	bool RemoveData(int len);
	int GetSafeDataLen();
	char* GetDataPtr();

private:
	/* this+ 0 */ char* m_buf;
	/* this+ 4 */ int m_frontPos;
	/* this+ 8 */ int m_rearPos;
	/* this+12 */ mystd::vector<char> m_buffer;
};
