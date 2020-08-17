#include "CITP.hpp"
#include "NPC.h"
#include "PC.h"
#include "CharacterMgr.h"
#include "CPCBattle.hpp"
#include "CSkillTypeInfoMgr.hpp"
#include "ZoneProcess.h" // GetServerRandom()
#include "Common/Packet.h"
#include "Custom/umage.hpp" // ModifyDamage_Emperium()


CPCBattle::CPCBattle(void)
{
}


CPCBattle::~CPCBattle(void)
{
}


hook_method<void (CPCBattle::*)(void)> CPCBattle::_Init(SERVER, "CPCBattle::Init");
void CPCBattle::Init(void)
{
	return (this->*_Init)();

	m_pc = 0;
	CPCBattle::Reset();
}


hook_method<void (CPCBattle::*)(void)> CPCBattle::_Reset(SERVER, "CPCBattle::Reset");
void CPCBattle::Reset(void)
{
	return (this->*_Reset)();

	//TODO
}


//hook_method<void (CPCBattle::*)(CPC* pc)> CPCBattle::_SetMyOwner(SERVER, "CPCBattle::SetMyOwner");
void CPCBattle::SetMyOwner(CPC* pc)
{
//	return (this->*_SetMyOwner)(pc);

	m_pc = pc;
}


hook_method<void (CPCBattle::*)(void)> CPCBattle::_CheckStateChange(SERVER, "CPCBattle::CheckStateChange");
void CPCBattle::CheckStateChange(void)
{
	return (this->*_CheckStateChange)();

	//TODO
}


hook_method<void (CPCBattle::*)(int ID)> CPCBattle::_CheckConsumedArrow(SERVER, "CPCBattle::CheckConsumedArrow");
void CPCBattle::CheckConsumedArrow(int ID)
{
	return (this->*_CheckConsumedArrow)(ID);

	//TODO
}


hook_method<void (CPCBattle::*)(int SKID, int AID, int SKInfo)> CPCBattle::_ActSkillToChar_ATK(SERVER, "CPCBattle::ActSkillToChar_ATK");
void CPCBattle::ActSkillToChar_ATK(int SKID, int AID, int SKInfo)
{
	return (this->*_ActSkillToChar_ATK)(SKID, AID, SKInfo);

	//TODO
}


