


#include "../../app/appmain.h"
#include "../../gui/gui.h"
#include "../../gui/widgets/winw.h"
#include "../../gui/widgets/editbox.h"
#include "../../gui/widgets/droplist.h"
#include "../../debug.h"
#include "../../window.h"
#include "../../algo/localmap.h"

char g_lastsave[DMD_MAX_PATH+1];

void Resize_Fullscreen(Widget* w)
{
	w->m_pos[0] = 0;
	w->m_pos[1] = 0;
	w->m_pos[2] = (float)g_width-1;
	w->m_pos[3] = (float)g_height-1;

#if 0
	if(w->m_type == WIDGET_IMAGE)
	{
		Texture* tex = &g_texture[w->m_tex];
	
		w->m_texc[0] = w->m_pos[0] / (float)tex->width;
		w->m_texc[1] = w->m_pos[1] / (float)tex->height;
		w->m_texc[2] = w->m_pos[2] / (float)tex->width;
		w->m_texc[3] = w->m_pos[3] / (float)tex->height;
	}
#endif
}

void Resize_FullscreenSq(Widget* w)
{
	float minsz = fmin((float)g_width-1, (float)g_height-1);

	w->m_pos[0] = g_width/2.0f - minsz/2.0f;
	w->m_pos[1] = g_height/2.0f - minsz/2.0f;
	w->m_pos[2] = g_width/2.0f + minsz/2.0f;
	w->m_pos[3] = g_height/2.0f + minsz/2.0f;

#if 0
	if(w->m_type == WIDGET_IMAGE)
	{
		Texture* tex = &g_texture[w->m_tex];
	
		w->m_texc[0] = w->m_pos[0] / (float)tex->width;
		w->m_texc[1] = w->m_pos[1] / (float)tex->height;
		w->m_texc[2] = w->m_pos[2] / (float)tex->width;
		w->m_texc[3] = w->m_pos[3] / (float)tex->height;
	}
#endif
}

void Resize_AppLogo(Widget* w)
{
	w->m_pos[0] = 30;
	w->m_pos[1] = 30;
	w->m_pos[2] = 200;
	w->m_pos[3] = 200;
}

void Resize_AppTitle(Widget* w)
{
	w->m_pos[0] = 30;
	w->m_pos[1] = 30;
	w->m_pos[2] = (float)g_width-1;
	w->m_pos[3] = 100;
}

void Resize_MenuItem(Widget* w)
{
	int32_t row;
	sscanf(w->m_name.c_str(), "%d", &row);
	Font* f = &g_font[w->m_font];

	//w->m_pos[0] = g_width/2 - f->gheight*4;
	w->m_pos[0] = f->gheight*4;
	w->m_pos[1] = g_height/2 - f->gheight*4 + f->gheight*1.5f*row;
	w->m_pos[2] = w->m_pos[0] + f->gheight * 10;
	w->m_pos[3] = w->m_pos[1] + f->gheight;
}

void Resize_LoadingStatus(Widget* w)
{
	w->m_pos[0] = g_width/2 - 64;
	w->m_pos[1] = g_height/2;
	w->m_pos[2] = g_width;
	w->m_pos[3] = g_height;
	w->m_tpos[0] = g_width/2;
	w->m_tpos[1] = g_height/2;
}

void Resize_WinText(Widget* w)
{
	Widget* parent = w->m_parent;

	w->m_pos[0] = parent->m_pos[0];
	w->m_pos[1] = parent->m_pos[1];
	w->m_pos[2] = w->m_pos[0] + 400;
	w->m_pos[3] = w->m_pos[1] + 2000;
}

void EnumDisplay()
{
	g_resolution.clear();
	
	for(int32_t i=0; i<SDL_GetNumDisplayModes(0); i++)
	{
		SDL_DisplayMode mode;
		SDL_GetDisplayMode(0, i, &mode);
		
		bool found = false;
		
		for(std::vector<Resolution>::iterator rit=g_resolution.begin(); rit!=g_resolution.end(); rit++)
		{
			if(rit->width == mode.w &&
			   rit->height == mode.h)
			{
				found = true;
				break;
			}
		}
		
		if(found)
			continue;
		
#ifdef PLATFORM_MOBILE
		//landscape only
		if(mode.h > mode.w)
			continue;
		
		if(mode.h < 480)
			continue;
#endif
		
		Resolution res;
		res.width = mode.w;
		res.height = mode.h;
		g_resolution.push_back(res);
	}
}

void Resize_Win(Widget* w)
{
	w->m_pos[0] = 20;
	w->m_pos[1] = 90;
	w->m_pos[2] = 400;
	w->m_pos[3] = 700;
}

void Resize_Enter(Widget* w)
{
	Widget* parw = w->m_parent;
	Font* f = &g_font[w->m_font];

	w->m_pos[0] = parw->m_pos[0] + 10;
	w->m_pos[1] = parw->m_pos[1] + 10;
	w->m_pos[2] = parw->m_pos[0] + 10 + f->gheight*20;
	w->m_pos[3] = parw->m_pos[1] + 10 + f->gheight;
}

