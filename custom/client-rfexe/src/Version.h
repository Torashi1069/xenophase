#pragma once
#include <string>


/// CRC32 hash of main application's executable.
uint32_t EXEHASH();

/// CRC32 hash of this dll module.
uint32_t DLLHASH();

/// Identify local executable version using PE header timestamp.
std::string LOCALVER();

// Identify remote server version using address and port.
std::string REMOTEVER(SOCKET s);
