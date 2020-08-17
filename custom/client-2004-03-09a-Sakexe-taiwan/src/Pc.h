#pragma once
#include "GameActor.h"
#include "Struct.h"
class CSprRes;
class CActRes;
class UIPcGage;


class CPc : public CGameActor
{
	struct vtable_t
	{
		void* (CPc::* scalar_deleting_destructor)(unsigned int flags);
		bool (CPc::* OnProcess)(void);
		void (CPc::* SendMsg)(CGameObject* sender, int message, int arg1, int arg2, int arg3);
		void (CPc::* Render)(matrix& ptm);
		int (CGameActor::* Get8Dir)(float rot);
		void (CGameActor::* SetRenderInfo)(RENDER_INFO_RECT& info, const float tlvertX, const float tlvertY);
		void (CRenderObject::* SetTlvert)(float tlvertX, float tlvertY);
		void (CGameActor::* SetAction)(int action, int speed, int type);
		void (CRenderObject::* ProcessMotion)(void);
		bool (CPc::* ProcessState)(void);

		void (CPc::* SetState)(int stateId);
		void (CGameActor::* RegisterPos)(void);
		void (CGameActor::* UnRegisterPos)(void);
		void (CGameActor::* SetSprAct)(int job, int sex);
		void (CPc::* SetSprAct_)(int job, int sex, int head, int weapon, int accessory, int accessory2, int accessory3, int shield, int headPal, int bodyPal);
		void (CPc::* SetSprAct2)(int job, int sex, int head, int weapon, int accessory, int accessory2, int accessory3, int shield, int headPal, int bodyPal, int effectState);
		void (CPc::* SetSprJob)(int job);
		void (CPc::* SetSprHead)(int head);
		void (CPc::* SetSprJobDye)(int job);
		void (CPc::* SetSprWeapon)(int weapon);

		void (CPc::* SetSprWeapon2)(int weapon);
		void (CPc::* SetSprAccessory)(int accessory);
		void (CPc::* SetSprAccessory2)(int accessory);
		void (CPc::* SetSprAccessory3)(int accessory);
		void (CPc::* SetSprShield)(int shield);
		void (CPc::* SetSprShoe)(int shoe);
		void (CPc::* SetImfFileName)(void);
		void (CPc::* SetHeadPaletteName)(void);
		void (CPc::* SetBodyPaletteName)(void);
		void (CPc::* SetBodyPalette)(int bodyPalette);

		void (CPc::* SetHeadPalette)(int headPalette);
		int (CPc::* GetWeapon)(void);
		void (CGameActor::* ProcessMotionWithDist)(void);
		int (CGameActor::* GetAttackMotion)(void);
		void (CGameActor::* MakeCorpse)(void);
		void (CPc::* SetModifyFactorOfmotionSpeed)(int attackM);
		void (CPc::* SetHonor)(int honor);
		void (CPc::* SetPropensityInfo)(int honor, int virtue);
		void (CGameActor::* SetGuildInfo)(int gdid, int emblemVersion);
		int (CGameActor::* GetGdid)(void);

		int (CGameActor::* GetEmblemVersion)(void);
	};

	/* this+  0 */ public: //CGameActor baseclass_0;
	/* this+684 */ protected: mystd::string m_imfName;
	/* this+700 */ protected: int m_honor;
	/* this+704 */ protected: int m_virtue;
	/* this+708 */ protected: int m_headDir;
	/* this+712 */ protected: int m_head;
	/* this+716 */ protected: int m_headPalette;
	/* this+720 */ protected: int m_weapon;
	/* this+724 */ protected: int m_accessory;
	/* this+728 */ protected: int m_accessory2;
	/* this+732 */ protected: int m_accessory3;
	/* this+736 */ protected: int m_shield;
	/* this+740 */ protected: int m_shoe;
	/* this+744 */ protected: int m_shoe_count;
	/* this+748 */ protected: vector3d shoe_pos;
	/* this+760 */ protected: int m_renderWithoutLayer;
	/* this+764 */ protected: mystd::string m_headPaletteName;
	/* this+780 */ protected: UIPcGage* m_gage;
	/* this+784 */ protected: long m_pk_rank;
	/* this+788 */ protected: long m_pk_total;
	/* this+792 */ private: mystd::vector<CSprRes*> m_sprResList;
	/* this+808 */ private: mystd::vector<CActRes*> m_actResList;

