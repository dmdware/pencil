



#include "platform.h"
#include "debug.h"
#include "utils.h"
#include "window.h"
#include "app/appmain.h"

Timer g_profile[TIMERS];
 bool g_debuglines = false;
std::ofstream g_profF;

#if 0

void StartTimer(int32_t id)
{
	return;

	//if(g_mode != APPMODE_PLAY)
	//	return;

	g_profile[id].starttick = GetTicks();
}

void StopTimer(int32_t id)
{
	return;

	if(g_mode != APPMODE_PLAY)
		return;

#ifdef DEBUGLOG
	if(id == TIMER_UPDATE)
	{
		Log(std::endl<<"upd el = "<<GetTicks()<<" - "<<g_profile[id].starttick););
	}
#endif

	uint64_t elapsed = GetTicks() - g_profile[id].starttick;
	g_profile[id].starttick = GetTicks();
	g_profile[id].lastframeelapsed += elapsed;

#ifdef DEBUGLOG
	if(id == TIMER_UPDATE)
	{
		Log(std::endl<<"upd el"<<elapsed<<" tot"<<g_profile[id].lastframeelapsed<<" avg"<<g_profile[id].averagems););
	}
#endif

	if(id == TIMER_FRAME || g_profile[id].lastframe < g_profile[TIMER_FRAME].lastframe)
	{

#ifdef DEBUGLOG
		if(id == TIMER_UPDATE)
		{
			Log(std::endl<<"upd ( (double)"<<g_profile[id].lastframeelapsed<<" + "<<g_profile[id].averagems<<"*(double)"<<g_profile[id].frames<<" ) / (double)("<<g_profile[id].frames<<"+1); = ";
		}
#endif

		//g_profile[id].averagems = ( g_profile[id].lastframeaverage + g_profile[id].averagems*g_profile[id].frames ) / (g_profile[id].frames+1);
		g_profile[id].averagems = ( (double)g_profile[id].lastframeelapsed + g_profile[id].averagems*(double)g_profile[id].frames ) / (double)(g_profile[id].frames+1);
		g_profile[id].frames++;
		//g_profile[id].timescountedperframe = 0;
		g_profile[id].lastframeelapsed = 0;
		g_profile[id].lastframe = g_profile[TIMER_FRAME].lastframe;


#ifdef DEBUGLOG
		if(id == TIMER_UPDATE)
		{
			Log(g_profile[id].averagems););
		}
#endif

		//Log(g_profile[id].name<<" "<<g_profile[id].averagems<<"ms");
	}
	if(id == TIMER_FRAME)
		g_profile[id].lastframe++;

	//g_profile[id].lastframeaverage = ( elapsed + g_profile[id].lastframeaverage*g_profile[id].timescountedperframe ) / (g_profile[id].timescountedperframe+1);
	//g_profile[id].timescountedperframe+=1.0f;
}

#endif

void WriteProfiles(int32_t in, int32_t layer)
{
	double parentavgms;

	if(in == -1)
	{
		char fullpath[DMD_MAX_PATH+1];
		FullWritePath("profiles.txt", fullpath);
		g_profF.open(fullpath, std::ios_base::out);
		parentavgms = g_profile[TIMER_FRAME].averagems;
	}
	else
	{
		parentavgms = g_profile[in].averagems;
	}

	double ofparentpct;
	double totalms = 0;
	double totalofparentpct = 0;
	double percentage;
	int32_t subprofiles = 0;

	int j;

	for(j=0; j<TIMERS; j++)
	{
		if(g_profile[j].inside != in)
			continue;

		totalms += g_profile[j].averagems;
	}

	for(j=0; j<TIMERS; j++)
	{
		if(g_profile[j].inside != in)
			continue;

		percentage = 100.0 * g_profile[j].averagems / totalms;
		ofparentpct = 100.0 * g_profile[j].averagems / parentavgms;
		totalofparentpct += ofparentpct;
		subprofiles++;

		for(int32_t k=0; k<layer; k++)
			g_profF<<"\t";

		g_profF<<g_profile[j].name<<"\t...\t"<<g_profile[j].averagems<<"ms per frame, "<<percentage<<"% of this level's total"<<std::endl;

		WriteProfiles(j, layer+1);
	}

	if(subprofiles > 0)
	{
		for(int32_t k=0; k<layer; k++)
			g_profF<<"\t";

		g_profF<<"level total sum: "<<totalms<<" ms per frame, that means "<<totalofparentpct<<"% of this parent's duration underwent profiling"<<std::endl;
	}

	if(in == -1)
	{
		g_profF.flush();
		g_profF.close();
	}
}

