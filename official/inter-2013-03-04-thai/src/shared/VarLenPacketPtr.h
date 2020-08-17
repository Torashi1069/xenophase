#pragma once


template<typename T, int N> class CVarLenPacketPtr
{
public:
	T* operator->() { return (T*)&m_Vector[0]; }
	operator BYTE*() { return (BYTE*)&m_Vector[0]; }
	operator char*() { return (char*)&m_Vector[0]; }
	operator int(); //TODO

public:
	void add(const BYTE* in_pData, const int in_Bytes) { m_Vector.insert(m_Vector.end(), &in_pData[0], &in_pData[in_Bytes]); }
	void add(const unsigned int ); //TODO
	int size() { return m_Vector.size(); }
	std::vector<BYTE>& GetVector() { return m_Vector; }

public:
	CVarLenPacketPtr() { m_Vector.resize(sizeof(T)); m_Vector.reserve(sizeof(T) + N); }
	~CVarLenPacketPtr() { }

private:
	std::vector<BYTE> m_Vector;
};
