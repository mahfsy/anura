#include "World.h"

#include <stdbool.h>
#include <stdio.h>

#include <game/systems/VelocitySystem.h>
#include <game/systems/AutoPatherSystem.h>
#include <game/systems/AutoPatherSystem.h>

static Vector data;
static bool data_initialized = false;

static Vector systems;
static bool systems_initialized = false;

void World_init_systems() {
    World_register_system((System) {VelocitySystem_start, VelocitySystem_update});
    World_register_system((System) {AutoPatherSystem_start, AutoPatherSystem_update});
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
    Vector_set(&systems, index, &s);
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

void World_remove_data(int index) {
    Vector_remove(&data, index);
}
