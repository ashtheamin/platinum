#ifndef PLATINUM_INCLUDES_AND_DEFIINTIONS
#define PLATINUM_INCLUDES_AND_DEFIINTIONS
    #include "includes_and_definitions.c"
#endif

struct world {
    struct camera* camera;
    struct player* player;
    struct platform* platform_list;
};

struct world* world_new() {
    struct world* world = malloc(sizeof(struct world));
    if (world == NULL) return NULL;

    world->camera = camera_new();
    if (world->camera == NULL) {free(world);return NULL;};

    world->player = player_new();
    if (world->player == NULL) 
        {camera_quit(world->camera);free(world);return NULL;};

    world->platform_list = platform_new();
    if (world->platform_list == NULL) {
        camera_quit(world->camera);player_quit(world->player);\
        free(world);return NULL;
    }
    world->platform_list->rect.x = 0;
    world->platform_list->rect.y = 400;
    world->platform_list->rect.w = 640;
    world->platform_list->rect.h = 80;

    return world;
}

void world_quit(struct world* world) {
    if (world == NULL) return;
    if (world->camera != NULL) {camera_quit(world->camera);};
    if (world->player != NULL) {player_quit(world->player);};
    if (world->platform_list != NULL) {platform_quit(world->platform_list);};
    free(world);
    return;
}


bool world_check_collision(SDL_Rect rect1, SDL_Rect rect2) {
    int left1, left2, right1, right2;
    int top1, top2, bottom1, bottom2;

    // Calculate sides of first rect.
    left1 = rect1.x;
    right1 = rect1.x + rect1.w;
    top1 = rect1.y;
    bottom1 = rect1.y + rect1.h;

    // Calculate sides of second rect.
    left2 = rect2.x;
    right2 = rect2.x + rect2.w;
    top2 = rect2.y;
    bottom2 = rect2.y + rect2.h;

    // Check to see if there are separations on axis.
    if (bottom1 <= top2) return false;
    if (top1 >= bottom2) return false;
    if (right1 <= left2) return false;
    if (left1 >= right2) return false;

    // If there are no separations, then the objects are colliding.
    return true;
}

void world_render(SDL_Renderer* renderer, struct world* world) {
    if (renderer == NULL || world == NULL) return;
    if (world->camera == NULL || world->player == NULL) return;


    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    player_render(renderer, world->player, world->camera);
    platform_render(renderer, world->platform_list, world->camera);
    SDL_RenderPresent(renderer);
}

void world_input(SDL_Event event, struct world* world) {
    player_input(event, world->player);
    camera_input(event, world->camera);
}

void world_update(struct world* world) {
    player_move(world->player);
    world->player->rect.y += world->player->velocity_max;
    struct platform* platform = world->platform_list;
    while (platform != NULL) {
        if (world_check_collision(platform->rect, world->player->rect)) {
            world->player->rect.y -= world->player->velocity_max;
        }
        platform = platform->next;
    }
    camera_move(world->camera);
    world->camera->position_x = world->player->rect.x - SCREEN_WIDTH/2;
    world->camera->position_y = world->player->rect.y - SCREEN_HEIGHT/2;
}
