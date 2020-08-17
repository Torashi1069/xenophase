#include "CharacterMgr.h"
#include "Enum.h"
#include "MapRes.h"
#include "MapTypePropertyMgr.h"
#include "NPC.h"
#include "Path.h"
#include "ZoneProcess.h"
#include "ZoneProcessStuff.h"
#include "Common/Packet.h"


/// globals
const int SECTION_SIZE = 40;


CMapRes::CMapRes(const int in_mapType)
: m_Property(CMapTypePropertyMgr::GetObj()->CMapTypePropertyMgr::GetProperty(in_mapType))
{
	m_mapType = in_mapType;
	m_TileInfo = NULL;
	m_pcCount = 0;
	m_mapPropertyCountPK = NULL;

	m_Scheduler.MapResScheduler::CScheduler::Init();
}


CMapRes::~CMapRes()
{
	this->CMapRes::Reset();
	m_pcCount = 0;
}


BOOL CMapRes::Load(const char* filename, int mapID, int mapType)
{
	memcpy_s(m_mapName, sizeof(m_mapName), filename, 16);
	m_mapID = mapID;
	m_mapType = mapType;

	char tempbuf[256];
	strcpy(tempbuf, this->GetLoadFileName().c_str());

	char seps[2+1];
	strcpy(seps, " .");

	const char* mapname = strtok(tempbuf, seps);
	if( mapname == NULL )
		return FALSE;

	char tempFileName[256];
	strcpy(tempFileName, "./mapfile/");
	strcat(tempFileName, mapname);
	strcat(tempFileName, ".rsw");

	FILE* cfp = fopen(g_pathData.CPathData::SetFileName(tempFileName), "rb");
	if( cfp == NULL )
		return FALSE;

	char magicId[4+1];
	strcpy(magicId, "GRSW");

	char magicBuf[4+1];
	fread(magicBuf, 4, 1, cfp);
	magicBuf[countof(magicBuf)-1] = '\0';

	if( strcmp(magicBuf, magicId) != 0 )
		return FALSE;

	unsigned char verMinor;
	unsigned char verMajor;
	fread(&verMajor, 1, 1, cfp);
	fread(&verMinor, 1, 1, cfp);

	if( verMajor == 2 && verMinor > 1 || verMajor > 2 )
		return FALSE;

	char nameBuf[40];
	fread(nameBuf, 40, 1, cfp);
	fread(nameBuf, 40, 1, cfp);

	if( verMajor == 1 && verMinor >= 4 || verMajor >= 2 )
		fread(nameBuf, 40, 1, cfp);

	fread(nameBuf, 40, 1, cfp);

	if( !(verMajor == 1 && verMinor >= 3 || verMajor >= 2) )
		return FALSE;

	float m_waterLevel;
	fread(&m_waterLevel, 4, 1, cfp);

	fclose(cfp);

	char checkSum[4+1];
	strcpy(checkSum, "GRAT");

	FILE* fp = fopen(this->GetLoadFileName().c_str(), "rb");
	if( fp == NULL )
	{
		char filedir[256];
		strcpy(filedir, "./mapfile/");
		strcat(filedir, this->GetLoadFileName().c_str());

		fp = fopen(g_pathData.CPathData::SetFileName(filedir), "rb");
		if( fp == NULL )
			return NULL;
	}

	char checkBuf[4+1];
	fread(&checkBuf, 4, 1, fp);
	checkBuf[countof(checkBuf)-1] = '\0';

	if( strcmp(checkBuf, checkSum) != 0 )
		return FALSE;

	unsigned char gatverMajor;
	unsigned char gatverMinor;
	fread(&gatverMajor, 1, 1, fp);
	fread(&gatverMinor, 1, 1, fp);

	if( !(gatverMajor == 1 && gatverMinor <= 2) )
		return 1; // unsupported gat version

	int w;
	int h;
	fread(&w, 4, 1, fp);
	fread(&h, 4, 1, fp);

	struct AttrCell
	{
		/* this+ 0 */ float h1;
		/* this+ 4 */ float h2;
		/* this+ 8 */ float h3;
		/* this+12 */ float h4;
		/* this+16 */ int flag; // enumCLICELLTYPE
	};

	AttrCell* cells = new AttrCell[w * h];
	fread(cells, w * h * sizeof(AttrCell), 1, fp);

	fclose(fp);

	m_height = h;
	m_width = w;
	m_TileInfo = new unsigned char[w * h];

	for( int j = 0; j < m_width; ++j )
	{
		for( int i = 0; i < m_height; ++i )
		{
			int pos = j + i * m_width;

			m_TileInfo[pos] = 0;

			if( cells[pos].flag == CLI_CELL_GAP )
			{
				m_TileInfo[pos] |= SVR_CELL_BLOCK;
				m_TileInfo[pos] |= SVR_CELL_ARROW;
			}
			else
			if( cells[pos].flag == CLI_CELL_WALL )
			{
				m_TileInfo[pos] |= SVR_CELL_BLOCK;
			}
			else // all others
			{
				m_TileInfo[pos] |= SVR_CELL_ARROW;
			}

			if( m_waterLevel < cells[pos].h1 )
			{
				m_TileInfo[pos] |= SVR_CELL_WATER;
			}
		}
	}

	m_pathFinder.CPathFinder::SetMap(this);
	delete[] cells;

	return TRUE;
}


