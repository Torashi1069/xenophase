#pragma once


class CBlockIPListMng
{
public:
//	CBlockIPListMng();
//	CBlockIPListMng(int, int);
//	~CBlockIPListMng();
//	void SetMaxLimitAccessNum(const int, const int);
//	int IsBlock(unsigned long);
//	bool Delete(unsigned long);
//	int Bring(unsigned long);
//	int Get(unsigned long);
//	void Disconnect(unsigned long);
//	int GetBlockCount(bool);
//	void Clear();

private:
	/* this+ 0 */ std::map<DWORD,int> m_mapConnectedIPList;
	/* this+16 */ std::map<DWORD,int> m_mapConnectedPCBonusIPList;
	/* this+32 */ int m_nMaxNumBlockingUserInEachIP;
	/* this+36 */ int m_nMaxNumBlockingUserInPCBonusIP;
	/* this+40 */ RTL_CRITICAL_SECTION m_cs;
};
