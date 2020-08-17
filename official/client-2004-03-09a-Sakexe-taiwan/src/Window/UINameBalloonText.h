#include "Struct.h" // struct NamePair
#include "Window/UIBalloonText.h"


class UINameBalloonText : public UIBalloonText
{
public:
	UINameBalloonText();
	virtual ~UINameBalloonText();
	virtual void OnDraw();
	virtual void SetEmblemResName(const char* EmblemResName);
	virtual void SetNameText(const char* cName);
	virtual void SetNameText(const NamePair& namePair, bool cutSharp);
//	bool HasEmblem();

public:
	/* this+  0 */ //UIBalloonText baseclass_0;
	/* this+108 */ mystd::string m_ebmResName;
	/* this+124 */ int m_textWidth;
};
