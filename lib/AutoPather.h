#ifndef AUTOPATHER_H
#define AUTOPATHER_H

#include <math/Vec2.h>
#include "Map.h"
#include "Entity.h"

typedef struct {
    Vec2* points;
    unsigned int num_points;
} Path;

typedef struct {
    Path path;
    unsigned int next_point;
} AutoPather;

void AutoPather_init(AutoPather* a);
void AutoPather_gen_path(AutoPather* a, const Map* m, Vec2 start, Vec2 end);

void AutoPather_update(AutoPather* a, Entity* e, float delta);

#endif
