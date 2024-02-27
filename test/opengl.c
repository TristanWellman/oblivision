#define OV_OPENGL
#include "../src/oblivision.h"
#define PORTABLEGL_IMPLEMENTATION
#include <portablegl.h>

vec4 Red = { 1.0f, 0.0f, 0.0f, 1.0f };
vec4 Green = { 0.0f, 1.0f, 0.0f, 1.0f };
vec4 Blue = { 0.0f, 0.0f, 1.0f, 1.0f };

typedef struct My_Uniforms {
	vec4 v_color;
} My_Uniforms;

void identity_vs(float* vs_output, vec4* vertex_attribs, Shader_Builtins* builtins, void* uniforms);
void uniform_color_fs(float* fs_input, Shader_Builtins* builtins, void* uniforms);

glContext globalGLContext;
u32 *globalGLPixBuf;
SDL_Texture *oglTexture;

int main(int argc, char *argv[]) {
    SDL_Window *window;
    SDL_Event event;

    /*Shows fps*/
    OV_setFlags(OV_DEBUG_ENABLE);
    OV_setFlags(OV_OPENGL_ENABLE);

    OV_setFont("iosevka.ttc");
    OVInit(window, 1280, 720, "test");

    if(!init_glContext(&globalGLContext,
        &globalGLPixBuf, 1280, 720,
        32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000)) {
        printf("ERROR:: Failed to init glContext");
        exit(1);
    }
	float points[] = { -0.5, -0.5, 0,
	                    0.5, -0.5, 0,
	                    0,    0.5, 0 };
	My_Uniforms the_uniforms;
	GLuint triangle;
	glGenBuffers(1, &triangle);
	glBindBuffer(GL_ARRAY_BUFFER, triangle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*9, points, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);


	GLuint myshader = pglCreateProgram(identity_vs, uniform_color_fs, 0, NULL, GL_FALSE);
	glUseProgram(myshader);

	pglSetUniform(&the_uniforms);

	the_uniforms.v_color = Red;

	glClearColor(0, 0, 0, 1);

    for(;;) {
        OV_pollEvent(event);

        /*Create window widget
         * Y position has to be at-least 20 */
        OV_createWindow(300, 200, (OV_vec2){0, 20}, "Window 1");
        OV_createWindow(300, 40, (OV_vec2){700, 500}, "Window 2");

        OV_addText("Window 1", "Window 1");
        OV_addText("Window 2", "Hello World!");
        OV_addText("Window 1", "Hello Sailor!");

        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES,0,3);
        OV_renderFrame(oglTexture, globalGLPixBuf);
    }

    OV_free();
    return 0;
}

void identity_vs(float* vs_output, vec4* vertex_attribs, Shader_Builtins* builtins, void* uniforms) {
	builtins->gl_Position = vertex_attribs[0];
}

void uniform_color_fs(float* fs_input, Shader_Builtins* builtins, void* uniforms) {
	builtins->gl_FragColor = ((My_Uniforms*)uniforms)->v_color;
}
