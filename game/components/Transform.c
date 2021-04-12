#include "Transform.h"
#include <utils/Vector.h>

static Vector transforms;
static int initialized = 0;

int Transform_new() {
    if (!initialized) {
        Vector_init(&transforms, sizeof(Transform));
        initialized = 1;
    }

    int earliest = Vector_new_at_earliest(&transforms);
    Transform* t = Vector_get(&transforms, earliest);
    t->transform = Mat3_identity();
    return earliest;
}

void* Transform_get(int index) {
    return Vector_get(&transforms, index);
}

void Transform_remove(int index) {
    Vector_remove(&transforms, index);
}
