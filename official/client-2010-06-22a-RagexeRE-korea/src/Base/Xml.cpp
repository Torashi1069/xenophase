#include "Globals.h" // Trace()
#include "Base/Xml.h"
////////////////////////////////////////


XMLElement::XMLElement(const char* name)
: m_name(name), m_start(NULL), m_end(NULL), m_contents(), m_next(NULL), m_child(NULL)
{
}


XMLElement::~XMLElement()
{
	this->XMLElement::Clear();
}


void XMLElement::Clear()
{
	if( m_next != NULL )
	{
		delete m_next;
		m_next = NULL;
	}

	if( m_child != NULL )
	{
		delete m_child;
		m_child = NULL;
	}

	m_start = NULL;
	m_end = NULL;
}


const char* XMLElement::GetName()
{
	return m_name;
}


mystd::string& XMLElement::GetContents()
{
	if( m_contents.size() != 0 )
		return m_contents; // already parsed.

	// text between tags starts here
	const char* document = this->XMLElement::SkipTag(m_start, m_end);
	const char* end = m_end;

	while( document != end )
	{
		for( XMLElement* j = m_child; j != NULL; j = j->m_child )
		{
			if( document == j->m_start )
				document = j->m_end;

			for( XMLElement* k = j->m_next; k != NULL; k = k->m_next )
			{
				if( document == k->m_start )
					document = k->m_end;
			}
		}

		char ch = *document;

		if( ch == '<' )
			break; // found closing tag, done.

		if( ch == '\r' || ch == '\n' )
		{// newline
			++document;
		}
		else
		if( ch == '&' )
		{// xml entity
			if( strcmp(m_name, "registrationweb") == 0 )
			{// raw ampersands in URL
				m_contents += '&';
				++document;
				continue;
			}

			m_contents += this->XMLElement::ParseSpecialCharater(document + 1, end);

			// inlined copy of XMLDocument::SkipEntity()
			const char* i;

			for( i = document; i != end; ++i )
				if( *i == ';' )
					break;

			document = i + 1;
		}
		else
		{// normal character
			m_contents += ch;
			++document;
		}
	}

	return m_contents;
}


void XMLElement::AddChild(XMLElement* element)
{
	if( m_child == NULL )
		m_child = element;
	else
	if( m_child->m_next == NULL )
		m_child->m_next = element;
	else
		m_child->m_next->XMLElement::AddNext(element);
}


void XMLElement::AddNext(XMLElement* element)
{
	XMLElement* last = this;

	for( XMLElement* p = this->m_next; p != NULL; p = p->m_next )
		last = p;

	last->m_next = element;
}


XMLElement* XMLElement::GetChild()
{
	return m_child;
}


XMLElement* XMLElement::FindChild(const char* name)
{
	if( m_child == NULL || strcmp(m_child->m_name, name) == 0 )
		return m_child;
	else
	if( m_child->m_next == NULL || strcmp(m_child->m_next->m_name, name) == 0 )
		return m_child->m_next;
	else
		return m_child->m_next->XMLElement::FindNext(name);
}


XMLElement* XMLElement::GetNext()
{
	return m_next;
}


XMLElement* XMLElement::FindNext(const char* name)
{
	XMLElement* last = this;
	
	for( XMLElement* p = this->m_next; p != NULL && strcmp(p->m_name, name) != 0; p = p->m_next )
		last = p;

	return last->m_next;
}


void XMLElement::SetStart(const char* start)
{
	m_start = start;
}


void XMLElement::SetEnd(const char* end)
{
	m_end = end;
}


mystd::string XMLElement::ParseSpecialCharater(const char* document, const char* end)
{
	if( document[0] == 'l' && document[1] == 't' )
		return "<";
	else
	if( document[0] == 'g' && document[1] == 't' )
		return ">";
	else
	if( document[0] == 'a' && document[1] == 'm' && document[2] == 'p' )
		return "&";
	else
	{
		return mystd::string();
	}
}


const char* XMLElement::SkipTag(const char* document, const char* end)
{
	const char* i;

	for( i = document; *i != '\0'; ++i )
		if( *i == '>' )
			break;
	
	return i + 1;
}


////////////////////////////////////////


XMLDocument::XMLDocument()
: m_root("XMLDocument"), m_buf(NULL)
{
}


XMLDocument::~XMLDocument()
{
	this->XMLDocument::Clear();
}


