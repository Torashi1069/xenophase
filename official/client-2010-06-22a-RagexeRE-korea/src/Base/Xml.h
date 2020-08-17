#pragma once


class XMLElement
{
public:
	XMLElement(const char* name);
	~XMLElement();

public:
	void Clear();
	const char* GetName();
	mystd::string& GetContents();
	void AddChild(XMLElement* element);
	XMLElement* GetChild();
	XMLElement* FindChild(const char* name);
	void AddNext(XMLElement* element);
	XMLElement* GetNext();
	XMLElement* FindNext(const char* name);
	void SetStart(const char* start);
	void SetEnd(const char* end);
	mystd::string ParseSpecialCharater(const char* document, const char* end);
	const char* SkipTag(const char* document, const char* end);

protected:
	/* this+ 0 */ const char* m_name;
	/* this+ 4 */ const char* m_start;
	/* this+ 8 */ const char* m_end;
	/* this+12 */ mystd::string m_contents;
	/* this+28 */ XMLElement* m_next;
	/* this+32 */ XMLElement* m_child;
};


class XMLDocument
{
public:
	XMLDocument();
	~XMLDocument();

public:
	void Clear();
	bool ReadDocument(const char* document, const char* end);
	XMLElement* GetRootElement();
	XMLElement* FindElement(const char* name);

protected:
	const char* ReadContents(XMLElement* element, const char* document, const char* end);
	const char* ReadElement(XMLElement* parent, const char* document, const char* end);
	bool IsEndTag(const char* document);
	bool IsPITag(const char* document);
	bool IsCommentTag(const char* document);
	bool IsClosedTag(const char* document, const char* end);
	const char* SkipTag(const char* document, const char* end);
	const char* ParseTag(const char* document, const char* end);
	static bool IsTag(const char* document); /// @custom
	static bool IsEntity(const char* document); /// @custom
	static const char* SkipEntity(const char* document, const char* end); /// @custom

protected:
	/* this+ 0 */ XMLElement m_root;
	/* this+36 */ char* m_buf;
};
