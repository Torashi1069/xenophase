#include "MapRes.h"
#include "MapTypePropertyMgr.h"
#include "Path.h"
#include "ErrorLog.h"
#include "ZoneProcess.h"


CMapRes::CMapRes(const int in_mapType) // line 21
: m_Property(CMapTypePropertyMgr::GetObj()->CMapTypePropertyMgr::GetProperty(in_mapType))
{
	m_mapType = in_mapType;
	m_TileInfo = NULL;
	m_pcCount = 0;
	m_mapPropertyCountPK = NULL;
}


CMapRes::~CMapRes(void) // line 29
{
	this->CMapRes::Reset();
	m_pcCount = 0;
}


hook_method<bool (CMapRes::*)(const int in_SKID, const int in_ObjType)> CMapRes::_IsPropertyBlockSkill(SERVER, "CMapRes::IsPropertyBlockSkill");
bool CMapRes::IsPropertyBlockSkill(const int in_SKID, const int in_ObjType) // line 729
{
	return (this->*_IsPropertyBlockSkill)(in_SKID, in_ObjType);

	return( this != NULL ) ? m_Property.CMapTypeProperty::isBlockSkill(in_SKID, in_ObjType) : false;
}


hook_method<bool (CMapRes::*)(const int in_ITID)> CMapRes::_IsPropertyBlockItem(SERVER, "CMapRes::IsPropertyBlockItem");
bool CMapRes::IsPropertyBlockItem(const int in_ITID) // line 737
{
	return (this->*_IsPropertyBlockItem)(in_ITID);

	return( this != NULL ) ? m_Property.CMapTypeProperty::isBlockItem(in_ITID) : false;
}


hook_method<bool (CMapRes::*)(const int in_ITID)> CMapRes::_IsPropertyBlockEquipItem(SERVER, "CMapRes::IsPropertyBlockEquipItem");
bool CMapRes::IsPropertyBlockEquipItem(const int in_ITID) // line 757
{
	return (this->*_IsPropertyBlockEquipItem)(in_ITID);

	return( this != NULL ) ? m_Property.CMapTypeProperty::isBlockEquipItem(in_ITID) : false;
}


hook_method<bool (CMapRes::*)(const int in_BuffID)> CMapRes::_IsPropertyBlockBuff(SERVER, "CMapRes::IsPropertyBlockBuff");
bool CMapRes::IsPropertyBlockBuff(const int in_BuffID) // line 763
{
	return (this->*_IsPropertyBlockBuff)(in_BuffID);

	return( this != NULL ) ? m_Property.CMapTypeProperty::isBlockBuff(in_BuffID) : false;
}


hook_method<int (CMapRes::*)(const int in_SKID)> CMapRes::_GetPropertyTrapDurationPercent(SERVER, "CMapRes::GetPropertyTrapDurationPercent");
int CMapRes::GetPropertyTrapDurationPercent(const int in_SKID) // line 745
{
	return (this->*_GetPropertyTrapDurationPercent)(in_SKID);

	return( this != NULL ) ? m_Property.CMapTypeProperty::GetTrapDurationPercent(in_SKID) : 100;
}


hook_method<int (CMapRes::*)(const int in_SKID)> CMapRes::_GetSkillDamagePercent(SERVER, "CMapRes::GetSkillDamagePercent");
int CMapRes::GetSkillDamagePercent(const int in_SKID) // line 751
{
	return (this->*_GetSkillDamagePercent)(in_SKID);

	return( this != NULL ) ? m_Property.CMapTypeProperty::GetSkillDamagePercent(in_SKID) : 100;
}


hook_method<bool (CMapRes::*)(void) const> CMapRes::_isInstantMap(SERVER, "CMapRes::isInstantMap");
const bool CMapRes::isInstantMap(void) const // line 61 (MapRes.h)
{
	return (this->*_isInstantMap)();

	return false;
}


hook_method<void (CMapRes::*)(unsigned char* out_pArray, const int in_MaxLength)> CMapRes::_GetProprtyByteArray(SERVER, "CMapRes::GetProprtyByteArray");
void CMapRes::GetProprtyByteArray(unsigned char* out_pArray, const int in_MaxLength) // line 334
{
	return (this->*_GetProprtyByteArray)(out_pArray, in_MaxLength);

	m_Property.CMapTypeProperty::GetByteArray(out_pArray, in_MaxLength);
}


