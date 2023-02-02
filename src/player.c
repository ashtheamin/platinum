#ifndef PLATINUM_INCLUDES_AND_DEFIINTIONS
#define PLATINUM_INCLUDES_AND_DEFIINTIONS
    #include "includes_and_definitions.c"
#endif

struct player {
    SDL_Rect rect;
    int velocity_x;
    int velocity_y;
    int velocity_max;
};

struct player* player_new() {
    struct player* player = malloc(sizeof(struct player));
    if (player == NULL) return NULL;

    player->rect.x = 0;
    player->rect.y = 0;
    player->rect.w = 10;
    player->rect.h = 10;
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

    SDL_Rect render_rect;
    render_rect.x = player->rect.x - camera->position_x;
    render_rect.y = player->rect.y - camera->position_y;
    render_rect.w = player->rect.w; render_rect.h = player->rect.h;

    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 0);
    SDL_RenderFillRect(renderer, &render_rect);
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

    player->rect.x += player->velocity_x;
    if (player->rect.x  < 0 || player->rect.x  >= WORLD_WIDTH) {
        player->rect.x  -= player->velocity_x;
    }

    player->rect.y += player->velocity_y;
    if (player->rect.y < 0 || player->rect.y >= WORLD_HEIGHT) {
        player->rect.y -= player->velocity_y;
    }
   
}