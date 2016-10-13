#include<stdio.h>
#include <stdlib.h>
#include "queue.h"

struct queue_t {

  void *data;
  struct queue_t *next;
};

queue queue_create(){
  
  queue s = malloc(sizeof(struct queue_t));
  s->data = NULL;
  s->next = NULL;
  return s;
}

int queue_empty(queue s){

  return s->next == NULL;
}

void queue_push(queue s, void *object){

  queue new = malloc(sizeof(struct queue_t));
  new->data = object;
  new->next = s->next;
  s->next = new;
}

void *queue_front(queue s){

  if(!queue_empty(s))
    return (s->next)->data;
  return NULL;
}

void queue_pop(queue s){

  if(!queue_empty(s)){
    queue old = s->next;
    s->next = s->next->next;
    free(old);
  }
}

void queue_destroy(queue s){

  while(!queue_empty(s))
    queue_pop(s);
  free(s);
}
