### Oblivision

<div align="center">
  <br />
  <p>
    <a href="https://github.com/TristanWellman/oblivision"><img src="oblivision.png" width="500" alt="oblivision" /></a>
  </p>
  <br />
</div>

## Support

Tested: 

- [x] Windows 11/10/7/vista/xp
- [x] Linux Arch/Debian
- [x] MacOS Intel&Arm

## Example

Initializes and renders two windows(Window 1 & 2).
```c
#include <oblivision.h>

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
        OV_createWindow(300, 200, (OV_vec2){0, 20}, "Window 1");
        OV_createWindow(300, 40, (OV_vec2){700, 500}, "Window 2");
        OV_addText("Window 1", "Window 1");
        OV_addText("Window 2", "Hello World!");
        OV_addText("Window 1", "Hello Sailor!");
		OV_createButton("Window 1", "Press Me", (OV_vec2){0,0});
        OV_renderFrame(NULL,NULL);
    }
    OV_free();
    return 0;
}
```
<div>
  <br />
  <p>
    <a href="https://github.com/TristanWellman/oblivision"><img src="window.PNG" width="1282" alt="oblivision" /></a>
  </p>
  <br />
</div>


## Build

Bulding requires:
* SDL 2.26.5
* SDL_ttf 2.20.2
* SDL_Image

Just drop source files into your project.

It should look like:
```
Project-|
       SDL-|
          sdl files...
       src-|
          oblivision.c
          oblivision.h
          colors.h 
          Your project files...
       Makefile (or prefered build method)
       SDL2.dll (for windows)
       SDL2_ttf.dll (for windows)
```


```bash
$ git clone https://github.com/TristanWellman/oblivision.git
$ cd oblivision
$ make
```
