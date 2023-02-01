#ifndef PLATINUM_INCLUDES_AND_DEFIINTIONS
#define PLATINUM_INCLUDES_AND_DEFIINTIONS
    #include "includes_and_definitions.c"
#endif

struct world {
    struct map* map;    
};

struct world* world_new() {
    struct world* world = malloc(sizeof(struct world));
    if (world == NULL) return NULL;
    world->map = map_new();
    return world;
}

void world_quit(struct world* world) {
    if (world == NULL) return;
    if (world->map != NULL) map_quit(world->map);
    free(world);
    return;
}