#include "Map.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <math/AnuraMath.h>

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
    Vec2* vertices = malloc(sizeof(Vec2) * VERTICES_SIZE);
    unsigned int num_vertices = 0;
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
            if (num_vertices == size_vertices) {
                size_vertices *= 2;
                vertices = realloc(vertices, sizeof(Vec2) * size_vertices);
            }
            vertices[num_vertices] = (Vec2) { x, y };
            num_vertices++;
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
                if (index >= num_vertices) {
                    printf("Error loading map: %s; Vertex index %d out of bounds\n", filename, index);
                }
                tri->points[i] = vertices[index];
            }
            Vec2 center_of_mass = Vec2_zero();
            for (int i = 0; i < 3; i++) {
                center_of_mass = Vec2_plus(center_of_mass, tri->points[i]);
            }
            center_of_mass = Vec2_div(center_of_mass, 3.0f);
            //calculate normals
            for (int i = 0; i < 3; i++) {
                Vec2 point_to_center = Vec2_minus(center_of_mass, tri->points[i]);
                tri->normals[i] = Vec2_rotated(Vec2_minus(tri->points[i], tri->points[(i + 1) % 3]), M_PI_2);
                if (Vec2_dot(tri->normals[i], point_to_center) < 0) {
                    tri->normals[i] = Vec2_mul(tri->normals[i], -1.0f);
                }
                tri->normals[i] = Vec2_normalized(tri->normals[i]);
            }
            m->num_tris++;
        }
    }
    free(vertices);

    fclose(file);
}

void Map_print(Map* m) {
    for (unsigned int i = 0; i < m->num_tris; i++) {
        printf("..\n");
        for (int j = 0; j < 3; j++) {
            printf("  ");
            Vec2_print(m->tris[i].points[j]);
            Vec2_print(m->tris[i].normals[j]);
        }
    }
}

void Map_delete(Map* m) {
    free(m->tris);
    m->size_tris = 0;
    m->num_tris = 0;
}
