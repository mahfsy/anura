#ifndef MAP_H
#define MAP_H

#include <math/Vec2.h>

typedef struct {
    Vec2 points[3];
    Vec2 normals[3];
} Tri;

typedef struct {
    Tri* tris;
    unsigned int num_tris;
    unsigned int size_tris;
} Map;

void Map_load(Map* m, const char* filename);
void Map_print(Map* m);

void Map_delete(Map* m);

#endif
