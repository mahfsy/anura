#include "World.h"

#include <stdbool.h>
#include <stdio.h>

#include <game/systems/VelocitySystem.h>

static Vector data;
static bool data_initialized = false;

static Vector systems;
static bool systems_initialized = false;

void World_init_systems() {
    World_register_system((System) {VelocitySystem_start, VelocitySystem_update});
}

void World_start() {
    for (unsigned int i = 0; i < systems.num_items; i++) {
        System* s = Vector_get(&systems, i);
        s->start_func();
    }
}

void World_update(float delta) {
    for (unsigned int i = 0; i < systems.num_items; i++) {
        System* s = Vector_get(&systems, i);
        s->update_func(delta);
    }
}

void World_register_system(System s) {
    if (!systems_initialized) {
        Vector_init(&systems, sizeof(System));
        systems_initialized = true;
    }
    //check if system is already there?
    
    int index = Vector_new_at_earliest(&systems);
    printf("%p, %p\n", s.start_func, s.update_func);
    Vector_set(&systems, index, &s);
    printf("registered: %d\n", systems.num_items);
}

int World_register_data(void* item) {
    if (!data_initialized) {
        Vector_init(&data, sizeof(void*));
        data_initialized = true;
    }
    int index = Vector_new_at_earliest(&data);
    Vector_set(&data, index, &item);
    return index;
}

void* World_get_data(int index) {
    return Vector_get(&data, index);
}
