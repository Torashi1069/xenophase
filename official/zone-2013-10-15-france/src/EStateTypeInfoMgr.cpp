#include "Enum.h"
#include "EStateTypeInfoMgr.h"
#include "ScriptCompiler.h"
#include "ItemServer/CEfstScriptEventHandler.h"
#include "shared/NCriticalErrorLog.h"
#include "shared/NLuaState.h"


/// singleton instance
EStateTypeInfoMgr*& EStateTypeInfoMgr::m_cpSelf = VTOR<EStateTypeInfoMgr*>(DetourFindFunction(EXEPATH(), "EStateTypeInfoMgr::m_cpSelf"));


ESTATE_SCRIPT_SCANNER::ESTATE_SCRIPT_SCANNER()
: m_isError(false), m_EStateScript(NULL)
{
	m_interpreter.CInterpreter::RegisterHandler(this);
}


bool ESTATE_SCRIPT_SCANNER::Scan(CBinBuf* binBuf)
{
	m_interpreter.CInterpreter::Scan(binBuf, 0);

	while( m_interpreter.CInterpreter::Proc() )
		;

	if( m_isError == true )
		return false;

	return true;
}


bool ESTATE_SCRIPT_SCANNER::OnFunc(int func, std::deque<TokenData>& parm, TokenData& ret)
{
	switch( func )
	{
	case FUNC_EVENT:
	{
		if( parm.size() != 1 || m_EStateScript == NULL )
			return false;

		int EventType = parm[0].TokenData::GetNum();
		int scriptPos = m_interpreter.CInterpreter::GetCurPos();
		m_EStateScript->ESTATE_SCRIPT::AddScript(EventType, scriptPos);
		return true;
	}
	break;
	case FUNC_BUFF:
	{
		if( parm.size() != 1 )
			return false;

		const char* EStateName = parm[0].TokenData::GetStr();
		return this->ESTATE_SCRIPT_SCANNER::FuncBuff(EStateName);
	}
	break;
	default:
	{
		return true;
	}
	break;
	};
}


void ESTATE_SCRIPT_SCANNER::OnError(const char* str)
{
}


bool ESTATE_SCRIPT_SCANNER::FuncBuff(const char* EStateName)
{
	ESTATE* pEState = EStateTypeInfoMgr::GetObj()->EStateTypeInfoMgr::GetPtr(EStateName);

	if( pEState == NULL || pEState->IsExistScript() != true )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "Buffspecial.sc  ... or...???  Not Matching buff %s", EStateName);
		MessageBoxA(NULL, (std::string() + "Buffspecial.sc  ... or...???  Not Matching buff" + EStateName).c_str(), "Check!!!", MB_OK);
		exit(EXIT_SUCCESS);
	}

	m_EStateScript = static_cast<ESTATE_SCRIPT*>(pEState);
	return true;
}


////////////////////////////////////////


EStateTypeInfoMgr::EStateTypeInfoMgr()
{
	m_bOK = false;

	if( this->EStateTypeInfoMgr::Create()
	 && this->EStateTypeInfoMgr::LoadConfigFile() )
		m_bOK = true;
}


EStateTypeInfoMgr::~EStateTypeInfoMgr()
{
	this->EStateTypeInfoMgr::Destroy();
}


void EStateTypeInfoMgr::Destroy()
{
	for( ESTATETYPEINFO_CONTAINER::iterator iter = m_ESateTypeInfoList.begin(); iter != m_ESateTypeInfoList.end(); ++iter )
		delete iter->second;

	m_ESateTypeInfoList.clear();
	m_EStateTypeInfoNameList.clear();
}


bool EStateTypeInfoMgr::LoadConfigFile()
{
	NLuaState L;
	if( !L.NLuaState::isOK() )
	{
		MessageBoxA(NULL, "state new fail", "EStateTypeInfoMgr", MB_OK);
		return false;
	}

	if( luaL_loadfile(L, "EFSTconfig.lua") != 0 )
	{
		MessageBoxA(NULL, lua_tolstring(L, -1, NULL), "EStateTypeInfoMgr", MB_OK);
		return false;
	}

	if( lua_pcall(L, 0, 0, 0) != 0 )
	{
		MessageBoxA(NULL, lua_tolstring(L, -1, NULL), "EStateTypeInfoMgr", MB_OK);
		return false;
	}

	static const char* BooleanVarNameTbl[] = {
		"ResetDead",
		"ResetDispel",
		"Save",
		"Send",
		"IgnorePretendDead",
		"DeBuff",
		"ResetCLEARANCE",
		"ActorAppearance",
		"SendMultiCast",
		"backward compatibility send",
		"ResetMADOGEAR",
	};

	for( ESTATETYPEINFO_CONTAINER::iterator iter = m_ESateTypeInfoList.begin(); iter == m_ESateTypeInfoList.end(); ++iter )
	{
		ESTATE* pEState = iter->second;

		lua_getfield(L, LUA_GLOBALSINDEX, pEState->ESTATE::GetName().c_str());
		if( lua_type(L, -1) == LUA_TTABLE )
		{
			for( int idx = 0; idx < 11; ++idx )
			{
				lua_pushstring(L, BooleanVarNameTbl[idx]);
				lua_gettable(L, -2);
				if( lua_type(L, -1) == LUA_TBOOLEAN )
				{
					bool bVal = ( lua_toboolean(L, -1) != FALSE );
					switch( idx )
					{
					case 0:
						lua_settop(L, -2);
						lua_pushstring(L, "ResetMADOGEAR");
						lua_gettable(L, -2);
						if( lua_type(L, -1) == LUA_TNIL )
							pEState->ESTATE::SetResetMADOGEAR(bVal);
						pEState->ESTATE::SetResetDead(bVal);
					break;
					case 1:
						pEState->ESTATE::SetResetDispel(bVal);
					break;
					case 2:
						pEState->ESTATE::SetSave(bVal);
					break;
					case 3:
						pEState->ESTATE::SetSend(bVal);
					break;
					case 4:
						pEState->ESTATE::SetIgnorePretendDead(bVal);
					break;
					case 5:
						pEState->ESTATE::SetDeBuff(bVal);
					break;
					case 6:
						pEState->ESTATE::SetResetCLEARANCE(bVal);
					break;
					case 7:
						pEState->ESTATE::SetActorAppearance(bVal);
					break;
					case 8:
						pEState->ESTATE::SetSendMultiCast(bVal);
					break;
					case 9:
						pEState->ESTATE::SetBackwardCompatibilitySend(bVal);
					break;
					case 10:
						pEState->ESTATE::SetResetMADOGEAR(bVal);
					break;
					};
				}
				else
				if( lua_type(L, -1) != LUA_TNIL )
				{
					std::string msg = std::string() + pEState->ESTATE::GetName() + "'s " + BooleanVarNameTbl[idx];
					MessageBoxA(NULL, msg.c_str(), "EStateTypeInfoMgr-LoadConfigFile", MB_OK);
					return false;
				}

				lua_settop(L, -2);
			}
		}

		lua_settop(L, -2);
	}

	return true;
}