BOOL CMapRes::UpdateTileInfo(int x, int y, int flag)
{
	if( x < 0 || y < 0 || x >= m_width || y >= m_height )
		return FALSE;

	int pos = x + y * m_width;

	m_TileInfo[pos] &= ~SVR_CELL_BLOCK;
	m_TileInfo[pos] &= ~SVR_CELL_ARROW;

	if( flag == CLI_CELL_GAP )
	{
		m_TileInfo[pos] |= SVR_CELL_BLOCK;
		m_TileInfo[pos] |= SVR_CELL_ARROW;
	}
	else
	if( flag == CLI_CELL_WALL )
	{
		m_TileInfo[pos] |= SVR_CELL_BLOCK;
	}
	else // all others
	{
		m_TileInfo[pos] |= SVR_CELL_ARROW;
	}

	return TRUE;
}


void CMapRes::Reset()
{
	if( m_TileInfo != NULL )
	{
		delete[] m_TileInfo;
		m_TileInfo = NULL;
	}

	if( m_mapPropertyCountPK != NULL )
	{
		delete m_mapPropertyCountPK;
		m_mapPropertyCountPK = NULL;
	}
}


void CMapRes::GetRandomPos(int& xPos, int& yPos, int minDis, int maxDis, unsigned long AID)
{
	int xdir = ( GetServerRandom(0, 20000) % 2 ) ? 1 : -1;
	int ydir = ( GetServerRandom(0, 20000) % 2 ) ? 1 : -1;

	for( int i = -1; i <= 1; ++i )
	{
		for( int j = -1; j <= 1; ++j )
		{
			if( i == 0 && j == 0 )
				continue; // skip center cell

			int range = maxDis - minDis;
			int x = xPos + i * xdir * (minDis + GetServerRandom(0, 20000) % max(1,range));
			int y = yPos + j * ydir * (minDis + GetServerRandom(0, 20000) % max(1,range));

			if( x <= 6 || x >= m_width - 6 || y <= 6 || y >= m_height - 6 )
				continue; // too close to the edge
			
			if( this->CMapRes::GetTileInfo(x, y) & SVR_CELL_BLOCK )
				continue; // non-walkable cell

			xPos = x;
			yPos = y;
			return; // found.
		}
	}

	return; // not found.
}


