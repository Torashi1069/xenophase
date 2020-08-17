#pragma once


template<typename T, int N> class DBProxy
{
public:
	static T* instance()
	{
		static LONG count;
		LONG i = InterlockedIncrement(&count) % N;
		return DBProxy<T,N>::instance(i);
	}

	static T* instance(unsigned int index)
	{
		static T _instance[N];
		return &_instance[index];
	}

	static BOOL connect(const char* in_szpFileDSN, const char* in_Pwd)
	{
		for( int i = 0; i < N; ++i )
			if( !DBProxy<T,N>::instance(i)->CDatabase::Connect(in_szpFileDSN, in_Pwd) )
				return FALSE;

		return TRUE;
	}
};
