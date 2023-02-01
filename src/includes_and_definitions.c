#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#ifndef PLATINUM_WORLD_FILE
#define PLATINUM_WORLD_FILE
    #include "world.c"
#endif

#ifndef PLATINUM_MAP_FILE
#define PLATINUM_MAP_FILE
    #include "map.c"
#endif

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define TILE_ROWS 50
#define TILE_COLUMNS 30

#define TILE_WIDTH SCREEN_WIDTH/50
#define TILE_HEIGHT SCREEN_HEIGHT/30