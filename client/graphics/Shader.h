#ifndef SHADER_H 
#define SHADER_H 

#include <stdbool.h>

#include <math/Mat4.h>
#include <math/Vec3.h>

typedef struct {
    bool is_valid;
    unsigned int shader_type; //GL_FRAGMENT_SHADER or GL_VERTEX_SHADER
    unsigned int shader_handle;
} Shader;

typedef struct {
    bool is_valid;
    unsigned int program_handle;
} ShaderProgram;

Shader Shader_load(unsigned int shader_type, const char* file);
ShaderProgram Shaders_link(Shader* shaders, int num);

void Shader_uniform_Mat4(ShaderProgram* program, const char* name, Mat4* mat);

#endif
