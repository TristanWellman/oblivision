/*Copyright (c) 2023, Tristan Wellman*/

#include "oblivision.h"

struct windata winData;
struct widget_data wigData;

int current_x = 0;
int current_y = 0;

void OV_colorTest() {

    OV_COLOR start_color = {BG};
        for (current_x = 0; current_x < winData.width; current_x++) {
            for (current_y = 0; current_y < winData.height; current_y++) {
                winData.pixel_data[current_y * winData.width + current_x] = start_color.color;
                start_color.color = start_color.color + current_x * current_y;
            }
        }

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
    int x2,y2;
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
                     for(x2 = wigData.wig_pos[i].x; x2 < (wigData.wig_pos[i].x + wigData.wig_sizes[i].x); x2++) {
                         for(y2 = wigData.wig_pos[i].y; y2 < (wigData.wig_pos[i].y + wigData.wig_sizes[i].y); y2++) {
                             winData.pixel_data[y2 * winData.width + x2] = WIN_BG;
                         }
                     }
                     /*make title bar*/
                     vec2 bar_pos = {wigData.wig_pos[i].x, wigData.wig_pos[i].y-20};
                     vec2 bar_size = {wigData.wig_sizes[i].x, 20};
                     int x3,y3,x4,y4;

                     for(x3 = bar_pos.x; x3 < (bar_pos.x + bar_size.x); x3++) {
                         for(y3 = bar_pos.y; y3 < (bar_pos.y + bar_size.y); y3++) {
                             winData.pixel_data[y3 * winData.width + x3] = WINBAR_BG;
                         }
                     }
                     break;
                }
            }
        }
        /*Load bar title*/
        winData.text_surface[i] = TTF_RenderText_Blended(winData.font,
                                                       wigData.names[i],
                                                       (SDL_Color){255,255,255});
        winData.text_texture[i] = SDL_CreateTextureFromSurface(winData.renderer, winData.text_surface[i]);
    }
}

void OV_renderFrame() {

    Uint64 start = SDL_GetPerformanceCounter();

    load_widgets();

    SDL_SetRenderTarget(winData.renderer, winData.target_texture);

    SDL_UpdateTexture(winData.texture, NULL,
                      winData.pixel_data, winData.width * 4);

    SDL_RenderCopy(winData.renderer, winData.texture,
            NULL, NULL);

    SDL_Rect title_rect;
    int i;
    for(i = 0; i < MAX_WIGS; i++) {
        if(wigData.names[i] == NULL) {
            break;
        }
        title_rect.x = wigData.wig_pos[i].x;
        title_rect.y = wigData.wig_pos[i].y-20;
        title_rect.w = wigData.wig_sizes[i].x/2;
        title_rect.h = 20;
        SDL_RenderCopy(winData.renderer, winData.text_texture[i],
                       NULL, &title_rect);
    }

    winData.pixel_data[0] = RED;
    SDL_Delay(41);

    Uint64 end = SDL_GetPerformanceCounter();
    float elapsed = (end - start)/(float)SDL_GetPerformanceFrequency();
    //printf("FPS: %d\n", (int)(1.0f/elapsed));
    if(winData.ovflag == OV_DEBUG_ENABLE) {
        char buf[0x100];
        snprintf(buf, sizeof(buf), "FPS: %d", (int) (1.0f / elapsed));
        SDL_Surface *fps_surface = TTF_RenderText_Solid(winData.font, buf,
                                                        (SDL_Color) {255, 75, 75});
        SDL_Texture *fps_texture = SDL_CreateTextureFromSurface(winData.renderer, fps_surface);
        SDL_Rect fps_rect = {0, winData.height - 24, 100, 24};
        SDL_RenderCopy(winData.renderer, fps_texture, NULL, &fps_rect);
    }
    SDL_SetRenderTarget(winData.renderer, NULL);
    SDL_RenderPresent(winData.renderer);

}

void OV_setFlags(int flag) {
    if(flag != 0) {
        winData.ovflag = flag;
    }
}
void OV_setFont(const char *font) {
    winData.fonttitle = font;
}

int OVInit(SDL_Window *window, int width, int height, const char *winname) {

    winData.window = window;
    winData.width = width;
    winData.height = height;
    wigData.num_wigs = 0;
    /*OV_CENTERED.x = winData.width/2;
    OV_CENTERED.y = winData.height/2;*/


    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("FATAL:: Could not init SDL2_ttf!\n");
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

    if(TTF_Init() < 0) {
        printf("FATAL:: Could not init TTF!\n");
        exit(1);
    }
    winData.font = TTF_OpenFont(winData.fonttitle, 24);
    if(winData.font == NULL) {
        printf("FATAL:: Could not load font!\n");
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
    TTF_CloseFont(winData.font);
    TTF_Quit();
    SDL_Quit();
}