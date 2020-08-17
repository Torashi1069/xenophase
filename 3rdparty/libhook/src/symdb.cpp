#include "symdb.hpp"
#include <windows.h>
#include <detours/detours.h> // DetourFindFunction()
#include <map> // std::map
#include <string> // std::string
#include <assert.h> // assert()
#include <stddef.h> // NULL


struct SymDB_members { std::map<std::string, void*> table; };


/// Returns a singleton instance of the symdb.
/// Dynamic allocation is used to ensure that the object is still there during shutdown.
/// This will produce a fixed-size memory leak, but that shouldn't be a problem.
SymDB& SymDB::DB(void)
{
	static SymDB* singleton = NULL;
	static bool bFirstRun = true;

	if( bFirstRun )
	{
		bFirstRun = false;
		singleton = new SymDB();
		singleton->Init();
	}

	return *singleton;
}


/// Initializes the db.
SymDB::SymDB(void)
{
	this->m = new SymDB_members;
}


/// Cleans up the db.
SymDB::~SymDB(void)
{
	delete this->m;
}


void SymDB::Init(void)
{
	SymDBInitCallback();
}


void* SymDB::Add(const char* name, void* address)
{
	SymDB& self = SymDB::DB();

	assert( name != NULL && address != NULL );
	if( name == NULL || address == NULL )
		return NULL;

	void* prev = SymDB::Find(name);

	assert( prev == NULL || prev == address );
	if( prev != NULL && prev != address )
		return NULL;

	self.m->table[name] = address;
	return address;
}


void* SymDB::Add(const char* name, unsigned long address)
{
	return SymDB::Add(name, (void*)address);
}


void* SymDB::Add(const char* name, const char* file, const char* symbol)
{
	SymDB& self = SymDB::DB();

	void* address = DetourFindFunction(file, symbol);
	if( address == NULL )
		return NULL;

	return SymDB::Add(name, address);
}


void* SymDB::Find(const char* name)
{
	SymDB& self = SymDB::DB();

	std::map<std::string, void*>::iterator it = self.m->table.find(name);
	return( it != self.m->table.end() ) ? it->second : NULL;
}
