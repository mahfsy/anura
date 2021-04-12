#ifndef WORLD_H
#define WORLD_H

#include "Components.h"
#include <utils/Vector.h>

typedef struct {
    void (*start_func)();
    void (*update_func)(float delta);
} System;

void World_init_systems();
void World_register_system(System s);

void World_start();
void World_update(float delta);

int World_register_data(void* data);
void* World_get_data(int index);

#endif 
