#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>

typedef struct {
    void* data;
    bool* index_is_used; 
    unsigned int num_items;
    unsigned int total_items_allocated;

    //these would be private in c++, don't mess with them after initialization
    unsigned int _bytes_per_item;
    unsigned int _earliest_open_slot;
} Vector;

void Vector_init(Vector* v, unsigned int bytes_per_item);
void Vector_resize(Vector* v, unsigned int new_total_items);
void Vector_use_all(Vector* v);

//use it like an array if u please
void* Vector_get(Vector* v, unsigned int index);
void  Vector_set(Vector* v, unsigned int index, void* data);

//it will keep track of elements that are valid/invalid in the array
void Vector_remove(Vector* v, unsigned int index);
bool Vector_index_is_used(Vector* v, unsigned int index);
unsigned int Vector_new_at_earliest(Vector* v);
unsigned int Vector_insert_at_earliest(Vector* v, void* data);

//make it act like a stack if you want
void Vector_push(Vector* v, void* new_item);
void* Vector_top(Vector* v);
void* Vector_pop(Vector* v);

//cleanup, frees all data allocated by Vector_ functions
void Vector_delete(Vector* v);

#endif
