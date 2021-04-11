#include "Player.h"

#include <stdio.h>

void Player_init(Player* p) {
    Entity_init(&p->entity);
    AutoPather_init(&p->auto_pather);
    p->name[0] = '\0';
    //snprintf(p->name, NAME_SIZE, "");
}

void Player_update(Player* p, float delta) {
    AutoPather_update(&p->auto_pather, &p->entity, delta);
    Entity_update(&p->entity, delta);
}
