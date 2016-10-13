#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "sequence.h"

#define SIZE 5

struct sequence_t{

  void **tab;
  int size;
  int nb_elem;
};

sequence sequence_create(){

  sequence s = malloc(sizeof(*s));
  s->tab = calloc(SIZE, sizeof(void *));
  s->nb_elem = 0;
  s->size = SIZE;
  return s;
}

void sequence_destroy(sequence s){

  if(s == NULL || s->tab == NULL)
    return;

  free(s->tab);
  free(s);
}

void* sequence_find(sequence s, int pos){

  if(pos >= 0 && pos < s->nb_elem)
    return s->tab[pos];
  return NULL;
}

void resize(sequence s, int newSize){

  assert(s->nb_elem < newSize);

  void **newTab = calloc(newSize, sizeof(void *));
  int i;

  for(i = 0; i < s->nb_elem; i++)
    newTab[i] = s->tab[i];

  free(s->tab);
  
  s->tab = newTab;
  s->size = newSize;
}

void sequence_insert(sequence s, void *object,  int pos){

  if(pos < 0 || pos > s->nb_elem)
    return;

  if(s->nb_elem == s->size)
    resize(s, 2* s->size);

  int i = s->nb_elem;
  
  for( ; i > pos; i--)
    s->tab[i] = s->tab[i - 1];

  s->tab[pos]= object;
  
  s->nb_elem++;

}

void sequence_delete(sequence s, int pos){

  if(pos >= s->nb_elem || pos < 0)
    return;

  int i;

  for(i = pos; i < s->nb_elem-1; i++)
    s->tab[i] = s->tab[i + 1];

  s->nb_elem--;
  
  if( (s->nb_elem < s->size/2) && (s->size > SIZE) )
    resize(s, s->size/2);

}

void sequence_dump(sequence s){

  int i;
  printf("[");
  
  for(i = 0; i < s->nb_elem; i++)
    printf(" %c", *(char *) s->tab[i]);
  
  printf(" ]\n");
  return;
}

int sequence_length(sequence s){

  return s->nb_elem;
}
  