void XMLDocument::Clear()
{
	m_root.XMLElement::Clear();

	if( m_buf != NULL )
	{
		delete[] m_buf;
		m_buf = NULL;
	}
}


bool XMLDocument::ReadDocument(const char* document, const char* end)
{
	if( m_root.XMLElement::GetChild() != NULL )
	{
		Trace("이전 XMLDocument를 삭제합니다.!!"); // "Previous XMLDocument deleted.!!"
		this->XMLDocument::Clear();
	}

	int size = end - document;
	m_buf = new char[size + 1];
	memcpy(m_buf, document, size);
	m_buf[size] = '\0';

	m_root.XMLElement::SetStart(&m_buf[0]);
	m_root.XMLElement::SetEnd(&m_buf[size]);

	this->XMLDocument::ReadContents(&m_root, &m_buf[0], &m_buf[size]);
	return ( m_root.XMLElement::GetChild() != NULL );
}


XMLElement* XMLDocument::GetRootElement()
{
	return &m_root;
}


XMLElement* XMLDocument::FindElement(const char* name)
{
	return m_root.XMLElement::FindChild(name);
}


const char* XMLDocument::ReadContents(XMLElement* element, const char* document, const char* end)
{
	const char* p = document;
	while( p != end )
	{
		if( XMLDocument::IsTag(p) )
		{
			if( this->XMLDocument::IsEndTag(p) )
			{
				// find end of tag name
				const char* tag_end = this->XMLDocument::SkipTag(p, end);

				// isolate tag name
				const char* tagname = this->XMLDocument::ParseTag(p + 2, end);

				p = tag_end;

				if( strcmp(tagname, element->XMLElement::GetName()) == 0 )
				{// found end of root element
					element->XMLElement::SetEnd(tag_end);
					return p; // done.
				}
			}
			else
			{
				p = this->XMLDocument::ReadElement(element, p, end);
			}
		}
		else
		if( XMLDocument::IsEntity(p) )
		{
			p = XMLDocument::SkipEntity(p, end);
		}
		else
		{// normal character
			++p;
		}
	};

	return p;
}


const char* XMLDocument::ReadElement(XMLElement* parent, const char* document, const char* end)
{
	const char* result;

	if( this->XMLDocument::IsPITag(document) )
	{
		result = this->XMLDocument::SkipTag(document, end);
	}
	else
	if( this->XMLDocument::IsCommentTag(document) )
	{
		result = this->XMLDocument::SkipTag(document, end);
	}
	else
	{
		result = this->XMLDocument::SkipTag(document, end);

		XMLElement* node = new XMLElement(this->XMLDocument::ParseTag(document + 1, end));
		parent->XMLElement::AddChild(node);

		if( !this->XMLDocument::IsClosedTag(result, end) )
		{
			node->XMLElement::SetStart(document);
			result = this->XMLDocument::ReadContents(node, result, end);
		}
	}

	return result;
}


bool XMLDocument::IsEndTag(const char* document)
{
	return ( *(document + 1) == '/' );
}


bool XMLDocument::IsPITag(const char* document)
{
	return ( *(document + 1) == '?' );
}


bool XMLDocument::IsCommentTag(const char* document)
{
	return ( *(document + 1) == '!' );
}


bool XMLDocument::IsClosedTag(const char* document, const char* end)
{
	return ( *(document - 2) == '/' );
}


const char* XMLDocument::SkipTag(const char* document, const char* end)
{
	const char* i;

	for( i = document; i != end - 1; ++i )
		if( *i == '>' )
			break;

	return i + 1;
}


const char* XMLDocument::ParseTag(const char* document, const char* end)
{
	// locate end of tag name
	const char* i;
	for( i = document; i != end; ++i )
		if( *i == ' ' || *i == '\t' || *i == '>' || *i == '/' )
			break;

	// cut off string here
	*const_cast<char*>(i) = '\0'; //FIXME: don't use const then!

	return document;
}


bool XMLDocument::IsTag(const char* document) /// @custom
{
	return ( *document == '<' );
}


bool XMLDocument::IsEntity(const char* document) /// @custom
{
	return ( *document == '&' );
}


const char* XMLDocument::SkipEntity(const char* document, const char* end) /// @custom
{
	const char* i;

	for( i = document; i != end; ++i )
		if( *i == ';' )
			break;

	return i + 1;
}


////////////////////////////////////////