hook_method<int (CMapRes::*)(const char* filename, int mapID, int mapType)> CMapRes::_Load(SERVER, "CMapRes::Load");
int CMapRes::Load(const char* filename, int mapID, int mapType) // line 35
{
	return (this->*_Load)(filename, mapID, mapType);

	memcpy(m_mapName, filename, sizeof(m_mapName));
	m_mapID = mapID;
	m_mapType = mapType;

	char tempbuf[256];
	strcpy(tempbuf, this->CMapRes::GetLoadFileName().c_str());

	char seps[4];
	strcpy(seps, " .");

	char* fname = strtok(tempbuf, seps);
	if( fname == NULL )
		return 0;

	char tempFileName[256];
	strcpy(tempFileName, "./mapfile/");
	strcat(tempFileName, fname);
	strcat(tempFileName, ".rsw");

	FILE* rswfile = fopen(g_pathData->CPathData::SetFileName(tempFileName), "rb");
	if( rswfile == NULL )
		return 0;

	char magicId[5];
	strcpy(magicId, "GRSW");

	char magicBuf[5];
	magicBuf[sizeof(magicBuf)-1] = '\0';
	fread(magicBuf, 4, 1, rswfile);

	if( strcmp(magicBuf, magicId) != 0 )
		return 0;

	unsigned char verMajor;
	unsigned char verMinor;
	fread(&verMajor, 1, 1, rswfile);
	fread(&verMinor, 1, 1, rswfile);

	if( verMajor > 2 || verMajor == 2 && verMinor > 1 )
		return 0;

	char nameBuf[40];
	fread(nameBuf, 40, 1, rswfile);
	fread(nameBuf, 40, 1, rswfile);

	if( verMajor == 1 && verMinor >= 4 || verMajor == 2 )
		fread(nameBuf, 40, 1, rswfile);

	fread(nameBuf, 40, 1, rswfile);

	if( !(verMajor == 1 && verMinor >= 3 || verMajor >= 2) )
		return 0;

	float m_waterLevel;
	fread(&m_waterLevel, 4, 1, rswfile);

	fclose(rswfile);

	strcpy(magicId, "GRAT");
	FILE* gatfile = fopen(this->CMapRes::GetLoadFileName().c_str(), "rb");
	if( gatfile == NULL )
	{
		char filedir[256];
		strcpy(filedir, "./mapfile/");
		strcat(filedir, this->CMapRes::GetLoadFileName().c_str());

		gatfile = fopen(g_pathData->CPathData::SetFileName(filedir), "rb");
		if( gatfile == NULL )
			return 0;
	}

	char checkBuf[5];
	checkBuf[sizeof(checkBuf)-1] = '\0';
	fread(checkBuf, 4, 1, gatfile);

	if( strcmp(checkBuf, magicId) != 0 )
		return 0;

	unsigned char gatverMajor;
	unsigned char gatverMinor;
	fread(&gatverMajor, 1, 1, gatfile);
	fread(&gatverMinor, 1, 1, gatfile);

	if( !(gatverMajor == 1 && gatverMinor <= 2) )
		return 1; // unsupported gat version

	int w;
	int h;
	fread(&w, 4, 1, gatfile);
	fread(&h, 4, 1, gatfile);

	struct AttrCell
	{
		/* this+ 0 */ float h1;
		/* this+ 4 */ float h2;
		/* this+ 8 */ float h3;
		/* this+12 */ float h4;
		/* this+16 */ int flag;
	};

	AttrCell* cells = new AttrCell[w * h];
	fread(cells, sizeof(AttrCell), w * h, gatfile);

	fclose(gatfile);

	m_width = w;
	m_height = h;
	m_TileInfo = new unsigned char[w * h];

	for( int j = 0; j < m_width; ++j )
	{
		for( int i = 0; i < m_height; ++i )
		{
			int pos = j + i * m_width;
			AttrCell& cell = cells[pos];

			m_TileInfo[pos] = 0;

			if( cell.flag == 1 || cell.flag == 5 )
				m_TileInfo[pos] |= 1;
			else
				m_TileInfo[pos] |= 2;

			if( m_waterLevel < cell.h1 )
				m_TileInfo[pos] |= 4;
		}
	}

	m_pathFinder.CPathFinder::SetMap(this);
	delete[] cells;

	return 1;
}


