#include "Enum.h"
#include "ObjectRecycleMgr.h"
#include "PC.h"
#include "AsyncDBWork/LoadCartADBWork.h"
#include "AsyncDBWork/NAsyncDBMgr.h"
#include "AsyncDBWork/SaveCartADBWork.h"
#include "Common/Packet.h"


const char* CPC::GetAccountName() const // 1141-1147
{
	return m_characterInfo.accountName;
}


unsigned long CPC::GetAccountID() // 1151-1153 (791-793)
{
	return m_characterInfo.accountID;
}


unsigned long CPC::GetCharacterID() // 1156-1158 (796-798)
{
	return m_characterInfo.characterID;
}


BOOL CPC::IsValid() // ??? (954.h)
{
	return m_isValid;
}


void CPC::SetValid(const BOOL flag) // ??? (801-803)
{
	m_isValid = flag;
}


char* CPC::GetCharacterName() // ??? (1092.h)
{
	return m_characterInfo.characterName;
}


PCBANG_INFO* CPC::GetPcBangInfo() // ??? (1150.h)
{
	return &m_PCBangInfo;
}


BOOL CPC::IsPcBang() // ??? (1159.h)
{
	return m_PCBangInfo.isPCBang;
}


void CPC::MultiCastStateInfo() // 2877-2887
{
	PACKET_ZC_STATE_CHANGE3 outpacket;
	outpacket.PacketType = HEADER_ZC_STATE_CHANGE3;
	outpacket.AID = m_characterInfo.accountID;
	outpacket.bodyState = static_cast<short>(m_characterPInfo.bodyState);
	outpacket.healthState = static_cast<short>(m_characterPInfo.healthState);
	outpacket.effectState = m_characterPInfo.effectState;
	outpacket.isPKModeON = ( this->CPC::IsPKModeON() != FALSE );

	this->Send(sizeof(outpacket), (char*)&outpacket);
	this->CCharacter::MultiCast((char*)&outpacket, sizeof(outpacket));
}


bool CPC::IsSendable2(const int in_Bytes)
{
	if( !CPC::IsSendable() )
		return false;

	return m_asyncStream->CAsyncStream::IsSendable2(in_Bytes);
}


int CPC::IsSendable() // 5363-5364
{
	return 0;
	//TODO
/*
	return m_pcClientUpdater->CPCClientUpdater::IsSendable();
*/
}


void CPC::AsyncDBComplete_LoadCart(int in_SKLevel, const unsigned char* in_pData, int in_Length) // 6107-6116
{
	//TODO
	/*
	if( m_pcitemInventoryMgr.CPCItemInventoryMgr::ParseDBFmtCartItemData(in_Length, in_pData) != true )
		return;

	m_characterInfo.plusCartspeed = g_skillTypeInfoMgr.CSkillTypeInfoMgr::SendMsg(this, SKID_MC_PUSHCART, SM_GETINFO_SKILL, in_SKLevel, 0, 0, 0) * m_characterInfo.speed / 100;
	m_pcClientUpdater.CPCClientUpdater::NotifyParameter(VAR_SPEED, this->CPC::GetSpeed());
	*/
}


void CPC::AsyncLoadCart(CCharacter* const in_pSender) // 6139-6198
{
	//TODO
	/*
	short skillLv = m_pcSkill.CPCSkill::GetSkillLevel(SKID_MC_PUSHCART, FALSE);
	if( skillLv == 0 )
	{
		skillLv = m_pcSkill.CPCSkill::GetSkillLevel(SKID_DA_MAGICCART, FALSE);
		if( skillLv > 1 )
			skillLv = 1;
	}

	if( in_pSender != NULL )
		this->SetEffective(EFST_ON_PUSH_CART, 9999, 1, 0, 0, FALSE);

	if( skillLv <= 0 )
		return;

	if( m_pcitemInventoryMgr.CPCItemInventoryMgr::IsCartOn() )
	{
		if( m_dwErrorCount < 4 )
			m_pcitemInventoryMgr.CPCItemInventoryMgr::NotifyItemInfo(CART);

		return;
	}

	CLoadCartADBWork* work = CObjectRecycleMgr<CLoadCartADBWork>::Instance()->CObjectRecycleMgr<CLoadCartADBWork>::Get();
	if( work == NULL )
	{
		this->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
		return;
	}

	work->CLoadCartADBWork::Init(this->GetAccountID(), this->CPC::GetCharacterID(), skillLv);
	if( NAsyncDBMgr::GetObj()->NAsyncDBMgr::RequestWork(work) != true )
	{
		CObjectRecycleMgr<CLoadCartADBWork>::Instance()->CObjectRecycleMgr<CLoadCartADBWork>::Put(work);
		this->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
		return;
	}

	this->SetEffective(EFST_NOACTION_WAIT, 40000, work->NAsyncDBWork::GetIdentity(), work->NAsyncDBWork::GetType(), timeGetTime(), 0);
	*/
}


