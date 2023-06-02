#include "../src/oblivision.h"

int pixel_data[500 * 500];
void fill_pixels() {
    int current_x, current_y;
    OV_COLOR start_color = {BG};
    for (current_x = 0; current_x < 500; current_x++) {
        for (current_y = 0; current_y < 500; current_y++) {
            pixel_data[current_y * 500 + current_x] = start_color.color;
            start_color.color = start_color.color + current_x * current_y;
        }
    }
}

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
        const char *window_id = "Window 1";
        OV_createWindow(500, 500, (vec2){0, 20}, window_id);
        fill_pixels();
        OV_fillWindowData(window_id, pixel_data);

        OV_renderFrame(event);
    }

    OV_free();
    return 0;
}