hook_method<void (CMapRes::*)(void)> CMapRes::_Reset(SERVER, "CMapRes::Reset");
void CMapRes::Reset(void) // line 227
{
	return (this->*_Reset)();

	if( m_TileInfo )
	{
		delete[] m_TileInfo;
		m_TileInfo = NULL;
	}

	if( m_mapPropertyCountPK )
	{
		delete m_mapPropertyCountPK;
		m_mapPropertyCountPK = NULL;
	}
}


//hook_method<void (CMapRes::*)(void)> CMapRes::_OnTimer(SERVER, "CMapRes::OnTimer");
void CMapRes::OnTimer(void) // line ??? (aliased)
{
//	return (this->*_OnTimer)();

	;
}


//hook_method<unsigned long (CMapRes::*)(void)> CMapRes::_GetGDID(SERVER, "CMapRes::GetGDID");
unsigned long CMapRes::GetGDID(void) // line ??? (aliased)
{
//	return (this->*_GetGDID)();

	return 0;
}


//hook_method<const char* (CMapRes::*)(void) const> CMapRes::_GetName(SERVER, "CMapRes::GetName");
const char* CMapRes::GetName(void) const // line ???
{
//	return (this->*_GetName)();

	return m_mapName;
}


//hook_method<int (CMapRes::*)(void)> CMapRes::_GetID(SERVER, "CMapRes::GetID");
int CMapRes::GetID(void) // line ???
{
//	return (this->*_GetID)();

	return m_mapID;
}


//hook_method<int (CMapRes::*)(void)> CMapRes::_GetType(SERVER, "CMapRes::GetType");
int CMapRes::GetType(void) // line ???
{
//	return (this->*_GetType)();

	return m_mapType;
}


//hook_method<int (CMapRes::*)(void) const> CMapRes::_GetHeight(SERVER, "CMapRes::GetHeight");
int CMapRes::GetHeight(void) const // line ???
{
//	return (this->*_GetHeight)();

	return m_height;
}


//hook_method<int (CMapRes::*)(void) const> CMapRes::_GetWidth(SERVER, "CMapRes::GetWidth");
int CMapRes::GetWidth(void) const // line ???
{
//	return (this->*_GetWidth)();

	return m_width;
}


hook_method<void (CMapRes::*)(int& xPos, int& yPos, int minDis, int maxDis, unsigned long AID)> CMapRes::_GetRandomPos(SERVER, "?GetRandomPos@CMapRes@@QAEXAAH0HHK@Z");
void CMapRes::GetRandomPos(int& xPos, int& yPos, int minDis, int maxDis, unsigned long AID) // line 241
{
	return (this->*_GetRandomPos)(xPos, yPos, minDis, maxDis, AID);

	int xdir = ( GetServerRandom(0, 20000) % 2 ) ? 1 : -1;
	int ydir = ( GetServerRandom(0, 20000) % 2 ) ? 1 : -1;

	for( int i = -1; i <= 1; ++i )
	{
		for( int j = -1; j <= 1; ++j )
		{
			if( i == 0 && j == 0 )
				continue; // skip center cell

			int radius = maxDis - minDis;

			int x = xPos + i*xdir * (minDis + GetServerRandom(0, 20000) % max(1,radius));
			int y = yPos + j*ydir * (minDis + GetServerRandom(0, 20000) % max(1,radius));

			if( x <= 6 || x >= m_width - 6 || y <= 6 || y >= m_height - 6 )
				continue; // too close to the edge

			if( (this->CMapRes::GetTileInfo(x,y) & 1) == 0 )
			{
				xPos = x;
				yPos = y;
				return; // done.
			}
		}
	}
}


