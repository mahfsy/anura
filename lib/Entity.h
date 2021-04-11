#ifndef ENTITY_H 
#define ENTITY_H 

#include "../math/AnuraMath.h"

typedef struct {
    Mat3 transform;
    Vec2 velocity;
    float speed;
} Entity;

void Entity_init(Entity* e);
void Entity_update(Entity* e, float delta);

#endif
