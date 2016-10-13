#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "assert.h"

struct node_t{
	void *object;
	struct node_t *next;
};

typedef struct node_t *node;

struct queue_t{
	node front;
	node rear;
};


queue create_queue(){
	queue q = malloc(sizeof(*q));
	q->front = malloc(sizeof(*q->front));
	q->front->object = NULL;
	q->front->next = NULL;
	q->rear = q->front;
	return q;
}

void enqueue(queue q, void* object){
	node new = malloc(sizeof(*new));
	new->next = NULL;
	new->object = object;
	q->rear->next = new;
	q->rear = new;
}

void *dequeue(queue q){
	if(is_empty(q))
		return NULL;
	void *value = q->front->next->object;

	if(q->front->next == q->rear){
		free(q->rear);
		q->rear = q->front;
		return value;
	}

	node first = q->front->next->next;
	free(q->front->next);
	q->front->next = first;
	return value;
}

void *front(queue q){
	if(is_empty(q))
		return NULL;
	return q->front->next->object;
}

int is_empty(queue q){
	return q->front == q->rear;
}

void destroy_queue(queue q){
	if(!q)
		return;
	while(!is_empty(q)){
		node copy = q->front->next;
		free(q->front);
		q->front = copy;
	}

	free(q->front);
	free(q);
}

