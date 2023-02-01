#ifndef PLATINUM_INCLUDES_AND_DEFIINTIONS
#define PLATINUM_INCLUDES_AND_DEFIINTIONS
    #include "includes_and_definitions.c"
#endif

/*
Main.c Copyright Ash Amin 2023.
This file is the entrypoint that controls the program state.
It contains everything the program contains, it allocates and initialises APIs,
it allocates the program state, and handles user interaction, and frees resources.
*/

enum program_status {program_status_quit, program_status_running};
struct program {
    SDL_Window* window;
    SDL_Renderer* renderer;
    enum program_status status;

    struct world* world;
};

// Create new program state. Returns NULL on failure.
struct program* program_new() {
    // Allocate memory for program state
    struct program* program = malloc(sizeof(struct program));
    if (program == NULL) {
        printf("Failed to initialise program state.\n");return NULL;
    }

    // Initialise SDL.
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Failed to init SDL. SDL_GetError(): %s",\
        SDL_GetError());free(program);return NULL;
    }

    // Initialise SDL Window.
    program->window = SDL_CreateWindow("Platinum", \
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,\
    SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (program->window == NULL) {
        printf("Failed to init SDL Window. SDL_GetError(): %s",\
        SDL_GetError());SDL_Quit();free(program);return NULL;
    }

    // Initialise SDL Renderer.
    program->renderer = SDL_CreateRenderer\
    (program->window, -1, SDL_RENDERER_ACCELERATED);
    if (program->renderer == NULL) {
        printf("Failed to init SDL Renderer. SDL_GetError(): %s",\
        SDL_GetError());SDL_DestroyWindow(program->window);\
        SDL_Quit();free(program);return NULL;
    }

    // Initialise world.
    program->world = world_new();
    if (program->world == NULL) {
        printf("Failed to init world");\
        SDL_DestroyRenderer(program->renderer);\
        SDL_DestroyWindow(program->window);\
        SDL_Quit();free(program);return NULL;  
    }

    // Initialise program state values.
    program->status = program_status_running;

    // Return program state.
    return program;
}

void program_quit(struct program* program) {
    if (program == NULL) return;
    if (program->renderer != NULL) {SDL_DestroyRenderer(program->renderer);};
    if (program->window != NULL) {SDL_DestroyWindow(program->window);};
    if (program->world != NULL) {world_quit(program->world);};
    SDL_Quit();
    free(program);
}

void program_loop(void* loop_argument) {
    struct program* program = (struct program*)loop_argument;
    if (program == NULL) return;
    SDL_Event event;
    SDL_Delay(16);
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            program->status = program_status_quit;
        }
        if (event.type == SDL_KEYDOWN) {
            world_input(event, program->world);
        }
        break;
    }

    world_render(program->renderer, program->world);
}

int main(void) {
    struct program* program = program_new();
    if (program == NULL) return 0;

    #if defined(__EMSCRIPTEN__)
        #include <emscripten.h>
        emscripten_set_main_loop_arg(program_loop, (void*)program, 0, 1);
    #else
        while (program->status != program_status_quit) {
            program_loop((void*)program);
        }
    #endif

    program_quit(program);
    return 0;
}