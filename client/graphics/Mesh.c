#include "Mesh.h"
#include "Texture.h"

#include <glad/glad.h>
#include <math/Vec3.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void Mesh_init(Mesh* m) {
    glGenBuffers(1, &m->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m->vbo);

    glGenVertexArrays(1, &m->vao);
    glBindVertexArray(m->vao);

    Vector_init(&m->vertices, sizeof(Vertex));
}

int tokenize(char* string, char delim, char** tokens, int max_tokens) {
    int len = strlen(string);
    tokens[0] = string;
    int item_index = 1;
    for (int i = 0; i < len; i++) {
        if (string[i] == delim) {
            tokens[item_index] = string + i + 1;
            string[i] = '\0';

            item_index++;
            if (item_index == max_tokens) {
                break;
            }
        }
    }
    return item_index;
}

void Mesh_load(Mesh* m, const char* file_name, int texture_handle) {
    FILE* file = fopen(file_name, "r");
    if (!file) {
        printf("Error loading mesh: %s, file not found\n", file_name);
        return;
    }

    Mesh_init(m);
    m->texture_handle = texture_handle;

    Vector vertices;
    Vector_init(&vertices, sizeof(Vec3));
    Vector tex_coords;
    Vector_init(&tex_coords, sizeof(Vec2));

    char line[1024];
    while (fgets(line, 1024, file)) {
        int len = strlen(line);
        if (len <= 2) continue;
        line[len-1] = '\0';

        //extract each space-deliminated string from each line
        char* items[4];
        tokenize(line, ' ', items, 4);

        if (!strcmp(items[0], "v")) {
            float values[3];
            for (int i = 0; i < 3; i++) {
                values[i] = atof(items[i + 1]);
            }
            Vec3 v = (Vec3) {values[0], values[1], values[2]};
            Vector_push(&vertices, &v);
        }
        else if (!strcmp(items[0], "vt")) {
            float values[2];
            for (int i = 0; i < 2; i++) {
                values[i] = atof(items[i + 1]);
            }
            Vec2 v = (Vec2) {values[0], 1.0f - values[1]};
            Vector_push(&tex_coords, &v);
        }
        else if (!strcmp(items[0], "f")) {
            for (int i = 0; i < 3; i++) {
                char* tokens[2];
                int num_tokens = tokenize(items[i+1], '/', tokens, 2);
                if (num_tokens != 2) {
                    break;
                }

                int vert_index = atoi(tokens[0]) - 1;
                int tex_index = atoi(tokens[1]) - 1;

                Vec3* vert = Vector_get(&vertices, vert_index);
                Vec2* tex = Vector_get(&tex_coords, tex_index);

                //Vertex v = (Vertex) {*vert, Vec2_minus((Vec2) {0.0f, 0.0f}, *tex)};
                Vertex v = (Vertex) {*vert, *tex};
                Vector_push(&m->vertices, &v);
            }
        }

    }

    Vector_delete(&vertices);
    Vector_delete(&tex_coords);

    glBindBuffer(GL_ARRAY_BUFFER, m->vbo);
    glBufferData(GL_ARRAY_BUFFER, m->vertices.num_items * m->vertices._bytes_per_item, m->vertices.data, GL_STATIC_DRAW);

    glBindVertexArray(m->vao);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex) , (void*)0);
    glEnableVertexAttribArray(0);  

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex) , (void*)sizeof(Vec3));
    glEnableVertexAttribArray(1);  

    fclose(file);
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
    Texture_bind(m->texture_handle);
    glBindVertexArray(m->vao);
    glDrawArrays(GL_TRIANGLES, 0, 3 * m->vertices.num_items);
}


void Mesh_delete(Mesh* m) {
    Vector_delete(&m->vertices);
}
