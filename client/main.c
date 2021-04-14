#include <stdio.h>
#include <math/AnuraMath.h>
#include <game/Map.h>
//#include <lib/Entity.h>
//#include <lib/Player.h>
#include <game/Entity.h>
#include <game/World.h>

#include <SDL2/SDL.h>

#include "graphics/Window.h"
#include "graphics/Shader.h"
#include "graphics/Mesh.h"
#include "graphics/Texture.h"
#include <glad/glad.h>

int main() {
    Window window;
    Window_init(&window, "anura", 640, 480);

    Shader vertex = Shader_load(GL_VERTEX_SHADER, "assets/shaders/vertex.glsl");
    Shader fragment = Shader_load(GL_FRAGMENT_SHADER, "assets/shaders/fragment.glsl");
    Shader shaders[] = {
        vertex, fragment,
    };
    ShaderProgram program = Shaders_link(shaders, 2);
    if (!program.is_valid || !vertex.is_valid || !fragment.is_valid) {
        printf("Error loading shaders...\n");
        return 1;
    }

    Mesh triangle;
    //Mesh_init_test_triangle(&triangle);
    int palette_texture = Texture_new("assets/color-palette.png");
    Mesh_load(&triangle, "assets/wizard.obj", palette_texture);
    
    World_init_systems();
    World_start();

    Mat4 projection = Mat4_perspective(90.0f, (float) (window.width) / (float) window.height, 0.01, 100.0f);
    //Mat4 view = Mat4_lookat((Vec3) {0.0f, 0.0f, -5.0f} , (Vec3) {0.0f, 1.0f, 0.0f}, (Vec3) {0.0f, 0.0f, 0.0f});
    Vec3 camera_location = {0.0f, 2.0f, -5.0f};
    Mat4 view = Mat4_lookat(camera_location, Vec3_y(), Vec3_zero());

    Mat4 model = Mat4_identity();

    float elapsed_time = 0.0f;
    unsigned int last_time = 0, current_time;
    int running = 1;
    while (running) {
        current_time = SDL_GetTicks();
        float dt = (current_time - last_time) / 1000.0f;
        last_time = current_time;
        elapsed_time += dt;

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

                    }
                    break;
            }
        }

        World_update(dt);

        //rendering
        glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        model = Mat4_rotate_around_y(elapsed_time * 0.05);

        //camera_location = Vec3_plus(camera_location, (Vec3) {0.0f, -1.0f*dt + 0.0f, 0.0f});
        //view = Mat4_lookat(camera_location, Vec3_y(), Vec3_zero());

        //Mat4_print(view);

        Shader_uniform_Mat4(&program, "projection", &projection);
        Shader_uniform_Mat4(&program, "view", &view);
        Shader_uniform_Mat4(&program, "model", &model);
        Mesh_draw(&triangle, &program);

        SDL_GL_SwapWindow(window.window);
    }

    Window_delete(&window);
}
