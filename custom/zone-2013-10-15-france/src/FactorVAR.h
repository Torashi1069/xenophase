#pragma once
namespace FactorVAR {
////////////////////////////////////////


class Fvar
{
public:
	virtual void Init() = 0;

public:
	Fvar() { }
	virtual ~Fvar() { } // line 19
};


////////////////////////////////////////


class INDvar : public Fvar
{
public:
	int operator()(const int in_IndividualFactor) const; //TODO
	void Set(const int in_IndividualFactor, const int in_Value);

public:
	virtual void Init() { m_Tbl.clear(); } // line 27

public:
	INDvar() : m_Tbl() { }
	virtual ~INDvar() { } // line 30

private:
	/* this+ 0 */ //Fvar baseclass_0;
	/* this+ 4 */ std::map<int,int> m_Tbl;
};


////////////////////////////////////////


class SUMvar : public Fvar
{
public:
	int operator()() const; //TODO
	void Set(const int in_Key, const int in_Amount);
	void Reset(const int in_Key);

public:
	virtual void Init() { m_Tbl.clear(); m_Sum = 0; }

public:
	SUMvar() : m_Tbl(), m_Sum() { } // line 43
	virtual ~SUMvar() { } // line 44

private:
	/* this+ 0 */ //Fvar baseclass_0;
	/* this+ 4 */ std::map<int,int> m_Tbl;
	/* this+20 */ int m_Sum;
};


////////////////////////////////////////


class MINvar : public Fvar
{
public:
	int operator()() const; //TODO
	void Set(const int in_Key, const int in_Amount);
	void Reset(const int in_Key);

public:
	virtual void Init() { m_Tbl.clear(); m_Min = 0; }

public:
	MINvar() : m_Tbl(), m_Min() { }
	virtual ~MINvar() { }

private:
	/* this+ 0 */ //FVar baseclass_0;
	/* this+ 4 */ std::map<int,int> m_Tbl;
	/* this+20 */ int m_Min;
};


////////////////////////////////////////


class MAXvar : public Fvar
{
public:
	int operator()() const; //TODO
	void Set(const int in_Key, const int in_Amount);
	void Reset(const int in_Key);

public:
	virtual void Init() { m_Tbl.clear(); m_Max = 0; }

public:
	MAXvar() : m_Tbl(), m_Max() { } // line 77
	virtual ~MAXvar() { } // line 78

private:
	/* this+ 0 */ //FVar baseclass_0;
	/* this+ 4 */ std::map<int,int> m_Tbl;
	/* this+20 */ int m_Max;
};


////////////////////////////////////////


class BOOLvar : public Fvar
{
public:
	bool operator()() const; //TODO
	void Set(const int in_Key);
	void Reset(const int in_Key);

public:
	virtual void Init() { m_Tbl.clear(); m_RefCnt = 0; } // line 92

public:
	BOOLvar() : m_Tbl(), m_RefCnt() { } // line 94
	virtual ~BOOLvar() { } // line 95

private:
	/* this+ 0 */ //Fvar baseclass_0;
	/* this+ 4 */ std::map<int,int> m_Tbl;
	/* this+20 */ int m_RefCnt;
};


////////////////////////////////////////


class INDHISTORYvar : public Fvar
{
public:
	virtual void Init() { m_Tbl.clear(); }

public:
	void Set(const int in_IndividualFactor, const int in_HistoryFactor, const int in_Value);
	void Reset(const int in_IndividualFactor, const int in_HistoryFactor);
	std::pair<bool,int> operator()(const int in_IndividualFactor);

public:
	INDHISTORYvar() : m_Tbl() { }
	virtual ~INDHISTORYvar() { } // line 113

private:
	struct tagData
	{
		/* this+0 */ int history;
		/* this+4 */ int value;

		tagData(const int ); //TODO
		tagData(const int in_history, const int in_value) : history(in_history), value(in_value) { }
		bool operator==(const tagData& ); //TODO
	};

	/* this+ 0 */ //Fvar baseclass_0;
	/* this+ 4 */ std::map<int,std::vector<tagData>> m_Tbl;
};


////////////////////////////////////////


class INDMAXHISTORYvar : public Fvar
{
public:
	virtual void Init() { m_Tbl.clear(); } // line 158

public:
	void Set(const int in_IndividualFactor, const int in_HistoryFactor, const int in_Value); //TODO
	void Reset(const int in_IndividualFactor, const int in_HistoryFactor); //TODO
	int operator()(const int in_IndividualFactor); //TODO

public:
	INDMAXHISTORYvar() : m_Tbl() { }
	virtual ~INDMAXHISTORYvar() { }

private:
	struct tagData
	{
		struct tagHistory
		{
			/* this+0 */ int HistoryFactor;
			/* this+4 */ int Value;

			bool operator==(const tagHistory& );
			tagHistory(const int , const int );
		};

