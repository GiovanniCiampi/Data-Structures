/* map.c */

#include "heap.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/*
typedef struct tree_t * tree;
struct tree_t{
  tree left;
  tree right;
  void * object;
};
*/



#define SIZE 5

struct heap_t{
  keyfunc f;
  void** array;
  int size;
  int nb_elem;
};





int max(int x, int y){
  if(x<y)
    return y;
  else
    return x;
}

int left(int index){
  return 2 * index;
}
int right(int index){
  return 2* index + 1;
}
int parent(int index){
  return index / 2;
}
void max_heapify(heap h, int index){
  assert(h && index >=0 && index <= h->nb_elem);
  int l = left(index);
  int r = right(index);
  int largest;
  if(l < h->nb_elem && h->array[l] > h->array[index])
    largest = l;
  else largest = index;
  if(r < h->nb_elem && h->array[r] > h->array[largest])
    largest = r;
  if(largest != index){
    void *swap = h->array[largest];
    h->array[largest] = h->array[index];
    h->array[index] = swap;
    max_heapify(h, largest);
  }

}

void heap_resize(heap h, int new_size){
  assert(h && new_size > h->nb_elem);
  void ** new_array = malloc(sizeof(void *) * new_size);
  for(int i = 0; i < h->nb_elem; i++)
    new_array[i] = h->array[i];  
  free(h->array);
  h->array = new_array;
  h->size = new_size;
}

/* create an empty map */
heap heap_create(keyfunc f){
  heap h = malloc(sizeof(*h));
  h->size = SIZE;
  h->nb_elem = 0;
  h->array = malloc((h->size) *sizeof(void*));
  h->f = f;
  return h;
}

/* create an empty map */
void heap_destroy(heap h){
  if(!h)
    return;
  if(h->array)
    free(h->array);
  free(h);
}

/**/
void heap_enqueue(heap h, void* object){
  if(!h)
    return ;
  if(h->size == h->nb_elem)
    heap_resize(h, 2*(h->size));
  h->array[h->nb_elem] = object;
  h->nb_elem++;
  max_heapify(h, parent(h->nb_elem - 1));
}

/* find an object in the map and return it or NULL if not found */
void* heap_dequeue(heap h){
  if(!h || !(h->array))
    return NULL;
  void *elem = h->array[0];
  h->array[0] = h->array[h->nb_elem];
  if(h->nb_elem > SIZE && h->nb_elem < (h->size / 2))
    heap_resize(h, h->size / 2);
  h->nb_elem--;
  max_heapify(h, 0);
  return elem;
}

/* insert an object in a map and return it or NULL in case of
   failure (NULL object or object already inside the map) */
void * heap_get_max(heap h){
  if(!h || !h->array)
    return NULL;
  return h->array[0];
}

/* dump the underlying binary research tree */
void heap_dump(heap h){

  if(!h)
    return;
  for(int i = 0; i < h->nb_elem ; i++){
    printf("-%d-", *((int *)h->array[i]));
  }
  printf("\n");
}



//------------------AFFICHAGE D'ARBRE BINAIRE--------------



