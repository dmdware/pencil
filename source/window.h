




#ifndef WINDOW_H
#define WINDOW_H

#include "platform.h"

#include "math/vec2i.h"

#define INI_WIDTH			900
#define INI_HEIGHT			800
#define INI_BPP				32
#define DRAW_FRAME_RATE		30
#define SIM_FRAME_RATE		30
//#define DRAW_FRAME_RATE			5
#define MIN_DISTANCE		1.0f
//#define MAX_DISTANCE		(100 * 1000 * 10.0f) //10km
//#define MAX_DISTANCE		(10 * 1000 * 10.0f) //10km
#define MAX_DISTANCE		(5.0f * 1000.0f * 1000.0f) //10km
#define FIELD_OF_VIEW		90.0f
//#define PROJ_LEFT			(-16*4)
#define PROJ_RIGHT			600 //(500)	//(30*12.5f)
//#define PROJ_TOP			(16*4)
//#define PROJ_BOTTOM			(-16*4)
//#define INI_ZOOM			0.025f
//#define MIN_ZOOM		0.1f
//#define MIN_ZOOM		0.025f
//#define MIN_ZOOM		0.005f
#define MIN_ZOOM		0.05f
#define MAX_ZOOM		0.7f
//#define MAX_ZOOM		0.1f
//#define INI_ZOOM			MIN_ZOOM
#define INI_ZOOM			0.05f

extern double g_drawfrinterval;
extern bool g_quit;
extern bool g_background;
extern bool g_active;
extern bool g_fullscreen;
#if 0
extern double g_currentTime;
extern double g_lastTime;
extern double g_framesPerSecond;
#endif
extern double g_instantdrawfps;
extern double g_instantupdfps;
extern double g_updfrinterval;

struct Resolution
{
	int32_t width;
	int32_t height;
};

extern Resolution g_selres;
extern std::vector<Resolution> g_resolution;
extern std::vector<int32_t> g_bpps;

extern int32_t g_currw;
extern int32_t g_currh;
extern int32_t g_width;
extern int32_t g_height;
extern int32_t g_bpp;
extern Vec2i g_mouse;
extern Vec2i g_mousestart;
extern bool g_keyintercepted;
extern bool g_keys[SDL_NUM_SCANCODES];
extern bool g_mousekeys[5];
extern float g_zoom;
extern bool g_mouseout;
extern bool g_moved;
extern bool g_mouseoveraction;
extern int32_t g_curst;	//cursor state
extern int32_t g_kbfocus;	//keyboad focus counter

void AddRes(int32_t w, int32_t h);
void CalcDrawRate();
bool DrawNextFrame();
void CalcUpdRate();
bool UpdNextFrame();
void EnumerateDisplay();
void Resize(int32_t width, int32_t height);
void BreakWin(const char* title);
bool MakeWin(const char* title);

#endif
