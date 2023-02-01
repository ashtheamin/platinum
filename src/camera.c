#ifndef PLATINUM_INCLUDES_AND_DEFIINTIONS
#define PLATINUM_INCLUDES_AND_DEFIINTIONS
    #include "includes_and_definitions.c"
#endif

struct camera {
    int x;
    int y;
};

struct camera* camera_new() {
    struct camera* camera = malloc(sizeof(struct camera));
    if (camera == NULL) return NULL;

    camera->x = 0;
    camera->y = 0;

    return camera;
}

void camera_quit(struct camera* camera) {
    if (camera == NULL) return;
    free(camera);
}