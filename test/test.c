#include "../src/util.h"
#include "../src/oblivision.h"

void run() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("ERROR:: Could not init SDL!\n");
        exit(1);
    }

    init_graphics(1280, 720);

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