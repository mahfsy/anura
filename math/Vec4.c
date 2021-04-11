#include "Vec4.h"
#include <math.h>

#include <stdio.h>

Vec4 Vec4_zero() {
    return (Vec4) { 0.0f, 0.0f, 0.0f, 0.0f };
}

Vec4 Vec4_from_Vec3(Vec3 v, float f) {
    return (Vec4) {v.x, v.y, v.z, f };
}

float Vec4_dot(Vec4 v, Vec4 w) {
    return (v.x * w.x) + (v.y * w.y) + (v.z * w.z) + (v.w * w.w);
}

float Vec4_length(Vec4 v) {
    return sqrt(Vec4_length_squared(v));
}

float Vec4_length_squared(Vec4 v) {
    return Vec4_dot(v,v);
}

static float* _index_ptr(Vec4* v, int i) {
    switch (i) {
        case 0: return &v->x; break;
        case 1: return &v->y; break;
        case 2: return &v->z; break;
        case 3: return &v->w; break;
        default: return NULL; break;
    }
}

float Vec4_get_index(Vec4* v, int i) {
    float* p = _index_ptr(v, i);
    if (!p) {
        return (1.0f / 0.0f);
    }
    return *p;
}

void Vec4_set_index(Vec4* v, int i, float s) {
    float* p = _index_ptr(v, i);
    if (!p) {
        printf("SETTING INVALID INDEX OF VEC2\n");
        return;
    }
    *p = s;
}

Vec4 Vec4_normalized(Vec4 v) {
    return Vec4_mul(v, 1.0f / Vec4_length(v));
}

Vec4 Vec4_plus(Vec4 v, Vec4 w) {
    return (Vec4) {v.x + w.x, v.y + w.y, v.z + w.z, v.w + w.w};
}

Vec4 Vec4_minus(Vec4 v, Vec4 w) {
    return (Vec4) {v.x - w.x, v.y - w.y, v.z - w.z, v.w - w.w};
}

Vec4 Vec4_mul(Vec4 v, float s) {
    return (Vec4) {v.x * s, v.y * s, v.z * s, v.w * s};
}

Vec4 Vec4_div(Vec4 v, float s) {
    return (Vec4) {v.x / s, v.y / s, v.z / s, v.w / s};
}

void Vec4_print(Vec4 v) {
    printf("(%.2f, %.2f, %.2f, %.2f)\n", v.x, v.y, v.z, v.w);
}
