/*Copyright (c) 2023, Tristan Wellman*/

#ifndef RENDERER_GRAPHICS_H
#define RENDERER_GRAPHICS_H
#include "util.h"

typedef struct color_s {
    int color;
} OV_COLOR;
typedef struct vec2_s {
    int x, y;
} vec2;

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

#define OV_CENTERED (vec2) {0, 0}
#define MAX_WIGS 256

struct widget_data {
    int num_wigs;
    const char *names[MAX_WIGS];
    vec2 wig_sizes[MAX_WIGS];
    vec2 wig_pos[MAX_WIGS];
};

void OV_colorTest();
void OV_setBackground(OV_COLOR bg_color);
void OV_putPixel(int x, int y, OV_COLOR color);
int OV_createWindow(int width, int height, vec2 pos, const char *name);
void OV_renderFrame();
int OVInit(SDL_Window *window, int width, int height, const char *winname);
void OV_free();

#endif