BOOL CMapRes::GetRandomPosByRange(int& xPos, int& yPos, int xRange, int yRange, unsigned long AID)
{
	int xdir = ( GetServerRandom(0, 20000) % 2 ) ? 1 : -1;
	int ydir = ( GetServerRandom(0, 20000) % 2 ) ? 1 : -1;

	for( int i = -1; i <= 1; ++i )
	{
		for( int j = -1; j <= 1; ++j )
		{
			if( i == 0 && j == 0 )
				continue; // skip center cell

			int x = xPos + xdir * i * GetServerRandom(0, 20000) % max(1,xRange);
			int y = yPos + ydir * j * GetServerRandom(0, 20000) % max(1,yRange);

			if( x <= 4 || x >= m_width - 4 || y <= 4 || y >= m_height - 4 )
				continue; // too close to the edge
			
			if( this->CMapRes::GetTileInfo(x, y) & SVR_CELL_BLOCK )
				continue; // non-walkable cell

			xPos = x;
			yPos = y;
			return TRUE; // found.
		}
	}

	return FALSE; // not found.
}


BOOL CMapRes::GetRandomPos(int& xPos, int& yPos)
{
	int x = 15 + GetServerRandom(0, 20000) % max(1, m_width - 30);
	int y = 15 + GetServerRandom(0, 20000) % max(1, m_height - 30);
	int count = 0;
	int loopCount = 3;
	
	for( count = 0; count < 50; ++count )
	{
		if( (this->CMapRes::GetTileInfo(x, y) & SVR_CELL_BLOCK) == 0 )
			break; // found walkable cell.

		loopCount += 7;

		x = 15 + loopCount * GetServerRandom(0, 20000) % max(1, m_width - 30);
		y = 15 + loopCount * GetServerRandom(0, 20000) % max(1, m_height - 30);
	}

	if( count == 50 || x < 5 || y < 5 || x > m_width || y > m_height )
	{
		xPos = 30;
		yPos = 30;
		return FALSE;
	}

	xPos = x;
	yPos = y;
	return TRUE;
}


void CMapRes::GetProprtyByteArray(BYTE* out_pArray, const int in_MaxLength)
{
	m_Property.CMapTypeProperty::GetByteArray(out_pArray, in_MaxLength);
}


int CMapRes::IsItPossible(int property)
{
	return m_Property.CMapTypeProperty::IsItPossible(property);
}


void CMapRes::Broadcast(const BROADCAST_INFO* in_pBROADCAST_INFO)
{
	if( in_pBROADCAST_INFO == NULL || in_pBROADCAST_INFO->str == NULL )
		return;

	const int chatlen = min(strlen(in_pBROADCAST_INFO->str), 256);

	if( in_pBROADCAST_INFO->packetType == HEADER_ZC_BROADCAST )
	{
		int packetlen = sizeof(PACKET_ZC_BROADCAST) + chatlen + 1;
		PACKET_ZC_BROADCAST* pPacket = (PACKET_ZC_BROADCAST*)_malloca(packetlen);
		if( pPacket == NULL )
			return;

		pPacket->PacketType = HEADER_ZC_BROADCAST;
		pPacket->PacketLength = packetlen;
		memcpy_s(pPacket->Text, packetlen - sizeof(PACKET_ZC_BROADCAST), in_pBROADCAST_INFO->str, chatlen);
		pPacket->Text[chatlen] = '\0';
		this->CMapRes::Send(pPacket->PacketLength, (char*)pPacket, in_pBROADCAST_INFO->broadcastType, in_pBROADCAST_INFO->extra);

		_freea(pPacket);
	}
	else // ( in_pBROADCAST_INFO->packetType == HEADER_ZC_BROADCAST2 )
	{
		int packetlen = sizeof(PACKET_ZC_BROADCAST2) + chatlen + 1;
		PACKET_ZC_BROADCAST2* pPacket = (PACKET_ZC_BROADCAST2*)_malloca(packetlen);
		if( pPacket == NULL )
			return;

		pPacket->PacketLength = packetlen;
		pPacket->PacketType = HEADER_ZC_BROADCAST2;
		pPacket->fontColor = in_pBROADCAST_INFO->fontColor;
		pPacket->fontType = in_pBROADCAST_INFO->fontType;
		pPacket->fontSize = in_pBROADCAST_INFO->fontSize;
		pPacket->fontAlign = in_pBROADCAST_INFO->fontAlign;
		pPacket->fontY = in_pBROADCAST_INFO->fontY;
		memcpy_s(pPacket->Text, packetlen - sizeof(PACKET_ZC_BROADCAST2), in_pBROADCAST_INFO->str, chatlen);
		pPacket->Text[chatlen] = '\0';
		this->CMapRes::Send(pPacket->PacketLength, (char*)pPacket, in_pBROADCAST_INFO->broadcastType, in_pBROADCAST_INFO->extra);

		_freea(pPacket);
	}
}


