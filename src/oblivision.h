#ifndef RENDERER_GRAPHICS_H
#define RENDERER_GRAPHICS_H
#include "util.h"

#define WIDTH 1280
#define HEIGHT 720

typedef struct color_s {
    uint8_t color;
} OV_COLOR;

struct windata {

    SDL_Surface *window;

    const char *keystate;

    int frame;
    int height, width;
    uint8_t pixel_data[WIDTH * HEIGHT];
    uint8_t last_pixel_data[WIDTH * HEIGHT];
    int exit;

};

void OV_colorTest();
void OV_setBackground(OV_COLOR bg_color);
void OV_putPixel(int x, int y, OV_COLOR color);
void OV_renderFrame();
int OVInit(SDL_Surface *window, int width, int height);

#endif