hook_method<void (CPCBattle::*)(int SKID, int tarAID, int SKInfo)> CPCBattle::_OPSkillToCharacter(SERVER, "CPCBattle::OPSkillToCharacter");
void CPCBattle::OPSkillToCharacter(int SKID, int tarAID, int SKInfo)
{
	return (this->*_OPSkillToCharacter)(SKID, tarAID, SKInfo);

/*
	signed int v10; // edx@10
	bool v12; // ebx@14
	IVItItem *v13; // eax@20
	int v14; // eax@32
	int v16; // ST64_4@43
	unsigned int v18; // ebx@47
	__int16 v19; // ax@47
	unsigned int v20; // ebx@47
	int v22; // ebx@49
	int v25; // eax@51
	int v27; // ecx@54
	CPC *v28; // edx@54
	CPC *v29; // ecx@55
	CPC *v30; // eax@64
	int v31; // eax@66
	int v32; // ebx@66
	CPC *v33; // eax@72
	__int16 v34; // dx@72
	void *v35; // eax@72
	int v36; // ebp@72
	__int16 v37; // ax@72
	CPC *v38; // ecx@76
	CPC *v39; // edi@78
	int v41; // ST64_4@83
	CCharacter *v42; // ST58_4@83
	unsigned __int16 v43; // ax@88
	__int16 v44; // ax@88
	int v47; // edx@92
	int v49; // ecx@95
	int v50; // edx@95
	__int16 v51; // ax@103
	CPC *v52; // ecx@103
	int v53; // edx@103
	CPC *v54; // eax@107
	CPC *v57; // ecx@113
	int v59; // ecx@120
	CCharacter *v60; // edx@120
	int v61; // ecx@120
	CCharacter *v62; // edx@120
	int v63; // edx@123
	MSGpar::CVar v64; // ecx@123
	__int16 v66; // bx@123
	char v67; // al@125
	char v68; // al@128
	char v69; // al@131
	char v70; // al@134
	char v71; // al@137
	char v72; // al@140
	char v73; // al@143
	char v74; // al@146
	char v75; // al@149
	std::_List_nod<unsigned long,std::allocator<unsigned long> >::_Node *v76; // eax@150
	CCharacter *v77; // eax@151
	CCharacter *v78; // ebx@151
	int v79; // eax@152
	CPC *v80; // ecx@155
	CCharacter *v87; // ebx@159
	CCharacter *v88; // eax@162
	CCharacter *v89; // ebx@162
	std::_List_nod<unsigned long,std::allocator<unsigned long> >::_Node *v91; // eax@171
	std::_List_nod<unsigned long,std::allocator<unsigned long> >::_Node *v92; // ecx@171
	signed int v93; // edx@181
	int v94; // ST6C_4@184
	int v95; // ST68_4@184
	CCharacter *v96; // ST58_4@184
	int v97; // eax@187
	void *v98; // edx@187
	std::deque<TokenData,std::allocator<TokenData> > *v100; // ebx@190
	char v101; // cl@190
	unsigned int v103; // eax@190
	int v104; // eax@191
	unsigned __int8 v105; // sf@196
	unsigned __int8 v106; // of@196
	TokenData *v107; // eax@204
	CPC *v108; // ecx@205
	TokenData *v109; // eax@207
	const char *v110; // eax@207
	unsigned int v111; // eax@208
	const char *v112; // eax@209
	int v114; // eax@215
	void *v118; // ebx@219
	__int16 v119; // ax@219
	int v122; // eax@232
	int v123; // eax@235
	double v126; // st7@238
	void *v127; // ebx@238
	int v129; // edx@239
	int v131; // eax@240
	int v132; // eax@243
	char v147; // [sp+70h] [bp-98h]@41
	unsigned int v148; // [sp+74h] [bp-94h]@1
	char v149; // [sp+78h] [bp-90h]@1
	int v150; // [sp+7Ch] [bp-8Ch]@47
	int v151; // [sp+80h] [bp-88h]@47
	signed int v152; // [sp+84h] [bp-84h]@52
	unsigned int maxHP; // [sp+8Ch] [bp-7Ch]@41
	int targetStatusDef; // [sp+94h] [bp-74h]@10
	int v157; // [sp+98h] [bp-70h]@72
	int level; // [sp+9Ch] [bp-6Ch]@51
	int v159; // [sp+A0h] [bp-68h]@10
	int mdefPower; // [sp+A4h] [bp-64h]@10
	char *targetItemMDef; // [sp+A8h] [bp-60h]@120
	unsigned int healthState; // [sp+ACh] [bp-5Ch]@47
	int targetStatusMDef; // [sp+B0h] [bp-58h]@47
	int race; // [sp+B8h] [bp-50h]@73
	int job; // [sp+C0h] [bp-48h]@156
	int size; // [sp+C4h] [bp-44h]@72
	SKILLATTACK_MSG msg; // [sp+CCh] [bp-3Ch]@72
	int v171; // [sp+FCh] [bp-Ch]@1
	int buf; // [sp+100h] [bp-8h]@1
	void *v174; // [sp+108h] [bp+0h]@76
	int v175; // [sp+108h] [bp+0h]@123
	unsigned int checkSKID; // [sp+124h] [bp+1Ch]@0
	unsigned int srcAID; // [sp+128h] [bp+20h]@0

	CCharacter* ch = g_characterMgr->CCharacterMgr::FastFindCharacter(tarAID);
	if( ch == NULL )
	{
		m_pc->SkillUseAck(SKID, 0, 0, 10);
		return;
	}

	if( this->CPCBattle::IsImmuneMagic(ch, SKID) )
		return;

	int type = ch->GetType();
	if( type == NPC_PET_TYPE || type == NPC_EVT_TYPE )
		return;

	if( type == PC_TYPE )
	{
		int reqEffective = EFST_BASILICA;
		ch->GetParameterValue(VAR_GETEFFECTIVE, &reqEffective);
		if( reqEffective) )
			return;
	}

	int CHJob;
	ch->GetParameterValue(VAR_JOB, &CHJob);
	if( CHJob == JT_EMPELIUM )
		return;

	int targetClass;
	ch->GetParameterValue(VAR_CLASS, &targetClass);
	if( targetClass == 4 )
		return;

	v10 = 0;
	v159 = (int)m_pc;
	targetStatusDef = 0;
	LOBYTE(mdefPower) = 10;

	switch( SKID )
	{
		case SKID_AL_HEAL:
		case SKID_AB_HIGHNESSHEAL:
			this->CPCBattle__OPSkillToCharacter_AL_HEAL(SKID, *(_DWORD *)(SKInfo + 16), *(_DWORD *)(SKInfo + 12), (MSG_TYPE4_FIVEDWORD *)SKInfo, tarAID, CHJob, type, ch);
			return;
		case SKID_ALL_SONKRAN:
			v114 = this->CPCBattle__ALL_SONKRAN((MSG_TYPE4_FIVEDWORD *)SKInfo, ch);
			targetStatusDef = v114;
			if ( targetStatusDef == 0 )
			{
				m_pc->SkillUseAck(SKID, 0, 0, mdefPower);
				return;
			}
			break;
		case 139:
			if ( type )
			{
				m_pc->SkillUseAck(SKID, 0, 0, mdefPower);
				return;
			}
			(*((void (__stdcall **)(_DWORD, _DWORD))m_pc->baseclass_0.baseclass_0.baseclass_0.vtable + 12))(7, -*(_DWORD *)(SKInfo + 12));
			(*(void (__thiscall **)(CCharacter *, signed int, _DWORD, signed int, signed int, _DWORD, _DWORD))((void (__thiscall **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD))ch->baseclass_0.vtable + 41))(ch, 7, *(_DWORD *)(SKInfo + 8), 1, 1, 0, 0);
			break;
		case 53:
			(*((void (__stdcall **)(_DWORD, _DWORD))m_pc->baseclass_0.baseclass_0.baseclass_0.vtable + 12))(7, -*(_DWORD *)(SKInfo + 12));
			g_characterMgr->CCharacterMgr::SendMsg(m_pc, ch, 113, 0, 0, 1, 0);
			break;
		case 71:
			(*((void (__stdcall **)(_DWORD, _DWORD))m_pc->baseclass_0.baseclass_0.baseclass_0.vtable + 12))(7, -*(_DWORD *)(SKInfo + 12));
			g_characterMgr->CCharacterMgr::SendMsg(m_pc, ch, 114, 14, *(_DWORD *)SKInfo, 1, 0);
			break;
		case 501:
			v114 = this->CPCBattle__SK_GS_Fling((MSG_TYPE4_FIVEDWORD *)SKInfo, ch);
			targetStatusDef = v114;
			if ( targetStatusDef == 0 )
			{
				m_pc->SkillUseAck(SKID, 0, 0, mdefPower);
				return;
			}
			break;
		case 508:
			v114 = this->CPCBattle__SK_GS_Cracker((MSG_TYPE4_FIVEDWORD *)SKInfo, ch);
			targetStatusDef = v114;
			if ( targetStatusDef == 0 )
			{
				m_pc->SkillUseAck(SKID, 0, 0, mdefPower);
				return;
			}
			break;
		case 513:
			v114 = this->CPCBattle__SK_GS_Disarm((MSG_TYPE4_FIVEDWORD *)SKInfo, ch);
			targetStatusDef = v114;
			if ( targetStatusDef == 0 )
			{
				m_pc->SkillUseAck(SKID, 0, 0, mdefPower);
				return;
			}
			break;
		case 536:
			v114 = this->CPCBattle__SK_NJ_BakuenRyu((MSG_TYPE4_FIVEDWORD *)SKInfo, ch);
			targetStatusDef = v114;
			if ( targetStatusDef == 0 )
			{
				m_pc->SkillUseAck(SKID, 0, 0, mdefPower);
				return;
			}
			break;
		case 694:
			v114 = this->CPCBattle__SK_ALL_ANGEL_PROTECT((MSG_TYPE4_FIVEDWORD *)SKInfo, ch);
			targetStatusDef = v114;
			if ( targetStatusDef == 0 )
			{
				m_pc->SkillUseAck(SKID, 0, 0, mdefPower);
				return;
			}
			break;
		case 472:
			(*((void (__stdcall **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD))m_pc->baseclass_0.baseclass_0.baseclass_0.vtable + 12))(7, -*(_DWORD *)(SKInfo + 12), v148, *(_DWORD *)&v149, v150, v151, v152, type, maxHP);
			v132 = (*((int (__thiscall **)(_DWORD))ch->baseclass_0.vtable + 1))(ch);
			if ( v132 != 5 )
			{
				v152 = 1000;
				(*(void (__cdecl **)(signed int, CPC *, signed int, _DWORD))((void (__cdecl **)(_DWORD, _DWORD, _DWORD, _DWORD))m_pc->baseclass_0.baseclass_0.baseclass_0.vtable + 38))(3, m_pc, 1000, 0);
				m_pc->SkillUseAck(SKID, 0, 0, mdefPower);
				return;
			}
			(*(void (__thiscall **)(CCharacter *, signed int, _DWORD, signed int, _DWORD, MSGpar::CVar))((void (__thiscall **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD))ch->baseclass_0.vtable + 41))(ch, 87, *(_DWORD *)(SKInfo + 4), 1, 0, 0);
			(*((void (__cdecl **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD))m_pc->baseclass_0.baseclass_0.baseclass_0.vtable + 41))(46, 500, 1, 0, 0, 0, 0);
			break;
		case 471:
			(*(void (__stdcall **)(signed int, int, unsigned int, _DWORD, int, int, signed int, MSGpar::CVar, unsigned int))((void (__stdcall **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD))m_pc->baseclass_0.baseclass_0.baseclass_0.vtable + 12))(7, -*(_DWORD *)(SKInfo + 12), v148, *(_DWORD *)&v149, v150, v151, v152, type, maxHP);
			v131 = (*((int (__thiscall **)(_DWORD))ch->baseclass_0.vtable + 1))(ch);
			maxHP = 0;
			type = 0;
			if ( v131 != 5 )
			{
				v152 = 1000;
				(*(void (__cdecl **)(signed int, CPC *, signed int, _DWORD))((void (__cdecl **)(_DWORD, _DWORD, _DWORD, _DWORD))m_pc->baseclass_0.baseclass_0.baseclass_0.vtable + 38))(3, m_pc, 1000, 0);
				m_pc->SkillUseAck(SKID, 0, 0, mdefPower);
				return;
			}
			(*(void (__thiscall **)(CCharacter *, signed int, _DWORD, signed int, _DWORD, MSGpar::CVar))((void (__thiscall **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD))ch->baseclass_0.vtable + 41))(ch, 160, *(_DWORD *)(SKInfo + 4), 1, 0, type);
			CNPC__SetATKPercentInfo((CNPC *)ch, 471, *(_DWORD *)(SKInfo + 4), 300);
			CNPC__SetDEFPercentInfo((CNPC *)ch, 471, *(_DWORD *)(SKInfo + 4), -50);
			(*((void (__stdcall **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD))m_pc->baseclass_0.baseclass_0.baseclass_0.vtable + 41))(159, 3000, 1, 0, 0, 1);
			type = 0;
			v152 = 0;
			v151 = 0;
			v150 = 1;
			*(_DWORD *)&v149 = 500;
			(*((void (__cdecl **)(_DWORD))m_pc->baseclass_0.baseclass_0.baseclass_0.vtable + 41))(46);
			break;
		case SKID_SM_PROVOKE:
		case SKID_SM_SELFPROVOKE:
			if( type != PC_TYPE && type != NPC_MOB_TYPE || ch->IsRightProperty(PROPERTY_UNDEAD) )
			{
				m_pc->SkillUseAck(SKID, 0, 0, mdefPower);
				return;
			}

			if( SKID == SKID_SM_SELFPROVOKE )
				SKID = SKID_SM_PROVOKE;
			else
			if( !ch->IsTarget(m_pc, 1) )
			{
				m_pc->SkillUseAck(SKID, 0, 0, mdefPower);
				return;
			}

			(*((void (__stdcall **)(_DWORD, _DWORD))m_pc->baseclass_0.baseclass_0.baseclass_0.vtable + 12))(7, -*(_DWORD *)(SKInfo + 12));

			reqEffective = 1;
			(void (__thiscall *)(_DWORD, _DWORD, _DWORD))*((_DWORD *)ch->baseclass_0.vtable + 11)(ch, 11, &reqEffective);
			if ( 3 * *(_DWORD *)(SKInfo + 16) + *(_WORD *)(m_pc + 578) - reqEffective + 70 <= GetServerRandom(0, 20000) % 100 )
			{
				m_pc->SkillUseAck(SKID, 0, 0, mdefPower);
				return;
			}

			*(_DWORD *)&msg.level = 0;
			*(_DWORD *)&msg.xPos = 0;
			*(_DWORD *)&msg.msgtype = 0;
			msg.par1 = 0;
			*(_DWORD *)&msg.actionType = 0;
			msg.isDivide = 0;
			*(_DWORD *)&msg.skLevel = 0;
			msg.targetAID = 6;
			*(_DWORD *)&msg.SKID = timeGetTime();
			msg.srcAID = *(_DWORD *)(m_pc + 404);
			*(_DWORD *)&msg.level = 0;
			*(_DWORD *)&msg.xPos = 1;
			*(_DWORD *)&msg.actionType = SKID;
			ch->InsertCommand(&msg);

			if( type == PC_TYPE )
			{
				CPCBattle__SetATKPercentInfo((CPCBattle *)&ch[15].m_mapRes, SKID, *(_DWORD *)(SKInfo + 8), *(_DWORD *)SKInfo - 100);
				CPCBattle__SetDEFPercentInfo((CPCBattle *)&ch[15].m_mapRes, SKID, *(_DWORD *)(SKInfo + 8), *(_DWORD *)(SKInfo + 4) - 100);
			}
			else
			if( type == NPC_MOB_TYPE )
			{
				CNPC__SetATKPercentInfo((CNPC *)ch, SKID, *(_DWORD *)(SKInfo + 8), *(_DWORD *)SKInfo - 100);
				CNPC__SetDEFPercentInfo((CNPC *)ch, SKID, *(_DWORD *)(SKInfo + 8), *(_DWORD *)(SKInfo + 4) - 100);
			}
			g_characterMgr->CCharacterMgr::SendMsg(m_pc, ch, 114, 0, *(_DWORD *)(SKInfo + 8), *(_DWORD *)(SKInfo + 16), 0);
			break;
		case 0x1B2:
			BYTE3(v157) = 0;
			if ( (*(int (__thiscall **)(CCharacter *))((int (__thiscall **)(_DWORD))ch->baseclass_0.vtable + 1))(ch) != 5 && (*((int (__thiscall **)(_DWORD))ch->baseclass_0.vtable + 1))(ch) )
			{
				m_pc->SkillUseAck(SKID, 0, 0, mdefPower);
				return;
			}
			(*((void (__stdcall **)(_DWORD, _DWORD))m_pc->baseclass_0.baseclass_0.baseclass_0.vtable + 12))(7, -*(_DWORD *)(SKInfo + 12));
			(*(void (__thiscall **)(_DWORD, signed int, int *))((void (__thiscall **)(_DWORD, _DWORD, _DWORD))ch->baseclass_0.vtable + 11))(ch, 147, &targetStatusDef);
			(*((void (__thiscall **)(_DWORD, _DWORD, _DWORD))ch->baseclass_0.vtable + 11))(ch, 6, &reqEffective);
			(*(void (__thiscall **)(_DWORD, signed int, MSGpar::CVar *))((void (__thiscall **)(_DWORD, _DWORD, _DWORD))ch->baseclass_0.vtable + 11))(ch, 19, &type);
			*(_DWORD *)&v147 = type;
			Trace("size=%d maxhp=%d job=%d\n", targetStatusDef, reqEffective, type, v148);
			v101 = *(_BYTE *)(SKInfo + 16);
			LOWORD(msg.targetAID) = 526;
			v103 = *(_DWORD *)(SKInfo + 16) - 1;
			*(&msg.actionType + 2) = v101 - 1;
			v100 = (std::deque<TokenData,std::allocator<TokenData> > *)&m_pc->m_pcSkill.m_warpInfo;
			maxHP = v103;
			if ( !*(_WORD *)&std__deque_TokenData_std__allocator_TokenData____operator__(v100, v103)->str.baseclass_0.___u0.baseclass_0.baseclass_0.dummy[0] )
			{
				v104 = *(_DWORD *)(SKInfo + 16);
				if ( v104 == 1 )
				{
					if ( targetStatusDef )
						goto LABEL_202;
				}
				else
				{
					if ( v104 == 2 )
					{
						if ( targetStatusDef != 1 )
							goto LABEL_202;
						v106 = __SETO__(reqEffective, 6000);
						v105 = reqEffective - 6000 < 0;
					}
					else
					{
						if ( v104 != 3 || targetStatusDef != 2 )
						{
							LABEL_202:
							if ( (*((int (__thiscall **)(_DWORD))ch->baseclass_0.vtable + 1))(ch) )
							{
								if ( BYTE3(v157) != 1 )
								{
									m_pc->SkillUseAck(SKID, 0, 0, mdefPower);
									return;
								}
								v109 = std__deque_TokenData_std__allocator_TokenData____operator__(v100, *(_DWORD *)(SKInfo + 16) - 1);
								*(_WORD *)&v109->str.baseclass_0.___u0.baseclass_0.baseclass_0.dummy[0] = *(_WORD *)&type;
								*(int *)((char *)&msg.par1 + 2) = (int)type;
								v110 = CMonParameterMgr__GetMonsterName(&g_monParameter, *(_DWORD *)&type);
								*(unsigned int *)((char *)&msg.targetAID + 2) = *(_DWORD *)v110;
								*(_QWORD *)((char *)&msg.SKID + 2) = *(_QWORD *)(v110 + 4);
								*(_DWORD *)&msg.count = *((_DWORD *)v110 + 3);
								HIBYTE(msg.xPos) = 0;
							}
							else
							{
								if ( !*(_DWORD *)&type )
								{
									m_pc->SkillUseAck(SKID, 0, 0, mdefPower);
									return;
								}
								v107 = std__deque_TokenData_std__allocator_TokenData____operator__(v100, *(_DWORD *)(SKInfo + 16) - 1);
								*(_WORD *)&v107->str.baseclass_0.___u0.baseclass_0.baseclass_0.dummy[0] = *(_WORD *)&type;
								*(int *)((char *)&msg.par1 + 2) = (int)type;
								BYTE2(msg.targetAID) = 0;
							}

							*(_DWORD *)&v147 = &msg;
							v108 = m_pc;
							*(&msg.actionType + 3) = 10;
							CPC__Send(v108, 32, (char *)&msg);
							break;
						}
						v106 = __SETO__(reqEffective, 20000);
						v105 = reqEffective - 20000 < 0;
					}

					if ( v105 ^ v106 )
						goto LABEL_202;
				}
				BYTE3(v157) = 1;
				goto LABEL_202;
			}

			v111 = *(_WORD *)&std__deque_TokenData_std__allocator_TokenData____operator__(v100, maxHP)->str.baseclass_0.___u0.baseclass_0.baseclass_0.dummy[0];
			*(int *)((char *)&msg.par1 + 2) = v111;
			if ( v111 - 28 > 0xF84 )
			{
				BYTE2(msg.targetAID) = 0;
			}
			else
			{
				v112 = CMonParameterMgr__GetMonsterName(&g_monParameter, v111);
				*(unsigned int *)((char *)&msg.targetAID + 2) = *(_DWORD *)v112;
				*(_QWORD *)((char *)&msg.SKID + 2) = *(_QWORD *)(v112 + 4);
				*(_DWORD *)&msg.count = *((_DWORD *)v112 + 3);
				HIBYTE(msg.xPos) = 0;
			}

			*(_DWORD *)&v147 = &msg;
			*(&msg.actionType + 3) = 11;
			CPC__Send(m_pc, 32, (char *)&msg);
			CPC__NotifyUseSkill(m_pc, 0x1B2u, tarAID, *(_DWORD *)(m_pc + 404), *(_WORD *)(SKInfo + 16), 0);
			return;
		case 470:
			(*(void (__stdcall **)(signed int, int, unsigned int, _DWORD, int, int, signed int, MSGpar::CVar, unsigned int))((void (__stdcall **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD))m_pc->baseclass_0.baseclass_0.baseclass_0.vtable + 12))(7, -*(_DWORD *)(SKInfo + 12), v148, *(_DWORD *)&v149, v150, v151, v152, type, maxHP);
			v122 = (*(int (__thiscall **)(CCharacter *))((int (__thiscall **)(_DWORD))ch->baseclass_0.vtable + 1))(ch);
			maxHP = 0;
			if ( v122 != 5 )
			{
				(*(void (__cdecl **)(signed int, CPC *, signed int, _DWORD, signed int, _DWORD, unsigned int))((void (__cdecl **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD))m_pc->baseclass_0.baseclass_0.baseclass_0.vtable + 38))(3, m_pc, 1000, 0, 1000, 0, maxHP);
				{
					m_pc->SkillUseAck(SKID, 0, 0, mdefPower);
					return;
				}
			}

			if ( (*(int (__thiscall **)(CCharacter *, signed int, unsigned int, int, int, int, int, int, int))((int (__thiscall **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD))ch->baseclass_0.vtable + 42))(ch, 154, maxHP, reqEffective, targetStatusDef, v157, level, v159, mdefPower) < 0 )
			{
				v123 = *(_DWORD *)(SKInfo + 8);
				mdefPower = 0;
				v159 = 0;
				level = 0;
				v157 = v123;
				targetStatusDef = 1;
				reqEffective = 154;
				(void (__thiscall *)(_DWORD))*((_DWORD *)ch->baseclass_0.vtable + 41)(ch);
				maxHP = 0;
				type = 0;
				v152 = 10000;
				(*(void (__cdecl **)(signed int, CPC *, signed int, _DWORD))((void (__cdecl **)(_DWORD, _DWORD, _DWORD, _DWORD))m_pc->baseclass_0.baseclass_0.baseclass_0.vtable + 38))(3, m_pc, 1000, 0);
				m_pc->SkillUseAck(SKID, 0, 0, mdefPower);
				return;
			}

			mdefPower = (int)&job;
			(void (__thiscall *)(_DWORD, _DWORD))*((_DWORD *)ch->baseclass_0.vtable + 11)(ch, 125);
			v159 = 0;
			level = 0;
			v157 = 0;
			if ( targetClass == 1 )
			{
				v126 = (double)*(signed int *)(SKInfo + 4);
				v127 = ch->baseclass_0.vtable;
				targetStatusDef = *(_DWORD *)(SKInfo + 8);
				reqEffective = (signed int)(v126 / 5.0);
				maxHP = 154;
				(void (__thiscall *)(_DWORD))*((_DWORD *)v127 + 41)(ch);
				type = 0;
				v152 = 0;
				v151 = 0;
				v150 = 1;
				*(_DWORD *)&v149 = 500;
			}
			else
			{
				v129 = *(_DWORD *)(SKInfo + 4);
				targetStatusDef = *(_DWORD *)(SKInfo + 8);
				reqEffective = v129;
				maxHP = 154;
				(void (__thiscall *)(_DWORD))*((_DWORD *)ch->baseclass_0.vtable + 41)(ch);
				type = 0;
				v152 = 0;
				v151 = 0;
				v150 = 1;
				*(_DWORD *)&v149 = 500;
			}

			(*((void (__cdecl **)(_DWORD))m_pc->baseclass_0.baseclass_0.baseclass_0.vtable + 41))(46);
			break;
		case 16:
			if ( !(*(int (__thiscall **)(CCharacter *, CPC *, _DWORD))((int (__thiscall **)(_DWORD, _DWORD, _DWORD))ch->baseclass_0.vtable + 20))(ch, m_pc, 0) )
			{
				m_pc->SkillUseAck(SKID, 0, 0, mdefPower);
				return;
			}
			v12 = *(_DWORD *)(SKInfo + 12) != 0;
			if ( (*((int (__stdcall **)(_DWORD, _DWORD))m_pc->baseclass_0.baseclass_0.baseclass_0.vtable + 42))(65, 0) == 16 )
			{
				if ( *(_DWORD *)(SKInfo + 12) < (signed int)CSkillTypeInfoMgr__GetSkillSPCost(&g_skillTypeInfoMgr, 0x10u, *(_WORD *)(SKInfo + 16)) )
					v12 = 0;
			}
			if ( !*(_DWORD *)(m_pc + 1084) )
			{
				if ( !(*((int (__stdcall **)(_DWORD, _DWORD))m_pc->baseclass_0.baseclass_0.baseclass_0.vtable + 42))(83, 0) )
				{
					if ( (*((int (__stdcall **)(_DWORD, _DWORD))m_pc->baseclass_0.baseclass_0.baseclass_0.vtable + 42))(149, 0) != 9 )
					{
						v13 = CPCItemInventoryMgr__SearchItemByID(&m_pc->m_pcitemInventoryMgr, 0, 0x2CCu);
						if ( v12 )
						{
							if ( !v13 || v13->m_count < 1 )
							{
								LOBYTE(mdefPower) = 7;
								m_pc->SkillUseAck(SKID, 0, 0, mdefPower);
								return;
							}
						}
					}
				}
			}
			(*((void (__stdcall **)(_DWORD, _DWORD))m_pc->baseclass_0.baseclass_0.baseclass_0.vtable + 12))(7, -*(_DWORD *)(SKInfo + 12));
			if ( (*(int (__stdcall **)(signed int, CCharacter *, _DWORD, signed int, _DWORD, signed int, _DWORD))((int (__stdcall **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD))m_pc->baseclass_0.baseclass_0.baseclass_0.vtable + 38))(1, ch, *(_DWORD *)SKInfo, 5000, 0, 1, 0) )
				targetStatusDef = 1;
			if ( !v12 )
			{
				if ( targetStatusDef == 0 )
				{
					m_pc->SkillUseAck(SKID, 0, 0, mdefPower);
					return;
				}
				break;
			}
			if ( !targetStatusDef && *(_DWORD *)(SKInfo + 16) >= 6 )
			{
				m_pc->SkillUseAck(SKID, 0, 0, mdefPower);
				return;
			}
			CPC__ConsumeItemForSkill(m_pc, 0x2CCu, 1);
			if ( targetStatusDef == 0 )
			{
				m_pc->SkillUseAck(SKID, 0, 0, mdefPower);
				return;
			}
			break;
		case 29:
			v14 = *(_DWORD *)(SKInfo + 4);
			if ( m_pc->m_characterInfo.hp < v14 )
			{
				LOBYTE(mdefPower) = 2;
				m_pc->SkillUseAck(SKID, 0, 0, mdefPower);
				return;
			}
			(*((void (__stdcall **)(_DWORD, _DWORD))m_pc->baseclass_0.baseclass_0.baseclass_0.vtable + 12))(5, -v14);
			(*((void (__stdcall **)(_DWORD, _DWORD))m_pc->baseclass_0.baseclass_0.baseclass_0.vtable + 12))(7, -*(_DWORD *)(SKInfo + 12));
			if ( !(*((int (__thiscall **)(_DWORD))ch->baseclass_0.vtable + 1))(ch) )
			{
				if ( CPC__GetCategoryFirstJob((CPC *)ch) != 4050
					&& !(*(int (__thiscall **)(CCharacter *, signed int, _DWORD))((int (__thiscall **)(_DWORD, _DWORD, _DWORD))ch->baseclass_0.vtable + 42))(ch, 97, 0) )
				{
					(*(void (__thiscall **)(CCharacter *, signed int, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD))((void (__thiscall **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD))ch->baseclass_0.vtable + 41))(ch, 12, *(_DWORD *)SKInfo, *(_DWORD *)(SKInfo + 16), 0, 0, 0);
					(*((void (__stdcall **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD))m_pc->baseclass_0.baseclass_0.baseclass_0.vtable + 41))(46, 1000, 1, 0, 0, 0);
					break;
				}
				if ( ch[2].baseclass_0.m_dwErrorCount == 1 )
					break;
				CNPC__NotifySkillAction(m_pc, &m_pc->baseclass_0.baseclass_0, &m_pc->baseclass_0.baseclass_0, ch, 1, 1, 1, 5u);
				break;
			}
			if ( (*((int (__thiscall **)(_DWORD))ch->baseclass_0.vtable + 1))(ch) == 9 )
			{
				maxHP = (unsigned int)&v147;
				g_characterMgr->CCharacterMgr::SendMsg(m_pc, ch, 114, 12, *(_DWORD *)SKInfo, *(_DWORD *)(SKInfo + 16), 0);
			}
			else
			{
				if ( (*(int (__thiscall **)(CCharacter *, signed int, _DWORD))((int (__thiscall **)(_DWORD, _DWORD, _DWORD))ch->baseclass_0.vtable + 42))(ch, 97, 0) )
				{
					CNPC__NotifySkillAction(m_pc, &m_pc->baseclass_0.baseclass_0, &m_pc->baseclass_0.baseclass_0, ch, 1, 1, 1, 5u);
					break;
				}
				g_characterMgr->CCharacterMgr::SendMsg(m_pc, ch, 0x79u, *(_DWORD *)(SKInfo + 16) + 2, *(_DWORD *)SKInfo, SKID, 0);
				g_characterMgr->CCharacterMgr::SendMsg(m_pc, ch, 114, 12, *(_DWORD *)SKInfo, *(_DWORD *)(SKInfo + 16), 0);
			}
			(*((void (__stdcall **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD))m_pc->baseclass_0.baseclass_0.baseclass_0.vtable + 41))(46, 1000, 1, 0, 0, 0);
			break;
		case 30:
			if ( !(*((int (__thiscall **)(_DWORD, _DWORD, _DWORD))ch->baseclass_0.vtable + 20))(ch, m_pc, 1) )
			{
				m_pc->SkillUseAck(SKID, 0, 0, mdefPower);
				return;
			}
			(*((void (__stdcall **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD))m_pc->baseclass_0.baseclass_0.baseclass_0.vtable + 12))(7, -*(_DWORD *)(SKInfo + 12), v148, *(_DWORD *)&v149, v150, v151);
			v19 = m_pc->CPC::GetIntValue();
			v20 = ((signed int)((unsigned __int64)(1717986919i64 * *(_WORD *)(targetStatusMDef + 578)) >> 32) >> 1)
				+ v19 / 5
				+ ((unsigned int)((unsigned __int64)(1717986919i64 * *(_WORD *)(targetStatusMDef + 578)) >> 32) >> 31)
				+ 3 * *(_DWORD *)(SKInfo + 16)
				+ 50;
			(*(void (__thiscall **)(_DWORD, signed int, int *))((void (__thiscall **)(_DWORD, _DWORD, _DWORD))ch->baseclass_0.vtable + 11))(ch, 123, &v159);
			healthState = v20 - v159;
			v18 = *(_DWORD *)(SKInfo + 4);
			if ( !(int (__thiscall *)(_DWORD))*((_DWORD *)ch->baseclass_0.vtable + 1)(ch) )
				v18 >>= 1;
			v151 = (int)&mdefPower;
			v150 = 16;
			(void (__thiscall *)(_DWORD))*((_DWORD *)ch->baseclass_0.vtable + 11)(ch);
			*(_DWORD *)&v149 = &reqEffective;
			v148 = 14;
			(void (__thiscall *)(_DWORD))*((_DWORD *)ch->baseclass_0.vtable + 11)(ch);
			v22 = -22 * (*(_DWORD *)&type + targetStatusDef) / 100 + v18;
			if ( (unsigned int)v22 < 0x3E8 )
				v22 = 1000;
			v25 = GetServerRandom(0, 20000);
			if ( v25 % 100 >= level )
			{
				m_pc->SkillUseAck(SKID, 0, 0, mdefPower);
				return;
			}
			if ( (*(int (__thiscall **)(CCharacter *, unsigned int, _DWORD, int, int, signed int, MSGpar::CVar))((int (__thiscall **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD))ch->baseclass_0.vtable + 1))(ch, v148, *(_DWORD *)&v149, v150, v151, v152, type) )
			{
				g_characterMgr->CCharacterMgr::SendMsg(&m_pc->baseclass_0.baseclass_0, ch, 0x79u, *(_DWORD *)SKInfo, v22, checkSKID, 0);
				g_characterMgr->CCharacterMgr::SendMsg(m_pc, ch, 114, 13, v22, *(_DWORD *)(SKInfo + 16), 0);
			}
			else
			{
				type = 0;
				v152 = 0;
				v151 = 0;
				if ( (int (__thiscall *)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD))*((_DWORD *)ch->baseclass_0.vtable + 41)(ch, 13, v22, *(_DWORD *)(SKInfo + 16), 0, 0, 0) )
				{
					v27 = *(_DWORD *)SKInfo;
					v28 = m_pc;
					v152 = checkSKID;
					v151 = v22;
					*(_DWORD *)&v149 = 121;
					v148 = (unsigned int)ch;
					*(_DWORD *)&v147 = v28;
					g_characterMgr->CCharacterMgr::SendMsg(*(CCharacter **)&v147, (CCharacter *)v148, *(unsigned int *)&v149, v27, v151, v152, 0);
				}
			}

			type = 0;
			v152 = 0;
			v151 = 0;
			v150 = 1;
			*(_DWORD *)&v149 = 1000;
			(*((void (__cdecl **)(_DWORD))m_pc->baseclass_0.baseclass_0.baseclass_0.vtable + 41))(46);
			break;
		case 34:
			(*((void (__stdcall **)(_DWORD, _DWORD))m_pc->baseclass_0.baseclass_0.baseclass_0.vtable + 12))(7, -*(_DWORD *)(SKInfo + 12));
			if ( (*((int (__thiscall **)(_DWORD))ch->baseclass_0.vtable + 1))(ch) == 5 && (*((int (__thiscall **)(_DWORD, _DWORD, _DWORD))ch->baseclass_0.vtable + 42))(ch, 97, 0) )
			{
				CNPC__NotifySkillAction(m_pc, &m_pc->baseclass_0.baseclass_0, &m_pc->baseclass_0.baseclass_0, ch, 1, 1, 1, 5u);
				break;
			}
			g_characterMgr->CCharacterMgr::SendMsg(m_pc, ch, 131, *(_DWORD *)SKInfo, *(_DWORD *)(SKInfo + 4), *(_DWORD *)(SKInfo + 16), 0);
			break;
		case 35:
			(*(void (__stdcall **)(signed int, int, unsigned int, _DWORD, int, int, signed int, MSGpar::CVar))((void (__stdcall **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD))m_pc->baseclass_0.baseclass_0.baseclass_0.vtable + 12))(7, -*(_DWORD *)(SKInfo + 12), v148, *(_DWORD *)&v149, v150, v151, v152, type);
			v30 = m_pc;
			v152 = 0;
			v151 = 0;
			v150 = 0;
			*(_DWORD *)&v149 = 132;
			v148 = (unsigned int)ch;
			*(_DWORD *)&v147 = v30;
			g_characterMgr->CCharacterMgr::SendMsg(*(CCharacter **)&v147, (CCharacter *)v148, *(unsigned int *)&v149, v150, v151, v152, 0);
			type = 0;
			v152 = 0;
			v151 = 0;
			v150 = 1;
			*(_DWORD *)&v149 = 1000;
			(*((void (__cdecl **)(_DWORD))m_pc->baseclass_0.baseclass_0.baseclass_0.vtable + 41))(46);
			break;
		case 54:
			if ( (CCharacter *)m_pc == ch )
			{
				m_pc->SkillUseAck(SKID, 0, 0, mdefPower);
				return;
			}
			v32 = v159;
			v31 = CPCSkill__GetSkillType((CPCSkill *)(m_pc + 3020), SKID);
			if ( v31 == -1 )
				return;
			if ( !v31 || v31 == 4 )
			{
				(*((void (__stdcall **)(_DWORD, _DWORD))m_pc->baseclass_0.baseclass_0.baseclass_0.vtable + 12))(7, -*(_DWORD *)(SKInfo + 12));
				if ( !CPC__ConsumeItemForSkill(m_pc, 0x2CDu, 1) )
				{
					LOBYTE(mdefPower) = 8;
					m_pc->SkillUseAck(SKID, 0, 0, mdefPower);
					return;
				}
			}
			(*(void (__thiscall **)(_DWORD, signed int, int *))((void (__thiscall **)(_DWORD, _DWORD, _DWORD))ch->baseclass_0.vtable + 11))(ch, 79, &targetStatusDef);
			(*(void (__thiscall **)(CCharacter *, signed int, int *))((void (__thiscall **)(_DWORD, _DWORD, _DWORD))ch->baseclass_0.vtable + 11))(ch, 125, &reqEffective);
			if ( (*(int (__thiscall **)(CCharacter *, signed int))((int (__thiscall **)(_DWORD, _DWORD))ch->baseclass_0.vtable + 22))(ch, 9) )
			{
				SKILLATTACK_MSG__SKILLATTACK_MSG(&msg);
				msg.SKID = SKID;
				msg.level = *(_WORD *)(SKInfo + 16);
				msg.skLevel = msg.level;
				v33 = m_pc;
				msg.targetAID = tarAID;
				msg.count = 1;
				msg.actionType = 6;
				msg.xPos = LOWORD(v33->m_pathInfo.m_moveInfo.xPos);
				v34 = LOWORD(v33->m_pathInfo.m_moveInfo.yPos);
				v35 = ch->baseclass_0.vtable;
				msg.yPos = v34;
				(*(void (__thiscall **)(CCharacter *, signed int, int *, unsigned int, _DWORD, int, int, signed int, MSGpar::CVar, unsigned int, int, int, int))((void (__thiscall **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD))v35 + 11))(ch, 5, &mdefPower, v148, *(_DWORD *)&v149, v150, v151, v152, type, maxHP, reqEffective, targetStatusDef, v157);
				(*(void (__thiscall **)(_DWORD, signed int, int *))((void (__thiscall **)(_DWORD, _DWORD, _DWORD))ch->baseclass_0.vtable + 11))(ch, 6, &targetStatusMDef);
				v36 = CPC__GetLukValue(m_pc);
				v37 = CPC__GetIntValue(m_pc);
				size = v36 + v37 + 20 * (signed __int16)buf + *(_WORD *)(v32 + 578);
				if ( (signed int)((double)size
					+ (1.0 - (double)(signed int)msg.targetAID / (double)targetStatusMDef) * 200.0) <= GetServerRandom(0, 20000) % 1000
					|| race == 1 )
					CPC__GetIntValue(m_pc);
				else
					(*(void (__thiscall **)(_DWORD, signed int, int *))((void (__thiscall **)(_DWORD, _DWORD, _DWORD))ch->baseclass_0.vtable + 11))(ch, 5, &size);
				v38 = m_pc;
				v157 = 0;
				targetStatusDef = 100;
				LOWORD(v174) = 1;
				if ( (*(int (__cdecl **)(int *, signed int, signed int, _DWORD))((int (__cdecl **)(_DWORD, _DWORD, _DWORD, _DWORD))v38->baseclass_0.baseclass_0.baseclass_0.vtable + 35))(&msg.finalDamage, 100, 100, 0) )
					this->CPCBattle__CheckSkillSpecialOption(checkSKID, ch, 0, 0);
				v39 = m_pc;
				type = 0;
				v152 = 0;
				v151 = 0;
				v150 = 1;
				*(_DWORD *)&v149 = 3000;
				v148 = 46;
				(void (__thiscall *)(_DWORD))*((_DWORD *)v39->baseclass_0.baseclass_0.baseclass_0.vtable + 41)(v39);
				return;
			}
			if ( targetStatusDef != 5 )
			{
				m_pc->SkillUseAck(SKID, 0, 0, mdefPower);
				return;
			}
			if ( type == NPC_MOB_TYPE )
			{
				if ( reqEffective == 1 )
				{
					m_pc->SkillUseAck(SKID, 0, 0, mdefPower);
					return;
				}
				*(_DWORD *)SKInfo = 100;
			}
			maxHP = (unsigned int)&v147;
			v41 = *(_DWORD *)SKInfo;
			v42 = (CCharacter *)m_pc;
			g_characterMgr->CCharacterMgr::SendMsg(v42, ch, 0x96u, v41, 0, 0, 0);
			(*((void (__stdcall **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD))m_pc->baseclass_0.baseclass_0.baseclass_0.vtable + 41))(46, 1000 * *(_DWORD *)(SKInfo + 16) - 1000, 1, 0, 0, 0);
			break;
		case 50:
			if ( type != 5 )
				return;
			(*(void (__thiscall **)(_DWORD, signed int, int *))((void (__thiscall **)(_DWORD, _DWORD, _DWORD))ch->baseclass_0.vtable + 11))(ch, 87, &level);
			(*(void (__thiscall **)(CCharacter *, signed int, int *))((void (__thiscall **)(_DWORD, _DWORD, _DWORD))ch->baseclass_0.vtable + 11))(ch, 125, &reqEffective);
			if ( level == 1
				|| level == 2
				|| reqEffective == 1
				|| ((*((void (__stdcall **)(_DWORD, _DWORD))m_pc->baseclass_0.baseclass_0.baseclass_0.vtable + 12))(7, -*(_DWORD *)(SKInfo + 12)), (*(void (__thiscall **)(CCharacter *, signed int, MSGpar::CVar *))((void (__thiscall **)(_DWORD, _DWORD, _DWORD))ch->baseclass_0.vtable + 11))(ch, 17, &type),
				v44 = CPC__GetDexValue(m_pc),
				v43 = CNPC__GetLostItem((CNPC *)ch, *(_DWORD *)SKInfo + ((signed int)v44 - *(_DWORD *)&type) / 2),
				!v43) )
			{
				m_pc->SkillUseAck(SKID, 0, 0, mdefPower);
				return;
			}
			if( CPC__OnAddItem(m_pc, v43, 6, 1, 0, 0) == 0 )
			{
				m_pc->SkillUseAck(SKID, 0, 0, mdefPower);
				return;
			}
			break;
		case 66:
			(*(void (__stdcall **)(signed int, int, unsigned int, _DWORD, int, int, signed int, MSGpar::CVar))((void (__stdcall **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD))m_pc->baseclass_0.baseclass_0.baseclass_0.vtable + 12))(7, -*(_DWORD *)(SKInfo + 12), v148, *(_DWORD *)&v149, v150, v151, v152, type);
			g_characterMgr->CCharacterMgr::SendMsg(m_pc, ch, 114, *(_DWORD *)(SKInfo + 8), *(_DWORD *)(SKInfo + 4), *(_DWORD *)SKInfo, 0);
			type = 0;
			v152 = 0;
			v151 = 0;
			v150 = 1;
			*(_DWORD *)&v149 = 3000;
			(*((void (__cdecl **)(_DWORD))m_pc->baseclass_0.baseclass_0.baseclass_0.vtable + 41))(46);
			break;
		case 67:
			if ( (CCharacter *)m_pc == ch )
			{
				m_pc->SkillUseAck(SKID, 0, 0, mdefPower);
				return;
			}
			(*((void (__stdcall **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD))m_pc->baseclass_0.baseclass_0.baseclass_0.vtable + 12))(7, -*(_DWORD *)(SKInfo + 12), v148, *(_DWORD *)&v149, v150, v151, v152, type);
			mdefPower = (int)&type;
			type = 0;
			v49 = *(_DWORD *)(SKInfo + 4);
			v50 = *(_DWORD *)(SKInfo + 8);
			v152 = *(_DWORD *)SKInfo;
			g_characterMgr->CCharacterMgr::SendMsg(&m_pc->baseclass_0.baseclass_0, ch, 0x72u, v50, v49, v152, 0);
			type = 0;
			v152 = 0;
			v151 = 0;
			v150 = 1;
			*(_DWORD *)&v149 = 2000;
			(*((void (__cdecl **)(_DWORD))m_pc->baseclass_0.baseclass_0.baseclass_0.vtable + 41))(46);
			break;
		case 68:
			if ( !CPC__ConsumeItemForSkill(m_pc, 0x20Bu, 1) )
			{
				m_pc->SkillUseAck(SKID, 0, 0, mdefPower);
				return;
			}
			(*((void (__stdcall **)(_DWORD, _DWORD))m_pc->baseclass_0.baseclass_0.baseclass_0.vtable + 12))(7, -*(_DWORD *)(SKInfo + 12));
			(*((void (__stdcall **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD))m_pc->baseclass_0.baseclass_0.baseclass_0.vtable + 41))(46, 2000, 1, 0, 0, 0);
			(*(void (__thiscall **)(CCharacter *, signed int, int *))((void (__thiscall **)(_DWORD, _DWORD, _DWORD))ch->baseclass_0.vtable + 11))(ch, 146, &level);
			if ( (*((int (__thiscall **)(_DWORD, _DWORD))ch->baseclass_0.vtable + 22))(ch, 9) || level == 6 )
			{
				if ( !(*((int (__thiscall **)(_DWORD, _DWORD, _DWORD))ch->baseclass_0.vtable + 20))(ch, m_pc, 0) )
				{
					m_pc->SkillUseAck(SKID, 0, 0, mdefPower);
					return;
				}
				SKILLATTACK_MSG__SKILLATTACK_MSG(&msg);
				msg.targetAID = tarAID;
				v51 = *(_WORD *)(SKInfo + 16);
				msg.count = 1;
				v52 = m_pc;
				msg.level = v51;
				msg.skLevel = v51;
				msg.SKID = SKID;
				msg.actionType = 6;
				msg.xPos = LOWORD(v52->m_pathInfo.m_moveInfo.xPos);
				v53 = *(_DWORD *)SKInfo;
				msg.yPos = LOWORD(v52->m_pathInfo.m_moveInfo.yPos);
				msg.par1 = v53;
				msg.msgtype = 1;
				if ( (*(int (__stdcall **)(SKILLATTACK_MSG *, signed int, signed int, _DWORD))((int (__stdcall **)(_DWORD, _DWORD, _DWORD, _DWORD))v52->baseclass_0.baseclass_0.baseclass_0.vtable + 35))(&msg, 100, 100, 0) )
					this->CPCBattle__CheckSkillSpecialOption(SKID, ch, 0, 0);
			}
			else
			{
				if ( !*(_DWORD *)&type || type == 9 )
				{
					(*(void (__thiscall **)(CCharacter *, signed int, _DWORD, signed int, _DWORD, _DWORD, _DWORD))((void (__thiscall **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD))ch->baseclass_0.vtable + 41))(ch, 17, *(_DWORD *)(SKInfo + 4), 1, 0, 0, 0);
					break;
				}
			}
			return;
		case 76:
			(*(void (__thiscall **)(CCharacter *, signed int, int *, unsigned int, _DWORD))((void (__thiscall **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD))ch->baseclass_0.vtable + 11))(ch, 88, &level, v148, *(_DWORD *)&v149);
			if ( mdefPower & 4 )
			{
				targetStatusDef = (int)&v149;
				*(_DWORD *)&v149 = 0;
				SKID = -1;
				g_characterMgr->CCharacterMgr::SendMsg(&m_pc->baseclass_0.baseclass_0, ch, 0x71u, 0, 0, 4, 0);
			}
			else
			{
				v54 = m_pc;
				*(_DWORD *)&v149 = 1;
				v148 = (unsigned int)v54;
				if ( !(int (__thiscall *)(_DWORD))*((_DWORD *)ch->baseclass_0.vtable + 20)(ch) )
				{
					m_pc->SkillUseAck(SKID, 0, 0, mdefPower);
					return;
				}
				(*(void (__stdcall **)(signed int, CCharacter *, signed int, signed int, _DWORD, _DWORD, _DWORD, unsigned int, _DWORD))((void (__stdcall **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD))m_pc->baseclass_0.baseclass_0.baseclass_0.vtable + 38))(8, ch, 1000, 1000, *(_DWORD *)(SKInfo + 4), 0, 0, v148, *(_DWORD *)&v149);
			}
			*(_DWORD *)&v149 = -*(_DWORD *)(SKInfo + 12);
			(void (__cdecl *)(_DWORD, _DWORD))*((_DWORD *)m_pc->baseclass_0.baseclass_0.baseclass_0.vtable + 12)(7, *(_DWORD *)&v149);
			(*((void (__stdcall **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD))m_pc->baseclass_0.baseclass_0.baseclass_0.vtable + 41))(46, 3000, 1, 0, 0, 0);
			break;
		case 78:
			if ( !(*((int (__thiscall **)(_DWORD, _DWORD, _DWORD))ch->baseclass_0.vtable + 20))(ch, m_pc, 0) || ((*(void (__thiscall **)(_DWORD, signed int, int *))((void (__thiscall **)(_DWORD, _DWORD, _DWORD))ch->baseclass_0.vtable + 11))(ch, 87, &level), level == 1) || level == 2 )
			{
				m_pc->SkillUseAck(SKID, 0, 0, mdefPower);
				return;
			}
			(*((void (__stdcall **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD))m_pc->baseclass_0.baseclass_0.baseclass_0.vtable + 12))( 7, -*(_DWORD *)(SKInfo + 12), v148, *(_DWORD *)&v149, v150, v151, v152, type);
			v57 = m_pc;
			v152 = 1;
			v151 = 9999;
			v150 = 22;
			*(_DWORD *)&v149 = 114;
			v148 = (unsigned int)ch;
			*(_DWORD *)&v147 = v57;
			g_characterMgr->CCharacterMgr::SendMsg(*(CCharacter **)&v147, (CCharacter *)v148, *(unsigned int *)&v149, v150, v151, v152, 0);
			type = 0;
			v152 = 0;
			v151 = 0;
			v150 = 1;
			*(_DWORD *)&v149 = 3000;
			(*((void (__cdecl **)(_DWORD))m_pc->baseclass_0.baseclass_0.baseclass_0.vtable + 41))(46);
			break;
		case 72:
			if ( (*(int (__thiscall **)(CCharacter *, signed int, unsigned int, _DWORD, int, int, signed int, MSGpar::CVar, unsigned int, int))((int (__thiscall **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD))ch->baseclass_0.vtable + 22))(ch, 9, v148, *(_DWORD *)&v149, v150, v151, v152, type, maxHP, reqEffective) )
			{
				if ( (*((int (__thiscall **)(_DWORD, _DWORD, _DWORD))ch->baseclass_0.vtable + 20))(ch, m_pc, 0) )
					(*(void (__stdcall **)(signed int, CCharacter *, signed int, signed int, _DWORD, _DWORD, _DWORD))((void (__stdcall **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD))m_pc->baseclass_0.baseclass_0.baseclass_0.vtable + 38))(10, ch, 1000, 1000, 0, 0, 0);
			}
			else
			{
				healthState = (unsigned int)&reqEffective;
				reqEffective = 0;
				g_characterMgr->CCharacterMgr::SendMsg(&m_pc->baseclass_0.baseclass_0, ch, 0x70u, 0, 0, 0, 0);
			}
			reqEffective = -*(_DWORD *)(SKInfo + 12);
			(void (__cdecl *)(_DWORD, _DWORD))*((_DWORD *)m_pc->baseclass_0.baseclass_0.baseclass_0.vtable + 12)(7, reqEffective);
			(*((void (__cdecl **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD))m_pc->baseclass_0.baseclass_0.baseclass_0.vtable + 41))(46, 2000, 1, 0, 0, 0);
			break;
		case 73:
			(*((void (__stdcall **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD))m_pc->baseclass_0.baseclass_0.baseclass_0.vtable + 12))(7, -*(_DWORD *)(SKInfo + 12), v148, *(_DWORD *)&v149, v150, v151, v152, type);
			CPC__NotifyUseSkill(m_pc, SKID, srcAID, srcAID, -1, 1);
			(*(void (__thiscall **)(_DWORD, signed int, int *))((void (__thiscall **)(_DWORD, _DWORD, _DWORD))ch->baseclass_0.vtable + 11))(ch, 155, &CHJob);
			if ( !CHJob )
			{
				v59 = *(_DWORD *)(SKInfo + 8);
				v60 = (CCharacter *)m_pc;
				v152 = *(_DWORD *)SKInfo;
				g_characterMgr->CCharacterMgr::SendMsg(v60, ch, 0x72u, 19, v59, v152, 0);
				(*(void (__thiscall **)(CCharacter *, signed int, char **))((void (__thiscall **)(_DWORD, _DWORD, _DWORD))ch->baseclass_0.vtable + 11))(ch, 6, &targetItemMDef);
				v61 = *(_DWORD *)(SKInfo + 8);
				v62 = (CCharacter *)m_pc;
				v152 = (_DWORD)targetItemMDef * *(_DWORD *)(SKInfo + 4) / 100;
				g_characterMgr->CCharacterMgr::SendMsg(v62, ch, 0x72u, 49, v61, v152, 0);
			}
			(*((void (__cdecl **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD))m_pc->baseclass_0.baseclass_0.baseclass_0.vtable + 41))(46, 2000, 1, 0, 0, 0);
			this->CPCBattle__CheckSkillSpecialOption(SKID, ch, 0, 0);
			return;
		case 93:
			if ( type != 5 )
			{
				m_pc->SkillUseAck(SKID, 0, 0, mdefPower);
				return;
			}
			(*((void (__stdcall **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD))m_pc->baseclass_0.baseclass_0.baseclass_0.vtable + 12))(7, -*(_DWORD *)(SKInfo + 12), v148, *(_DWORD *)&v149, v150, v151, v152, 5, maxHP, reqEffective, targetStatusDef, v157, level, v159, mdefPower);
			(*(void (__thiscall **)(CCharacter *, signed int, unsigned __int16 *))((void (__thiscall **)(_DWORD, _DWORD, _DWORD))ch->baseclass_0.vtable + 11))(ch, 11, &msg.SKID);
			(*(void (__thiscall **)(CCharacter *, signed int, unsigned int *))((void (__thiscall **)(_DWORD, _DWORD, _DWORD))ch->baseclass_0.vtable + 11))(ch, 147, &v170);
			(*(void (__thiscall **)(_DWORD, signed int, int *))((void (__thiscall **)(_DWORD, _DWORD, _DWORD))ch->baseclass_0.vtable + 11))(ch, 5, &v171);
			v66 = HIWORD(ch[3].m_charBuff2.m_heal.sp_modifyPercent);
			*(_DWORD *)&msg.level = ch[4].baseclass_0.m_dwErrorCount;
			(void (__thiscall *)(_DWORD, _DWORD, _DWORD))*((_DWORD *)ch->baseclass_0.vtable + 11)(ch, 146, &msg.isDivide);
			(*(void (__thiscall **)(_DWORD, signed int, int *))((void (__thiscall **)(_DWORD, _DWORD, _DWORD))ch->baseclass_0.vtable + 11))(ch, 148, &targetClass);
			(*(void (__thiscall **)(_DWORD, signed int, int *))((void (__thiscall **)(_DWORD, _DWORD, _DWORD))ch->baseclass_0.vtable + 11))(ch, 19, &msg.finalDamage);
			LOWORD(v173) = msg.SKID;
			LOWORD(tarAID) = msg.level;
			LOWORD(buf) = 396;
			HIWORD(v173) = v170;
			v64 = par4;
			HIWORD(buf) = LOWORD(msg.finalDamage);
			v63 = targetClass;
			v175 = v171;
			LOWORD(SKID) = v66;
			HIWORD(tarAID) = targetClass;
			HIWORD(SKID) = LOWORD(msg.isDivide);
			if ( par4 )
			{
				v67 = CAttackPlusPowerInfo::GetAttackPlusPowerByProperty(*(CAttackPlusPowerInfo **)&par4, targetClass, 1);
				v64 = par4;
				v63 = targetClass;
			}
			if ( v64 )
			{
				v68 = CAttackPlusPowerInfo__GetAttackPlusPowerByProperty(*(CAttackPlusPowerInfo **)&v64, v63, 2);
				v64 = par4;
				v63 = targetClass;
			}
			if ( v64 )
			{
				v69 = CAttackPlusPowerInfo__GetAttackPlusPowerByProperty(*(CAttackPlusPowerInfo **)&v64, v63, 3);
				v64 = par4;
				v63 = targetClass;
			}
			if ( v64 )
			{
				v70 = CAttackPlusPowerInfo__GetAttackPlusPowerByProperty(*(CAttackPlusPowerInfo **)&v64, v63, 4);
				v64 = par4;
				v63 = targetClass;
			}
			if ( v64 )
			{
				v71 = CAttackPlusPowerInfo__GetAttackPlusPowerByProperty(*(CAttackPlusPowerInfo **)&v64, v63, 5);
				v64 = par4;
				v63 = targetClass;
			}
			if ( v64 )
			{
				v72 = CAttackPlusPowerInfo__GetAttackPlusPowerByProperty(*(CAttackPlusPowerInfo **)&v64, v63, 6);
				v64 = par4;
				v63 = targetClass;
			}
			if ( v64 )
			{
				v73 = CAttackPlusPowerInfo__GetAttackPlusPowerByProperty(*(CAttackPlusPowerInfo **)&v64, v63, 7);
				v64 = par4;
				v63 = targetClass;
			}
			if ( v64 )
			{
				v74 = CAttackPlusPowerInfo__GetAttackPlusPowerByProperty(*(CAttackPlusPowerInfo **)&v64, v63, 8);
				v64 = par4;
				v63 = targetClass;
			}
			if ( v64 )
				v75 = CAttackPlusPowerInfo__GetAttackPlusPowerByProperty(*(CAttackPlusPowerInfo **)&v64, v63, 9);

			v76 = m_pc->m_groupMember._Myhead;
			*(_DWORD *)&msg.level = v76->_Next;
			if ( *(std::_List_nod<unsigned long,std::allocator<unsigned long> >::_Node **)&msg.level != v76 )
			{
				do
				{
					v77 = CCharacterMgr__FindCharacter(&g_characterMgr, *(_DWORD *)(*(_DWORD *)&msg.level + 8), 0);
					v78 = v77;
					if ( v77 )
					{
						v79 = (*(int (__thiscall **)(CCharacter *))((int (__thiscall **)(_DWORD))v77->baseclass_0.vtable + 9))(v77);
						if ( v79 != *(_DWORD *)(msg.srcAID + 404) )
						{
							(*(void (__thiscall **)(CCharacter *, signed int, __int16 *))((void (__thiscall **)(_DWORD, _DWORD, _DWORD))v78->baseclass_0.vtable + 11))(v78, 66, &msg.msgtype);
							if ( *(_DWORD *)(msg.srcAID + 428) == *(_DWORD *)&msg.msgtype )
								CAsyncStream__Send(v78->baseclass_0.m_asyncStream, 29, (const char *)&buf);
						}
					}
					v80 = m_pc;
					*(_DWORD *)&msg.level = **(_DWORD **)&msg.level;
				}
				while ( *(std::_List_nod<unsigned long,std::allocator<unsigned long> >::_Node **)&msg.level != v80->m_groupMember._Myhead );
			}
			CPC__Send(m_pc, 29, (char *)&buf);
			mdefPower = 0;
			v159 = 0;
			level = 0;
			(void (__thiscall *)(_DWORD))*((_DWORD *)ch->baseclass_0.vtable + 66)(ch);
			v157 = (int)&CHJob;
			targetStatusDef = 188;
			(void (__thiscall *)(_DWORD))*((_DWORD *)ch->baseclass_0.vtable + 11)(ch);
			CHJob = 0;
			targetStatusMDef = 0;
			reqEffective = (int)&CHJob;
			maxHP = 121;
			(void (__thiscall *)(_DWORD))*((_DWORD *)ch->baseclass_0.vtable + 11)(ch);
			type = (MSGpar::CVar)&targetItemMDef;
			v152 = 45;
			(void (__thiscall *)(_DWORD))*((_DWORD *)ch->baseclass_0.vtable + 11)(ch);
			targetClass = mdefPower + v159;
			v151 = (int)&job;
			v150 = 124;
			(void (__thiscall *)(_DWORD))*((_DWORD *)ch->baseclass_0.vtable + 11)(ch);
			*(_DWORD *)&v149 = &targetStatusMDef;
			v148 = 123;
			(void (__thiscall *)(_DWORD))*((_DWORD *)ch->baseclass_0.vtable + 11)(ch);
			*(_DWORD *)&v147 = &targetItemMDef[targetStatusMDef];
			CTestButton___CTestButton((CPacketHandler *)&ch[3].m_neighborCache.m_cacheMPool.m_cs.LockCount);
			break;
		case 124:
		case 131:
			if ( (*((int (__thiscall **)(_DWORD))ch->baseclass_0.vtable + 1))(ch) != 3
				|| !(ch[1].m_neighborCache.m_cacheMPool.m_data.baseclass_0._Mysize & 1)
				|| (v87 = CSkill__GetMasterCharacter((CSkill *)ch), !v87)
				|| (*(int (__thiscall **)(CCharacter *))((int (__thiscall **)(_DWORD))v87->baseclass_0.vtable + 1))(v87)
				|| CPC__GetCategorySecondJob((CPC *)v87) != 11 )
			{
				m_pc->SkillUseAck(SKID, 0, 0, mdefPower);
				return;
			}
			(*((void (__stdcall **)(_DWORD, _DWORD))m_pc->baseclass_0.baseclass_0.baseclass_0.vtable + 12))(7, -*(_DWORD *)(SKInfo + 12));
			v88 = CCharacterMgr__FastFindCharacter(&g_characterMgr, ch[1].m_neighborCache.m_cacheMPool.m_cs.LockCount);
			v89 = v88;
			if ( v88 )
			{
				reqEffective = 45;
				(void (__thiscall *)(_DWORD, _DWORD, _DWORD))*((_DWORD *)v88->baseclass_0.vtable + 11)(v88, 92, &reqEffective);
				if ( reqEffective )
					(*(void (__thiscall **)(CCharacter *, signed int, signed int))((void (__thiscall **)(_DWORD, _DWORD, _DWORD))v89->baseclass_0.vtable + 12))(v89, 91, 45);
			}
			if ( SKID == 124 )
			{
				if ( ch[1].m_neighborCache.m_cacheMPool.m_buf == (ClientCache **)4 )
				{
					m_pc->SkillUseAck(SKID, 0, 0, mdefPower);
					return;
				}
				CSkill__SetExpireTime((CSkill *)ch, 0);
				CPC__OnAddItem(m_pc, 1065, 0, 1, 0, 0);
			}
			else
			{
				(*(void (__thiscall **)(CCharacter *, signed int, signed int))((void (__thiscall **)(_DWORD, _DWORD, _DWORD))ch->baseclass_0.vtable + 12))(ch, 19, 140);
				CSkill__SetExpireTime((CSkill *)ch, 0x5DCu);
			}
			break;
		case 138:
			if ( tarAID == m_pc->m_characterInfo.accountID )
			{
				targetStatusDef = 1;
				(*((void (__stdcall **)(_DWORD, _DWORD))m_pc->baseclass_0.baseclass_0.baseclass_0.vtable + 12))(7, -*(_DWORD *)(SKInfo + 12));
				(*(void (__thiscall **)(CCharacter *, signed int, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD))((void (__thiscall **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD))ch->baseclass_0.vtable + 41))(ch, 6, *(_DWORD *)(SKInfo + 8), *(_DWORD *)SKInfo, 0, 0, 0);
				if ( targetStatusDef == 0 )
				{
					m_pc->SkillUseAck(SKID, 0, 0, mdefPower);
					return;
				}
				break;
			}
			v92 = m_pc->m_groupMember._Myhead;
			v91 = v92->_Next;
			if ( v92->_Next != v92 )
			{
				do
				{
					if ( v91->_Myval == tarAID )
						v10 = 1;
					v91 = v91->_Next;
				}
				while ( v91 != v92 );
				targetStatusDef = v10;
				if ( v10 )
				{
					(*((void (__stdcall **)(_DWORD, _DWORD))m_pc->baseclass_0.baseclass_0.baseclass_0.vtable + 12))(7, -*(_DWORD *)(SKInfo + 12));
					(*(void (__thiscall **)(CCharacter *, signed int, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD))((void (__thiscall **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD))ch->baseclass_0.vtable + 41))(ch, 6, *(_DWORD *)(SKInfo + 8), *(_DWORD *)SKInfo, 0, 0, 0);
					if ( targetStatusDef == 0 )
					{
						m_pc->SkillUseAck(SKID, 0, 0, mdefPower);
						return;
					}
					break;
				}
			}
			m_pc->SkillUseAck(SKID, 0, 0, mdefPower);
			return;
		case 141:
			if ( !CPCSkill__IsEndPostdelaySkill(&m_pc->m_pcSkill, 0x8Du)
				|| ((*(void (__thiscall **)(_DWORD, signed int, int *))((void (__thiscall **)(_DWORD, _DWORD, _DWORD))ch->baseclass_0.vtable + 11))(ch, 5, &targetStatusMDef),
				(*(void (__thiscall **)(_DWORD, signed int, unsigned int *))((void (__thiscall **)(_DWORD, _DWORD, _DWORD))ch->baseclass_0.vtable + 11))(ch, 6, &maxHP),
				(*(void (__thiscall **)(_DWORD, signed int, unsigned int *))((void (__thiscall **)(_DWORD, _DWORD, _DWORD))ch->baseclass_0.vtable + 11))(ch, 88, &healthState),
				!(*((int (__thiscall **)(_DWORD, _DWORD, _DWORD))ch->baseclass_0.vtable + 20))(ch, m_pc, 1))
				|| ((*((void (__stdcall **)(_DWORD, _DWORD))m_pc->baseclass_0.baseclass_0.baseclass_0.vtable
				+ 12))(7, -*(_DWORD *)(SKInfo + 12)),
				v93 = (signed int)((unsigned __int64)(1374389535i64 * (signed int)(75 * maxHP)) >> 32) >> 5,
				targetStatusMDef >= (signed int)(v93 + ((unsigned int)v93 >> 31)))
				|| (CPCSkill__SetPostdelaySkill(&m_pc->m_pcSkill, 0x8Du, 500 * (*(_DWORD *)(SKInfo + 16) + 14)), *(_DWORD *)(SKInfo + 12))
				&& !CPC__ConsumeItemForSkill(m_pc, 0x2CCu, 1) )
			{
				m_pc->SkillUseAck(SKID, 0, 0, mdefPower);
				return;
			}
			g_characterMgr->CCharacterMgr::SendMsg(m_pc, ch, 0x72u, 44, *(_DWORD *)(SKInfo + 8), *(_DWORD *)(m_pc + 404), 0);
			if( type == PC_TYPE )
			{
				targetItemMDef = (char *)44;
				std__map_int_EFFECTIVE_INFO_std__less_int__std__allocator_std__pair_int_const_EFFECTIVE_INFO_____operator__(&ch->m_effectiveList, (const int *)&targetItemMDef)->val[1] = *(_DWORD *)(SKInfo + 16);
			}
			else
			if ( type == NPC_MOB_TYPE )
			{
				v97 = (*(int (__thiscall **)(CCharacter *, signed int, signed int))((int (__thiscall **)(_DWORD, _DWORD, _DWORD))ch->baseclass_0.vtable + 42))(ch, 44, 1);
				v98 = ch->baseclass_0.vtable;
				*(_DWORD *)&v147 = 1;
				(*(void (__thiscall **)(CCharacter *, signed int, int, signed int))((void (__thiscall **)(_DWORD, _DWORD, _DWORD, _DWORD))v98 + 43))(ch, 44, -v97, 1);
				(*(void (__thiscall **)(CCharacter *, signed int, _DWORD, signed int))((void (__thiscall **)(_DWORD, _DWORD, _DWORD, _DWORD))ch->baseclass_0.vtable + 43))(ch, 44, *(_DWORD *)(SKInfo + 16), 1);
			}
			break;
		default:
			if( GetCharSkill()->CCharSkill__OperSkillToChar(m_pc, ch, SKID, (MSG_TYPE4_FIVEDWORD *)SKInfo) != -1 )
			{
				m_pc->SkillUseAck(SKID, 0, 0, mdefPower);
				return;
			}
			break;
	}

	m_pc->CPC::NotifyUseSkill(SKID, tarAID, *(_DWORD *)(m_pc + 404), *(_WORD *)(SKInfo + 16), 1);
	v119 = CSkillTypeInfoMgr__GetPostDelayTM(&g_skillTypeInfoMgr, SKID, *(_WORD *)(SKInfo + 16));
	(*(void (__thiscall **)(CPC *, signed int, _DWORD, signed int, _DWORD, _DWORD, _DWORD))((void (__thiscall **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD))m_pc->vtable + 41))(m_pc, 46, v119, 1, 0, 0, 0);
	this->CPCBattle__CheckSkillSpecialOption(SKID, ch, 0, 0);
	return;
*/
}


