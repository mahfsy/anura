#ifndef ENTITY_H
#define ENTITY_H

#include "Components.h"

typedef struct {
    int index;
    int generation;
} EntityHandle;

typedef struct {
    int index;
    int generation;
} EntityQueryHandle;

typedef struct {
    EntityHandle* handles;
    int num;

    //private
    int _total_handles_allocated;
    int _generation;
} EntityQuery;

EntityHandle Entity_new();
void Entity_delete(EntityHandle handle);

void Entity_add_component(EntityHandle handle, ComponentType type);
void Entity_remove_component(EntityHandle handle, ComponentType type);

void* Entity_get_component(EntityHandle handle, ComponentType type);

EntityQueryHandle Entity_query(int num, ...); 
EntityQuery* Entity_get_query(EntityQueryHandle handle);
void Entity_return_query(EntityQueryHandle handle);

#endif
