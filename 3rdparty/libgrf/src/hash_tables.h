#pragma once
#include <algorithm> // std::replace(), std::transform()
#include <cctype> // std::tolower()
#include <string> // std::string
#include <unordered_map>
#if defined(_MSC_VER) && _MSC_VER == 1500 // vs2008 fix
namespace std { using std::tr1::unordered_map; }
#endif


/// Key-Value store (unordered, case-insensitive).
template<typename T> class HashTable
{
public:
	T* find(const std::string& key);
	bool insert(const std::string& key, T* value);
	bool remove(const std::string& key);

private:
	std::string normalize(const std::string& str);

private:
	std::unordered_map<std::string,T*> m_table;
};


template<typename T> T* HashTable<T>::find(const std::string& key)
{
	std::string str = normalize(key);
	std::unordered_map<std::string,T*>::iterator it = m_table.find(str);
	if( it == m_table.end() )
		return NULL; // not found
	
	return it->second;
}


template<typename T> bool HashTable<T>::insert(const std::string& key, T* value)
{
	std::string str = normalize(key);
	std::unordered_map<std::string,T*>::iterator it = m_table.find(str);
	if( it != m_table.end() )
		return false; // already present

	m_table[str] = value;
	return true;
}


template<typename T> bool HashTable<T>::remove(const std::string& key)
{
	std::string str = normalize(key);
	std::unordered_map<std::string,T*>::iterator it = m_table.find(str);
	if( it == m_table.end() )
		return false; // not found

	m_table.erase(it);
	return true;
}


/// Converts string to lowercase.
template<typename T> std::string HashTable<T>::normalize(const std::string& str)
{
	std::string res = str;
	std::transform(res.begin(), res.end(), res.begin(), std::tolower);
	return res;
}
