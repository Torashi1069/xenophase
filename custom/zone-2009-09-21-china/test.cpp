#include "NetLib/Connector.h"
#include "Instant Map/InstantMapRes.h"
#include "ScriptLib/Interpreter.h"
#include "GuildMgr.h"
#include "CCharBuff.hpp"
#include "Client.h"


void Test(void)
{
	CDia dia, dia2;
	dia.Open(EXEPATH());
	dia2.Open(DLLPATH());

	// some integrity checks:
	C_ASSERT( sizeof(float) == 4 );
	C_ASSERT( sizeof(long) == 4 );

	//CAcceptHandler
	COMPARE_SIZE(CAcceptHandler);
//	COMPARE_VTABLE(CAcceptHandler, OnConnect);
	//CActor
	COMPARE_SIZE(CActor);
	COMPARE_OFFSET(CActor, m_BodyStateValue);
	COMPARE_OFFSET(CActor, m_BodyStateTime);
	COMPARE_OFFSET(CActor, m_HealthStateTime);
	COMPARE_OFFSET(CActor, m_HealthStateValue);
	COMPARE_OFFSET(CActor, m_effectStateTimeL);
	//TODO: vtable
	//CAgitDB
	COMPARE_SIZE(CAgitDB);
	//CAgitMapRes
	COMPARE_SIZE(CAgitMapRes);
	COMPARE_OFFSET(CAgitMapRes, m_guildID);
	COMPARE_OFFSET(CAgitMapRes, m_agitName);
	COMPARE_OFFSET(CAgitMapRes, m_economy);
	COMPARE_OFFSET(CAgitMapRes, m_defense);
	COMPARE_OFFSET(CAgitMapRes, m_triggerE);
	COMPARE_OFFSET(CAgitMapRes, m_triggerD);
	COMPARE_OFFSET(CAgitMapRes, m_incTime);
	COMPARE_OFFSET(CAgitMapRes, m_payTime);
	COMPARE_OFFSET(CAgitMapRes, m_noGuardian);
	COMPARE_OFFSET(CAgitMapRes, m_guardianArray);
	COMPARE_OFFSET(CAgitMapRes, m_npcArray);
	COMPARE_OFFSET(CAgitMapRes, m_visibleC);
	COMPARE_OFFSET(CAgitMapRes, m_visibleG);
	COMPARE_OFFSET(CAgitMapRes, m_flagNpc);
	COMPARE_OFFSET(CAgitMapRes, m_treasureNpc);
	COMPARE_OFFSET(CAgitMapRes, m_timerQ);
	COMPARE_OFFSET(CAgitMapRes, m_isPKTime);
	COMPARE_OFFSET(CAgitMapRes, m_isDisableSkill);
	COMPARE_OFFSET(CAgitMapRes, m_createCount);
	COMPARE_OFFSET(CAgitMapRes, m_siegeTimeVersion);
	COMPARE_OFFSET(CAgitMapRes, m_empeliumConqueror);
	COMPARE_OFFSET(CAgitMapRes, m_bInstantMapBlockRequest);
	//TODO: vtable
	//CAsyncStream
	COMPARE_SIZE(CAsyncStream);
	COMPARE_OFFSET(CAsyncStream, m_completionKey);
	COMPARE_OFFSET(CAsyncStream, m_socket);
	COMPARE_OFFSET(CAsyncStream, m_sendQueue);
	COMPARE_OFFSET(CAsyncStream, m_recvQueue);
	COMPARE_OFFSET(CAsyncStream, m_csLock);
	COMPARE_OFFSET(CAsyncStream, m_recvOperation);
	COMPARE_OFFSET(CAsyncStream, m_sendOperation);
	COMPARE_OFFSET(CAsyncStream, m_packetHandler);
	COMPARE_OFFSET(CAsyncStream, m_lastError);
	//CAuctionCtrl
	COMPARE_SIZE(CAuctionCtrl);
	COMPARE_OFFSET(CAuctionCtrl, m_ZoneServerID);
	COMPARE_OFFSET(CAuctionCtrl, m_AuctionDB);
	COMPARE_OFFSET(CAuctionCtrl, m_DateTime);
	COMPARE_OFFSET(CAuctionCtrl, m_lastTime);
	COMPARE_OFFSET(CAuctionCtrl, m_EndChkItemType);
	COMPARE_OFFSET(CAuctionCtrl, m_ArmorItem);
	COMPARE_OFFSET(CAuctionCtrl, m_WeaponItem);
	COMPARE_OFFSET(CAuctionCtrl, m_CardItem);
	COMPARE_OFFSET(CAuctionCtrl, m_EtcItem);
	COMPARE_OFFSET(CAuctionCtrl, m_ArmorPool);
	COMPARE_OFFSET(CAuctionCtrl, m_WeaponPool);
	COMPARE_OFFSET(CAuctionCtrl, m_CardPool);
	COMPARE_OFFSET(CAuctionCtrl, m_EtcPool);
	//TODO: vtable
	//CAuctionDB
	COMPARE_SIZE(CAuctionDB);
	//CBattleFieldMapRes
	COMPARE_SIZE(CBattleFieldMapRes);
	COMPARE_OFFSET(CBattleFieldMapRes, m_mapInfo);
	COMPARE_OFFSET(CBattleFieldMapRes, m_stateInfo);
	COMPARE_OFFSET(CBattleFieldMapRes, m_a_aliveMemberList);
	COMPARE_OFFSET(CBattleFieldMapRes, m_b_aliveMemberList);
	COMPARE_OFFSET(CBattleFieldMapRes, m_campNpc);
	COMPARE_OFFSET(CBattleFieldMapRes, m_aliveCheck);
	COMPARE_OFFSET(CBattleFieldMapRes, m_checkNpcNoti);
	COMPARE_OFFSET(CBattleFieldMapRes, m_campCommand);
	//TODO: vtable
	//CBinBuf
	COMPARE_SIZE(CBinBuf);
	COMPARE_OFFSET(CBinBuf, m_buf);
	COMPARE_OFFSET(CBinBuf, m_bufSize);
	//CBuffInfoMgr
	COMPARE_SIZE(CBuffInfoMgr);
	COMPARE_OFFSET(CBuffInfoMgr, m_buffInfoMap);
	COMPARE_OFFSET(CBuffInfoMgr, m_buffInfoNames);
	COMPARE_OFFSET(CBuffInfoMgr, m_binBuf);
	//CCashItemShopDB
	COMPARE_SIZE(CCashItemShopDB);
	//TODO: vtable
	//CCashItemShopScript
//	COMPARE_SIZE(CCashItemShopScript);
	//CCharacter
	COMPARE_SIZE(CCharacter);
	COMPARE_OFFSET(CCharacter, m_characterPInfo);
	COMPARE_OFFSET(CCharacter, m_type);
	COMPARE_OFFSET(CCharacter, m_commandQueue);
	COMPARE_OFFSET(CCharacter, m_neighborCache);
	COMPARE_OFFSET(CCharacter, m_mapRes);
	COMPARE_OFFSET(CCharacter, m_sectionList);
	COMPARE_OFFSET(CCharacter, m_effectiveList);
	COMPARE_OFFSET(CCharacter, m_statusEffInfo);
	COMPARE_OFFSET(CCharacter, m_charBuff2);
	//TODO: vtable
	//CCharacterMgr
	COMPARE_SIZE(CCharacterMgr);
	COMPARE_OFFSET(CCharacterMgr, m_PC);
	COMPARE_OFFSET(CCharacterMgr, m_PCCount);
	COMPARE_OFFSET(CCharacterMgr, m_curPlayChar);
	COMPARE_OFFSET(CCharacterMgr, m_curValidPlayChar);
	COMPARE_OFFSET(CCharacterMgr, m_curDisconnectCountPlayChar);
	COMPARE_OFFSET(CCharacterMgr, m_pcMemoryPool);
	COMPARE_OFFSET(CCharacterMgr, m_itemMemoryPool);
	COMPARE_OFFSET(CCharacterMgr, m_skillMemoryPool);
	COMPARE_OFFSET(CCharacterMgr, m_item);
	COMPARE_OFFSET(CCharacterMgr, m_skill);
	COMPARE_OFFSET(CCharacterMgr, m_npcMap);
	COMPARE_OFFSET(CCharacterMgr, m_AIDPool);
	COMPARE_OFFSET(CCharacterMgr, m_csPC);
	COMPARE_OFFSET(CCharacterMgr, m_pcNonclusteredIndex);
	COMPARE_OFFSET(CCharacterMgr, m_warpNPCList);
	COMPARE_OFFSET(CCharacterMgr, m_bossInMap);
	//CCharBuff
	COMPARE_SIZE(CCharBuff);
	COMPARE_OFFSET(CCharBuff, m_owner);
	COMPARE_OFFSET(CCharBuff, m_status);
	COMPARE_OFFSET(CCharBuff, m_damaged);
	COMPARE_OFFSET(CCharBuff, m_heal);
	COMPARE_OFFSET(CCharBuff, m_aspd);
	COMPARE_OFFSET(CCharBuff, m_immuneMagic);
	VERIFY_VTABLE(CCharBuff, Reset);
	//CCharInfoDB
	COMPARE_SIZE(CCharInfoDB);
	//CCharMTInfo
	COMPARE_SIZE(CCharMTInfo);
	COMPARE_OFFSET(CCharMTInfo, m_attackMTInfo);
	COMPARE_OFFSET(CCharMTInfo, m_attackedMTInfo);
	COMPARE_OFFSET(CCharMTInfo, m_attackMotionTime);
	COMPARE_OFFSET(CCharMTInfo, m_itemClassList);
	//CCheckUseItemList
	COMPARE_SIZE(CCheckUseItemList);
	COMPARE_OFFSET(CCheckUseItemList, m_createItemList);
	//CClient
	COMPARE_SIZE(CClient);
	COMPARE_OFFSET(CClient, m_asyncStream);
	COMPARE_OFFSET(CClient, m_disconnector_cs);
	COMPARE_OFFSET(CClient, m_dwErrorCount);
	COMPARE_OFFSET(CClient, m_nBanTime);
//	VERIFY_VTABLE(CClient, vector_deleting_destructor);
	VERIFY_VTABLE(CClient, GetType);
	VERIFY_VTABLE(CClient, AddErrorCount);
//	VERIFY_VTABLE(CClient, AddErrorCount2);
	VERIFY_VTABLE(CClient, Init);
	//CCompositionLog
	COMPARE_SIZE(CCompositionLog);
	//CConnector
	COMPARE_SIZE(CConnector);
	VERIFY_VTABLE(CConnector, Connect);
	//CCoupleInfoDB
	COMPARE_SIZE(CCoupleInfoDB);
	//CCreatePackageScript
//	COMPARE_SIZE(CCreatePackageScript);
	//CCriticalSection
	COMPARE_SIZE(CCriticalSection);
	COMPARE_OFFSET(CCriticalSection, m_CriticalSection);
	//CCSAuth
	COMPARE_SIZE(CCSAuth);
	COMPARE_OFFSET(CCSAuth, m_dwSeed);
	COMPARE_OFFSET(CCSAuth, m_dwAuthValue);
	COMPARE_OFFSET(CCSAuth, m_bAuth);
	COMPARE_OFFSET(CCSAuth, m_dwCurrIndex);
	COMPARE_OFFSET(CCSAuth, m_table);
	COMPARE_OFFSET(CCSAuth, m_dwClientSequenceNumber);
	COMPARE_OFFSET(CCSAuth, m_dwServerSequenceNumber);
	COMPARE_OFFSET(CCSAuth, m_adwLastSeqs);
	COMPARE_OFFSET(CCSAuth, m_dwPPLastError);
	COMPARE_OFFSET(CCSAuth, m_dwSeq);
	//CCSAuth2
	COMPARE_SIZE(CCSAuth2);
	COMPARE_OFFSET(CCSAuth2, m_pProtocol);
	COMPARE_OFFSET(CCSAuth2, m_bPrtcRef);
	COMPARE_OFFSET(CCSAuth2, m_dwUserFlag);
	COMPARE_OFFSET(CCSAuth2, m_AuthQuery);
	COMPARE_OFFSET(CCSAuth2, m_AuthAnswer);
	//CDatabaseLog
//	COMPARE_SIZE(CDatabaseLog);
	//CDateTime
	COMPARE_SIZE(CDateTime);
	COMPARE_OFFSET(CDateTime, m_time);
	//CDungeonScript
	COMPARE_SIZE(CDungeonScript);
	COMPARE_OFFSET(CDungeonScript, m_map);
	//CDBScriptInfo
	COMPARE_SIZE(CDBScriptInfo);
	COMPARE_OFFSET(CDBScriptInfo, m_map);
	//CDGNpcMgr
	COMPARE_SIZE(CDGNpcMgr);
	COMPARE_OFFSET(CDGNpcMgr, m_map);
	//CErrorLog
	COMPARE_SIZE(CErrorLog);
	COMPARE_OFFSET(CErrorLog, m_csCriticalError);
	//CExpParameter
	COMPARE_SIZE(CExpParameter);
	COMPARE_OFFSET(CExpParameter, m_expValue);
	COMPARE_OFFSET(CExpParameter, m_jobNoviceExpValue);
	COMPARE_OFFSET(CExpParameter, m_jobFirstJobExpValue);
	COMPARE_OFFSET(CExpParameter, m_jobSecondExpValue);
	COMPARE_OFFSET(CExpParameter, m_guildexpValue);
	COMPARE_OFFSET(CExpParameter, m_expValue2);
	COMPARE_OFFSET(CExpParameter, m_jobNoviceExpValue2);
	COMPARE_OFFSET(CExpParameter, m_jobFirstJobExpValue2);
	COMPARE_OFFSET(CExpParameter, m_job_Ninja_Gunner_ExpValue);
	COMPARE_OFFSET(CExpParameter, m_jobSecondExpValue2);
	COMPARE_OFFSET(CExpParameter, m_expVal_Homun);
	//CExtendedODBC
	COMPARE_SIZE(CExtendedODBC);
	//CFamilyInfoDB
	COMPARE_SIZE(CFamilyInfoDB);
	//CFontShopMgr
	COMPARE_SIZE(CFontShopMgr);
	COMPARE_OFFSET(CFontShopMgr, m_bOK);
	COMPARE_OFFSET(CFontShopMgr, m_FontListMap);
	COMPARE_OFFSET(CFontShopMgr, m_Font2ITIDMap);
	//CFSM
	COMPARE_SIZE(CFSM);
	COMPARE_OFFSET(CFSM, m_fsmID);
	COMPARE_OFFSET(CFSM, m_fsmState);
	//CFSMMgr
	COMPARE_SIZE(CFSMMgr);
	COMPARE_OFFSET(CFSMMgr, m_scriptKeyword);
	COMPARE_OFFSET(CFSMMgr, m_fsm);
	//CFSMState
	COMPARE_SIZE(CFSMState);
	COMPARE_OFFSET(CFSMState, m_count);
	COMPARE_OFFSET(CFSMState, m_transition);
	COMPARE_OFFSET(CFSMState, m_table);
	//CFTToken
	COMPARE_SIZE(CFTToken);
	COMPARE_OFFSET(CFTToken, m_Type);
	COMPARE_OFFSET(CFTToken, m_Value);
	COMPARE_OFFSET(CFTToken, m_Line);
	COMPARE_OFFSET(CFTToken, m_Col);
	//CGlobalVarDB
	COMPARE_SIZE(CGlobalVarDB);
	//CGuild
	COMPARE_SIZE(CGuild);
	COMPARE_OFFSET(CGuild, m_GDID);
	COMPARE_OFFSET(CGuild, m_level);
	COMPARE_OFFSET(CGuild, m_guildName);
	COMPARE_OFFSET(CGuild, m_guildMasterName);
	COMPARE_OFFSET(CGuild, m_maxUserNum);
	COMPARE_OFFSET(CGuild, m_userNum);
	COMPARE_OFFSET(CGuild, m_honor);
	COMPARE_OFFSET(CGuild, m_virtue);
	COMPARE_OFFSET(CGuild, m_type);
	COMPARE_OFFSET(CGuild, m_class);
	COMPARE_OFFSET(CGuild, m_money);
	COMPARE_OFFSET(CGuild, m_arenaWin);
	COMPARE_OFFSET(CGuild, m_arenaLose);
	COMPARE_OFFSET(CGuild, m_arenaDrawn);
	COMPARE_OFFSET(CGuild, m_manageLand);
	COMPARE_OFFSET(CGuild, m_exp);
	COMPARE_OFFSET(CGuild, m_emblemVersion);
	COMPARE_OFFSET(CGuild, m_point);
	COMPARE_OFFSET(CGuild, m_desc);
	COMPARE_OFFSET(CGuild, m_isEmblemLoad);
	COMPARE_OFFSET(CGuild, m_emblemSize);
	COMPARE_OFFSET(CGuild, m_guildNotice);
	COMPARE_OFFSET(CGuild, m_guildEmblem);
	COMPARE_OFFSET(CGuild, m_guildMInfo);
	COMPARE_OFFSET(CGuild, m_guildAllyInfo);
	COMPARE_OFFSET(CGuild, m_guildBanishInfo);
	COMPARE_OFFSET(CGuild, m_guildMPosition);
	COMPARE_OFFSET(CGuild, m_GuildMInfoMPool);
	COMPARE_OFFSET(CGuild, m_GuildAllyInfoMPool);
	COMPARE_OFFSET(CGuild, m_GuildBanishInfoMPool);
	COMPARE_OFFSET(CGuild, m_GuildMPositionMPool);
	COMPARE_OFFSET(CGuild, m_skillDataLength);
	COMPARE_OFFSET(CGuild, m_skillPoint);
	COMPARE_OFFSET(CGuild, m_skillData);
	//CGuildDB
	COMPARE_SIZE(CGuildDB);
	COMPARE_OFFSET(CGuildDB, m_getProcTable);
	//CGuildMgr
	COMPARE_SIZE(CGuildMgr);
	COMPARE_OFFSET(CGuildMgr, m_guildInfo);
//	VERIFY_VTABLE(CGuildMgr, vector_deleting_destructor);
	VERIFY_VTABLE(CGuildMgr, Init);
	//CGVar
	COMPARE_SIZE(CGVar);
	COMPARE_OFFSET(CGVar, m_DBColumnSizeBodyItem);
	COMPARE_OFFSET(CGVar, m_DBColumnSizeStoreItem);
	COMPARE_OFFSET(CGVar, m_DBColumnSizeCartItem);
	COMPARE_OFFSET(CGVar, m_valid_client_file_length);
	COMPARE_OFFSET(CGVar, m_character_data_save_interval_minute);
	COMPARE_OFFSET(CGVar, m_AsyncDBThreadNum);
	COMPARE_OFFSET(CGVar, m_bOK);
	//CHomunLog
	COMPARE_SIZE(CHomunLog);
	//CHostPathInfo
	COMPARE_SIZE(CHostPathInfo);
	COMPARE_OFFSET(CHostPathInfo, m_moveInfo);
	//CHuntingList
	COMPARE_SIZE(CHuntingList);
	//CHSvrIO
	COMPARE_SIZE(CHSvrIO);
//	VERIFY_VTABLE(CHSvrIO, scalar_deleting_destructor);
//	VERIFY_VTABLE(CHSvrIO, OnProcess);
//	VERIFY_VTABLE(CHSvrIO, OnCustomInit);
	//CHSvrIOPacketHandler
	COMPARE_SIZE(CHSvrIOPacketHandler);
	//CImportantItem
	COMPARE_SIZE(CImportantItem);
	COMPARE_OFFSET(CImportantItem, m_mapImportantItem);
	//CIMWTWork
	COMPARE_SIZE(CIMWTWork);
	COMPARE_OFFSET(CIMWTWork, m_Type);
	//CIMWTWork_LoadMap
	COMPARE_SIZE(CIMWTWork_LoadMap);
	COMPARE_OFFSET(CIMWTWork_LoadMap, m_cpInstantMapRes);
	COMPARE_OFFSET(CIMWTWork_LoadMap, m_bOK);
	COMPARE_OFFSET(CIMWTWork_LoadMap, m_MapName);
	COMPARE_OFFSET(CIMWTWork_LoadMap, m_MapID);
	COMPARE_OFFSET(CIMWTWork_LoadMap, m_MapType);
	COMPARE_OFFSET(CIMWTWork_LoadMap, m_Result);
	//CInstantMapMgr
	COMPARE_SIZE(CInstantMapMgr);
	COMPARE_OFFSET(CInstantMapMgr, m_InstantMapCtrlContainer);
	COMPARE_OFFSET(CInstantMapMgr, m_bOK);
	//CInstantMapRes
	COMPARE_SIZE(CInstantMapRes);
	COMPARE_OFFSET(CInstantMapRes, m_bOK);
	VERIFY_VTABLE(CInstantMapRes, isInstantMap);
//	VERIFY_VTABLE(CInstantMapRes, scalar_deleting_destructor);
//	VERIFY_VTABLE(CInstantMapRes, Load);
//	VERIFY_VTABLE(CInstantMapRes, Reset);
//	VERIFY_VTABLE(CInstantMapRes, OnTimer);
//	VERIFY_VTABLE(CInstantMapRes, GetGDID);
//	VERIFY_VTABLE(CInstantMapRes, AddCharacter);
//	VERIFY_VTABLE(CInstantMapRes, GetLoadFileName);
//	VERIFY_VTABLE(CInstantMapRes, IsBattleField);
//	VERIFY_VTABLE(CInstantMapRes, IsAgit);
	//CInterpreter
	COMPARE_SIZE(CInterpreter);
	COMPARE_OFFSET(CInterpreter, m_varMap);
	COMPARE_OFFSET(CInterpreter, m_tokenDataStack);
	COMPARE_OFFSET(CInterpreter, m_handler);
	COMPARE_OFFSET(CInterpreter, m_bin);
	COMPARE_OFFSET(CInterpreter, m_pos);
	COMPARE_OFFSET(CInterpreter, m_size);
	COMPARE_OFFSET(CInterpreter, m_scan);
	COMPARE_OFFSET(CInterpreter, m_gotoLock);
	VERIFY_VTABLE(CInterpreter, CodeFunc);
	VERIFY_VTABLE(CInterpreter, CodeMov);
	VERIFY_VTABLE(CInterpreter, CodeAdd);
	VERIFY_VTABLE(CInterpreter, CodeSub);
	VERIFY_VTABLE(CInterpreter, CodeMul);
	VERIFY_VTABLE(CInterpreter, CodeDiv);
	VERIFY_VTABLE(CInterpreter, CodeMod);
	VERIFY_VTABLE(CInterpreter, CodeInc);
	VERIFY_VTABLE(CInterpreter, CodeDec);
	VERIFY_VTABLE(CInterpreter, CodeCmp);
	VERIFY_VTABLE(CInterpreter, CodeGoto);
	VERIFY_VTABLE(CInterpreter, CodePush);
	VERIFY_VTABLE(CInterpreter, CodePop);
	VERIFY_VTABLE(CInterpreter, CodeCase);
	//CInterpretHandler
	COMPARE_SIZE(CInterpretHandler);
	COMPARE_OFFSET(CInterpretHandler, m_varMap);
	//CInventory
	COMPARE_SIZE(CInventory);
	//CInventoryItemFactory
	COMPARE_SIZE(CInventoryItemFactory);
	//CISvrIO
	COMPARE_SIZE(CISvrIO);
	COMPARE_OFFSET(CISvrIO, m_PingTimer);
//	VERIFY_VTABLE(CISvrIO, scalar_deleting_destructor);
//	VERIFY_VTABLE(CISvrIO, OnProcess);
//	VERIFY_VTABLE(CISvrIO, OnCustomInit);
	//CISvrIOPacketHandler
	COMPARE_SIZE(CISvrIOPacketHandler);
	COMPARE_OFFSET(CISvrIOPacketHandler, m_OldHeader);
	COMPARE_OFFSET(CISvrIOPacketHandler, m_OldPacketSize);
	COMPARE_OFFSET(CISvrIOPacketHandler, m_PacketBuffer);
	//TODO: vtable
	//CItem
	COMPARE_SIZE(CItem);
	//CItemList
	COMPARE_SIZE(CItemList);
	//CItemLog
	COMPARE_SIZE(CItemLog);
	//CItemPackageScript
//	COMPARE_SIZE(CItemPackageScript);
	//CItemReuseLimit
	COMPARE_SIZE(CItemReuseLimit);
	//CITP
	COMPARE_SIZE(CITP);
	//CITPMgr
	COMPARE_SIZE(CITPMgr);
	//CIVItItemFactory
	COMPARE_SIZE(CIVItItemFactory);
	//CJobCodeForItem
	COMPARE_SIZE(CJobCodeForItem);
	//CLoadDGScriptList
	COMPARE_SIZE(CLoadDGScriptList);
	COMPARE_OFFSET(CLoadDGScriptList, m_buff);
	COMPARE_OFFSET(CLoadDGScriptList, m_tSize);
	COMPARE_OFFSET(CLoadDGScriptList, m_list);
	//CLogRecorder
	COMPARE_SIZE(CLogRecorder);
	//CLottoDB
	COMPARE_SIZE(CLottoDB);
	//CMakerRankDB
	COMPARE_SIZE(CMakerRankDB);
	//CMakingLog
	COMPARE_SIZE(CMakingLog);
	//CMapInfo
	COMPARE_SIZE(CMapInfo);
	//CMapPropertyCountPK
	COMPARE_SIZE(CMapPropertyCountPK);
	//CMapRes
	COMPARE_SIZE(CMapRes);
	//CMapResMgr
	COMPARE_SIZE(CMapResMgr);
	//CMapTypeProperty
	COMPARE_SIZE(CMapTypeProperty);
	//CMapTypePropertyMgr
	COMPARE_SIZE(CMapTypePropertyMgr);
	//CMatchTable
	COMPARE_SIZE(CMatchTable);
	//CMaxHpSp
	COMPARE_SIZE(CMaxHpSp);
	//CMemorialDungeon
	COMPARE_SIZE(CMemorialDungeon);
	//CMemorialDungeonMgr
	COMPARE_SIZE(CMemorialDungeonMgr);
	//CMemoryMgr
//	COMPARE_SIZE(CMemoryMgr);
	//CMerceDB
	COMPARE_SIZE(CMerceDB);
	//CMercenaryConfiguration
	COMPARE_SIZE(CMercenaryConfiguration);
	//CMercenaryDBV2
	COMPARE_SIZE(CMercenaryDBV2);
	//CMercenaryLog
	COMPARE_SIZE(CMercenaryLog);
	//CMercenarySkillMgr
	COMPARE_SIZE(CMercenarySkillMgr);
	//CMEventDB
	COMPARE_SIZE(CMEventDB);
	//CMobileEvent
	COMPARE_SIZE(CMobileEvent);
	//CMonParameterMgr
	COMPARE_SIZE(CMonParameterMgr);
	//CMonsterParameterTable
	COMPARE_SIZE(CMonsterParameterTable);
	//CMsg
	COMPARE_SIZE(CMsg);
	//CMVPInfo
	COMPARE_SIZE(CMVPInfo);
	//CMyMiniDumpUnhandledExceptionHandler
	COMPARE_SIZE(CMyMiniDumpUnhandledExceptionHandler);
	//CNeighborCache
	COMPARE_SIZE(CNeighborCache);
	//CNPC
	COMPARE_SIZE(CNPC);
	//CNpc
	COMPARE_SIZE(CNpc);
	//CNPCAddSkillInfo
	COMPARE_SIZE(CNPCAddSkillInfo);
	//CNpcEvent
	COMPARE_SIZE(CNpcEvent);
	//CNpcHomun
	COMPARE_SIZE(CNpcHomun);
	//CNpcMgr
	COMPARE_SIZE(CNpcMgr);
	//CNpcMob
	COMPARE_SIZE(CNpcMob);
	//CNpcPet
	COMPARE_SIZE(CNpcPet);
	//CNPCSkill
	COMPARE_SIZE(CNPCSkill);
	//CNPCStateUpdater
	COMPARE_SIZE(CNPCStateUpdater);
	//CNpcSvr
	COMPARE_SIZE(CNpcSvr);
	//CNPCUpdater
	COMPARE_SIZE(CNPCUpdater);
	//CODBC
	COMPARE_SIZE(CODBC);
	//CODBCV2
	COMPARE_SIZE(CODBCV2);
	//CODBCV2Connector
	COMPARE_SIZE(CODBCV2Connector);
	//CPacketHandler
	COMPARE_SIZE(CPacketHandler);
	//CPacketQueue
	COMPARE_SIZE(CPacketQueue);
	//CPath
	COMPARE_SIZE(CPath);
	//CPathData
	COMPARE_SIZE(CPathData);
	//CPathFinder
	COMPARE_SIZE(CPathFinder);
	//CPathInfo
	COMPARE_SIZE(CPathInfo);
	//CPC
	COMPARE_SIZE(CPC);
	//CPCBattle
	COMPARE_SIZE(CPCBattle);
	//CPCBattleMercenary
	COMPARE_SIZE(CPCBattleMercenary);
	//CPCCartItemIV
	COMPARE_SIZE(CPCCartItemIV);
	//CPCClientUpdater
	COMPARE_SIZE(CPCClientUpdater);
	//CPCHireItemCtrl
	COMPARE_SIZE(CPCHireItemCtrl);
	//CPCHuntIndex
	COMPARE_SIZE(CPCHuntIndex);
	//CPCItem
	COMPARE_SIZE(CPCItem);
	//CPCItemInventory
	COMPARE_SIZE(CPCItemInventory);
	//CPCItemInventoryMgr
	COMPARE_SIZE(CPCItemInventoryMgr);
	//CPCMCStoreItemIV
	COMPARE_SIZE(CPCMCStoreItemIV);
	//CPCPacketHandler
	COMPARE_SIZE(CPCPacketHandler);
	//CPCProperty
	COMPARE_SIZE(CPCProperty);
	//CPCQuestEvent
	COMPARE_SIZE(CPCQuestEvent);
	//CPCSkill
	COMPARE_SIZE(CPCSkill);
	//CPCSkillDB
	COMPARE_SIZE(CPCSkillDB);
	//CPetDB
	COMPARE_SIZE(CPetDB);
	//CPetDefaultValue
	COMPARE_SIZE(CPetDefaultValue);
	//CPetLog
	COMPARE_SIZE(CPetLog);
	//CPEventDB
	COMPARE_SIZE(CPEventDB);
	//CPKInfoMgr
	COMPARE_SIZE(CPKInfoMgr);
	//CPollTimer
	COMPARE_SIZE(CPollTimer);
	//CPresentLog
	COMPARE_SIZE(CPresentLog);
	//CPriorityQueue
	COMPARE_SIZE(CPriorityQueue);
	//CPubScheduler
	COMPARE_SIZE(CPubScheduler);
	//CPubSchedulerJob
	COMPARE_SIZE(CPubSchedulerJob);
	//CPvPScoreDB
	COMPARE_SIZE(CPvPScoreDB);
	//CQuestEventMgr
	COMPARE_SIZE(CQuestEventMgr);
	//CQuestTFile
	COMPARE_SIZE(CQuestTFile);
	//CQVar
	COMPARE_SIZE(CQVar);
	//CRefiningLog
	COMPARE_SIZE(CRefiningLog);
	//CRoom
	COMPARE_SIZE(CRoom);
	//CRoomMgr
	COMPARE_SIZE(CRoomMgr);
	//CScriptCompiler
	COMPARE_SIZE(CScriptCompiler);
	//CScriptEventHandler
	COMPARE_SIZE(CScriptEventHandler);
	//CScriptEventMgr
	COMPARE_SIZE(CScriptEventMgr);
	//CSectionMgr
	COMPARE_SIZE(CSectionMgr);
	//CServerInfo
	COMPARE_SIZE(CServerInfo);
	//CSkill
	COMPARE_SIZE(CSkill);
	//CSkillLog
	COMPARE_SIZE(CSkillLog);
	//CSkillTypeBaseInfo
	COMPARE_SIZE(CSkillTypeBaseInfo);
	//CSkillTypeInfoMgr
	COMPARE_SIZE(CSkillTypeInfoMgr);
	//CSpecialItemMgr
	COMPARE_SIZE(CSpecialItemMgr);
	//CStatpointPerLevel
	COMPARE_SIZE(CStatpointPerLevel);
	//CStatusLog
	COMPARE_SIZE(CStatusLog);
	//CStatusPlusInfoByJLV
	COMPARE_SIZE(CStatusPlusInfoByJLV);
	//CStorePasswordDB
	COMPARE_SIZE(CStorePasswordDB);
	//CSummonItemTable
	COMPARE_SIZE(CSummonItemTable);
	//CSummonMobBySkillTable
	COMPARE_SIZE(CSummonMobBySkillTable);
	//CSummonMonsterTable
	COMPARE_SIZE(CSummonMonsterTable);
	//CSvrIO
	COMPARE_SIZE(CSvrIO);
	//CTimeList
	COMPARE_SIZE(CTimeList);
	//CUIDGenerator
	COMPARE_SIZE(CUIDGenerator);
	//CZGuildInfo
	COMPARE_SIZE(CZGuildInfo);
	//CZGuildInfoPacketDispatcher
	COMPARE_SIZE(CZGuildInfoPacketDispatcher);
	//CZGuildMgr
	COMPARE_SIZE(CZGuildMgr);
	//CZoneScript
	COMPARE_SIZE(CZoneScript);
	//CZSAcceptHandler
	COMPARE_SIZE(CZSAcceptHandler);
	//enum
	//globals
	//MannerPointInfo
	COMPARE_SIZE(MannerPointInfo);
	//MSGpar
	//N2FTAToken
	COMPARE_SIZE(N2FTAToken);
	COMPARE_OFFSET(N2FTAToken, m_Type);
	COMPARE_OFFSET(N2FTAToken, m_Value);
	COMPARE_OFFSET(N2FTAToken, m_SourceFileLine);
	COMPARE_OFFSET(N2FTAToken, m_SourceFileCol);
	COMPARE_OFFSET(N2FTAToken, m_SourceFileName);
	//N2FTAVar
	COMPARE_SIZE(N2FTAVar);
	COMPARE_OFFSET(N2FTAVar, m_Type);
	COMPARE_OFFSET(N2FTAVar, m_strData);
	COMPARE_OFFSET(N2FTAVar, m_intData);
	COMPARE_OFFSET(N2FTAVar, m_floatData);
	//N2SystemMgr
	COMPARE_SIZE(N2SystemMgr);
	//NAsyncDBMgr
	COMPARE_SIZE(NAsyncDBMgr);
	//NAsyncDBThread
	COMPARE_SIZE(NAsyncDBThread);
	//NInter
	COMPARE_SIZE(NInter);
	//NInterMessageQueue
	COMPARE_SIZE(NInterMessageQueue);
	//NObject
	COMPARE_SIZE(NObject);
	//NSystemMgr
	COMPARE_SIZE(NSystemMgr);
	//NThread
	COMPARE_SIZE(NThread);
	//packet
	//struct
	COMPARE_SIZE(GUILDMINFO);
	COMPARE_OFFSET(GUILDMINFO, GID);
	COMPARE_OFFSET(GUILDMINFO, CharName);
	COMPARE_OFFSET(GUILDMINFO, AccountName);
	COMPARE_OFFSET(GUILDMINFO, Level);
	COMPARE_OFFSET(GUILDMINFO, Memo);
	COMPARE_OFFSET(GUILDMINFO, Service);
	COMPARE_OFFSET(GUILDMINFO, MemberExp);
	COMPARE_OFFSET(GUILDMINFO, GDID);
	COMPARE_OFFSET(GUILDMINFO, AID);
	COMPARE_OFFSET(GUILDMINFO, PositionID);
	COMPARE_OFFSET(GUILDMINFO, head);
	COMPARE_OFFSET(GUILDMINFO, headPalette);
	COMPARE_OFFSET(GUILDMINFO, sex);
	COMPARE_OFFSET(GUILDMINFO, job);
	COMPARE_OFFSET(GUILDMINFO, status);
};
