#pragma once
#include "Actor.h"


class ESTATE
{
public:
	virtual bool IsExistScript();
	virtual bool IsGC_POISON() const;
	virtual RESET_EFST_TYPE IsWANDERERandMINSTRELoverlapDeny() const;
	virtual void SetComplete(CActor* in_cpActor, const int in_Time, const int in_Val1, const int in_Val2, const int in_Val3);
	virtual bool SetCheckup(CActor* in_cpActor, int& io_Time, int& io_Val1, int& io_Val2, int& io_val3);
	virtual bool ResetCheckup(CActor* in_cpActor, const int in_Val, EFFECTIVE_INFO* io_pInfo);
	virtual void ResetComplete(CActor* in_cpActor, const int in_Val1, const int in_Val2, const int in_Val3);
	virtual void Process(CActor* in_cpActor, EFFECTIVE_INFO* const io_pInfo);
	const std::string GetName() const;
	const int GetID() const;
	bool IsDeBuff() const;
	void SetDeBuff(bool in_isDeBuff);
	bool IsSave() const;
	void SetSave(bool in_isSave);
	bool IsResetDead() const;
	void SetResetDead(bool in_isResetDead);
	bool IsResetDispel() const;
	void SetResetDispel(bool in_isResetDispel);
	bool IsResetCLEARANCE() const;
	void SetResetCLEARANCE(bool in_isResetCLEARANCE);
	bool IsResetMADOGEAR() const;
	void SetResetMADOGEAR(const bool in_isResetMADOGEAR);
	bool IsIgnorePretendDead() const;
	void SetIgnorePretendDead(bool in_isIgnorePretendDead);
	virtual bool IsResetPretendDead() const;
	void SetSend(bool in_isSend);
	void SetSendMultiCast(const bool in_isSendMultiCast);
	bool IsSend2() const;
	bool IsSendMultiCast() const;
	bool IsActorAppearance() const;
	void SetActorAppearance(bool in_isActorAppearance);
	void SetBackwardCompatibilitySend(const bool in_isBackwardCompatibilitySend);
	bool IsBackwardCompatibilitySend() const;

public:
	ESTATE(const int in_EfstID, const std::string in_Name);
	virtual ~ESTATE();

protected:
	/* this+ 0 */ //const ESTATE::`vftable';
	/* this+ 4 */ const int m_EfstID;
	/* this+ 8 */ const std::string m_name;
	/* this+36 */ bool m_isResetDead;
	/* this+37 */ bool m_isResetDispel;
	/* this+38 */ bool m_isSave;
	/* this+39 */ bool m_isSend;
	/* this+40 */ bool m_isSendMultiCast;
	/* this+41 */ bool m_isIgnorePretendDead;
	/* this+42 */ bool m_isDeBuff;
	/* this+43 */ bool m_isResetCLEARANCE;
	/* this+44 */ bool m_isActorAppearance;
	/* this+45 */ bool m_isBackwardCompatibilitySend;
	/* this+46 */ bool m_isResetMADOGEAR;
};


class ESTATE_SCRIPT : public ESTATE
{
public:
	virtual bool IsExistScript();
	void AddScript(int in_EventType, int int_scriptPos);
	int GetScriptPos(int in_EventType);

public:
	ESTATE_SCRIPT(const int in_EfstID, const std::string in_Name);
	virtual ~ESTATE_SCRIPT();

private:
	/* this+ 0 */ //ESTATE baseclass_0;
	/* this+48 */ std::map<unsigned long,unsigned long> m_scriptPos;
};
