#ifndef TEXTURE_H
#define TEXTURE_H

int Texture_new(const char* file_name);
void Texture_bind(int index);
void Texture_remove(int index);

#endif
