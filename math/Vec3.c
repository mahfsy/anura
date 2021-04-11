#include "Vec3.h"
#include <math.h>

#include <stdio.h>

Vec3 Vec3_zero() {
    return (Vec3) { 0.0f, 0.0f, 0.0f };
}

Vec3 Vec3_from_Vec2(Vec2 v, float f) {
    return (Vec3) {v.x, v.y, f };
}

float Vec3_dot(Vec3 v, Vec3 w) {
    return (v.x * w.x) + (v.y * w.y) + (v.z * w.z);
}

float Vec3_length(Vec3 v) {
    return sqrt(Vec3_length_squared(v));
}

float Vec3_length_squared(Vec3 v) {
    return Vec3_dot(v,v);
}

static float* _index_ptr(Vec3* v, int i) {
    switch (i) {
        case 0: return &v->x; break;
        case 1: return &v->y; break;
        case 2: return &v->z; break;
        default: return NULL; break;
    }
}

float Vec3_get_index(Vec3* v, int i) {
    float* p = _index_ptr(v, i);
    if (!p) {
        return (1.0f / 0.0f);
    }
    return *p;
}

void Vec3_set_index(Vec3* v, int i, float s) {
    float* p = _index_ptr(v, i);
    if (!p) {
        printf("SETTING INVALID INDEX OF VEC2\n");
        return;
    }
    *p = s;
}

Vec3 Vec3_normalized(Vec3 v) {
    return Vec3_mul(v, 1.0f / Vec3_length(v));
}

Vec3 Vec3_plus(Vec3 v, Vec3 w) {
    return (Vec3) {v.x + w.x, v.y + w.y, v.z + w.z};
}

Vec3 Vec3_minus(Vec3 v, Vec3 w) {
    return (Vec3) {v.x - w.x, v.y - w.y, v.z - w.z };
}

Vec3 Vec3_mul(Vec3 v, float s) {
    return (Vec3) {v.x * s, v.y * s, v.z * s};
}

Vec3 Vec3_div(Vec3 v, float s) {
    return (Vec3) {v.x / s, v.y / s, v.z / s};
}

void Vec3_print(Vec3 v) {
    printf("(%.2f, %.2f, %.2f)\n", v.x, v.y, v.z);
}