hook_func<void (__stdcall *)()> EStateTypeInfoMgr__Create(EXEPATH(), "EStateTypeInfoMgr::Create");
bool EStateTypeInfoMgr::Create() // 177-941-1233
{
	bool result;
	void* hookptr = EStateTypeInfoMgr__Create;
	__asm push this
	__asm call hookptr
	__asm mov result, al
	return result; //TODO
/*
	#define ADD_ESTATE(_EFST_, _ESTATE_) {                    \
		ESTATE* p = new(std::nothrow) _ESTATE_();             \
		if( p == NULL )                                       \
			return false;                                     \
												              \
		m_ESateTypeInfoList[_EFST_] = p;                      \
		m_EStateTypeInfoNameList[_CRT_STRINGIZE(_EFST_)] = p; \
	}
	
	ADD_ESTATE(EFST_PROVOKE, ESTATE_PROVOKE);
	ADD_ESTATE(EFST_ENDURE, ESTATE_ENDURE);
	ADD_ESTATE(EFST_TWOHANDQUICKEN, ESTATE_TWOHANDQUICKEN);
	ADD_ESTATE(EFST_CONCENTRATION, ESTATE_CONCENTRATION);
	ADD_ESTATE(EFST_ENCHANTPOISON, ESTATE_ENCHANTPOISON);
	ADD_ESTATE(EFST_POISONREACT, ESTATE_POISONREACT);
	ADD_ESTATE(EFST_QUAGMIRE, ESTATE_QUAGMIRE);
	ADD_ESTATE(EFST_ANGELUS, ESTATE_ANGELUS);
	ADD_ESTATE(EFST_BLESSING, ESTATE_BLESSING);
	ADD_ESTATE(EFST_INC_AGI, ESTATE_INC_AGI);
	ADD_ESTATE(EFST_DEC_AGI, ESTATE_DEC_AGI);
	ADD_ESTATE(EFST_SLOWPOISON, ESTATE_SLOWPOISON);
	ADD_ESTATE(EFST_IMPOSITIO, ESTATE_IMPOSITIO);
	ADD_ESTATE(EFST_SUFFRAGIUM, ESTATE_SUFFRAGIUM);
	ADD_ESTATE(EFST_ASPERSIO, ESTATE_ASPERSIO);
	ADD_ESTATE(EFST_BENEDICTIO, ESTATE_BENEDICTIO);
	ADD_ESTATE(EFST_KYRIE, ESTATE_KYRIE);
	ADD_ESTATE(EFST_MAGNIFICAT, ESTATE_MAGNIFICAT);
	ADD_ESTATE(EFST_GLORIA, ESTATE_GLORIA);
	ADD_ESTATE(EFST_LEXAETERNA, ESTATE_LEXAETERNA);
	ADD_ESTATE(EFST_ADRENALINE, ESTATE_ADRENALINE);
	ADD_ESTATE(EFST_WEAPONPERFECT, ESTATE_WEAPONPERFECT);
	ADD_ESTATE(EFST_OVERTHRUST, ESTATE_OVERTHRUST);
	ADD_ESTATE(EFST_MAXIMIZE, ESTATE_MAXIMIZE);
	ADD_ESTATE(EFST_TRICKDEAD, ESTATE_TRICKDEAD);
	ADD_ESTATE(EFST_SHOUT, ESTATE_SHOUT);
	ADD_ESTATE(EFST_ENERGYCOAT, ESTATE_ENERGYCOAT);
	ADD_ESTATE(EFST_ATTHASTE_POTION1, ESTATE_ATTHASTE_POTION1);
	ADD_ESTATE(EFST_ATTHASTE_POTION2, ESTATE_ATTHASTE_POTION2);
	ADD_ESTATE(EFST_ATTHASTE_POTION3, ESTATE_ATTHASTE_POTION3);
	ADD_ESTATE(EFST_MOVHASTE_POTION, ESTATE_MOVHASTE_POTION);
	ADD_ESTATE(EFST_POSTDELAY, ESTATE_POSTDELAY);
	ADD_ESTATE(EFST_BARRIER, ESTATE_BARRIER);
	ADD_ESTATE(EFST_NOEQUIPWEAPON, ESTATE_NOEQUIPWEAPON);
	ADD_ESTATE(EFST_NOEQUIPSHIELD, ESTATE_NOEQUIPSHIELD);
	ADD_ESTATE(EFST_NOEQUIPARMOR, ESTATE_NOEQUIPARMOR);
	ADD_ESTATE(EFST_NOEQUIPHELM, ESTATE_NOEQUIPHELM);
	ADD_ESTATE(EFST_PROTECTWEAPON, ESTATE_PROTECTWEAPON);
	ADD_ESTATE(EFST_PROTECTSHIELD, ESTATE_PROTECTSHIELD);
	ADD_ESTATE(EFST_PROTECTARMOR, ESTATE_PROTECTARMOR);
	ADD_ESTATE(EFST_PROTECTHELM, ESTATE_PROTECTHELM);
	ADD_ESTATE(EFST_AUTOGUARD, ESTATE_AUTOGUARD);
	ADD_ESTATE(EFST_REFLECTSHIELD, ESTATE_REFLECTSHIELD);
	ADD_ESTATE(EFST_DEVOTION, ESTATE_DEVOTION);
	ADD_ESTATE(EFST_PROVIDENCE, ESTATE_PROVIDENCE);
	ADD_ESTATE(EFST_DEFENDER, ESTATE_DEFENDER);
	ADD_ESTATE(EFST_MAGICROD, ESTATE_MAGICROD);
	ADD_ESTATE(EFST_WEAPONPROPERTY, ESTATE_WEAPONPROPERTY);
	ADD_ESTATE(EFST_AUTOSPELL, ESTATE_AUTOSPELL);
	ADD_ESTATE(EFST_SPECIALZONE, ESTATE_SPECIALZONE);
	ADD_ESTATE(EFST_MASK, ESTATE_MASK);
	ADD_ESTATE(EFST_SPEARQUICKEN, ESTATE_SPEARQUICKEN);
	ADD_ESTATE(EFST_BLADESTOP, ESTATE_BLADESTOP);
	ADD_ESTATE(EFST_EXPLOSIONSPIRITS, ESTATE_EXPLOSIONSPIRITS);
	ADD_ESTATE(EFST_STEELBODY, ESTATE_STEELBODY);
	ADD_ESTATE(EFST_PROPERTYFIRE, ESTATE_PROPERTYFIRE);
	ADD_ESTATE(EFST_PROPERTYWATER, ESTATE_PROPERTYWATER);
	ADD_ESTATE(EFST_PROPERTYWIND, ESTATE_PROPERTYWIND);
	ADD_ESTATE(EFST_PROPERTYGROUND, ESTATE_PROPERTYGROUND);
	ADD_ESTATE(EFST_STOP, ESTATE_STOP);
	ADD_ESTATE(EFST_PROPERTYUNDEAD, ESTATE_PROPERTYUNDEAD);
	ADD_ESTATE(EFST_STATUSONE, ESTATE_STATUSONE);
	ADD_ESTATE(EFST_AURABLADE, ESTATE_AURABLADE);
	ADD_ESTATE(EFST_PARRYING, ESTATE_PARRYING);
	ADD_ESTATE(EFST_LKCONCENTRATION, ESTATE_LKCONCENTRATION);
	ADD_ESTATE(EFST_TENSIONRELAX, ESTATE_TENSIONRELAX);
	ADD_ESTATE(EFST_BERSERK, ESTATE_BERSERK);
	ADD_ESTATE(EFST_SACRIFICE, ESTATE_SACRIFICE);
	ADD_ESTATE(EFST_GOSPEL, ESTATE_GOSPEL);
	ADD_ESTATE(EFST_ASSUMPTIO, ESTATE_ASSUMPTIO);
	ADD_ESTATE(EFST_BASILICA, ESTATE_BASILICA);
	ADD_ESTATE(EFST_GROUNDMAGIC, ESTATE_GROUNDMAGIC);
	ADD_ESTATE(EFST_MAGICPOWER, ESTATE_MAGICPOWER);
	ADD_ESTATE(EFST_EDP, ESTATE_EDP);
	ADD_ESTATE(EFST_TRUESIGHT, ESTATE_TRUESIGHT);
	ADD_ESTATE(EFST_WINDWALK, ESTATE_WINDWALK);
	ADD_ESTATE(EFST_MELTDOWN, ESTATE_MELTDOWN);
	ADD_ESTATE(EFST_CARTBOOST, ESTATE_CARTBOOST);
	ADD_ESTATE(EFST_BLOODING, ESTATE_BLOODING);
	ADD_ESTATE(EFST_JOINTBEAT, ESTATE_JOINTBEAT);
	ADD_ESTATE(EFST_MINDBREAKER, ESTATE_MINDBREAKER);
	ADD_ESTATE(EFST_MEMORIZE, ESTATE_MEMORIZE);
	ADD_ESTATE(EFST_FOGWALL, ESTATE_FOGWALL);
	ADD_ESTATE(EFST_SPIDERWEB, ESTATE_SPIDERWEB);
	ADD_ESTATE(EFST_SUB_WEAPONPROPERTY, ESTATE_SUB_WEAPONPROPERTY);
	ADD_ESTATE(EFST_RUN, ESTATE_RUN);
	ADD_ESTATE(EFST_STRUP, ESTATE_STRUP);
	ADD_ESTATE(EFST_PROPERTYDARK, ESTATE_PROPERTYDARK);
	ADD_ESTATE(EFST_ADRENALINE2, ESTATE_ADRENALINE2);
	ADD_ESTATE(EFST_PROPERTYTELEKINESIS, ESTATE_PROPERTYTELEKINESIS);
	ADD_ESTATE(EFST_SOULLINK, ESTATE_SOULLINK);
	ADD_ESTATE(EFST_PLUSATTACKPOWER, ESTATE_PLUSATTACKPOWER);
	ADD_ESTATE(EFST_PLUSMAGICPOWER, ESTATE_PLUSMAGICPOWER);
	ADD_ESTATE(EFST_KAITE, ESTATE_KAITE);
	ADD_ESTATE(EFST_KAAHI, ESTATE_KAAHI);
	ADD_ESTATE(EFST_KAUPE, ESTATE_KAUPE);
	ADD_ESTATE(EFST_ONEHANDQUICKEN, ESTATE_ONEHANDQUICKEN);
	ADD_ESTATE(EFST_GDSKILL_POSTDELAY, ESTATE_GDSKILL_POSTDELAY);
	ADD_ESTATE(EFST_PRESERVE, ESTATE_PRESERVE);
	ADD_ESTATE(EFST_CHASEWALK2, ESTATE_CHASEWALK2);
	ADD_ESTATE(EFST_MOVESLOW_POTION, ESTATE_MOVESLOW_POTION);
	ADD_ESTATE(EFST_DOUBLECASTING, ESTATE_DOUBLECASTING);
	ADD_ESTATE(EFST_GRAVITATION, ESTATE_GRAVITATION);
	ADD_ESTATE(EFST_OVERTHRUSTMAX, ESTATE_OVERTHRUSTMAX);
	ADD_ESTATE(EFST_TAROTCARD, ESTATE_TAROTCARD);
	ADD_ESTATE(EFST_CR_SHRINK, ESTATE_CR_SHRINK);
	ADD_ESTATE(EFST_WZ_SIGHTBLASTER, ESTATE_WZ_SIGHTBLASTER);
	ADD_ESTATE(EFST_RG_CCONFINE_M, ESTATE_RG_CCONFINE_M);
	ADD_ESTATE(EFST_RG_CCONFINE_S, ESTATE_RG_CCONFINE_S);
	ADD_ESTATE(EFST_NJ_UTSUSEMI, ESTATE_NJ_UTSUSEMI);
	ADD_ESTATE(EFST_NJ_BUNSINJYUTSU, ESTATE_NJ_BUNSINJYUTSU);
	ADD_ESTATE(EFST_NJ_SUITON, ESTATE_NJ_SUITON);
	ADD_ESTATE(EFST_MENTAL, ESTATE_MENTAL);
	ADD_ESTATE(EFST_EXPMEMORY, ESTATE_EXPMEMORY);
	ADD_ESTATE(EFST_PERFORMANCE, ESTATE_PERFORMANCE);
	ADD_ESTATE(EFST_GAIN, ESTATE_GAIN);
	ADD_ESTATE(EFST_DRIFT, ESTATE_DRIFT);
	ADD_ESTATE(EFST_WALLSHIFT, ESTATE_WALLSHIFT);
	ADD_ESTATE(EFST_REINCARNATION, ESTATE_REINCARNATION);
	ADD_ESTATE(EFST_DENERGY, ESTATE_DENERGY);
	ADD_ESTATE(EFST_DAURA, ESTATE_DAURA);
	ADD_ESTATE(EFST_DFREEZER, ESTATE_DFREEZER);
	ADD_ESTATE(EFST_DPUNISH, ESTATE_DPUNISH);
	ADD_ESTATE(EFST_DBARRIER, ESTATE_DBARRIER);
	ADD_ESTATE(EFST_DWARNING, ESTATE_DWARNING);
	ADD_ESTATE(EFST_MOUSEWHEEL, ESTATE_MOUSEWHEEL);
	ADD_ESTATE(EFST_DACCEL, ESTATE_DACCEL);
	ADD_ESTATE(EFST_DBLOCK, ESTATE_DBLOCK);
	ADD_ESTATE(EFST_FOOD_STR, ESTATE_FOOD_STR);
	ADD_ESTATE(EFST_FOOD_AGI, ESTATE_FOOD_AGI);
	ADD_ESTATE(EFST_FOOD_VIT, ESTATE_FOOD_VIT);
	ADD_ESTATE(EFST_FOOD_DEX, ESTATE_FOOD_DEX);
	ADD_ESTATE(EFST_FOOD_INT, ESTATE_FOOD_INT);
	ADD_ESTATE(EFST_FOOD_LUK, ESTATE_FOOD_LUK);
	ADD_ESTATE(EFST_FOOD_BASICAVOIDANCE, ESTATE_FOOD_BASICAVOIDANCE);
	ADD_ESTATE(EFST_FOOD_BASICHIT, ESTATE_FOOD_BASICHIT);
	ADD_ESTATE(EFST_FOOD_CRITICALSUCCESSVALUE, ESTATE_FOOD_CRITICALSUCCESSVALUE);
	ADD_ESTATE(EFST_CASH_PLUSEXP, ESTATE_CASH_PLUSEXP);
	ADD_ESTATE(EFST_CASH_DEATHPENALTY, ESTATE_CASH_DEATHPENALTY);
	ADD_ESTATE(EFST_CASH_RECEIVEITEM, ESTATE_CASH_RECEIVEITEM);
	ADD_ESTATE(EFST_CASH_BOSS_ALARM, ESTATE_CASH_BOSS_ALARM);
	ADD_ESTATE(EFST_DA_ENERGY, ESTATE_DA_ENERGY);
	ADD_ESTATE(EFST_DA_FIRSTSLOT, ESTATE_DA_FIRSTSLOT);
	ADD_ESTATE(EFST_DA_HEADDEF, ESTATE_DA_HEADDEF);
	ADD_ESTATE(EFST_DA_SPACE, ESTATE_DA_SPACE);
	ADD_ESTATE(EFST_DA_ITEMREBUILD, ESTATE_DA_ITEMREBUILD);
	ADD_ESTATE(EFST_DA_ILLUSION, ESTATE_DA_ILLUSION);
	ADD_ESTATE(EFST_DA_EARPLUG, ESTATE_DA_EARPLUG);
	ADD_ESTATE(EFST_DA_CONTRACT, ESTATE_DA_CONTRACT);
	ADD_ESTATE(EFST_DA_BLACK, ESTATE_DA_BLACK);
	ADD_ESTATE(EFST_DA_MAGICCART, ESTATE_DA_MAGICCART);
	ADD_ESTATE(EFST_CRYSTAL, ESTATE_CRYSTAL);
	ADD_ESTATE(EFST_DA_REBUILD, ESTATE_DA_REBUILD);
	ADD_ESTATE(EFST_DA_EDARKNESS, ESTATE_DA_EDARKNESS);
	ADD_ESTATE(EFST_DA_EGUARDIAN, ESTATE_DA_EGUARDIAN);
	ADD_ESTATE(EFST_DA_TIMEOUT, ESTATE_DA_TIMEOUT);
	ADD_ESTATE(EFST_FOOD_STR_CASH, ESTATE_FOOD_STR_CASH);
	ADD_ESTATE(EFST_FOOD_AGI_CASH, ESTATE_FOOD_AGI_CASH);
	ADD_ESTATE(EFST_FOOD_VIT_CASH, ESTATE_FOOD_VIT_CASH);
	ADD_ESTATE(EFST_FOOD_DEX_CASH, ESTATE_FOOD_DEX_CASH);
	ADD_ESTATE(EFST_FOOD_INT_CASH, ESTATE_FOOD_INT_CASH);
	ADD_ESTATE(EFST_FOOD_LUK_CASH, ESTATE_FOOD_LUK_CASH);
	ADD_ESTATE(EFST_MER_FLEE, ESTATE_MER_FLEE);
	ADD_ESTATE(EFST_MER_ATK, ESTATE_MER_ATK);
	ADD_ESTATE(EFST_MER_HP, ESTATE_MER_HP);
	ADD_ESTATE(EFST_MER_SP, ESTATE_MER_SP);
	ADD_ESTATE(EFST_MER_HIT, ESTATE_MER_HIT);
	ADD_ESTATE(EFST_SLOWCAST, ESTATE_SLOWCAST);
	ADD_ESTATE(EFST_CRITICALWOUND, ESTATE_CRITICALWOUND);
	ADD_ESTATE(EFST_MOVHASTE_HORSE, ESTATE_MOVHASTE_HORSE);
	ADD_ESTATE(EFST_PROTECT_DEF, ESTATE_PROTECT_DEF);
	ADD_ESTATE(EFST_PROTECT_MDEF, ESTATE_PROTECT_MDEF);
	ADD_ESTATE(EFST_HEALPLUS, ESTATE_HEALPLUS);
	ADD_ESTATE(EFST_S_LIFEPOTION, ESTATE_S_LIFEPOTION);
	ADD_ESTATE(EFST_L_LIFEPOTION, ESTATE_L_LIFEPOTION);
	ADD_ESTATE(EFST_CRITICALPERCENT, ESTATE_CRITICALPERCENT);
	ADD_ESTATE(EFST_PLUSAVOIDVALUE, ESTATE_PLUSAVOIDVALUE);
	ADD_ESTATE(EFST_ATKER_ASPD, ESTATE_ATKER_ASPD);
	ADD_ESTATE(EFST_TARGET_ASPD, ESTATE_TARGET_ASPD);
	ADD_ESTATE(EFST_ATKER_MOVESPEED, ESTATE_ATKER_MOVESPEED);
	ADD_ESTATE(EFST_ATKER_BLOOD, ESTATE_ATKER_BLOOD);
	ADD_ESTATE(EFST_TARGET_BLOOD, ESTATE_TARGET_BLOOD);
	ADD_ESTATE(EFST_ARMOR_PROPERTY, ESTATE_ARMOR_PROPERTY);
	ADD_ESTATE(EFST_REUSE_LIMIT_A, ESTATE_REUSE_LIMIT_A);
	ADD_ESTATE(EFST_HELLPOWER, ESTATE_HELLPOWER);
	ADD_ESTATE(EFST_STEAMPACK, ESTATE_STEAMPACK);
	ADD_ESTATE(EFST_REUSE_LIMIT_B, ESTATE_REUSE_LIMIT_B);
	ADD_ESTATE(EFST_REUSE_LIMIT_C, ESTATE_REUSE_LIMIT_C);
	ADD_ESTATE(EFST_REUSE_LIMIT_D, ESTATE_REUSE_LIMIT_D);
	ADD_ESTATE(EFST_REUSE_LIMIT_E, ESTATE_REUSE_LIMIT_E);
	ADD_ESTATE(EFST_REUSE_LIMIT_F, ESTATE_REUSE_LIMIT_F);
	ADD_ESTATE(EFST_REUSE_LIMIT_G, ESTATE_REUSE_LIMIT_G);
	ADD_ESTATE(EFST_REUSE_LIMIT_H, ESTATE_REUSE_LIMIT_H);
	ADD_ESTATE(EFST_CASH_PLUSONLYJOBEXP, ESTATE_CASH_PLUSONLYJOBEXP);
	ADD_ESTATE(EFST_PARTYFLEE, ESTATE_PARTYFLEE);
	ADD_ESTATE(EFST_ANGEL_PROTECT, ESTATE_ANGEL_PROTECT);
	ADD_ESTATE(EFST_ENDURE_MDEF, ESTATE_ENDURE_MDEF);
	ADD_ESTATE(EFST_ENCHANTBLADE, ESTATE_ENCHANTBLADE);
	ADD_ESTATE(EFST_DEATHBOUND, ESTATE_DEATHBOUND);
	ADD_ESTATE(EFST_REFRESH, ESTATE_REFRESH);
	ADD_ESTATE(EFST_GIANTGROWTH, ESTATE_GIANTGROWTH);
	ADD_ESTATE(EFST_STONEHARDSKIN, ESTATE_STONEHARDSKIN);
	ADD_ESTATE(EFST_VITALITYACTIVATION, ESTATE_VITALITYACTIVATION);
	ADD_ESTATE(EFST_FIGHTINGSPIRIT, ESTATE_FIGHTINGSPIRIT);
	ADD_ESTATE(EFST_ABUNDANCE, ESTATE_ABUNDANCE);
	ADD_ESTATE(EFST_REUSE_MILLENNIUMSHIELD, ESTATE_REUSE_MILLENNIUMSHIELD);
	ADD_ESTATE(EFST_REUSE_CRUSHSTRIKE, ESTATE_REUSE_CRUSHSTRIKE);
	ADD_ESTATE(EFST_REUSE_REFRESH, ESTATE_REUSE_REFRESH);
	ADD_ESTATE(EFST_REUSE_STORMBLAST, ESTATE_REUSE_STORMBLAST);
	ADD_ESTATE(EFST_EPICLESIS, ESTATE_EPICLESIS);
	ADD_ESTATE(EFST_ORATIO, ESTATE_ORATIO);
	ADD_ESTATE(EFST_LAUDAAGNUS, ESTATE_LAUDAAGNUS);
	ADD_ESTATE(EFST_LAUDARAMUS, ESTATE_LAUDARAMUS);
	ADD_ESTATE(EFST_EXPIATIO, ESTATE_EXPIATIO);
	ADD_ESTATE(EFST_DUPLELIGHT, ESTATE_DUPLELIGHT);
	ADD_ESTATE(EFST_ELECTRICSHOCKER, ESTATE_ELECTRICSHOCKER);
	ADD_ESTATE(EFST_MARSHOFABYSS, ESTATE_MARSHOFABYSS);
	ADD_ESTATE(EFST_RECOGNIZEDSPELL, ESTATE_RECOGNIZEDSPELL);
	ADD_ESTATE(EFST_WUGRIDER, ESTATE_WUGRIDER);
	ADD_ESTATE(EFST_WUGDASH, ESTATE_WUGDASH);
	ADD_ESTATE(EFST_WUGBITE, ESTATE_WUGBITE);
	ADD_ESTATE(EFST_MVPCARD_TAOGUNKA, ESTATE_MVPCARD_TAOGUNKA);
	ADD_ESTATE(EFST_MVPCARD_MISTRESS, ESTATE_MVPCARD_MISTRESS);
	ADD_ESTATE(EFST_MVPCARD_ORCHERO, ESTATE_MVPCARD_ORCHERO);
	ADD_ESTATE(EFST_MVPCARD_ORCLORD, ESTATE_MVPCARD_ORCLORD);
	ADD_ESTATE(EFST_MANU_ATK, ESTATE_MANU_ATK);
	ADD_ESTATE(EFST_MANU_DEF, ESTATE_MANU_DEF);
	ADD_ESTATE(EFST_SPL_ATK, ESTATE_SPL_ATK);
	ADD_ESTATE(EFST_SPL_DEF, ESTATE_SPL_DEF);
	ADD_ESTATE(EFST_MANU_MATK, ESTATE_MANU_MATK);
	ADD_ESTATE(EFST_SPL_MATK, ESTATE_SPL_MATK);
	ADD_ESTATE(EFST_STR_SCROLL, ESTATE_STR_SCROLL);
	ADD_ESTATE(EFST_INT_SCROLL, ESTATE_INT_SCROLL);
	ADD_ESTATE(EFST_BUCHEDENOEL, ESTATE_BUCHEDENOEL);
	ADD_ESTATE(EFST_AUTOSHADOWSPELL, ESTATE_AUTOSHADOWSPELL);
	ADD_ESTATE(EFST_RAID, ESTATE_RAID);
	ADD_ESTATE(EFST_EXEEDBREAK, ESTATE_EXEEDBREAK);
	ADD_ESTATE(EFST_ACARAJE, ESTATE_ACARAJE);
	ADD_ESTATE(EFST_CRESCENTELBOW, ESTATE_CRESCENTELBOW);
	ADD_ESTATE(EFST_NOEQUIPACCESSARY, ESTATE_NOEQUIPACCESSARY);
	ADD_ESTATE(EFST_POPECOOKIE, ESTATE_POPECOOKIE);
	ADD_ESTATE(EFST_SKELSCROLL, ESTATE_SKELSCROLL);
	ADD_ESTATE(EFST_DISTRUCTIONSCROLL, ESTATE_DISTRUCTIONSCROLL);
	ADD_ESTATE(EFST_ROYALSCROLL, ESTATE_ROYALSCROLL);
	ADD_ESTATE(EFST_IMMUNITYSCROLL, ESTATE_IMMUNITYSCROLL);
	ADD_ESTATE(EFST_MYSTICSCROLL, ESTATE_MYSTICSCROLL);
	ADD_ESTATE(EFST_BATTLESCROLL, ESTATE_BATTLESCROLL);
	ADD_ESTATE(EFST_ARMORSCROLL, ESTATE_ARMORSCROLL);
	ADD_ESTATE(EFST_FREYJASCROLL, ESTATE_FREYJASCROLL);
	ADD_ESTATE(EFST_SOULSCROLL, ESTATE_SOULSCROLL);
	ADD_ESTATE(EFST_G_LIFEPOTION, ESTATE_G_LIFEPOTION);
	ADD_ESTATE(EFST_VITALIZE_POTION, ESTATE_VITALIZE_POTION);
	ADD_ESTATE(EFST_MAGIC_CANDY, ESTATE_MAGIC_CANDY);
	ADD_ESTATE(EFST_ALL_RIDING, ESTATE_ALL_RIDING);
	ADD_ESTATE(EFST_ALL_RIDING_REUSE_LIMIT, ESTATE_ALL_RIDING_REUSE_LIMIT);
	ADD_ESTATE(EFST_RENOVATIO, ESTATE_RENOVATIO);
	ADD_ESTATE(EFST_ADORAMUS, ESTATE_ADORAMUS);
	ADD_ESTATE(EFST_FROSTMISTY, ESTATE_FROSTMISTY);
	ADD_ESTATE(EFST_SUMMON1, ESTATE_SUMMON1);
	ADD_ESTATE(EFST_SUMMON2, ESTATE_SUMMON2);
	ADD_ESTATE(EFST_SUMMON3, ESTATE_SUMMON3);
	ADD_ESTATE(EFST_SUMMON4, ESTATE_SUMMON4);
	ADD_ESTATE(EFST_SUMMON5, ESTATE_SUMMON5);
	ADD_ESTATE(EFST_SHADOWFORM, ESTATE_SHADOWFORM);
	ADD_ESTATE(EFST_BODYPAINT, ESTATE_BODYPAINT);
	ADD_ESTATE(EFST_INVISIBILITY, ESTATE_INVISIBILITY);
	ADD_ESTATE(EFST_DEADLYINFECT, ESTATE_DEADLYINFECT);
	ADD_ESTATE(EFST_ENERVATION, ESTATE_ENERVATION);
	ADD_ESTATE(EFST_GROOMY, ESTATE_GROOMY);
	ADD_ESTATE(EFST_IGNORANCE, ESTATE_IGNORANCE);
	ADD_ESTATE(EFST_LAZINESS, ESTATE_LAZINESS);
	ADD_ESTATE(EFST_UNLUCKY, ESTATE_UNLUCKY);
	ADD_ESTATE(EFST_WEAKNESS, ESTATE_WEAKNESS);
	ADD_ESTATE(EFST_STRIPACCESSARY, ESTATE_STRIPACCESSARY);
	ADD_ESTATE(EFST_MANHOLE, ESTATE_MANHOLE);
	ADD_ESTATE(EFST_BLOODYLUST, ESTATE_BLOODYLUST);
	ADD_ESTATE(EFST_SWING, ESTATE_SWING);
	ADD_ESTATE(EFST_SYMPHONY_LOVE, ESTATE_SYMPHONY_LOVE);
	ADD_ESTATE(EFST_NETHERWORLD, ESTATE_NETHERWORLD);
	ADD_ESTATE(EFST_SIREN, ESTATE_SIREN);
	ADD_ESTATE(EFST_HANDICAPSTATE_DEEP_SLEEP, ESTATE_HANDICAPSTATE_DEEP_SLEEP);
	ADD_ESTATE(EFST_SIRCLEOFNATURE, ESTATE_SIRCLEOFNATURE);
	ADD_ESTATE(EFST_GLOOMYDAY, ESTATE_GLOOMYDAY);
	ADD_ESTATE(EFST_SONG_OF_MANA, ESTATE_SONG_OF_MANA);
	ADD_ESTATE(EFST_DANCE_WITH_WUG, ESTATE_DANCE_WITH_WUG);
	ADD_ESTATE(EFST_RUSH_WINDMILL, ESTATE_RUSH_WINDMILL);
	ADD_ESTATE(EFST_ECHOSONG, ESTATE_ECHOSONG);
	ADD_ESTATE(EFST_HARMONIZE, ESTATE_HARMONIZE);
	ADD_ESTATE(EFST_MOONLIT_SERENADE, ESTATE_MOONLIT_SERENADE);
	ADD_ESTATE(EFST_SATURDAY_NIGHT_FEVER, ESTATE_SATURDAY_NIGHT_FEVER);
	ADD_ESTATE(EFST_SITDOWN_FORCE, ESTATE_SITDOWN_FORCE);
	ADD_ESTATE(EFST_LERADS_DEW, ESTATE_LERADS_DEW);
	ADD_ESTATE(EFST_MELODYOFSINK, ESTATE_MELODYOFSINK);
	ADD_ESTATE(EFST_BEYOND_OF_WARCRY, ESTATE_BEYOND_OF_WARCRY);
	ADD_ESTATE(EFST_UNLIMITED_HUMMING_VOICE, ESTATE_UNLIMITED_HUMMING_VOICE);
	ADD_ESTATE(EFST_LG_REFLECTDAMAGE, ESTATE_LG_REFLECTDAMAGE);
	ADD_ESTATE(EFST_FORCEOFVANGUARD, ESTATE_FORCEOFVANGUARD);
	ADD_ESTATE(EFST_SHIELDSPELL_DEF, ESTATE_SHIELDSPELL_DEF);
	ADD_ESTATE(EFST_SHIELDSPELL_MDEF, ESTATE_SHIELDSPELL_MDEF);
	ADD_ESTATE(EFST_SHIELDSPELL_REF, ESTATE_SHIELDSPELL_REF);
	ADD_ESTATE(EFST_PRESTIGE, ESTATE_PRESTIGE);
	ADD_ESTATE(EFST_BANDING, ESTATE_BANDING);
	ADD_ESTATE(EFST_BANDING_DEFENCE, ESTATE_BANDING_DEFENCE);
	ADD_ESTATE(EFST_EARTHDRIVE, ESTATE_EARTHDRIVE);
	ADD_ESTATE(EFST_INSPIRATION, ESTATE_INSPIRATION);
	ADD_ESTATE(EFST_RAISINGDRAGON, ESTATE_RAISINGDRAGON);
	ADD_ESTATE(EFST_LIGHTNINGWALK, ESTATE_LIGHTNINGWALK);
	ADD_ESTATE(EFST_CAMOUFLAGE, ESTATE_CAMOUFLAGE);
	ADD_ESTATE(EFST_GENTLETOUCH_ENERGYGAIN, ESTATE_GENTLETOUCH_ENERGYGAIN);
	ADD_ESTATE(EFST_GENTLETOUCH_CHANGE, ESTATE_GENTLETOUCH_CHANGE);
	ADD_ESTATE(EFST_GENTLETOUCH_REVITALIZE, ESTATE_GENTLETOUCH_REVITALIZE);
	ADD_ESTATE(EFST_PROPERTYWALK, ESTATE_PROPERTYWALK);
	ADD_ESTATE(EFST_SPELLFIST, ESTATE_SPELLFIST);
	ADD_ESTATE(EFST_CLOUD_KILL, ESTATE_CLOUD_KILL);
	ADD_ESTATE(EFST_FALLENEMPIRE, ESTATE_FALLENEMPIRE);
	ADD_ESTATE(EFST_CURSEDCIRCLE_ATKER, ESTATE_CURSEDCIRCLE_ATKER);
	ADD_ESTATE(EFST_CURSEDCIRCLE_TARGET, ESTATE_CURSEDCIRCLE_TARGET);
	ADD_ESTATE(EFST_STRIKING, ESTATE_STRIKING);
	ADD_ESTATE(EFST_COLD, ESTATE_COLD);
	ADD_ESTATE(EFST_WARMER, ESTATE_WARMER);
	ADD_ESTATE(EFST_VACUUM_EXTREME, ESTATE_VACUUM_EXTREME);
	ADD_ESTATE(EFST_GN_TRAINING_SWORD, ESTATE_GN_TRAINING_SWORD);
	ADD_ESTATE(EFST_GN_REMODELING_CART, ESTATE_GN_REMODELING_CART);
	ADD_ESTATE(EFST_REPRODUCE, ESTATE_REPRODUCE);
	ADD_ESTATE(EFST_GN_CARTBOOST, ESTATE_GN_CARTBOOST);
	ADD_ESTATE(EFST_THORNS_TRAP, ESTATE_THORNS_TRAP);
	ADD_ESTATE(EFST_BLOOD_SUCKER, ESTATE_BLOOD_SUCKER);
	ADD_ESTATE(EFST_SPORE_EXPLOSION, ESTATE_SPORE_EXPLOSION);
	ADD_ESTATE(EFST_DEMONIC_FIRE, ESTATE_DEMONIC_FIRE);
	ADD_ESTATE(EFST_FIRE_EXPANSION_SMOKE_POWDER, ESTATE_FIRE_EXPANSION_SMOKE_POWDER);
	ADD_ESTATE(EFST_FIRE_EXPANSION_TEAR_GAS, ESTATE_FIRE_EXPANSION_TEAR_GAS);
	ADD_ESTATE(EFST_MANDRAGORA, ESTATE_MANDRAGORA);
	ADD_ESTATE(EFST_VENOMIMPRESS, ESTATE_VENOMIMPRESS);
	ADD_ESTATE(EFST_POISONINGWEAPON, ESTATE_POISONINGWEAPON);
	ADD_ESTATE(EFST_TOXIN, ESTATE_TOXIN);
	ADD_ESTATE(EFST_PARALYSE, ESTATE_PARALYSE);
	ADD_ESTATE(EFST_VENOMBLEED, ESTATE_VENOMBLEED);
	ADD_ESTATE(EFST_MAGICMUSHROOM, ESTATE_MAGICMUSHROOM);
	ADD_ESTATE(EFST_DEATHHURT, ESTATE_DEATHHURT);
	ADD_ESTATE(EFST_PYREXIA, ESTATE_PYREXIA);
	ADD_ESTATE(EFST_OBLIVIONCURSE, ESTATE_OBLIVIONCURSE);
	ADD_ESTATE(EFST_LEECHESEND, ESTATE_LEECHESEND);
	ADD_ESTATE(EFST_WEAPONBLOCKING, ESTATE_WEAPONBLOCKING);
	ADD_ESTATE(EFST_WEAPONBLOCKING_POSTDELAY, ESTATE_WEAPONBLOCKING_POSTDELAY);
	ADD_ESTATE(EFST_CLOAKINGEXCEED, ESTATE_CLOAKINGEXCEED);
	ADD_ESTATE(EFST_HALLUCINATIONWALK, ESTATE_HALLUCINATIONWALK);
	ADD_ESTATE(EFST_HALLUCINATIONWALK_POSTDELAY, ESTATE_HALLUCINATIONWALK_POSTDELAY);
	ADD_ESTATE(EFST_ROLLINGCUTTER, ESTATE_ROLLINGCUTTER);
	ADD_ESTATE(EFST_FEARBREEZE, ESTATE_FEARBREEZE);
	ADD_ESTATE(EFST_ACCELERATION, ESTATE_ACCELERATION);
	ADD_ESTATE(EFST_HOVERING, ESTATE_HOVERING);
	ADD_ESTATE(EFST_OVERHEAT_LIMITPOINT, ESTATE_OVERHEAT_LIMITPOINT);
	ADD_ESTATE(EFST_OVERHEAT, ESTATE_OVERHEAT);
	ADD_ESTATE(EFST_SHAPESHIFT, ESTATE_SHAPESHIFT);
	ADD_ESTATE(EFST_INFRAREDSCAN, ESTATE_INFRAREDSCAN);
	ADD_ESTATE(EFST_ANALYZE, ESTATE_ANALYZE);
	ADD_ESTATE(EFST_MAGNETICFIELD, ESTATE_MAGNETICFIELD);
	ADD_ESTATE(EFST_NEUTRALBARRIER, ESTATE_NEUTRALBARRIER);
	ADD_ESTATE(EFST_NEUTRALBARRIER_MASTER, ESTATE_NEUTRALBARRIER_MASTER);
	ADD_ESTATE(EFST_STEALTHFIELD, ESTATE_STEALTHFIELD);
	ADD_ESTATE(EFST_STEALTHFIELD_MASTER, ESTATE_STEALTHFIELD_MASTER);
	ADD_ESTATE(EFST_SPELLBOOK1, ESTATE_SPELLBOOK1);
	ADD_ESTATE(EFST_SPELLBOOK2, ESTATE_SPELLBOOK2);
	ADD_ESTATE(EFST_SPELLBOOK3, ESTATE_SPELLBOOK3);
	ADD_ESTATE(EFST_SPELLBOOK4, ESTATE_SPELLBOOK4);
	ADD_ESTATE(EFST_SPELLBOOK5, ESTATE_SPELLBOOK5);
	ADD_ESTATE(EFST_SPELLBOOK6, ESTATE_SPELLBOOK6);
	ADD_ESTATE(EFST_SPELLBOOK7, ESTATE_SPELLBOOK7);
	ADD_ESTATE(EFST_FREEZE_SP, ESTATE_FREEZE_SP);
	ADD_ESTATE(EFST_FIXEDCASTINGTM_REDUCE, ESTATE_FIXEDCASTINGTM_REDUCE);
	ADD_ESTATE(EFST_AB_SECRAMENT, ESTATE_AB_SECRAMENT);
	ADD_ESTATE(EFST_ASSUMPTIO2, ESTATE_ASSUMPTIO2);
	ADD_ESTATE(EFST_TK_SEVENWIND, ESTATE_TK_SEVENWIND);
	ADD_ESTATE(EFST_LIMIT_ODINS_RECALL, ESTATE_LIMIT_ODINS_RECALL);
	ADD_ESTATE(EFST_RETURN_TO_ELDICASTES, ESTATE_RETURN_TO_ELDICASTES);
	ADD_ESTATE(EFST_GUARDIAN_RECALL, ESTATE_GUARDIAN_RECALL);
	ADD_ESTATE(EFST_MORA_BUFF, ESTATE_MORA_BUFF);
	ADD_ESTATE(EFST_ODINS_POWER, ESTATE_ODINS_POWER);
	ADD_ESTATE(EFST_SPIRITS_SAVEINFO1, ESTATE_SPIRITS_SAVEINFO1);
	ADD_ESTATE(EFST_SPIRITS_SAVEINFO2, ESTATE_SPIRITS_SAVEINFO2);
	ADD_ESTATE(EFST_SAVAGE_STEAK, ESTATE_SAVAGE_STEAK);
	ADD_ESTATE(EFST_COCKTAIL_WARG_BLOOD, ESTATE_COCKTAIL_WARG_BLOOD);
	ADD_ESTATE(EFST_MINOR_BBQ, ESTATE_MINOR_BBQ);
	ADD_ESTATE(EFST_SIROMA_ICE_TEA, ESTATE_SIROMA_ICE_TEA);
	ADD_ESTATE(EFST_DROCERA_HERB_STEAMED, ESTATE_DROCERA_HERB_STEAMED);
	ADD_ESTATE(EFST_PUTTI_TAILS_NOODLES, ESTATE_PUTTI_TAILS_NOODLES);
	ADD_ESTATE(EFST_STOMACHACHE, ESTATE_STOMACHACHE);
	ADD_ESTATE(EFST_MYSTERIOUS_POWDER, ESTATE_MYSTERIOUS_POWDER);
	ADD_ESTATE(EFST_MELON_BOMB, ESTATE_MELON_BOMB);
	ADD_ESTATE(EFST_BANANA_BOMB_SITDOWN_POSTDELAY, ESTATE_BANANA_BOMB_SITDOWN_POSTDELAY);
	ADD_ESTATE(EFST_BANANA_BOMB, ESTATE_BANANA_BOMB);
	ADD_ESTATE(EFST_PROMOTE_HEALTH_RESERCH, ESTATE_PROMOTE_HEALTH_RESERCH);
	ADD_ESTATE(EFST_ENERGY_DRINK_RESERCH, ESTATE_ENERGY_DRINK_RESERCH);
	ADD_ESTATE(EFST_EXTRACT_WHITE_POTION_Z, ESTATE_EXTRACT_WHITE_POTION_Z);
	ADD_ESTATE(EFST_VITATA_500, ESTATE_VITATA_500);
	ADD_ESTATE(EFST_EXTRACT_SALAMINE_JUICE, ESTATE_EXTRACT_SALAMINE_JUICE);
	ADD_ESTATE(EFST_BOOST500, ESTATE_BOOST500);
	ADD_ESTATE(EFST_FULL_SWING_K, ESTATE_FULL_SWING_K);
	ADD_ESTATE(EFST_MANA_PLUS, ESTATE_MANA_PLUS);
	ADD_ESTATE(EFST_MUSTLE_M, ESTATE_MUSTLE_M);
	ADD_ESTATE(EFST_LIFE_FORCE_F, ESTATE_LIFE_FORCE_F);
	ADD_ESTATE(EFST_WATER_BARRIER, ESTATE_WATER_BARRIER);
	ADD_ESTATE(EFST_ZEPHYR, ESTATE_ZEPHYR);
	ADD_ESTATE(EFST_POWER_OF_GAIA, ESTATE_POWER_OF_GAIA);
	ADD_ESTATE(EFST_EL_WAIT, ESTATE_EL_WAIT);
	ADD_ESTATE(EFST_EL_PASSIVE, ESTATE_EL_PASSIVE);
	ADD_ESTATE(EFST_EL_COST, ESTATE_EL_COST);
	ADD_ESTATE(EFST_PYROTECHNIC, ESTATE_PYROTECHNIC);
	ADD_ESTATE(EFST_PYROTECHNIC_OPTION, ESTATE_PYROTECHNIC_OPTION);
	ADD_ESTATE(EFST_HEATER, ESTATE_HEATER);
	ADD_ESTATE(EFST_HEATER_OPTION, ESTATE_HEATER_OPTION);
	ADD_ESTATE(EFST_TROPIC, ESTATE_TROPIC);
	ADD_ESTATE(EFST_TROPIC_OPTION, ESTATE_TROPIC_OPTION);
	ADD_ESTATE(EFST_AQUAPLAY, ESTATE_AQUAPLAY);
	ADD_ESTATE(EFST_AQUAPLAY_OPTION, ESTATE_AQUAPLAY_OPTION);
	ADD_ESTATE(EFST_COOLER, ESTATE_COOLER);
	ADD_ESTATE(EFST_COOLER_OPTION, ESTATE_COOLER_OPTION);
	ADD_ESTATE(EFST_CHILLY_AIR, ESTATE_CHILLY_AIR);
	ADD_ESTATE(EFST_CHILLY_AIR_OPTION, ESTATE_CHILLY_AIR_OPTION);
	ADD_ESTATE(EFST_GUST, ESTATE_GUST);
	ADD_ESTATE(EFST_GUST_OPTION, ESTATE_GUST_OPTION);
	ADD_ESTATE(EFST_BLAST, ESTATE_BLAST);
	ADD_ESTATE(EFST_BLAST_OPTION, ESTATE_BLAST_OPTION);
	ADD_ESTATE(EFST_WILD_STORM, ESTATE_WILD_STORM);
	ADD_ESTATE(EFST_WILD_STORM_OPTION, ESTATE_WILD_STORM_OPTION);
	ADD_ESTATE(EFST_PETROLOGY, ESTATE_PETROLOGY);
	ADD_ESTATE(EFST_PETROLOGY_OPTION, ESTATE_PETROLOGY_OPTION);
	ADD_ESTATE(EFST_CURSED_SOIL, ESTATE_CURSED_SOIL);
	ADD_ESTATE(EFST_CURSED_SOIL_OPTION, ESTATE_CURSED_SOIL_OPTION);
	ADD_ESTATE(EFST_UPHEAVAL, ESTATE_UPHEAVAL);
	ADD_ESTATE(EFST_UPHEAVAL_OPTION, ESTATE_UPHEAVAL_OPTION);
	ADD_ESTATE(EFST_EL_DEFENSIVE, ESTATE_EL_DEFENSIVE);
	ADD_ESTATE(EFST_CIRCLE_OF_FIRE, ESTATE_CIRCLE_OF_FIRE);
	ADD_ESTATE(EFST_CIRCLE_OF_FIRE_OPTION, ESTATE_CIRCLE_OF_FIRE_OPTION);
	ADD_ESTATE(EFST_FIRE_CLOAK, ESTATE_FIRE_CLOAK);
	ADD_ESTATE(EFST_FIRE_CLOAK_OPTION, ESTATE_FIRE_CLOAK_OPTION);
	ADD_ESTATE(EFST_WATER_SCREEN, ESTATE_WATER_SCREEN);
	ADD_ESTATE(EFST_WATER_SCREEN_OPTION, ESTATE_WATER_SCREEN_OPTION);
	ADD_ESTATE(EFST_WATER_DROP, ESTATE_WATER_DROP);
	ADD_ESTATE(EFST_WATER_DROP_OPTION, ESTATE_WATER_DROP_OPTION);
	ADD_ESTATE(EFST_WIND_STEP, ESTATE_WIND_STEP);
	ADD_ESTATE(EFST_WIND_STEP_OPTION, ESTATE_WIND_STEP_OPTION);
	ADD_ESTATE(EFST_WIND_CURTAIN, ESTATE_WIND_CURTAIN);
	ADD_ESTATE(EFST_WIND_CURTAIN_OPTION, ESTATE_WIND_CURTAIN_OPTION);
	ADD_ESTATE(EFST_SOLID_SKIN, ESTATE_SOLID_SKIN);
	ADD_ESTATE(EFST_SOLID_SKIN_OPTION, ESTATE_SOLID_SKIN_OPTION);
	ADD_ESTATE(EFST_STONE_SHIELD, ESTATE_STONE_SHIELD);
	ADD_ESTATE(EFST_STONE_SHIELD_OPTION, ESTATE_STONE_SHIELD_OPTION);
	ADD_ESTATE(EFST_EL_OFFENSIVE, ESTATE_EL_OFFENSIVE);
	ADD_ESTATE(EFST_TIDAL_WEAPON, ESTATE_TIDAL_WEAPON);
	ADD_ESTATE(EFST_TIDAL_WEAPON_OPTION, ESTATE_TIDAL_WEAPON_OPTION);
	ADD_ESTATE(EFST_ROCK_CRUSHER, ESTATE_ROCK_CRUSHER);
	ADD_ESTATE(EFST_ROCK_CRUSHER_ATK, ESTATE_ROCK_CRUSHER_ATK);
	ADD_ESTATE(EFST_FIRE_INSIGNIA, ESTATE_FIRE_INSIGNIA);
	ADD_ESTATE(EFST_WATER_INSIGNIA, ESTATE_WATER_INSIGNIA);
	ADD_ESTATE(EFST_WIND_INSIGNIA, ESTATE_WIND_INSIGNIA);
	ADD_ESTATE(EFST_EARTH_INSIGNIA, ESTATE_EARTH_INSIGNIA);
	ADD_ESTATE(EFST_EQUIPED_FLOOR, ESTATE_EQUIPED_FLOOR);
	ADD_ESTATE(EFST_NEEDLE_OF_PARALYZE, ESTATE_NEEDLE_OF_PARALYZE);
	ADD_ESTATE(EFST_PAIN_KILLER, ESTATE_PAIN_KILLER);
	ADD_ESTATE(EFST_OVERED_BOOST, ESTATE_OVERED_BOOST);
	ADD_ESTATE(EFST_LIGHT_OF_REGENE, ESTATE_LIGHT_OF_REGENE);
	ADD_ESTATE(EFST_STYLE_CHANGE, ESTATE_STYLE_CHANGE);
	ADD_ESTATE(EFST_SONIC_CLAW_POSTDELAY, ESTATE_SONIC_CLAW_POSTDELAY);
	ADD_ESTATE(EFST_SILVERVEIN_RUSH_POSTDELAY, ESTATE_SILVERVEIN_RUSH_POSTDELAY);
	ADD_ESTATE(EFST_MIDNIGHT_FRENZY_POSTDELAY, ESTATE_MIDNIGHT_FRENZY_POSTDELAY);
	ADD_ESTATE(EFST_GOLDENE_FERSE, ESTATE_GOLDENE_FERSE);
	ADD_ESTATE(EFST_ANGRIFFS_MODUS, ESTATE_ANGRIFFS_MODUS);
	ADD_ESTATE(EFST_TINDER_BREAKER, ESTATE_TINDER_BREAKER);
	ADD_ESTATE(EFST_TINDER_BREAKER_POSTDELAY, ESTATE_TINDER_BREAKER_POSTDELAY);
	ADD_ESTATE(EFST_CBC, ESTATE_CBC);
	ADD_ESTATE(EFST_CBC_POSTDELAY, ESTATE_CBC_POSTDELAY);
	ADD_ESTATE(EFST_EQC, ESTATE_EQC);
	ADD_ESTATE(EFST_MAGMA_FLOW, ESTATE_MAGMA_FLOW);
	ADD_ESTATE(EFST_GRANITIC_ARMOR, ESTATE_GRANITIC_ARMOR);
	ADD_ESTATE(EFST_PYROCLASTIC, ESTATE_PYROCLASTIC);
	ADD_ESTATE(EFST_VOLCANIC_ASH, ESTATE_VOLCANIC_ASH);
	ADD_ESTATE(EFST_SEARCH_STORE_INFO, ESTATE_SEARCH_STORE_INFO);
	ADD_ESTATE(EFST_MACRO, ESTATE_MACRO);
	ADD_ESTATE(EFST_MACRO_POSTDELAY, ESTATE_MACRO_POSTDELAY);
	ADD_ESTATE(EFST_BEER_BOTTLE_CAP, ESTATE_BEER_BOTTLE_CAP);
	ADD_ESTATE(EFST_OVERLAPEXPUP, ESTATE_OVERLAPEXPUP);
	ADD_ESTATE(EFST_PC_IZ_DUN05, ESTATE_PC_IZ_DUN05);
	ADD_ESTATE(EFST_CRUSHSTRIKE, ESTATE_CRUSHSTRIKE);
	ADD_ESTATE(EFST_MONSTER_TRANSFORM, ESTATE_MONSTER_TRANSFORM);
	ADD_ESTATE(EFST_MTF_ASPD, ESTATE_MTF_ASPD);
	ADD_ESTATE(EFST_MTF_RANGEATK, ESTATE_MTF_RANGEATK);
	ADD_ESTATE(EFST_MTF_MATK, ESTATE_MTF_MATK);
	ADD_ESTATE(EFST_MTF_MLEATKED, ESTATE_MTF_MLEATKED);
	ADD_ESTATE(EFST_MTF_CRIDAMAGE, ESTATE_MTF_CRIDAMAGE);
	ADD_ESTATE(EFST_REUSE_LIMIT_MTF, ESTATE_REUSE_LIMIT_MTF);
	ADD_ESTATE(EFST_SIT, ESTATE_SIT);
	ADD_ESTATE(EFST_SKF_CAST, ESTATE_SKF_CAST);
	ADD_ESTATE(EFST_SKF_ASPD, ESTATE_SKF_ASPD);
	ADD_ESTATE(EFST_SKF_ATK, ESTATE_SKF_ATK);
	ADD_ESTATE(EFST_SKF_MATK, ESTATE_SKF_MATK);
	ADD_ESTATE(EFST_REWARD_PLUSONLYJOBEXP, ESTATE_REWARD_PLUSONLYJOBEXP);
	ADD_ESTATE(EFST_EXTREMITYFIST, ESTATE_EXTREMITYFIST);
	ADD_ESTATE(EFST_PERIOD_TIME_CHECK_DETECT_SKILL, ESTATE_PERIOD_TIME_CHECK_DETECT_SKILL);
	ADD_ESTATE(EFST_ATTHASTE_CASH, ESTATE_ATTHASTE_CASH);
	ADD_ESTATE(EFST_2011RWC, ESTATE_2011RWC);
	ADD_ESTATE(EFST_TETANY, ESTATE_TETANY);
	ADD_ESTATE(EFST_2011RWC_SCROLL, ESTATE_2011RWC_SCROLL);
	ADD_ESTATE(EFST_ACTIVE_MONSTER_TRANSFORM, ESTATE_ACTIVE_MONSTER_TRANSFORM);
	ADD_ESTATE(EFST_M_LIFEPOTION, ESTATE_M_LIFEPOTION);
	ADD_ESTATE(EFST_ON_PUSH_CART, ESTATE_ON_PUSH_CART);
	ADD_ESTATE(EFST_ILLUSION, ESTATE_ILLUSION);
	ADD_ESTATE(EFST_ANKLESNARE, ESTATE_ANKLESNARE);
	ADD_ESTATE(EFST_MOVHASTE_INFINITY, ESTATE_MOVHASTE_INFINITY);
	ADD_ESTATE(EFST_STASIS, ESTATE_STASIS);
	ADD_ESTATE(EFST_STASIS, ESTATE_CUP_OF_BOZA);
	#undef ADD_ESTATE
*/
}


