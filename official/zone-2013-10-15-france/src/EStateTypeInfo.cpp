#include "EStateTypeInfo.h"


ESTATE::ESTATE(const int in_EfstID, const std::string in_Name)
: m_EfstID(in_EfstID), m_name(in_Name),
  m_isResetDead(false), m_isResetDispel(false), m_isSave(false), m_isSend(false), m_isSendMultiCast(false), m_isIgnorePretendDead(false),
  m_isDeBuff(false), m_isResetCLEARANCE(false), m_isActorAppearance(false), m_isBackwardCompatibilitySend(false), m_isResetMADOGEAR(false)
{
}


ESTATE::~ESTATE()
{
}


bool ESTATE::IsExistScript()
{
	return false;
}


bool ESTATE::IsGC_POISON() const
{
	return false;
}


RESET_EFST_TYPE ESTATE::IsWANDERERandMINSTRELoverlapDeny() const
{
	return RESET_EFST_WANDERERandMINSTREL_OVERLAPDENY_GROUP_NONE;
}


void ESTATE::SetComplete(CActor* in_cpActor, const int in_Time, const int in_Val1, const int in_Val2, const int in_Val3)
{
}


bool ESTATE::SetCheckup(CActor* in_cpActor, int& io_Time, int& io_Val1, int& io_Val2, int& io_val3)
{
	return true;
}


bool ESTATE::ResetCheckup(CActor* in_cpActor, const int in_Val, EFFECTIVE_INFO* io_pInfo)
{
	return true;
}


void ESTATE::ResetComplete(CActor* in_cpActor, const int in_Val1, const int in_Val2, const int in_Val3)
{
}


void ESTATE::Process(CActor* in_cpActor, EFFECTIVE_INFO* const io_pInfo)
{
}


const std::string ESTATE::GetName() const
{
	return m_name;
}


const int ESTATE::GetID() const
{
	return m_EfstID;
}


bool ESTATE::IsDeBuff() const
{
	return m_isDeBuff;
}


void ESTATE::SetDeBuff(bool in_isDeBuff)
{
	m_isDeBuff = in_isDeBuff;
}


bool ESTATE::IsSave() const
{
	return m_isSave;
}


void ESTATE::SetSave(bool in_isSave)
{
	m_isSave = in_isSave;
}


bool ESTATE::IsResetDead() const
{
	return m_isResetDead;
}


void ESTATE::SetResetDead(bool in_isResetDead)
{
	m_isResetDead = in_isResetDead;
}


bool ESTATE::IsResetDispel() const
{
	return m_isResetDispel;
}


void ESTATE::SetResetDispel(bool in_isResetDispel)
{
	m_isResetDispel = in_isResetDispel;
}


bool ESTATE::IsResetCLEARANCE() const
{
	return m_isResetCLEARANCE;
}


void ESTATE::SetResetCLEARANCE(bool in_isResetCLEARANCE)
{
	m_isResetCLEARANCE = in_isResetCLEARANCE;
}


bool ESTATE::IsResetMADOGEAR() const
{
	return m_isResetMADOGEAR;
}


void ESTATE::SetResetMADOGEAR(const bool in_isResetMADOGEAR)
{
	m_isResetMADOGEAR = in_isResetMADOGEAR;
}


bool ESTATE::IsIgnorePretendDead() const
{
	return m_isIgnorePretendDead;
}


void ESTATE::SetIgnorePretendDead(bool in_isIgnorePretendDead)
{
	m_isIgnorePretendDead = in_isIgnorePretendDead;
}


bool ESTATE::IsResetPretendDead() const
{
	if( m_isIgnorePretendDead )
		return false;

	return m_isResetDead;
}


void ESTATE::SetSend(bool in_isSend)
{
	m_isSend = in_isSend;
}


void ESTATE::SetSendMultiCast(const bool in_isSendMultiCast)
{
	m_isSendMultiCast = in_isSendMultiCast;
}


bool ESTATE::IsSend2() const
{
	return m_isSend;
}


bool ESTATE::IsSendMultiCast() const
{
	return m_isSendMultiCast;
}


bool ESTATE::IsActorAppearance() const
{
	return m_isActorAppearance;
}


void ESTATE::SetActorAppearance(bool in_isActorAppearance)
{
	m_isActorAppearance = in_isActorAppearance;
}


void ESTATE::SetBackwardCompatibilitySend(const bool in_isBackwardCompatibilitySend)
{
	m_isBackwardCompatibilitySend = in_isBackwardCompatibilitySend;
}


bool ESTATE::IsBackwardCompatibilitySend() const
{
	return m_isBackwardCompatibilitySend;
}


////////////////////////////////////////


ESTATE_SCRIPT::ESTATE_SCRIPT(const int in_EfstID, const std::string in_Name)
: ESTATE(in_EfstID, in_Name)
{
}


ESTATE_SCRIPT::~ESTATE_SCRIPT()
{
}


bool ESTATE_SCRIPT::IsExistScript()
{
	return true;
}


void ESTATE_SCRIPT::AddScript(int in_EventType, int int_scriptPos)
{
	m_scriptPos[in_EventType] = int_scriptPos;
}


int ESTATE_SCRIPT::GetScriptPos(int in_EventType)
{
	std::map<unsigned long,unsigned long>::iterator iter = m_scriptPos.find(in_EventType);
	if( iter == m_scriptPos.end() )
		return -1;

	return iter->second;
}
