

#include "appmain.h"
#include "../debug.h"
#include "../utils.h"
#include "../gui/gui.h"
#include "../gui/cursor.h"
#include "../gui/draw2d.h"
#include "../math/matrix.h"
#include "../math/vec3f.h"
#include "../math/3dmath.h"
#include "../render/shader.h"
#include "../algo/localmap.h"
#include "../gui/layouts/appgui.h"

LoadedTex board;
Vec2i penpos = Vec2i(INI_WIDTH/2,INI_HEIGHT/2);
HASHINT lasthash = -1;
HASHINT lasthashi = -1;
unsigned int boardtexn = -1;
unsigned int penrgb = 0xffffffff;
int mode = 0;

unsigned int hashtexn = -1;

#define HASHTEXW	64
#define HASHTEXH	(3*(HASHLEVELS+2)+30)

void MakeTex()
{
	glDeleteTextures(1, &hashtexn);

	LoadedTex out;
	AllocTex(&out, HASHTEXW, HASHTEXH, 4);
	memset(out.data, 0, HASHTEXW*HASHTEXH*4);

	//HASHINT masks[HASHLEVELS];
	//memset(masks, 0, sizeof(HASHINT)*HASHLEVELS);

	int sqx = 0;
	int sqy = 0;

	int sqw = (1+HASHBITS*1)+1;
	int sqh = (1+2)*HASHLEVELS+2+2+2;

	//while(true)
	{	
		//try inputs
		//HASHINT i=0;
		HASHINT i=lasthashi;
		//while(true)
		{
			int x = sqx*sqw;
			int y = (sqy+1)*sqh;

			//i
			for(int b=0; b<HASHBITS; ++b)
			{
				if(i&(1<<b))
					out.data[((x+b*1)+y*HASHTEXW)*4+0] = 255;
				else
					out.data[((x+b*1)+y*HASHTEXW)*4+0] = 63;
				out.data[((x+b*1)+y*HASHTEXW)*4+3] = 255;
			}

			y-=2;

			HASHINT s = HASHROTL(i,1);
			HASHINT o = i;

			for(int l=0; l<HASHLEVELS; ++l)
			{
				o = HASHCROP( s ^ ~(m[l] & o) );
				s = HASHROTL(o,1);

				int b;

				//m
				for(b=0; b<HASHBITS; ++b)
				{
					if(m[l]&(1<<b))
					{
						out.data[((x+b*1)+y*HASHTEXW)*4+0] = 255;
						out.data[((x+b*1)+y*HASHTEXW)*4+1] = 255;
						out.data[((x+b*1)+y*HASHTEXW)*4+2] = 255;
					}
					else
					{
						out.data[((x+b*1)+y*HASHTEXW)*4+0] = 63;
						out.data[((x+b*1)+y*HASHTEXW)*4+1] = 63;
						out.data[((x+b*1)+y*HASHTEXW)*4+2] = 63;
					}
					out.data[((x+b*1)+y*HASHTEXW)*4+3] = 255;
				}

				y--;

				//o
				for(b=0; b<HASHBITS; ++b)
				{
					if(o&(1<<b))
						out.data[((x+b*1)+y*HASHTEXW)*4+0] = 255;
					else
						out.data[((x+b*1)+y*HASHTEXW)*4+0] = 63;
					out.data[((x+b*1)+y*HASHTEXW)*4+3] = 255;
				}

				y-=2;
			}

#if 0
			//next square
			if((sqy+2)*sqh >= HASHTEXH)
			{
				goto next1;
			}
			else if((sqx+2)*sqw >= HASHTEXW)
			{
				sqx=0;
				sqy++;
			}
			else
			{
				sqx++;
			}

			if(i==MAXHASH)
				break;

			++i;
#endif
		}
		
#if 0
		//next mask
		for(int l=0; l<HASHLEVELS; ++l)
		{
			if(masks[l] < MAXHASH)
			{
				masks[l]++;

				for(--l; l>=0; --l)
					masks[l] = 0;

				break;
			}		

			if(l+1==HASHLEVELS)
				goto next1;
		}

		//next square
		if((sqy+2)*sqh >= HASHTEXH)
		{
			goto next1;
		}
		else if((sqx+2)*sqw >= HASHTEXW)
		{
			sqx=0;
			sqy++;
		}
		else
		{
			sqx++;
		}
#endif
	}

//next1:
	//unsigned int texi;
	//unsigned int hashtexn;
	CreateTex(&out, &hashtexn, true, false);
}

