#include <stdio.h>
#include <game/World.h>
#include <game/Entity.h>
#include <game/Components.h>
#include <game/components/Transform.h>
#include <game/components/Velocity.h>
#include <game/components/AutoPather.h>

int main() {
    EntityHandle handle = Entity_new();
    Entity_add_component(handle, TRANSFORM);
    Entity_add_component(handle, VELOCITY);
    Entity_add_component(handle, AUTO_PATHER);

    Transform* t = Entity_get_component(handle, TRANSFORM);
    Mat3_print(t->transform);

    Velocity* v = Entity_get_component(handle, VELOCITY);
    v->speed = 1.0;
    v->velocity = Vec2_normalized((Vec2) {1.0f, 1.0f} );

    World_init_systems();
    World_start();
    while (1) {
        World_update(0.000001);
        Mat3_print(t->transform);
    }
}
