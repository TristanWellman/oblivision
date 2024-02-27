/*Copyright (c) 2023, Tristan Wellman*/

#include "oblivision.h"

struct windata winData;
struct widget_data wigData;
struct windataopt backup;

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
int *backup_pointer = &backup.pixelDataBack[0];
void OV_setBackground(OV_COLOR bg_color) {
    if(backup.pixelDataBack[0]==bg_color.color) {
	    //memcpy(winData.pixel_data, backup.pixelDataBack, sizeof(backup.pixelDataBack));
		winData.pixel_data[0] = (int)*backup_pointer;
		return;
	}
    winData.bg_color = bg_color;
    if ((unsigned int)winData.pixel_data[0] != RED) {
        for (current_x = 0; current_x < winData.width; current_x++) {
            for (current_y = 0; current_y < winData.height; current_y++) {
                winData.pixel_data[current_y * winData.width + current_x] = bg_color.color;
            }
        }
    }
    current_x = 0;
    current_y = 0;

    *backup_pointer = winData.pixel_data[0];
}

int custom_window_fill = MAX_WIGS+1;
int current_pixel_data[1];
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
        for(j = 0; (unsigned int)j < sizeof(*pixel_data); j++) {
            current_pixel_data[j] = pixel_data[j];
        }
    }
}

void OV_addImage(const char *image_file, OV_vec2 position, OV_vec2 size) {
    SDL_Surface *image_surface = IMG_Load(image_file);
    if(image_surface == NULL) {
        printf("FATAL:: Could not load image: %s\n", image_file);
        exit(1);
    }

    SDL_Texture *tempt = SDL_CreateTextureFromSurface(winData.renderer,
                                                      image_surface);

    int i;
    for(i = 0; i < MAX_IMAGES; i++) {
        if(winData.custom_image_textures[i] != NULL) {
            if(strcmp(winData.image_files[i], image_file) == 0) {
                break;
            }
        }
        if(winData.custom_image_textures[i] == NULL) {
            winData.image_files[i] = image_file;
            winData.custom_image_textures[i] = SDL_CreateTextureFromSurface(winData.renderer,
                                                                            image_surface);;

            winData.custom_image_rects[i].x = position.x;
            winData.custom_image_rects[i].y = position.y;
            winData.custom_image_rects[i].w = size.x;
            winData.custom_image_rects[i].h = size.y;

            log_debug("Image loaded: [%d]%s\n", i, image_file);
            break;
        }
    }
    SDL_FreeSurface(image_surface);
    SDL_DestroyTexture(tempt);
}

void OV_unloadImage(const char *image_file) {
    int i;
    for(i = 0; i < MAX_IMAGES; i++) {
        if(winData.image_files[i] == NULL) {
            break;
        }
        if(strcmp(winData.image_files[i], image_file) == 0) {
            winData.image_files[i] = NULL;
            winData.custom_image_textures[i] = NULL;
            break;
        }
    }
}

void OV_addCustomText(TTF_Font *font,
                      SDL_Texture *font_texture, SDL_Surface *font_surface,
                      OV_vec2 position, char *text, SDL_Color color) {

    font_surface = TTF_RenderText_Solid(font, text, color);
    font_texture = SDL_CreateTextureFromSurface(winData.renderer, font_surface);
    SDL_Rect custom_rect;
    custom_rect.x = position.x;
    custom_rect.y = position.y;

    custom_rect.h = 24;
    custom_rect.w = strlen(text)*(5+PIXELSPERCHAR);

    int i;
    for(i = 0; i < MAX_CTEXTS; i++) {
        if(winData.custom_text_textures[i] != NULL) {
            if(strcmp(winData.custom_texts[i], text) == 0) {
                break;
            }
        }
        if(winData.custom_text_textures[i] == NULL) {
            winData.custom_texts[i] = text;
            winData.custom_text_textures[i] = SDL_CreateTextureFromSurface(winData.renderer, font_surface);;
            winData.custom_text_rects[i] = custom_rect;
            log_debug("Custom text loaded: [%d]\"%s\"\n", i, text);
            break;
        }
    }
    SDL_FreeSurface(font_surface);
    SDL_DestroyTexture(font_texture);
}

