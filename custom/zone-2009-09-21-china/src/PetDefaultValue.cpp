#include "PetDefaultValue.h"
#include "struct.hpp"


CPetDefaultValue::CPetDefaultValue(void) // line 14
{
	m_array = new PET_INFO[MAX_PETDEFAULTVALUE_ENTRY];
}


CPetDefaultValue::~CPetDefaultValue(void) // line 20
{
	delete[] m_array;
}


hook_func<void (__cdecl *)(int* x, int iMin, int iMax)> _CHECK_MINMAX(SERVER, "CHECK_MINMAX");
void __cdecl CHECK_MINMAX(int* x, int iMin, int iMax) // line 28
{
	return (_CHECK_MINMAX)(x, iMin, iMax);

	if( *x < iMin )
		*x = iMin;
	else
	if( *x > iMax )
		*x = iMax;
}


hook_method<bool (CPetDefaultValue::*)(const char* szFile)> CPetDefaultValue::_Load(SERVER, "CPetDefaultValue::Load");
bool CPetDefaultValue::Load(const char* szFile) // line 36
{
	return (this->*_Load)(szFile);

	FILE* fp = fopen(szFile, "rt");
	if( fp == NULL )
		return false;

	int i = 0;
	char szBuf[256];
	while( fgets(szBuf, sizeof(szBuf), fp) )
	{
		if( strlen(szBuf) < 3 || szBuf[0] == '/' && szBuf[1] == '/' )
			continue;

		if( ++i >= MAX_PETDEFAULTVALUE_ENTRY )
			return false;

		PET_INFO* p = &m_array[i];

		int iSpecialON;
		if( sscanf(szBuf, "%d, %d,  %d, %d, %d, %d,  %d, %d,  %d, %d, %d, %d, %d", &p->iKind, &p->iCapturePercent, &p->iRIWF, &p->iRDWF, &p->iRD, &p->iRDWD, &p->iSIWF, &p->iSD, &iSpecialON, &p->nAccID, &p->nFoodID, &p->nTrap, &p->nPetEgg) != 13 )
		{
			--i;
			continue;
		}

		CHECK_MINMAX(&p->iCapturePercent, 0, 100);
		CHECK_MINMAX(&p->iRIWF, 1, 1000);
		CHECK_MINMAX(&p->iRDWF, 1, 1000);
		CHECK_MINMAX(&p->iRD, 1, 1000);
		CHECK_MINMAX(&p->iRDWD, 1, 1000);
		CHECK_MINMAX(&p->iSIWF, 1, 100);
		CHECK_MINMAX(&p->iSD, 1, 100);

		p->iRDWF = -p->iRDWF;
		p->iSD   = -p->iSD;
		p->iRD   = -p->iRD;
		p->iRDWD = -p->iRDWD;
		p->bSpecialON = ( iSpecialON == 1 );

		if( !m_table.insert(mystd::pair<int,PET_INFO*>(p->iKind, p)).second )
			return false;
	}

	this->CPetDefaultValue::BuildSet();
	fclose(fp);
	return true;
}


hook_method<PET_INFO* (CPetDefaultValue::*)(int petJob)> CPetDefaultValue::_GetDefaultValue(SERVER, "CPetDefaultValue::GetDefaultValue");
PET_INFO* CPetDefaultValue::GetDefaultValue(int petJob) // line 101
{
	return (this->*_GetDefaultValue)(petJob);

	mystd::map<int,PET_INFO*>::iterator it = m_table.find(petJob);
	return ( it != m_table.end() ) ? it->second : NULL;
}


hook_method<int (CPetDefaultValue::*)(unsigned short itemID, int petJob)> CPetDefaultValue::_IsWearableItem(SERVER, "CPetDefaultValue::IsWearableItem");
int CPetDefaultValue::IsWearableItem(unsigned short itemID, int petJob) // line 112
{
	return (this->*_IsWearableItem)(itemID, petJob);

	PET_INFO* p = this->CPetDefaultValue::GetDefaultValue(petJob);
	return ( p != NULL && itemID == p->nAccID ) ? 1 : 0;
}


hook_method<void (CPetDefaultValue::*)(void)> CPetDefaultValue::_BuildSet(SERVER, "CPetDefaultValue::BuildSet");
void CPetDefaultValue::BuildSet(void) // line 124
{
	return (this->*_BuildSet)();

	for( mystd::map<int,PET_INFO*>::iterator it = m_table.begin(); it != m_table.end(); ++it )
		m_petEggSet.insert(it->second->nPetEgg);
}


hook_method<int (CPetDefaultValue::*)(unsigned short itemID)> CPetDefaultValue::_IsPetEgg(SERVER, "CPetDefaultValue::IsPetEgg");
int CPetDefaultValue::IsPetEgg(unsigned short itemID) // line 149
{
	return (this->*_IsPetEgg)(itemID);

	return ( m_petEggSet.find(itemID) != m_petEggSet.end() );
}
