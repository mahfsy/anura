#ifndef QUEUE_H
#define QUEUE_H

typedef struct {
    void* data;

    int front;
    int rear;

    unsigned int _total_items_allocated;
    unsigned int _bytes_per_item;
} Queue;

void Queue_init(Queue* q, unsigned int bytes_per_item);

void Queue_enqueue(Queue* q, void* item);
void* Queue_get_front(Queue* q); //returns NULL if queue is empty
void Queue_dequeue(Queue* q); //returns false if queue was empty

#endif
