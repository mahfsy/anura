#include "AbilityUser.h"

#include <stddef.h>
#include <utils/Vector.h>

static Vector users;
static int initialized = 0;

static const int ABILITY_MAXLEVELS[NUM_ABILITIES] = {
    5,
    5,
    5,
    3,
};

void AbilityUser_init(AbilityUser* c) {
    for (int i = 0; i < NUM_ABILITIES; i++) {
        Ability* a = &c->abilities[i];
        a->function = NULL;
        a->level = 0;
        a->max_levels = ABILITY_MAXLEVELS[i];
    }
}

int AbilityUser_new() {
    if (!initialized) {
        Vector_init(&users, sizeof(AbilityUser));
        initialized = 1;
    }

    int earliest = Vector_new_at_earliest(&users);
    AbilityUser* a = Vector_get(&users, earliest);
    AbilityUser_init(a);
    return earliest;
}

void* AbilityUser_get(int index) {
    return Vector_get(&users, index);
}

void AbilityUser_remove(int index) {
    Vector_remove(&users, index);
}
