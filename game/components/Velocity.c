#include "Velocity.h"

#include <utils/Vector.h>

static Vector vector;
static int initialized = 0;

int Velocity_new() {
    if (!initialized) {
        Vector_init(&vector, sizeof(Velocity));
        initialized = 1;
    }

    int earliest = Vector_new_at_earliest(&vector);
    Velocity* v = Vector_get(&vector, earliest);
    v->velocity = Vec2_zero();
    v->speed = 0.0f;

    return earliest;
}

void* Velocity_get(int index) {
    return Vector_get(&vector, index);
}

void Velocity_remove(int index) {
    Vector_remove(&vector, index);
}