hook_method<int (CMapRes::*)(int& xPos, int& yPos)> CMapRes::_GetRandomPos2(SERVER, "?GetRandomPos@CMapRes@@QAEHAAH0@Z");
int CMapRes::GetRandomPos(int& xPos, int& yPos) // line 299
{
	return (this->*_GetRandomPos2)(xPos, yPos);

	int x = 15 + GetServerRandom(0, 20000) % max(1, m_width - 30);
	int y = 15 + GetServerRandom(0, 20000) % max(1, m_height - 30);
	int coef = 3;
	int count;

	for( count = 0; this->CMapRes::GetTileInfo(x,y) != 1 && count < 50; ++count )
	{
		coef += 7;
		x = 15 + GetServerRandom(0, 20000) * coef % max(1, m_width - 30);
		y = 15 + GetServerRandom(0, 20000) * coef % max(1, m_height - 30);
	}

	if( count == 50 || x < 5 || y < 5 || x > m_width || y > m_height )
	{
		xPos = 30;
		yPos = 30;

		char temp[256];
		sprintf(temp, "CMapRes :: GetRandomPos(int,int) return False  %s\n", m_mapName);
		g_errorLogs->CErrorLog::CriticalErrorLog(temp, 319, ".\\MapRes.cpp");
		return 0;
	}

	xPos = x;
	yPos = y;
	return 1;
}


hook_method<int (CMapRes::*)(int& xPos, int& yPos, int xRange, int yRange, unsigned long AID)> CMapRes::_GetRandomPosByRange(SERVER, "CMapRes::GetRandomPosByRange");
int CMapRes::GetRandomPosByRange(int& xPos, int& yPos, int xRange, int yRange, unsigned long AID) // line 270
{
	return (this->*_GetRandomPosByRange)(xPos, yPos, xRange, yRange, AID);

	int xdir = ( GetServerRandom(0, 20000) % 2 ) ? 1 : -1;
	int ydir = ( GetServerRandom(0, 20000) % 2 ) ? 1 : -1;

	for( int i = -1; i <= 1; ++i )
	{
		for( int j = -1; j <= 1; ++j )
		{
			if( i == 0 && j == 0 )
				continue;

			int x = xPos + xdir * i * GetServerRandom(0, 20000) % max(1,xRange);
			int y = yPos + ydir * j * GetServerRandom(0, 20000) % max(1,yRange);

			if( x < 5 || x > m_width - 5 || y < 5 || y > m_height - 5 )
				continue;

			if( (this->CMapRes::GetTileInfo(x,y) & 1) == 0 )
			{
				xPos = x;
				yPos = y;
				return 1; // done.
			}
		}
	}

	return 0;
}


hook_method<int (CMapRes::*)(int& xPos, int& yPos)> CMapRes::_GetRandomPosExceptWarp(SERVER, "CMapRes::GetRandomPosExceptWarp");
int CMapRes::GetRandomPosExceptWarp(int& xPos, int& yPos) // line 623
{
	return (this->*_GetRandomPosExceptWarp)(xPos, yPos);

	//TODO
}


hook_method<int (CMapRes::*)(int x, int y, int flag)> CMapRes::_UpdateTileInfo(SERVER, "CMapRes::UpdateTileInfo");
int CMapRes::UpdateTileInfo(int x, int y, int flag) // line 204
{
	return (this->*_UpdateTileInfo)(x, y, flag);

	//TODO
}


hook_method<int (CMapRes::*)(int property)> CMapRes::_IsItPossible(SERVER, "CMapRes::IsItPossible");
int CMapRes::IsItPossible(int property) // line 342
{
	return (this->*_IsItPossible)(property);

	return m_Property.CMapTypeProperty::IsItPossible(property);
}


hook_method<void (CMapRes::*)(BROADCAST_INFO* info)> CMapRes::_Broadcast(SERVER, "CMapRes::Broadcast");
void CMapRes::Broadcast(BROADCAST_INFO* info) // line 436
{
	return (this->*_Broadcast)(info);

	//TODO
}


hook_method<void (CMapRes::*)(int len, const char* buf, int broadcastType, int data)> CMapRes::_Send(SERVER, "CMapRes::Send");
void CMapRes::Send(int len, const char* buf, int broadcastType, int data) // line 462
{
	return (this->*_Send)(len, buf, broadcastType, data);

	//TODO
}