		/* this+0 */ int Max;
		/* this+4 */ std::vector<tagHistory> History;

		tagData() : Max(), History() { }
	};

	/* this+ 0 */ //Fvar baseclass_0;
	/* this+ 4 */ std::map<int,tagData> m_Tbl;
};


////////////////////////////////////////


class INDMINHISTORYvar : public Fvar
{
public:
	virtual void Init() { m_Tbl.clear(); }

public:
	void Set(const int in_IndividualFactor, const int in_HistoryFactor, const int in_Value); //TODO
	void Reset(const int in_IndividualFactor, const int in_HistoryFactor); //TODO
	int operator()(const int in_IndividualFactor) const; //TODO

public:
	INDMINHISTORYvar() : m_Tbl() { }
	virtual ~INDMINHISTORYvar() { }

private:
	struct lcData
	{
		struct lcHistory
		{
			/* this+0 */ //const lcHistory::`vftable';
			/* this+4 */ int m_Factor;
			/* this+8 */ int m_Value;

			bool operator==(const lcHistory& );
			lcHistory(const int , const int );
			virtual ~lcHistory() { } // line 204
		};

		/* this+0 */ //const lcData::`vftable';
		/* this+4 */ int m_Min;
		/* this+8 */ std::vector<lcHistory> m_History;

		lcData() { }
		virtual ~lcData() { } // line 211
	};

	/* this+ 0 */ //Fvar baseclass_0;
	/* this+ 4 */ std::map<int,lcData> m_Tbl;
};


////////////////////////////////////////


class HISTORYvar : public Fvar
{
public:
	std::pair<bool,int> operator()(); //TODO
	void Set(const int, const int); //TODO
	void Reset(const int); //TODO

public:
	virtual void Init() { m_History.clear(); m_Value = 0; }

public:
	HISTORYvar() : m_History(), m_Value() { }
	virtual ~HISTORYvar() { } // line 227

private:
	struct tagHistory
	{
		/* this+0 */ int HistoryFactor;
		/* this+4 */ int Value;

		tagHistory(const int , const int ); //TODO
		bool operator==(const tagHistory& ); //TODO
	};

private:
	/* this+ 0 */ //Fvar baseclass_0;
	/* this+ 4 */ std::vector<tagHistory> m_History;
	/* this+20 */ int m_Value;
};


////////////////////////////////////////


class SUMHISTORYvar : public Fvar
{
public:
	int operator()(); //TODO
	void Set(const int in_HistoryFactor, const int in_Value);
	void Reset(const int in_HistoryFactor);

public:
	virtual void Init() { m_History.clear(); m_Value = 0; }

public:
	SUMHISTORYvar() : m_History(), m_Value() { }
	virtual ~SUMHISTORYvar() { } // line 248

private:
	struct tagHistory
	{
		/* this+0 */ int HistoryFactor;
		/* this+4 */ int Value;

		tagHistory(const int in_HistoryFactor, const int in_Value) : HistoryFactor(in_HistoryFactor), Value(in_Value) { }
		tagHistory operator+(const tagHistory& ); //TODO
		bool operator==(const tagHistory& ); //TODO
	};

	/* this+ 0 */ //Fvar baseclass_0;
	/* this+ 4 */ std::vector<tagHistory> m_History;
	/* this+20 */ int m_Value;
};


////////////////////////////////////////


class INDSUMHISTORYvar : public Fvar
{
public:
	virtual void Init() { m_Tbl.clear(); } // line 264

public:
	void Set(const int , const int , const int ); //TODO
	void Reset(const int , const int ); //TODO
	int operator()(const int ); //TODO

public:
	INDSUMHISTORYvar() : m_Tbl() { }
	virtual ~INDSUMHISTORYvar() { } // line 270

private:
	/* this+ 0 */ //Fvar baseclass_0;
	/* this+ 4 */ std::map<int,SUMHISTORYvar> m_Tbl;
};


////////////////////////////////////////


class PassiveSKHPSPRecovery : public Fvar
{
public:
	virtual void Init() { m_Time = 0; m_Value = 0; m_Tbl.clear(); } // line 278

public:
	void Set(const int , const int , const int ); //TODO
	void Reset(const int ); //TODO
	std::pair<int,int> operator()(); //TODO

public:
	int GetTime(); //TODO
	int GetValue(); //TODO
	void Evaluation(); //TODO

public:
	PassiveSKHPSPRecovery() : m_Time(), m_Value(), m_Tbl() { }
	virtual ~PassiveSKHPSPRecovery() { } // line 289

private:
	/* this+ 0 */ //Fvar baseclass_0;
	/* this+ 4 */ int m_Time;
	/* this+ 8 */ int m_Value;
	/* this+12 */ std::vector<std::tr1::tuple<int,int,int>> m_Tbl;
};


////////////////////////////////////////
}; // namespace
