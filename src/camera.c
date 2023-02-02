#ifndef PLATINUM_INCLUDES_AND_DEFIINTIONS
#define PLATINUM_INCLUDES_AND_DEFIINTIONS
    #include "includes_and_definitions.c"
#endif

struct camera {
    int position_x;
    int position_y;
    int velocity_x;
    int velocity_y;
    int velocity_max;
};

struct camera* camera_new() {
    struct camera* camera = malloc(sizeof(struct camera));
    if (camera == NULL) return NULL;

    camera->position_x = 0;
    camera->position_y = 0;
    camera->velocity_x = 0;
    camera->velocity_y = 0;

    camera->velocity_max = 10;

    return camera;
}

void camera_quit(struct camera* camera) {
    if (camera == NULL) return;
    free(camera);
}

void camera_input(SDL_Event event, struct camera* camera) {
    if (camera == NULL) return;
    
    if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
        switch(event.key.keysym.sym) {
            case SDLK_UP: camera->velocity_y -= camera->velocity_max;break;
            case SDLK_DOWN: camera->velocity_y += camera->velocity_max;break;
            case SDLK_LEFT: camera->velocity_x -= camera->velocity_max;break;
            case SDLK_RIGHT: camera->velocity_x += camera->velocity_max;break;
        }
    }

    else if (event.type == SDL_KEYUP && event.key.repeat == 0) {
        switch(event.key.keysym.sym) {
            case SDLK_UP: camera->velocity_y += camera->velocity_max;break;
            case SDLK_DOWN: camera->velocity_y -= camera->velocity_max;break;
            case SDLK_LEFT: camera->velocity_x += camera->velocity_max;break;
            case SDLK_RIGHT: camera->velocity_x -= camera->velocity_max;break;
        }
    }
}

void camera_move(struct camera* camera) {
    if (camera == NULL) return;

    camera->position_x += camera->velocity_x;
    if (camera->position_x < 0 || camera->position_x >= WORLD_WIDTH) {
        camera->position_x -= camera->velocity_x;
    }

    camera->position_y += camera->velocity_y;
    if (camera->position_y < 0 || camera->position_y >= WORLD_HEIGHT) {
        camera->position_y -= camera->velocity_y;
    }
   
}