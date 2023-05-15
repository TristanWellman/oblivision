#ifndef RENDERER_GRAPHICS_H
#define RENDERER_GRAPHICS_H
#include "util.h"

#define WIDTH 1280
#define HEIGHT 720

typedef struct vec_s {
    int x, y;
} vec2;

struct windata {

    SDL_Surface *window;

    const char *keystate;

    int frame;
    int height, width;
    int pixel_data[WIDTH * HEIGHT];
    int exit;

};

int init_graphics(int width, int height);

#endif