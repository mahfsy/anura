#include "Window.h"

#include <glad/glad.h>

void Window_init(Window* w, const char* name, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Failed to init SDL2\n");
        w->window = NULL;
        return;
    }

    w->window = SDL_CreateWindow(name,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            width, height,
            SDL_WINDOW_OPENGL);

    if (!w->window) {
        printf("Error creating window!\n");
        return;
    }

    w->width = width;
    w->height = height;

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,3);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    w->context = SDL_GL_CreateContext(w->window);

    gladLoadGLLoader(SDL_GL_GetProcAddress);

    SDL_GL_SetSwapInterval(0);

    glEnable(GL_DEPTH_TEST);
}

void Window_delete(Window* w) {
    SDL_DestroyWindow(w->window);
    w->window = NULL;
    SDL_Quit();
}

