#include "Entity.h"

#include <utils/Vector.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>

static Vector entities;
static bool initialized = false;

typedef struct {
    int components[NUM_COMPONENTS];
    int generation;
} Entity;

EntityHandle Entity_new() {
    if (!initialized) {
        Vector_init(&entities, sizeof(Entity));
    }
    int idx = Vector_new_at_earliest(&entities);
    Entity* e = Vector_get(&entities, idx);

    for(int i = 0; i < NUM_COMPONENTS; i++) {
        e->components[i] = -1;
    }
    e->generation++;
    return (EntityHandle) { idx, e->generation };
}

Entity* dereference_handle(EntityHandle handle) {
    Entity *e = Vector_get(&entities, handle.index);
    if (!e) return NULL;
    if (e->generation != handle.generation) { return NULL; }
    return e;
}

void Entity_delete(EntityHandle handle) {
    Entity *e = dereference_handle(handle);
    if (!e) return;

    for (int i = 0; i < NUM_COMPONENTS; i++) {
        if (e->components[i] >= 0) {
            Component_remove(i, e->components[i]);
            e->components[i] = -1;
        }
    }
    Vector_remove(&entities, handle.index);
}

void Entity_add_component(EntityHandle handle, ComponentType type) {
    Entity* e = dereference_handle(handle);
    if (!e) return;
    if (e->components[type] >= 0) {
        return;
    }

    e->components[type] = Component_new(type);
}

void Entity_remove_component(EntityHandle handle, ComponentType type) {
    Entity* e = dereference_handle(handle);
    if (!e) return;
    if (e->components[type] < 0) {
        return;
    }   
    
    Component_remove(type, e->components[type]);
    e->components[type] = -1;
}

void* Entity_get_component(EntityHandle handle, ComponentType type) {
    Entity* e = dereference_handle(handle);
    if (!e) return NULL;

    return Component_get(type, e->components[type]);
}

static Vector queries;
static bool queries_initialized = false;

EntityQueryHandle Entity_query(int num, ...) {
    if (!queries_initialized) {
        Vector_init(&queries, sizeof(EntityQuery));
    }
    if (num > NUM_COMPONENTS) {
        return (EntityQueryHandle) {-1, -1};
    }
    int requested_components[NUM_COMPONENTS];

    va_list valist;
    va_start(valist, num);
    for(int i = 0; i < num; i++) {
        requested_components[i] = va_arg(valist, int);
    }
    va_end(valist);

    unsigned int query_index = Vector_new_at_earliest(&queries);
    EntityQuery* query = Vector_get(&queries, query_index);
    if (query->_generation == 0) {
        query->_total_handles_allocated = 4;
        query->handles = malloc(sizeof(EntityHandle) * query->_total_handles_allocated);
    }
    query->num = 0;
    query->_generation++;

    for (unsigned int i = 0; i < entities.num_items; i++) {
        Entity* e = Vector_get(&entities, i);
        if (!e) continue;

        {
            bool match = true;
            for (int c = 0; c < num; c++) {
                if (e->components[requested_components[c]] < 0) {
                    match = false;
                }
            }
            if (!match) continue;
        }

        EntityHandle handle = (EntityHandle) {i, e->generation};
        query->handles[query->num] = handle;
        query->num++;
        if (query->num == query->_total_handles_allocated) {
            query->_total_handles_allocated *= 2;
            query->handles = realloc(query->handles, sizeof(EntityHandle) * query->_total_handles_allocated);
        }
    }

    return (EntityQueryHandle) { query_index, query->_generation };
}

EntityQuery* Entity_get_query(EntityQueryHandle handle) {
    EntityQuery *q = Vector_get(&queries, handle.index);
    if (!q) return NULL;
    if (q->_generation != handle.generation) { return NULL; }
    return q;
}

void Entity_return_query(EntityQueryHandle handle) {
    EntityQuery* q = Entity_get_query(handle);
    if (!q) return;

    Vector_remove(&queries, handle.index);
}
