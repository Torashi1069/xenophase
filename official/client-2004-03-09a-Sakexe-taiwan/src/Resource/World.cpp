#include "GameWorld.h"
#include "Globals.h"
#include "RagEffect2.h"
#include "Base/ResMgr.h"
#include "Resource/World.h"
#define _USE_MATH_DEFINES
#include <math.h>


C3dWorldRes::C3dWorldRes(Exemplar __formal, const char* resid, const char* baseDir) // line 23 (World.h)
{
	g_resMgr().CResMgr::RegisterType(resid, baseDir, this);
}


C3dWorldRes::C3dWorldRes(void) // line 22
: m_CalculatedNode(0)
{
}


hook_method<CRes* (C3dWorldRes::*)(void) const> C3dWorldRes::_Clone(SAKEXE, "C3dWorldRes::Clone");
CRes* C3dWorldRes::Clone(void) const // line 23 (Resource/World.h)
{
	return (this->*_Clone)();

	return new C3dWorldRes();
}


hook_method<void (C3dWorldRes::*)(void)> C3dWorldRes::_Reset(SAKEXE, "C3dWorldRes::Reset");
void C3dWorldRes::Reset(void) // line 27
{
	return (this->*_Reset)();

	for( mystd::list<C3dWorldRes::actorInfo*>::iterator it = m_3dActors.begin(); it != m_3dActors.end(); ++it )
		delete *it;
	m_3dActors.clear();

	for( mystd::list<C3dWorldRes::effectSrcInfo*>::iterator it = m_particles.begin(); it != m_particles.end(); ++it )
		delete *it;
	m_particles.clear();

	for( mystd::list<C3dWorldRes::soundSrcInfo*>::iterator it = m_sounds.begin(); it != m_sounds.end(); ++it )
		delete *it;
	m_sounds.clear();

	if( m_CalculatedNode != NULL )
	{
		delete m_CalculatedNode;
		m_CalculatedNode = NULL;
	}
}