void Update()
{
	//srand(GetTicks());
//	srand(1231283992);
//	for(int l=0; l<HASHLEVELS; ++l)
//		m[l] = rand()%(1+MAXHASH);
//	m[0] = 1;
//	m[1] = 2;
//	m[2] = 2;
//	m[3] = 7;
//	m[4] = 0;
//	m[5] = 0;
	//for(int l=4; l<HASHLEVELS; ++l)
	//	m[l] = rand()%(1+MAXHASH);
#if 0	
	m[0]=6;
	m[1]=0;
	m[2]=0;
	m[3]=0;
	m[4]=3;
	m[5]=0;
	m[6]=4;
	m[7]=111;
	m[8]=78;
	m[9]=0;
	m[10]=0;
	m[11]=9;
	m[12]=121;
	m[13]=0;
	m[14]=0;
	m[15]=0;
	m[16]=34;
	m[17]=0;
	m[18]=0;
	m[19]=6;
	m[20]=0;
	m[21]=201;
	m[22]=234;
	m[23]=0;
#endif

	lasthashi = lasthash;

	MakeTex();

	static int count = 0;
	if(mode == 0)
		lasthash = Hash(m, lasthash, 0, false);
	if(mode == 1)	
		lasthash = Hash(m, (GetTicks()%(1+MAXHASH)), 0, false);
	if(mode == 2)
		lasthash = Hash(m, (count++)%(1+MAXHASH), 0, false);

	board.data[(penpos.x+penpos.y*INI_WIDTH)*3+0] = (penrgb&(255<<0))>>0;
	board.data[(penpos.x+penpos.y*INI_WIDTH)*3+1] = (penrgb&(255<<8))>>8;
	board.data[(penpos.x+penpos.y*INI_WIDTH)*3+2] = (penrgb&(255<<16))>>16;

	if(lasthash&(1<<0))
	//if(lasthash%4==0)
		penpos.x = (penpos.x+1)%INI_WIDTH;
	//else
	//	penpos.x = (penpos.x+INI_WIDTH-1)%INI_WIDTH;
	if(lasthash&(1<<1))
	//if(lasthash%4==1)
		penpos.y = (penpos.y+1)%INI_HEIGHT;
	//else
	//	penpos.y = (penpos.y+INI_HEIGHT-1)%INI_HEIGHT;

	if(lasthash&(1<<2))
	//if(lasthash%4==2)
		penpos.x = (penpos.x+INI_WIDTH-1)%INI_WIDTH;
		//penpos.x = (penpos.x+3)%INI_WIDTH;
		//penrgb = (~(penrgb^(255<<8)));	//toggle
	if(lasthash&(1<<3))
	//if(lasthash%4==3)
		penpos.y = (penpos.y+INI_HEIGHT-1)%INI_HEIGHT;
		//penrgb = (~(penrgb^(255<<16)));
#if 1

	if(lasthash&(1<<4))
		penpos.x = (penpos.x+3)%INI_WIDTH;
	//else
	//	penpos.x = (penpos.x+INI_WIDTH-1)%INI_WIDTH;
	if(lasthash&(1<<5))
		penpos.y = (penpos.y+3)%INI_HEIGHT;
	//else
	//	penpos.y = (penpos.y+INI_HEIGHT-1)%INI_HEIGHT;

	if(lasthash&(1<<6))
		penpos.x = (penpos.x+INI_WIDTH-3)%INI_WIDTH;
		//penpos.x = (penpos.x+3)%INI_WIDTH;
		//penrgb = (~(penrgb^(255<<8)));	//toggle
	if(lasthash&(1<<7))
		penpos.y = (penpos.y+INI_HEIGHT-3)%INI_HEIGHT;
		//penrgb = (~(penrgb^(255<<16)));
#endif
	glDeleteTextures(1, &boardtexn);
	CreateTex(&board, &boardtexn, true, false);
}

void Draw()
{
	GUI* gui = &g_gui;

	Ortho(g_width, g_height, 1,1,1,1);
	//RichText r = RichText("Физика Относительность Наука русский транз лекция гершейн");
	float color[] = {1,1,1,1};
	//DrawLine(MAINFONT8, 0, 10, &r, color);

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	float crop[] = {0,0,(float)g_width,(float)g_height};


	RichText r = RichText("lm8");
	//float color[] = {1,1,1,1};
	DrawLine(MAINFONT8, 0, 10, &r, color);

	DrawImage(boardtexn, 0, 0, INI_WIDTH, INI_HEIGHT, 0, 0, 1, 1, crop);
	DrawImage(hashtexn, 
		g_width-10-HASHTEXW*4, 
		g_height-10-HASHTEXH*4, 
		g_width-10, 
		g_height-10, 
		0, 0, 1, 1, crop);

	gui->draw();
	EndS();
	gui->frameupd();
}

