#pragma once
class CPC;


class CPCItem
{
public:
	CPCItem();
	virtual ~CPCItem();

public:
	void Init();
	void SetMyOwner(CPC* pc);
	BOOL ParseItem(const char* buf, short len);
	BOOL ParseStoredItem(const char* buf, short len);
	BOOL ParseCartItem(const char* buf, short len);
	void CheckStateSpecialItem();
	void OnEquipedSpecialITM(unsigned long itmID);
	void OnTakeOffSpecialITM(unsigned long itmID);
	void RefreshEquipItem();
	int GetCombinationItemCount();

private:
	BOOL IsEquipedSPItem(unsigned long ID);
	void CHK_CompleteCombination();
	void CHK_ReleaseCombination();

private:
	/* this+ 0 */ //const CPCItem::`vftable';
	/* this+ 4 */ CPC* m_pc;
	/* this+ 8 */ std::map<unsigned short,unsigned short> m_equipedSPItem;
	/* this+24 */ std::map<unsigned short,int> m_isCombination;
};
