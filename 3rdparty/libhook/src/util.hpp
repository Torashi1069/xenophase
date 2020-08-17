#pragma once


// use on hooked functions to prevent the compiler from messing with calling conventions
#define HOOKED __declspec(dllexport)
#define VHOOKED HOOKED


/// Func pointer to Void pointer.
/// Assumes first four bytes hold the address.
template<typename T> void* FTOV(T func)
{// truncates T to 4 bytes
	return( *(void**)&func );
}


/// Void pointer to Func pointer.
/// Assumes first four bytes should hold the address and rest be zero.
template<typename T> T VTOF(void* ptr)
{// fills in 4 bytes and zeroes the rest
	T result = 0;
	*(void**)&result = ptr;
	return result;
}


/// Void pointer to Reference.
template<typename T> inline T& VTOR(void* ptr)
{// just a straightforward typecast
	return *(T*)ptr;
}


// executable module path lookup
const char* EXEPATH(void);
const char* DLLPATH(void);


/// Replaces memory contents at a specified location. Can be used on bytecode.
/// @param addr starting offset
/// @param size number of bytes to write
/// @param from data expected at 'addr' (optional, for verification purposes)
/// @param to data to write
/// @return true on success, false if data mismatch
bool Hex(void* addr, size_t size, const void* from, const void* to);
bool Hex(unsigned long addr, size_t size, const void* from, const void* to);
