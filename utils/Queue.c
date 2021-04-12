#include "Queue.h"

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define INITIAL_SIZE 64

void Queue_init(Queue* q, unsigned int bytes_per_item) {
    q->_bytes_per_item = bytes_per_item;
    q->front = -1;
    q->rear = -1;

    q->_total_items_allocated = INITIAL_SIZE;
    q->data = calloc(q->_total_items_allocated, q->_bytes_per_item);
}

bool Queue_is_full(Queue* q) {
    return 
        ((q->front == 0 && q->rear == (int)q->_total_items_allocated - 1) ||
         (q->rear == (int) ((q->front - 1)%(q->_total_items_allocated - 1))));
}

void Queue_set_data_index(Queue* q, int index, void* item) {
    memcpy(q->data + (index * q->_bytes_per_item), item, q->_bytes_per_item);
}

void* Queue_get_data_index(Queue* q, int index) {
    return q->data + (index * q->_bytes_per_item);
}

void Queue_enqueue(Queue* q, void* item) {
    if (Queue_is_full(q)) {
        //adjust for this, remove rturn statement
        return;
    }
    
    if (q->front == -1) { //first element
        q->rear = 0;
        q->front = q->rear;
        Queue_set_data_index(q, q->rear, item);
    }
    else if (q->rear == (int) q->_total_items_allocated-1 && q->front != 0) { // we're at the end of allocation
        q->rear = 0;
        Queue_set_data_index(q, q->rear, item);
    }
    else {
        q->rear++;
        Queue_set_data_index(q, q->rear, item);
    }
}

void* Queue_get_front(Queue* q) {
    if (q->front == -1) {
        return NULL;
    }
    return Queue_get_data_index(q, q->front);
}

void Queue_dequeue(Queue* q) {
    if (q->front == q->rear) {
        q->front = -1;
        q->rear = -1;
    }
    else if (q->front == (int) q->_total_items_allocated - 1) {
        q->front = 0;
    }
    else {
        q->front++;
    }
}
