#include "Vector.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static const unsigned int INITIAL_SIZE = 4;

void Vector_init(Vector* v, unsigned int bytes_per_item) {
    v->_bytes_per_item = bytes_per_item;
    v->num_items = 0;
    v->total_items_allocated = INITIAL_SIZE;
    v->data = calloc(v->total_items_allocated, v->_bytes_per_item);
    v->index_is_used = calloc(v->total_items_allocated, sizeof(bool));
    v->_earliest_open_slot = 0;
}

void Vector_resize(Vector* v, unsigned int new_total_items) {
    if (new_total_items < v->num_items) {
        v->num_items = new_total_items;
    }

    v->total_items_allocated = new_total_items;

    v->data = realloc(v->data, v->total_items_allocated * v->_bytes_per_item);
    v->index_is_used = realloc(v->index_is_used, v->total_items_allocated * sizeof(int));
}

void* Vector_get(Vector* v, unsigned int index) {
    if (index > v->total_items_allocated) {
        return NULL;
    }
    if (!v->index_is_used[index]) {
        return NULL;
    }

    return (v->data + (v->_bytes_per_item * index));
}

void Vector_set(Vector* v, unsigned int index, void* new_item) {
    if (index >= v->total_items_allocated) {
        printf("Error: vector index out of bounds: %d out of %d allocated\n", index, v->total_items_allocated);
        return;
    }
    if (index >= v->num_items) {
        v->num_items = index + 1;
    }
    v->index_is_used[index] = 1;
    if (index == v->_earliest_open_slot) {
        for(unsigned int i = index + 1; i < v->total_items_allocated; v++) {
            if (!v->index_is_used[i]) {
                v->_earliest_open_slot = i;
                break;
            }
        }
    }
    memcpy(v->data + (index * v->_bytes_per_item), new_item, v->_bytes_per_item);
}

void Vector_remove(Vector* v, unsigned int index) {
    if (index >= v->total_items_allocated) {
        return;
    }
    v->index_is_used[index] = false;
}

bool Vector_index_is_used(Vector* v, unsigned int index) {
    if (index >= v->total_items_allocated) {
        return true;
    }
    return v->index_is_used[index];
}

unsigned int Vector_new_at_earliest(Vector* v) {
    if (v->_earliest_open_slot >= v->total_items_allocated) {
        int new_size = v->total_items_allocated * 2;
        if (new_size == 0) {
            new_size = INITIAL_SIZE;
        }
        Vector_resize(v, new_size);
    }   

    unsigned int new_earliest = v->total_items_allocated;
    for (unsigned int i = v->_earliest_open_slot; i < v->total_items_allocated; i++) {
        if (!v->index_is_used[i]) {
            new_earliest = i;
            break;
        }
    }
    unsigned int ret = v->_earliest_open_slot;
    v->index_is_used[ret] = true;
    v->_earliest_open_slot = new_earliest;
    if (ret >= v->num_items) {
        v->num_items = ret + 1;
    }
    return ret;
}

unsigned int Vector_insert_at_earliest(Vector* v, void* data) {
    unsigned int earliest = Vector_new_at_earliest(v);
    Vector_set(v, earliest, data);
    return earliest;
}

void Vector_push(Vector* v, void* new_item) {
    if (v->num_items == v->total_items_allocated) {
        Vector_resize(v, v->total_items_allocated * 2);
    }

    Vector_set(v, v->num_items, new_item);
}

void* Vector_top(Vector* v) {
    if (v->num_items == 0) {
        return NULL;
    }

    return v->data + ((v->num_items -1) * v->_bytes_per_item);
}

void* Vector_pop(Vector* v) {
    void* item = Vector_top(v);
    if (v->num_items > 0) {
        v->num_items--;
        v->index_is_used[v->num_items] = false;
    }
    return item;
}

void Vector_delete(Vector* v) {
    free(v->data);
    v->num_items = 0;
    v->_bytes_per_item = 0;
    v->total_items_allocated = 0;
}
