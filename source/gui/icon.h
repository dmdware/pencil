

#ifndef ICON_H
#define ICON_H

#include "../platform.h"
#include "../ustring.h"

class Icon
{
public:
	uint32_t m_tex;
	int32_t m_width;
	int32_t m_height;
	UStr m_tag;

	Icon()
	{
		m_tag = UStr("\\not");
	}
};

#define ICONS				37

extern Icon g_icon[ICONS];

#ifndef MATCHMAKER
void DefI(int32_t type, const char* relative, const char* tag);
#endif

#endif
