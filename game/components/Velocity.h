#ifndef VELOCITY_H
#define VELOCITY_H

#include <math/Vec2.h>

typedef struct {
    Vec2 velocity;
    float speed;
} Velocity;

int Velocity_new();
void* Velocity_get(int index);
void Velocity_remove(int index);

#endif
