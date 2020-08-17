#pragma once


class NOutputTextMgr
{
public:
	bool isOK() const;
	void Insert(const std::string in_msg);
	void InsertFmt(const char* in_pFmt, ...);
	unsigned int GetMaxLineCnt();
	std::string GetText(const unsigned int in_LineCnt);

public:
	static bool CreateInstance();
	static void DestroyInstance();
	static NOutputTextMgr* GetObj();

private:
	NOutputTextMgr();
	~NOutputTextMgr();

private:
	/* this+ 0 */ bool m_bOK;
	/* this+ 4 */ unsigned int m_LineCnt;
	/* this+ 8 */ RTL_CRITICAL_SECTION m_CS;
	/* this+32 */ std::map<unsigned int,std::vector<char>> m_Note;
	/* static  */ static NOutputTextMgr* m_cpSelf;
};
