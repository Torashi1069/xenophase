#include "Patcher.h"
#include "Internet.h"
#include "patchclient.h" // PN_*
#include "rgz.h" // rgz_unpack()
#include "Signature.h" // Signature::Verify()
#include "SubWCRev.h" // SVN_REV, SVN_DATE
#include "WndProc.h" // pmc_*()
#include <autorelease/AutoRelease.hpp>
#include <libgrf/libgrf.h>
#include <platform/disk.h> // stat()


bool Patcher::Run()
{
	pmc_setstatusmsg("Getting PatchLevel");
	if( level() == 0 ) // also loads it into cache
	{
#ifndef _DEBUG
		pmc_setstatusmsg("Error: Unable to read PatchLevel file");
		return false;
#endif
	}

	pmc_setstatusmsg("Opening Internet Context");
	if( !m_net.Open("Patch Client r"SVN_REV" "SVN_DATE) )
	{
		pmc_setstatusmsg("Error: Can't open InternetContext");
		return false;
	}

	if( !this->checkPatchAllow() )
		return false;

	patchlist_t patchlist;
	if( !this->getPatchList(patchlist) )
		return false;

	if( !this->downloadPatches(patchlist) )
		return false;

	// Check to make sure the client is not running
	if( patchlist.size() != 0 && this->isClientRunning() )
	{
		pmc_setstatusmsg("Failed to patch. Client is running.");
		return false;
	}

	pmc_denyexit();
	if( !this->applyPatches(patchlist) )
	{
		pmc_permitexit();
		return false;
	}
	pmc_permitexit();

	pmc_permitstart();
	return true;
}


unsigned int Patcher::level()
{
	unsigned int level = 0;
	m_level.Get(&level); // no checking
	return level;
}


bool Patcher::checkPatchAllow()
{
	pmc_setstatusmsg("Getting PatchAllow");

	std::string allowData;
	int attempts;
	const int MAX_ATTEMPTS = 10;
	for( attempts = 1; attempts <= MAX_ATTEMPTS; ++attempts )
	{
		allowData = m_net.Get("https://%s:%d/%s", PN_WEBADDRESS, PN_WEBPORT, PN_ALLOWFILE).FetchToStr();
		if( allowData.size() != 0 )
			break; // success.

		pmc_setstatusmsg("Error: Failed to fetch PatchAllow, retrying... (attempt %d/%d)", attempts, MAX_ATTEMPTS);
		Sleep(1000);
	}
	if( attempts > MAX_ATTEMPTS )
	{
		pmc_setstatusmsg("Error: The Patchserver seems to be down, or some files are missing!");
		return false;
	}

	if( strnicmp(allowData.c_str(), "deny", 4) == 0 )
	{
		pmc_setstatusmsg("Getting NoticeClose");
		std::string closeNotice = m_net.Get("https://%s:%d/%s", PN_WEBADDRESS, PN_WEBPORT, PN_NOTICECLOSEFILE).FetchToStr();
		if( closeNotice.size() == 0 )
		{
			pmc_setstatusmsg("NoticeClose: The Patchserver seems to be down, or some files are missing!");
			return false;
		}

		pmc_setstatusmsg("Server is Closed.");
		pmc_setnotice(closeNotice.c_str());
		return false;
	}
	else
	{
		pmc_setstatusmsg("Getting Patch Notice");
		std::string patchNotice = m_net.Get("https://%s:%d/%s", PN_WEBADDRESS, PN_WEBPORT, PN_NOTICEFILE).FetchToStr();
		if( patchNotice.size() == 0 )
		{
			pmc_setstatusmsg("PatchNotice: The Patchserver seems to be down, or some files are missing!");
			return false;
		}

		pmc_setnotice(patchNotice.c_str());
		return true;
	}
}


