#ifndef QUEUE_H
#define QUEUE_H

struct queue_t;

typedef struct queue_t *queue;

queue create_queue();

void enqueue(queue q, void* object);

void *dequeue(queue q);

void *front(queue q);

int is_empty(queue q);

void destroy_queue(queue q);

#endif