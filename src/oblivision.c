#include "oblivision.h"

struct windata winData;

int current_x = 0;
int current_y = 0;

void OV_colorTest() {

    OV_COLOR start_color = {BG};

    for(current_x = 0; current_x < winData.width; current_x++) {
        for(current_y = 0; current_y < winData.height; current_y++) {
            winData.pixel_data[current_y * winData.width + current_x] = start_color.color;
            start_color.color = start_color.color + current_x*current_y;
        }
    }
    int i;
    for(i = 0; i < sizeof(winData.pixel_data); i++) {
        if(winData.pixel_data[i] == 0) {
            break;
        }
        winData.last_pixel_data = winData.pixel_data;
    }
    current_x = 0;
    current_y = 0;
}

void OV_setBackground(OV_COLOR bg_color) {

    for(current_x = 0; current_x < winData.width; current_x++) {
        for(current_y = 0; current_y < winData.height; current_y++) {
            winData.pixel_data[current_y * winData.width + current_x] = bg_color.color;
        }
    }

    current_x = 0;
    current_y = 0;

}

void OV_renderFrame() {

    SDL_UpdateTexture(winData.texture, NULL,
                      winData.pixel_data, winData.width * 4);

    SDL_RenderCopyEx(
            winData.renderer, winData.texture,
            NULL, NULL, 0.0, NULL,
            SDL_FLIP_VERTICAL
            );

    SDL_RenderPresent(winData.renderer);

}

int OVInit(SDL_Window *window, int width, int height, const char *winname) {

    winData.window = window;
    winData.width = width;
    winData.height = height;

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("FATAL:: Could not init SDL2!\n");
        exit(1);
    }

    winData.window = SDL_CreateWindow(
            winname,
            SDL_WINDOWPOS_CENTERED_DISPLAY(0),
            SDL_WINDOWPOS_CENTERED_DISPLAY(0),
            winData.width, winData.height, 0);

    if(winData.window == NULL) {
        printf("FATAL:: Could not set video mode!\n");
        exit(1);
    }
/*
    winData.pixel_data = (char *)malloc(
            sizeof(char *)*(winData.width * winData.height)
            );*/

    winData.renderer = SDL_CreateRenderer(winData.window, -1,
                                          SDL_RENDERER_PRESENTVSYNC);
    if(winData.renderer == NULL) {
        printf("FATAL:: Could not init renderer!\n");
        exit(1);
    }

    winData.texture = SDL_CreateTexture(winData.renderer,
                                        SDL_PIXELFORMAT_RGBA8888,
                                        SDL_TEXTUREACCESS_STREAMING,
                                        winData.width, winData.height);

    if(winData.texture == NULL) {
        printf("FATAL:: Could not init texture!\n");
        exit(1);
    }

    int i;
    for(i = 0; i < sizeof(winData.pixel_data); i++) {

    }

    return 0;

}

void OV_free() {
    /*free(winData.pixel_data);*/
    SDL_DestroyTexture(winData.texture);
    SDL_DestroyWindow(winData.window);
    SDL_DestroyRenderer(winData.renderer);
}