void CMapRes::Send(int len, const char* buf, int broadcastType, int data)
{
	std::vector<CCharacter*>** sectionListPointer = m_sectionMgr.CSectionMgr::GetSectionList();
	int n = m_sectionMgr.CSectionMgr::GetSectionSize();
	std::vector<unsigned long> tmp;

	for( int i = 0; i < n; ++i )
	{
		std::vector<CCharacter*>* sectionList = sectionListPointer[i];

		for( std::vector<CCharacter*>::const_iterator iter = sectionList->begin(); iter != sectionList->end(); ++iter )
		{
			CCharacter* ch = *iter;
			if( ch == NULL || ch->GetType() != PC_TYPE || broadcastType == 1 )
				continue;

			int id;
			ch->GetParameterValue(VAR_GDID, id);
			if( id != data )
				continue;

			int mapID;
			ch->GetParameterValue(VAR_MAPID, mapID);
			if( mapID != m_mapID )
				continue;

			tmp.push_back(ch->GetAccountID());
		}
	}

	for( std::vector<unsigned long>::const_iterator iter = tmp.begin(); iter != tmp.end(); ++iter )
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, *iter, CM_SEND_PACKET, len, (int)buf, 0, 0);

	tmp.clear();
}


BOOL CMapRes::IsMovableCell(int x, int y) const
{
	if( x < 0 || y < 0 || x >= m_width || y >= m_height )
		return FALSE;

	if( (this->CMapRes::GetTileInfo(x, y) & SVR_CELL_BLOCK) == SVR_CELL_BLOCK )
		return FALSE;

	return TRUE;
}


BOOL CMapRes::IsArrowCrossCell(int x, int y)
{
	if( x < 0 || y < 0 || x >= m_width || y >= m_height )
		return FALSE;

	if( (this->CMapRes::GetTileInfo(x, y) & SVR_CELL_ARROW) != SVR_CELL_ARROW )
		return FALSE;

	return TRUE;
}


BOOL CMapRes::IsWaterCell(int x, int y)
{
	if( x < 0 || y < 0 || x >= m_width || y >= m_height )
		return FALSE;

	if( (this->CMapRes::GetTileInfo(x, y) & SVR_CELL_WATER) != SVR_CELL_WATER )
		return FALSE;

	return TRUE;
}


BOOL CMapRes::IsValidPosition(int x, int y)
{
	return ( x >= 5 && y >= 5 && x <= m_width - 5 && y <= m_height - 5 );
}


BOOL CMapRes::IsExsistCells(int xPos, int yPos, int range, unsigned long property)
{
	for( int dx = -range; dx <= range; ++dx )
	{
		for( int dy = -range; dy <= range; ++dy )
		{
			if( property & SVR_CELL_BLOCK )
			{
				if( this->CMapRes::GetTileInfo(xPos + dx, yPos + dy) & SVR_CELL_BLOCK )
					return TRUE; // found!
			}
			if( property & SVR_CELL_ARROW )
			{
				if( this->CMapRes::GetTileInfo(xPos + dx, yPos + dy) & SVR_CELL_ARROW )
					return TRUE; // found!
			}
		}
	}

	return FALSE; // no matching cells found.
}


