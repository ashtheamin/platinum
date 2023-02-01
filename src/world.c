#ifndef PLATINUM_INCLUDES_AND_DEFIINTIONS
#define PLATINUM_INCLUDES_AND_DEFIINTIONS
    #include "includes_and_definitions.c"
#endif

struct world {
    struct camera* camera;
    struct player* player;
};

struct world* world_new() {
    struct world* world = malloc(sizeof(struct world));
    if (world == NULL) return NULL;

    world->camera = camera_new();
    if (world->camera == NULL) {free(world);return NULL;};

    world->player = player_new();
    if (world->player == NULL) 
        {camera_quit(world->camera);free(world);return NULL;};

    return world;
}

void world_quit(struct world* world) {
    if (world == NULL) return;
    if (world->camera != NULL) {camera_quit(world->camera);};
    if (world->player != NULL) {player_quit(world->player);};
    free(world);
    return;
}

void world_render(SDL_Renderer* renderer, struct world* world) {
    if (renderer == NULL || world == NULL) return;
    if (world->camera == NULL || world->player == NULL) return;

    player_render(renderer, world->player, world->camera);
}

void world_input(SDL_Event event, struct world* world) {
    player_input(event, world->player);
}

void world_update(struct world* world) {
    player_move(world->player);
}