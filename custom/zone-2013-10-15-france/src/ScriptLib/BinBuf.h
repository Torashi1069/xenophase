#pragma once


class CBinBuf
{
public:
	CBinBuf();
	~CBinBuf();

public:
	void Clear();
	bool Load(char* fName);
	char* GetBase();
	int GetSize();

private:
	/* this+0 */ char* m_buf;
	/* this+4 */ int m_bufSize;
};