BOOL CMapRes::IsConnected(int sx, int sy, int dx, int dy)
{
	if( dx < 0 || dy < 0 || dx >= m_width || dy >= m_height )
		return FALSE;

	if( this->CMapRes::GetTileInfo(dx, dy) & SVR_CELL_BLOCK )
		return FALSE;

	if( sx != dx && sy != dy )
	{// diagonal
		if( this->CMapRes::GetTileInfo(sx, dy) & SVR_CELL_BLOCK )
			return FALSE;

		if( this->CMapRes::GetTileInfo(dx, sy) & SVR_CELL_BLOCK )
			return FALSE;
	}

	return TRUE;
}


bool CMapRes::IsDirectPath2(const int in_sourceXpos, const int in_sourceYpos, const int in_targetXpos, const int in_targetYpos, const unsigned char in_BlockCellMask)
{
	int sourceXpos = in_sourceXpos;
	int sourceYpos = in_sourceYpos;
	int targetXpos = in_targetXpos;
	int targetYpos = in_targetYpos;

	if( in_sourceXpos == in_targetXpos && in_sourceYpos == in_targetYpos )
		return true;

	if( abs(in_targetXpos - in_sourceXpos) <= abs(in_targetYpos - in_sourceYpos) )
	{
		if( in_sourceYpos > in_targetYpos )
		{
			sourceXpos = in_targetXpos;
			targetXpos = in_sourceXpos;
			sourceYpos = in_targetYpos;
			targetYpos = in_sourceYpos;
		}

		if( this->CMapRes::GetTileInfo(sourceXpos, sourceYpos) & SVR_CELL_BLOCK )
			return false;

		for( int dy = 1; dy < targetYpos - sourceYpos; ++dy )
		{
			float slope = (float)(targetXpos - sourceXpos) / (float)(targetYpos - sourceYpos);
			int xPos = int(sourceXpos + dy * slope);
			int yPos = int(sourceYpos + dy);

			if( this->CMapRes::GetTileInfo(xPos, yPos) & SVR_CELL_BLOCK )
				return false;
		}

		if( this->CMapRes::GetTileInfo(targetXpos, targetYpos) & SVR_CELL_BLOCK )
			return false;

		return true;
	}
	else
	{
		if( in_sourceXpos > in_targetXpos )
		{
			sourceXpos = in_targetXpos;
			targetXpos = in_sourceXpos;
			sourceYpos = in_targetYpos;
			targetYpos = in_sourceYpos;
		}

		if( this->CMapRes::GetTileInfo(sourceXpos, sourceYpos) & SVR_CELL_BLOCK )
			return false;

		for( int dx = 1; dx < targetXpos - sourceXpos; ++dx )
		{
			float slope = (float)(targetYpos - sourceYpos) / (float)(targetXpos - sourceXpos);
			int xPos = int(sourceXpos + dx);
			int yPos = int(sourceYpos + dx * slope);
 
			if( this->CMapRes::GetTileInfo(xPos, yPos) & SVR_CELL_BLOCK )
				return false;
		}

		if( this->CMapRes::GetTileInfo(targetXpos, targetYpos) & SVR_CELL_BLOCK )
			return false;

		return true;
	}
}