hook_method<void (CPCBattle::*)(const int in_SKID, const int in_skLevel, const int in_spCost, const MSG_TYPE4_FIVEDWORD* in_pData, const int in_TargetCHAID, const int in_TargetCHJob, const int in_TargetCHType, CCharacter* in_cpTargetCh)> CPCBattle::_OPSkillToCharacter_AL_HEAL(SERVER, "CPCBattle::OPSkillToCharacter_AL_HEAL");
void CPCBattle::OPSkillToCharacter_AL_HEAL(const int in_SKID, const int in_skLevel, const int in_spCost, const MSG_TYPE4_FIVEDWORD* in_pData, const int in_TargetCHAID, const int in_TargetCHJob, const int in_TargetCHType, CCharacter* in_cpTargetCh)
{
	return (this->*_OPSkillToCharacter_AL_HEAL)(in_SKID, in_skLevel, in_spCost, in_pData, in_TargetCHAID, in_TargetCHJob, in_TargetCHType, in_cpTargetCh);

	//TODO
}


hook_method<void (CPCBattle::*)(int SKID, int tarAID, int SKInfo)> CPCBattle::_OPSkillToSelf(SERVER, "CPCBattle::OPSkillToSelf");
void CPCBattle::OPSkillToSelf(int SKID, int tarAID, int SKInfo)
{
	return (this->*_OPSkillToSelf)(SKID, tarAID, SKInfo);

	//TODO
}


