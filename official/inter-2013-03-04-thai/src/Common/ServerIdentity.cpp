#include "Common/ServerIdentity.h"


namespace {


void ServerIdentityNation(void (* output)(const char in_pStr[]))
{
	output("_THAI_VER");
}

void ServerIdentity_Account(void (* output)(const char in_pStr[]))
{
	output("[account server identity start]");
	output("__READ_SERVER_PORT_GLOBALINFO_DB\t// [2012/07/18, kimig82] Global DB에서 어카운트 서버 Port 정보를 읽어온다.");
	output("[account server identity end]");
};


void ServerIdentity_Character(void (* output)(const char in_pStr[]))
{
	output("[character server identity start]");
	output("__HSVR_READ_SERVERINFOTBL_PRIVATECOLUMN //[10/27/2012] 서버인포테이블의 PrivateXXXX 값을 읽어서 리슨아이피와포트를 설정한다-blreo");
	output("[character server identity end]");
}


} // namespace


void ServerIdentity(void (* output)(const char in_pStr[]))
{
	char temp[1024] = {};
	_snprintf_s(temp, countof(temp), _TRUNCATE, "Ep%d.%d.%d", 14, 2, 1);
	output(temp);

	ServerIdentityNation(output);
	ServerIdentity_Account(output);
	ServerIdentity_Character(output);

	output("__GM_WHISPER_FORCE");
	output("__BROADCASTING_SPECIAL_ITEM_OBTAIN");
	output("__BROADCASTING_SPECIAL_ITEM_OBTAIN_R2");
	output("__DEFINE_CHECK");
	output("_PROTECTION");
	output("__MCSTORE_UNIQUEID");
	output("__AUTOMATIC_USER_BLOCK");
	output("__PARTY_EXP_SHARE_LEVEL_DIFF_15");
	output("__ASPD_THIRD_MODIFY");
	output("__ELEMENTAL");
	output("__HANDCAPSTATE_FORMULA_REV100412");
	output("_BUYING_STORE");
	output("__BABY_STAT_REWIND");
	output("__MONPARAMETER_ATTR_MVP");
	output("__THIRDJOB1");
	output("__VARIABLE_CHARSLOT");
	output("__MODIFY_DEF_RENEWAL_FORMULA");
	output("RENEWAL_PACKAGEITEM");
	output("__SERVER_RANDOM_R2");
	output("__SHADOWCHASER_BALANCE0415");
	output("__GENETIC_BALANCE0507");
	output("__MODIFY_FINAL_ATKPOWER_FORMULA");
	output("__PACKETLENGHTEX_MGR");
	output("__NEO_INSURANCE_ITEM");
	output("__UNPACK_PACKAGEITEM_V3");
	output("__RIDING_SYSTEM");
	output("__ZERO_STEAL");
	output("__REFACTORING_FUNC_SPLASHATTACK2 // 함수 CPC :: SplashAttack2() 를 리팩토링한다.");
	output("__SUMMON_R2 // [10/18/2010] 아이템(고목나무가지,피묻은나무가지,포링상자)으로 소환하는 몬스터의 위치를 자신의 위치에서 1셀내의 이동가능지역으로 한정한다.");
	output("__SE_SIMPLE_CASH_SHOP_ // [10/25/2010] 간편캐쉬샆2 파일추가: SimpleCashShopScript.lua");
	output("__FACTORVAR_PASSIVE_SKILL_HPSP_RECOVERY // [10/22/2010] 패시브스킬 HP회복력향상과 SP회복력향상을 factorVar 형태로 변경합니다.");
	output("__MDEF_EXTRA_FLOAT_USE // [10/22/2010] 아이템마법방어에 대한 percent 증가가 INT형으로 되어 있어서 수치가 제대로 적용되지 않코 있었다.(연인들을 위한 심포니)");
	output("__FIN_SKILL_BALANCE_ARCHBISHOP // [10/27/2010] 아크비숍 스킬 밸런스 최종");
	output("__FIN_SKILL_BALANCE_WARLOCK // [11/01/2010] 워록 스킬 밸런스 최종 + skillspecial.sc ");
	output("__FIN_SKILL_BALANCE_GUILLOTINE_CROSS // [11/09/2010] 길로틴크로스 밸런스 최종 + skillspecial.sc");
	output("_COSTUME_ITEM // [6/28/2010]");
	output("__2D_LAYER // [11/11/2010] 2D Layer 작업");
	output("__SE_SIMPLE_CASH_SHOP_  //[10/25/2010] 간편캐쉬샆2 파일추가: SimpleCashShopScript.lua");
	output("__BOSS_TOMB_SYSTEM //[11/4/2010] 보스무덤 시스템");
	output("__PACKET_REFACTORING_SIMPLE //[11/17/2010] 페켓구조체에 존재하는 복잡한 디파인 지정자들을 제거한다.");
	output("__REFACTORING_AID_REMOVE //[12/21/2010] AID를 이용하여 접속한 케릭터로 이동하는 명령어 수정");
	output("__SUPERNOVICE_EXPANSION //[12/1/2010]슈퍼노비스확장 직업");
	output("__ENABLE_PERSONAL_PREMIUM_SERVICE[1/27/2011] 기존 PACKET_HZ_NOTIFY_PCBANG -> PACKET_HZ_PERSONAL_INFORMATION 변경");
	output("__CHANGE_EXP_TYPE_IN_PREMIUM_SVC [2011/02/25, kimig82] 프리미엄 서비스 안에 경험치 타입형을 Int형으로 바꾼다.");
	output("__RECYLE_NPC_AID_FOR_PUTMOB // [2/15/2011] PUTMOB으로 배치되는 몹및NPC들은 MAX_AID_COUNT(50000) < AID < PC_MINIMUM_ACCOUNTID(100000) 범위여야 한다. 모자라서 재사용해야 한다.");
	output("ENABLE_MONSTER_TRANSFORM // [1/27/2011] 몬스터 변신");
	output("__MONPARAMETER_R2_LONG_RNG_PHYSICAL_ATK // [11/20/2010] 몬스터파라미터의 Attr 값 ATTRMASK_MUST_DAMAGE_ONE_RNGATK 의 의미를 수정한다. 원거리-> 원거리물리공격으로");
	output("__MONPARAMETER_R3_SKILLPATT_NONE // [1/3/2011] 몬스터 Attr속성에 스킬패턴 SKILLPATT_NONE인경우 무조건 1의 데미지만 받도록하는 속성을 추가합니다.");
	output("ENABLE_MULTI_ZONE_SERVER[12/21/2010] 1머신에 존서버 다중 실행");
	output("__FIN_SKILL_BALANCE_SORCERER //[3/18/2011] 소서러 최종 스킬 밸런스");
	output("__ADD_CARDITEM_COMPOSITIONTYPE2 //[6/30/2010]카드 조합type2(모든장비에착용) 추가");
	output("__PARTY_SHARE_EXPJOBEXP_MODIFY20110329 // [3/29/2011] 파티원수에 따른 EXP및 JOBEXP 보상 수정");
	output("__BUGFIX_RAG_1826_TRADE // [4/8/2011] 브라질 트레이드 버그를 이용한 교환창 사기");
	output("__ASYNC_DB_WORK_REMAINDER\t\t\t//[3/30/2011] character DB 중 아직 async로 변환 안된 것들 처리함");
	output("__UNHANDLEEXCEPTION_ADD_ZSVRLOG // [5/30/2011] 스택로그에 존서버디버깅에 필요한 로그를 추가로 남긴다.");
	output("__REFACTORING_ZSVR_OUTPUT // [5/30/2011] 존서버 화면출력부분을 리팩토링한다.");
	output("__ZSVR_PROCESSMGR // [5/31/2011] 존서버의 메인쓰레드에서 작업쓰레드를 분리한다");
	output("__REFACTORING_SP_AMOUNT\t// [6/10/2011] SP관리를 클래스로 변경한다.");
	output("__SB_MO_EXTREMITYFIST // [6/14/2011] 아수라패황권");
	output("_SEARCH_STORE_INFO\t// 노점 검색 [8/17/2010 sadlyfox]");
	output("__AUTH_TIMEOUT // [2011/08/03] 인터서버와 연결시 인증 제한 시간을 설정하여 초과하면 끊어버리고 재연결한다.");
	output("__AUTH_FLAG_OUTPUT // [2011/08/08] 캐릭터, 인터서버와의 인증 상태를 화면에 출력");
	output("__FIN_3RD_SKILL_BALANCE //[4/7/2011] 3차직업군 최종스킬밸런스 패치");
	output("__HOMUN_MUTATION //[6/16/2010] __BUGFIX_HOMUN_FULLNESS 디파인이 정의되어 있어야함.(게임 오브젝트들/호문(Homun)/호문변이관련문서/호문변이 업데이트 관련.txt)");
	output("__BUG_FIX_0005744_TRADE // [8/23/2011] 구매노점,판매노점 양쪽을 이용한 사기거래 - blreo");
	output("__N3SYSTEM // [8/30/2011] N3시스템을 구성합니다.-blreo");
	output("__REFACTORING_QFILE // CQFile 클래스를 리팩토링 한다. -blreo");
	output("__ACCEPT_ASYNC_ZSVR // [9/5/2011] 존서버 어셉트쓰레들와 프로세스스레드간 비동기 메세지 방식으로 처리한다.-blreo");
	output("__REFACTORING_TRACELOG // [8/26/2011] 트레이스 파일로그 출력부분 수정-blreo");
	output("__BUGFIX_GETWARPINFO //[09/28/2011] 어콜라이트 어프포털 /memo(기억)시 마지막에 위치가 저장이 안되는 현상수정 - jkcha");
	output("                     //프로시져 수정 파일 존재(프로시져명:usp_GetWarpInfo)");
	output("__ITEMDB_USABLE_LEVEL_RANGE // [6/22/2010] DB에 아이템을 사용/장착 가능한 최소레벨, 최대레벨을 추가함, 디비테이블 수정 및 프로시저 추가작업이 필요함!");
	output("__SETAUTOSPELL_ATKED_V2 // [10/06/2009] 일본요청, 아이템 명령어 분리, SetAutoSpell_MLEATKED -> SetAutoSpell_MLEATKED_V2 + SetAutoSpell_RANGEATKED_V2");
	output("__ADD_ITEM_SCRIPT_FUNC_SHOWSCRIPT\t//[1/4/2011] 아이템에서 대사를 보여준다");
	output("__BUG_FIX_0006715_AUTOSPELL // [10/21/2011] 플레임로드링(공링) 아이템을 두개 착용 후 타격 시 오른쪽의 공링을 탈착했을 때, 오토스펠 발동되지 않는현상-blreo");
	output("                            // 주의) 패치시에는 special.sc 파일내용 대부분을 수정해야 합니다.");
	output("                            // 주의) buffspecial.sc 파일내용 대부분을 수정해야 합니다.");
	output("__CHECK_IS_SAME_MAP\t\t\t\t\t//[12/09/2011]   공격시 동일맵인지 체크한다. - jkcha");
	output("__REFACTORING_MAKE_COOK\t\t\t\t//[01/06/2012] 요리 관련 부분 리펙토링 mkCook.txt --> mkCook.Lua 파일로 변경 - jkcha");
	output("__REFACTORING_CHANGECART\t\t\t\t\t//[01/17/2011] 카트 레벨별 타입을 추가한다. 기존 EFFECTSTATE_형을 EFST_형 으로 변경한다.-jkcha");
	output("__ENTRY_QUEUE // [2011/09/29] 입장대기열(퀘스트, 전장등 인터페이스를 통해서 자유롭게 신청이 가능하다.) - minieyo80");
	output("ENABLE_PARTY_PROPERTY\t// [/2/10/2011] 파티 관련 맵속성 추가(결성, 가입, 탈퇴, 추방을 선택해서 금지시킬수 있습니다.)");
	output("__CHANGE_PARTY_MASTER_SAME_MAP // [2/29/2012] 동일 맵에서만 파티장을 변경할 수 있다. - minieyo80");
	output("__ISVR_MULTIZSVR_ACCEPTTHREAD_MULTIPLEXING // [3/19/2012] 멀티존시 AcceptThread 의 인증시 멀티플렉싱(multiplexing)방식으로 변경한다-blreo");
	output("__MC_CARTDECORATE // [4/26/2012] 카트꾸미기(MC_CARTDECORATE)스킬(skillspecial.sc)");
	output("ADD_SCRIPT_FUNC_FOR_MERGING_ITEM\t//[02/07/2012]  아이템(시리얼이 있는 일반아이템)을 합쳐주는 스크립트 함수");
	output("__GR_MONSTER_TRANSFORM //[6/4/2012] 몬스터변신 그룹디파인정리-blreo");
	output("__INCREASE_MAX_CNT_MEMORIAL_DUNGEON\t\t// [2011/10/25, kimig82] 메모리얼 던전 생성 최대 개수를 증가 시킨다.(36진법 이용) (존, 인터 모두 빌드)");
	output("__MEMORIAL_DUNGEON_REMOVE_MANAGEMENT_CMD // [6/26/2012] 메모리얼던젼 관리자모드 명령어제거-blreo");
	output("__REFACTORING_MEMORYMGR2ND //[7/3/2012] 메모리관리자에서 stl을 완전히 제거해보자-blreo");
	output("__REFACTORING_INVENTORY_ITEM_OBJECT //[7/19/2012] 인벤토리 아이템관련 객체들을 정리한다-blreo");
	output("__ITEMDBFMT_BUFFER //[7/20/2012] 아이템정보를 바이너리로 변경하여 저장할때 버퍼를 클래스화한다.-blreo");
	output("__ITEMDBFMT_READBUFFERADDAPTER //[7/21/2012] 아이템바이너리 정보 파싱시 취약점보강을 위한 관리자 클래스 도입-blreo");
	output("__TAIWAN_MLEAK //[7/25/2012] vtbl 문제확인을위한 코드-blreo");
	output("__TAIWAN_MLEAK_SHIELD //[7/25/2012] vtbl문제 발생시 객체를 버리고( 삭제하면않됨) 새로 할당-blreo");
	output("__REFACTORING_CLASS_CMAPINFO //[7/30/2012] 맵인포 클래스를 리팩토링합니다.-blreo");
	output("__GR_BUGFIX_1ST //[8/8/2012] 스킬밸런스이후적용된 수정버그적용 -blreo");
	output("__BUG_FIX_0012564_NPC_TALK   // [2012,07,03,jkcha] NPC 대화지문 발생후 강제 이동시 클라이언트 종료 현상");
	output("__EFFECTSTATE_SPECIALHIDING_TO_COMPLEMENT\t\t//[2012/05/18] 일반 유저의  스페셜 하이딩의 시간이 안풀리는 버그가 있어 보완 한다 - jkcha");
	output("__BUG_FIX_0013172_EFFECTSTATE_TIME //[8/21/2012] 이펙트스테이트(EFFECTSTATE_SPECIALHIDING...)의 시간정보가 잘못저장되는 문제 수정-blreo");
	output("__GR_MEMORIAL_DUNGEON_EX //[9/17/2012] 메모리얼던젼 확장작업을 그룹디파인으로 정리합니다.-blreo");
	output("__BUG_FIX_0011778_EVENT_ACTIVEARMOR //[2012/05/18,jkcha] : 호드렘린 카드의 옵션 중 물리/마법 데미지를 입었을때, 완전회피+30 옵션이 중첩되는 현상");
	output("__AHNLAB_HACKSHIELD_R5671_BUILD237 //[10/1/2012,jkcha]안랩핵쉴드 SDK 버젼[R.5.6.7.1(build237)]\t");
	output("__BUF_FIX_0013693_COMBIITEM\t//[10/09/2012,jkcha] 0013693: 콤비아이템 착용중 같은 무기의 아이템을 착용할 경우 생기는 문제");
	output("__REFACTORING_FUNC_LOADENUM // [11/2/2012, minieyo80] enum_V2.sc 로딩하는 부분을 리팩토링한다.");
	output("__GR_SIMPLE_CASHSHOP_SE //[2012-11-15] 심플캐쉬샵 그룹디파인 - hwpark");
}
