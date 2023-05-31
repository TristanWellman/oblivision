### Oblivision

<div align="center">
  <br />
  <p>
    <a href="https://github.com/TristanWellman/oblivision"><img src="https://github.com/TristanWellman/oblivision/blob/master/window.PNG" width="800" alt="oblivision" /></a>
  </p>
  <br />
</div>

## Support

- [x] Windows XP - Windows 10
- [ ] Linux (Untested)

## Example

Initializes and renders two windows(Window 1 & 2).
```c
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
        OV_setBackground(color_test);
        /*Create window widget
         * Y position has to be at-least 20 */
        OV_createWindow(256, 144, (vec2){0, 20}, "Window 1");
        OV_createWindow(200, 20, (vec2){700, 500}, "Window 2");
        OV_renderFrame(event);
    }
    OV_free();
    return 0;
}
```

## Build

Bulding requires:
* SDL 2.26.5
* SDL_ttf 2.20.2

```bash
$ git clone https://github.com/TristanWellman/oblivision.git
$ cd oblivision
$ make
```