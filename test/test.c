#include "../src/oblivision.h"

int main(int argc, char *argv[]) {
    SDL_Window *window;
    SDL_Event event;

    /*Shows fps*/
    OV_setFlags(OV_DEBUG_ENABLE);

    OV_setFont("iosevka.ttc");
    OVInit(window, 1280, 720, "test");

    for(;;) {
        OV_pollEvent(event);

        OV_COLOR color_test = {GREY};
        /*OV_colorTest();*/
        OV_setBackground(color_test);

        /*Create window widget
         * Y position has to be at-least 20 */
        OV_createWindow(300, 200, (vec2){0, 20}, "Window 1");
        OV_createWindow(300, 40, (vec2){700, 500}, "Window 2");

        OV_addText("Window 1", "Hello World!");
        OV_addText("Window 2", "Hello World!");
        OV_addText("Window 1", "Hello Sailor!");

        OV_renderFrame(event);
    }

    OV_free();
    return 0;
}