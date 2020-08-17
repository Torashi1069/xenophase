#pragma once


class CFTToken
{
public:
	enum enumType
	{
		NONE        = 0,
		STRING      = 1,
		NUMBER      = 2,
		SYMBOL      = 3,
		LEFT_BRACE  = 4,
		RIGHT_BRACE = 5,
		COMMA       = 6,
		EOF_        = 7,
	};

protected:
	/* this+ 0 */ //const CFTToken::`vftable';
	/* this+ 4 */ enumType m_Type;
	/* this+ 8 */ std::string m_Value;
	/* this+36 */ int m_Line;
	/* this+40 */ int m_Col;

public:
	enumType GetType() const;
	int GetINT() const;
	bool GetBOOL() const;
	std::string GetSTRING() const;

public:
	int GetLine() const;
	int GetCol() const;

public:
	CFTToken();
	CFTToken(const enumType in_Type, const std::string in_Value, const int in_Line, const int in_Col);
	~CFTToken();
};
