template<typename T> void __cdecl stlwipe_second(T* t) // line 84
{
	for( T::iterator it = t->begin(); it != t->end(); ++it )
		delete it->second;

	t->clear();
}
