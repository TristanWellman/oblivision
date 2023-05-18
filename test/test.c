#include "../src/util.h"
#include "../src/oblivision.h"

int main(int argc, char *argv[]) {
    SDL_Window *window;
    SDL_Event event;

    OVInit(window, 1280, 720, "test");
    int running = 1;
    while(running == 1) {
        while(SDL_PollEvent(&event) != 0) {
            if(event.type == SDL_QUIT) {
                running = 0;
                break;
            }
        }
        OV_COLOR color_test = {GREY};
        /*OV_colorTest();*/
        OV_setBackground(color_test);

        /*Create window widget*/
        OV_createWindow(20, 20, (vec2){200, 200}, "test");
        OV_createWindow(20, 20, (vec2){500, 500}, "test2");

        OV_renderFrame();
    }

    OV_free();
    return 0;
}