BOOL CPC::IsPKModeON() // 13712-13714
{
	return m_isPKModeON;
}


void CPC::Send(int len, const char* buf) // 15497-15502
{
	if( !this->CPC::IsSendable() )
		return;

	m_lastSendTime = timeGetTime();
	m_asyncStream->CAsyncStream::Send(len, buf);
}


void CPC::ForceSend(int len, char* buf) // 15505-15508
{
	m_lastSendTime = timeGetTime();
	m_asyncStream->CAsyncStream::Send(len, buf);
}


void CPC::GetEfstListDBFmt_And_UpdateResetFlag(std::vector<Effect3rd::tagEffect3rdDBFmt>& io_List, const bool in_bKeepDeleteDBWhenResetFlag) // 22094-22157
{
	//TODO
/*
	DWORD CurTM = timeGetTime();

	for( EFFECTIVE_CONTAINER::iterator iter = m_effectiveList.begin(); iter != m_effectiveList.end(); ++iter )
	{
		int hEfst = iter->first;
		EFFECTIVE_INFO data = iter->second;

		if( !EStateTypeInfoMgr::GetObj()->EStateTypeInfoMgr::IsSave(CurTM, hEfst, &data) )
			continue;

		if( hEfst == EFST_MACRO_PERMIT )
		{
			EFFECTIVE_INFO* info = this->CActor::GetEffectiveInfo(EFST_MACRO_PLAY);
			if( info != NULL && info->val[0] != 0 )
			{
				DWORD delta = timeGetTime() - info->val[0];
				data.val[0] = ( delta < data.val[0] ) ? data.val[0] - delta : 0;
			}
		}

		DWORD TimeMS = ( data.time != 9999 ) ? data.time - CurTM : 0;
		if( TimeMS == 9999 )
			TimeMS = 9998;

		io_List.push_back(Effect3rd::tagEffect3rdDBFmt(hEfst, TimeMS, data.val[0], data.val[1], data.val[2]);

		if( !in_bKeepDeleteDBWhenResetFlag )
			iter->second.bDeleteDBWhenReset = TRUE;
	}
*/
}


void CPC::AsyncSaveCart() // 25507-25555
{
	//TODO
/*
	if( !m_pcitemInventoryMgr.m_cartItem.m_isFirstCartOn )
		return;

	CSaveCartADBWork* work = CObjectRecycleMgr<CSaveCartADBWork>::Instance()->CObjectRecycleMgr<CSaveCartADBWork>::Get();
	if( work == NULL )
		return;

	work->CSaveCartADBWork::Init(this->GetAccountID(), this->CPC::GetCharacterID());
	work->m_Length = m_pcitemInventoryMgr->CPCItemInventoryMgr::GetCartItemDBFormat(work->m_Data, sizeof(work->m_Data));
	if( !NAsyncDBMgr::GetObj()->NAsyncDBMgr::RequestWork(work) )
		CObjectRecycleMgr<CSaveCartADBWork>::Instance()->CObjectRecycleMgr<CSaveCartADBWork>::Put(work);
*/
}


hook_func<int (CPC::*)(int index, int time, int val1, int val2, int val3, int isSendClient)> CPC__SetEffective(EXEPATH(), "CPC::SetEffective");
int CPC::SetEffective(int index, int time, int val1, int val2, int val3, int isSendClient) // 8003-9697 (PC2_2(1).cpp)
{
	return (this->*CPC__SetEffective)(index, time, val1, val2, val3, isSendClient);

	//TODO
}


hook_func<int (CPC::*)(CCharacter* sender, CCharacter* receiver, unsigned long msgID, int par1, int par2, int par3, MSGpar::CVar par4)> CPC__OnMsg(EXEPATH(), "CPC::OnMsg");
int CPC::OnMsg(CCharacter* sender, CCharacter* receiver, unsigned long msgID, int par1, int par2, int par3, MSGpar::CVar par4) // 1690-2841 (PCMsg.cpp)
{
	return (this->*CPC__OnMsg)(sender, receiver, msgID, par1, par2, par3, par4);

	//TODO
}
