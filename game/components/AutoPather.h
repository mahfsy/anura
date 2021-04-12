#ifndef AUTOPATHER_H
#define AUTOPATHER_H

#include <math/Vec2.h>
#include <game/Map.h>

typedef struct {
    Vec2* points;
    unsigned int num_points;
} Path;

typedef struct {
    Path path;
    unsigned int next_point;
} AutoPather;


int AutoPather_new();
void* AutoPather_get(int index);
void AutoPather_remove(int index);

//void AutoPather_gen_path(AutoPather* a, const Map* m, Vec2 start, Vec2 end);

//void AutoPather_update(AutoPather* a, Velocity* e, float delta);

#endif