BOOL CMapRes::IsDirectPath(int x1, int y1, int x2, int y2, BOOL isClose)
{
	if( abs(x2 - x1) < 2 && abs(y2 - y1) < 2 )
		return TRUE;

	if( abs(x2 - x1) <= abs(y2 - y1) )
	{
		if( y1 > y2 )
		{
			std::swap(x1, x2);
			std::swap(y1, y2);
		}

		for( int dy = 1; dy < y2 - y1; ++dy )
		{
			float slope = (float)(x2 - x1) / (float)(y2 - y1);
			int xPos = int(x1 + dy * slope);
			int yPos = int(y1 + dy);

			if( !this->CMapRes::IsArrowCrossCell(xPos, yPos) )
				return FALSE;

			if( isClose && !this->CMapRes::IsMovableCell(xPos, yPos) )
				return FALSE;
		}

		return TRUE;
	}
	else
	{
		if( x1 > x2 )
		{
			std::swap(x1, x2);
			std::swap(y1, y2);
		}

		for( int dx = 1; dx < x2 - x1; ++dx )
		{
			float slope = (float)(y2 - y1) / (float)(x2 - x1);
			int xPos = int(x1 + dx);
			int yPos = int(y1 + dx * slope);

			if( !this->CMapRes::IsArrowCrossCell(xPos, yPos) )
				return FALSE;

			if( isClose && !this->CMapRes::IsMovableCell(xPos, yPos) )
				return FALSE;
		}

		return TRUE;
	}
}


namespace {
bool InWarpNPCArea(std::vector<CNPC*>* in_WarpNPCList, int in_myXpos, int in_myYpos)
{
	for( std::vector<CNPC*>::iterator iter = in_WarpNPCList->begin(); iter != in_WarpNPCList->end(); ++iter )
	{
		CNPC* warpNPC = *iter;

		int npcXPos = 0;
		int npcYPos = 0;
		int npcXSize = 0;
		int npcYSize = 0;
		warpNPC->GetParameterValue(VAR_CURXPOS, npcXPos);
		warpNPC->GetParameterValue(VAR_CURYPOS, npcYPos);
		warpNPC->GetParameterValue(VAR_NPCXSIZE, npcXSize);
		warpNPC->GetParameterValue(VAR_NPCYSIZE, npcYSize);

		if( abs(npcXPos - in_myXpos) <= npcXSize + 1 && abs(npcYPos - in_myYpos) <= npcYSize + 1 )
			return true; // found a warp.
	}

	return false; // no warps found.
}
}; // namespace


BOOL CMapRes::GetRandomPosExceptWarp(int& io_xPos, int& io_yPos)
{
	const int startXPos = io_xPos;
	const int startYPos = io_yPos;

	std::vector<CNPC*> warpNpcList = CCharacterMgr::GetObj()->CCharacterMgr::GetWarpNpcList(this);
	for( int cnt = 1; cnt <= 3; ++cnt )
	{
		if( !this->CMapRes::GetRandomPos(io_xPos, io_yPos) )
			break; // free cell lookup failed

		if( !InWarpNPCArea(&warpNpcList, io_xPos, io_yPos) )
			return TRUE; // found!
	}

	io_xPos = startXPos;
	io_yPos = startYPos;
	this->CMapRes::GetRandomPos(io_xPos, io_yPos, 2, 2, 0);
	return TRUE; // give up and use an adjacent cell.
}


int CMapRes::GetCellType(int x, int y)
{
	if( !this->CMapRes::IsValidPosition(x, y) )
		return CLI_CELL_WALL;

	unsigned char type = m_TileInfo[x + y * m_width];
	if( !(type & SVR_CELL_BLOCK) )
		return CLI_CELL_GROUND;
	else
	if( !(type & SVR_CELL_ARROW) )
		return CLI_CELL_WALL;
	else
	{
		return CLI_CELL_GAP;
	}
}


bool CMapRes::IsPropertyBlockSkill(const int in_SKID, const int in_ObjType)
{
	if( this == NULL )
		return false;

	return m_Property.CMapTypeProperty::isBlockSkill(in_SKID, in_ObjType);
}


bool CMapRes::IsPropertyBlockItem(const int in_ITID)
{
	if( this == NULL )
		return false;

	return m_Property.CMapTypeProperty::isBlockItem(in_ITID);
}


