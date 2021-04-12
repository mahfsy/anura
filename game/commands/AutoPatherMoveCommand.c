#include "AutoPatherMoveCommand.h"

#include <math/Vec2.h>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <utils/Vector.h>

static void straight_path(AutoPather* a, Vec2 start, Vec2 end) {
    (void)(start);
    if (!a->path.points) {
        a->path.points = malloc(sizeof(Vec2) * 1);
    }
    a->path.num_points = 1;
    a->next_point = 0;

    a->path.points[0] = end;
}

/*
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
            //reconstruct path TODO
            
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
*/

static Vector commands;
static bool commands_initialized = false;

void AutoPatherMoveCommand_issue(int index) {
    AutoPatherMoveCommand* command = Vector_get(&commands, index);
    if (!command) {
        return;
    }
    printf("issuing autoPatherMoveCommand\n");
    AutoPather* a = AutoPather_get(command->auto_pather_index);

    //get rid of the old path
    straight_path(a, command->start, command->end);
    Vector_remove(&commands, index);
}

void* AutoPatherMoveCommand_get(int index) {
    return Vector_get(&commands, index);
}

int AutoPatherMoveCommand_new() {
    if (!commands_initialized) {
        Vector_init(&commands, sizeof(AutoPatherMoveCommand));
        commands_initialized = true;
    }
    int index = Vector_new_at_earliest(&commands);
    return index;
}
