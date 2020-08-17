#include "CDGNpcMgr.hpp"
#include "CLoadDGScriptList.hpp"
#include "Path.h"
#include "ScriptCompiler.h"
#include "ScriptDefine.h"
#include "shared.h" // Trace
#include "globals.hpp"
////////////////////////////////////////


hook_func<const char* (__cdecl *)(SCRIPT_FILE_TYPE file)> _GetScriptFileName(SERVER, "GetScriptFileName");
const char* __cdecl GetScriptFileName(SCRIPT_FILE_TYPE file) // line 475
{
	return (_GetScriptFileName)(file);

	switch( file )
	{
	case DEF_ITEM        : return ".\\scriptdata\\itp.def";
	case DEF_MOBNAME     : return ".\\scriptdata\\mobname.def";
	case DEF_NPCSPR      : return ".\\scriptdata\\npcspr.def";
	case DEF_SKILL       : return ".\\scriptdata\\skill.def";
	case BIN_COMMON      : return ".\\scriptbin\\common.bin";
	case BIN_ITEM        : return ".\\scriptbin\\item.bin";
	case BIN_NPC         : return ".\\scriptbin\\npc.bin";
	case BIN_SKILL       : return ".\\scriptbin\\skill.bin";
	case BIN_BUFF        : return ".\\scriptbin\\buff.bin";
	case ASM_COMMON      : return ".\\scriptbin\\common.asm";
	case ASM_ITEM        : return ".\\scriptbin\\item.asm";
	case ASM_NPC         : return ".\\scriptbin\\npc.asm";
	case ASM_SKILL       : return ".\\scriptbin\\skill.asm";
	case ASM_BUFF        : return ".\\scriptbin\\buff.asm";
	case SC_ENUM_V2      : return g_pathData->CPathData::SetFileName(".\\scriptdata\\enum_v2.sc");
	case SC_STD_V2       : return g_pathData->CPathData::SetFileName(".\\scriptdata\\std_v2.sc");
	case SC_ITEM_SPECIAL : return g_pathData->CPathData::SetFileName(".\\itemdata\\special.sc");
	case SC_NPC_MOBDEF   : return g_pathData->CPathData::SetFileName(".\\scriptdata\\mobdef.sc");
	case SC_SKILL_SPECIAL: return g_pathData->CPathData::SetFileName("SkillSpecial.sc");
	case SC_BUFF_SPECIAL : return g_pathData->CPathData::SetFileName("BuffSpecial.sc");
	case NPC_LIST        : return g_pathDataNpc->CPathData::SetFileName(".\\npcdata\\list.txt");
	case DUNGEON_NPC_LIST: return g_pathDataNpc->CPathData::SetFileName(".\\npcdata\\dungeonList.txt");
	case HIS_NPC_LIST    : return ".\\npcScript_history.txt";
	default              : return "";
	}
}


hook_func<void (__cdecl *)(const char* str)> _CompileError(SERVER, "CompileError");
void __cdecl CompileError(const char* str) // line 519
{
	return (_CompileError)(str);

	MessageBoxA(NULL, str, "SCRIPT COMPILER ERROR", MB_OK);
}


////////////////////////////////////////


CScriptCompiler::CScriptCompiler(void) // line ??
{
	m_compiler = NULL;
}


CScriptCompiler::~CScriptCompiler(void) // line 20
{
	this->CScriptCompiler::Reset();
}


hook_method<bool (CScriptCompiler::*)(void)> CScriptCompiler::_Init(SERVER, "CScriptCompiler::Init");
bool CScriptCompiler::Init(void) // line 24
{
	return (this->*_Init)();

	m_compiler = new CCompiler();
	if( m_compiler == NULL )
	{
		MessageBoxA(NULL, "CCompiler Alloc Fail", "Script Compiler Error", MB_OK);
		return false;
	}

	m_compiler->CCompiler::SetGlobalErrorFunc(CompileError);

	mkdir(".\\scriptbin");
	mkdir(".\\scriptdata");

	if( !this->CScriptCompiler::InitTokenMap()
	||  !this->CScriptCompiler::InitItemScript()
	||  !this->CScriptCompiler::InitNpcScript()
	||  !this->CScriptCompiler::InitSkillScript()
	||  !this->CScriptCompiler::InitBuffScript()
	||  !this->CScriptCompiler::InitDungenNpcScript() )
		return false;

	this->CScriptCompiler::Reset();
	return true;
}


