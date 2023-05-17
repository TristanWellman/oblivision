#include "oblivision.h"

struct windata winData;

int current_x = 0;
int current_y = 0;

void OV_colorTest() {

    OV_COLOR start_color = {255};

    for(current_x = 0; current_x < winData.width; current_x++) {
        for(current_y = 0; current_y < winData.height; current_y++) {
            winData.pixel_data[(current_y * winData.width) + current_x] = start_color.color;
            start_color.color--;
        }
    }

    current_x = 0;
    current_y = 0;
}

void OV_setBackground(OV_COLOR bg_color) {

    for(current_x = 0; current_x < winData.width; current_x++) {
        for(current_y = 0; current_y < winData.height; current_y++) {
            winData.pixel_data[(current_y * winData.width) + current_x] = bg_color.color;
        }
    }

    current_x = 0;
    current_y = 0;

}

void OV_renderFrame() {

    SDL_LockSurface(winData.window);

    uint8_t *pixels = (uint8_t *) winData.window->pixels;
    for (current_x = 0; current_x < winData.width; current_x++) {
        for (current_y = 0; current_y < winData.height; current_y++) {
            pixels[(current_y * winData.width) + current_x] = winData.pixel_data[(current_y * winData.width) + current_x];
        }
    }

    SDL_UnlockSurface(winData.window);
    SDL_Flip(winData.window);
}

int OVInit(SDL_Surface *window, int width, int height) {

    winData.window = window;
    winData.width = width;
    winData.height = height;

    winData.window = SDL_SetVideoMode(winData.width, winData.height,
                                      8, SDL_SWSURFACE|SDL_ANYFORMAT);

    if(winData.window == NULL) {
        printf("FATAL:: Could not set video mode!\n");
        exit(1);
    }

    return 0;

}