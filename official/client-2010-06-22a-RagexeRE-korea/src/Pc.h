#pragma once
#include "GameActor.h"
#include "3dLib/Prim.h"
#include "std/string"
#include "std/vector"
class CActRes;
class CSprRes;
class UIPcGage;


class CPc : public CGameActor
{
public:
	CPc();
	virtual ~CPc();
	void OnInit();
	void OnExit();
	virtual bool OnProcess();
	virtual void SendMsg(CGameObject* sender, int message, int arg1, int arg2, int arg3);
	virtual void Render(matrix& vtm);
	virtual bool ProcessState();
	virtual void SetState(int stateId);
	virtual void SetSprAct(int job, int sex, int head, int weapon, int accessory, int accessory2, int accessory3, int shield, int headPal, int bodyPal);
	virtual void SetSprAct2(int job, int sex, int head, int weapon, int accessory, int accessory2, int accessory3, int shield, int headPal, int bodyPal, int effectState);
	virtual void SetSprJob(int job);
	virtual void SetSprHead(int head);
	virtual void SetSprJobDye(int job);
	virtual void SetSprWeapon(int weapon);
	virtual void SetSprWeapon2(int weapon);
	virtual void SetSprAccessory(int accessory);
	virtual void SetSprAccessory2(int accessory2);
	virtual void SetSprAccessory3(int accessory3);
	virtual void SetSprShield(int shield);
	virtual void SetSprShoe(int shoe);
	virtual void SetImfFileName();
	virtual void SetHeadPaletteName();
	virtual void SetBodyPaletteName();
	virtual void SetBodyPalette(int bodyPalette);
	virtual void SetHeadPalette(int headPalette);
	virtual int GetWeapon();
	virtual void SetModifyFactorOfmotionSpeed(int attackM);
	virtual void SetHonor(int honor);
	virtual void SetPropensityInfo(int honor, int virtue);

	void RenderBody2(matrix& vtm, int isBlur);
	void RenderBodyLayer(matrix& vtm, int isBlur, bool arg3_2010);
	void RenderShoe(int shoenum);

protected:
	/* this+  0 */ //CGameActor baseclass_0;
	/* this+856 */ mystd::string m_imfName;
	/* this+872 */ int m_honor;
	/* this+876 */ int m_virtue;
	/* this+880 */ int m_headDir;
	/* this+884 */ int m_head;
	/* this+888 */ int m_headPalette;
	/* this+892 */ int m_weapon;
	/* this+896 */ int m_accessory;
	/* this+900 */ int m_accessory2;
	/* this+904 */ int m_accessory3;
	/* this+908 */ int m_shield;
	/* this+912 */ int m_shoe;
	/* this+916 */ int m_shoe_count;
	/* this+920 */ vector3d shoe_pos;
	/* this+932 */ int m_renderWithoutLayer;
	/* this+936 */ mystd::string m_headPaletteName;
	/* this+952 */ UIPcGage* m_gage;
	/* this+956 */ long m_pk_rank;
	/* this+960 */ long m_pk_total;
private:
	/* this+964 */ mystd::vector<CSprRes*> m_sprResList;
	/* this+980 */ mystd::vector<CActRes*> m_actResList;

public:
	static hook_func<CPc* (CPc::*)()> CPc::_cCPc;
	static hook_func<void (CPc::*)()> CPc::_dCPc;
	static hook_func<void (CPc::*)()> CPc::_OnInit;
	static hook_func<void (CPc::*)()> CPc::_OnExit;
	static hook_func<bool (CPc::*)()> CPc::_OnProcess;
	static hook_func<void (CPc::*)(CGameObject* sender, int message, int arg1, int arg2, int arg3)> CPc::_SendMsg;
	static hook_func<void (CPc::*)(matrix& vtm)> CPc::_Render;
	static hook_func<bool (CPc::*)()> CPc::_ProcessState;
	static hook_func<void (CPc::*)(int stateId)> CPc::_SetState;
	static hook_func<void (CPc::*)(int job, int sex, int head, int weapon, int accessory, int accessory2, int accessory3, int shield, int headPal, int bodyPal)> CPc::_SetSprAct;
	static hook_func<void (CPc::*)(int job, int sex, int head, int weapon, int accessory, int accessory2, int accessory3, int shield, int headPal, int bodyPal, int effectState)> CPc::_SetSprAct2;
	static hook_func<void (CPc::*)(int job)> CPc::_SetSprJob;
	static hook_func<void (CPc::*)(int head)> CPc::_SetSprHead;
	static hook_func<void (CPc::*)(int job)> CPc::_SetSprJobDye;
	static hook_func<void (CPc::*)(int weapon)> CPc::_SetSprWeapon;
	static hook_func<void (CPc::*)(int weapon)> CPc::_SetSprWeapon2;
	static hook_func<void (CPc::*)(int accessory)> CPc::_SetSprAccessory;
	static hook_func<void (CPc::*)(int accessory2)> CPc::_SetSprAccessory2;
	static hook_func<void (CPc::*)(int accessory3)> CPc::_SetSprAccessory3;
	static hook_func<void (CPc::*)(int shield)> CPc::_SetSprShield;
	static hook_func<void (CPc::*)(int shoe)> CPc::_SetSprShoe;
	static hook_func<void (CPc::*)()> CPc::_SetImfFileName;
	static hook_func<void (CPc::*)()> CPc::_SetHeadPaletteName;
	static hook_func<void (CPc::*)()> CPc::_SetBodyPaletteName;
	static hook_func<void (CPc::*)(int bodyPalette)> CPc::_SetBodyPalette;
	static hook_func<void (CPc::*)(int headPalette)> CPc::_SetHeadPalette;
	static hook_func<int (CPc::*)()> CPc::_GetWeapon;
	static hook_func<void (CPc::*)(int attackM)> CPc::_SetModifyFactorOfmotionSpeed;
	static hook_func<void (CPc::*)(int honor)> CPc::_SetHonor;
	static hook_func<void (CPc::*)(int honor, int virtue)> CPc::_SetPropensityInfo;

	static hook_func<void (CPc::*)(matrix& vtm, int isBlur)> CPc::_RenderBody2;
	static hook_func<void (CPc::*)(matrix& vtm, int isBlur, bool arg3_2010)> CPc::_RenderBodyLayer;
	static hook_func<void (CPc::*)(int shoenum)> CPc::_RenderShoe;
};
C_ASSERT( sizeof CPc == 996 );


class CBlurPC : public CPc
{
	/* this+   0 */ public: //CPc baseclass_0;
	/* this+ 996 */ protected: float m_motionY;
	/* this+1000 */ protected: unsigned long m_alphaDelta;
	/* this+1004 */ protected: unsigned long m_r;
	/* this+1008 */ protected: unsigned long m_g;
	/* this+1012 */ protected: unsigned long m_b;

	public: CBlurPC::CBlurPC(CPc* pc);
	public: CBlurPC::~CBlurPC(void); //virtual
	public: void CBlurPC::Render(matrix& ptm); //virtual

public:
	static hook_func<CBlurPC* (CBlurPC::*)(CPc* pc)> CBlurPC::_cCBlurPC;
	static hook_func<void (CBlurPC::*)(void)> CBlurPC::_dCBlurPC;
	static hook_func<void (CBlurPC::*)(matrix& ptm)> CBlurPC::_Render;
};
C_ASSERT( sizeof CBlurPC == 1016 );
