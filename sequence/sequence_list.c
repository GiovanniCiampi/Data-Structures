#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "sequence.h"

#define SIZE 5

struct node_t{

  void *elem;
  struct node_t *next;
};

typedef struct node_t *list;

struct sequence_t{

  list lista;
  int nb_elem;
};

sequence sequence_create(){

  sequence s = malloc(sizeof(*s));
  s->lista = NULL;
  s->nb_elem = 0;
  return s;
}

void sequence_destroy(sequence s){

  if(s == NULL)
    return;
  if(s->lista ==NULL){

    free(s);
    return;
  }
  list copy = s->lista->next;
  while(copy != NULL){

    free(s->lista);
    s->lista = copy;
    copy = copy->next;
  }
  free(s->lista);
  free(s);
}

void* sequence_find(sequence s, int pos){
  
  if(pos < 0 || pos >= s->nb_elem)
    return NULL;
  
  int i = 0;
  list copy = s->lista;
  
  while(copy->next != NULL && i < pos){
    copy = copy->next;
    i++;
  }
  return copy->elem;

}


void sequence_insert(sequence s, void *object,  int pos){

  if(pos < 0 || pos >s->nb_elem)
    return;

  if(pos == 0){

    list newNode = malloc(sizeof(*newNode));
    newNode->elem = object;
    newNode->next = s->lista;
    s->lista = newNode;
    s->nb_elem++;
    return;
  }

  int i = 0;
  list copy = s->lista;
  
  while(copy->next != NULL && i < pos-1){
    copy = copy->next;
    i++;
  }

  list newNode = malloc(sizeof(*newNode));
  newNode->elem = object;
  newNode->next = copy->next;
  copy->next = newNode;

  s->nb_elem++;
}

void sequence_delete(sequence s, int pos){
  
  if(pos < 0 || pos >=s->nb_elem)
    return;

  if(pos == 0){
    s->lista = s->lista->next;
    s->nb_elem--;
    return;
  }

  int i = 0;
  list copy = s->lista;
  while(copy->next != NULL && i < pos -1){
    copy = copy->next;
    i++;
  }
  copy->next = copy->next->next;
  s->nb_elem--;
}

void sequence_dump(sequence s){
  
  list copy = s->lista;
  while(copy != NULL){
    printf(" %c", *(char *) copy->elem);
    copy = copy->next;
   }
  printf("\n");

}

int sequence_length(sequence s){

  return s->nb_elem;
}
  
