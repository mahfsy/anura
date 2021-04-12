#include "AutoPather.h"

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#include <math.h>

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


