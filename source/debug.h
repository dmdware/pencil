




#ifndef DEBUG_H
#define DEBUG_H

#include "platform.h"

#define	TIMER_FRAME				0
#define TIMER_EVENT				1
#define TIMER_UPDATE				2
#define TIMER_DRAW				3
#define TIMERS					5

class Timer
{
public:
	char name[64];
	double averagems;
	int32_t lastframe;
	int32_t frames;
	//double framems;
	uint64_t starttick;
	//double timescountedperframe;
	//double lastframeaverage;
	int32_t lastframeelapsed;
	int32_t inside;

	Timer()
	{
		averagems = 0.0;
		lastframeelapsed = 0;
		lastframe = 0;
		frames = 0;
		inside = -1;
	}
};

extern Timer g_profile[TIMERS];
extern bool g_debuglines;

//TODO too CPU heavy
#define StartTimer(a)	(void)0
#define StopTimer(a)	(void)0

//void StartTimer(int32_t id);
//void StopTimer(int32_t id);
void DefTimer(int32_t id, int32_t inside, char* name);

void WriteProfiles(int32_t in, int32_t layer);
void InitProfiles();

void LastNum(const char* l);
void CheckMem(const char* file, int32_t line, const char* sep);

#ifdef GLDEBUG
void CheckGLError(const char* file, int32_t line);
#endif

//#define CHECKERRS

#ifdef CHECKERRS
void CheckError(const char* file, int line);
#define CHECKERR()		CheckError(__FILE__,__LINE__)
#else
#define CHECKERR()		(void)0
#endif

//#define MEMDEBUG
#ifndef MEMDEBUG
#define CheckMem(a,b,c) (void)0
#endif

#ifndef MATCHMAKER
#if !defined( PLATFORM_MAC ) && !defined( PLATFORM_IOS )
GLvoid APIENTRY GLMessageHandler(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, GLvoid* userParam);
//DEBUGPROC GLMessageHandler(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, GLvoid* userParam);
#endif
#endif

int32_t GetFreeVideoMem();

#endif	//DEBUG_H