void DefTimer(int32_t id, int32_t inside, const char* name)
{
	g_profile[id].inside = inside;
	strcpy(g_profile[id].name, name);
}

void Profiles()
{
	DefTimer(TIMER_FRAME, -1, "Frame");
	DefTimer(TIMER_EVENT, TIMER_FRAME, "EventProc");
	DefTimer(TIMER_DRAW, TIMER_FRAME, "Draw();");
	DefTimer(TIMER_UPDATE, TIMER_FRAME, "Update();");
}

void LastNum(const char* l)
{
	return;

#if 1
	char fullpath[DMD_MAX_PATH+1];
	FullWritePath("last.txt", fullpath);
	std::ofstream last;
	last.open(fullpath, std::ios_base::out);
	last<<l;
	last.flush();
#else
	Log(l);
	
#endif
}

#ifdef GLDEBUG
void CheckGLError(const char* file, int32_t line)
{
	//char msg[2048];
	//sprintf(msg, "Failed to allocate memory in %s on line %d.", file, line);
	//ErrMess("Out of memory", msg);
	int32_t error = glGetError();

	if(error == GL_NO_ERROR)
		return;

	Log("GL Error #%d in %s on line %d using shader #%d", error, file, line, g_curS);
}
#endif

#ifdef PLATFORM_WIN
#include <windows.h>
//#include <Psapi.h>

//#pragma comment(lib, "Psapi.lib")
#endif

#ifdef MEMDEBUG
void CheckMem(const char* file, int32_t line, const char* sep)
{
	return;
#ifdef PLATFORM_WIN
	PROCESS_MEMORY_COUNTERS info = {0};
	DWORD cb;
	bool b = GetProcessMemoryInfo(GetCurrentProcess(), &info, sizeof(info));
	Log(sep<<" "<<file<<" line"<<line<<" (?"<<b<<")info.WorkingSetSize: "<<info.WorkingSetSize<<"B / "<<(info.WorkingSetSize/1024)<<"KB "<<(info.WorkingSetSize/1024/1024)<<"MB "<<(info.WorkingSetSize/1024/1024/1024)<<"GB ");
	
#endif
}
#endif

#if !defined( PLATFORM_MAC ) && !defined( PLATFORM_IOS )
GLvoid APIENTRY GLMessageHandler(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, GLvoid* userParam)
//DEBUGPROC GLMessageHandler(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, GLvoid* userParam)
{
	//ErrMess("GL Error", message);
	Log("GL Message: %s\r\n", message);
}
#endif

void CheckError(const char* file, int line)
{
	const char* m = SDL_GetError();

	if(!m[0])
		return;

	Log("SDL error: %s %d : %s", file, line, m);
}

int32_t GetFreeVideoMem()
{
	//TODO mobile
	int availableKB[4];
//#ifdef GL234
#ifndef PLATFORM_MOBILE
#ifdef PLATFORM_WIN
	if(GLEW_NVX_gpu_memory_info)
		glGetIntegerv(GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &availableKB[0]);
	int32_t temp = GLEW_ATI_meminfo;
	if(GLEW_ATI_meminfo)
		glGetIntegerv(GL_TEXTURE_FREE_MEMORY_ATI, availableKB);
	return availableKB[0];
#endif
#endif
	return 0;
}
