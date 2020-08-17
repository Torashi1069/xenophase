#pragma once


class AClassIPMap
{
public:
//	AClassIPMap();
//	bool add(DWORD);
//	bool remove(DWORD);
//	bool isInclude(DWORD);

private:
	enum { MAX_MAP_BUFFER = 0x200000 };
	/* this+0 */ BYTE mMap[MAX_MAP_BUFFER];
};


class BClassIPMap
{
public:
//	BClassIPMap();
//	bool add(WORD);
//	bool remove(WORD);
//	bool isInclude(WORD);

private:
	enum { MAX_MAP_BUFFER = 0x2000 };
	/* this+0 */ BYTE mMap[MAX_MAP_BUFFER];
};


class CClassIPMap
{
public:
//	CClassIPMap();
//	bool add(BYTE);
//	bool remove(BYTE);
//	bool isInclude(BYTE);

private:
	enum { MAX_MAP_BUFFER = 0x20 };
	/* this+0 */ BYTE mMap[MAX_MAP_BUFFER];
};


class IPBean
{
public:
	IPBean(const char* ip);
//	IPBean(DWORD);
//	const IPBean& operator =(const IPBean&);
//	const char* toString();
//	static const char* toString(DWORD);
//	operator DWORD();
//	DWORD addr();
//	DWORD hostbyteorder();
//	bool operator <(const IPBean&);
//	bool operator >(const IPBean&);
//	bool operator <=(const IPBean&);
//	bool operator >=(const IPBean&);
//	bool operator ==(const IPBean&);
//	bool operator !=(const IPBean&);
//	IPBean operator ++(int);
//	const IPBean& operator ++();
//	IPBean operator --(int);
//	const IPBean& operator --();

public:
	/* static */ static IPBean Null;

private:
	/* this+0 */ DWORD mIP;
};


class IPRange
{
public:
//	IPRange();
//	IPRange(const IPBean&, const IPBean&);
//	const IPBean& start();
//	const IPBean& end();
//	bool isInclude(const IPBean&);
//	bool isInclude(const IPRange&);
//	static bool isInclude(const IPBean&, const IPBean&, const IPBean&);
//	bool isNull();

private:
	/* this+0 */ IPBean mStartIP;
	/* this+4 */ IPBean mEndIP;
};


class IPMap
{
public:
	IPMap();
	~IPMap();
//	bool add(const IPBean&);
//	bool add(const IPRange&);
//	bool remove(const IPBean&);
//	bool remove(const IPRange&);
//	bool isInclude(const IPBean&);

public:
	enum
	{
		UINT8_MAX = 0x100,
		UINT16_MAX = 0x10000,
		TOLERABLE_SOLT = 5,
	};

private:
	/* this+0 */ BClassIPMap* mBClassIPMap[UINT16_MAX];
};
