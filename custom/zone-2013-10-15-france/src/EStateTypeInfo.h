#pragma once


class ESTATE
{
public:
//	bool IsExistScript();
//	bool IsGC_POISON();
//	enum RESET_EFST_TYPE IsWANDERERandMINSTRELoverlapDeny();
//	void SetComplete(class CActor *, const int, const int, const int, const int);
//	bool SetCheckup(class CActor *, int &, int &, int &, int &);
//	bool ResetCheckup(class CActor *, const int, struct EFFECTIVE_INFO *);
//	void ResetComplete(class CActor *, const int, const int, const int);
//	void Process(class CActor *, struct EFFECTIVE_INFO * const);
//	const std::string GetName();
//	const int GetID();
//	bool IsDeBuff();
//	void SetDeBuff(bool);
//	bool IsSave();
//	void SetSave(bool);
//	bool IsResetDead();
//	void SetResetDead(bool);
//	bool IsResetDispel();
//	void SetResetDispel(bool);
//	bool IsResetCLEARANCE();
//	void SetResetCLEARANCE(bool);
//	bool IsResetMADOGEAR();
//	void SetResetMADOGEAR(const bool);
//	bool IsIgnorePretendDead();
//	void SetIgnorePretendDead(bool);
//	bool IsResetPretendDead();
//	void SetSend(bool);
//	void SetSendMultiCast(const bool);
//	bool IsSend2();
//	bool IsSendMultiCast();
//	bool IsActorAppearance();
//	void SetActorAppearance(bool);
//	void SetBackwardCompatibilitySend(const bool);
//	bool IsBackwardCompatibilitySend();

public:
//	ESTATE(const int , const std::string );
//	~ESTATE();

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