hook_method<int (CMapRes::*)(int x, int y)> CMapRes::_IsWaterCell(SERVER, "CMapRes::IsWaterCell");
int CMapRes::IsWaterCell(int x, int y) // line 527
{
	return (this->*_IsWaterCell)(x, y);

	return ( this->CMapRes::IsValidCell(x, y) ) ? ( (m_TileInfo[x + y * m_width] & 4) == 4 ) : false;

}


hook_method<int (CMapRes::*)(int x, int y) const> CMapRes::_IsMovableCell(SERVER, "CMapRes::IsMovableCell");
int CMapRes::IsMovableCell(int x, int y) const // line 501
{
	return (this->*_IsMovableCell)(x, y);

	return ( this->CMapRes::IsValidCell(x, y) ) ? ( (this->CMapRes::GetTileInfo(x, y) & 1) != 1 ) : false;
}


hook_method<int (CMapRes::*)(int sx, int sy, int dx, int dy)> CMapRes::_IsConnected(SERVER, "CMapRes::IsConnected");
int CMapRes::IsConnected(int sx, int sy, int dx, int dy) // line 557
{
	return (this->*_IsConnected)(sx, sy, dx, dy);

	//TODO
}


hook_method<int (CMapRes::*)(int x, int y)> CMapRes::_IsArrowCrossCell(SERVER, "CMapRes::IsArrowCrossCell");
int CMapRes::IsArrowCrossCell(int x, int y) // line 519
{
	return (this->*_IsArrowCrossCell)(x, y);

	//TODO
}


hook_method<int (CMapRes::*)(int x1, int y1, int x2, int y2, int isClose)> CMapRes::_IsDirectPath(SERVER, "CMapRes::IsDirectPath");
int CMapRes::IsDirectPath(int x1, int y1, int x2, int y2, int isClose) // line 576
{
	return (this->*_IsDirectPath)(x1, y1, x2, y2, isClose);

	//TODO
}


hook_method<int (CMapRes::*)(int x, int y)> CMapRes::_IsValidPosition(SERVER, "CMapRes::IsValidPosition");
int CMapRes::IsValidPosition(int x, int y) // line 535
{
	return (this->*_IsValidPosition)(x, y);

	return (x >= 5 && y >= 5 && x <= m_width - 5 && y <= m_height - 5);
}


hook_method<int (CMapRes::*)(int xPos, int yPos, int range, unsigned long property)> CMapRes::_IsExsistCells(SERVER, "CMapRes::IsExsistCells");
int CMapRes::IsExsistCells(int xPos, int yPos, int range, unsigned long property) // line 542
{
	return (this->*_IsExsistCells)(xPos, yPos, range, property);

	//TODO
}


hook_method<int (CMapRes::*)(int xPos, int yPos) const> CMapRes::_IsValidCell(SERVER, "CMapRes::IsValidCell");
int CMapRes::IsValidCell(int xPos, int yPos) const // line 115 (MapRes.h)
{
	return (this->*_IsValidCell)(xPos, yPos);

	return ( xPos >= 0 && yPos >= 0 && xPos < m_width && yPos < m_height );
}


//hook_method<mystd::vector<CCharacter *>* (CMapRes::*)(int xCellPos, int yCellPos)> CMapRes::_GetSectionByCellPos(SERVER, "CMapRes::GetSectionByCellPos");
mystd::vector<CCharacter *>* CMapRes::GetSectionByCellPos(int xCellPos, int yCellPos) // line ???
{
//	return (this->*_GetSectionByCellPos)(xCellPos, yCellPos);

	return m_sectionMgr.CSectionMgr::GetSectionByCellPos(xCellPos, yCellPos);
}


//hook_method<int (CMapRes::*)(unsigned long AID, int& xPos, int& yPos)> CMapRes::_GetEmptyPosition(SERVER, "CMapRes::GetEmptyPosition");
int CMapRes::GetEmptyPosition(unsigned long AID, int& xPos, int& yPos) // line ???
{
//	return (this->*_GetEmptyPosition)(AID, xPos, yPos);

	return m_sectionMgr.CSectionMgr::GetEmptyPosition(AID, xPos, yPos);
}


