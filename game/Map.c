#include "Map.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <math/AnuraMath.h>

//static void construct_bsp(Map* m);

static void Map_construct_graph(Map* m);

//load the navmesh from a .obj file; 
//in blender ONLY check triangulate faces on export
//this ignores the y coordinate of all triangles since we are in 2d
void Map_load(Map* m, const char* filename) {
    const unsigned int TRIS_SIZE = 512;
    m->size_tris = TRIS_SIZE;
    m->num_tris = 0;
    m->tris = malloc(sizeof(Tri) * m->size_tris);

    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error loading file: %s\n", filename);
    }

    const unsigned int LINE_LENGTH = 1024;
    char line[LINE_LENGTH];

    const unsigned int VERTICES_SIZE = 512;
    m->vertices = malloc(sizeof(Vec2) * VERTICES_SIZE);
    m->num_vertices = 0;
    unsigned int size_vertices = VERTICES_SIZE;

    while (fgets(line, LINE_LENGTH, file)) {
        if (*line == '#') {
            continue;
        }
        line[strlen(line) - 1] = '\0';

        //get tokens
        char* tokens[4];
        tokens[0] = line;
        int tok_index = 1;
        for (char* c = line; *c; c++) {
            if (*c == ' ') {
                *c = '\0';
                tokens[tok_index] = c + 1;
                tok_index++;
                if (tok_index == 4) {
                    break;
                }
            }
        }

        //add a vertex
        if (*line == 'v') {
            float x = atof(tokens[1]);
            float y = atof(tokens[3]);
            if (m->num_vertices == size_vertices) {
                size_vertices *= 2;
                m->vertices = realloc(m->vertices, sizeof(Vec2) * size_vertices);
            }
            m->vertices[m->num_vertices] = (Vec2) { x, y };
            m->num_vertices++;
        }
        //construct a new tri
        else if (*line == 'f') {
            if (m->num_tris == m->size_tris) {
                m->size_tris *= 2;
                m->tris = realloc(m->tris, sizeof(Tri) * m->size_tris);
            }
            Tri* tri = &m->tris[m->num_tris];
            for (int i = 0; i < 3; i++) {
                unsigned int index = atoi(tokens[i + 1]) - 1;
                if (index >= m->num_vertices) {
                    printf("Error loading map: %s; Vertex index %d out of bounds\n", filename, index);
                }
                tri->points[i] = index;
            }
            Vec2 center_of_mass = Vec2_zero();
            for (int i = 0; i < 3; i++) {
                center_of_mass = Vec2_plus(center_of_mass, m->vertices[tri->points[i]]);
            }
            center_of_mass = Vec2_div(center_of_mass, 3.0f);
            tri->center = center_of_mass;

            //calculate normals for this tri
            for (int i = 0; i < 3; i++) {
                Vec2 point_to_center = Vec2_minus(center_of_mass, m->vertices[tri->points[i]]);
                tri->normals[i] = 
                    Vec2_rotated(
                        Vec2_minus(
                            m->vertices[tri->points[i]], 
                            m->vertices[tri->points[(i + 1) % 3]]), 
                        M_PI_2);
                if (Vec2_dot(tri->normals[i], point_to_center) < 0) {
                    tri->normals[i] = Vec2_mul(tri->normals[i], -1.0f);
                }
                tri->normals[i] = Vec2_normalized(tri->normals[i]);
            }
            m->num_tris++;
        }
    }
    fclose(file);

    //construct the graph we will use for the A* algorithm
    Map_construct_graph(m);
}

static int triangles_share_edge(Tri* a, Tri* b) {
    int shared_points = 0;
    int the_points[2] = {-1, -1};
    for (int a_point = 0; a_point < 3; a_point++) {
        for (int b_point = 0; b_point < 3; b_point++) {
            if (a->points[a_point] == b->points[b_point]) {
                the_points[shared_points] = a_point;
                shared_points++;
                break;
            }
        }
    }
    //we return a specific index depending on WHICH edge it is sharing
    if (the_points[0] == 0 && the_points[1] == 1) {
        return 0;
    }
    else if (the_points[0] == 1 && the_points[1] == 2) {
        return 1;
    }
    else if (the_points[0] == 0 && the_points[1] == 2) {
        return 2;
    }
    else {
        return -1;
    }
}

static void Map_construct_graph(Map* m) {
    m->nodes = malloc(sizeof(MapNode) * m->num_tris);
    for (unsigned int i = 0; i < m->num_tris; i++) {
        for (int n = 0; n < 3; n++) {
            m->nodes[i].neighbors[n] = -1;
        }
        for (unsigned int j = 0; j < m->num_tris; j++) {
            if (i == j) continue;
            //this shared_edge is the index of the edge so we can match it up
            //later in the traversal of the graph
            int shared_edge = triangles_share_edge(&m->tris[i], &m->tris[j]);
            if (shared_edge >= 0) {
                m->nodes[i].neighbors[shared_edge] = j;
            }
        }
    }
}

/*
static void Bsp_helper(Bsp* root, Map* m, Tri* left, int num_left, Tri* right, int num_right) {
    
}

static void construct_bsp(Map* m) {
    m->bsp = malloc(sizeof(Bsp));
    m->bsp->tri_index = m->num_tris / 2;
    m->bsp->plane = (Plane) { m->tris[m->bsp->tri_index].points[0], m->tris[m->bsp->tri_index].normals[0] };
    m->bsp->front = NULL;
    m->bsp->back = NULL;



    Bsp_helper(m->bsp, 
}
*/

int point_is_inside_triangle(const Map* m, const Tri* t, Vec2 point) {
    for (unsigned int i = 0; i < 3; i++) {
        Vec2 point_to_vertex = Vec2_minus(point, m->vertices[t->points[i]]);
        if (Vec2_dot(point_to_vertex, t->normals[i]) < 0) {
            return 0;
        }
    }
    return 1;
}

int Map_surrounding_triangle(const Map* m, Vec2 point) {
    for (unsigned int i = 0; i < m->num_tris; i++) {
        if (point_is_inside_triangle(m, &m->tris[i], point)) {
            return i;
        }
    }
    return -1;
}

void Map_delete(Map* m) {
    free(m->vertices);
    m->num_vertices = 0;

    free(m->tris);
    m->size_tris = 0;
    m->num_tris = 0;

    free(m->nodes);
}

void Map_print(Map* m) {
    for (unsigned int i = 0; i < m->num_tris; i++) {
        printf("..\n");
        for (int j = 0; j < 3; j++) {
            printf("  ");
            Vec2_print(m->vertices[m->tris[i].points[j]]);
            Vec2_print(m->tris[i].normals[j]);
        }
    }
}