void Resize_Box(Widget* w)
{
	Widget* parw = w->m_parent;
	Font* f = &g_font[w->m_font];

	int x = 0;
	int y = 0;
	sscanf(w->m_name.c_str(), "%d %d", &x, &y);
	y++;

	w->m_pos[0] = parw->m_pos[0] + 10 + f->gheight*3 * x;
	w->m_pos[1] = parw->m_pos[1] + 10 + f->gheight * y;
	w->m_pos[2] = parw->m_pos[0] + 10 + f->gheight*3 * (1+x);
	w->m_pos[3] = parw->m_pos[1] + 10 + f->gheight*(y+1);
}

void Click_Button()
{
	GUI* gui = &g_gui;
	
	Win* mainw = (Win*)gui->get("main");

	int i = 0;

	for(int x=0; x<3*2; x++)
	{
		for(int y=0; y<4; y++)
		{
			char n[12];
			sprintf(n, "%d %d", x, y);

			EditBox* e = (EditBox*)mainw->get(n);

			sscanf(e->m_value.rawstr().c_str(), "%hhu", &m[i]);

			++i;
		}
	}

	DropList* drop = (DropList*)mainw->get("drop");
	mode = drop->m_selected;
}

void Resize_Drop(Widget* w)
{
	Widget* parw = w->m_parent;
	Font* f = &g_font[w->m_font];

	int x = 0;
	int y = 1+4+0;

	w->m_pos[0] = parw->m_pos[0] + 10 + f->gheight*7 * 0;
	w->m_pos[1] = parw->m_pos[1] + 10 + f->gheight * y;
	w->m_pos[2] = parw->m_pos[0] + 10 + f->gheight*7 * (1+0);
	w->m_pos[3] = parw->m_pos[1] + 10 + f->gheight*(y+1);
}

void Resize_Button(Widget* w)
{
	Widget* parw = w->m_parent;
	Font* f = &g_font[w->m_font];

	int x = 0;
	int y = 1+4+2;

	w->m_pos[0] = parw->m_pos[0] + 10 + f->gheight*5 * 0;
	w->m_pos[1] = parw->m_pos[1] + 10 + f->gheight * y;
	w->m_pos[2] = parw->m_pos[0] + 10 + f->gheight*5 * (1+0);
	w->m_pos[3] = parw->m_pos[1] + 10 + f->gheight*(y+1);
}

void Resize_Text(Widget* w)
{
	Widget* parw = w->m_parent;
	Font* f = &g_font[w->m_font];

	int x = 0;
	int y = 0;
	sscanf(w->m_name.c_str(), "%d %d", &x, &y);
	y+=9;

	w->m_pos[0] = parw->m_pos[0] + 10 + f->gheight*7 * x;
	w->m_pos[1] = parw->m_pos[1] + 10 + f->gheight * y;
	w->m_pos[2] = parw->m_pos[0] + 10 + f->gheight*7 * (1+x);
	w->m_pos[3] = parw->m_pos[1] + 10 + f->gheight*(y+1);
}

void FillGUI()
{
	GUI* gui = &g_gui;
	
	gui->add(new Win(gui, "main", Resize_Win));
	Win* mainw = (Win*)gui->get("main");

	mainw->add(new Text(mainw, "enter", RichText("Enter 0 to 255:"), MAINFONT16, Resize_Enter));

	for(int x=0; x<3*2; x++)
	{
		for(int y=0; y<4; y++)
		{
			char n[12];
			sprintf(n, "%d %d", x, y);
			char v[12];
			sprintf(v, "%d", (int)m[x+y*3*2]);
			mainw->add(new EditBox(mainw, n,
				RichText(v), MAINFONT16, Resize_Box,
				false, 4, NULL, NULL, -1));
		}
	}

	mainw->add(new DropList(mainw, "drop", MAINFONT16, Resize_Drop, NULL));
	DropList* drop = (DropList*)mainw->get("drop");
	drop->m_options.push_back(RichText("Output to input"));
	drop->m_options.push_back(RichText("Time to input"));
	drop->m_options.push_back(RichText("Counter to input"));
	
	mainw->add(new Button(mainw, "button", "gui/p.png", RichText("Adjust"),
		RichText(""), MAINFONT16, BUST_LEFTIMAGE, Resize_Button, Click_Button,
		NULL, NULL, NULL, NULL, -1, NULL));
	
	mainw->add(new Text(mainw, "0 0", RichText("out bit 0=move(+1,0)"), MAINFONT16, Resize_Text));
	mainw->add(new Text(mainw, "0 1", RichText("out bit 1=move(-1,0)"), MAINFONT16, Resize_Text));
	mainw->add(new Text(mainw, "0 2", RichText("out bit 2=move(0,+1)"), MAINFONT16, Resize_Text));
	mainw->add(new Text(mainw, "0 3", RichText("out bit 3=move(0,-1)"), MAINFONT16, Resize_Text));

	mainw->add(new Text(mainw, "0 4", RichText("out bit 4=move(+3,0)"), MAINFONT16, Resize_Text));
	mainw->add(new Text(mainw, "0 5", RichText("out bit 5=move(-3,0)"), MAINFONT16, Resize_Text));
	mainw->add(new Text(mainw, "0 6", RichText("out bit 6=move(0,+3)"), MAINFONT16, Resize_Text));
	mainw->add(new Text(mainw, "0 7", RichText("out bit 7=move(0,-3)"), MAINFONT16, Resize_Text));

	gui->show("main");
}
