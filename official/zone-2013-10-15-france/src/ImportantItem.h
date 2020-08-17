#pragma once


class CImportantItem
{
public:
	CImportantItem();
	~CImportantItem();

public:
	void LoadImportantItem();
	BOOL IsImportantItem(DWORD dwItemID);

private:
	/* this+0 */ std::map<DWORD,DWORD> m_mapImportantItem;
};
