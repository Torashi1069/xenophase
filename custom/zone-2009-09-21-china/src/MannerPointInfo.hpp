#pragma once
#include "std/list"
class CPC;


struct MannerPointData
{
	/* this+0 */ unsigned long otherGID;
	/* this+4 */ unsigned long type;
};


struct MannerPointInfo
{
	/* this+ 0 */ private: int m_lastTimeGivingMP;
	/* this+ 4 */ private: mystd::list<MannerPointData> m_info;
	/* this+16 */ private: CPC* m_owner;

	public: void MannerPointInfo::Init(CPC* pc);
	public: void MannerPointInfo::Reset(void);
	public: unsigned long MannerPointInfo::IsGivableMP(unsigned long otherGID);
	public: int MannerPointInfo::LoadMPInfo(void);
	public: void MannerPointInfo::InsertNewMP(unsigned long otherGID, int type);
	private: int MannerPointInfo::SearchOtherCharacter(unsigned long otherGID);
	private: int MannerPointInfo::GetSize(void);
	private: int MannerPointInfo::DeleteFirstRecord(void);
};
