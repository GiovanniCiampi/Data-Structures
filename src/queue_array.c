#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#include "queue.h"

#define BASIC_SIZE 5

struct queue_t{

  void **tab;
  int size;
  int front;
  int nb_elem;
};

void queue_resize(queue s, int newSize){

  assert(s->nb_elem < newSize);
  void **newTab = calloc(newSize, sizeof(void *));

  int i;
  for(i = 0; i< s->nb_elem; i++){
    newTab[i] = s->tab[(s->front+i) % s->size];
  } 

  void **oldTab = s->tab;
  s->size = newSize;
  s->tab = newTab;
  s->front = 0;
  free(oldTab);
}

queue queue_create(void){

  queue s = malloc(sizeof(struct queue_t));
  s->tab = calloc(BASIC_SIZE, sizeof(void *));
  s->size = BASIC_SIZE;
  s->front = 0;
  s->nb_elem = 0;
  return s;
}

int queue_empty(queue s){

  return s->nb_elem == 0;
}

void queue_push(queue s, void *object){

   if(s->size == s->nb_elem)
     queue_resize(s, 2 * s->size);
   
   int back = (s->front + s->nb_elem) % s->size;
   s->tab[back] = object;
   s->nb_elem++;

}

void *queue_front(queue s){

  if(!queue_empty(s))
    return s->tab[s->front];
  return NULL;
}

void queue_pop(queue s){
  if(queue_empty(s)){
    return;
  }
  
  s->front=(s->front +1) % s->size;
  s->nb_elem--;
  if(s->size > 5 && s->nb_elem < (s->size / 2))
    queue_resize(s, s->size / 2);
}

void queue_destroy(queue s){

  free(s->tab);
  free(s);
}
