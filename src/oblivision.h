#ifndef RENDERER_GRAPHICS_H
#define RENDERER_GRAPHICS_H
#include "util.h"

typedef struct color_s {
    int color;
} OV_COLOR;

#define MAXWID 7680
#define MAXHEI 4320

struct windata {

    SDL_Window *window;
    SDL_Texture *texture;
    SDL_Renderer *renderer;

    const char *keystate;

    int pixel_data[MAXWID*MAXHEI];
    char *last_pixel_data;

    int frame;
    int height, width;
    int exit;

};

void OV_colorTest();
void OV_setBackground(OV_COLOR bg_color);
void OV_putPixel(int x, int y, OV_COLOR color);
void OV_renderFrame();
int OVInit(SDL_Window *window, int width, int height, const char *winname);
void OV_free();

#endif