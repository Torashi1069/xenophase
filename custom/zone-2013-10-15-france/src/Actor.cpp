#include "Actor.h"
#include "Enum.h"


CActor::CActor() // 51-52
{
}


CActor::~CActor() // 55-57
{
}


void CActor::Init() // 79-97
{
	//TODO
/*
	this->CCharacter::Init();
	m_FixedSKcasingTMvar.CFixedSKcastingTMvar::Init();
	m_Scheduler.MapResScheduler::CScheduler::Init();
	m_MspdSlowPercentEfstList.clear();
	m_MspdHastePercentEfstList.clear();
	m_AspdSlowPercentEfstList.clear();
	m_AspdHastePercentEfstList.clear();
*/
}


bool CActor::IsActor() // ??
{
	return true;
}


int CActor::GetStateDBFmt(unsigned char* out_pData, const int in_MaxBytes) const // 107-171
{
	class CStateDBTime
	{
	private:
		/* this+0 */ //const CStateDBTime::`vftable';
		/* this+4 */ const DWORD m_CutTime;

	public:
		DWORD operator()(DWORD in_StateTime) // 112-121
		{
			if( in_StateTime == 9999 )
				return 9999;

			if( in_StateTime <= m_CutTime )
				return 0;

			DWORD outTime = (in_StateTime - m_CutTime) / 1000;
			if( outTime == 9999 )
				outTime = 9998;
			return outTime;
		}

	public:
		CStateDBTime() : m_CutTime(timeGetTime()) { }
		virtual ~CStateDBTime() { }
	};

	CStateDBTime GetStateDBTime;
	int offset = 0;

	*(WORD*)(out_pData + offset + 0) = static_cast<WORD>(m_BodyStateValue);
	*(WORD*)(out_pData + offset + 2) = static_cast<WORD>(GetStateDBTime(m_BodyStateTime[1]));
	offset += 4;

	for( int i = 0; i < 9; ++i )
	{
		if( offset > in_MaxBytes - 4 )
			break; // no more room.

		if( m_HealthStateTime[i][1] != 0 )
		{
			*(WORD*)(out_pData + offset + 0) = 1 << i;
			*(WORD*)(out_pData + offset + 2) = static_cast<WORD>(GetStateDBTime(m_HealthStateTime[i][1]));
			offset += 4;
		}
	}

	*(WORD*)(out_pData + offset) = -1;
	offset += 2;

	for( EFFECTSTATEMAP::const_iterator iter = m_effectStateTimeL.begin(); iter != m_effectStateTimeL.end(); ++iter )
	{
		if( offset > in_MaxBytes - 6 )
			break; // no more room.

		int mask = iter->first;
		if( mask == EFFECTSTATE_BURROW ) //TODO: verify
			continue;

		if( m_characterPInfo.effectState & mask )
		{
			*(DWORD*)(out_pData + offset + 0) = mask;
			*( WORD*)(out_pData + offset + 4) = static_cast<WORD>(GetStateDBTime(iter->second));
			offset += 6;
		}
	}

	return offset;
}
