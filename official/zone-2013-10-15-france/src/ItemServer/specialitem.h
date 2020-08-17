#pragma once


struct SpecialItemEvent
{
	/* this+0 */ int beginPos;
	/* this+4 */ std::list<int> varList;
};


class CSpecialItem
{
public:
	CSpecialItem();
	virtual ~CSpecialItem();

public:
	SpecialItemEvent* CreateEvent(int eventCode, int beginPos);
	bool DestroyEvent(int eventCode);
	bool GetEvent(int eventCode, SpecialItemEvent*& eventRet);

private:
	/* this+0 */ //const CSpecialItem::`vftable';
	/* this+4 */ std::map<int,SpecialItemEvent*> m_eventMap;
};
