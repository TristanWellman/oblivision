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
    winData.bg_color = bg_color;
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

int custom_window_fill = MAX_WIGS+1;
int current_pixel_data[];
void OV_fillWindowData(const char *window_ID, int pixel_data[]) {
    int i;
    for(i = 0; i < MAX_WIGS; i++) {
        if(wigData.names[i] == window_ID) {
            custom_window_fill = i;
            break;
        }
    }
    if(custom_window_fill == MAX_WIGS+1) {
        printf("ERROR:: %s: Wrong window ID!\n", window_ID);
    } else {
        int j;
        for(j = 0; j < sizeof(*pixel_data); j++) {
            current_pixel_data[j] = pixel_data[j];
        }
    }
}

void OV_addText(const char *window_ID, char *text) {
    int wig_index;
    int i;
    for(i = 0; i < MAX_WIGS; i++) {
        if(wigData.names[i] == window_ID) {
            wig_index = i;
            break;
        }
    }

}

int OV_createWindow(int width, int height, vec2 pos, const char *name) {

    int i;
    for(i = 0; i < sizeof(wigData.names); i++) {
        if(wigData.names[i] == name) {
            return 1;
        }
        if(wigData.names[i] == NULL) {
            wigData.names[i] = name;
            if(pos.y < 20) {
                pos.y = 20;
            }
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
                     if(i == custom_window_fill) {
                         for(x2 = wigData.wig_pos[i].x; x2 < (wigData.wig_pos[i].x + wigData.wig_sizes[i].x); x2++) {
                             for(y2 = wigData.wig_pos[i].y; y2 < (wigData.wig_pos[i].y + wigData.wig_sizes[i].y); y2++) {
                                 winData.pixel_data[y2 * winData.width + x2] = current_pixel_data[x2+y2];
                             }
                         }
                     } else {
                         for (x2 = wigData.wig_pos[i].x; x2 < (wigData.wig_pos[i].x + wigData.wig_sizes[i].x); x2++) {
                             for (y2 = wigData.wig_pos[i].y;
                                  y2 < (wigData.wig_pos[i].y + wigData.wig_sizes[i].y); y2++) {
                                 winData.pixel_data[y2 * winData.width + x2] = WIN_BG;
                             }
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

void unload_widget(int widget_offset) {
    current_x = 0;
    current_y = 0;
    int x2,y2;
    for(current_x = 0; current_x < winData.width; current_x++) {
        if(current_x == wigData.wig_pos[widget_offset].x+1) {
            break;
        }
        for(current_y = 0; current_y < winData.height; current_y++) {
            if(current_x == wigData.wig_pos[widget_offset].x &&
                current_y == wigData.wig_pos[widget_offset].y) {
                winData.pixel_data[current_y * winData.width + current_x] = winData.bg_color.color;
                for(x2 = wigData.wig_pos[widget_offset].x;
                    x2 < (wigData.wig_pos[widget_offset].x + wigData.wig_sizes[widget_offset].x); x2++) {
                    for(y2 = wigData.wig_pos[widget_offset].y;
                        y2 < (wigData.wig_pos[widget_offset].y + wigData.wig_sizes[widget_offset].y); y2++) {
                        winData.pixel_data[y2 * winData.width + x2] = winData.bg_color.color;
                    }
                }
                /*make title bar*/
                vec2 bar_pos = {wigData.wig_pos[widget_offset].x, wigData.wig_pos[widget_offset].y-20};
                vec2 bar_size = {wigData.wig_sizes[widget_offset].x, 20};
                int x3,y3,x4,y4;

                for(x3 = bar_pos.x; x3 < (bar_pos.x + bar_size.x); x3++) {
                    for(y3 = bar_pos.y; y3 < (bar_pos.y + bar_size.y); y3++) {
                        winData.pixel_data[y3 * winData.width + x3] = winData.bg_color.color;
                    }
                }
                break;
            }
        }
    }
}

int in_window = MAX_WIGS+1;
void update_position(SDL_Event event) {
    vec2 mouse_pos;
    int i, j, k;

    SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);
    //printf("%d:%d\n", mouse_pos.x, mouse_pos.y);
    if(event.type == SDL_MOUSEBUTTONDOWN) {
        //printf("%d:%d\n", mouse_pos.x, mouse_pos.y);
        for(i = 0; i < MAX_WIGS; i++) {
            for(j = wigData.wig_pos[i].x; j < (wigData.wig_pos[i].x + wigData.wig_sizes[i].x); j++) {
                for(k = wigData.wig_pos[i].y-20; k < wigData.wig_pos[i].y; k++) {
                    if(j == mouse_pos.x && k == mouse_pos.y) {
                        winData.in_window = i;
                        break;
                    }
                    if(winData.in_window == i) {
                        break;
                    }
                }
            }
        }
        //printf("%d\n", winData.in_window);
    }
    if(event.type == SDL_MOUSEBUTTONUP) {
        vec2 prev_wiv_pos;
        //printf("%d\n", winData.in_window);
        for(i = 0; i < MAX_WIGS; i++) {
            if(i == winData.in_window) {
                prev_wiv_pos.x = wigData.wig_pos[i].x;
                prev_wiv_pos.y = wigData.wig_pos[i].y;
                unload_widget(i);
                if(mouse_pos.y < 20) {
                    mouse_pos.y = 20;
                }
                wigData.wig_pos[i].x = mouse_pos.x;
                wigData.wig_pos[i].y = mouse_pos.y;

                break;
            }
        }
    }
}

void OV_pollEvent(SDL_Event event) {
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            OV_free();
            break;
        }
        update_position(event);
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

    int i;
    for(i = 0; i < MAX_WIGS; i++) {
        if(wigData.names[i] == NULL) {
            break;
        }
        wigData.title_rect[i].x = wigData.wig_pos[i].x;
        wigData.title_rect[i].y = wigData.wig_pos[i].y-20;
        wigData.title_rect[i].w = /*wigData.wig_sizes[i].x/2*/ strlen(wigData.names[i])*PIXELSPERCHAR;
        wigData.title_rect[i].h = 20;
        SDL_RenderCopy(winData.renderer, winData.text_texture[i],
                       NULL, &wigData.title_rect[i]);
    }

    winData.pixel_data[0] = RED;
    SDL_Delay(38);

    Uint64 end = SDL_GetPerformanceCounter();
    float elapsed = (end - start)/(float)SDL_GetPerformanceFrequency();
    //printf("FPS: %d\n", (int)(1.0f/elapsed));
    if(winData.ovflag == OV_DEBUG_ENABLE) {
        char buf[0x100];
        snprintf(buf, sizeof(buf), "FPS: %d", (int) (1.0f / elapsed));
        SDL_Surface *fps_surface = TTF_RenderText_Blended(winData.font, buf,
                                                        (SDL_Color) {255, 75, 75});
        SDL_Texture *fps_texture = SDL_CreateTextureFromSurface(winData.renderer, fps_surface);
        SDL_Rect fps_rect = {0, winData.height - 24, 100, 20};
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
    winData.in_window = MAX_WIGS+1;
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

    int i,j,k;
    for(i = 0; i < sizeof(winData.pixel_data); i++) {
        if (i >= winData.width * winData.height) {
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
    exit(0);
}