#pragma once
class CCharacter;
class CMapRes;


struct NEIGHBORHOOD_SECTION
{
	std::vector<CCharacter*>* section[4];
};


class CSectionMgr
{
public:
	CSectionMgr();
	virtual ~CSectionMgr();

public:
	void Init(const char* mapName, int w, int h, int scale, const CMapRes* mapRes);
	std::vector<CCharacter*>* GetSectionByCellPos(int x, int y);
	BOOL GetEmptyPosition(unsigned long AID, int& xPos, int& yPos);
	BOOL AddCharacter(int x, int y, CCharacter* ch);
	void RemoveCharacter(CCharacter* ch);
	int GetTotalSectionSize();
	BOOL MoveCharacter(std::vector<CCharacter*>* src, std::vector<CCharacter*>* dst, CCharacter* ch);
	int MoveChracter(std::vector<CCharacter*>* src, std::vector<CCharacter*>::iterator& iter, int x, int y, CCharacter* ch);
	void GetNeighborhoodSections(int x, int y, int range, NEIGHBORHOOD_SECTION* result);
	int GetSectionSize();
	std::vector<CCharacter*>** GetSectionList();

private:
	BOOL IsEmptyPos(unsigned long AID, int xPos, int yPos);
	std::vector<CCharacter*>* GetSectionListPtr(const int in_X, const int in_Y, const int in_Range, const int in_Idx);

private:
	/* this+ 0 */ //const CSectionMgr::`vftable';
	/* this+ 4 */ int m_w;
	/* this+ 8 */ int m_h;
	/* this+12 */ int m_scale;
	/* this+16 */ std::vector<CCharacter*>** m_sectionList;
	/* this+20 */ const CMapRes* m_mapRes;
	/* this+24 */ char m_mapName[16];
	/* this+40 */ int m_MaxSectionList;

	friend class CMapRes; // IsEmptyPos()
};