hook_method<void (CScriptCompiler::*)(void)> CScriptCompiler::_Reset(SERVER, "CScriptCompiler::Reset");
void CScriptCompiler::Reset(void) // line 102
{
	return (this->*_Reset)();

	if( m_compiler )
	{
		m_compiler->CCompiler::Release();
		if( m_compiler != NULL )
			delete m_compiler;
		m_compiler = NULL;
	}
}


hook_method<bool (CScriptCompiler::*)(void)> CScriptCompiler::_InitTokenMap(SERVER, "CScriptCompiler::InitTokenMap");
bool CScriptCompiler::InitTokenMap(void) // line 112
{
	return (this->*_InitTokenMap)();

	Trace("\n\n ----- Begin : Init Token Map ------ ");

	if( !this->CScriptCompiler::SetAsm((char*)GetScriptFileName(ASM_COMMON))
	||  !this->CScriptCompiler::SetBin((char*)GetScriptFileName(BIN_COMMON))
	||  !this->CScriptCompiler::LoadEnum(GetScriptFileName(SC_ENUM_V2), 20020715)
	||  !this->CScriptCompiler::LoadDef((char*)GetScriptFileName(DEF_ITEM))
	||  !this->CScriptCompiler::LoadDef((char*)GetScriptFileName(DEF_MOBNAME))
	||  !this->CScriptCompiler::LoadDef((char*)GetScriptFileName(DEF_NPCSPR))
	||  !this->CScriptCompiler::LoadDef((char*)GetScriptFileName(DEF_SKILL))
	||  !this->CScriptCompiler::LoadV2() )
		return false;

	this->CScriptCompiler::Compelete();
	Trace("\n ----- End  : Init Token Map ------ \n");
	return true;
}


hook_method<bool (CScriptCompiler::*)(void)> CScriptCompiler::_InitItemScript(SERVER, "CScriptCompiler::InitItemScript");
bool CScriptCompiler::InitItemScript(void) // line 140
{
	return (this->*_InitItemScript)();

	Trace("\n\n ----- Begin : Init Item Script ------ ");

	if( !this->CScriptCompiler::SetAsm((char*)GetScriptFileName(ASM_ITEM))
	||  !this->CScriptCompiler::SetBin((char*)GetScriptFileName(BIN_ITEM))
	||  !this->CScriptCompiler::Run(GetScriptFileName(SC_ITEM_SPECIAL), 0) )
		return false;

	this->CScriptCompiler::Compelete();
	Trace("\n ----- End : Init Item Script ------ \n");
	return true;
}


