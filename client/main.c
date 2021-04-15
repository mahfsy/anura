#include <stdio.h>
#include <math/AnuraMath.h>
#include <game/Map.h>
//#include <lib/Entity.h>
//#include <lib/Player.h>
#include <game/Entity.h>
#include <game/World.h>
#include <game/Commands.h>

#include <SDL2/SDL.h>

#include "graphics/Window.h"
#include "graphics/Shader.h"
#include "graphics/Mesh.h"
#include "graphics/Texture.h"

#include <game/components/Champion.h>
#include <game/components/Transform.h>
#include <game/components/Velocity.h>

#include "systems/RenderSystem3D.h"

#include <glad/glad.h>

int main() {
    Window window;
    Window_init(&window, "anura", 640, 480);

    EntityHandle wizard_handle = Entity_new();
    //create wizard champion
    {
        Entity_add_component(wizard_handle, TRANSFORM);
        Entity_add_component(wizard_handle, VELOCITY);

        Velocity* v = Entity_get_component(wizard_handle, VELOCITY);
        v->speed = 20.0f;

        Entity_add_component(wizard_handle, ABILITY_USER);
        Entity_add_component(wizard_handle, AUTO_PATHER);
        Entity_add_component(wizard_handle, CHAMPION);
        Champion* c = Entity_get_component(wizard_handle, CHAMPION);
        Champion_init(c, CHAMP_WIZARD);
    }

    //init systems
    World_init_systems();

    RenderSystem3D_init(&window);
    System render_system = (System) {
        RenderSystem3D_start,
        RenderSystem3D_update,
    };
    World_register_system(render_system);

    World_start();

    Command_init_defaults();
    {
        int cmd_index = Command_new(AUTO_PATHER_MOVE_COMMAND);
        AutoPatherMoveCommand* c = Command_get(AUTO_PATHER_MOVE_COMMAND, cmd_index);
        c->auto_pather_index = Entity_get_component_index(wizard_handle, AUTO_PATHER);
        c->start = (Vec2) { 0.0f, 0.0f };
        c->end = (Vec2) { 20.0f, 5.0f };
        Command_issue(AUTO_PATHER_MOVE_COMMAND, cmd_index);
    }

    float elapsed_time = 0.0f;
    unsigned int last_time = 0, current_time;
    int running = 1;
    float time_in_this_tick = 0.0f;
    while (running) {
        current_time = SDL_GetTicks();
        float dt = (current_time - last_time) / 1000.0f;
        last_time = current_time;

        elapsed_time += dt;
        time_in_this_tick += dt;
        if (time_in_this_tick < 0.001) {
            continue;
        }
        dt = time_in_this_tick;
        time_in_this_tick = 0;

        //polling events
        SDL_Event e;
        while(SDL_PollEvent(&e) > 0)
        {
            switch(e.type)
            {
                case SDL_QUIT:
                    running = 0;
                    break;
                case SDL_KEYDOWN:
                    switch(e.key.keysym.sym) {
                        case SDLK_a: RenderSystem3D_move_camera(CAMERA_MOVE_LEFT, true); break;
                        case SDLK_w: RenderSystem3D_move_camera(CAMERA_MOVE_UP, true); break;
                        case SDLK_s: RenderSystem3D_move_camera(CAMERA_MOVE_DOWN, true); break;
                        case SDLK_d: RenderSystem3D_move_camera(CAMERA_MOVE_RIGHT, true); break;
                    }
                    break;
                case SDL_KEYUP:
                    switch(e.key.keysym.sym) {
                        case SDLK_a: RenderSystem3D_move_camera(CAMERA_MOVE_LEFT, false); break;
                        case SDLK_w: RenderSystem3D_move_camera(CAMERA_MOVE_UP, false); break;
                        case SDLK_s: RenderSystem3D_move_camera(CAMERA_MOVE_DOWN, false); break;
                        case SDLK_d: RenderSystem3D_move_camera(CAMERA_MOVE_RIGHT, false); break;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN: {
                    float mouse_x = (e.button.x - window.width / 2.0f) / (window.width / 2.0f);
                    float mouse_y = -1.0f * (e.button.y - window.height / 2.0f) / (window.height / 2.0f);

                    Vec3 click_coords = RenderSystem3D_screen_coords_raycast_to_floor(mouse_x, mouse_y);

                    int cmd_index = Command_new(AUTO_PATHER_MOVE_COMMAND);
                    AutoPatherMoveCommand* c = Command_get(AUTO_PATHER_MOVE_COMMAND, cmd_index);
                    c->auto_pather_index = Entity_get_component_index(wizard_handle, AUTO_PATHER);
                    c->start = (Vec2) { 0.0f, 0.0f };
                    c->end = (Vec2) { click_coords.x, click_coords.z };
                    Command_issue(AUTO_PATHER_MOVE_COMMAND, cmd_index);
                } break;
            }
        }

        //clear the color before updating, because our rendersystem is in the game
        glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        World_update(dt);

        //Transform* t = Entity_get_component(wizard_handle, TRANSFORM);
        //t->transform = Mat3_rotated(t->transform, dt);
        //Mat3_print(t->transform);

        SDL_GL_SwapWindow(window.window);
    }

    Window_delete(&window);
}