//hook_method<OptionInfo* (CPCBattle::*)(void)> CPCBattle::_GetOptionInfo(SERVER, "CPCBattle::GetOptionInfo");
OptionInfo* CPCBattle::GetOptionInfo(void)
{
//	return (this->*_GetOptionInfo)();

	return &m_optionInfo;
}


hook_method<int (CPCBattle::*)(CCharacter* other, int isRangeATK, PACKET_ZC_NOTIFY_ACT* packet, bool& isConsumePlusArrow)> CPCBattle::_GetPhysicalATKDamage(SERVER, "CPCBattle::GetPhysicalATKDamage");
int CPCBattle::GetPhysicalATKDamage(CCharacter* other, int isRangeATK, PACKET_ZC_NOTIFY_ACT* packet, bool& isConsumePlusArrow)
{
	return (this->*_GetPhysicalATKDamage)(other, isRangeATK, packet, isConsumePlusArrow);

	//TODO
}


hook_method<int (CPCBattle::*)(CCharacter* other, bool isIncluingLevelRatio)> CPCBattle::_GetMagicATKPower(SERVER, "CPCBattle::GetMagicATKPower");
int CPCBattle::GetMagicATKPower(CCharacter* other, bool isIncluingLevelRatio)
{
	return (this->*_GetMagicATKPower)(other, isIncluingLevelRatio);

	m_pc->CPC::GetIntValue(); // ???
	int minMATK = m_pc->CPC::GetMagicAttMinPowOnClient();
	int maxMATK = m_pc->CPC::GetMagicAttMaxPowOnClient();
	int MATK = maxMATK;

	int rngMATK = maxMATK - minMATK;
	if( rngMATK > 0 )
		MATK = minMATK + GetServerRandom(0, 20000) % max(1,rngMATK);

	CITP* weapon = m_pc->CPC::GetITPEquipedWeapon();
	if( weapon && (weapon->GetClass() == 10 || weapon->GetClass() == 23) )
		MATK = (int)(MATK * 1.15);

	int par1 = m_pc->GetEffective(113, 0);
	if( par1 && par1 & 0xFFFFFF00 )
	{
		int percent = m_pc->GetEffective(113, 0) & 0xFF;
		MATK = MATK * (percent + 100) / 100;

		m_pc->m_characterInfo.virtue &= ~0x100;

		PACKET_ZC_MSG_STATE_CHANGE outpacket;
		outpacket.PacketType = HEADER_ZC_MSG_STATE_CHANGE;
		outpacket.index = EFST_MAGICPOWER;
		outpacket.AID = m_pc->GetAccountID();
		outpacket.state = 0;
		m_pc->CPC::Send(sizeof(outpacket), (char*)&outpacket);
		m_pc->CCharacter::MultiCast((char*)&outpacket, sizeof(outpacket));
	}

	return MATK;
}


hook_method<int (CPCBattle::*)(unsigned long itemclass, unsigned short scale)> CPCBattle::_GetDamagePercent(SERVER, "CPCBattle::GetDamagePercent");
int CPCBattle::GetDamagePercent(unsigned long itemclass, unsigned short scale)
{
	return (this->*_GetDamagePercent)(itemclass, scale);

	//TODO
}


hook_method<int (CPCBattle::*)(int SKID, int who)> CPCBattle::_GetDamagePercent_SKID(SERVER, "CPCBattle::GetDamagePercent_SKID");
int CPCBattle::GetDamagePercent_SKID(int SKID, int who)
{
	return (this->*_GetDamagePercent_SKID)(SKID, who);

	//TODO
}


hook_method<int (CPCBattle::*)(unsigned short ITID)> CPCBattle::_GetHealPercent_ITEM(SERVER, "CPCBattle::GetHealPercent_ITEM");
int CPCBattle::GetHealPercent_ITEM(unsigned short ITID)
{
	return (this->*_GetHealPercent_ITEM)(ITID);

	//TODO
}


//hook_method<mystd::map<unsigned short,int>& (CPCBattle::*)(int race)> CPCBattle::_GetDropItemList_KILL(SERVER, "CPCBattle::GetDropItemList_KILL");
mystd::map<unsigned short,int>& CPCBattle::GetDropItemList_KILL(int race)
{
//	return (this->*_GetDropItemList_KILL)(race);

	return m_dropItemOfRace_KILL[race];
}


