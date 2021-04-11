#ifndef VEC2_H
#define VEC2_H

typedef struct {
    float x;
    float y;
} Vec2;

Vec2 Vec2_zero();

float Vec2_dot(Vec2 v, Vec2 w);
float Vec2_length(Vec2 v);
float Vec2_length_squared(Vec2 v);
float Vec2_get_index(Vec2* v, int i);
void  Vec2_set_index(Vec2* v, int i, float s);

Vec2 Vec2_normalized(Vec2 v);
Vec2 Vec2_rotated(Vec2 v, float theta);

Vec2 Vec2_plus(Vec2 v, Vec2 w);
Vec2 Vec2_minus(Vec2 v, Vec2 w);
Vec2 Vec2_mul(Vec2 v, float s);
Vec2 Vec2_div(Vec2 v, float s);

void Vec2_print(Vec2 v);

#endif