	public: CPc::CPc(void);
	public: virtual CPc::~CPc(void);
	public: void CPc::OnInit(void);
	public: void CPc::OnExit(void);
	public: virtual bool CPc::OnProcess(void);
	public: virtual bool CPc::ProcessState(void);
	public: virtual void CPc::SetState(int stateId);
	public: virtual void CPc::Render(matrix& ptm);
	public: virtual void CPc::SetSprAct(int job, int sex, int head, int weapon, int accessory, int accessory2, int accessory3, int shield, int headPal, int bodyPal);
	public: virtual void CPc::SetSprAct2(int job, int sex, int head, int weapon, int accessory, int accessory2, int accessory3, int shield, int headPal, int bodyPal, int effectState);
	public: virtual void CPc::SetSprJob(int job);
	public: virtual void CPc::SetSprHead(int head);
	public: virtual void CPc::SetSprJobDye(int job);
	public: virtual void CPc::SetSprWeapon(int weapon);
	public: virtual void CPc::SetSprWeapon2(int weapon);
	public: virtual void CPc::SetSprAccessory(int accessory);
	public: virtual void CPc::SetSprAccessory2(int accessory);
	public: virtual void CPc::SetSprAccessory3(int accessory);
	public: virtual void CPc::SetSprShield(int shield);
	public: virtual void CPc::SetSprShoe(int shoe);
	public: virtual void CPc::SetImfFileName(void);
	public: virtual void CPc::SetHeadPaletteName(void);
	public: virtual void CPc::SetBodyPaletteName(void);
	public: virtual int CPc::GetWeapon(void);
	public: virtual void CPc::SetModifyFactorOfmotionSpeed(int attackM);
	public: virtual void CPc::SendMsg(CGameObject* sender, int message, int arg1, int arg2, int arg3);
	public: virtual void CPc::SetBodyPalette(int bodyPalette);
	public: virtual void CPc::SetHeadPalette(int headPalette);
	public: virtual void CPc::SetHonor(int honor);
	public: virtual void CPc::SetPropensityInfo(int honor, int virtue);
	public: long CPc::GetPKRank(void);
	public: long CPc::GetPKTotal(void);
	public: void CPc::SetPKRank(int rank);
	public: void CPc::SetPKTotal(int total);
	public: void CPc::RenderBody2(matrix& vtm, int isBlur);
	public: void CPc::RenderBodyLayer(matrix& vtm, int isBlur);
	public: void CPc::RenderShadowLayer(matrix& vtm);
	public: void CPc::ProcessGage(void);
	public: void CPc::SetRank(int Total, int Rank);
	public: const mystd::vector<mystd::string> CPc::GetSprNames(void);
	public: void CPc::SetSprNames(const mystd::vector<mystd::string>& sprNames);
	public: const mystd::vector<mystd::string> CPc::GetActNames(void);
	public: void CPc::SetActNames(const mystd::vector<mystd::string>& actNames);
	public: const mystd::string& CPc::GetImfNames(void);
	public: int CPc::GetHeadPalette(void);
	public: mystd::string CPc::GetHeadPaletteName(void);
	public: void CPc::RenderShoe(int shoenum);
	protected: void CPc::SetSprNameList(int layer, const char* sprName);
	protected: const char* CPc::GetSprNameList(int layer);
	protected: CSprRes* CPc::GetSprResList(int layer);
	protected: void CPc::SetActNameList(int layer, const char* actName);
	protected: const char* CPc::GetActNameList(int layer);
	protected: CActRes* CPc::GetActResList(int layer);
	protected: int CPc::MakeWeaponType(int left, int right);

private:
	static hook_method<void (CPc::*)(void)> CPc::_OnInit;
	static hook_method<void (CPc::*)(void)> CPc::_OnExit;
	static hook_method<bool (CPc::*)(void)> CPc::_OnProcess;
	static hook_method<bool (CPc::*)(void)> CPc::_ProcessState;
	static hook_method<void (CPc::*)(int stateId)> CPc::_SetState;
	static hook_method<void (CPc::*)(matrix& ptm)> CPc::_Render;
	static hook_method<void (CPc::*)(int job, int sex, int head, int weapon, int accessory, int accessory2, int accessory3, int shield, int headPal, int bodyPal)> CPc::_SetSprAct;
	static hook_method<void (CPc::*)(int job, int sex, int head, int weapon, int accessory, int accessory2, int accessory3, int shield, int headPal, int bodyPal, int effectState)> CPc::_SetSprAct2;
	static hook_method<void (CPc::*)(int job)> CPc::_SetSprJob;
	static hook_method<void (CPc::*)(int head)> CPc::_SetSprHead;
	static hook_method<void (CPc::*)(int job)> CPc::_SetSprJobDye;
	static hook_method<void (CPc::*)(int weapon)> CPc::_SetSprWeapon;
	static hook_method<void (CPc::*)(int weapon)> CPc::_SetSprWeapon2;
	static hook_method<void (CPc::*)(int accessory)> CPc::_SetSprAccessory;
	static hook_method<void (CPc::*)(int accessory)> CPc::_SetSprAccessory2;
	static hook_method<void (CPc::*)(int accessory)> CPc::_SetSprAccessory3;
	static hook_method<void (CPc::*)(int shield)> CPc::_SetSprShield;
	static hook_method<void (CPc::*)(int shoe)> CPc::_SetSprShoe;
	static hook_method<void (CPc::*)(void)> CPc::_SetImfFileName;
	static hook_method<void (CPc::*)(void)> CPc::_SetHeadPaletteName;
	static hook_method<void (CPc::*)(void)> CPc::_SetBodyPaletteName;
	static hook_method<int (CPc::*)(void)> CPc::_GetWeapon;
	static hook_method<void (CPc::*)(int attackM)> CPc::_SetModifyFactorOfmotionSpeed;
	static hook_method<void (CPc::*)(CGameObject* sender, int message, int arg1, int arg2, int arg3)> CPc::_SendMsg;
	static hook_method<void (CPc::*)(int bodyPalette)> CPc::_SetBodyPalette;
	static hook_method<void (CPc::*)(int headPalette)> CPc::_SetHeadPalette;
	static hook_method<void (CPc::*)(int honor)> CPc::_SetHonor;
	static hook_method<void (CPc::*)(int honor, int virtue)> CPc::_SetPropensityInfo;
	static hook_method<long (CPc::*)(void)> CPc::_GetPKRank;
	static hook_method<long (CPc::*)(void)> CPc::_GetPKTotal;
	static hook_method<void (CPc::*)(int rank)> CPc::_SetPKRank;
	static hook_method<void (CPc::*)(int total)> CPc::_SetPKTotal;
	static hook_method<void (CPc::*)(matrix& vtm, int isBlur)> CPc::_RenderBody2;
	static hook_method<void (CPc::*)(matrix& vtm, int isBlur)> CPc::_RenderBodyLayer;
	static hook_method<void (CPc::*)(matrix& vtm)> CPc::_RenderShadowLayer;
	static hook_method<void (CPc::*)(void)> CPc::_ProcessGage;
	static hook_method<void (CPc::*)(int Total, int Rank)> CPc::_SetRank;
	static hook_method<const mystd::vector<mystd::string> (CPc::*)(void)> CPc::_GetSprNames;
	static hook_method<void (CPc::*)(const mystd::vector<mystd::string>& sprNames)> CPc::_SetSprNames;
	static hook_method<const mystd::vector<mystd::string> (CPc::*)(void)> CPc::_GetActNames;
	static hook_method<void (CPc::*)(const mystd::vector<mystd::string>& actNames)> CPc::_SetActNames;
	static hook_method<const mystd::string& (CPc::*)(void)> CPc::_GetImfNames;
	static hook_method<int (CPc::*)(void)> CPc::_GetHeadPalette;
	static hook_method<mystd::string (CPc::*)(void)> CPc::_GetHeadPaletteName;
	static hook_method<void (CPc::*)(int shoenum)> CPc::_RenderShoe;
	static hook_method<void (CPc::*)(int layer, const char* sprName)> CPc::_SetSprNameList;
	static hook_method<const char* (CPc::*)(int layer)> CPc::_GetSprNameList;
	static hook_method<CSprRes* (CPc::*)(int layer)> CPc::_GetSprResList;
	static hook_method<void (CPc::*)(int layer, const char* actName)> CPc::_SetActNameList;
	static hook_method<const char* (CPc::*)(int layer)> CPc::_GetActNameList;
	static hook_method<CActRes* (CPc::*)(int layer)> CPc::_GetActResList;
	static hook_method<int (CPc::*)(int left, int right)> CPc::_MakeWeaponType;
};