// Define the function to be called when ctrl-c (SIGINT) signal is sent to process
void SignalCallback(int32_t signum)
{
	//printf("Caught signal %d\n",signum);
	// Cleanup and hide up stuff here

	// Terminate program
	//g_quit = true;
	exit(0);	//force quit NOW
}

void Init()
{
#ifdef PLATFORM_LINUX
	signal(SIGINT, SignalCallback);
#endif
	
	g_selres.width = INI_WIDTH;
	g_selres.height = INI_HEIGHT;

	OpenLog("log.txt", VERSION);

	SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_VERBOSE);
	SDL_LogSetPriority(SDL_LOG_CATEGORY_ERROR, SDL_LOG_PRIORITY_VERBOSE);
	SDL_LogSetPriority(SDL_LOG_CATEGORY_SYSTEM, SDL_LOG_PRIORITY_VERBOSE);
	SDL_LogSetPriority(SDL_LOG_CATEGORY_AUDIO, SDL_LOG_PRIORITY_VERBOSE);
	SDL_LogSetPriority(SDL_LOG_CATEGORY_VIDEO, SDL_LOG_PRIORITY_VERBOSE);
	SDL_LogSetPriority(SDL_LOG_CATEGORY_RENDER, SDL_LOG_PRIORITY_VERBOSE);
	SDL_LogSetPriority(SDL_LOG_CATEGORY_INPUT, SDL_LOG_PRIORITY_VERBOSE);
	SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);
	//SDL_LogSetOutputFunction(log, NULL);

	SDL_SetHint(SDL_HINT_VIDEO_HIGHDPI_DISABLED, "0");
	
	if(SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		char msg[1280];
		sprintf(msg, "SDL_Init: %s\n", SDL_GetError());
		ErrMess("Error", msg);
	}

#if 0

	if(SDLNet_Init() == -1)
	{
		char msg[1280];
		sprintf(msg, "SDLNet_Init: %s\n", SDLNet_GetError());
		ErrMess("Error", msg);
	}

	SDL_version compile_version;
	const SDL_version *link_version=Mix_Linked_Version();
	SDL_MIXER_VERSION(&compile_version);
	printf("compiled with SDL_mixer version: %d.%d.%d\n",
		compile_version.major,
		compile_version.minor,
		compile_version.patch);
	printf("running with SDL_mixer version: %d.%d.%d\n",
		link_version->major,
		link_version->minor,
		link_version->patch);

	// load support for the OGG and MOD sample/music formats
	//int32_t flags=MIX_INIT_OGG|MIX_INIT_MOD|MIX_INIT_MP3;
	int32_t flags=MIX_INIT_OGG|MIX_INIT_MP3;
	int32_t initted=Mix_Init(flags);
	if( (initted & flags) != flags)
	{
		char msg[1280];
		sprintf(msg, "Mix_Init: Failed to init required ogg and mod support!\nMix_Init: %s", Mix_GetError());
		//ErrMess("Error", msg);
		// handle error
	}

	///Mix_ChannelFinished(ChannelDone);

	// start SDL with audio support
	if(SDL_Init(SDL_INIT_AUDIO)==-1) {
		char msg[1280];
		sprintf(msg, "SDL_Init: %s\n", SDL_GetError());
		ErrMess("Error", msg);
		// handle error
		//exit(1);
	}
	// show 44.1KHz, signed 16bit, system byte order,
	//      stereo audio, using 1024 byte chunks
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024)==-1) {
		char msg[1280];
		printf("Mix_OpenAudio: %s\n", Mix_GetError());
		ErrMess("Error", msg);
		// handle error
		//exit(2);
	}

	///Mix_AllocateChannels(SOUND_CHANNELS);
#endif

	srand((uint32_t)GetTicks());
}

void Deinit()
{
	BreakWin(TITLE);

	//Mix_CloseAudio();

	// force a quit
	//while(Mix_Init(0))
	//	Mix_Quit();
	//Mix_Quit();

	//SDLNet_Quit();
	SDL_Quit();
}

