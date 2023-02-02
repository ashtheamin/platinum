#ifndef PLATINUM_INCLUDES_AND_DEFIINTIONS
#define PLATINUM_INCLUDES_AND_DEFIINTIONS
    #include "includes_and_definitions.c"
#endif

struct platform {
    SDL_Rect rect;

    struct platform* next;
};

struct platform* platform_new() {
    struct platform* platform = malloc(sizeof(struct platform));
    if (platform == NULL) return NULL;

    platform->rect.x = 0;
    platform->rect.y = 0;
    platform->rect.w = 100;
    platform->rect.h = 10;

    platform->next = NULL;

    return platform;
}

void platform_quit(struct platform* platform) {
    if (platform == NULL) return;
    struct platform* temp = platform;
    struct platform* next = NULL;
    while (temp != NULL) {
        next = temp->next;
        free(temp);
        temp = next;
    }
}

void platform_render(SDL_Renderer* renderer, \
struct platform* platform, struct camera* camera) {
    if (renderer == NULL || platform == NULL || camera == NULL) return;

    SDL_Rect render_rect;

    while (platform != NULL) {
        render_rect.x = platform->rect.x - camera->position_x;
        render_rect.y = platform->rect.y - camera->position_y;
        render_rect.w = platform->rect.w; 
        render_rect.h = platform->rect.h;

        SDL_SetRenderDrawColor(renderer, 50, 100, 100, 0);
        SDL_RenderFillRect(renderer, &render_rect);

        platform = platform->next;
    }
}