class CBlurPC : public CPc
{
	struct vtable_t
	{
		//TOOD
	};

	/* this+  0 */ public: //CPc baseclass_0;
	/* this+824 */ protected: float m_motionY;
	/* this+828 */ protected: unsigned long m_alphaDelta;
	/* this+832 */ protected: unsigned long m_r;
	/* this+836 */ protected: unsigned long m_g;
	/* this+840 */ protected: unsigned long m_b;

	public: CBlurPC::CBlurPC(CPc* pc);
	public: virtual CBlurPC::~CBlurPC(void);
	public: void CBlurPC::OnInit(void);
	public: void CBlurPC::OnExit(void);
	public: virtual bool CBlurPC::OnProcess(void);
	public: virtual void CBlurPC::Render(matrix& ptm);
	public: virtual void CBlurPC::SendMsg(CGameObject* sender, int message, int arg1, int arg2, int arg3);

private:
	static hook_method<void (CBlurPC::*)(void)> CBlurPC::_OnInit;
	static hook_method<void (CBlurPC::*)(void)> CBlurPC::_OnExit;
	static hook_method<bool (CBlurPC::*)(void)> CBlurPC::_OnProcess;
	static hook_method<void (CBlurPC::*)(matrix& ptm)> CBlurPC::_Render;
	static hook_method<void (CBlurPC::*)(CGameObject* sender, int message, int arg1, int arg2, int arg3)> CBlurPC::_SendMsg;
};
