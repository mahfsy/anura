#ifndef VEC4_H
#define VEC4_H

#include "Vec3.h"

typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vec4;

Vec4 Vec4_zero();
Vec4 Vec4_from_Vec3(Vec3 v, float f);

float Vec4_dot(Vec4 v, Vec4 w);
float Vec4_length(Vec4 v);
float Vec4_length_squared(Vec4 v);
float Vec4_get_index(Vec4* v, int i);
void  Vec4_set_index(Vec4* v, int i, float s);

Vec4 Vec4_normalized(Vec4 v);
//Vec4 Vec4_rotated(Vec4 v, float theta);

Vec4 Vec4_plus(Vec4 v, Vec4 w);
Vec4 Vec4_minus(Vec4 v, Vec4 w);
Vec4 Vec4_mul(Vec4 v, float s);
Vec4 Vec4_div(Vec4 v, float s);

void Vec4_print(Vec4 v);

#endif