hook_method<int (CPCBattle::*)(CSkillTypeInfo* SKTypeInfo, short skLevel, CCharacter* ch, int x, int y, int spCost)> CPCBattle::_GetSKCastingTM(SERVER, "CPCBattle::GetSKCastingTM");
int CPCBattle::GetSKCastingTM(CSkillTypeInfo* SKTypeInfo, short skLevel, CCharacter* ch, int x, int y, int spCost)
{
	return (this->*_GetSKCastingTM)(SKTypeInfo, skLevel, ch, x, y, spCost);

	//TODO
}


/* hook_method<int (CPCBattle::*)(unsigned short SKID, short skLevel, int in_castTM)> CPCBattle::_GetSoulLinkSKCastingTM(SERVER, "CPCBattle::GetSoulLinkSKCastingTM");
int CPCBattle::GetSoulLinkSKCastingTM(unsigned short SKID, short skLevel, int in_castTM)
{
	return (this->*_GetSoulLinkSKCastingTM)(SKID, skLevel, in_castTM);

	//TODO
} */


hook_method<void (CPCBattle::*)(unsigned short ITID, int percent)> CPCBattle::_SetHealPercent_ITEM(SERVER, "CPCBattle::SetHealPercent_ITEM");
void CPCBattle::SetHealPercent_ITEM(unsigned short ITID, int percent)
{
	return (this->*_SetHealPercent_ITEM)(ITID, percent);

	//TODO
}


hook_method<void (CPCBattle::*)(int SKID, int level, int percent, int who)> CPCBattle::_SetAutoSpellInfo(SERVER, "CPCBattle::SetAutoSpellInfo");
void CPCBattle::SetAutoSpellInfo(int SKID, int level, int percent, int who)
{
	return (this->*_SetAutoSpellInfo)(SKID, level, percent, who);

	//TODO
}


hook_method<void (CPCBattle::*)(unsigned short SKID, unsigned short level, int percent, unsigned short who)> CPCBattle::_SetAutoSpell_MLEATKED(SERVER, "CPCBattle::SetAutoSpell_MLEATKED");
void CPCBattle::SetAutoSpell_MLEATKED(unsigned short SKID, unsigned short level, int percent, unsigned short who)
{
	return (this->*_SetAutoSpell_MLEATKED)(SKID, level, percent, who);

	//TODO
}


hook_method<void (CPCBattle::*)(unsigned short SKID, unsigned short level, int percent, unsigned short who)> CPCBattle::_SetAutoSpell_MAGATKED(SERVER, "CPCBattle::SetAutoSpell_MAGATKED");
void CPCBattle::SetAutoSpell_MAGATKED(unsigned short SKID, unsigned short level, int percent, unsigned short who)
{
	return (this->*_SetAutoSpell_MAGATKED)(SKID, level, percent, who);

	//TODO
}


hook_method<void (CPCBattle::*)(unsigned short SKID, unsigned short level, int percent, unsigned short who)> CPCBattle::_SetAutoSpell_MLEATK(SERVER, "CPCBattle::SetAutoSpell_MLEATK");
void CPCBattle::SetAutoSpell_MLEATK(unsigned short SKID, unsigned short level, int percent, unsigned short who)
{
	return (this->*_SetAutoSpell_MLEATK)(SKID, level, percent, who);

	//TODO
}


hook_method<void (CPCBattle::*)(unsigned short SKID, unsigned short level, int percent, unsigned short who)> CPCBattle::_SetAutoSpell_RANGEATK(SERVER, "CPCBattle::SetAutoSpell_RANGEATK");
void CPCBattle::SetAutoSpell_RANGEATK(unsigned short SKID, unsigned short level, int percent, unsigned short who)
{
	return (this->*_SetAutoSpell_RANGEATK)(SKID, level, percent, who);

	//TODO
}


hook_method<void (CPCBattle::*)(int SKID, int range)> CPCBattle::_SetPushingSkill(SERVER, "CPCBattle::SetPushingSkill");
void CPCBattle::SetPushingSkill(int SKID, int range)
{
	return (this->*_SetPushingSkill)(SKID, range);

	//TODO
}


hook_method<void (CPCBattle::*)(int SKID, unsigned long time, int val)> CPCBattle::_SetATKPercentInfo(SERVER, "CPCBattle::SetATKPercentInfo");
void CPCBattle::SetATKPercentInfo(int SKID, unsigned long time, int val)
{
	return (this->*_SetATKPercentInfo)(SKID, time, val);

	//TODO
}


hook_method<void (CPCBattle::*)(int SKID, unsigned long time, int val)> CPCBattle::_SetDEFPercentInfo(SERVER, "CPCBattle::SetDEFPercentInfo");
void CPCBattle::SetDEFPercentInfo(int SKID, unsigned long time, int val)
{
	return (this->*_SetDEFPercentInfo)(SKID, time, val);

	//TODO
}


hook_method<void (CPCBattle::*)(int SKID, unsigned long time, int val)> CPCBattle::_SetMATKPercentInfo(SERVER, "CPCBattle::SetMATKPercentInfo");
void CPCBattle::SetMATKPercentInfo(int SKID, unsigned long time, int val)
{
	return (this->*_SetMATKPercentInfo)(SKID, time, val);

	//TODO
}


hook_method<void (CPCBattle::*)(int SKID, unsigned long time, int val)> CPCBattle::_SetMDEFPercentInfo(SERVER, "CPCBattle::SetMDEFPercentInfo");
void CPCBattle::SetMDEFPercentInfo(int SKID, unsigned long time, int val)
{
	return (this->*_SetMDEFPercentInfo)(SKID, time, val);

	//TODO
}


hook_method<void (CPCBattle::*)(unsigned short property, int val, unsigned short who)> CPCBattle::_SetDamagePercent_PROP(SERVER, "CPCBattle::SetDamagePercent_PROP");
void CPCBattle::SetDamagePercent_PROP(unsigned short property, int val, unsigned short who)
{
	return (this->*_SetDamagePercent_PROP)(property, val, who);

	//TODO
}


hook_method<void (CPCBattle::*)(unsigned short SKID, int val, unsigned short who)> CPCBattle::_SetDamagePercent_SKID(SERVER, "CPCBattle::SetDamagePercent_SKID");
void CPCBattle::SetDamagePercent_SKID(unsigned short SKID, int val, unsigned short who)
{
	return (this->*_SetDamagePercent_SKID)(SKID, val, who);

	//TODO
}


hook_method<void (CPCBattle::*)(unsigned short monJOB, int val, unsigned short who)> CPCBattle::_SetDamagePercent_MON(SERVER, "CPCBattle::SetDamagePercent_MON");
void CPCBattle::SetDamagePercent_MON(unsigned short monJOB, int val, unsigned short who)
{
	return (this->*_SetDamagePercent_MON)(monJOB, val, who);

	//TODO
}


hook_method<void (CPCBattle::*)(unsigned short monJOB, int val, unsigned short who)> CPCBattle::_SetMagicDamagePercent_MON(SERVER, "CPCBattle::SetMagicDamagePercent_MON");
void CPCBattle::SetMagicDamagePercent_MON(unsigned short monJOB, int val, unsigned short who)
{
	return (this->*_SetMagicDamagePercent_MON)(monJOB, val, who);

	//TODO
}


hook_method<void (CPCBattle::*)(int state, int val, unsigned short who)> CPCBattle::_SetBadState_ArrowATK(SERVER, "CPCBattle::SetBadState_ArrowATK");
void CPCBattle::SetBadState_ArrowATK(int state, int val, unsigned short who)
{
	return (this->*_SetBadState_ArrowATK)(state, val, who);

	//TODO
}


hook_method<void (CPCBattle::*)(int state, int val, unsigned short who)> CPCBattle::_SetBadState_MLEATK(SERVER, "CPCBattle::SetBadState_MLEATK");
void CPCBattle::SetBadState_MLEATK(int state, int val, unsigned short who)
{
	return (this->*_SetBadState_MLEATK)(state, val, who);

	//TODO
}


hook_method<void (CPCBattle::*)(int state, int val, unsigned short who)> CPCBattle::_SetBadState_MLEAttacked(SERVER, "CPCBattle::SetBadState_MLEAttacked");
void CPCBattle::SetBadState_MLEAttacked(int state, int val, unsigned short who)
{
	return (this->*_SetBadState_MLEAttacked)(state, val, who);

	//TODO
}


hook_method<void (CPCBattle::*)(int state, int val, unsigned short who)> CPCBattle::_SetBadState_MATK(SERVER, "CPCBattle::SetBadState_MATK");
void CPCBattle::SetBadState_MATK(int state, int val, unsigned short who)
{
	return (this->*_SetBadState_MATK)(state, val, who);

	//TODO
}


hook_method<void (CPCBattle::*)(int state, int val, unsigned short who)> CPCBattle::_SetBadState_MAttacked(SERVER, "CPCBattle::SetBadState_MAttacked");
void CPCBattle::SetBadState_MAttacked(int state, int val, unsigned short who)
{
	return (this->*_SetBadState_MAttacked)(state, val, who);

	//TODO
}


hook_method<void (CPCBattle::*)(int race, unsigned short ITID, int percent)> CPCBattle::_SetDropItemOfRace_KILL(SERVER, "CPCBattle::SetDropItemOfRace_KILL");
void CPCBattle::SetDropItemOfRace_KILL(int race, unsigned short ITID, int percent)
{
	return (this->*_SetDropItemOfRace_KILL)(race, ITID, percent);

	//TODO
}


hook_method<void (CPCBattle::*)(unsigned short ITID, unsigned short prop, int amount, int time, unsigned short who)> CPCBattle::_SetDamage_PropTM(SERVER, "CPCBattle::SetDamage_PropTM");
void CPCBattle::SetDamage_PropTM(unsigned short ITID, unsigned short prop, int amount, int time, unsigned short who)
{
	return (this->*_SetDamage_PropTM)(ITID, prop, amount, time, who);

	//TODO
}


hook_method<void (CPCBattle::*)(int SKID, int who)> CPCBattle::_ResetAutoSpellInfo(SERVER, "CPCBattle::ResetAutoSpellInfo");
void CPCBattle::ResetAutoSpellInfo(int SKID, int who)
{
	return (this->*_ResetAutoSpellInfo)(SKID, who);

	//TODO
}


hook_method<void (CPCBattle::*)(int SKID)> CPCBattle::_ResetPushingSkill(SERVER, "CPCBattle::ResetPushingSkill");
void CPCBattle::ResetPushingSkill(int SKID)
{
	return (this->*_ResetPushingSkill)(SKID);

	//TODO
}


hook_method<void (CPCBattle::*)(int SKID)> CPCBattle::_ResetATKPercentInfo(SERVER, "CPCBattle::ResetATKPercentInfo");
void CPCBattle::ResetATKPercentInfo(int SKID)
{
	return (this->*_ResetATKPercentInfo)(SKID);

	//TODO
}


hook_method<void (CPCBattle::*)(int SKID)> CPCBattle::_ResetDEFPercentInfo(SERVER, "CPCBattle::ResetDEFPercentInfo");
void CPCBattle::ResetDEFPercentInfo(int SKID)
{
	return (this->*_ResetDEFPercentInfo)(SKID);

	//TODO
}


hook_method<void (CPCBattle::*)(int SKID)> CPCBattle::_ResetMATKPercentInfo(SERVER, "CPCBattle::ResetMATKPercentInfo");
void CPCBattle::ResetMATKPercentInfo(int SKID)
{
	return (this->*_ResetMATKPercentInfo)(SKID);

	//TODO
}


hook_method<void (CPCBattle::*)(int SKID)> CPCBattle::_ResetMDEFPercentInfo(SERVER, "CPCBattle::ResetMDEFPercentInfo");
void CPCBattle::ResetMDEFPercentInfo(int SKID)
{
	return (this->*_ResetMDEFPercentInfo)(SKID);

	//TODO
}


hook_method<void (CPCBattle::*)(CCharacter* other, int& damage, int isRNGATK, int isSKATK, int isCRI)> CPCBattle::_ModifyDamage_ATK(SERVER, "CPCBattle::ModifyDamage_ATK");
HOOKED void CPCBattle::ModifyDamage_ATK(CCharacter* other, int& damage, int isRNGATK, int isSKATK, int isCRI)
{
	(this->*_ModifyDamage_ATK)(other, damage, isRNGATK, isSKATK, isCRI);
	int jobid;
	if( other->GetParameterValue(VAR_JOB, jobid) && jobid == JT_EMPELIUM )
		damage = ModifyDamage_Emperium(damage);
	return;

	if( damage <= 0 )
		return;

	int property, race = 0, scale, otherClass;
	eObjectType otherType = (eObjectType)other->GetType();
	other->GetParameterValue(VAR_CURRENTSTATE, property);
	other->GetParameterValue(VAR_RACE, race);
	other->GetParameterValue(VAR_SCALE, scale);
	other->GetParameterValue(VAR_CLASS, otherClass);

	CharacterInfo* charInfo = &m_pc->m_characterInfo;

	int PROP = property - property / 10 * 10; // poor man's modulo operator
	mystd::map<unsigned short,int>::const_iterator itPROP = m_damagePercent_PROP[1].find(PROP);
	if( itPROP != m_damagePercent_PROP[1].end() ) damage += damage * itPROP->second / 100;

	int factorRace = charInfo->plusByRace[race];
	if( factorRace != 0 ) damage += damage * factorRace / 100;

	int factorScale = m_optionInfo.damagePercent_Scale[1][scale];
	if( factorScale != 0 ) damage += damage * factorScale / 100;

	if( isRNGATK )
	{
		int factorRanged = charInfo->modifyDamge_RNGATK[1];
		if( factorRanged != 0 ) damage += damage * factorRanged / 100;
	}

	int factorClass = charInfo->userTarInfo[1].plusDamageByClass[otherClass];
	if( factorClass != 0 ) damage += damage * factorClass / 100;

	if( m_damagePercent_MON[1].size() >= 1 )
	{
		int job;
		other->GetParameterValue(VAR_JOB, job);
		mystd::map<unsigned short,int>::const_iterator itMON = m_damagePercent_MON[1].find(job);
		if( itMON != m_damagePercent_MON[1].end() ) damage += damage * itMON->second / 100;
	}

	if( isCRI )
	{
		int factorCRI = m_optionInfo.damagePercent_CRI[1];
		if( factorCRI != 0 ) damage += damage * factorCRI / 100;
	}

	if( damage <= 0 )
		return;

	if( isRNGATK )
	{// ranged status effect
		mystd::map<unsigned short,unsigned short>::const_iterator it;
		for( it = m_badState_ArrowATK[1].begin(); it != m_badState_ArrowATK[1].end(); ++it )
		{
			int state = it->first;
			int percent = it->second;
			m_pc->SetHandicapState(state, other, percent, m_pc->CPC::GetAttackMotionTime() + 500, 0, 0, 0);
		}
	}
	else
	{// melee status effect
		for( int i = 0; i < countof(m_badState_MLEATK); ++i )
		{
			CCharacter* target;
			int delay;
			if( i == 0 )
			{
				target = m_pc;
				delay = m_pc->CPC::GetAttackedMotionTime();
			}
			else
			{
				target = other;
				delay = m_pc->CPC::GetAttackMotionTime() + 500;
			}

			mystd::map<unsigned short,unsigned short>::const_iterator it;
			for( it = m_badState_MLEATK[i].begin(); it != m_badState_MLEATK[i].end(); ++it )
			{
				int state = it->first;
				int percent = it->second;
				m_pc->SetHandicapState(state, target, percent, delay, 0, 0, 0);
			}
		}
	}

	if( otherType == NPC_MOB_TYPE )
	{
		if( !isRNGATK && !isSKATK && m_pc->m_pcSkill.CPCSkill::GetSkillLevel(SKID_RG_SNATCHER, 0) >= 1 )
		{
			int lvlSNATCHER = m_pc->m_pcSkill.CPCSkill::GetSkillLevel(SKID_RG_SNATCHER, 0);
			int rateSNATCHER = g_skillTypeInfoMgr->CSkillTypeInfoMgr::SendMsg(0, SKID_RG_SNATCHER, 14, lvlSNATCHER, 0, 0, 0);
			if( rateSNATCHER > GetServerRandom(0, 20000) % 100 )
			{
				short lvlSTEAL = m_pc->m_pcSkill.CPCSkill::GetSkillLevel(SKID_TF_STEAL, 0);
				m_pc->m_pcSkill.CPCSkill::UpdateSkillType(SKID_TF_STEAL, 3, lvlSTEAL);
				g_characterMgr->CCharacterMgr::SendMsg(m_pc, m_pc, CM_USE_SKILL, SKID_TF_STEAL, other->GetAccountID(), lvlSTEAL, 0);
			}
		}

		if( otherClass != NPC_CLASS_BOSS )
		{
			int rateWeapon = m_pc->GetEffective(EFST_MELTDOWN, 0);
			if( rateWeapon > 0 && rateWeapon > GetServerRandom(0, 20000) % 10000 )
				static_cast<CNPC*>(other)->CNPC::SetATKPercentInfo(SKID_WS_MELTDOWN, 5000, -25);
			else
			{
				int rateArmor = m_pc->GetEffective(EFST_MELTDOWN, 1);
				if( rateArmor > 0 && rateArmor > GetServerRandom(0, 20000) % 10000 )
					static_cast<CNPC*>(other)->CNPC::SetDEFPercentInfo(SKID_WS_MELTDOWN, 5000, -25);
			}
		}
	}
	else
	if( otherType == PC_TYPE )
	{
		if( charInfo->attackDamageWeapon[1] && charInfo->attackDamageWeapon[1] > GetServerRandom(0, 20000) % 100 )
			g_characterMgr->CCharacterMgr::SendMsg(NULL, other, CM_DAMAGE_WEAPON, 0, 0, 0, 0);

		if( charInfo->attackDamageArmor[1] && charInfo->attackDamageArmor[1] > GetServerRandom(0, 20000) % 100 )
			g_characterMgr->CCharacterMgr::SendMsg(NULL, other, CM_DAMAGE_ARMOR, 0, 0, 0, 0);

		int rateWeapon = m_pc->GetEffective(EFST_MELTDOWN, 0);
		if( rateWeapon > 0 && rateWeapon > GetServerRandom(0, 20000) % 10000 )
			g_characterMgr->CCharacterMgr::SendMsg(NULL, other, CM_DAMAGE_WEAPON, 0, 0, 0, 0);
		else
		{
			int rateArmor = m_pc->GetEffective(EFST_MELTDOWN, 1);
			if( rateArmor > 0 && rateArmor > GetServerRandom(0, 20000) % 10000 )
				g_characterMgr->CCharacterMgr::SendMsg(NULL, other, CM_DAMAGE_ARMOR, 0, 0, 0, 0);
		}
	}

	if( CPC::GetCategorySecondJob(m_pc->m_characterInfo.job) == JT_STAR )
	{
		if( otherType == NPC_MOB_TYPE )
		{
			int otherJobType;
			other->GetParameterValue(VAR_JOB, otherJobType);

			if( m_pc->GetEffective(EFST_SKE, 0) )
			{// miracle of the sun, moon and stars
				int rate = 100 + 20 * m_pc->m_pcSkill.CPCSkill::GetSkillLevel(SKID_SG_STAR_BLESS, 0);
				g_characterMgr->CCharacterMgr::SendMsg(NULL, other, CM_SETEFFECTIVE, EFST_EXPUP, 3000, rate, 0);
			}
			else
			if( otherJobType == m_pc->m_pcSkill.CPCSkill::GetWarpInfoXpos(2) )
			{// blessing of the stars
				SYSTEMTIME curTime;
				GetLocalTime(&curTime);
				if( curTime.wDay % 5 == 0 )
				{
					int rate = 100 + 20 * m_pc->m_pcSkill.CPCSkill::GetSkillLevel(SKID_SG_STAR_BLESS, 0);
					g_characterMgr->CCharacterMgr::SendMsg(NULL, other, CM_SETEFFECTIVE, EFST_EXPUP, 3000, rate, 0);
				}
			}
			else
			if( otherJobType == m_pc->m_pcSkill.CPCSkill::GetWarpInfoXpos(1) )
			{// blessing of the moon
				SYSTEMTIME curTime;
				GetLocalTime(&curTime);
				if( curTime.wDay % 2 == 1 )
				{
					int rate = 100 + 10 * m_pc->m_pcSkill.CPCSkill::GetSkillLevel(SKID_SG_MOON_BLESS, 0);
					g_characterMgr->CCharacterMgr::SendMsg(NULL, other, CM_SETEFFECTIVE, EFST_EXPUP, 3000, rate, 0);
				}
			}
			else
			if( otherJobType == m_pc->m_pcSkill.CPCSkill::GetWarpInfoXpos(0) )
			{// blessing of the sun
				SYSTEMTIME curTime;
				GetLocalTime(&curTime);
				if( curTime.wDay %2 == 0 )
				{
					int rate = 100 + 10 * m_pc->m_pcSkill.CPCSkill::GetSkillLevel(SKID_SG_SUN_BLESS, 0);
					g_characterMgr->CCharacterMgr::SendMsg(NULL, other, CM_SETEFFECTIVE, EFST_EXPUP, 3000, rate, 0);
				}
			}
		}

		// miracle of the sun, moon and stars activation check
		if( GetServerRandom(0, 20000) % 20000 == 27 ) // 1:20000 chance
		{
			int agi;
			m_pc->GetParameterValue(VAR_AGI, agi);
			if( agi == 0 )
				agi = 1;
			if( GetServerRandom(0, 20000) % agi <= 45 ) // 46:agi chance
				m_pc->SetEffective(EFST_SKE, 3600000, 1, 0, 0, 1);
		}
	}

	int lvlEDP = m_pc->GetEffective(EFST_EDP, 0);
	if( lvlEDP > 0 )
	{
		damage = damage * m_pc->GetEffective(EFST_EDP, 1) / 100;
		m_pc->SetHandicapState(HEALTH_HEAVYPOISON, other, lvlEDP, m_pc->CPC::GetAttackMotionTime(), 0, 0, 0);
	}
	else
	{
		int lvlPOISON = m_pc->GetEffective(EFST_ENCHANTPOISON, 0);
		if( lvlPOISON > 0 )
		{
			m_pc->SetHandicapState(HEALTH_POISON, other, lvlPOISON, m_pc->CPC::GetAttackMotionTime(), 0, 0, 0);
		}
	}

	if( m_pc->GetEffective(EFST_SUB_WEAPONPROPERTY, 0) > 0 )
	{
		int prop0val = m_pc->GetEffective(EFST_SUB_WEAPONPROPERTY, 0);
		int prop1val = m_pc->GetEffective(EFST_SUB_WEAPONPROPERTY, 1);
		damage += prop0val * m_pc->CPC::GetAttackFinalDamage(other, 2, prop1val, 100, 100, 1, 0, 0, 0) / 100;
	}

	CITP* itpWEAPON = m_pc->CPC::GetITPEquipedWeapon();
	if( itpWEAPON != NULL && itpWEAPON->GetClass() == WEAPONTYPE_CATARRH )
	{
		int lvlKATAR = m_pc->m_pcSkill.CPCSkill::GetSkillLevel(SKID_ASC_KATAR, 0);
		int rateKATAR = g_skillTypeInfoMgr->CSkillTypeInfoMgr::SendMsg(NULL, SKID_ASC_KATAR, 14, lvlKATAR, 0, 0, 0);
		damage += damage * rateKATAR / 100;
	}
}


