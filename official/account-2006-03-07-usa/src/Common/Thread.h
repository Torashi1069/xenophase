#pragma once


template<typename T> struct ThreadData
{
	typedef void (T::* TFunc)(void*);

	/* this+0 */ T* pThreadObject;
	/* this+4 */ void (T::* pThreadFunc)(void*);
	/* this+8 */ void* pParam;

	static unsigned int __stdcall ThreadFunc(void* p)
	{
		ThreadData<T> td = *reinterpret_cast<ThreadData<T>*>(p); //copy
		delete p;

		(td.pThreadObject->*td.pThreadFunc)(td.pParam);
		return 0;
	}
};


template<typename T> uintptr_t CreateMemberThread(T* p, void (T::* func)(void*), void* param)
{
	ThreadData<T>* ptd = new ThreadData<T>;
	ptd->pThreadObject = p;
	ptd->pThreadFunc = func;
	ptd->pParam = param;

	return _beginthreadex(NULL, 0, &ThreadData<T>::ThreadFunc, ptd, 0, NULL);
}
