#include "AutoPather.h"

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#include <utils/Vector.h>

static Vector auto_pathers;
static int initialized = 0;

void AutoPather_init(AutoPather* a) {
    a->path.points = NULL;
    a->path.num_points = 0;
    a->next_point = 0;
}

int AutoPather_new() {
    if (!initialized) {
        Vector_init(&auto_pathers, sizeof(AutoPather));
        initialized = 1;
    }

    int earliest = Vector_new_at_earliest(&auto_pathers);
    AutoPather* a = Vector_get(&auto_pathers, earliest);
    AutoPather_init(a);
    return earliest;
}

void* AutoPather_get(int index) {
    return Vector_get(&auto_pathers, index);
}

void AutoPather_remove(int index) {
    Vector_remove(&auto_pathers, index);
}

/*
static void straight_path(AutoPather* a, Vec2 start, Vec2 end) {
    (void)(start);
    a->path.points = malloc(sizeof(Vec2) * 1);
    a->path.num_points = 1;
    a->next_point = 0;

    a->path.points[0] = end;
}

void AutoPather_gen_path(AutoPather* a, const Map* m, Vec2 start_loc, Vec2 end_loc) {
    //straight_path(a, start_loc, end_loc);
    
    int start = Map_surrounding_triangle(m, start_loc);
    int end = Map_surrounding_triangle(m, end_loc);

    if (start == -1 || end == -1) {
        printf("ERROR, bad path!\n");
        return;
    }

    int* open = malloc(sizeof(int) * m->num_tris);
    for(unsigned int i = 0; i < m->num_tris; i++) {
        open[i] = 0;
    }
    open[start] = 1;
    int num_open = 1;

    int* came_from = malloc(sizeof(int) * m->num_tris);
    for (unsigned int i = 0; i < m->num_tris; i++) {
        came_from[i] = -1;
    }

    float* f_score = malloc(sizeof(float) * m->num_tris);
    for (unsigned int i = 0; i < m->num_tris; i++) {
        f_score[i] = INFINITY;
    }
    f_score[start] = 0;

    float* g_score = malloc(sizeof(float) * m->num_tris);
    for (unsigned int i = 0; i < m->num_tris; i++) {
        g_score[i] = INFINITY;
    }
    g_score[start] = Vec2_length(Vec2_minus(end_loc, start_loc));

    while(num_open > 0) {
        int current = -1;
        for (unsigned int i = 0; i < m->num_tris; i++) {
            if (!open[i]) continue;

            if (current < 0) {
                current = i;
            }
            else if (f_score[i] < f_score[current]) {
                current = i;
            }
        }

        if (current == end) {
            while (came_from[current] > 0) {
                printf("%d\n", current);
                current = came_from[current];
            }
            //reconstruct path
            break;
        }

        open[current] = 0;
        for (int n = 0; n < 3; n++) {
            int neighbor = m->nodes[current].neighbors[n];
            if (neighbor < 0) continue;

            float tentative_g_score = g_score[current] + Vec2_length(Vec2_minus(m->tris[current].center, m->tris[neighbor].center));
            if (tentative_g_score < g_score[neighbor]) {
                came_from[neighbor] = current;
                g_score[neighbor] = tentative_g_score;
                f_score[neighbor] = tentative_g_score + Vec2_length(Vec2_minus(end_loc, m->tris[neighbor].center));
                    
                open[neighbor] = 1;
            }
        }
    }

    free(open);
    free(came_from);
    free(f_score);
    free(g_score);
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
*/
