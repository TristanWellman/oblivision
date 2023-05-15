#ifndef RENDERER_GRAPHICS_H
#define RENDERER_GRAPHICS_H
#include "util.h"

#define WIDTH 1280
#define HEIGHT 720

typedef struct color_s {
    int r, g, b;
} OV_COLOR;

struct windata {

    SDL_Surface *window;

    const char *keystate;

    int frame;
    int height, width;
    int pixel_data[WIDTH * HEIGHT];
    int exit;

};

void OV_putPixel(int x, int y, OV_COLOR color);
int OVInit(int width, int height);

#endif