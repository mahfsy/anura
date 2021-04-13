#include "VelocitySystem.h" 

#include <stdio.h>

#include <game/components/Velocity.h>
#include <game/components/Transform.h>
#include <game/Entity.h>
#include <game/Components.h>

void VelocitySystem_start() {
    return;
}

void VelocitySystem_update(float delta) {
    EntityQueryHandle query_handle = Entity_query(2, TRANSFORM, VELOCITY);
    EntityQuery* query = Entity_get_query(query_handle);

    for (int i = 0; i < query->num; i++) {
        Transform* t = Entity_get_component(query->handles[i], TRANSFORM);
        Velocity* v = Entity_get_component(query->handles[i], VELOCITY);

        t->transform = Mat3_translated(t->transform, Vec2_mul(v->velocity, delta));
    }

    Entity_return_query(query_handle);
}
