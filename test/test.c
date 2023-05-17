#include "../src/util.h"
#include "../src/oblivision.h"

void run() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("ERROR:: Could not init SDL!\n");
        exit(1);
    }

    SDL_Surface *window;
    SDL_Event event;

    OVInit(window, 1280, 720);
    int running = 1;
    while(running == 1) {
        SDL_PollEvent(&event);
        if(event.type == SDL_QUIT) {
            running = 0;
        }
        OV_COLOR color_test = {255};
        OV_colorTest();
        //OV_setBackground(color_test);
        OV_renderFrame();
    }
    SDL_Quit();
}

#if defined __WIN32 | __WIN64 | __WIN32__ | __WIN64__
int WinMain(int argc, char *argv[]) {
    run();
    return 0;
}
#else
int main(int argc, char *argv[]) {
    run();
    return 0;
}
#endif