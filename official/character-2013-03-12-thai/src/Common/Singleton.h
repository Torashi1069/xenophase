/// @source Mark DeLoura: "Game Programming Gems" (2000), section 1.3: "An Automatic Singleton Utility" by Scott Bilas
/// @source http://scottbilas.com/publications/gem-singleton/
#pragma once


template<typename T> class CSingleton
{
protected:
	/* static */ static T* ms_Singleton;

public:
	CSingleton() { ms_Singleton = static_cast<T*>(this); }
	~CSingleton() { ms_Singleton = static_cast<T*>(NULL); }
	static T& getSingleton() { return *ms_Singleton; }
	static T* getSingletonPtr() { return ms_Singleton; }
//	static T* GetInstance();
};
