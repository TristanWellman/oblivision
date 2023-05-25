/*Copyright (c) 2023, Tristan Wellman*/

#ifndef RENDERER_GRAPHICS_H
#define RENDERER_GRAPHICS_H
#include "util.h"

#define OV_DEBUG_ENABLE 1

typedef struct color_s {
    int color;
} OV_COLOR;
typedef struct vec2_s {
    int x, y;
} vec2;

#define MAXWID 7680
#define MAXHEI 4320
#define MAX_WIGS 256

struct windata {

    int ovflag;
    SDL_Window *window;
    SDL_Renderer *renderer;

    SDL_Texture *target_texture;
    SDL_Texture *texture;

    SDL_Surface *text_surface[MAX_WIGS];
    SDL_Texture *text_texture[MAX_WIGS];

    const char *fonttitle;
    TTF_Font *font;

    OV_COLOR bg_color;

    int pixel_data[MAXWID*MAXHEI];
    char *last_pixel_data;

    int height, width;
    int in_window;

};



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
void OV_pollEvent(SDL_Event event);
void OV_renderFrame(SDL_Event event);
void OV_setFlags(int flag);
void OV_setFont(const char *font);
int OVInit(SDL_Window *window, int width, int height, const char *winname);
void OV_free();

#endif