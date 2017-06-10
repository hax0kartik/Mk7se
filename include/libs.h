#ifndef LIB_FILE

#define LIB_FILE
#include <3ds.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <sf2d.h>
#include <sftd.h>
#include <font_ttf.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <sys/types.h>
#include "offset.h"
#include "conversion.h"
#include "crc.h"
#include "fs.h"
#include "guithread.h"
Thread thread;
Handle event;
Result ret;
char *data, *data2, *file;
typedef struct
{
	int selected;
	int options;
}Menu;

typedef void (*guiFunc)(void);

typedef struct 
{
	guiFunc topFunc;
	guiFunc botFunc;
	sftd_font *font;
	Menu menu;
}Gui;
bool stopScreen;
Gui gui;
#endif
