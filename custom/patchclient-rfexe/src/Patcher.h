#pragma once
#include "PatchLevel.h"
#include "PatchList.h"
#include "Internet.h"


class Patcher
{
public:
	bool Run();

private:
	unsigned int level();
	bool checkPatchAllow();
	bool getPatchList(patchlist_t& out_list);
	bool downloadPatches(const patchlist_t& list);
	bool applyPatches(const patchlist_t& list);

	static bool unpackRGZ(const char* filename);
	static bool mergeGRF(const char* filename);
	static bool isClientRunning();
	static void updateDownloadProgress(const char* filename, DWORD current, DWORD total, DWORD speed_bps);

private:
	PatchLevel m_level; // current patch level
	Internet m_net; // internet connection
};
