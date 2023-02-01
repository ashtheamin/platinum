#ifndef PLATINUM_INCLUDES_AND_DEFIINTIONS
#define PLATINUM_INCLUDES_AND_DEFIINTIONS
    #include "includes_and_definitions.c"
#endif

struct player {
    int x;
    int y;
};

struct player* player_new() {
    struct player* player = malloc(sizeof(struct player));
    if (player == NULL) return;

    player->x = 0;
    player->y = 0;

    return player;
}

void player_quit(struct player* player) {
    if (player == NULL) return;
    free(player);
}