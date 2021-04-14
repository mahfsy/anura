#include "Texture.h"

#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>

#include <glad/glad.h>

#include <utils/Vector.h>

static Vector vector;
static int initialized = 0;

typedef struct {
    unsigned int handle;
} Texture;

int Texture_new(const char* file_name) {
    if (!initialized) {
        Vector_init(&vector, sizeof(Texture));
        initialized = 1;

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }

    int earliest = Vector_new_at_earliest(&vector);
    Texture* t = Vector_get(&vector, earliest);

    SDL_Surface* image = IMG_Load(file_name);
    if (!image) {
        Texture_remove(earliest);
        return -1;
    }

    glGenTextures(1, &t->handle);  
    
    glBindTexture(GL_TEXTURE_2D, t->handle);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
    glGenerateMipmap(GL_TEXTURE_2D);

    SDL_FreeSurface(image);
    return earliest;
}

void Texture_bind(int index) {
    Texture* t = Vector_get(&vector, index);
    if (!t) return;
    glBindTexture(GL_TEXTURE_2D, t->handle);
}

void Texture_remove(int index) {
    Texture* t = Vector_get(&vector, index); 
    if (!t) return;

    Vector_remove(&vector, index);
    if (vector.num_items == 0) {
        IMG_Quit();
    }
}
