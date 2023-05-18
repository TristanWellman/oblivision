#include "oblivision.h"

struct windata winData;
struct widget_data wigData;

int current_x = 0;
int current_y = 0;

void add_to_queue(int type) {

}

void OV_colorTest() {

    OV_COLOR start_color = {BG};
   // if (winData.pixel_data[0] != RED) {
        for (current_x = 0; current_x < winData.width; current_x++) {
            for (current_y = 0; current_y < winData.height; current_y++) {
                winData.pixel_data[current_y * winData.width + current_x] = start_color.color;
                start_color.color = start_color.color + current_x * current_y;
            }
        }
    //}

    current_x = 0;
    current_y = 0;
}

void OV_setBackground(OV_COLOR bg_color) {

    if (winData.pixel_data[0] != RED) {
        for (current_x = 0; current_x < winData.width; current_x++) {
            for (current_y = 0; current_y < winData.height; current_y++) {
                winData.pixel_data[current_y * winData.width + current_x] = bg_color.color;
            }
        }
    }
    current_x = 0;
    current_y = 0;

}

int OV_createWindow(int width, int height, vec2 pos, const char *name) {

    int i;
    for(i = 0; i < sizeof(wigData.names); i++) {
        if(wigData.names[i] == name) {
            return 1;
        }
        if(wigData.names[i] == NULL) {
            wigData.names[i] = name;
            wigData.wig_pos[i] = pos;
            wigData.wig_sizes[i] = (vec2){width, height};
            printf("[%d]%s: (%d,%d)\n", i, name, wigData.wig_pos[i].x, wigData.wig_pos[i].y);
            break;
        }
    }

    return 0;
}

void load_widgets() {
    int i;
    current_x = 0;
    current_y = 0;
    for(i = 0; i < sizeof(wigData.names); i++) {
        if(wigData.names[i] == NULL) {
            break;
        }
        for(current_x = 0; current_x < winData.width; current_x++) {
            if(current_x == wigData.wig_pos[i].x+1) {
                break;
            }
            for(current_y = 0; current_y < winData.height; current_y++) {
                 if(current_x == wigData.wig_pos[i].x && current_y == wigData.wig_pos[i].y) {
                     winData.pixel_data[current_y * winData.width + current_x] = ORANGE;
                     break;
                }
            }
        }
    }
}

void OV_renderFrame() {

    load_widgets();

    SDL_UpdateTexture(winData.texture, NULL,
                      winData.pixel_data, winData.width * 4);

    SDL_RenderCopyEx(
            winData.renderer, winData.texture,
            NULL, NULL, 0.0, NULL,
            0
            );

    SDL_RenderPresent(winData.renderer);

    winData.pixel_data[0] = RED;
    SDL_Delay(41);

}

int OVInit(SDL_Window *window, int width, int height, const char *winname) {

    winData.window = window;
    winData.width = width;
    winData.height = height;
    wigData.num_wigs = 0;
    OV_CENTERED.x = winData.width/2;
    OV_CENTERED.y = winData.height/2;


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
        if(i >= winData.width * winData.height) {
            break;
        }
        winData.pixel_data[i] = 0;
    }

    return 0;

}

void OV_free() {
    /*free(winData.pixel_data);*/
    SDL_DestroyTexture(winData.texture);
    SDL_DestroyWindow(winData.window);
    SDL_DestroyRenderer(winData.renderer);
}