hook_method<int (CMapRes::*)(int xCellPos, int yCellPos, CCharacter* character)> CMapRes::_AddCharacter(SERVER, "CMapRes::AddCharacter");
int CMapRes::AddCharacter(int xCellPos, int yCellPos, CCharacter* character) // line 137 (MapRes.h)
{
	return (this->*_AddCharacter)(xCellPos, yCellPos, character);

	return m_sectionMgr.CSectionMgr::AddCharacter(xCellPos, yCellPos, character);
}


//hook_method<void (CMapRes::*)(CCharacter* character)> CMapRes::_RemoveCharacter(SERVER, "CMapRes::RemoveCharacter");
void CMapRes::RemoveCharacter(CCharacter* character) // line ???
{
//	return (this->*_RemoveCharacter)(character);

	m_sectionMgr.CSectionMgr::RemoveCharacter(character);
}


//hook_method<int (CMapRes::*)(void)> CMapRes::_GetTotalSectionSize(SERVER, "CMapRes::GetTotalSectionSize");
int CMapRes::GetTotalSectionSize(void) // line ???
{
//	return (this->*_GetTotalSectionSize)();

	return m_sectionMgr.CSectionMgr::GetTotalSectionSize();
}


//hook_method<int (CMapRes::*)(mystd::vector<CCharacter *>* src, mystd::vector<CCharacter *>* dest, CCharacter* character)> CMapRes::_MoveCharacter(SERVER, "CMapRes::MoveCharacter");
int CMapRes::MoveCharacter(mystd::vector<CCharacter *>* src, mystd::vector<CCharacter *>* dest, CCharacter* character) // line ???
{
//	return (this->*_MoveCharacter)(src, dest, character);

	return m_sectionMgr.CSectionMgr::MoveCharacter(src, dest, character);
}


//hook_method<void (CMapRes::*)(int xPos, int yPos, int range, NEIGHBORHOOD_SECTION* result)> CMapRes::_GetNeighborhoodSections(SERVER, "CMapRes::GetNeighborhoodSections");
void CMapRes::GetNeighborhoodSections(int xPos, int yPos, int range, NEIGHBORHOOD_SECTION* result) // line ???
{
//	return (this->*_GetNeighborhoodSections)(xPos, yPos, range, result);

	m_sectionMgr.CSectionMgr::GetNeighborhoodSections(xPos, yPos, range, result);
}


//hook_method<int (CMapRes::*)(void)> CMapRes::_GetSectionSize(SERVER, "CMapRes::GetSectionSize");
int CMapRes::GetSectionSize(void) // line ???
{
//	return (this->*_GetSectionSize)();

	return m_sectionMgr.CSectionMgr::GetSectionSize();
}


//hook_method<mystd::vector<CCharacter *>** (CMapRes::*)(void)> CMapRes::_GetSectionList(SERVER, "CMapRes::GetSectionList");
mystd::vector<CCharacter *>** CMapRes::GetSectionList(void) // line ???
{
//	return (this->*_GetSectionList)();

	return m_sectionMgr.CSectionMgr::GetSectionList();
}


//hook_method<int (CMapRes::*)(unsigned long startTime, int sx, int sy, int xM, int yM, int dx, int dy, int speedFactor, CPathInfo* result)> CMapRes::_FindPath(SERVER, "CMapRes::FindPath");
int CMapRes::FindPath(unsigned long startTime, int sx, int sy, int xM, int yM, int dx, int dy, int speedFactor, CPathInfo* result) // line ???
{
//	return (this->*_FindPath)(startTime, sx, sy, xM, yM, dx, dy, speedFactor, result);

	return m_pathFinder.CPathFinder::FindPath(startTime, sx, sy, xM, yM, dx, dy, speedFactor, result);
}


//hook_method<int (CMapRes::*)(unsigned long AID, int xPos, int yPos)> CMapRes::_IsEmptyPos(SERVER, "CMapRes::IsEmptyPos");
int CMapRes::IsEmptyPos(unsigned long AID, int xPos, int yPos) // line ???
{
//	return (this->*_IsEmptyPos)(AID, xPos, yPos);

	return m_sectionMgr.CSectionMgr::IsEmptyPos(AID, xPos, yPos);
}


