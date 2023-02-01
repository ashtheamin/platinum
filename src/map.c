#ifndef PLATINUM_INCLUDES_AND_DEFIINTIONS
#define PLATINUM_INCLUDES_AND_DEFIINTIONS
    #include "includes_and_definitions.c"
#endif


struct map {
    int grid[TILE_ROWS][TILE_COLUMNS];
};

struct map* map_new() {
    struct map* map = malloc(sizeof(struct map));
    if (map == NULL) return NULL;
    for (int i=0; i < TILE_ROWS; i++) {
        for (int j=0; j < TILE_COLUMNS; j++) {
            map->grid[i][j] = 0;
        }
    }
    return map;
}

void map_quit(struct map* map) {
    if (map == NULL) return;
    free(map);
    return;
}