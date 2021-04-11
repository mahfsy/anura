#include "Vec2.h"
#include "Mat2.h"
#include <math.h>

#include <stdio.h>

Vec2 Vec2_zero() {
    return (Vec2) { 0.0f, 0.0f };
}

float Vec2_dot(Vec2 v, Vec2 w) {
    return (v.x * w.x) + (v.y * w.y);
}

float Vec2_length(Vec2 v) {
    return sqrt(Vec2_length_squared(v));
}

float Vec2_length_squared(Vec2 v) {
    return Vec2_dot(v,v);
}

static float* _index_ptr(Vec2* v, int i) {
    switch (i) {
        case 0: return &v->x; break;
        case 1: return &v->y; break;
        default: return NULL; break;
    }
}

float Vec2_get_index(Vec2* v, int i) {
    float* p = _index_ptr(v, i);
    if (!p) {
        return (1.0f / 0.0f);
    }
    return *p;
}

void Vec2_set_index(Vec2* v, int i, float s) {
    float* p = _index_ptr(v, i);
    if (!p) {
        printf("SETTING INVALID INDEX OF VEC2\n");
        return;
    }
    *p = s;
}

Vec2 Vec2_normalized(Vec2 v) {
    return Vec2_mul(v, 1.0f / Vec2_length(v));
}

Vec2 Vec2_rotated(Vec2 v, float theta) {
    Mat2 rotation = Mat2_rotation(theta);
    return Mat2_apply(rotation, v);
}

Vec2 Vec2_plus(Vec2 v, Vec2 w) {
    return (Vec2) {v.x + w.x, v.y + w.y};
}

Vec2 Vec2_minus(Vec2 v, Vec2 w) {
    return (Vec2) {v.x - w.x, v.y - w.y};
}

Vec2 Vec2_mul(Vec2 v, float s) {
    return (Vec2) {v.x * s, v.y * s};
}

Vec2 Vec2_div(Vec2 v, float s) {
    return (Vec2) {v.x / s, v.y / s};
}

void Vec2_print(Vec2 v) {
    printf("(%.2f, %.2f)\n", v.x, v.y);
}
