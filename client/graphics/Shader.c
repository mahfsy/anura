#include "Shader.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <glad/glad.h>

Shader Shader_load(unsigned int shader_type, const char* file_name) {
    Shader ret;
    ret.is_valid = true;
    ret.shader_type = shader_type;

    FILE* file = fopen(file_name, "r");
    if (!file) {
        printf("Error opening shader file: %s\n",  file_name);
        ret.is_valid = false;
        return ret;
    }

    static const int MALLOC_SIZE = 1024;
    int buffer_len = 0;
    int buffer_size = MALLOC_SIZE;
    char* buffer = malloc(buffer_size * sizeof(char));

    char line[1024];
    while (fgets(line, 1024, file)) {
        int len = strlen(line);
        if (len >= 1023) {
            printf("Warning: shader %s contains a line longer than 1023 characters.\n", file_name);
            printf("\tThe internal code of this program does not allow that.\n");
        }

        //the +1 is insurance for when we insert \0 after this loop
        if (buffer_len + len + 1 >= buffer_size) {
            buffer_size *= 2;
            buffer = realloc(buffer, buffer_size);
        }

        strncpy(buffer + buffer_len, line, len);
        buffer_len += len;
    }
    buffer[buffer_len] = '\0';

    ret.shader_handle = glCreateShader(ret.shader_type);
    glShaderSource(ret.shader_handle, 1, (const char**) &buffer, NULL);
    glCompileShader(ret.shader_handle);

    free(buffer);

    {
        int  success;
        glGetShaderiv(ret.shader_handle, GL_COMPILE_STATUS, &success);
        if(!success) {
            char infoLog[512];
            glGetShaderInfoLog(ret.shader_handle, 512, NULL, infoLog);
            printf("ERROR: SHADER COMPILATION FAILED for %s\n%s\n", file_name, infoLog);
            ret.is_valid = false;
            return ret;
        }
    }

    return ret;
}

ShaderProgram Shaders_link(Shader* shaders, int num) {
    ShaderProgram ret;
    ret.is_valid = true;
    ret.program_handle = glCreateProgram();
    for (int i = 0; i < num; i++) {
        glAttachShader(ret.program_handle, shaders[i].shader_handle);
    }
    glLinkProgram(ret.program_handle);

    {
        int  success;
        glGetProgramiv(ret.program_handle, GL_LINK_STATUS, &success);
        if(!success) {
            char infoLog[512];
            glGetProgramInfoLog(ret.program_handle, 512, NULL, infoLog);
            printf("ERROR::SHADER::LINKING_FAILED\n%s\n", infoLog);
            ret.is_valid = false;
            return ret;
        }
    }

    return ret;
}

void Shader_uniform_matrix_4fv(ShaderProgram* program, const char* name, Mat4* mat) {
    unsigned int location = glGetUniformLocation(program->program_handle, name);
    glUniformMatrix4fv(location, 1, GL_FALSE, (float*) mat);
}
