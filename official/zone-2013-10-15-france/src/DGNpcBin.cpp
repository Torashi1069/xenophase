#include "DGNpcBin.h"


CDGNpcBin::CDGNpcBin()
{
}


CDGNpcBin::~CDGNpcBin()
{
}


void CDGNpcBin::ClearBinBuff()
{
	m_binBuf.CBinBuf::Clear();
}


bool CDGNpcBin::LoadScriptBin(const char* mapName)
{
	char name[256] = {};
	sprintf_s(name, countof(name), ".\\scriptbin\\%s.bin", mapName);
	return m_binBuf.CBinBuf::Load(name);
}


CBinBuf* CDGNpcBin::GetBinBuff()
{
	return &m_binBuf;
}
