#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>

typedef struct {
    SDL_Window* window;
    int height;
    int width;
    SDL_GLContext context;
} Window;

void Window_init(Window* w, const char* name, int width, int height);
void Window_delete(Window* w);

#endif