void OV_unloadCustomText(char *text) {
    int i;
    for(i = 0; i < MAX_CTEXTS; i++) {
        if(winData.custom_texts[i] == NULL) {
            break;
        }
        if(strcmp(winData.custom_texts[i], text) == 0) {
            winData.custom_texts[i] = NULL;
            winData.custom_text_textures[i] = NULL;
            break;
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
    int j,k;
    for(j = 0; j < MAX_WIGS; j++) {
        if(j == wig_index) {
            for(k = 0; k < MAX_WIGS; k++) {
                if(wigData.wig_texts[j][k] == NULL ||
                    wigData.wig_texts[j][k] == text) {

                    char *check = strstr(text, "~b~");
					if(check!=NULL) {
						check++;
						wigData.wig_texts[j][k] = text;
                    	wigData.wig_texts_surfaces[j][k] = TTF_RenderText_Solid(winData.font, check,(SDL_Color) {0,0,0,255});
					} else {
						wigData.wig_texts[j][k] = text;
						wigData.wig_texts_surfaces[j][k] = TTF_RenderText_Solid(winData.font, wigData.wig_texts[j][k],(SDL_Color) {0,0,0,255});   
					}
					wigData.wig_texts_textures[j][k] = SDL_CreateTextureFromSurface(winData.renderer, wigData.wig_texts_surfaces[j][k]);

                    wigData.wig_texts_rects[j][k].x = wigData.wig_pos[j].x;

                    if(k == 0) {
                        wigData.wig_texts_rects[j][k].y = wigData.wig_pos[j].y;
                    } else {
                        wigData.wig_texts_rects[j][k].y = wigData.wig_texts_rects[j][k-1].y + 30;
                    }
                    wigData.wig_texts_rects[j][k].h = 20;
                    wigData.wig_texts_rects[j][k].w = strlen(wigData.wig_texts[j][k])*(PIXELSPERCHAR);
                    /*if(winData.ovflag == OV_DEBUG_ENABLE) {
                        log_debug("[%s]: %s[%d]: (%d,%d)\n",
                               wigData.names[j],
                               wigData.wig_texts[j][k], k,
                               wigData.wig_texts_rects[j][k].x,
                               wigData.wig_texts_rects[j][k].y);
                    }*/
                    break;
                }
            }
        } else {
            continue;
        }
    }

}

void OV_createButton(const char *window_ID, const char *button_ID, OV_vec2 pos) {
    int buttonWidth = 50;
    int buttonHeight = 50;
    int i,j;
    for(i=0;i<MAX_WIGS;i++) {
		if(wigData.names[i] == window_ID) {
			for(j=0;j<MAX_WIGS;j++) {
				int l=0;
				char buf[256];
				strcpy(buf,button_ID);
				if(buf == wigData.buttons.button_names[i][j]) {
					snprintf(buf, sizeof(buf), "~b~%s:%d",button_ID,l);
					strcpy((char *)button_ID,buf);
					l++;
				}
			}
			OV_addText(window_ID, (char *)button_ID);
			break;
        }
    }

}

int OV_createWindow(int width, int height, OV_vec2 pos, const char *name) {

    int i;
    for(i = 0; (unsigned int)i < sizeof(wigData.names); i++) {
        if(wigData.names[i] == name) {
            return 1;
        }
        if(wigData.names[i] == NULL) {
            wigData.names[i] = name;
            if(pos.y < 20) {
                pos.y = 20;
            }
            wigData.wig_pos[i] = pos;
            wigData.wig_sizes[i] = (OV_vec2){width, height};
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
	if(wigData.wig_pos != winData.opt.wigPosBack) {
    	for(i = 0; (unsigned int)i < sizeof(wigData.names); i++) {
        	if(wigData.names[i] == NULL) break;
        	for(current_x = 0; current_x < winData.width; current_x++) {
            	if(current_x == wigData.wig_pos[i].x+1) break;
            	for(current_y = 0; current_y < winData.height; current_y++) {
				    if(current_y == wigData.wig_pos[i].y+1) break;
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
                     	OV_vec2 bar_pos = {wigData.wig_pos[i].x, wigData.wig_pos[i].y-20};
                     	OV_vec2 bar_size = {wigData.wig_sizes[i].x, 20};
                     	int x3,y3;

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
            	                                           (SDL_Color){255,255,255,255});
        	winData.text_texture[i] = SDL_CreateTextureFromSurface(winData.renderer, winData.text_surface[i]);
    	}
	}
	int j,k;
	memcpy(winData.opt.wigPosBack, wigData.wig_pos, ARRLEN(wigData.wig_pos));
	//memcpy(winData.opt.pixelDataBack, winData.pixel_data, ARRLEN(winData.pixel_data)); 
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
                OV_vec2 bar_pos = {wigData.wig_pos[widget_offset].x, wigData.wig_pos[widget_offset].y-20};
                OV_vec2 bar_size = {wigData.wig_sizes[widget_offset].x, 20};
                int x3,y3;

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
    OV_vec2 mouse_pos;
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
        //vec2 prev_wiv_pos;
        //printf("%d\n", winData.in_window);
        for(i = 0; i < MAX_WIGS; i++) {
            if(i == winData.in_window) {
                //prev_wiv_pos.x = wigData.wig_pos[i].x;
                //prev_wiv_pos.y = wigData.wig_pos[i].y;
                unload_widget(i);
                if(mouse_pos.y < 20) {
                    mouse_pos.y = 20;
                }
                wigData.wig_pos[i].x = mouse_pos.x;
                wigData.wig_pos[i].y = mouse_pos.y;
				winData.in_window = MAX_WIGS+1;
                break;
            }
        }
    }
}

Uint64 start;
void OV_pollEvent(SDL_Event event) {
    start = SDL_GetPerformanceCounter();
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            OV_free();
            break;
        }
        update_position(event);
    }
}

float OV_FPS() {
    return winData.OV_FPS;
}

void OV_updateOGLRect(int x, int y, int w, int h) {
	winData.ovogl_global_rect.x = x;
	winData.ovogl_global_rect.y = y;
	winData.ovogl_global_rect.w = w;
	winData.ovogl_global_rect.h = h;
}

void free_OV() {
    int k,l;
    for(l = 0; l < MAX_WIGS; l++) {
        if(winData.text_surface[l] != NULL) {
            SDL_FreeSurface(winData.text_surface[l]);
        }
        if(winData.text_texture[l] != NULL) {
            SDL_DestroyTexture(winData.text_texture[l]);
        }
        for(k = 0; k < MAX_WIGS; k++) {
            if(wigData.wig_texts_surfaces[l][k] != NULL) {
                SDL_FreeSurface(wigData.wig_texts_surfaces[l][k]);
            }
            if(wigData.wig_texts_textures[l][k] != NULL) {
                SDL_DestroyTexture(wigData.wig_texts_textures[l][k]);
            }
        }
    }
}

void OV_renderFrame(SDL_Texture *oglTexture, uint32_t *oglPixBuf) {

    load_widgets();

    SDL_SetRenderTarget(winData.renderer, winData.target_texture);

    SDL_UpdateTexture(winData.texture, NULL,
                      winData.pixel_data, winData.width * 4);

    SDL_RenderCopy(winData.renderer, winData.texture,
                   NULL, NULL);

    if(winData.opengl_enabled == 1) {
		SDL_Rect oglRect;
		if(RECTCHECK(winData.ovogl_global_rect)) oglRect = winData.ovogl_global_rect; 
		oglTexture = SDL_CreateTexture(winData.renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, winData.width, winData.height);
        SDL_UpdateTexture(oglTexture, NULL,
            oglPixBuf, winData.width * sizeof(uint32_t));
        SDL_RenderCopy(winData.renderer,oglTexture,NULL,&oglRect);
    }
    /*images are first*/
    int m;
    for(m = 0; m < MAX_IMAGES; m++) {
        if(winData.custom_image_textures[m] == NULL) {
            break;
        }
        SDL_RenderCopy(winData.renderer, winData.custom_image_textures[m],
                       NULL, &winData.custom_image_rects[m]);
    }

    /*rendercopy custom texts*/
    int l;
    for(l = 0; l < MAX_CTEXTS; l++) {
        if(winData.custom_text_textures[l] == NULL /*||
            winData.custom_text_rects[l] == NULL*/) {
            break;
        }
        SDL_RenderCopy(winData.renderer, winData.custom_text_textures[l],
                       NULL, &winData.custom_text_rects[l]);
    }

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

    /*rendercopy all the window texts*/
    int j,k;
    for(j = 0; j < MAX_WIGS; j++) {
        for(k = 0; k < MAX_WIGS; k++) {
            if(wigData.wig_texts_textures[j][k] == NULL) {
                break;
            }
            SDL_RenderCopy(winData.renderer, wigData.wig_texts_textures[j][k],
                           NULL, &wigData.wig_texts_rects[j][k]);
        }
    }

    //SDL_Delay(12);

    Uint64 end = SDL_GetPerformanceCounter();
    float elapsed = (end - start)/(float)SDL_GetPerformanceFrequency();
    winData.OV_FPS = (float)(1.0f/elapsed);
    //printf("FPS: %d\n", (int)(1.0f/elapsed));
    if(winData.ovflag == OV_DEBUG_ENABLE) {
        char buf[0x100];
        snprintf(buf, sizeof(buf), "FPS: %d", (int) (1.0f / elapsed));
        SDL_Surface *fps_surface = TTF_RenderText_Blended(winData.font, buf,
                                                        (SDL_Color) {255,75,75,255});
        SDL_Texture *fps_texture = SDL_CreateTextureFromSurface(winData.renderer, fps_surface);
        SDL_Rect fps_rect = {0, winData.height - 24, 100, 20};
        SDL_RenderCopy(winData.renderer, fps_texture, NULL, &fps_rect);
        SDL_FreeSurface(fps_surface);
        SDL_DestroyTexture(fps_texture);
    }

    SDL_SetRenderTarget(winData.renderer, NULL);
    SDL_RenderPresent(winData.renderer);

    if(winData.opengl_enabled == 1) SDL_DestroyTexture(oglTexture);
    free_OV();

}

void OV_setFlags(int flag) {
    if(flag == OV_DEBUG_ENABLE) {
        winData.ovflag = flag;
    }
    if(flag == OV_OPENGL_ENABLE) {
        winData.opengl_enabled = 1;
#define OV_OGL 1
    }
}

struct OV_customFontData customFontData;
struct OV_customFontData OV_addCustomFont(const char *font_file, int font_size) {

    /*clear if used multiple times*/
    customFontData.font_file = NULL;
    customFontData.font = NULL;

    customFontData.font_file = font_file;
    customFontData.font = TTF_OpenFont(customFontData.font_file, font_size);
    if(customFontData.font == NULL) {
        log_fatal("FATAL:: Could not load font: %s\n", font_file);
        exit(1);
    }
    return customFontData;
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
        log_fatal("Could not init SDL2_ttf!\n");
        exit(1);
    }

        winData.window = SDL_CreateWindow(
                winname,
                SDL_WINDOWPOS_CENTERED_DISPLAY(0),
                SDL_WINDOWPOS_CENTERED_DISPLAY(0),
                winData.width, winData.height, 0);

    if(winData.window == NULL) {
        log_fatal("Could not set video mode!\n");
        exit(1);
    }
/*
    winData.pixel_data = (char *)malloc(
            sizeof(char *)*(winData.width * winData.height)
            );*/
    winData.renderer = SDL_CreateRenderer(winData.window, -1,
                                          SDL_RENDERER_SOFTWARE);

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
    if(winData.fonttitle == NULL) {
        /*official font for oblivision*/
        winData.font = TTF_OpenFont("iosevka.ttc", 24);
        if(winData.font == NULL) {
            printf("FATAL:: Could not load font!\n");
            exit(1);
        }
    } else {
        winData.font = TTF_OpenFont(winData.fonttitle, 24);
        if(winData.font == NULL) {
            printf("FATAL:: Could not load font!\n");
            exit(1);
        }
    }

    if (IMG_Init(IMG_INIT_PNG) == 0) {
        printf("FATAL:: Could not init SDL_image!\n");
        exit(1);
    }

    int i;
    for(i = 0; (unsigned int)i < sizeof(winData.pixel_data); i++) {
        if (i >= winData.width * winData.height) break;
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
