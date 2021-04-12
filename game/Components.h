#ifndef COMPONENTS_H
#define COMPONENTS_H

typedef enum {
    TRANSFORM,
    VELOCITY,
    AUTO_PATHER,
    NUM_COMPONENTS,
} ComponentType;

void* Component_get(ComponentType type, int index);
void Component_remove(ComponentType type, int index);
int Component_new(ComponentType type);

#endif
