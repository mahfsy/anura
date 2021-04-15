#ifndef CHAMPION_H
#define CHAMPION_H

enum ChampType {
    CHAMP_NULL,
    CHAMP_WIZARD,
    NUM_CHAMPS,
};

typedef struct {
    const char* name;
    int type;
} Champion;

void Champion_init(Champion* c, int champ_type);

int Champion_new();
void* Champion_get(int index);
void Champion_remove(int index);

#endif
