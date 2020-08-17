#pragma once


class N3DataTransferMgr
{
public:
	bool isOK() const;
	unsigned int Put(std::vector<unsigned char>& in_Data);
	unsigned int Put(std::string in_Str);
	std::vector<unsigned char> Get(unsigned int in_Key);
	std::string GetStr(unsigned int in_Key);

public:
	static bool CreateInstance();
	static void DestroyInstance();
	static N3DataTransferMgr* GetObj(); /// @custom

private:
	N3DataTransferMgr();
	virtual ~N3DataTransferMgr();
	N3DataTransferMgr(N3DataTransferMgr&); // = delete;
	N3DataTransferMgr& operator=(N3DataTransferMgr&); // = delete;

private:
	/* static */ static N3DataTransferMgr*& m_cpSelf; //TODO
	/* this+0 */ //const N3DataTransferMgr::`vftable';
	/* this+4 */ bool m_bOK;
	/* this+8 */ RTL_CRITICAL_SECTION m_CS;

private:
	class lcData
	{
	public:
		lcData() { };
		lcData(std::vector<unsigned char>& in_data, unsigned long in_Time) : m_data(in_data), m_Time(in_Time) { };
		virtual ~lcData() { };

	public:
		/* this+ 0 */ //const lcData::`vftable';
		/* this+ 4 */ std::vector<unsigned char> m_data;
		/* this+20 */ unsigned long m_Time;
	};

private:
	typedef std::map<unsigned int,N3DataTransferMgr::lcData> DATAMAP;
	/* this+32 */ DATAMAP m_DataMap;

private:
	enum { DATA_GUARANTEE_TIME_SEC = 30 };
};
