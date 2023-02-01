#ifndef PLATINUM_INCLUDES_AND_DEFIINTIONS
#define PLATINUM_INCLUDES_AND_DEFIINTIONS
    #include "includes_and_definitions.c"
#endif

struct world {
    struct player* player; 
};

struct world* world_new() {
    struct world* world = malloc(sizeof(struct world));
    if (world == NULL) return NULL;

    world->player = player_new();
    if (world->player == NULL) {free(world);return NULL;};

    return world;
}

void world_quit(struct world* world) {
    if (world == NULL) return;
    if (world->player != NULL) {player_free(world->player);};
    free(world);
    return;
}