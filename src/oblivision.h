/*Copyright (c) 2023, Tristan Wellman*/

/**
 * @file oblivision.h
 * @author Tristan Wellman
 * @brief header for the Oblivision API.
 * */

#ifndef RENDERER_GRAPHICS_H
#define RENDERER_GRAPHICS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "colors.h"


#define OV_DEBUG_ENABLE 1

/**
 * @typedef OV_COLOR
 * @brief A "non-proprietary" typedef holding colordata */
typedef struct color_s {
    int color;
} OV_COLOR;

/**
 * @typedef vec2
 * @brief Vector data for things like window position/sizes*/
typedef struct vec2_s {
    int x, y;
} vec2;

/**
 * @defgroup OVMaximums
 * @brief OV specific definitions for maximums
 * @{*/
#define MAXWID 7680
#define MAXHEI 4320
#define MAX_WIGS 256
/** @} OVMaximums*/

/**
 * @struct windata
 * @brief Main structure for managing all pixel data, textures, sizes, etc.*/
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


/**
 * @struct widget_data
 * @brief Structure to hold all widget(OV window) data.*/
struct widget_data {
    int num_wigs;
    const char *names[MAX_WIGS];
    vec2 wig_sizes[MAX_WIGS];
    vec2 wig_pos[MAX_WIGS];
};

/**
 * @brief Runs a simple color tester.
 * @note Oblivision should be initialized prior to OV_colorTest()
 * */
void OV_colorTest();

/**
 * @brief Sets the background color of your Oblivision window.
 *
 * @param bg_color the RGBA8888 color set for the background*/
void OV_setBackground(OV_COLOR bg_color);

/**
 * @brief Initializes and creates an Oblivision window.
 * @note Oblivision should be initialized prior to OV_createWindow
 *
 * @param width the desired width of the window
 * @param height the desired height of the window
 * @param pos vector holding the x & y position for the OV window;
 * @param name name initialized as an ID with the window
 * */
int OV_createWindow(int width, int height, vec2 pos, const char *name);

/**
 * @brief runs the SDL event poll loop to register key events and update window positions
 * @note Requires an initialized & running session of Oblivision.
 *
 * @param event SDL_Event used to poll key & mouse events as well as positions*/
void OV_pollEvent(SDL_Event event);

/**
 * @brief Renders current frame filled with pixel data
 * @note Oblivision should be initialized prior to OV_renderFrame*/
void OV_renderFrame();

/**
 * @brief W.I.P*/
void OV_setFlags(int flag);
void OV_setFont(const char *font);
int OVInit(SDL_Window *window, int width, int height, const char *winname);
void OV_free();

#endif