hook_method<int (CMapRes::*)(int x, int y)> CMapRes::_GetCellType(SERVER, "CMapRes::GetCellType");
int CMapRes::GetCellType(int x, int y) // line 686
{
	return (this->*_GetCellType)(x, y);

	if( !this->CMapRes::IsValidPosition(x, y) )
		return 1;

    unsigned char cell = m_TileInfo[x + y * m_width];
    if( cell & 1 )
      return 2 * (cell & 2) | 1;

	return 0;
}


hook_method<bool (CMapRes::*)(void)> CMapRes::_IsVillage(SERVER, "CMapRes::IsVillage");
bool CMapRes::IsVillage(void) // line 192 (MapRes.h)
{
	return (this->*_IsVillage)();

	return (m_mapType == MAPTYPE_VILLAGE || m_mapType == MAPTYPE_VILLAGE_IN);
}


//hook_method<void (CMapRes::*)(void)> CMapRes::_SectionMgrInit(SERVER, "CMapRes::SectionMgrInit");
void CMapRes::SectionMgrInit(void) // line ???
{
//	return (this->*_SectionMgrInit)();

	m_sectionMgr.CSectionMgr::Init(m_mapName, m_width, m_height, SECTION_SIZE, this);
}


hook_method<mystd::string (CMapRes::*)(void)> CMapRes::_GetLoadFileName(SERVER, "CMapRes::GetLoadFileName");
mystd::string CMapRes::GetLoadFileName(void) // line 201 (MapRes.h)
{
	return (this->*_GetLoadFileName)();

	return m_mapName;
}


hook_method<bool (CMapRes::*)(void)> CMapRes::_IsBattleField(SERVER, "CMapRes::IsBattleField");
bool CMapRes::IsBattleField(void) // line 61 (MapRes.h)
{
	return (this->*_IsBattleField)();

	return false;
}


//hook_method<bool (CMapRes::*)(void)> CMapRes::_IsAgit(SERVER, "CMapRes::IsAgit");
bool CMapRes::IsAgit(void) // line ?? (aliased)
{
//	return (this->*_IsAgit)();

	return false;
}


hook_method<bool (CMapRes::*)(void)> CMapRes::_AllocMapPropertyCountPK(SERVER, "CMapRes::AllocMapPropertyCountPK");
bool CMapRes::AllocMapPropertyCountPK(void) // line 769
{
	return (this->*_AllocMapPropertyCountPK)();

	m_mapPropertyCountPK = new CMapPropertyCountPK();
	return ( m_mapPropertyCountPK != NULL );
}


hook_method<bool (CMapRes::*)(unsigned long AID, int winpoint)> CMapRes::_UpdateWinPoint(SERVER, "CMapRes::UpdateWinPoint");
bool CMapRes::UpdateWinPoint(unsigned long AID, int winpoint) // line 781
{
	return (this->*_UpdateWinPoint)(AID, winpoint);

	return( m_mapPropertyCountPK != NULL ) ? m_mapPropertyCountPK->CMapPropertyCountPK::UpdateWinPoint(AID, winpoint) : 0;
}


hook_method<bool (CMapRes::*)(unsigned long AID)> CMapRes::_DeleteWinPoint(SERVER, "CMapRes::DeleteWinPoint");
bool CMapRes::DeleteWinPoint(unsigned long AID) // line 790
{
	return (this->*_DeleteWinPoint)(AID);

	return( m_mapPropertyCountPK != NULL ) ? m_mapPropertyCountPK->CMapPropertyCountPK::DeleteWinPoint(AID) : 0;
}


hook_method<unsigned char (CMapRes::*)(int xPos, int yPos) const> CMapRes::_GetTileInfo(SERVER, "CMapRes::GetTileInfo");
unsigned char CMapRes::GetTileInfo(int xPos, int yPos) const // line 219 (MapRes.h)
{
	return (this->*_GetTileInfo)(xPos, yPos);

	return ( this->CMapRes::IsValidCell(xPos, yPos) ) ? m_TileInfo[xPos + yPos * m_width] : 1;
}
