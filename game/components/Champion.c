#include "Champion.h"

#include <utils/Vector.h>

static Vector champs;
static int initialized = 0;

static const char* names[NUM_CHAMPS] = {
    "Null",
    "Wizard",
};

void Champion_init(Champion* c, int champ_type) {
    if (champ_type < 0 || champ_type >= NUM_CHAMPS) {
        c->type = CHAMP_NULL;
    }
    else {
        c->type = champ_type;
    }
    c->name = names[c->type];
}

int Champion_new() {
    if (!initialized) {
        Vector_init(&champs, sizeof(Champion));
        initialized = 1;
    }
    int earliest = Vector_new_at_earliest(&champs);
    Champion* c = Vector_get(&champs, earliest);
    Champion_init(c, CHAMP_NULL);
    return earliest;
}

void* Champion_get(int index) {
    return Vector_get(&champs, index);
}

void Champion_remove(int index) {
    Vector_remove(&champs, index);
}
