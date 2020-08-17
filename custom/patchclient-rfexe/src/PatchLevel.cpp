#include "PatchLevel.h"
#include "patchclient.h" // PN_PATCHLEVELFILE, PN_PATCHLEVELFILE_OLD
#include <stdio.h>


PatchLevel::PatchLevel()
{
	m_level = 0;
	m_loaded = false;
}


PatchLevel::~PatchLevel()
{
}


bool PatchLevel::Get(unsigned int* out_level)
{
	if( !m_loaded && !this->Load() )
		return false;

	*out_level = m_level;
	return true;
}


bool PatchLevel::Set(unsigned int new_level)
{
	m_level = new_level;
	m_loaded = true;
	return this->Save();
}


bool PatchLevel::Load()
{
	unsigned int level = 0;

	FILE* fp = fopen(PN_PATCHLEVELFILE, "rb");
	if( fp != NULL )
	{
		fread(&level, sizeof(level), 1, fp);
		fclose(fp);
	}

	// Check to see if old file still exists if ActualPatchLevel is zero
	// since UAC can't write INF to VirtualStore due to stupid security.
	if( level == 0 )
	{
		FILE* fp = fopen(PN_PATCHLEVELFILE_OLD, "rb");
		if( fp != NULL )
		{
			fread(&level, sizeof(level), 1, fp);
			fclose(fp);
		}
	}

	m_level = level;
	m_loaded = true;
	return true;
}


bool PatchLevel::Save()
{
	FILE* fp = fopen(PN_PATCHLEVELFILE, "wb");
	if( fp == NULL )
		return false;

	if( fwrite(&m_level, sizeof(m_level), 1, fp) != 1 )
	{
		fclose(fp);
		return false;
	}

	fclose(fp);
	return true;
}
