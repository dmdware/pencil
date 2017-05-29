

#include "gui.h"
#include "../render/shader.h"

GUI g_gui;

void GUI::draw()
{
	glClear(GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);
	CHECKGLERROR();
	Ortho(g_width, g_height, 1, 1, 1, 1);
	CHECKGLERROR();

	Widget::draw();
	CHECKGLERROR();
	Widget::drawover();
	
	CHECKGLERROR();

	EndS();
	CHECKGLERROR();

	UseS(SHADER_COLOR2D);
	glUniform1f(g_shader[SHADER_COLOR2D].slot[SSLOT_WIDTH], (float)g_width);
	glUniform1f(g_shader[SHADER_COLOR2D].slot[SSLOT_HEIGHT], (float)g_height);
	glUniform4f(g_shader[SHADER_COLOR2D].slot[SSLOT_COLOR], 0, 1, 0, 0.75f);
	//glEnable(GL_DEPTH_TEST);
	//DrawMarquee();

	CHECKGLERROR();
	EndS();
	CHECKGLERROR();

	glEnable(GL_DEPTH_TEST);
}

void GUI::inev(InEv* ie)
{
#ifdef PLATFORM_MOBILE
	if(ie->type == INEV_MOUSEDOWN ||
	   ie->type == INEV_MOUSEUP)
	{
		InEv ie2 = *ie;
		ie2.type = INEV_MOUSEMOVE;
		ie2.intercepted = false;
		ie2.interceptor = NULL;
		Widget::inev(&ie2);
	}
#endif
	
	Widget::inev(ie);

	if(!ie->intercepted)
	{
		//if(ie->type == INEV_MOUSEUP && ie->key == MOUSE_LEFT) Log("mouse up l");

		if(ie->type == INEV_MOUSEMOVE && mousemovefunc) mousemovefunc(ie);
		else if(ie->type == INEV_MOUSEDOWN && ie->key == MOUSE_LEFT && lbuttondownfunc) lbuttondownfunc();
		else if(ie->type == INEV_MOUSEUP && ie->key == MOUSE_LEFT && lbuttonupfunc) lbuttonupfunc();
		else if(ie->type == INEV_MOUSEDOWN && ie->key == MOUSE_MIDDLE && mbuttondownfunc) mbuttondownfunc();
		else if(ie->type == INEV_MOUSEUP && ie->key == MOUSE_MIDDLE && mbuttonupfunc) mbuttonupfunc();
		else if(ie->type == INEV_MOUSEDOWN && ie->key == MOUSE_RIGHT && rbuttondownfunc) rbuttondownfunc();
		else if(ie->type == INEV_MOUSEUP && ie->key == MOUSE_RIGHT && rbuttonupfunc) rbuttonupfunc();
		else if(ie->type == INEV_MOUSEWHEEL && mousewheelfunc) mousewheelfunc(ie->amount);
		else if(ie->type == INEV_KEYDOWN && keydownfunc[ie->scancode]) keydownfunc[ie->scancode]();
		else if(ie->type == INEV_KEYUP && keyupfunc[ie->scancode]) keyupfunc[ie->scancode]();
		//cse fix
		else if(ie->type == INEV_COPY && keydownfunc[ie->scancode]) keydownfunc[ie->scancode]();
		else if(ie->type == INEV_PASTE && keydownfunc[ie->scancode]) keydownfunc[ie->scancode]();

		if(ie->type != INEV_MOUSEMOVE && anykeydownfunc) anykeydownfunc(-1);
	}
}

void GUI::reframe()
{
	m_pos[0] = 0;
	m_pos[1] = 0;
	m_pos[2] = g_width-1;
	m_pos[3] = g_height-1;

	Widget::reframe();
}

bool MousePosition()
{
	Vec2i old = g_mouse;
	SDL_GetMouseState(&g_mouse.x, &g_mouse.y);

	if(g_mouse.x == old.x && g_mouse.y == old.y)
		return false;

	return true;
}

void CenterMouse()
{
	g_mouse.x = g_width/2;
	g_mouse.y = g_height/2;
	
#ifndef PLATFORM_MOBILE
	SDL_WarpMouseInWindow(g_window, g_mouse.x, g_mouse.y);
#else
	//for mobile, half of real screen is full "drawing" screen
	SDL_WarpMouseInWindow(g_window, g_mouse.x*2, g_mouse.y*2);
#endif
}

void Ortho(int32_t width, int32_t height, float r, float g, float b, float a)
{
	CHECKGLERROR();
	UseS(SHADER_ORTHO);
	Shader* s = &g_shader[g_curS];
	glUniform1f(s->slot[SSLOT_WIDTH], (float)width);
	glUniform1f(s->slot[SSLOT_HEIGHT], (float)height);
	glUniform4f(s->slot[SSLOT_COLOR], r, g, b, a);
	//glEnableVertexAttribArray(s->slot[SSLOT_POSITION]);
	//glEnableVertexAttribArray(g_shader[SHADER_ORTHO].slot[SSLOT_TEXCOORD0]);
	//glEnableVertexAttribArray(g_shader[SHADER_ORTHO].slot[SSLOT_NORMAL]);
	g_currw = width;
	g_currh = height;
	CHECKGLERROR();
}
