#include "Mesh.h"

#include <glad/glad.h>

void Mesh_init(Mesh* m) {
    glGenBuffers(1, &m->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m->vbo);

    glGenVertexArrays(1, &m->vao);
    glBindVertexArray(m->vao);
}

void Mesh_load(Mesh* m, const char* file_name) {
    Mesh_init(m);
}

static const float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};  

void Mesh_init_test_triangle(Mesh* m) {
    Mesh_init(m);

    glBindBuffer(GL_ARRAY_BUFFER, m->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);  
}

void Mesh_draw(Mesh* m, const ShaderProgram* program) {
    glUseProgram(program->program_handle);
    glBindVertexArray(m->vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Mesh_delete(Mesh* m) {
    
}
