#include "Components.h"

#include "components/Transform.h"
#include "components/AutoPather.h"
#include "components/Velocity.h"

#include <stdio.h>

typedef struct {
    int (*new_func)();
    void* (*get_func)(int);
    void (*remove_func)(int);
} Component;

static const Component components[NUM_COMPONENTS]  = {
    //TRANSFORM,
    {
        Transform_new,
        Transform_get,
        Transform_remove,
    },
    //VELOCITY,
    {
        Velocity_new,
        Velocity_get,
        Velocity_remove,
    },
    //AUTO_PATHER,
    {
        AutoPather_new,
        AutoPather_get,
        AutoPather_remove,
    },
};

void* Component_get(ComponentType type, int index) {
    if (type >= NUM_COMPONENTS || type < 0) {
        printf("Error: invalid component id: %d\n", type);
        return NULL;
    }
    return components[type].get_func(index);
}

void Component_remove(ComponentType type, int index) {
    if (type >= NUM_COMPONENTS || type < 0) {
        printf("Error: invalid component id: %d\n", type);
        return;
    }
    return components[type].remove_func(index);
}

int Component_new(ComponentType type) {
    if (type >= NUM_COMPONENTS || type < 0) {
        printf("Error: invalid component id: %d\n", type);
        return -1;
    }
    return components[type].new_func();
}