int CMapRes::GetPropertyTrapDurationPercent(const int in_SKID)
{
	if( this == NULL )
		return 100;

	return m_Property.CMapTypeProperty::GetTrapDurationPercent(in_SKID);
}


int CMapRes::GetSkillDamagePercent(const int in_SKID)
{
	if( this == NULL )
		return 100;

	return m_Property.CMapTypeProperty::GetSkillDamagePercent(in_SKID);
}


bool CMapRes::IsPropertyBlockEquipItem(const int in_ITID)
{
	if( this == NULL )
		return false;

	return m_Property.CMapTypeProperty::isBlockEquipItem(in_ITID);
}


bool CMapRes::IsPropertyBlockBuff(const int in_BuffID)
{
	if( this == NULL )
		return false;

	return m_Property.CMapTypeProperty::isBlockBuff(in_BuffID);
}


bool CMapRes::AllocMapPropertyCountPK()
{
	m_mapPropertyCountPK = new(std::nothrow) CMapPropertyCountPK();
	if( m_mapPropertyCountPK == NULL )
		return false;

	return true;
}


bool CMapRes::UpdateWinPoint(unsigned long AID, int winpoint)
{
	if( m_mapPropertyCountPK == NULL )
		return false;

	return m_mapPropertyCountPK->CMapPropertyCountPK::UpdateWinPoint(AID, winpoint);
}


bool CMapRes::DeleteWinPoint(unsigned long AID)
{
	if( m_mapPropertyCountPK == NULL )
		return false;

	return m_mapPropertyCountPK->CMapPropertyCountPK::DeleteWinPoint(AID);
}


BOOL CMapRes::GetValidPos(int& io_xPos, int& io_yPos)
{
	if( !this->CMapRes::IsMovableCell(io_xPos, io_yPos) )
	{
		int cnt;
		for( cnt = 1; cnt <= 2; ++cnt )
		{
			this->CMapRes::GetRandomPos(io_xPos, io_yPos, 2, 2, 0);

			if( this->CMapRes::IsMovableCell(io_xPos, io_yPos) )
				break; // found walkable cell.
		}

		if( cnt > 2 )
			return FALSE;
	}

	std::vector<CNPC*> npcList = CCharacterMgr::GetObj()->CCharacterMgr::GetWarpNpcList(this);
	if( InWarpNPCArea(&npcList, io_xPos, io_yPos) )
		return FALSE;

	return TRUE;
}


void CMapRes::Process()
{
	m_Scheduler.MapResScheduler::CScheduler::Process(this);
}


unsigned long CMapRes::InsertSchedule(std::tr1::shared_ptr<MapResScheduler::CTask>& in_TaskPtr)
{
	m_Scheduler.MapResScheduler::CScheduler::Insert(in_TaskPtr, 00000000); //TODO: unknown value
	return in_TaskPtr->MapResScheduler::CTask::GetIdentity();
}


void CMapRes::AddMobTombInfo(const unsigned long in_NAID, const short in_hour, const short in_min, const std::string& in_MPVName, const std::string& in_MobName)
{
	m_MobTombList.insert(std::make_pair(in_NAID, stMobTombInfo(in_hour, in_min, in_MPVName, in_MobName)));
}


void CMapRes::DeleteMobTombInfo(const unsigned long in_NAID)
{
	m_MobTombList.erase(in_NAID);
}


const stMobTombInfo& CMapRes::GetMobTombInfo(const unsigned long in_NAID) const
{
	static stMobTombInfo empty;

	std::map<unsigned long,stMobTombInfo>::const_iterator iter = m_MobTombList.find(in_NAID);
	if( iter == m_MobTombList.end() )
		return empty;

	return iter->second;
}


const bool CMapRes::isInstantMap() const
{
	return false;
}


void CMapRes::OnTimer()
{
}


