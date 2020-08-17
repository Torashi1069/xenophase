#pragma once
#include "std/map"
#include "std/set"
struct PET_INFO;


class CPetDefaultValue
{
public:
	enum { MAX_PETDEFAULTVALUE_ENTRY = 256 };

	/* this+ 0 */ public: //const CPetDefaultValue::`vftable';
	/* this+ 4 */ protected: PET_INFO* m_array;
	/* this+ 8 */ protected: mystd::map<int,PET_INFO*> m_table;
	/* this+20 */ protected: mystd::set<int> m_accSet;
	/* this+32 */ protected: mystd::set<int> m_petEggSet;

	public: CPetDefaultValue::CPetDefaultValue(void);
	public: virtual CPetDefaultValue::~CPetDefaultValue(void);
	protected: void CPetDefaultValue::BuildSet(void);
	public: bool CPetDefaultValue::Load(const char* szFile);
	public: PET_INFO* CPetDefaultValue::GetDefaultValue(int petJob);
	public: int CPetDefaultValue::IsWearableItem(unsigned short itemID, int petJob);
	public: int CPetDefaultValue::IsPetEgg(unsigned short itemID);

private:
	static hook_method<void (CPetDefaultValue::*)(void)> CPetDefaultValue::_BuildSet;
	static hook_method<bool (CPetDefaultValue::*)(const char* szFile)> CPetDefaultValue::_Load;
	static hook_method<PET_INFO* (CPetDefaultValue::*)(int petJob)> CPetDefaultValue::_GetDefaultValue;
	static hook_method<int (CPetDefaultValue::*)(unsigned short itemID, int petJob)> CPetDefaultValue::_IsWearableItem;
	static hook_method<int (CPetDefaultValue::*)(unsigned short itemID)> CPetDefaultValue::_IsPetEgg;
};
