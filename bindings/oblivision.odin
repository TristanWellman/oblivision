package oblivision

import "core:fmt"
import "core:c"
import "vendor:sdl2"
import "vendor:sdl2/ttf"
import "vendor:sdl2/image"
//when ODIN_OS != .Windows do
@(extra_linker_flags="-Llib -lSDL2_ttf -lSDL2_image -lSDL2")
foreign import ov "liboblivision.a" 

//@(link_name="OV_customFontData")
CustomFontData :: struct {
		font_texture : ^sdl2.Texture,
		font_Surface : ^sdl2.Surface,
		font : ^ttf.Font,
		font_file : cstring
}
//@(link_name="vec2_s")
Vec2 :: struct {
		x : c.int,
		y : c.int}
//@(link_name="color_s")
Color :: struct {
		color : c.int}

DEBUG_ENABLE :: 1
OPENGL_ENABLE :: 2

foreign ov {


		@(link_name="OV_free")
		Free :: proc() ---
		@(link_name="OVInit")
		Init :: proc(window : ^sdl2.Window, 
				width : c.int, height : c.int,
				winname : cstring) -> c.int ---
		@(link_name="OV_setFont")
		SetFont :: proc(font : cstring) ---
		@(link_name="OV_customFontData")
		OV_CustomFontData :: proc(font_file : cstring, font_size : c.int) -> CustomFontData ---
		@(link_name="OV_setFlags")
		SetFlags :: proc(flag : c.int) ---
		@(link_name="OV_renderFrame")
		RenderFrame :: proc(oglTexture : ^sdl2.Texture, oglPixBuf : c.uint32_t) ---
		@(link_name="OV_FPS")
		fps :: proc() -> c.float ---
		@(link_name="OV_pollEvent")
		PollEvent :: proc(event : sdl2.Event) ---
		@(link_name="OV_createWindow")
		CreateWindow :: proc(width : c.int, height : c.int, pos : Vec2, name : cstring) -> c.int ---
		@(link_name="OV_createButton")
		CreateButton :: proc(window_ID : cstring, button_ID : cstring, pos : Vec2) ---
		@(link_name="OV_addText")
		AddText :: proc(window_ID : cstring, text : cstring) --- 
		@(link_name="OV_addCustomText")
		AddCustomText :: proc(font : ^ttf.Font, font_texture : ^sdl2.Texture, 
				font_surface : ^sdl2.Surface, text : ^c.char, color : sdl2.Color) ---
		@(link_name="OV_unloadImage")
		UnloadImage :: proc(image_file : cstring) ---
		@(link_name="OV_addImage")
		AddImage :: proc(image_file : cstring, position : Vec2, size : Vec2) ---
		@(link_name="OV_fillWindowData")
		FillWindowData :: proc(window_ID : cstring, pixel_data : [dynamic]c.int) ---
		@(link_name="OV_setBackground")
		SetBackground :: proc(bg_color : Color) ---
		@(link_name="OV_colorTest")
		ColorTest :: proc() ---
		
}

