#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "AutoPather.h"

#define NAME_SIZE 128

typedef struct {
    char name[NAME_SIZE];
    Entity entity;
    AutoPather auto_pather;
} Player;

void Player_init(Player* p);

void Player_update(Player* p, float delta);

#endif
