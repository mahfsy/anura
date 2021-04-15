#include "RenderSystem3D.h"

#include <game/Entity.h>
#include <game/components/Champion.h>
#include <game/components/Transform.h>
#include <math/Mat4.h>
#include <client/graphics/Mesh.h>
#include <client/graphics/Texture.h>

#include <glad/glad.h>

#include <stdio.h>

static bool camera_moving[CAMERA_NUM_MOVES] = {
    false,
    false,
    false,
    false,
};
static const float camera_move_speed = 20.0f;

Vector champion_meshes;
static int palette_texture = -1;

static ShaderProgram shader_program;

//Mat4 view = Mat4_lookat((Vec3) {0.0f, 0.0f, -5.0f} , (Vec3) {0.0f, 1.0f, 0.0f}, (Vec3) {0.0f, 0.0f, 0.0f});
static Vec3 camera_facing_dir = { 0.0f, -2.0f, -0.5f};
static Vec3 camera_right_dir = { -1.0f, 0.0f, 0.0f };
static Vec3 camera_forward_dir = { 0.0f, 0.0f, -1.0f };
static Vec3 camera_location = {0.0f, 25.0f, 5.0f};
static Mat4 projection;
static Mat4 view;

static Window* window;

void RenderSystem3D_init(Window* the_window) {
    window = the_window;
}

void RenderSystem3D_start() {
    printf("Starting render system!\n");

    view = Mat4_lookat(camera_location, Vec3_y(), Vec3_plus(camera_location, camera_facing_dir));
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

void RenderSystem3D_update(float delta) {
    (void)(delta); //surpress warning

    camera_location = Vec3_plus(camera_location, Vec3_mul(camera_right_dir, (delta * camera_move_speed * camera_moving[CAMERA_MOVE_LEFT])));
    camera_location = Vec3_plus(camera_location, Vec3_mul(camera_right_dir, (delta * -1.0f * camera_move_speed * camera_moving[CAMERA_MOVE_RIGHT])));
    camera_location = Vec3_plus(camera_location, Vec3_mul(camera_forward_dir, (delta * camera_move_speed * camera_moving[CAMERA_MOVE_UP])));
    camera_location = Vec3_plus(camera_location, Vec3_mul(camera_forward_dir, (delta * -1.0f * camera_move_speed * camera_moving[CAMERA_MOVE_DOWN])));
    view = Mat4_lookat(camera_location, Vec3_y(), Vec3_plus(camera_location, camera_facing_dir));

    Shader_uniform_Mat4(&shader_program, "projection", &projection);
    Shader_uniform_Mat4(&shader_program, "view", &view);

    {
        EntityQueryHandle query_handle = Entity_query(2, TRANSFORM, CHAMPION);
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


            Shader_uniform_Mat4(&shader_program, "model", &model);

            Mesh* m = Vector_get(&champion_meshes, c->type);
            Mesh_draw(m, &shader_program);
        }
        Entity_return_query(query_handle);
    }
}

Vec3 RenderSystem3D_screen_coords_raycast_to_floor(float x, float y) {
    //this is done empirically. I don't quite grasp the math to prove this, but \_(">)_/
    Mat4 project_inverse = projection;
    project_inverse.x.x = 1.0f / project_inverse.x.x;
    project_inverse.y.y = 1.0f / project_inverse.y.y;
    project_inverse.z.z = 0.0f;
    project_inverse.z.w = 1.0f / projection.w.z;
    project_inverse.w.w = -1.0f / projection.w.z;
    project_inverse.w.z = -1.0f;

    Mat3 view_inverse_basis = Mat3_transpose(Mat4_basis(view));
    Vec3 view_inverse_origin = Vec3_mul(Mat4_origin(view), -1.0f);
    Mat4 view_inverse = Mat4_with_basis_origin(view_inverse_basis, view_inverse_origin);

    Vec4 mouse_clip = (Vec4) {x,y, 0.0f, 1.0f};

    Vec4 mouse_world = Mat4_apply(Mat4_mul(view_inverse, project_inverse), mouse_clip);
    mouse_world = Vec4_div(mouse_world, mouse_world.w);
    Vec4_print(mouse_world);

    Vec3 mouse_world_3 = (Vec3) { mouse_world.x, mouse_world.y, mouse_world.z };

    Vec3 ray = Vec3_minus(mouse_world_3, camera_location);
    float t = -1.0f * camera_location.y / ray.y;

    Vec3 ret = Vec3_plus(camera_location, Vec3_mul(ray, t));
    Vec3_print(ret);
    return ret;
}

void RenderSystem3D_move_camera(int dir, bool moving) {
    if (dir < 0 || dir >= CAMERA_NUM_MOVES) {
        return;
    }
    camera_moving[dir] = moving;
}

