#ifndef ABILITYUSER_H
#define ABILITYUSER_H

enum Abilities {
    ABILITY_Q,
    ABILITY_W,
    ABILITY_E,
    ABILITY_R,
    NUM_ABILITIES,
};

typedef struct {
    float base_cooldowns[5];
    int level;
    int max_levels;
    void (*function)();
} Ability;

typedef struct {
    Ability abilities[NUM_ABILITIES];
    int buffered_ability;
} AbilityUser;

int AbilityUser_new();
void* AbilityUser_get(int index);
void AbilityUser_remove(int index);

#endif
