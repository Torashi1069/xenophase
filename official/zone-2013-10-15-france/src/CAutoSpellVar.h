#pragma once


class CAutoSpellVar
{
public:
	void Set(const unsigned int in_Identity, const unsigned int in_Level, const unsigned int in_Permill);
	void Reset(const unsigned int in_Identity);
	void Pause(const unsigned int in_Identity);
	void Resume(const unsigned int in_Identity);
	unsigned int GetPermill();
	unsigned int GetLevel();
	bool GetActive(); //TODO

public:
	CAutoSpellVar();
	virtual ~CAutoSpellVar();

	class lcData
	{
	public:
		bool operator<(const lcData& in_rhs) { return ( m_Level < in_rhs.m_Level || m_Level == in_rhs.m_Level && m_Permill < in_rhs.m_Permill ); }
		bool operator==(const lcData& ); //TODO

	public:
		lcData() : m_Identity(0), m_Level(0), m_Permill(0) { }
		lcData(const unsigned int in_Identity, const unsigned int in_Level, const unsigned int in_Permill) : m_Identity(in_Identity), m_Level(in_Level), m_Permill(in_Permill) { }
		virtual ~lcData() { }

	public:
		/* this+ 0 */ //const CAutoSpellVar::lcData::`vftable';
		/* this+ 4 */ unsigned int m_Identity;
		/* this+ 8 */ unsigned int m_Level;
		/* this+12 */ unsigned int m_Permill;
	};

private:
	/* this+ 0 */ //const CAutoSpellVar::`vftable';
	/* this+ 4 */ int m_PlayRefCnt;
	/* this+ 8 */ lcData m_Data;
	/* this+24 */ std::vector<lcData> m_History;
};