bool EStateTypeInfoMgr::CreateInstance()
{
	if( m_cpSelf != NULL )
		return false;

	m_cpSelf = new(std::nothrow) EStateTypeInfoMgr();
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->EStateTypeInfoMgr::isOK() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void EStateTypeInfoMgr::DestoryInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


EStateTypeInfoMgr* EStateTypeInfoMgr::GetObj() /// @custom
{
	return m_cpSelf;
}


bool EStateTypeInfoMgr::isOK() const
{
	return m_bOK;
}


ESTATE* EStateTypeInfoMgr::GetPtr(const int in_EStateID)
{
	ESTATETYPEINFO_CONTAINER::iterator iter = m_ESateTypeInfoList.find(in_EStateID);
	if( iter == m_ESateTypeInfoList.end() )
		return NULL;

	ESTATE* pEState = iter->second;
	return pEState;
}


ESTATE* EStateTypeInfoMgr::GetPtr(const char* in_EStateName)
{
	ESTATETYPEINFO_NAME_CONTAINER::iterator iter = m_EStateTypeInfoNameList.find(in_EStateName);
	if( iter == m_EStateTypeInfoNameList.end() )
		return NULL;

	ESTATE* pEState = iter->second;
	return pEState;
}


void EStateTypeInfoMgr::SetComplete(const int in_EStateID, CActor* in_cpActor, const int in_Time, const int in_Val1, const int in_Val2, const int in_Val3)
{
	ESTATETYPEINFO_CONTAINER::iterator iter = m_ESateTypeInfoList.find(in_EStateID);
	if( iter == m_ESateTypeInfoList.end() )
		return;

	ESTATE* pEState = iter->second;
	pEState->SetComplete(in_cpActor, in_Time, in_Val1, in_Val2, in_Val3);
}


bool EStateTypeInfoMgr::SetCheckup(const int in_EStateID, CActor* in_cpActor, int& io_Time, int& io_Val1, int& io_Val2, int& io_Val3)
{
	ESTATETYPEINFO_CONTAINER::iterator iter = m_ESateTypeInfoList.find(in_EStateID);
	if( iter == m_ESateTypeInfoList.end() )
		return true;

	ESTATE* pEState = iter->second;
	return pEState->SetCheckup(in_cpActor, io_Time, io_Val1, io_Val2, io_Val3);
}


void EStateTypeInfoMgr::ResetComplete(const int in_EStateID, CActor* in_cpActor, const int in_Val1, const int in_Val2, const int in_Val3)
{
	ESTATETYPEINFO_CONTAINER::iterator iter = m_ESateTypeInfoList.find(in_EStateID);
	if( iter == m_ESateTypeInfoList.end() )
		return;

	ESTATE* pEState = iter->second;
	pEState->ResetComplete(in_cpActor, in_Val1, in_Val2, in_Val3);
}


bool EStateTypeInfoMgr::ResetCheckup(const int in_EStateID, CActor* in_cpActor, const int in_Val, EFFECTIVE_INFO* io_pInfo)
{
	ESTATETYPEINFO_CONTAINER::iterator iter = m_ESateTypeInfoList.find(in_EStateID);
	if( iter == m_ESateTypeInfoList.end() )
		return true;

	ESTATE* pEState = iter->second;
	return pEState->ResetCheckup(in_cpActor, in_Val, io_pInfo);
}


void EStateTypeInfoMgr::Process(const int in_EStateID, CActor* in_cpActor, EFFECTIVE_INFO* io_pInfo)
{
	ESTATETYPEINFO_CONTAINER::iterator iter = m_ESateTypeInfoList.find(in_EStateID);
	if( iter == m_ESateTypeInfoList.end() )
		return;

	ESTATE* pEState = iter->second;
	pEState->Process(in_cpActor, io_pInfo);
}


bool EStateTypeInfoMgr::InitScript()
{
	if( !m_binBuf.CBinBuf::Load(GetScriptFileName(BIN_BUFF)) )
		return false;

	ESTATE_SCRIPT_SCANNER scanner;
	if( !scanner.ESTATE_SCRIPT_SCANNER::Scan(&m_binBuf) )
		return false;

	return true;
}


bool EStateTypeInfoMgr::RunScript(const unsigned long in_AID, const int in_EventType, const int in_EStateID)
{
	ESTATE* pEState = this->EStateTypeInfoMgr::GetPtr(in_EStateID);
	if( pEState == NULL )
		return false;

	if( !pEState->IsExistScript() )
		return false;

	ESTATE_SCRIPT* pEStateScript = static_cast<ESTATE_SCRIPT*>(pEState);

	int pos = pEStateScript->ESTATE_SCRIPT::GetScriptPos(in_EventType);
	if( pos == -1 )
		return false;

	CEfstScriptEventHandler handler;
	int identity = (in_EStateID & 0xFFFFFF) + 0x2000000;
	handler.CEfstScriptEventHandler::Set(in_AID, identity);

	if( !handler.CScriptEventHandler::RunInterpreter(&m_binBuf, pos) )
		return false;

	handler.CScriptEventHandler::Proc(true);

	return true;
}


int EStateTypeInfoMgr::GetEStateID(const char* in_EStateName)
{
	ESTATE* pEState = this->EStateTypeInfoMgr::GetPtr(in_EStateName);
	if( pEState == NULL )
		return -1;

	return pEState->ESTATE::GetID();
}


namespace {
std::set<int> GetInfinityTimeEfstSaveTbl()
{
	std::set<int> result;
	result.insert(EFST_MAXIMIZE);
	result.insert(EFST_DA_CONTRACT);
	result.insert(EFST_DA_REBUILD);
	result.insert(EFST_WUGRIDER);
	result.insert(EFST_BANDING);
	result.insert(EFST_REPRODUCE);
	result.insert(EFST_SPELLBOOK1);
	result.insert(EFST_SPELLBOOK2);
	result.insert(EFST_SPELLBOOK3);
	result.insert(EFST_SPELLBOOK4);
	result.insert(EFST_SPELLBOOK5);
	result.insert(EFST_SPELLBOOK6);
	result.insert(EFST_SPELLBOOK7);
	result.insert(EFST_EL_WAIT);
	result.insert(EFST_EL_PASSIVE);
	result.insert(EFST_EL_DEFENSIVE);
	result.insert(EFST_EL_OFFENSIVE);
	result.insert(EFST_STYLE_CHANGE);
	result.insert(EFST_ONAIR);
	result.insert(EFST_MACRO_PERMIT);
	result.insert(EFST_SAVEPOSITION);
	result.insert(EFST_ALL_RIDING);
	result.insert(EFST_OVERHEAT_LIMITPOINT);
	result.insert(EFST_OVERHEAT);
	result.insert(EFST_ON_PUSH_CART);
	result.erase(EFST_PYROTECHNIC_OPTION);
	result.erase(EFST_HEATER_OPTION);
	result.erase(EFST_TROPIC_OPTION);
	result.erase(EFST_AQUAPLAY_OPTION);
	result.erase(EFST_COOLER_OPTION);
	result.erase(EFST_CHILLY_AIR_OPTION);
	result.erase(EFST_GUST_OPTION);
	result.erase(EFST_BLAST_OPTION);
	result.erase(EFST_WILD_STORM_OPTION);
	result.erase(EFST_PETROLOGY_OPTION);
	result.erase(EFST_CURSED_SOIL_OPTION);
	result.erase(EFST_UPHEAVAL_OPTION);
	result.erase(EFST_CIRCLE_OF_FIRE_OPTION);
	result.erase(EFST_FIRE_CLOAK_OPTION);
	result.erase(EFST_WATER_SCREEN_OPTION);
	result.erase(EFST_WATER_DROP_OPTION);
	result.erase(EFST_WIND_STEP_OPTION);
	result.erase(EFST_WIND_CURTAIN_OPTION);
	result.erase(EFST_SOLID_SKIN_OPTION);
	result.erase(EFST_STONE_SHIELD_OPTION);
	result.erase(EFST_TIDAL_WEAPON_OPTION);
	return result;
}
}; // namespace


bool EStateTypeInfoMgr::IsSaveInfinitTimeEfst(const int in_Efst) const
{
	static std::set<int> InfinityTimeEfstSaveTbl = GetInfinityTimeEfstSaveTbl();
	return ( InfinityTimeEfstSaveTbl.find(in_Efst) != InfinityTimeEfstSaveTbl.end() );
}


bool EStateTypeInfoMgr::IsSave(const unsigned long in_CurTM, const int in_Efst, const EFFECTIVE_INFO& in_Data)
{
	if( in_Data.time == 9999 && !this->EStateTypeInfoMgr::IsSaveInfinitTimeEfst(in_Efst) )
		return false;

	ESTATE* pEState = this->EStateTypeInfoMgr::GetPtr(in_Efst);
	if( pEState == NULL )
		return false;

	if( !pEState->ESTATE::IsSave() )
		return false;

	if( in_Data.time != 9999 && in_CurTM >= in_Data.time )
		return false;

	return true;
}
