#include "RenderSystem.h"

#include <game/Entity.h>
#include <game/components/Champion.h>
#include <game/components/Transform.h>
#include <math/Mat4.h>
#include <client/graphics/Mesh.h>
#include <client/graphics/Texture.h>

#include <glad/glad.h>

#include <stdio.h>

Vector champion_meshes;
static int palette_texture = -1;

static ShaderProgram shader_program;

//Mat4 view = Mat4_lookat((Vec3) {0.0f, 0.0f, -5.0f} , (Vec3) {0.0f, 1.0f, 0.0f}, (Vec3) {0.0f, 0.0f, 0.0f});
static Vec3 camera_location = {0.0f, 2.0f, -5.0f};
static Mat4 projection;
static Mat4 view;

static Window* window;

void RenderSystem_init(Window* the_window) {
    window = the_window;
}

void RenderSystem_start() {
    printf("Starting render system!\n");

    view = Mat4_lookat(camera_location, Vec3_y(), Vec3_zero());
    projection = Mat4_perspective(90.0f, (float) (window->width) / (float) window->height, 0.01, 100.0f);

    palette_texture = Texture_new("assets/color-palette.png");

    Shader vertex = Shader_load(GL_VERTEX_SHADER, "assets/shaders/vertex.glsl");
    Shader fragment = Shader_load(GL_FRAGMENT_SHADER, "assets/shaders/fragment.glsl");
    Shader shaders[] = {
        vertex, fragment,
    };
    shader_program = Shaders_link(shaders, 2);
    if (!shader_program.is_valid || !vertex.is_valid || !fragment.is_valid) {
        printf("Error loading shaders...\n");
        return;
    }

    Vector_init(&champion_meshes, sizeof(Mesh));
    Vector_resize(&champion_meshes, NUM_CHAMPS);

    {
        Mesh m;
        Mesh_load(&m, "assets/wizard.obj", palette_texture);
        Vector_set(&champion_meshes, CHAMP_WIZARD, &m);
    }
}

void RenderSystem_update(float delta) {
    EntityQueryHandle query_handle = Entity_query(2, TRANSFORM, CHAMPION);
    {
        EntityQuery* query = Entity_get_query(query_handle);

        for(int i = 0; i < query->num; i++) {
            Transform* t = Entity_get_component(query->handles[i], TRANSFORM);
            Champion* c = Entity_get_component(query->handles[i], CHAMPION);

            Mat4 model = Mat4_identity();
            model.x.x = t->transform.x.x;
            model.x.z = t->transform.x.y;

            model.z.x = t->transform.y.x;
            model.z.z = t->transform.y.y;

            model.w.x = t->transform.z.x;
            model.w.z = t->transform.z.y;


            Shader_uniform_Mat4(&shader_program, "projection", &projection);
            Shader_uniform_Mat4(&shader_program, "view", &view);
            Shader_uniform_Mat4(&shader_program, "model", &model);

            Mesh* m = Vector_get(&champion_meshes, c->type);
            Mesh_draw(m, &shader_program);
        }
    }
    Entity_return_query(query_handle);
}