bool Patcher::getPatchList(patchlist_t& out_list)
{
	// download patch list file
	pmc_setstatusmsg("Getting PatchList");
	std::vector<char> patchData = m_net.Get("https://%s:%d/%s", PN_WEBADDRESS, PN_WEBPORT, PN_LISTFILE).FetchToMem();
	if( patchData.size() == 0 )
	{
		pmc_setstatusmsg("PatchList: The Patchserver seems to be down, or some files are missing!");
		return false;
	}

	// download patch list signature
	pmc_setstatusmsg("Getting PatchList Signature");
	std::vector<char> patchSig = m_net.Get("https://%s:%d/%s.sig", PN_WEBADDRESS, PN_WEBPORT, PN_LISTFILE).FetchToMem();
	if( patchSig.size() == 0 )
	{
		pmc_setstatusmsg("PatchList: failed to download the patchlist signature (connection error, or the file is missing)!");
		return false;
	}

	// verify integrity of patch list
	pmc_setstatusmsg("Verifying PatchList Integrity"); 
	if( Signature::Verify(PN_PUBLICKEY, patchData, patchSig) == false )
	{
		pmc_setstatusmsg("PatchList: patchlist signature mismatch, patchlist has not been signed properly!");
		return false;
	}

	// parse patch list file
	pmc_setstatusmsg("Parsing Patchlist");

	const char* data = &patchData.front();
	size_t size = patchData.size();
	unsigned int min_level = level() + 1;

	size_t linelen;
	for( size_t i = 0; i < size; i += linelen )
	{
		const char* curline = data + i;
		const char* nextline = (const char*)memchr(curline, '\n', size - i);
		nextline = ( nextline != NULL ) ? nextline + 1 : data + size;
		linelen = nextline - curline;

		patchentry_t entry;
		if( !entry.loadFromStr(curline, linelen) )
			continue; // not a patch entry

		if( entry.num < min_level )
			continue; // already applied

		if( entry.ext() != "gpf" && entry.ext() != "rgz" )
			continue; // unsupported filetype

		out_list.push_back(entry);
	}

	return true;
}


bool Patcher::downloadPatches(const patchlist_t& list)
{
	int cnt = 0;
	for( patchlist_t::const_iterator entry = list.begin(); entry != list.end(); ++entry )
	{
		cnt++;
		pmc_setstatusfootmsg("Downloading file %d/%d", cnt, list.size());

		pmc_setstatusmsg("Preparing to receive %s", entry->filename);
		pmc_setprogress(0);	
		pmc_setdltimeleft("");
		pmc_setdlspeed("");

		struct stat st;
		DWORD dwDiskSize = ( stat(entry->filename, &st) == 0 ) ? st.st_size : 0;

		if( entry->size != 0 && entry->size == dwDiskSize )
			continue; // already downloaded, skip

		Download dl = m_net.Get("https://%s:%d/%s%s", PN_FILEWEBADDR, PN_FILEWEBPORT, PN_FILEWEBDIR, entry->filename);
		if( !dl.isOK() )
		{
			pmc_setstatusmsg("%s: connection error.", entry->filename);
			return false;
		}

		if( entry->size != 0 && entry->size != dl.size() )
		{
			pmc_setstatusmsg("%s: file size on patch server does not match size in patch list!", entry->filename);
			return false;
		}

		if( dwDiskSize == dl.size() )
			continue; // already downloaded, skip

		FILE* fp = fopen(entry->filename, "wb");
		if( fp == NULL )
		{
			pmc_setstatusmsg("%s: write error, cannot open local file for writing!", entry->filename);
			return false;
		}

		pmc_setprogress(0);

		DWORD total_read = 0;
		DWORD last_recv = 0;
		DWORD last_tick = GetTickCount();

		std::vector<char> buf;
		while( dl.FetchOnce(buf, 2*1024) && buf.size() != 0 )
		{
			DWORD bytes_read = buf.size();
			total_read += bytes_read;

			if( fwrite(&buf.front(), 1, bytes_read, fp) < bytes_read )
			{
				//error it couldn't write all the buffer to file
				pmc_setstatusmsg("%s: write error (out of memory)", entry->filename);
				fclose(fp);
				DeleteFile(entry->filename);
				return false;
			}

			DWORD cur_tick = GetTickCount();
			if( cur_tick - last_tick >= 1000/2 )
			{
				DWORD bytes_per_sec = 1000 * (total_read - last_recv) / (cur_tick - last_tick);
				last_recv = total_read;
				last_tick = cur_tick;

				this->updateDownloadProgress(entry->filename, total_read, dl.size(), bytes_per_sec);
			}

			buf.clear(); // prepare for next fetch
		}

		pmc_setprogress(100);
		fclose(fp);

		if( total_read != dl.size() )
		{
			pmc_setstatusmsg("%s: download incomplete!", entry->filename);
			DeleteFile(entry->filename);
			return false;
		}

		if( entry->hasMD5() && !entry->checkMD5() )
		{
			pmc_setstatusmsg("%s: md5 hash mismatch!", entry->filename);
			DeleteFile(entry->filename);
			return false;
		}
	}

	pmc_setstatusfootmsg("");
	return true;
}


