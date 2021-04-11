#include <stdio.h>
#include <math/AnuraMath.h>
#include <lib/Entity.h>
#include <lib/Player.h>

#include <SDL2/SDL.h>

int main() {
    //SDL stuff
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Failed to init SDL2\n");
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("anura",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            680, 480,
            0);

    if (!window) {
        printf("Error creating window!\n");
        return -1;
    }

    SDL_Surface *window_surface = SDL_GetWindowSurface(window);

    if(!window_surface)
    {
        printf("Failed to get the surface from the window\n");
        return -1;
    }
    SDL_UpdateWindowSurface(window);
    //end SDL

    Map m;
    Map_load(&m, "navmesh.obj");
    //Map_print(&m);

    Player p;
    Player_init(&p);

    AutoPather_gen_path(&p.auto_pather, &m, (Vec2) {0.0f, 0.0f}, (Vec2){4.0f, 3.0f});

    SDL_Renderer* renderer = SDL_GetRenderer(window);
    unsigned int last_time = 0, current_time;
    int running = 1;
    while (running) {
        current_time = SDL_GetTicks();
        float dt = (current_time - last_time) / 1000.0f;
        last_time = current_time;

        //polling events
        SDL_Event e;
        while(SDL_PollEvent(&e) > 0)
        {
            switch(e.type)
            {
                case SDL_QUIT:
                    running = 0;
                    break;
            }

        }

        //updating
        Player_update(&p, dt);

        //rendering
        
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_Rect rect;
        rect.x = 10;
        rect.y = 50;
        rect.w = 100;
        rect.h = 100;
        SDL_RenderFillRect(renderer, &rect);

        SDL_RenderPresent(renderer);
    }

    if (window) {
        SDL_DestroyWindow(window);
    }

    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }

    Map_delete(&m);
}
