#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <client/graphics/Window.h>
#include <math/Vec3.h>

#include <stdbool.h>

enum CameraMoving {
    CAMERA_MOVE_LEFT,
    CAMERA_MOVE_RIGHT,
    CAMERA_MOVE_UP,
    CAMERA_MOVE_DOWN,
    CAMERA_NUM_MOVES,
};

void RenderSystem3D_init(Window* the_window);

void RenderSystem3D_start();
void RenderSystem3D_update(float delta);

Vec3 RenderSystem3D_screen_coords_raycast_to_floor(float x, float y);
void RenderSystem3D_move_camera(int dir, bool moving);

#endif
