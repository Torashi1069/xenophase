#pragma once


class CQuestEventInfo
{
public:
	typedef mystd::vector<int> TLIST_HUNT;

public:
	CQuestEventInfo();
	virtual ~CQuestEventInfo();

public:
	/* this+ 0 */ //const CPCQuestEvent::`vftable';
	/* this+ 4 */ unsigned long m_qID;
	/* this+ 8 */ bool m_activ;
	/* this+12 */ TLIST_HUNT m_huntList;
	/* this+28 */ bool m_isTimeMission;
	/* this+32 */ long m_startTime;
	/* this+36 */ long m_misTime;

public:
//	void Initialize();
//	void SetQuest(unsigned long);
//	void SetActiv(bool);
//	void SetHuntList(int);
//	void SetPlayTime(long, long, bool);
//	unsigned long GetQID();
//	bool GetActiv();
//	int GetHuntList(TLIST_HUNT&);
//	int GetHuntCount();
//	long GetPlayStartTime();
//	long GetPlayEndingTime();
//	bool IsTimeQuset();
//	void ClearQuest();
};
