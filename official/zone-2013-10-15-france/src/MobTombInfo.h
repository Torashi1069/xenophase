#pragma once


class CScriptMobTombInfo
{
private:
	enum { DIALOGMSG_NUM = 3 };

public:
	struct MobTombInfo
	{
		/* this+ 0 */ std::string NpcName;
		/* this+28 */ std::string DialogMsg[DIALOGMSG_NUM];
	};

public:
	bool LoadLuaFIle();

public:
	static bool CreateInstance();
	static void DestroyInstance();
	static CScriptMobTombInfo* GetObj(); /// @custom
	bool IsCreateInstance();

public:
	const MobTombInfo& GetMobTombInfo();
	void SetMobTombInfo(const MobTombInfo& info);

private:
	/* static   */ static CScriptMobTombInfo*& m_cpSelf; //TODO
	/* this+  0 */ bool m_bCreateInstance;
	/* this+  4 */ MobTombInfo m_MobTombInfo;
	/* this+116 */ const std::string m_FileName;

private:
	CScriptMobTombInfo();
	~CScriptMobTombInfo();
};
