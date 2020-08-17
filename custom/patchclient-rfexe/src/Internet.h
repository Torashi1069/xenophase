#pragma once
#include <string>
#include <vector>
#include <windows.h>
#include <wininet.h> // HINTERNET


class Download
{
public:
	Download(HINTERNET hUrl);
	~Download();

	/// Is it OK to start downloading? 
	bool isOK();

	/// Size of content, reported by the server.
	DWORD size();

	/// Downloads up to 'maxBytes' of data and appends to 'output'.
	bool FetchOnce(std::vector<char>& output, DWORD maxBytes, DWORD* outBytes = NULL);

	/// Downloads all data and appends to 'output'.
	bool FetchAll(std::vector<char>& output);

	/// Convenience functions.
	std::vector<char> FetchToMem(); 
	std::string FetchToStr();

	/// Magic value to indicate that size is unavailable.
	static const DWORD UNKNOWN_SIZE = (DWORD)-1;

private:
	bool statusCode(DWORD* output);
	bool contentSize(DWORD* output);

private:
	HINTERNET m_inet; // connection handle
};


class Internet
{
public:
	Internet();
	~Internet();

	/// Starts a new WinINet session.
	bool Open(const char* szUserAgent);

	/// Ends the current WinINet session.
	void Close();

	/// Initializes the download of the selected url.
	Download Get(const char* szUrlFmt, ...);

private:
	HINTERNET m_inet; // main handle
};
