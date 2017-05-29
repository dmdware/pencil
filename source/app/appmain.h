


#ifndef appmain_H
#define appmain_H

#include "../window.h"

#define VERSION				1
#define TITLE				"Pencil"

extern int mode;	//pen mode

int32_t HandleEvent(void *userdata, SDL_Event *e);

#endif
