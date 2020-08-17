#include "hookdb.hpp"
#include "util.hpp" // Hex()
#include <windows.h>
#include <detours/detours.h>
#include <map> // std::map
#include <string> // std::string
#include <assert.h> // assert()
#include <stddef.h> // NULL
#include <string.h> // memset()


struct HookDB_members { std::map<std::string, HookDB::entry> table; };


/// Initializes the db.
HookDB::HookDB(void)
{
	this->m = new HookDB_members;
}


/// Cleans up the db and destroys it.
HookDB::~HookDB(void)
{
	delete this->m;
}


/// Returns a singleton instance of the hookdb.
HookDB& HookDB::DB(void)
{
	/// Dynamic allocation is used to ensure that the object is still there during shutdown.
	/// This will produce a fixed-size memory leak, but that shouldn't be a problem.
	static HookDB* singleton = new HookDB();

	return *singleton;
}


/// Retrieves the 'entry' value belonging to the 'name' from the table, or NULL if no such entry exists.
HookDB::entry* HookDB::Get(const char* name)
{
	std::map<std::string, entry>::iterator i = this->m->table.find(name);
	return ( i != this->m->table.end() ) ? &i->second : NULL;
}


/// Registers a hook under the specified name.
/// @param name Name for the new hook.
/// @param origfunc Address of the original, unhooked function.
/// @param myfunc Address of the replacement function.
HookDB::entry* HookDB::Register(const char* name, void* origfunc, void* myfunc)
{
	std::pair<std::map<std::string,entry>::iterator,bool> i = this->m->table.insert(std::pair<const std::string,entry>(name, entry(origfunc, myfunc)));
	entry* e = &i.first->second;
	if( i.second == false )
	{// entry already exists
		assert( e->original() == NULL || e->original() == origfunc ); // not perfect
		assert( e->mine() == NULL || e->mine() == myfunc );
		*e = entry(origfunc, myfunc);
	}

	return e;
}


/// Hooks the specified target, and activates the hook.
void HookDB::Hook(const char* name, void* origfunc, void* myfunc)
{
	entry* e = Register(name, origfunc, myfunc);
	e->hook();
}


/// Deactivates all hooks.
/// NOTE: Not compatible with hook stacking.
void HookDB::UnhookAll(void)
{
	for( std::map<std::string, entry>::iterator i = this->m->table.begin(); i != this->m->table.end(); ++i )
		i->second.unhook();
}


/// Scans all active hooks and makes sure they're all intact.
/// Attempts to repair hooked code that has been altered.
/// NOTE: Not compatible with hook stacking.
bool HookDB::Verify(void)
{
	bool result = true;

	for( std::map<std::string,entry>::iterator i = this->m->table.begin(); i != this->m->table.end(); ++i )
	{
		entry* e = &i->second;

		if( e->verify() )
			continue; // hook is intact

		result = false;
	}

	return result;
}


////////////////////////////////////////


HookDB::entry::entry(void* origfunc, void* myfunc)
{
	m_funcReal = origfunc;
	m_funcMine = myfunc;
	m_funcJump = NULL;
	m_funcOrig = m_funcReal; // cache
}


HookDB::entry::~entry(void)
{
	this->unhook();
}


/// If the hook is not active, returns the original function's address,
/// otherwise returns the address of the associated trampoline.
void* HookDB::entry::original(void)
{
	return m_funcOrig;
}


void* HookDB::entry::mine(void)
{
	return m_funcMine;
}


bool HookDB::entry::active(void)
{
	return ( m_funcJump != NULL );
}


void HookDB::entry::hook(void)
{
	if( active() )
		return; // already hooked

	void* myfunc = m_funcMine;
	void* origfunc = m_funcReal;
	void* jumpfunc = NULL;

	assert( myfunc != NULL && origfunc != NULL );
	if( myfunc == NULL || origfunc == NULL )
		return;

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	LONG error = DetourAttachEx(&origfunc, myfunc, (PDETOUR_TRAMPOLINE*)&jumpfunc, NULL, NULL);
	assert( error == NO_ERROR );
	m_funcJump = jumpfunc;
	m_funcOrig = m_funcJump; // cache
	DetourTransactionCommit();
}


void HookDB::entry::unhook(void)
{
	if( !active() )
		return; // already unhooked

	void* myfunc = m_funcMine;
	void* origfunc = m_funcJump;

	assert( myfunc != NULL && origfunc != NULL );
	if( myfunc == NULL || origfunc == NULL )
		return;

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourDetach(&origfunc, myfunc);
	DetourTransactionCommit();
	m_funcJump = NULL;
	m_funcOrig = m_funcReal; // cache
}


bool HookDB::entry::verify(void)
{
	if( !active() )
		return true; // not hooked

#pragma pack(push,1)
	struct { unsigned char jmpopcode; unsigned int jmpdelta; } verify;
#pragma pack(pop)
	assert( sizeof(verify) == 5 );
	verify.jmpopcode = '\xE9';
	verify.jmpdelta = (unsigned int)m_funcMine - (unsigned int)m_funcReal - sizeof(verify);

	if( memcmp(m_funcReal, &verify, sizeof(verify)) == 0 )
		return true; // hook is intact

	// repair the hook
	Hex(m_funcReal, sizeof(verify), NULL, &verify);

	return false; // hook was messed with
}