hook_method<bool (CScriptCompiler::*)(void)> CScriptCompiler::_InitNpcScript(SERVER, "CScriptCompiler::InitNpcScript");
bool CScriptCompiler::InitNpcScript(void) // line 167
{
	return (this->*_InitNpcScript)();

	Trace("\n\n ----- Begin : Init Npc Script ------ \n");

	if( !this->CScriptCompiler::SetAsm((char*)GetScriptFileName(ASM_NPC))
	||  !this->CScriptCompiler::SetBin((char*)GetScriptFileName(BIN_NPC))
	||  !this->CScriptCompiler::Run(GetScriptFileName(SC_NPC_MOBDEF), 20021009) )
		return false;

	mystd::deque<mystd::string> scriptQ;

	FILE* listf = fopen(GetScriptFileName(NPC_LIST), "r");
	if( listf == NULL )
	{
		this->CScriptCompiler::Error("Can't Open %s", GetScriptFileName(NPC_LIST));
		return false;
	}

	char line[256];
	while( fgets(line, sizeof(line), listf) != NULL )
	{
		char name[256];
		memset(name, 0, sizeof(name));
		sscanf(line, "%s", name);

		if( name[0] && strncmp(name, "//", 2) && strncmp(name, "; ", 1) )
			scriptQ.push_back(g_pathDataNpc->CPathData::SetFileName(name));
	}
	fclose(listf);

	mystd::deque<mystd::string>::const_iterator it;
	for( it = scriptQ.begin(); it != scriptQ.end(); ++it )
		if( !this->CScriptCompiler::Run((*it).c_str(), 0) )
			return false;

	this->CScriptCompiler::Compelete();
	Trace("\n ----- End : Init Npc Script ------ \n");
	return true;
}


hook_method<bool (CScriptCompiler::*)(void)> CScriptCompiler::_InitSkillScript(SERVER, "CScriptCompiler::InitSkillScript");
bool CScriptCompiler::InitSkillScript(void) // line 245
{
	return (this->*_InitSkillScript)();

	Trace("\n\n ---- Begin : Init Skill Script ----- ");

	if( !this->CScriptCompiler::SetAsm((char*)GetScriptFileName(ASM_SKILL))
	||  !this->CScriptCompiler::SetBin((char*)GetScriptFileName(BIN_SKILL)) )
		return false;

	FILE* f = fopen(GetScriptFileName(SC_SKILL_SPECIAL), "r");
	if( f == NULL )
	{
		Trace("\n\n ----- %s Not Existed ------ \n", GetScriptFileName(SC_SKILL_SPECIAL));
		return true;
	}
	fclose(f);

	if( !this->CScriptCompiler::Run(GetScriptFileName(SC_SKILL_SPECIAL), 0) )
		return false;

	this->CScriptCompiler::Compelete();
	Trace("\n ----- End : Init Skill Script ------ \n\n");
	return true;
}


hook_method<bool (CScriptCompiler::*)(void)> CScriptCompiler::_InitBuffScript(SERVER, "CScriptCompiler::InitBuffScript");
bool CScriptCompiler::InitBuffScript(void) // line 276
{
	return (this->*_InitBuffScript)();

	Trace("\n\n ---- Begin : Init BUFF Script ----- ");

	if( !this->CScriptCompiler::SetAsm((char*)GetScriptFileName(ASM_BUFF))
	||  !this->CScriptCompiler::SetBin((char*)GetScriptFileName(BIN_BUFF)) )
		return false;

	FILE* f = fopen(GetScriptFileName(SC_BUFF_SPECIAL), "r");
	if( f == NULL )
	{
		Trace("\n\n ----- %s Not Existed ------ \n", GetScriptFileName(SC_BUFF_SPECIAL));
		return true;
	}
	fclose(f);

	if( !this->CScriptCompiler::Run(GetScriptFileName(SC_BUFF_SPECIAL), 0) )
		return false;

	this->CScriptCompiler::Compelete();
	Trace("\n ----- End : Init BUFF Script ------ \n\n");
	return true;
}