int32_t HandleEvent(void *userdata, SDL_Event *e)
{
	GUI* gui = &g_gui;
	InEv ie;
	ie.intercepted = false;
	ie.curst = CU_DEFAULT;
	Vec2i old;
	
	SDL_TouchFingerEvent* tfe = &e->tfinger;
	
	switch(e->type)
	{
#ifdef PLATFORM_IOS
		case SDL_APP_TERMINATING:
			/* Terminate the app.
			 Shut everything down before returning from this function.
			 */
			g_quit = true;
			g_background = true;
			exit(0);
			return 0;
		case SDL_APP_LOWMEMORY:
			/* You will get this when your app is paused and iOS wants more memory.
			 Release as much memory as possible.
			 */
			exit(0);
			return 0;
		case SDL_APP_WILLENTERBACKGROUND:
			/* Prepare your app to go into the background.  Stop loops, etc.
			 This gets called when the user hits the home button, or gets a call.
			 */
			g_quit = true;
			g_background = true;
			exit(0);
			return 0;
		case SDL_APP_DIDENTERBACKGROUND:
			/* This will get called if the user accepted whatever sent your app to the background.
			 If the user got a phone call and canceled it, you'll instead get an SDL_APP_DIDENTERFOREGROUND event and restart your loops.
			 When you get this, you have 5 seconds to save all your state or the app will be terminated.
			 Your app is NOT active at this point.
			 */
			g_quit = true;
			g_background = true;
			exit(0);
			return 0;
		case SDL_APP_WILLENTERFOREGROUND:
			/* This call happens when your app is coming back to the foreground.
			 Restore all your state here.
			 */
			g_background = false;
			return 0;
		case SDL_APP_DIDENTERFOREGROUND:
			/* Restart your loops here.
			 Your app is interactive and getting CPU again.
			 */
			g_background = false;
			return 0;
#endif
		case SDL_QUIT:
			g_quit = true;
			break;
		case SDL_KEYDOWN:
			ie.type = INEV_KEYDOWN;
			ie.key = e->key.keysym.sym;
			ie.scancode = e->key.keysym.scancode;
			
			//Handle copy
			if( e->key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL )
			{
				ie.type = INEV_COPY;
			}
			//Handle paste
			if( e->key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL )
			{
				ie.type = INEV_PASTE;
			}
			//Select all
			if( e->key.keysym.sym == SDLK_a && SDL_GetModState() & KMOD_CTRL )
			{
				ie.type = INEV_SELALL;
			}
			
			gui->inev(&ie);
			
			if(!ie.intercepted)
				g_keys[e->key.keysym.scancode] = true;
			
			g_keyintercepted = ie.intercepted;
			break;
		case SDL_KEYUP:
			ie.type = INEV_KEYUP;
			ie.key = e->key.keysym.sym;
			ie.scancode = e->key.keysym.scancode;
			
			gui->inev(&ie);
			
			if(!ie.intercepted)
				g_keys[e->key.keysym.scancode] = false;
			
			g_keyintercepted = ie.intercepted;
			break;
		case SDL_TEXTINPUT:
			ie.type = INEV_TEXTIN;
			ie.text = e->text.text;
			
			gui->inev(&ie);
			break;
			
#ifndef PLATFORM_MOBILE
		case SDL_MOUSEWHEEL:
			ie.type = INEV_MOUSEWHEEL;
			ie.amount = e->wheel.y;
			
			gui->inev(&ie);
			break;
		case SDL_MOUSEBUTTONDOWN:

			switch (e->button.button)
		{
			case SDL_BUTTON_LEFT:
				g_mousekeys[MOUSE_LEFT] = true;
				g_moved = false;
				
				ie.type = INEV_MOUSEDOWN;
				ie.key = MOUSE_LEFT;
				ie.amount = 1;
				ie.x = g_mouse.x;
				ie.y = g_mouse.y;

				gui->inev(&ie);
				
				g_keyintercepted = ie.intercepted;
				break;
			case SDL_BUTTON_RIGHT:
				g_mousekeys[MOUSE_RIGHT] = true;
				
				ie.type = INEV_MOUSEDOWN;
				ie.key = MOUSE_RIGHT;
				ie.amount = 1;
				ie.x = g_mouse.x;
				ie.y = g_mouse.y;
				
				gui->inev(&ie);
				break;
			case SDL_BUTTON_MIDDLE:
				g_mousekeys[MOUSE_MIDDLE] = true;
				
				ie.type = INEV_MOUSEDOWN;
				ie.key = MOUSE_MIDDLE;
				ie.amount = 1;
				ie.x = g_mouse.x;
				ie.y = g_mouse.y;
				
				gui->inev(&ie);
				break;
		}
			break;
		case SDL_MOUSEBUTTONUP:
			switch (e->button.button)
		{
				case SDL_BUTTON_LEFT:
					g_mousekeys[MOUSE_LEFT] = false;
					
					ie.type = INEV_MOUSEUP;
					ie.key = MOUSE_LEFT;
					ie.amount = 1;
					ie.x = g_mouse.x;
					ie.y = g_mouse.y;
					
					gui->inev(&ie);
					break;
				case SDL_BUTTON_RIGHT:
					g_mousekeys[MOUSE_RIGHT] = false;
					
					ie.type = INEV_MOUSEUP;
					ie.key = MOUSE_RIGHT;
					ie.amount = 1;
					ie.x = g_mouse.x;
					ie.y = g_mouse.y;
					
					gui->inev(&ie);
					break;
				case SDL_BUTTON_MIDDLE:
					g_mousekeys[MOUSE_MIDDLE] = false;
					
					ie.type = INEV_MOUSEUP;
					ie.key = MOUSE_MIDDLE;
					ie.amount = 1;
					ie.x = g_mouse.x;
					ie.y = g_mouse.y;
					
					gui->inev(&ie);
					break;
			}
			break;
		case SDL_MOUSEMOTION:
			
			if(g_mouseout)
			{
				g_mouseout = false;
			}
			
			old = g_mouse;
			
			if(MousePosition())
			{
				g_moved = true;
				
				ie.type = INEV_MOUSEMOVE;
				ie.x = g_mouse.x;
				ie.y = g_mouse.y;
				ie.dx = g_mouse.x - old.x;
				ie.dy = g_mouse.y - old.y;
				
				gui->inev(&ie);
				
				g_curst = ie.curst;
			}
			break;
#else	//def PLATFORM_MOBILE
		case SDL_FINGERMOTION:
			
			if(g_mouseout)
			{
				g_mouseout = false;
			}
			
			old = g_mouse;
			
			g_moved = true;
				
			ie.type = INEV_MOUSEMOVE;
			ie.x = tfe->x * g_width;
			ie.y = tfe->y * g_height;
			ie.dx = tfe->dx * g_width;
			ie.dy = tfe->dy * g_height;
			g_mouse.x = tfe->x * g_width;
			g_mouse.y = tfe->y * g_height;
				
			gui->inev(&ie);
				
			g_curst = ie.curst;
			break;
		case SDL_FINGERDOWN:
		{
			g_mousekeys[MOUSE_LEFT] = true;
			g_moved = false;
			
			ie.type = INEV_MOUSEDOWN;
			ie.key = MOUSE_LEFT;
			ie.amount = 1;
			ie.x = tfe->x * g_width;
			ie.y = tfe->y * g_height;
			ie.dx = ie.x - g_mouse.x;
			ie.dy = ie.y - g_mouse.y;
			g_mouse.x = tfe->x * g_width;
			g_mouse.y = tfe->y * g_height;
			gui->inev(&ie);
			
			g_keyintercepted = ie.intercepted;
		}
			break;
		case SDL_FINGERUP:
		{
			
			g_mousekeys[MOUSE_LEFT] = false;
			
			ie.type = INEV_MOUSEUP;
			ie.key = MOUSE_LEFT;
			ie.amount = 1;
			ie.x = tfe->x * g_width;
			ie.y = tfe->y * g_height;
			ie.dx = ie.x - g_mouse.x;
			ie.dy = ie.y - g_mouse.y;
			g_mouse.x = tfe->x * g_width;
			g_mouse.y = tfe->y * g_height;
			gui->inev(&ie);
		}
		break;
#endif
	}

	return 0;
}

void EventLoop()
{
	while (!g_quit)
	{
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			HandleEvent(NULL, &e);
		}
		
		Update();
		Draw();
		SDL_GL_SwapWindow(g_window);
	}
}

//#ifdef PLATFORM_WIN
//int32_t WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int32_t nCmdShow)
//#else
int32_t main(int32_t argc, char* argv[])
//#endif
{
	Init();
	
	MakeWin(TITLE);
	
	AllocTex(&board, INI_WIDTH, INI_HEIGHT, 3);
	//LoadSysRes();
	//Queue();
	FillGUI();
	
	EventLoop();
	
	Deinit();

	return 0;
}
