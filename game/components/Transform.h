#ifndef TRANFORM_H 
#define TRANFORM_H 

#include <math/AnuraMath.h>

typedef struct {
    Mat3 transform;
} Transform;

int Transform_new();
void* Transform_get(int index);
void Transform_remove(int index);

#endif
