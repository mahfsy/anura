#ifndef MAP_H
#define MAP_H

#include <math/Vec2.h>

typedef struct {
    int points[3];
    Vec2 normals[3];
    Vec2 center;
} Tri;

/*
typedef struct {
    Vec2 point;
    Vec2 normal;
} Plane;

struct BspStruct;
typedef struct BspStruct Bsp;
struct BspStruct {
    int tri_index;
    Plane plane;
    Bsp* front;
    Bsp* back;
};
*/

typedef struct {
    int neighbors[3];
} MapNode;

typedef struct {
    Vec2* vertices;
    unsigned int num_vertices;
    //Bsp* bsp;
    Tri* tris;
    unsigned int num_tris;
    unsigned int size_tris;

    MapNode* nodes;
} Map;

void Map_load(Map* m, const char* filename);
void Map_print(Map* m);
int Map_surrounding_triangle(const Map* m, Vec2 point);

void Map_delete(Map* m);

#endif