/// 
/// Format:
///   File         := Header Objects (v2.1+)SceneGraph
///     Header     := "GRSW".4b <verMajor>.1b <verMinor>.1b <iniFile>.40s <gndFile>.40s (v1.4+)<gatFile>.40s <scrFile>.40s (v1.3+)<waterLevel>.4f (v1.8+)[<waterType>.4i <waveHeight>.4f <waveSpeed>.4f <wavePitch>.4f].16b (v1.9+)<waterAnimSpeed>.4i (v1.5+)[<lightLongitude>.4i <lightLatitude>.4i <diffuseCol>.vec3d, <ambientCol>.vec3d].32b (v1.7+)<unknown>.4f (v1.6+)[<groundTop>.4i <groundBottom>.4i <groundLeft>.4i <groundRight>.4i].16b
///     Objects    := <count>.4i Object*
///     SceneGraph := ...
///   Object       := Model | Light | Sound | Effect
///     Model      := (v1.3+)[<name>.40s <animType>.4i <animSpeed>.4f <blockType>.4i].52b <modelName>.80s <nodeName>.80s <pos>.vec3d <rot>.vec3d <scale>.vec3d
///     Light      := <name>.40s <pos>.vec3d <red>.4i <green>.4i <blue>.4i <range>.4f
///     Sound      := <name>.80s <waveName>.80s <pos>.vec3d <vol>.4f <width>.4i <height>.4i <range>.4f (v2.0+)<cycle>.4f
///     Effect     := <name>.80s <pos>.vec3d <type>.4i <emitSpeed>.4f [<param>.4f][4]
/// 
hook_method<bool (C3dWorldRes::*)(const char* fName)> C3dWorldRes::_Load(SAKEXE, "C3dWorldRes::Load");
bool C3dWorldRes::Load(const char* fName) // line 66
{
	return (this->*_Load)(fName);

	this->Reset();

	CFile fp;
	if( !fp.CFile::Open(fName, 0) )
		return false;

	// 1.2  4b  magic "GRSW"
	char magicBuf[4];
	fp.CFile::Read(magicBuf, 4);
	if( strncmp(magicBuf, "GRSW", 4) != 0 )
	{
		ErrorMsg("Invalid Format");
		return false;
	}

	// 1.2  1b  major version
	unsigned char verMajor;
	fp.CFile::Read(&verMajor, 1);

	// 1.2  1b  minor version
	unsigned char verMinor;
	fp.CFile::Read(&verMinor, 1);

	if( (verMajor == 2 && verMinor > 1) || verMajor > 2 )
	{
		ErrorMsg("C3dWorldRes :: Unsupported Version");
		return false;
	}

	m_verMinor = verMinor;
	m_verMajor = verMajor;

	// 1.2  40s  ini file
	char ininameBuf[40];
	fp.CFile::Read(ininameBuf, 40);

	// 1.2  40s  gnd file
	char gndnameBuf[40];
	fp.CFile::Read(gndnameBuf, 40);
	m_gndFile = gndnameBuf;

	// 1.4  40s  gat file
	if( (verMajor == 1 && verMinor >= 4) || verMajor >= 2 )
	{
		char gatnameBuf[40];
		fp.CFile::Read(gatnameBuf, 40);
		m_attrFile = gatnameBuf;
	}

	// 1.2  40s  scr file
	char scrnameBuf[40];
	fp.CFile::Read(scrnameBuf, 40);
	m_scrFile = scrnameBuf;

	// 1.3  4f  water level
	if( (verMajor == 1 && verMinor >= 3) || verMajor >= 2 )
		fp.CFile::Read(&m_waterLevel, 4);

	// 1.8  16b  waterType, waveHeight, waveSpeed, wavePitch
	if( (verMajor == 1 && verMinor >= 8 ) || verMajor >= 2 )
	{
		fp.CFile::Read(&m_waterType, 4);
		fp.CFile::Read(&m_waveHeight, 4);
		fp.CFile::Read(&m_waveSpeed, 4);
		fp.CFile::Read(&m_wavePitch, 4);
	}
	else
	{
		m_waterType = 0;
		m_waveHeight = 1.0;
		m_waveSpeed = 2.0;
		m_wavePitch = 50.0;
	}

	// 1.9  4i  water animation speed
	if( (verMajor == 1 && verMinor >= 9 ) || verMajor >= 2 )
		fp.CFile::Read(&m_waterAnimSpeed, 4);
	else
		m_waterAnimSpeed = 3;

	// 1.5  32b  lightLongitude, lightLatitude, diffuseCol, ambientCol
	if( (verMajor == 1 && verMinor >= 5) || verMajor >= 2 )
	{
		fp.CFile::Read(&m_lightLongitude, 4);
		fp.CFile::Read(&m_lightLatitude, 4);
		fp.CFile::Read(&m_diffuseCol, 12);
		fp.CFile::Read(&m_ambientCol, 12);
	}
	else
	{
		m_lightLatitude = 45;
		m_lightLongitude = 45;
		m_diffuseCol.x = 1.0f;
		m_diffuseCol.y = 1.0f;
		m_diffuseCol.z = 1.0f;
		m_ambientCol.x = 0.3f;
		m_ambientCol.y = 0.3f;
		m_ambientCol.z = 0.3f;
	}

	matrix r;
	r.matrix::MakeXRotation(float(m_lightLatitude * M_PI / 180));
	r.matrix::AppendYRotation(float(m_lightLongitude * M_PI / 180));
	m_lightDir.x = float((r.v31 + r.v11) * 0.0 + r.v41 + r.v21);
	m_lightDir.y = float((r.v32 + r.v12) * 0.0 + r.v42 + r.v22);
	m_lightDir.z = float((r.v33 + r.v13) * 0.0 + r.v43 + r.v23);

	// 1.7  4f  unknown
	if( (verMajor == 1 && verMinor >= 7) || verMajor >= 2 )
	{
		float unknown;
		fp.CFile::Read(&unknown, 4);
	}

	// 1.6  16b  groundTop, groundBottom, groundLeft, groundRight
	if( (verMajor == 1 && verMinor >= 6) || verMajor >= 2 )
	{
		fp.CFile::Read(&m_groundTop, 4);
		fp.CFile::Read(&m_groundBottom, 4);
		fp.CFile::Read(&m_groundLeft, 4);
		fp.CFile::Read(&m_groundRight, 4);
	}
	else
	{
		m_groundTop = -500;
		m_groundBottom = 500;
		m_groundLeft = -500;
		m_groundRight = 500;
	}

	int len;
	fp.CFile::Read(&len, 4);

	for( int i = 0; i < len; ++i )
	{
		int type;
		fp.CFile::Read(&type, 4);

		switch( type )
		{
		case 1:
		{// Model
			char nameBuf[40];
			int animType;
			float animSpeed;
			int blockType;

			if( (verMajor == 1 && verMinor >= 3) || verMajor >= 2 )
			{
				fp.CFile::Read(nameBuf, 40);
				fp.CFile::Read(&animType, 4);
				fp.CFile::Read(&animSpeed, 4);
				fp.CFile::Read(&blockType, 4);

				if( animSpeed <= 0.0 && animSpeed > 100.0 )
					animSpeed = 1.0;
			}
			else
			{
				strcpy(nameBuf, scrnameBuf); //FIXME: uninitialized, stack variable overlap in official code
				animType = 0;
				blockType = 0;
				animSpeed = 1.0;
			}

			struct tmpActorInfo
			{
				/* this+  0 */ char modelName[80];
				/* this+ 80 */ char nodeName[80];
				/* this+160 */ vector3d pos;
				/* this+172 */ vector3d rot;
				/* this+184 */ vector3d scale;
			};

			tmpActorInfo tmpInfo;
			fp.CFile::Read(&tmpInfo, 196);
			C3dWorldRes::actorInfo* Info = new C3dWorldRes::actorInfo;
			strcpy(Info->name, nameBuf);
			strcpy(Info->modelName, tmpInfo.modelName);
			strcpy(Info->nodeName, tmpInfo.nodeName);
			Info->animSpeed = animSpeed;
			Info->animType = animType;
			Info->blockType = blockType;
			Info->pos.x = tmpInfo.pos.x;
			Info->pos.y = tmpInfo.pos.y;
			Info->pos.z = tmpInfo.pos.z;
			Info->rot.x = tmpInfo.rot.x;
			Info->rot.y = tmpInfo.rot.y;
			Info->rot.z = tmpInfo.rot.z;
			Info->scale.x = tmpInfo.scale.x;
			Info->scale.y = tmpInfo.scale.y;
			Info->scale.z = tmpInfo.scale.z;
			m_3dActors.push_back(Info);
		}
		break;
		case 2:
		{// Light Source
			char Buf[108];
			fp.CFile::Read(Buf, 108);
		}
		break;
		case 3:
		{// Sound Source
			if( verMajor < 2 )
			{
				C3dWorldRes::soundSrcInfo_V19 Info_V19;
				fp.CFile::Read(&Info_V19, 188);
				C3dWorldRes::soundSrcInfo* Info = new C3dWorldRes::soundSrcInfo;
				strncpy(Info->name, Info_V19.name, sizeof(Info->name)-1);
				strncpy(Info->waveName, Info_V19.waveName, sizeof(Info->waveName)-1);
				Info->pos.x = Info_V19.pos.x;
				Info->pos.y = Info_V19.pos.y;
				Info->pos.z = Info_V19.pos.z;
				Info->vol = Info_V19.vol;
				Info->width = Info_V19.width;
				Info->height = Info_V19.height;
				Info->range = Info_V19.range;
				Info->cycle = 4.0;
				m_sounds.push_back(Info);
			}
			else
			{
				C3dWorldRes::soundSrcInfo* Info = new C3dWorldRes::soundSrcInfo;
				fp.CFile::Read(Info, 192);
				m_sounds.push_back(Info);
			}
		}
		break;
		case 4:
		{// Effect Source
			C3dWorldRes::effectSrcInfo* Info = new C3dWorldRes::effectSrcInfo;
			fp.CFile::Read(Info, 116);
			m_particles.push_back(Info);
		}
		break;
		default:
			Trace("not implemented type == %d (%d/%d)\n", type, i + 1, len);
		break;
		}
	}

	// 2.1  ?  scene graph (quadtree)
	if( verMajor == 2 && verMinor == 1 )
	{
		m_CalculatedNode = new SceneGraphNode();
		m_CalculatedNode->SceneGraphNode::Build(0);
		m_CalculatedNode->SceneGraphNode::LoadSceneGraph(&fp, 0);
		Trace("SceneGraphNode Load.");
	}

	fp.CFile::Close();

	if( g_isLightMap != 1 )
	{
		m_ambientCol.x = float(m_ambientCol.x * 1.5);
		m_ambientCol.y = float(m_ambientCol.y * 1.5);
		m_ambientCol.z = float(m_ambientCol.z * 1.5);

		if( m_ambientCol.x > 1.0 )
			m_ambientCol.x = 1.0;

		if( m_ambientCol.y > 1.0 )
			m_ambientCol.y = 1.0;

		if( m_ambientCol.z > 1.0 )
			m_ambientCol.z = 1.0;
	}

	g_Weather.CWeather::SetAmbient(m_ambientCol);
	g_Weather.CWeather::SetDiffuse(m_diffuseCol);
	g_Weather.CWeather::SetMaxDiffuse(m_diffuseCol);
	g_Weather.CWeather::SetNightDegree();

	return true;
}
