#pragma once


class HookDB
{
public:
	/// Represents a hook.
	class entry
	{
	private:
		void* m_funcOrig; // (cached) current address of original func
		void* m_funcReal; // real address of original func
		void* m_funcMine; // address of hook func
		void* m_funcJump; // trampoline to original func (or NULL)

	public:
		entry(void* origfunc, void* myfunc);
		~entry(void);
		void* original(void);
		void* mine(void);
		bool active(void);
		void hook(void);
		void unhook(void);
		bool verify(void);
	};

public:
	/// Returns a singleton instance of the hookdb.
	static HookDB& DB(void);

	/// Retrieves the 'entry' value belonging to the 'name' from the table, or NULL if no such entry exists.
	entry* Get(const char* name);

	/// Registers a hook under the specified name.
	/// @param name Name for the new hook.
	/// @param origfunc Address of the original, unhooked function.
	/// @param myfunc Address of the replacement function.
	entry* Register(const char* name, void* origfunc, void* myfunc);

	/// Hooks the specified target, and activates the hook.
	void Hook(const char* name, void* origfunc, void* myfunc);

	/// Deactivates all hooks.
	/// NOTE: Not compatible with hook stacking.
	void UnhookAll(void);

	/// Scans all active hooks and makes sure they're all intact.
	/// Attempts to repair hooked code that has been altered.
	/// NOTE: Not compatible with hook stacking.
	bool Verify(void);

private:
	/// Initializes the db.
	HookDB(void);

	/// Cleans up the db and destroys it.
	~HookDB(void);

private:
	/// Hook database.
	struct HookDB_members* m;
//	-> std::map<std::string, entry> table;
};
