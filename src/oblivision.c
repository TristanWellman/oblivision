#include "oblivision.h"

struct windata winData;

int current_x = 0;
int current_y = 0;

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

void update_position(char key) {

}

void keyboard_handle() {
}

void render_loop() {
}

int init_graphics(int width, int height) {

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