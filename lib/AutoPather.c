#include "AutoPather.h"

#include <stddef.h>
#include <stdlib.h>

#include <math.h>

#define DISTANCE_TOLERANCE 0.1

void AutoPather_init(AutoPather* a) {
    a->path.points = NULL;
    a->path.num_points = 0;
    a->next_point = 0;
}

static void straight_path(AutoPather* a, Vec2 start, Vec2 end) {
    (void)(start);
    a->path.points = malloc(sizeof(Vec2) * 1);
    a->path.num_points = 1;
    a->next_point = 0;

    a->path.points[0] = end;
}

void AutoPather_gen_path(AutoPather* a, Map* m, Vec2 start, Vec2 end) {
    (void)(m);
    straight_path(a, start, end);
    //the hard part
}

void AutoPather_update(AutoPather* a, Entity* e, float delta) {
    if (a->next_point >= a->path.num_points) {
        return;
    }

    Vec2 current_loc = Mat3_origin(e->transform);
    Vec2 target_loc = a->path.points[a->next_point];

    Vec2 diff = Vec2_minus(target_loc, current_loc);
    float diff_length = Vec2_length(diff);
    
    if (diff_length < DISTANCE_TOLERANCE) {
        e->transform = Mat3_with_origin(e->transform, target_loc);
        e->velocity = Vec2_zero();
        a->next_point += 1;
        return;
    }

    float distance_to_travel = e->speed * delta;
    if (distance_to_travel >= diff_length) {
        e->transform = Mat3_with_origin(e->transform, target_loc);
        e->velocity = Vec2_zero();
        a->next_point += 1;
        return;
    }

    Vec2 diff_direction = Vec2_mul(diff, 1.0f / diff_length);

    e->velocity = Vec2_mul(diff_direction, distance_to_travel);
    e->transform = Mat3_with_basis(e->transform, (Mat2) {
        diff_direction, Vec2_rotated(diff_direction, -M_PI / 2.0f)
    });
}
