#include "Entity.h"

void Entity_init(Entity* e) {
    e->transform = Mat3_identity();
    e->velocity = Vec2_zero();
    e->speed = 1.0f;
}

void Entity_update(Entity* e, float delta) {
    e->transform = Mat3_translated(e->transform, Vec2_mul(e->velocity, delta));
}
