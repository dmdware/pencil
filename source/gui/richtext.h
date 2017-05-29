

#ifndef RICHTEXT_H
#define RICHTEXT_H

#include "../platform.h"
#include "../ustring.h"

#define RICH_TEXT		0
#define RICH_ICON		1

// Rich text part
class RichPart
{
public:
	int32_t m_type;
	int32_t m_icon;
	UStr m_text;
	int32_t texlen() const;	//each icon counts as 1
	int32_t rawlen() const;	//icon tags are counted
	std::string texval() const;
	RichPart substr(int32_t start, int32_t length) const;
	RichPart();
	RichPart(const RichPart& original);
	RichPart(const char* cstr);
	RichPart(UStr ustr);
	RichPart& operator=(const RichPart &original);
	RichPart(int32_t type, int32_t subtype);
};

class RichText
{
public:
	std::list<RichPart> m_part;
	std::string rawstr() const;
	int32_t texlen() const;	//each icon counts as 1
	int32_t rawlen() const;	//icon tags are counted
	RichText pwver() const;	//asterisk-mask password std::string
	RichText();
	RichText(const RichPart& part);
	RichText(const RichText& original);
	RichText(const char* cstr);
	RichText& operator=(const RichText &original);
	RichText operator+(const RichText &other);
	RichText substr(int32_t start, int32_t length) const;
	//RichText parsetags(int32_t* caret) const;
};

RichText ParseTags(RichText original, int32_t* caret);

#endif
