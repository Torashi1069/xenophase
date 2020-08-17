#pragma once


class CharPrtLess : public mystd::binary_function<const char*, const char*, bool>
{
	public: bool CharPrtLess::operator()(const char* left, const char* right) const // line 103
	{
		while( *left != '\0' && *left == *right )
		{
			++left;
			++right;
		}

		return( (unsigned char)*left < (unsigned char)*right );		
	}
};


class LPCSTRComp
{
	public: bool LPCSTRComp::operator()(LPCSTR left, LPCSTR const right)
	{
		return ( strcmp(left, right) < 0 );
	}
};


class DComp
{
	public: bool DComp::operator()(const mystd::pair<const char*,enum TALKTYPE>& left, const char* const& right)
	{
		return KeyLess(left.first, right);
	}

	public: bool DComp::operator()(const char*& left, const mystd::pair<const char*,enum TALKTYPE>& right)
	{
		return KeyLess(left, right.first);
	}

	public: bool DComp::operator()(const mystd::pair<const char*,enum TALKTYPE>& left, const mystd::pair<const char*,enum TALKTYPE>& right)
	{
		return KeyLess(left.first, right.first);
	}

	private: bool DComp::KeyLess(const char* const& k1, const char* const& k2) // line ???
	{
		return ( strcmp(k1, k2) < 0 );
	}
};


class SComp
{
	public: bool SComp::operator()(const mystd::pair<const char*,const char*>& left, const char* const& right)
	{
		return KeyLess(left.first, right);
	}

	public: bool SComp::operator()(const char*& left, const mystd::pair<const char*,const char*>& right)
	{
		return KeyLess(left, right.first);
	}

	public: bool SComp::operator()(const mystd::pair<const char*,const char*>& left, const mystd::pair<const char*,const char*>& right)
	{
		return KeyLess(left.first, right.first);
	}

	private: bool SComp::KeyLess(const char* const& k1, const char* const& k2) // line ???
	{
		return ( strcmp(k1, k2) < 0 );
	}
};


class SListComp
{
	public: bool SListComp::operator()(const mystd::pair< mystd::string,mystd::vector<mystd::string> >& left, const mystd::string& right)
	{
		return KeyLess(left.first, right);
	}

	public: bool SListComp::operator()(mystd::string& left, const mystd::pair< mystd::string,mystd::vector<mystd::string> >& right)
	{
		return KeyLess(left, right.first);
	}

	public: bool SListComp::operator()(const mystd::pair< mystd::string,mystd::vector<mystd::string> >& left, const mystd::pair< mystd::string,mystd::vector<mystd::string> >& right)
	{
		return KeyLess(left.first, right.first);
	}

	private: bool SListComp::KeyLess(const mystd::string& k1, const mystd::string& k2) // line 152 (Session.h)
	{
		return ( strcmp(k1.c_str(), k2.c_str()) < 0 );
	}
};


class IListComp
{
	public: bool IListComp::operator()(const mystd::pair< mystd::string,mystd::vector<int> >& left, const mystd::string& right)
	{
		return KeyLess(left.first, right);
	}

	public: bool IListComp::operator()(mystd::string& left, const mystd::pair< mystd::string,mystd::vector<int> >& right)
	{
		return KeyLess(left, right.first);
	}

	public: bool IListComp::operator()(const mystd::pair< mystd::string,mystd::vector<int> >& left, const mystd::pair< mystd::string,mystd::vector<int> >& right)
	{
		return KeyLess(left.first, right.first);
	}

	private: bool IListComp::KeyLess(const mystd::string& k1, const mystd::string& k2) // line 164 (Session.h)
	{
		return ( strcmp(k1.c_str(), k2.c_str()) < 0 );
	}
};


class IListComp2
{
	public: bool IListComp2::operator()(const mystd::pair<const char*,bool>& left, const char* const& right)
	{
		return KeyLess(left.first, right);
	}

	public: bool IListComp2::operator()(const char*& left, const mystd::pair<const char*,bool>& right)
	{
		return KeyLess(left, right.first);
	}

	public: bool IListComp2::operator()(const mystd::pair<const char*,bool>& left, const mystd::pair<const char*,bool>& right)
	{
		return KeyLess(left.first, right.first);
	}

	private: bool IListComp2::KeyLess(const char* const& k1, const char* const& k2) // line ???
	{
		return ( strcmp(k1, k2) < 0 );
	}
};