hook_method<void (CPCBattle::*)(CCharacter* other, int& damage, int isRNGATK, int type, int property, int SKID, int isArrowProperty)> CPCBattle::_ModifyDamage_ATKED(SERVER, "CPCBattle::ModifyDamage_ATKED");
void CPCBattle::ModifyDamage_ATKED(CCharacter* other, int& damage, int isRNGATK, int type, int property, int SKID, int isArrowProperty)
{
	return (this->*_ModifyDamage_ATKED)(other, damage, isRNGATK, type, property, SKID, isArrowProperty);

	//TODO
}


hook_method<void (CPCBattle::*)(CCharacter* other, int& damage)> CPCBattle::_ModifyDamage_MATK(SERVER, "CPCBattle::ModifyDamage_MATK");
void CPCBattle::ModifyDamage_MATK(CCharacter* other, int& damage)
{
	return (this->*_ModifyDamage_MATK)(other, damage);

	//TODO
}


hook_method<void (CPCBattle::*)(CCharacter* other, int damage, int isMeleeATK, int isSKATK)> CPCBattle::_ProcessEffect_ATK(SERVER, "CPCBattle::ProcessEffect_ATK");
void CPCBattle::ProcessEffect_ATK(CCharacter* other, int damage, int isMeleeATK, int isSKATK)
{
	return (this->*_ProcessEffect_ATK)(other, damage, isMeleeATK, isSKATK);

	//TODO
}


hook_method<void (CPCBattle::*)(CCharacter* other, int isMLEATK, unsigned short SKID)> CPCBattle::_ProcessEffectOnKill(SERVER, "CPCBattle::ProcessEffectOnKill");
void CPCBattle::ProcessEffectOnKill(CCharacter* other, int isMLEATK, unsigned short SKID)
{
	return (this->*_ProcessEffectOnKill)(other, isMLEATK, SKID);

	//TODO
}


hook_method<void (CPCBattle::*)(CCharacter* other, int isMLEATK, int isMATK, unsigned short SKID, int in_Damage)> CPCBattle::_ApplyEffect_ATKED(SERVER, "CPCBattle::ApplyEffect_ATKED");
void CPCBattle::ApplyEffect_ATKED(CCharacter* other, int isMLEATK, int isMATK, unsigned short SKID, int in_Damage)
{
	return (this->*_ApplyEffect_ATKED)(other, isMLEATK, isMATK, SKID, in_Damage);

	//TODO
}


hook_method<int (CPCBattle::*)(CCharacter* other, SKILLATTACK_MSG* msg, int damage)> CPCBattle::_ReflectMagic(SERVER, "CPCBattle::ReflectMagic");
int CPCBattle::ReflectMagic(CCharacter* other, SKILLATTACK_MSG* msg, int damage)
{
	return (this->*_ReflectMagic)(other, msg, damage);

	//TODO
}


hook_method<int (CPCBattle::*)(CCharacter* other, int SKID)> CPCBattle::_IsImmuneMagic(SERVER, "CPCBattle::IsImmuneMagic");
int CPCBattle::IsImmuneMagic(CCharacter* other, int SKID)
{
	return (this->*_IsImmuneMagic)(other, SKID);

	//TODO
}


hook_method<void (CPCBattle::*)(int SKID, int target, int level, int spCost)> CPCBattle::_OnDoubleCasting(SERVER, "CPCBattle::OnDoubleCasting");
void CPCBattle::OnDoubleCasting(int SKID, int target, int level, int spCost)
{
	return (this->*_OnDoubleCasting)(SKID, target, level, spCost);

	//TODO
}


hook_method<int (CPCBattle::*)(CCharacter* other)> CPCBattle::_SetEffectiveByTarotCard(SERVER, "CPCBattle::SetEffectiveByTarotCard");
int CPCBattle::SetEffectiveByTarotCard(CCharacter* other)
{
	return (this->*_SetEffectiveByTarotCard)(other);

	//TODO
}


hook_method<void (CPCBattle::*)(unsigned short SKID, int percent)> CPCBattle::_SetSkillCastTimePercent(SERVER, "CPCBattle::SetSkillCastTimePercent");
void CPCBattle::SetSkillCastTimePercent(unsigned short SKID, int percent)
{
	return (this->*_SetSkillCastTimePercent)(SKID, percent);

	//TODO
}


hook_method<int (CPCBattle::*)(unsigned short SKID)> CPCBattle::_GetSkillCastTimePercent(SERVER, "CPCBattle::GetSkillCastTimePercent");
int CPCBattle::GetSkillCastTimePercent(unsigned short SKID)
{
	return (this->*_GetSkillCastTimePercent)(SKID);

	//TODO
}


hook_method<void (CPCBattle::*)(unsigned short itemID, unsigned long term, short amount)> CPCBattle::_SetHPAmountTime(SERVER, "CPCBattle::SetHPAmountTime");
void CPCBattle::SetHPAmountTime(unsigned short itemID, unsigned long term, short amount)
{
	return (this->*_SetHPAmountTime)(itemID, term, amount);

	//TODO
}


hook_method<void (CPCBattle::*)(unsigned short itemID, unsigned long term, short amount)> CPCBattle::_SetSPAmountTime(SERVER, "CPCBattle::SetSPAmountTime");
void CPCBattle::SetSPAmountTime(unsigned short itemID, unsigned long term, short amount)
{
	return (this->*_SetSPAmountTime)(itemID, term, amount);

	//TODO
}


hook_method<void (CPCBattle::*)(unsigned short itemID, unsigned long term, short amount)> CPCBattle::_SetHPPercentTime(SERVER, "CPCBattle::SetHPPercentTime");
void CPCBattle::SetHPPercentTime(unsigned short itemID, unsigned long term, short amount)
{
	return (this->*_SetHPPercentTime)(itemID, term, amount);

	//TODO
}


hook_method<void (CPCBattle::*)(unsigned short itemID, unsigned long term, short amount)> CPCBattle::_SetSPPercentTime(SERVER, "CPCBattle::SetSPPercentTime");
void CPCBattle::SetSPPercentTime(unsigned short itemID, unsigned long term, short amount)
{
	return (this->*_SetSPPercentTime)(itemID, term, amount);

	//TODO
}


hook_method<void (CPCBattle::*)(void)> CPCBattle::_ProcessItemHealRegularly(SERVER, "CPCBattle::ProcessItemHealRegularly");
void CPCBattle::ProcessItemHealRegularly(void)
{
	return (this->*_ProcessItemHealRegularly)();

	//TODO
}


hook_method<void (CPCBattle::*)(unsigned long checkSKID, unsigned long percent, unsigned long autospellSKID, short autospellSKLV, short who)> CPCBattle::_SetSkillAutoSpell(SERVER, "CPCBattle::SetSkillAutoSpell");
void CPCBattle::SetSkillAutoSpell(unsigned long checkSKID, unsigned long percent, unsigned long autospellSKID, short autospellSKLV, short who)
{
	return (this->*_SetSkillAutoSpell)(checkSKID, percent, autospellSKID, autospellSKLV, who);

	//TODO
}


hook_method<void (CPCBattle::*)(unsigned long checkSKID, unsigned long percent, unsigned long autospellSKID, short autospellSKLV, short who)> CPCBattle::_ResetSkillAutoSpell(SERVER, "CPCBattle::ResetSkillAutoSpell");
void CPCBattle::ResetSkillAutoSpell(unsigned long checkSKID, unsigned long percent, unsigned long autospellSKID, short autospellSKLV, short who)
{
	return (this->*_ResetSkillAutoSpell)(checkSKID, percent, autospellSKID, autospellSKLV, who);

	//TODO
}


hook_method<void (CPCBattle::*)(HOMUN_DBINFO* info)> CPCBattle::_SetHomunDBInfo(SERVER, "CPCBattle::SetHomunDBInfo");
void CPCBattle::SetHomunDBInfo(HOMUN_DBINFO* info)
{
	return (this->*_SetHomunDBInfo)(info);

	//TODO
}


hook_method<CNpcHomun* (CPCBattle::*)(short state)> CPCBattle::_CallHomun(SERVER, "CPCBattle::CallHomun");
CNpcHomun* CPCBattle::CallHomun(short state)
{
	return (this->*_CallHomun)(state);

	//TODO
}


hook_method<void (CPCBattle::*)(void)> CPCBattle::_RemoveHomun(SERVER, "CPCBattle::RemoveHomun");
void CPCBattle::RemoveHomun(void)
{
	return (this->*_RemoveHomun)();

	//TODO
}


//hook_method<void (CPCBattle::*)(int ID)> CPCBattle::_SetMyHomunID(SERVER, "CPCBattle::SetMyHomunID");
void CPCBattle::SetMyHomunID(int ID)
{
//	return (this->*_SetMyHomunID)(ID);

	m_myHomunID = ID;
}


//hook_method<int (CPCBattle::*)(void)> CPCBattle::_GetMyHomunID(SERVER, "CPCBattle::GetMyHomunID");
int CPCBattle::GetMyHomunID(void)
{
//	return (this->*_GetMyHomunID)();

	return m_myHomunID;
}


/* hook_method<HOMUN_DBINFO* (CPCBattle::*)(void)> CPCBattle::_GetHomunDBInfo(SERVER, "CPCBattle::GetHomunDBInfo");
HOMUN_DBINFO* CPCBattle::GetHomunDBInfo(void)
{
	return (this->*_GetHomunDBInfo)();

	//TODO
} */


hook_method<CNpcHomun* (CPCBattle::*)(void)> CPCBattle::_GetMyHomun(SERVER, "CPCBattle::GetMyHomun");
CNpcHomun* CPCBattle::GetMyHomun(void)
{
	return (this->*_GetMyHomun)();

	//TODO
}


hook_method<short (CPCBattle::*)(void)> CPCBattle::_IsCallableHomun(SERVER, "CPCBattle::IsCallableHomun");
short CPCBattle::IsCallableHomun(void)
{
	return (this->*_IsCallableHomun)();

	//TODO
}


hook_method<int  (CPCBattle::*)(int isForce)> CPCBattle::_RestHomun(SERVER, "CPCBattle::RestHomun");
int CPCBattle::RestHomun(int isForce)
{
	return (this->*_RestHomun)(isForce);

	//TODO
}


hook_method<void (CPCBattle::*)(void)> CPCBattle::_EvolutionHomun(SERVER, "CPCBattle::EvolutionHomun");
void CPCBattle::EvolutionHomun(void)
{
	return (this->*_EvolutionHomun)();

	//TODO
}


hook_method<void (CPCBattle::*)(MERSOL_DBINFO* info)> CPCBattle::_SetMerceDBInfo(SERVER, "CPCBattle::SetMerceDBInfo");
void CPCBattle::SetMerceDBInfo(MERSOL_DBINFO* info)
{
	return (this->*_SetMerceDBInfo)(info);

	//TODO
}


/* hook_method<MERSOL_DBINFO* (CPCBattle::*)(void)> CPCBattle::_GetMerceDBInfo(SERVER, "CPCBattle::GetMerceDBInfo");
MERSOL_DBINFO* CPCBattle::GetMerceDBInfo(void)
{
	return (this->*_GetMerceDBInfo)();

	//TODO
} */


hook_method<void (CPCBattle::*)(unsigned short mon_id, unsigned short ITID, int percent)> CPCBattle::_SetDropItemOfMonster_Kill(SERVER, "CPCBattle::SetDropItemOfMonster_Kill");
void CPCBattle::SetDropItemOfMonster_Kill(unsigned short mon_id, unsigned short ITID, int percent)
{
	return (this->*_SetDropItemOfMonster_Kill)(mon_id, ITID, percent);

	//TODO
}


hook_method<bool (CPCBattle::*)(unsigned short mon_id, mystd::map<unsigned short,int>& dropItemList)> CPCBattle::_GetDropItemOfMonster_Kill(SERVER, "CPCBattle::GetDropItemOfMonster_Kill");
bool CPCBattle::GetDropItemOfMonster_Kill(unsigned short mon_id, mystd::map<unsigned short,int>& dropItemList)
{
	return (this->*_GetDropItemOfMonster_Kill)(mon_id, dropItemList);

	mystd::map<unsigned short,mystd::map<unsigned short,int> >::iterator result = this->m_dropItemOfMonster_KILL.find(mon_id);

	if( result == this->m_dropItemOfMonster_KILL.end() )
		return false; // not found

	if( &dropItemList != &result->second )
		dropItemList = result->second; // erase old data, copy new data

	return true;
}


hook_method<bool (CPCBattle::*)(const enum CPCBattle::enumMercenary_CallType in_CallType, const int in_Job)> CPCBattle::_MercenaryCall(SERVER, "CPCBattle::MercenaryCall");
bool CPCBattle::MercenaryCall(const enum CPCBattle::enumMercenary_CallType in_CallType, const int in_Job)
{
	return (this->*_MercenaryCall)(in_CallType, in_Job);

	//TODO
}


hook_method<bool (CPCBattle::*)(const int in_Job)> CPCBattle::_MercenaryCall_Create(SERVER, "CPCBattle::MercenaryCall_Create");
bool CPCBattle::MercenaryCall_Create(const int in_Job)
{
	return (this->*_MercenaryCall_Create)(in_Job);

	//TODO
}


hook_method<bool (CPCBattle::*)(void)> CPCBattle::_MercenaryCall_Load(SERVER, "CPCBattle::MercenaryCall_Load");
bool CPCBattle::MercenaryCall_Load(void)
{
	return (this->*_MercenaryCall_Load)();

	//TODO
}


hook_method<void (CPCBattle::*)(const int in_reason)> CPCBattle::_Mercenary_Delete(SERVER, "CPCBattle::Mercenary_Delete");
void CPCBattle::Mercenary_Delete(const int in_reason)
{
	return (this->*_Mercenary_Delete)(in_reason);

	//TODO
}


hook_method<void (CPCBattle::*)(const bool in_bDisconnect)> CPCBattle::_Mercenary_Release(SERVER, "CPCBattle::Mercenary_Release");
void CPCBattle::Mercenary_Release(const bool in_bDisconnect)
{
	return (this->*_Mercenary_Release)(in_bDisconnect);

	//TODO
}


hook_method<void (CPCBattle::*)(const int in_Job)> CPCBattle::_MercenaryCall_Create_After(SERVER, "CPCBattle::MercenaryCall_Create_After");
void CPCBattle::MercenaryCall_Create_After(const int in_Job)
{
	return (this->*_MercenaryCall_Create_After)(in_Job);

	//TODO
}


hook_method<void (CPCBattle::*)(const int in_reason)> CPCBattle::_MercenaryCall_Delete_After(SERVER, "CPCBattle::MercenaryCall_Delete_After");
void CPCBattle::MercenaryCall_Delete_After(const int in_reason)
{
	return (this->*_MercenaryCall_Delete_After)(in_reason);

	//TODO
}


hook_method<void (CPCBattle::*)(void)> CPCBattle::_Mercenary_TYPICALJOBINFO_CHANGED(SERVER, "CPCBattle::Mercenary_TYPICALJOBINFO_CHANGED");
void CPCBattle::Mercenary_TYPICALJOBINFO_CHANGED(void)
{
	return (this->*_Mercenary_TYPICALJOBINFO_CHANGED)();

	//TODO
}


hook_method<void (CPCBattle::*)(void)> CPCBattle::_Mercenary_SaveToProxyDB(SERVER, "CPCBattle::Mercenary_SaveToProxyDB");
void CPCBattle::Mercenary_SaveToProxyDB(void)
{
	return (this->*_Mercenary_SaveToProxyDB)();

	//TODO
}


hook_method<void (CPCBattle::*)(const int in_ID)> CPCBattle::_SetMercenaryID(SERVER, "CPCBattle::SetMercenaryID");
void CPCBattle::SetMercenaryID(const int in_ID)
{
	return (this->*_SetMercenaryID)(in_ID);

	m_mercenaryID = in_ID;
}


