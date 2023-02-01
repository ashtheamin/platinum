#ifndef PLATINUM_INCLUDES_AND_DEFIINTIONS
#define PLATINUM_INCLUDES_AND_DEFIINTIONS
    #include "includes_and_definitions.c"
#endif

struct player {
    int position_x;
    int position_y;
    int velocity_x;
    int velocity_y;
    int velocity_max;
};

struct player* player_new() {
    struct player* player = malloc(sizeof(struct player));
    if (player == NULL) return NULL;

    player->position_x = 0;
    player->position_y = 0;
    player->velocity_x = 0;
    player->velocity_y = 0;

    player->velocity_max = 10;

    return player;
}

void player_quit(struct player* player) {
    if (player == NULL) return;
    free(player);
}

void player_render(SDL_Renderer* renderer, \
struct player* player, struct camera* camera) {
    if (renderer == NULL || player == NULL || camera == NULL) return;

    SDL_Rect rect;
    rect.x = player->position_x - camera->x;
    rect.y = player->position_y - camera->y;
    rect.w = 10; rect.h = 10;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 0);
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);
}

void player_input(SDL_Event event, struct player* player) {
    if (player == NULL) return;
    
    if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
        switch(event.key.keysym.sym) {
            case SDLK_w: player->velocity_y -= player->velocity_max;break;
            case SDLK_s: player->velocity_y += player->velocity_max;break;
            case SDLK_a: player->velocity_x -= player->velocity_max;break;
            case SDLK_d: player->velocity_x += player->velocity_max;break;
        }
    }

    else if (event.type == SDL_KEYUP && event.key.repeat == 0) {
        switch(event.key.keysym.sym) {
            case SDLK_w: player->velocity_y += player->velocity_max;break;
            case SDLK_s: player->velocity_y -= player->velocity_max;break;
            case SDLK_a: player->velocity_x += player->velocity_max;break;
            case SDLK_d: player->velocity_x -= player->velocity_max;break;
        }
    }
}

void player_move(struct player* player) {
    if (player == NULL) return;

    player->position_x += player->velocity_x;
    if (player->position_x < 0 || player->position_x >= WORLD_WIDTH) {
        player->position_x -= player->velocity_x;
    }

    player->position_y += player->velocity_y;
    if (player->position_y < 0 || player->position_y >= WORLD_HEIGHT) {
        player->position_y -= player->velocity_y;
    }
   
}