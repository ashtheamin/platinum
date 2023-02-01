#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#ifndef PLATINUM_PLAYER_FILE
#define PLATINUM_PLAYER_FILE
    #include "player.c"
#endif

#ifndef PLATINUM_CAMERA_FILE
#define PLATINUM_CAMERA_FILE
    #include "camera.c"
#endif

#ifndef PLATINUM_WORLD_FILE
#define PLATINUM_WORLD_FILE
    #include "world.c"
#endif

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define WORLD_WIDTH 10000
#define WORLD_HEIGHT 10000