//hook_method<int (CPCBattle::*)(void)> CPCBattle::_GetMercenaryID(SERVER, "CPCBattle::GetMercenaryID");
int CPCBattle::GetMercenaryID(void)
{
//	return (this->*_GetMercenaryID)();

	return m_mercenaryID;
}


/* hook_method<short (CPCBattle::*)(void)> CPCBattle::_GetFaith(SERVER, "CPCBattle::GetFaith");
short CPCBattle::GetFaith(void)
{
	return (this->*_GetFaith)();

	//TODO
} */


/* hook_method<short (CPCBattle::*)(short job)> CPCBattle::_GetSummonCount(SERVER, "CPCBattle::GetSummonCount");
short CPCBattle::GetSummonCount(short job)
{
	return (this->*_GetSummonCount)(job);

	//TODO
} */


/* hook_method<short (CPCBattle::*)(short job)> CPCBattle::_GetMerceType(SERVER, "CPCBattle::GetMerceType");
short CPCBattle::GetMerceType(short job)
{
	return (this->*_GetMerceType)(job);

	//TODO
} */


hook_method<CNpcMercenary* (CPCBattle::*)(void)> CPCBattle::_GetMercenary(SERVER, "CPCBattle::GetMercenary");
CNpcMercenary* CPCBattle::GetMercenary(void)
{
	return (this->*_GetMercenary)();

	//TODO
}


//hook_method<int (CPCBattle::*)(void)> CPCBattle::_GetEnemyAID(SERVER, "CPCBattle::GetEnemyAID");
int CPCBattle::GetEnemyAID(void)
{
//	return (this->*_GetEnemyAID)();

	return m_enemyAID;
}


hook_method<short (CPCBattle::*)(void)> CPCBattle::_GetMercenaryJob(SERVER, "CPCBattle::GetMercenaryJob");
short CPCBattle::GetMercenaryJob(void)
{
	return (this->*_GetMercenaryJob)();

	//TODO
}


hook_method<int (CPCBattle::*)(void)> CPCBattle::_GetMercenary_Type(SERVER, "CPCBattle::GetMercenary_Type");
int CPCBattle::GetMercenary_Type(void)
{
	return (this->*_GetMercenary_Type)();

	//TODO
}


hook_method<void (CPCBattle::*)(unsigned long checkSKID, CCharacter* target, short xPos, short yPos)> CPCBattle::_CheckSkillSpecialOption(SERVER, "CPCBattle::CheckSkillSpecialOption");
void CPCBattle::CheckSkillSpecialOption(unsigned long checkSKID, CCharacter* target, short xPos, short yPos)
{
	return (this->*_CheckSkillSpecialOption)(checkSKID, target, xPos, yPos);

	//TODO
}


//hook_method<unsigned long (CPCBattle::*)(void)> CPCBattle::_GetActivatedSkill(SERVER, "CPCBattle::GetActivatedSkill");
unsigned long CPCBattle::GetActivatedSkill(void)
{
//	return (this->*_GetActivatedSkill)();

	return m_skillActiveInfo.lastActivatedSkill;
}


//hook_method<unsigned long (CPCBattle::*)(void)> CPCBattle::_GetDeactivatedSkill(SERVER, "CPCBattle::GetDeactivatedSkill");
unsigned long CPCBattle::GetDeactivatedSkill(void)
{
//	return (this->*_GetDeactivatedSkill)();

	return m_skillActiveInfo.lastDeactivatedSkill;
}


hook_method<void (CPCBattle::*)(unsigned long itemID, unsigned long checkSKID, unsigned long percent, unsigned long time)> CPCBattle::_SetSkillActivate(SERVER, "CPCBattle::SetSkillActivate");
void CPCBattle::SetSkillActivate(unsigned long itemID, unsigned long checkSKID, unsigned long percent, unsigned long time)
{
	return (this->*_SetSkillActivate)(itemID, checkSKID, percent, time);

	//TODO
}


hook_method<void (CPCBattle::*)(unsigned long itemID, unsigned long checkSKID, unsigned long percent, unsigned long time)> CPCBattle::_ResetSkillActivate(SERVER, "CPCBattle::ResetSkillActivate");
void CPCBattle::ResetSkillActivate(unsigned long itemID, unsigned long checkSKID, unsigned long percent, unsigned long time)
{
	return (this->*_ResetSkillActivate)(itemID, checkSKID, percent, time);

	//TODO
}


hook_method<void (CPCBattle::*)(short who, unsigned long SKID, short state, int percent)> CPCBattle::_AddState_SKID(SERVER, "CPCBattle::AddState_SKID");
void CPCBattle::AddState_SKID(short who, unsigned long SKID, short state, int percent)
{
	return (this->*_AddState_SKID)(who, SKID, state, percent);

	//TODO
}


hook_method<void (CPCBattle::*)(short who, unsigned long SKID, short state, int percent)> CPCBattle::_SubState_SKID(SERVER, "CPCBattle::SubState_SKID");
void CPCBattle::SubState_SKID(short who, unsigned long SKID, short state, int percent)
{
	return (this->*_SubState_SKID)(who, SKID, state, percent);

	//TODO
}


hook_method<void (CPCBattle::*)(unsigned long SKID, short level, short who, int percent)> CPCBattle::_SetAutoSpellMagic(SERVER, "CPCBattle::SetAutoSpellMagic");
void CPCBattle::SetAutoSpellMagic(unsigned long SKID, short level, short who, int percent)
{
	return (this->*_SetAutoSpellMagic)(SKID, level, who, percent);

	//TODO
}


hook_method<void (CPCBattle::*)(unsigned long SKID, short level, short who, int percent)> CPCBattle::_ResetAutoSpellMagic(SERVER, "CPCBattle::ResetAutoSpellMagic");
void CPCBattle::ResetAutoSpellMagic(unsigned long SKID, short level, short who, int percent)
{
	return (this->*_ResetAutoSpellMagic)(SKID, level, who, percent);

	//TODO
}


hook_method<void (CPCBattle::*)(CCharacter* other, int damage)> CPCBattle::_ReflectDamage(SERVER, "CPCBattle::ReflectDamage");
void CPCBattle::ReflectDamage(CCharacter* other, int damage)
{
	return (this->*_ReflectDamage)(other, damage);

	//TODO
}


hook_method<void (CPCBattle::*)(CCharacter* other, int isMeleeATK)> CPCBattle::_ProcessAutoSpell(SERVER, "CPCBattle::ProcessAutoSpell");
void CPCBattle::ProcessAutoSpell(CCharacter* other, int isMeleeATK)
{
	return (this->*_ProcessAutoSpell)(other, isMeleeATK);

	//TODO
}


hook_method<void (CPCBattle::*)(CCharacter* other, int isMLEATK, int isMAGATK)> CPCBattle::_ProcessAutoSpell_ATKED(SERVER, "CPCBattle::ProcessAutoSpell_ATKED");
void CPCBattle::ProcessAutoSpell_ATKED(CCharacter* other, int isMLEATK, int isMAGATK)
{
	return (this->*_ProcessAutoSpell_ATKED)(other, isMLEATK, isMAGATK);

	//TODO
}


hook_method<void (CPCBattle::*)(unsigned short SKID, CCharacter* ch, short skillLv, MSGpar::CVar in_par)> CPCBattle::_UseAutoSpell(SERVER, "CPCBattle::UseAutoSpell");
void CPCBattle::UseAutoSpell(unsigned short SKID, CCharacter* ch, short skillLv, MSGpar::CVar in_par)
{
	return (this->*_UseAutoSpell)(SKID, ch, skillLv, in_par);

	//TODO
}


hook_method<void (CPCBattle::*)(unsigned short SKID, short xPos, short yPos, short skillLv)> CPCBattle::_UseAutoSpellToGround(SERVER, "CPCBattle::UseAutoSpellToGround");
void CPCBattle::UseAutoSpellToGround(unsigned short SKID, short xPos, short yPos, short skillLv)
{
	return (this->*_UseAutoSpellToGround)(SKID, xPos, yPos, skillLv);

	//TODO
}


hook_method<void (CPCBattle::*)(mystd::map<unsigned short,MSG_TYPE1_TWODWORD>* autoSpellList, CCharacter* target, int isPercentKeep)> CPCBattle::_CheckAutoSpellList(SERVER, "CPCBattle::CheckAutoSpellList");
void CPCBattle::CheckAutoSpellList(mystd::map<unsigned short,MSG_TYPE1_TWODWORD>* autoSpellList, CCharacter* target, int isPercentKeep)
{
	return (this->*_CheckAutoSpellList)(autoSpellList, target, isPercentKeep);

	//TODO
}


hook_method<void (CPCBattle::*)(int SKID, short range, CCharacter* exceptCH, int par1, int par2)> CPCBattle::_ProcessRegionSkill(SERVER, "CPCBattle::ProcessRegionSkill");
void CPCBattle::ProcessRegionSkill(int SKID, short range, CCharacter* exceptCH, int par1, int par2)
{
	return (this->*_ProcessRegionSkill)(SKID, range, exceptCH, par1, par2);

	//TODO
}


hook_method<int (CPCBattle::*)(int SKID, short range)> CPCBattle::_PartySkill(SERVER, "CPCBattle::PartySkill");
int CPCBattle::PartySkill(int SKID, short range)
{
	return (this->*_PartySkill)(SKID, range);

	//TODO
}


hook_method<void (CPCBattle::*)(unsigned char type)> CPCBattle::_CheckAutoActItem(SERVER, "CPCBattle::CheckAutoActItem");
void CPCBattle::CheckAutoActItem(unsigned char type)
{
	return (this->*_CheckAutoActItem)(type);

	//TODO
}


hook_method<void (CPCBattle::*)(void)> CPCBattle::_ProcessAutoActItemScript(SERVER, "CPCBattle::ProcessAutoActItemScript");
void CPCBattle::ProcessAutoActItemScript(void)
{
	return (this->*_ProcessAutoActItemScript)();

	//TODO
}


hook_method<void (CPCBattle::*)(unsigned char type, unsigned long itemID, short percent, short time)> CPCBattle::_AddAutoActItem(SERVER, "CPCBattle::AddAutoActItem");
void CPCBattle::AddAutoActItem(unsigned char type, unsigned long itemID, short percent, short time)
{
	return (this->*_AddAutoActItem)(type, itemID, percent, time);

	//TODO
}


hook_method<void (CPCBattle::*)(unsigned char type, unsigned long itemID, short percent, short time)> CPCBattle::_SubAutoActItem(SERVER, "CPCBattle::SubAutoActItem");
void CPCBattle::SubAutoActItem(unsigned char type, unsigned long itemID, short percent, short time)
{
	return (this->*_SubAutoActItem)(type, itemID, percent, time);

	//TODO
}


hook_method<void (CPCBattle::*)(unsigned char type, unsigned long itemID, unsigned long time)> CPCBattle::_AddAutoActItemScript(SERVER, "CPCBattle::AddAutoActItemScript");
void CPCBattle::AddAutoActItemScript(unsigned char type, unsigned long itemID, unsigned long time)
{
	return (this->*_AddAutoActItemScript)(type, itemID, time);

	//TODO
}


hook_method<void (CPCBattle::*)(unsigned char type, unsigned long itemID)> CPCBattle::_SubAutoActItemScript(SERVER, "CPCBattle::SubAutoActItemScript");
void CPCBattle::SubAutoActItemScript(unsigned char type, unsigned long itemID)
{
	return (this->*_SubAutoActItemScript)(type, itemID);

	//TODO
}


hook_method<int (CPCBattle::*)(mystd::map<unsigned short,HEAL_REGULARLY_INFO>* infos)> CPCBattle::_GetTotalHealRegularlyAmount(SERVER, "CPCBattle::GetTotalHealRegularlyAmount");
int CPCBattle::GetTotalHealRegularlyAmount(mystd::map<unsigned short,HEAL_REGULARLY_INFO>* infos)
{
	return (this->*_GetTotalHealRegularlyAmount)(infos);

	//TODO
}


hook_method<void (CPCBattle::*)(CCharacter* other, unsigned short SKID)> CPCBattle::_ProcessTargetAttackedBuff(SERVER, "CPCBattle::ProcessTargetAttackedBuff");
void CPCBattle::ProcessTargetAttackedBuff(CCharacter* other, unsigned short SKID)
{
	return (this->*_ProcessTargetAttackedBuff)(other, SKID);

	//TODO
}


hook_method<void (CPCBattle::*)(unsigned long percent, short who, unsigned short buffType, unsigned long time, unsigned long value)> CPCBattle::_SetTargetAttackedBuff(SERVER, "CPCBattle::SetTargetAttackedBuff");
void CPCBattle::SetTargetAttackedBuff(unsigned long percent, short who, unsigned short buffType, unsigned long time, unsigned long value)
{
	return (this->*_SetTargetAttackedBuff)(percent, who, buffType, time, value);

	//TODO
}


hook_method<void (CPCBattle::*)(unsigned long percent, short who, unsigned short buffType, unsigned long time, unsigned long value)> CPCBattle::_ResetTargetAttackedBuff(SERVER, "CPCBattle::ResetTargetAttackedBuff");
void CPCBattle::ResetTargetAttackedBuff(unsigned long percent, short who, unsigned short buffType, unsigned long time, unsigned long value)
{
	return (this->*_ResetTargetAttackedBuff)(percent, who, buffType, time, value);

	//TODO
}


hook_method<void (CPCBattle::*)(void)> CPCBattle::_ProcessSkillActivate(SERVER, "CPCBattle::ProcessSkillActivate");
void CPCBattle::ProcessSkillActivate(void)
{
	return (this->*_ProcessSkillActivate)();

	//TODO
}


hook_method<void (CPCBattle::*)(unsigned long checkSKID, CCharacter* target, short xPos, short yPos)> CPCBattle::_CheckSkillAutoSpell(SERVER, "CPCBattle::CheckSkillAutoSpell");
void CPCBattle::CheckSkillAutoSpell(unsigned long checkSKID, CCharacter* target, short xPos, short yPos)
{
	return (this->*_CheckSkillAutoSpell)(checkSKID, target, xPos, yPos);

	//TODO
}


hook_method<void (CPCBattle::*)(unsigned long checkSKID)> CPCBattle::_CheckSkillActivate(SERVER, "CPCBattle::CheckSkillActivate");
void CPCBattle::CheckSkillActivate(unsigned long checkSKID)
{
	return (this->*_CheckSkillActivate)(checkSKID);

	//TODO
}


hook_method<void (CPCBattle::*)(unsigned long checkSKID, CCharacter* target)> CPCBattle::_CheckSkillHandicap(SERVER, "CPCBattle::CheckSkillHandicap");
void CPCBattle::CheckSkillHandicap(unsigned long checkSKID, CCharacter* target)
{
	return (this->*_CheckSkillHandicap)(checkSKID, target);

	//TODO
}


hook_method<void (CPCBattle::*)(CCharacter* target)> CPCBattle::_CheckAutoSpellMagic(SERVER, "CPCBattle::CheckAutoSpellMagic");
void CPCBattle::CheckAutoSpellMagic(CCharacter* target)
{
	return (this->*_CheckAutoSpellMagic)(target);

	//TODO
}


hook_method<void (CPCBattle::*)(unsigned long checkSKID, CCharacter* target)> CPCBattle::_CheckPushingSkill(SERVER, "CPCBattle::CheckPushingSkill");
void CPCBattle::CheckPushingSkill(unsigned long checkSKID, CCharacter* target)
{
	return (this->*_CheckPushingSkill)(checkSKID, target);

	//TODO
}


hook_method<int (CPCBattle::*)(MSG_TYPE4_FIVEDWORD* msg, SKILLATTACK_MSG* skMsg, CCharacter* ch)> CPCBattle::_SK_SM_Bash(SERVER, "CPCBattle::SK_SM_Bash");
int CPCBattle::SK_SM_Bash(MSG_TYPE4_FIVEDWORD* msg, SKILLATTACK_MSG* skMsg, CCharacter* ch)
{
	return (this->*_SK_SM_Bash)(msg, skMsg, ch);

	//TODO
}


hook_method<int (CPCBattle::*)(MSG_TYPE4_FIVEDWORD* msg, SKILLATTACK_MSG* skMsg, CCharacter* ch)> CPCBattle::_SK_TF_SprinkleSand(SERVER, "CPCBattle::SK_TF_SprinkleSand");
int CPCBattle::SK_TF_SprinkleSand(MSG_TYPE4_FIVEDWORD* msg, SKILLATTACK_MSG* skMsg, CCharacter* ch)
{
	return (this->*_SK_TF_SprinkleSand)(msg, skMsg, ch);

	//TODO
}


hook_method<int (CPCBattle::*)(MSG_TYPE4_FIVEDWORD* msg, SKILLATTACK_MSG* skMsg, CCharacter* ch)> CPCBattle::_SK_TF_ThrowStone(SERVER, "CPCBattle::SK_TF_ThrowStone");
int CPCBattle::SK_TF_ThrowStone(MSG_TYPE4_FIVEDWORD* msg, SKILLATTACK_MSG* skMsg, CCharacter* ch)
{
	return (this->*_SK_TF_ThrowStone)(msg, skMsg, ch);

	//TODO
}


hook_method<void (CPCBattle::*)(MSG_TYPE4_FIVEDWORD* msg, SKILLATTACK_MSG* skMsg, CCharacter* ch)> CPCBattle::_SK_KN_ChargeATK(SERVER, "CPCBattle::SK_KN_ChargeATK");
void CPCBattle::SK_KN_ChargeATK(MSG_TYPE4_FIVEDWORD* msg, SKILLATTACK_MSG* skMsg, CCharacter* ch)
{
	return (this->*_SK_KN_ChargeATK)(msg, skMsg, ch);

	//TODO
}


hook_method<void (CPCBattle::*)(MSG_TYPE4_FIVEDWORD* msg)> CPCBattle::_SK_WZ_SightBlaster(SERVER, "CPCBattle::SK_WZ_SightBlaster");
void CPCBattle::SK_WZ_SightBlaster(MSG_TYPE4_FIVEDWORD* msg)
{
	return (this->*_SK_WZ_SightBlaster)(msg);

	//TODO
}


hook_method<int (CPCBattle::*)(MSG_TYPE4_FIVEDWORD* msg, CCharacter* ch)> CPCBattle::_SK_BA_PangVoice(SERVER, "CPCBattle::SK_BA_PangVoice");
int CPCBattle::SK_BA_PangVoice(MSG_TYPE4_FIVEDWORD* msg, CCharacter* ch)
{
	return (this->*_SK_BA_PangVoice)(msg, ch);

	//TODO
}


hook_method<int (CPCBattle::*)(MSG_TYPE4_FIVEDWORD* msg, CCharacter* ch)> CPCBattle::_SK_DC_WinkCharm(SERVER, "CPCBattle::SK_DC_WinkCharm");
int CPCBattle::SK_DC_WinkCharm(MSG_TYPE4_FIVEDWORD* msg, CCharacter* ch)
{
	return (this->*_SK_DC_WinkCharm)(msg, ch);

	//TODO
}


hook_method<int (CPCBattle::*)(MSG_TYPE4_FIVEDWORD* msg)> CPCBattle::_SK_BS_Greed(SERVER, "CPCBattle::SK_BS_Greed");
int CPCBattle::SK_BS_Greed(MSG_TYPE4_FIVEDWORD* msg)
{
	return (this->*_SK_BS_Greed)(msg);

	//TODO
}


