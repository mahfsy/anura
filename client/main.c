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
    Mesh_init_test_triangle(&triangle);
    
    World_init_systems();
    World_start();

    Mat4 projection = Mat4_perspective(90.0f, (float) (window.width) / (float) window.height, 0.01, 100.0f);
    Mat4 view = Mat4_lookat((Vec3) {0.0f, 0.0f, -5.0f} , (Vec3) {0.0f, 1.0f, 0.0f}, (Vec3) {0.0f, 0.0f, 0.0f});
    Mat4 model = Mat4_identity();

    Mat4_print(Mat4_mul(view, projection));
    Vec3_print(Mat4_transform(Mat4_mul(view, projection), (Vec3) {-0.5f, -0.5f, 0.0f}));
    Vec3_print(Mat4_transform(view, (Vec3) {-0.5f, -0.5f, 0.0f}));

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
            }

        }

        World_update(dt);

        //rendering
        glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        model = Mat4_rotate_around_y(elapsed_time);

        Shader_uniform_matrix_4fv(&program, "projection", &projection);
        Shader_uniform_matrix_4fv(&program, "view", &view);
        Shader_uniform_matrix_4fv(&program, "model", &model);
        Mesh_draw(&triangle, &program);

        SDL_GL_SwapWindow(window.window);
    }

    Window_delete(&window);
}
