#pragma once
class CPC;


class CPCClientUpdater
{
public:
	CPCClientUpdater();
	virtual ~CPCClientUpdater();

public:
	void SetMyOwner(CPC* pc);
	void Init();
	void SetAccountID(int AccountID);
	void SetCharacterID(int CharacterID);
//	void SetAccountName(const char* );
//	void SetCharacterName(const char* );
	void SetAuthCode(int AuthCode);
	void SetSendable(BOOL isActive);
//	void InitPosition(int , int , unsigned char );
	void SetIndex(int index);
	BOOL IsMyArea(CCharacter* other, int Range);
	BOOL IsMyArea(CCharacter* other, int xRange, int yRange);
//	int AddSectionMgr();
//	void RemoveSectionMgr();
//	void SaveCharUsingTime();
//	int IsNeighborhood(int , int , int , int , int* , int* );
	int MapMove(const char* mapName, short xPos, short yPos, unsigned long NAID, int type);
private:
//	int MapMove_SameServer(const char* , short , short );
//	int MapMove_OtherServer(const int , const char* , short , short , const unsigned long );
//	bool MapMove_OtherServer_Part1(const unsigned long , const int );
public:
	void MapMove_OtherServer_Part2(const unsigned long in_NAID, const int in_TargetSvrID);
	void OnDead(unsigned long enemyAID);
//	void PCDataMoveToPVP();
	unsigned long GetAccountID();
	unsigned long GetCharacterID();
//	void SetParameterPointValue();
	int GetAuthCode();
	int GetErrorCount(); //TODO
	void NotifyParameter(unsigned short type, int count);
//	int GetParPointValue(char );
	void ReStart(unsigned long NAID);
	BOOL IsSendable();

public:
	/* this+4 */ unsigned char m_disconnectType;

public:
//	void NotifyDisconnect();
//	int GetSPHealVelocity();
//	int GetHPHealVelocity();
//	int GetStatusUpgradeCost(const int );
	void StopMove();
//	void NotifyStopMove(const bool );
//	void NotifyStatuePlusInfo();
//	void ReleaseEffectState();
//	void CatchInfo(unsigned long );
//	void CatchInfoRemove(unsigned long );
//	void RestartAtCampBase(unsigned long );

private:
	/* this+8 */ CPC* m_pc;

private:
//	void UpdateCharacter(std::vector<CCharacter*>* );
//	void OnClearDialog(int );
//	void OnDialog(int , int , int );
//	void OnWaitDialog(int );
//	void OnCloseDialog(int );
//	void OnNavigationActive(int , int , int );
//	void OnProgress(unsigned long , unsigned long );
//	void OnPorgressCancel();
//	void OnMenuList(int , int , int );
	void NotifyLongParameter(unsigned short varID, int amount);
//	void NotifyBan(const unsigned long , const int );
//	int UpdateState(unsigned char , unsigned char );
//	void IncreaseJobPoint(short );
//	void IncreaseSkillPoint(short );
//	void ReqStatus();
//	void NotifyUpdateInfo(CPC* );
//	void NotifyMoveToNeighborCharacter();
//	void Pause(unsigned long );
//	void Reset();
//	void OnWhisper(int , short , char* );
//	void OnWhisper_2(int , short , char* );
//	void OnWhisperAck(unsigned  char);
//	void OnUserCount(int );
//	void OnChat(CCharacter* , int , char* );
//	void NotifyStatusParameter(unsigned long , int , int );
//	void NotifyRankingInfo(CPC* );
//	void NotifySpiritsInfo(CPC* );
	void NotifySpriteChange(CPC* other, int type, int value); // enumSPRITETYPE
//	void AckStatusToGM(CPC* );
//	void NotifyBattleFieldCampInfo(CPC* );
//	void BroadcastHP();
//	void NotifyMillenniumShieldInfo(CPC* , short );
//	void NotifyForceOfVanguardInfo(CPC* , short );
//	void NotifyOptionalInfo(CPC* , int );

	friend class CPC; // NotifyParameter()
};
