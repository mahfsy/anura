#ifndef VEC3_H
#define VEC3_H

#include "Vec2.h"

typedef struct {
    float x;
    float y;
    float z;
} Vec3;

Vec3 Vec3_zero();
Vec3 Vec3_from_Vec2(Vec2 v, float f);

float Vec3_dot(Vec3 v, Vec3 w);
float Vec3_length(Vec3 v);
float Vec3_length_squared(Vec3 v);
float Vec3_get_index(Vec3* v, int i);
void  Vec3_set_index(Vec3* v, int i, float s);

Vec3 Vec3_normalized(Vec3 v);
//Vec3 Vec3_rotated(Vec3 v, float theta);

Vec3 Vec3_plus(Vec3 v, Vec3 w);
Vec3 Vec3_minus(Vec3 v, Vec3 w);
Vec3 Vec3_mul(Vec3 v, float s);
Vec3 Vec3_div(Vec3 v, float s);

void Vec3_print(Vec3 v);

#endif
