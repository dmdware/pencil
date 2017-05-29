



#ifndef GUI_H
#define GUI_H

#include "../platform.h"
#include "widget.h"

class GUI : public Widget
{
public:
	void (*keyupfunc[SDL_NUM_SCANCODES])();
	void (*keydownfunc[SDL_NUM_SCANCODES])();
	void (*anykeyupfunc)(int32_t k);
	void (*anykeydownfunc)(int32_t k);
	void (*mousemovefunc)(InEv* ie);
	void (*lbuttondownfunc)();
	void (*lbuttonupfunc)();
	void (*rbuttondownfunc)();
	void (*rbuttonupfunc)();
	void (*mbuttondownfunc)();
	void (*mbuttonupfunc)();
	void (*mousewheelfunc)(int32_t delta);
	Widget* activewidg;

	GUI() : Widget()
	{
		m_type = WIDGET_GUI;

		for(int32_t i=0; i<SDL_NUM_SCANCODES; i++)
		{
			keyupfunc[i] = NULL;
			keydownfunc[i] = NULL;
		}
		
		anykeyupfunc = NULL;
		anykeydownfunc = NULL;
		lbuttondownfunc = NULL;
		lbuttonupfunc = NULL;
		rbuttondownfunc = NULL;
		rbuttonupfunc = NULL;
		mbuttondownfunc = NULL;
		mbuttonupfunc = NULL;
		mousewheelfunc = NULL;
		mousemovefunc = NULL;

		m_hidden = false;
	}

	void assignmousewheel(void (*wheel)(int32_t delta))
	{
		mousewheelfunc = wheel;
	}

	void assignlbutton(void (*down)(), void (*up)())
	{
		lbuttondownfunc = down;
		lbuttonupfunc = up;
	}

	void assignrbutton(void (*down)(), void (*up)())
	{
		rbuttondownfunc = down;
		rbuttonupfunc = up;
	}

	void assignmbutton(void (*down)(), void (*up)())
	{
		mbuttondownfunc = down;
		mbuttonupfunc = up;
	}

	void assignmousemove(void (*mouse)(InEv* ie))
	{
		mousemovefunc = mouse;
	}

	void assignkey(int32_t i, void (*down)(), void (*up)())
	{
		keydownfunc[i] = down;
		keyupfunc[i] = up;
	}

	void assignanykey(void (*down)(int32_t k), void (*up)(int32_t k))
	{
		anykeydownfunc = down;
		anykeyupfunc = up;
	}

	void draw();
	void drawover(){}
	void inev(InEv* ie);
	void reframe();
};

extern GUI g_gui;

bool MousePosition();
void CenterMouse();
void Status(const char* status, bool logthis=false);
void Ortho(int32_t width, int32_t height, float r, float g, float b, float a);

#endif
