#pragma once


///
/// Symbol DB.
/// 
/// Stores information about symbols in executables.
/// Provides the means to look up a symbol's address by name.
/// (name -> information -> address)
/// 
/// Supported symbol specifications:
/// * by memory address (directly)
/// * by filename and symbol name (needs debug/exported symbols)
/// 
class SymDB
{
public:
	/// Adds a symbol entry by memory address.
	/// @return Address of symbol, or NULL if the parameters are invalid.
	static void* Add(const char* name, void* address);
	static void* Add(const char* name, unsigned long address);

	/// Adds a symbol entry by symbol name in executable.
	/// @return Address of symbol, or NULL if the parameters are invalid or if the symbol could not be found.
	static void* Add(const char* name, const char* file, const char* symbol);

	/// Looks up a symbol's address by name.
	static void* Find(const char* name);

private:
	/// Returns a singleton instance of the symdb.
	static SymDB& DB(void);

	/// Initializes the db.
	SymDB(void);

	/// Cleans up the db.
	~SymDB(void);

	/// Actually initializes the db.
	/// Calls the user-provided SymDBInitCallback function.
	void Init(void);

private:
	/// The name-to-address database.
	struct SymDB_members* m;
//	-> std::map<std::string, void*> table;
};


/// User-provided callback function, will be called when initializing.
/// Fill the db with data in here.
extern void SymDBInitCallback(void);
