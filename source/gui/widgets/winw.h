


#ifndef WINDOWW_H
#define WINDOWW_H

#include "../widget.h"
#include "image.h"
#include "text.h"
#include "button.h"
#include "../draw2d.h"
#include "../../render/shader.h"
#include "../cursor.h"

class Win : public Widget
{
public:

	Image bg_logo_image;

	Text title_text;
	//VScroll m_vscroll;
	
	Button m_trclose;	//top right close
	Button m_trfull;	//top full size toggle
	float prevpos[4];	//for fullscreen toggle

	int32_t m_mousedown[2];

	Win();
	Win(Widget* parent, const char* n, void (*reframef)(Widget* w));

	virtual void fillout(float* outpos);
	virtual void show();
	virtual void inev(InEv* ie);
	virtual void draw();
	virtual void drawover();
	virtual void reframe();
	virtual void chcall(Widget* ch, int32_t type, void* data);
	virtual void subframe(float* fr);
	void fullsize();	//toggle fullscreen size
};

#endif
