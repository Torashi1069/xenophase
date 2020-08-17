#pragma once
#include "hookdb.hpp"
#include "symdb.hpp"
#include "util.hpp"
#include <assert.h> // assert()
#include <stddef.h> // NULL


/// The 'hooking reference' system.
/// Latches onto a remote symbol and tries to act as a reference to that symbol.
/// This essentially makes it as if the symbol was directly present in your code.
///
/// Positives:
/// * Type is specified in <>'s, not around the variable (makes things cleaner).
/// * Raises an assertion if the symbol lookup step fails.
/// * Constructor can have various parameters and can do extra things.
/// * Automatically synchronizes function hooks with HookDB.
///
/// Downsides:
/// * Can't overload . (member access operator), need to use the -> workaround instead.
/// * Can't use sizeof().
/// * Sometimes requires explicit typecast when used in expressions.
/// * Need to pick the correct template to use manually.


/// Acts as a reference to a pointer.
template <typename T> class hook_ptr
{
protected:
	void* _ptr;

public:
	explicit hook_ptr(const char* name)
	{
		_ptr = SymDB::Find(name);
		assert( _ptr != NULL );
	}

	explicit hook_ptr(const char* module, const char* symbol)
	{
		_ptr = SymDB::Add(symbol, module, symbol);
		assert( _ptr != NULL );
	}

	explicit hook_ptr(const char* name, const char* module, const char* symbol)
	{
		_ptr = SymDB::Add(name, module, symbol);
		assert( _ptr != NULL );
	}

	                      T* operator  &()      { return (T*)_ptr; }
	                      T& operator ->()      { return *(T*)_ptr; }
	                         operator T&()      { return *(T*)_ptr; }
	template <typename S>    operator S ()      { return (S)*(T*)_ptr; }
	template <typename S> T& operator = (S val) { return *(T*)_ptr = val; }
};


/// Acts as a reference to a variable/structure/class.
/// Use the -> operator to access members (workaround for C++ limitation).
template <typename T> class hook_val
{
protected:
	void* _ptr;

public:
	explicit hook_val(const char* name)
	{
		_ptr = SymDB::Find(name);
		assert( _ptr != NULL );
	}

	explicit hook_val(const char* module, const char* symbol)
	{
		_ptr = SymDB::Add(symbol, module, symbol);
		assert( _ptr != NULL );
	}

	explicit hook_val(const char* name, const char* module, const char* symbol)
	{
		_ptr = SymDB::Add(name, module, symbol);
		assert( _ptr != NULL );
	}

	                      T* operator  &()      { return (T*)_ptr; }
	                      T* operator ->()      { return (T*)_ptr; }
	                         operator T&()      { return *(T*)_ptr; }
	template <typename S>    operator S ()      { return (S)*(T*)_ptr; }
	template <typename S> T& operator = (S val) { return *(T*)_ptr = val; }
};


/// Acts as a reference to a function.
template <typename T> class hook_func
{
protected:
	HookDB::entry* _entry;

public:
	explicit hook_func(const char* name)
	{
		void* _ptr = SymDB::Find(name);
		assert( _ptr != NULL );

		_entry = HookDB::DB().Register(name, _ptr, NULL);
	}

	explicit hook_func(const char* module, const char* symbol)
	{
		void* _ptr = SymDB::Add(symbol, module, symbol);
		assert( _ptr != NULL );

		_entry = HookDB::DB().Register(symbol, _ptr, NULL);
	}

	explicit hook_func(const char* name, const char* module, const char* symbol)
	{
		void* _ptr = SymDB::Add(name, module, symbol);
		assert( _ptr != NULL );

		_entry = HookDB::DB().Register(name, _ptr, NULL);
	}

	operator T() { return VTOF<T>(_entry->original()); }
	T operator &() { return VTOF<T>(_entry->original()); }
};


/// Backwards compatibility.
#define hook_method hook_func
