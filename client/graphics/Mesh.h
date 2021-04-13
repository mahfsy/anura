#ifndef MESH_H
#define MESH_H

#include <math/Vec3.h>
#include <utils/Vector.h>
#include "Shader.h"

typedef struct {
    unsigned int vbo;
    unsigned int vao;

    Vector vertices;
    Vector faces;
} Mesh;

void Mesh_load(Mesh* m, const char* file_name);
void Mesh_init_test_triangle(Mesh* m);
void Mesh_draw(Mesh* m, const ShaderProgram* program);
void Mesh_delete(Mesh* m);

#endif