hook_method<bool (CScriptCompiler::*)(void)> CScriptCompiler::_InitDungenNpcScript(SERVER, "CScriptCompiler::InitDungenNpcScript");
bool CScriptCompiler::InitDungenNpcScript(void) // line 309
{
	return (this->*_InitDungenNpcScript)();

	Trace("\n\n ---- Begin : Init DunGeon Script ----- ");

	CLoadDGScriptList scriptList;
	if( !scriptList.CLoadDGScriptList::Load(".\\npcdata\\DungeonList.txt") || !scriptList.CLoadDGScriptList::Parsing() )
		return false;

	while( scriptList.GetListCount() > 0 )
	{
		mystd::list<mystd::string> scList;
		const char* list = scriptList.CLoadDGScriptList::GetList(scList);

		char asmName[128];
		char binName[128];
		memset(&asmName, 0, sizeof(asmName));
		memset(&binName, 0, sizeof(binName));
		sprintf(asmName, ".\\scriptbin\\%s.asm", list);
		sprintf(binName, ".\\scriptbin\\%s.bin", list);
		this->CScriptCompiler::SetAsm(asmName);
		this->CScriptCompiler::SetBin(binName);

		while( scList.size() != 0 )
		{
			mystd::string scFile = scList.front();
			scList.pop_front();
			this->CScriptCompiler::Run(scFile.c_str(), 0);
		}

		this->CScriptCompiler::Compelete();
		CDGNpcMgr::GetObj()->CDGNpcMgr::AddInstantMap(list);

		scriptList.CLoadDGScriptList::GetNext();
	}
	Trace("\n ----- End : Init DunGeon Npc Script ------ \n");

	return true;
}


hook_method<bool (CScriptCompiler::*)(char* fName)> CScriptCompiler::_SetAsm(SERVER, "CScriptCompiler::SetAsm");
bool CScriptCompiler::SetAsm(char* fName) // line 397
{
	return (this->*_SetAsm)(fName);

	//TODO
}


hook_method<bool (CScriptCompiler::*)(char* fName)> CScriptCompiler::_SetBin(SERVER, "CScriptCompiler::SetBin");
bool CScriptCompiler::SetBin(char* fName) // line 407
{
	return (this->*_SetBin)(fName);

	//TODO
}


hook_method<bool (CScriptCompiler::*)(const char* fName, int verDate)> CScriptCompiler::_LoadEnum(SERVER, "CScriptCompiler::LoadEnum");
bool CScriptCompiler::LoadEnum(const char* fName, int verDate) // line 417
{
	return (this->*_LoadEnum)(fName, verDate);

	//TODO
}


hook_method<bool (CScriptCompiler::*)(char* fName)> CScriptCompiler::_LoadDef(SERVER, "CScriptCompiler::LoadDef");
bool CScriptCompiler::LoadDef(char* fName) // line 429
{
	return (this->*_LoadDef)(fName);

	Trace("\nLoading.... %s", fName);

	if( !m_compiler->CCompiler::LoadDef(const_cast<char*>(fName)) )
	{
		this->CScriptCompiler::Error("Can't Load Def, %s", fName);
		return false;
	}

	return true;
}


hook_method<bool (CScriptCompiler::*)(const char* fName, int verDate)> CScriptCompiler::_Run(SERVER, "CScriptCompiler::Run");
bool CScriptCompiler::Run(const char* fName, int verDate) // line 441
{
	return (this->*_Run)(fName, verDate);

	Trace("\nLoading.... %s", fName);

	if( !m_compiler->CCompiler::Run(fName, verDate) )
	{
		this->CScriptCompiler::Error("Can't Run or Old Version, %s", fName);
		return false;
	}

	return true;
}


hook_method<void (CScriptCompiler::*)(const char* str, ...)> CScriptCompiler::_Error(SERVER, "CScriptCompiler::Error");
void CScriptCompiler::Error(const char* str, ...) // line 453
{
//	return (this->*_Error)(str, ...);

	va_list va;
	va_start(va, str);

	char szBuffer[1024];
	memset(szBuffer, 0, sizeof(szBuffer));

	vsprintf(szBuffer, str, va);
	Trace(szBuffer);
	MessageBoxA(NULL, szBuffer, "SCRIPT COMPILER ERROR", MB_OK);
}


hook_method<void (CScriptCompiler::*)(void)> CScriptCompiler::_Compelete(SERVER, "CScriptCompiler::Compelete");
void CScriptCompiler::Compelete(void) // line 466
{
	return (this->*_Compelete)();

	m_compiler->CCompiler::Optimize();
	m_compiler->CCompiler::Release();
}


////////////////////////////////////////