hook_method<int (CPCBattle::*)(MSG_TYPE4_FIVEDWORD* msg)> CPCBattle::_SK_PR_Redemtio(SERVER, "CPCBattle::SK_PR_Redemtio");
int CPCBattle::SK_PR_Redemtio(MSG_TYPE4_FIVEDWORD* msg)
{
	return (this->*_SK_PR_Redemtio)(msg);

	//TODO
}


hook_method<int (CPCBattle::*)(MSG_TYPE4_FIVEDWORD* msg, CCharacter* ch)> CPCBattle::_SK_MO_KITranslation(SERVER, "CPCBattle::SK_MO_KITranslation");
int CPCBattle::SK_MO_KITranslation(MSG_TYPE4_FIVEDWORD* msg, CCharacter* ch)
{
	return (this->*_SK_MO_KITranslation)(msg, ch);

	//TODO
}


hook_method<int (CPCBattle::*)(MSG_TYPE4_FIVEDWORD* msg, SKILLATTACK_MSG* skMsg, CCharacter* ch)> CPCBattle::_SK_MO_Balkyoung(SERVER, "CPCBattle::SK_MO_Balkyoung");
int CPCBattle::SK_MO_Balkyoung(MSG_TYPE4_FIVEDWORD* msg, SKILLATTACK_MSG* skMsg, CCharacter* ch)
{
	return (this->*_SK_MO_Balkyoung)(msg, skMsg, ch);

	//TODO
}


hook_method<int (CPCBattle::*)(MSG_TYPE4_FIVEDWORD* msg, CCharacter* ch)> CPCBattle::_SK_RG_CloseConfine(SERVER, "CPCBattle::SK_RG_CloseConfine");
int CPCBattle::SK_RG_CloseConfine(MSG_TYPE4_FIVEDWORD* msg, CCharacter* ch)
{
	return (this->*_SK_RG_CloseConfine)(msg, ch);

	//TODO
}


hook_method<void (CPCBattle::*)(MSG_TYPE4_FIVEDWORD* msg)> CPCBattle::_SK_SA_CreateConverter(SERVER, "CPCBattle::SK_SA_CreateConverter");
void CPCBattle::SK_SA_CreateConverter(MSG_TYPE4_FIVEDWORD* msg)
{
	return (this->*_SK_SA_CreateConverter)(msg);

	//TODO
}


hook_method<int (CPCBattle::*)(MSG_TYPE4_FIVEDWORD* msg, CCharacter* ch)> CPCBattle::_SK_SA_ElementalCHG(SERVER, "CPCBattle::SK_SA_ElementalCHG");
int CPCBattle::SK_SA_ElementalCHG(MSG_TYPE4_FIVEDWORD* msg, CCharacter* ch)
{
	return (this->*_SK_SA_ElementalCHG)(msg, ch);

	//TODO
}


hook_method<int (CPCBattle::*)(MSG_TYPE4_FIVEDWORD* msg)> CPCBattle::_SK_GS_Glittering(SERVER, "CPCBattle::SK_GS_Glittering");
int CPCBattle::SK_GS_Glittering(MSG_TYPE4_FIVEDWORD* msg)
{
	return (this->*_SK_GS_Glittering)(msg);

	//TODO
}


hook_method<int (CPCBattle::*)(MSG_TYPE4_FIVEDWORD* msg, CCharacter* ch)> CPCBattle::_SK_GS_Fling(SERVER, "CPCBattle::SK_GS_Fling");
int CPCBattle::SK_GS_Fling(MSG_TYPE4_FIVEDWORD* msg, CCharacter* ch)
{
	return (this->*_SK_GS_Fling)(msg, ch);

	//TODO
}


hook_method<int (CPCBattle::*)(MSG_TYPE4_FIVEDWORD* msg, SKILLATTACK_MSG* skMsg, CCharacter* ch)> CPCBattle::_SK_GS_BullsEye(SERVER, "CPCBattle::SK_GS_BullsEye");
int CPCBattle::SK_GS_BullsEye(MSG_TYPE4_FIVEDWORD* msg, SKILLATTACK_MSG* skMsg, CCharacter* ch)
{
	return (this->*_SK_GS_BullsEye)(msg, skMsg, ch);

	//TODO
}


hook_method<int (CPCBattle::*)(MSG_TYPE4_FIVEDWORD* msg)> CPCBattle::_SK_GS_MadnessCancel(SERVER, "CPCBattle::SK_GS_MadnessCancel");
int CPCBattle::SK_GS_MadnessCancel(MSG_TYPE4_FIVEDWORD* msg)
{
	return (this->*_SK_GS_MadnessCancel)(msg);

	//TODO
}


hook_method<int (CPCBattle::*)(MSG_TYPE4_FIVEDWORD* msg)> CPCBattle::_SK_GS_Adjustment(SERVER, "CPCBattle::SK_GS_Adjustment");
int CPCBattle::SK_GS_Adjustment(MSG_TYPE4_FIVEDWORD* msg)
{
	return (this->*_SK_GS_Adjustment)(msg);

	//TODO
}


hook_method<int (CPCBattle::*)(MSG_TYPE4_FIVEDWORD* msg)> CPCBattle::_SK_GS_Increasing(SERVER, "CPCBattle::SK_GS_Increasing");
int CPCBattle::SK_GS_Increasing(MSG_TYPE4_FIVEDWORD* msg)
{
	return (this->*_SK_GS_Increasing)(msg);

	//TODO
}


hook_method<int (CPCBattle::*)(MSG_TYPE4_FIVEDWORD* msg, SKILLATTACK_MSG* skMsg, CCharacter* ch)> CPCBattle::_SK_GS_MagicalBullet(SERVER, "CPCBattle::SK_GS_MagicalBullet");
int CPCBattle::SK_GS_MagicalBullet(MSG_TYPE4_FIVEDWORD* msg, SKILLATTACK_MSG* skMsg, CCharacter* ch)
{
	return (this->*_SK_GS_MagicalBullet)(msg, skMsg, ch);

	//TODO
}


hook_method<int (CPCBattle::*)(MSG_TYPE4_FIVEDWORD* msg, CCharacter* ch)> CPCBattle::_SK_GS_Cracker(SERVER, "CPCBattle::SK_GS_Cracker");
int CPCBattle::SK_GS_Cracker(MSG_TYPE4_FIVEDWORD* msg, CCharacter* ch)
{
	return (this->*_SK_GS_Cracker)(msg, ch);

	//TODO
}


hook_method<int (CPCBattle::*)(MSG_TYPE4_FIVEDWORD* msg, SKILLATTACK_MSG* skMsg)> CPCBattle::_SK_GS_FullBuster(SERVER, "CPCBattle::SK_GS_FullBuster");
int CPCBattle::SK_GS_FullBuster(MSG_TYPE4_FIVEDWORD* msg, SKILLATTACK_MSG* skMsg)
{
	return (this->*_SK_GS_FullBuster)(msg, skMsg);

	//TODO
}


hook_method<void (CPCBattle::*)(MSG_TYPE4_FIVEDWORD* msg)> CPCBattle::_SK_GS_SingleAction(SERVER, "CPCBattle::SK_GS_SingleAction");
void CPCBattle::SK_GS_SingleAction(MSG_TYPE4_FIVEDWORD* msg)
{
	return (this->*_SK_GS_SingleAction)(msg);

	//TODO
}


hook_method<void (CPCBattle::*)(MSG_TYPE4_FIVEDWORD* msg)> CPCBattle::_SK_GS_SnakeEye(SERVER, "CPCBattle::SK_GS_SnakeEye");
void CPCBattle::SK_GS_SnakeEye(MSG_TYPE4_FIVEDWORD* msg)
{
	return (this->*_SK_GS_SnakeEye)(msg);

	//TODO
}


hook_method<void (CPCBattle::*)(MSG_TYPE4_FIVEDWORD* msg)> CPCBattle::_SK_NJ_TobidoUgu(SERVER, "CPCBattle::SK_NJ_TobidoUgu");
void CPCBattle::SK_NJ_TobidoUgu(MSG_TYPE4_FIVEDWORD* msg)
{
	return (this->*_SK_NJ_TobidoUgu)(msg);

	//TODO
}


hook_method<void (CPCBattle::*)(MSG_TYPE4_FIVEDWORD* msg)> CPCBattle::_SK_NJ_NinPou(SERVER, "CPCBattle::SK_NJ_NinPou");
void CPCBattle::SK_NJ_NinPou(MSG_TYPE4_FIVEDWORD* msg)
{
	return (this->*_SK_NJ_NinPou)(msg);

	//TODO
}


hook_method<int (CPCBattle::*)(MSG_TYPE4_FIVEDWORD* msg, CCharacter* ch)> CPCBattle::_SK_GS_Disarm(SERVER, "CPCBattle::SK_GS_Disarm");
int CPCBattle::SK_GS_Disarm(MSG_TYPE4_FIVEDWORD* msg, CCharacter* ch)
{
	return (this->*_SK_GS_Disarm)(msg, ch);

	//TODO
}


hook_method<int (CPCBattle::*)(MSG_TYPE4_FIVEDWORD* msg, SKILLATTACK_MSG* skMsg, CCharacter* ch)> CPCBattle::_SK_GS_PiercingShot(SERVER, "CPCBattle::SK_GS_PiercingShot");
int CPCBattle::SK_GS_PiercingShot(MSG_TYPE4_FIVEDWORD* msg, SKILLATTACK_MSG* skMsg, CCharacter* ch)
{
	return (this->*_SK_GS_PiercingShot)(msg, skMsg, ch);

	//TODO
}


hook_method<int (CPCBattle::*)(MSG_TYPE4_FIVEDWORD* msg)> CPCBattle::_SK_GS_Desperado(SERVER, "CPCBattle::SK_GS_Desperado");
int CPCBattle::SK_GS_Desperado(MSG_TYPE4_FIVEDWORD* msg)
{
	return (this->*_SK_GS_Desperado)(msg);

	//TODO
}


hook_method<void (CPCBattle::*)(MSG_TYPE4_FIVEDWORD* msg)> CPCBattle::_SK_GS_GatlingFever(SERVER, "CPCBattle::SK_GS_GatlingFever");
void CPCBattle::SK_GS_GatlingFever(MSG_TYPE4_FIVEDWORD* msg)
{
	return (this->*_SK_GS_GatlingFever)(msg);

	//TODO
}


hook_method<int (CPCBattle::*)(MSG_TYPE4_FIVEDWORD* msg, SKILLATTACK_MSG* skMsg, CCharacter* ch)> CPCBattle::_SK_NJ_Syuriken(SERVER, "CPCBattle::SK_NJ_Syuriken");
int CPCBattle::SK_NJ_Syuriken(MSG_TYPE4_FIVEDWORD* msg, SKILLATTACK_MSG* skMsg, CCharacter* ch)
{
	return (this->*_SK_NJ_Syuriken)(msg, skMsg, ch);

	//TODO
}


hook_method<int (CPCBattle::*)(MSG_TYPE4_FIVEDWORD* msg, SKILLATTACK_MSG* skMsg, CCharacter* ch)> CPCBattle::_SK_NJ_Kunai(SERVER, "CPCBattle::SK_NJ_Kunai");
int CPCBattle::SK_NJ_Kunai(MSG_TYPE4_FIVEDWORD* msg, SKILLATTACK_MSG* skMsg, CCharacter* ch)
{
	return (this->*_SK_NJ_Kunai)(msg, skMsg, ch);

	//TODO
}


hook_method<int (CPCBattle::*)(MSG_TYPE4_FIVEDWORD* msg, SKILLATTACK_MSG* skMsg, CCharacter* ch)> CPCBattle::_SK_NJ_ZenyNage(SERVER, "CPCBattle::SK_NJ_ZenyNage");
int CPCBattle::SK_NJ_ZenyNage(MSG_TYPE4_FIVEDWORD* msg, SKILLATTACK_MSG* skMsg, CCharacter* ch)
{
	return (this->*_SK_NJ_ZenyNage)(msg, skMsg, ch);

	//TODO
}


hook_method<void (CPCBattle::*)(MSG_TYPE4_FIVEDWORD* msg)> CPCBattle::_SK_NJ_TatamiGaeshi(SERVER, "CPCBattle::SK_NJ_TatamiGaeshi");
void CPCBattle::SK_NJ_TatamiGaeshi(MSG_TYPE4_FIVEDWORD* msg)
{
	return (this->*_SK_NJ_TatamiGaeshi)(msg);

	//TODO
}


hook_method<int (CPCBattle::*)(MSG_TYPE4_FIVEDWORD* msg, SKILLATTACK_MSG* skMsg, CCharacter* ch)> CPCBattle::_SK_NJ_KasumiKiri(SERVER, "CPCBattle::SK_NJ_KasumiKiri");
int CPCBattle::SK_NJ_KasumiKiri(MSG_TYPE4_FIVEDWORD* msg, SKILLATTACK_MSG* skMsg, CCharacter* ch)
{
	return (this->*_SK_NJ_KasumiKiri)(msg, skMsg, ch);

	//TODO
}


hook_method<void (CPCBattle::*)(MSG_TYPE5_SIXDWORD* msg)> CPCBattle::_SK_NJ_ShadowJump(SERVER, "CPCBattle::SK_NJ_ShadowJump");
void CPCBattle::SK_NJ_ShadowJump(MSG_TYPE5_SIXDWORD* msg)
{
	return (this->*_SK_NJ_ShadowJump)(msg);

	//TODO
}


hook_method<int (CPCBattle::*)(MSG_TYPE4_FIVEDWORD* msg, SKILLATTACK_MSG* skMsg, CCharacter* ch)> CPCBattle::_SK_NJ_KiriKage(SERVER, "CPCBattle::SK_NJ_KiriKage");
int CPCBattle::SK_NJ_KiriKage(MSG_TYPE4_FIVEDWORD* msg, SKILLATTACK_MSG* skMsg, CCharacter* ch)
{
	return (this->*_SK_NJ_KiriKage)(msg, skMsg, ch);

	//TODO
}


hook_method<int (CPCBattle::*)(MSG_TYPE4_FIVEDWORD* msg)> CPCBattle::_SK_NJ_Utsusemi(SERVER, "CPCBattle::SK_NJ_Utsusemi");
int CPCBattle::SK_NJ_Utsusemi(MSG_TYPE4_FIVEDWORD* msg)
{
	return (this->*_SK_NJ_Utsusemi)(msg);

	//TODO
}


hook_method<int (CPCBattle::*)(MSG_TYPE4_FIVEDWORD* msg)> CPCBattle::_SK_NJ_BunsinJyutsu(SERVER, "CPCBattle::SK_NJ_BunsinJyutsu");
int CPCBattle::SK_NJ_BunsinJyutsu(MSG_TYPE4_FIVEDWORD* msg)
{
	return (this->*_SK_NJ_BunsinJyutsu)(msg);

	//TODO
}


hook_method<int (CPCBattle::*)(MSG_TYPE4_FIVEDWORD* msg)> CPCBattle::_SK_NJ_KaenSin(SERVER, "CPCBattle::SK_NJ_KaenSin");
int CPCBattle::SK_NJ_KaenSin(MSG_TYPE4_FIVEDWORD* msg)
{
	return (this->*_SK_NJ_KaenSin)(msg);

	//TODO
}


hook_method<int (CPCBattle::*)(MSG_TYPE4_FIVEDWORD* msg, CCharacter* ch)> CPCBattle::_SK_NJ_BakuenRyu(SERVER, "CPCBattle::SK_NJ_BakuenRyu");
int CPCBattle::SK_NJ_BakuenRyu(MSG_TYPE4_FIVEDWORD* msg, CCharacter* ch)
{
	return (this->*_SK_NJ_BakuenRyu)(msg, ch);

	//TODO
}


hook_method<int (CPCBattle::*)(MSG_TYPE4_FIVEDWORD* msg, SKILLATTACK_MSG* skMsg)> CPCBattle::_SK_NJ_HyousenSou(SERVER, "CPCBattle::SK_NJ_HyousenSou");
int CPCBattle::SK_NJ_HyousenSou(MSG_TYPE4_FIVEDWORD* msg, SKILLATTACK_MSG* skMsg)
{
	return (this->*_SK_NJ_HyousenSou)(msg, skMsg);

	//TODO
}


hook_method<void (CPCBattle::*)(MSG_TYPE5_SIXDWORD* msg)> CPCBattle::_SK_NJ_SuiTon(SERVER, "CPCBattle::SK_NJ_SuiTon");
void CPCBattle::SK_NJ_SuiTon(MSG_TYPE5_SIXDWORD* msg)
{
	return (this->*_SK_NJ_SuiTon)(msg);

	//TODO
}


hook_method<int (CPCBattle::*)(MSG_TYPE4_FIVEDWORD* msg)> CPCBattle::_SK_NJ_HyouSyouRaku(SERVER, "CPCBattle::SK_NJ_HyouSyouRaku");
int CPCBattle::SK_NJ_HyouSyouRaku(MSG_TYPE4_FIVEDWORD* msg)
{
	return (this->*_SK_NJ_HyouSyouRaku)(msg);

	//TODO
}


hook_method<int (CPCBattle::*)(MSG_TYPE4_FIVEDWORD* msg)> CPCBattle::_SK_NJ_Raigekisai(SERVER, "CPCBattle::SK_NJ_Raigekisai");
int CPCBattle::SK_NJ_Raigekisai(MSG_TYPE4_FIVEDWORD* msg)
{
	return (this->*_SK_NJ_Raigekisai)(msg);

	//TODO
}


hook_method<int (CPCBattle::*)(MSG_TYPE4_FIVEDWORD* msg)> CPCBattle::_SK_NJ_Nen(SERVER, "CPCBattle::SK_NJ_Nen");
int CPCBattle::SK_NJ_Nen(MSG_TYPE4_FIVEDWORD* msg)
{
	return (this->*_SK_NJ_Nen)(msg);

	//TODO
}


hook_method<int (CPCBattle::*)(MSG_TYPE4_FIVEDWORD* msg, SKILLATTACK_MSG* skMsg, CCharacter* ch)> CPCBattle::_SK_NJ_Issen(SERVER, "CPCBattle::SK_NJ_Issen");
int CPCBattle::SK_NJ_Issen(MSG_TYPE4_FIVEDWORD* msg, SKILLATTACK_MSG* skMsg, CCharacter* ch)
{
	return (this->*_SK_NJ_Issen)(msg, skMsg, ch);

	//TODO
}


hook_method<int (CPCBattle::*)(MSG_TYPE4_FIVEDWORD* msg)> CPCBattle::_SK_ALL_PARTYFLEE(SERVER, "CPCBattle::SK_ALL_PARTYFLEE");
int CPCBattle::SK_ALL_PARTYFLEE(MSG_TYPE4_FIVEDWORD* msg)
{
	return (this->*_SK_ALL_PARTYFLEE)(msg);

	//TODO
}


hook_method<int (CPCBattle::*)(MSG_TYPE4_FIVEDWORD* msg, CCharacter* ch)> CPCBattle::_SK_ALL_ANGEL_PROTECT(SERVER, "CPCBattle::SK_ALL_ANGEL_PROTECT");
int CPCBattle::SK_ALL_ANGEL_PROTECT(MSG_TYPE4_FIVEDWORD* msg, CCharacter* ch)
{
	return (this->*_SK_ALL_ANGEL_PROTECT)(msg, ch);

	//TODO
}


hook_method<int (CPCBattle::*)(const MSG_TYPE4_FIVEDWORD& msg, CCharacter* ch)> CPCBattle::_ALL_SONKRAN(SERVER, "CPCBattle::ALL_SONKRAN");
int CPCBattle::ALL_SONKRAN(const MSG_TYPE4_FIVEDWORD& msg, CCharacter* ch)
{
	return (this->*_ALL_SONKRAN)(msg, ch);

	//TODO
}