unsigned long CMapRes::GetGDID()
{
	return 0;
}


const char* CMapRes::GetName() const
{
	return m_mapName;
}


int CMapRes::GetID() const
{
	return m_mapID;
}


int CMapRes::GetType() const
{
	return m_mapType;
}


int CMapRes::GetHeight() const
{
	return m_height;
}


int CMapRes::GetWidth() const
{
	return m_width;
}


BOOL CMapRes::IsValidCell(int xPos, int yPos) const
{
	return ( xPos >= 0 && yPos >= 0 && xPos < m_width && yPos < m_height );
}


std::vector<CCharacter*>* CMapRes::GetSectionByCellPos(int xCellPos, int yCellPos)
{
	return m_sectionMgr.CSectionMgr::GetSectionByCellPos(xCellPos, yCellPos);
}


BOOL CMapRes::GetEmptyPosition(unsigned long AID, int& xPos, int& yPos)
{
	return m_sectionMgr.CSectionMgr::GetEmptyPosition(AID, xPos, yPos);
}


BOOL CMapRes::AddCharacter(int xCellPos, int yCellPos, CCharacter* character)
{
	return m_sectionMgr.CSectionMgr::AddCharacter(xCellPos, yCellPos, character);
}


void CMapRes::RemoveCharacter(CCharacter* character)
{
	m_sectionMgr.CSectionMgr::RemoveCharacter(character);
}


int CMapRes::GetTotalSectionSize()
{
	return m_sectionMgr.CSectionMgr::GetTotalSectionSize();
}


BOOL CMapRes::MoveCharacter(std::vector<CCharacter*>* src, std::vector<CCharacter*>* dest, CCharacter* character)
{
	return m_sectionMgr.CSectionMgr::MoveCharacter(src, dest, character);
}


int CMapRes::MoveChracter(std::vector<CCharacter*>* src, std::vector<CCharacter*>::iterator& iter, int x, int y, CCharacter* character)
{
	return m_sectionMgr.CSectionMgr::MoveChracter(src, iter, x, y, character);
}


void CMapRes::GetNeighborhoodSections(int xPos, int yPos, int range, NEIGHBORHOOD_SECTION* result)
{
	m_sectionMgr.CSectionMgr::GetNeighborhoodSections(xPos, yPos, range, result);
}


int CMapRes::GetSectionSize()
{
	return m_sectionMgr.CSectionMgr::GetSectionSize();
}


std::vector<CCharacter*>** CMapRes::GetSectionList()
{
	return m_sectionMgr.CSectionMgr::GetSectionList();
}


BOOL CMapRes::FindPath(DWORD startTime, int sx, int sy, int xM, int yM, int dx, int dy, int speedFactor, CPathInfo* result)
{
	return m_pathFinder.CPathFinder::FindPath(startTime, sx, sy, xM, yM, dx, dy, speedFactor, result);
}


BOOL CMapRes::IsEmptyPos(unsigned long AID, int xPos, int yPos)
{
	return m_sectionMgr.CSectionMgr::IsEmptyPos(AID, xPos, yPos);
}


bool CMapRes::IsVillage()
{
	return ( m_mapType == MAPTYPE_VILLAGE || m_mapType == MAPTYPE_VILLAGE_IN );
}


void CMapRes::SectionMgrInit()
{
	m_sectionMgr.CSectionMgr::Init(m_mapName, m_width, m_height, SECTION_SIZE, this);
}


std::string CMapRes::GetLoadFileName()
{
	return m_mapName;
}


bool CMapRes::IsBattleField()
{
	return false;
}


bool CMapRes::IsAgit()
{
	return false;
}


unsigned char CMapRes::GetTileInfo(int xPos, int yPos) const
{
	if( xPos < 0 || yPos < 0 || xPos >= m_width || yPos >= m_height )
		return SVR_CELL_BLOCK;

	return m_TileInfo[xPos + yPos * m_width];
}
