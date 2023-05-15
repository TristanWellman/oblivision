#include "oblivision.h"

struct windata winData;

int current_x = 0;
int current_y = 0;

void OV_putPixel(int x, int y, OV_COLOR color) {
    Uint32 p_color = SDL_MapRGB(winData.window->format,
                                color.r, color.g, color.b);
    int bpp = winData.window->format->BytesPerPixel;
    if(SDL_MUSTLOCK(winData.window)) {
        if(SDL_LockSurface(winData.window) < 0) {
            printf("FATAL:: Could not lock screen!\n");
            exit(1);
        }
    }

    Uint8 *p = (Uint8 *)winData.window->pixels + y * winData.window->pitch + x * bpp;

    switch(bpp) {
        case 1:
            *p = p_color;
            break;

        case 2:
            *(Uint16 *)p = p_color;
            break;

        case 3:
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
                p[0] = (p_color >> 16) & 0xff;
                p[1] = (p_color >> 8) & 0xff;
                p[2] = p_color & 0xff;
            } else {
                p[0] = p_color & 0xff;
                p[1] = (p_color >> 8) & 0xff;
                p[2] = (p_color >> 16) & 0xff;
            }
            break;

        case 4:
            *(Uint32 *)p = p_color;
            break;
    }

    if(SDL_MUSTLOCK(winData.window)) {
        SDL_UnlockSurface(winData.window);
    }
    SDL_UpdateRect(winData.window, x, y, 1, 1);
}

void render_frame() {

    int color = BG;

    /*set bg*/
    for(current_x = 0; current_x < WIDTH; current_x++) {
        for (current_y = 0; current_y < HEIGHT; current_y++) {
            winData.pixel_data[current_y * winData.width + current_x] = color;
            color = color + current_x*current_y;
        }
    }

    /*int i;
    for(i = 0; i < map_size; i++) {
        for(current_x = 0; current_x < (WIDTH / 8)) {

        }
    }*/
    current_y = 0;
    current_x = 0;
}

void render_loop() {

}

int OVInit(int width, int height) {

    winData.width = width;
    winData.height = height;

    winData.window = SDL_SetVideoMode(winData.width, winData.height,
                                      8, SDL_SWSURFACE|SDL_ANYFORMAT);

    if(winData.window == NULL) {
        printf("FATAL:: Could not set video mode!\n");
        exit(1);
    }
    render_loop();

    return 0;

}