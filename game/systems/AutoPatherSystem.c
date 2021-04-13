#include "AutoPatherSystem.h"

#include <stdio.h>

#include <game/components/Velocity.h>
#include <game/components/Transform.h>
#include <game/components/AutoPather.h>
#include <game/Entity.h>
#include <game/Components.h>

void AutoPatherSystem_start() {
    return;
}

#define DISTANCE_TOLERANCE 0.1

void AutoPather_update(AutoPather* a, Transform* t, Velocity* v, float delta) {
    if (a->next_point >= a->path.num_points) {
        return;
    }

    Vec2 current_loc = Mat3_origin(t->transform);
    Vec2 target_loc = a->path.points[a->next_point];

    Vec2 diff = Vec2_minus(target_loc, current_loc);
    float diff_length = Vec2_length(diff);
    
    if (diff_length < DISTANCE_TOLERANCE) {
        t->transform = Mat3_with_origin(t->transform, target_loc);
        v->velocity = Vec2_zero();
        a->next_point += 1;
        return;
    }

    float distance_to_travel = v->speed * delta;
    if (distance_to_travel >= diff_length) {
        t->transform = Mat3_with_origin(t->transform, target_loc);
        v->velocity = Vec2_zero();
        a->next_point += 1;
        return;
    }

    Vec2 diff_direction = Vec2_mul(diff, 1.0f / diff_length);

    v->velocity = Vec2_mul(diff_direction, distance_to_travel / delta);
    t->transform = Mat3_with_basis(t->transform, (Mat2) {
        diff_direction, Vec2_rotated(diff_direction, -M_PI / 2.0f)
    });
}

void AutoPatherSystem_update(float delta) {
    EntityQueryHandle query_handle = Entity_query(3, TRANSFORM, VELOCITY, AUTO_PATHER);
    EntityQuery* query = Entity_get_query(query_handle);

    for (int i = 0; i < query->num; i++) {
        Transform* t = Entity_get_component(query->handles[i], TRANSFORM);
        Velocity* v = Entity_get_component(query->handles[i], VELOCITY);
        AutoPather* a = Entity_get_component(query->handles[i], AUTO_PATHER);
        AutoPather_update(a, t, v, delta);
    }

    Entity_return_query(query_handle);
}