bool Patcher::applyPatches(const patchlist_t& list)
{
	pmc_setprogress(0);
	pmc_setstatusmsg("Preparing to repack %s", PN_DATAFILE);
	pmc_setstatusfootmsg("");
	pmc_setdltimeleft("");
	pmc_setdlspeed("");

	int count = 0;
	for( patchlist_t::const_iterator entry = list.begin(); entry != list.end(); ++entry )
	{
		count++;
		pmc_setstatusfootmsg("Patch %d of %d", count, list.size());

		if( entry->ext() == "rgz" )
		{// is RGZ -> simply unpack
			pmc_setstatusmsg("Unpack: %s", entry->filename);

			if( !this->unpackRGZ(entry->filename) )
			{
				pmc_setstatusmsg("Unpack %s fail.", entry->filename);
				return false;
			}
		}
		else
		if( entry->ext() == "gpf" )
		{// is GPF -> merge with IDS_DATAFILE
			pmc_setstatusmsg("Writing Patch: %s", entry->filename);

			if( !this->mergeGRF(entry->filename) )
				return false;
		}

		if( !m_level.Set(entry->num) )
		{
			pmc_setstatusmsg("%s: failed to update patch level file", entry->filename);
			return false;
		}

		DeleteFile(entry->filename);

		pmc_setprogress(100 * count / list.size());
	}

	pmc_setstatusmsg("Patch process completed.");
	pmc_setstatusfootmsg("");
	return true;
}


bool Patcher::unpackRGZ(const char* filename)
{
	return ( rgz_unpack(filename) != -1 );
}


bool Patcher::mergeGRF(const char* filename)
{
	grf_handle dgrf = grf_load(PN_DATAFILE);
	if( dgrf == NULL )
	{
		pmc_setstatusmsg("DataFile, %s open error", PN_DATAFILE);
		return false;
	}
	AUTORELEASEL(dgrf, (grf_handle& grf) { grf_free(grf); });

	grf_handle grf = grf_load(filename);
	if( grf == NULL )
	{
		pmc_setstatusmsg("%s: open error.", filename);
		return false;
	}
	AUTORELEASEL(grf, (grf_handle& grf) { grf_free(grf); });

	if( !grf_merge(dgrf, grf) )
	{
		pmc_setstatusmsg("%s: grf merge error(%s)", PN_DATAFILE, filename);
		return false;
	}

	return true;
}


bool Patcher::isClientRunning()
{
	return ( FindWindowA(PMC_GAMEWNDCLASS,PMC_GAMETITLE) != NULL );
}


void Patcher::updateDownloadProgress(const char* filename, DWORD current, DWORD total, DWORD speed_bps)
{
	// progress bar
	pmc_setprogress(100 * current / total);

	// progress status text
	if( total > 1258292 )
		pmc_setstatusmsg("Receiving file %s (%0.2f / %0.2f MB)", filename, current/1048576., total/1048576.);
	else if( total > 51200 )
		pmc_setstatusmsg("Receiving file %s (%d / %d KB)", filename, current/1024, total/1024);
	else //( total <= 51200 )
		pmc_setstatusmsg("Receiving %s (%d / %d B)", filename, current, total);

	// speed indicator
	if( speed_bps > 1024*1024 )
		pmc_setdlspeed("Speed: %d MB/s", speed_bps/1024/1024);
	else if( speed_bps > 1024 )
		pmc_setdlspeed("Speed: %d KB/s", speed_bps/1024);
	else
		pmc_setdlspeed("Speed: %d B/s", speed_bps);

	// remaining time indicator
	DWORD seconds = (total - current) / speed_bps;
	DWORD t_h = seconds / 3600;
	DWORD t_m = seconds % 3600 / 60;
	DWORD t_s = seconds % 60;

	if( seconds < 60 )
		pmc_setdltimeleft("Time left: %d Seconds", seconds);
	else
		pmc_setdltimeleft("Time left: %2.2d:%2.2d", t_m, t_s);
}
