/* test_map.c */

#include "heap.h"
#include "stdio.h"

int f(void * object) { return *((int*)object); }

int main (int argc, char* argv[]) 
{
  heap h = heap_create(f);
  int a=10, b=6, c=13, d=19, e=14, f=20, g=11, m = 2, i = 8, l = 7;
  printf("en1\n");
  heap_enqueue(h, &a);
    printf("en1\n");

  heap_enqueue(h, &b);
  heap_enqueue(h, &c);
  heap_enqueue(h, &d);
  heap_enqueue(h, &e);
  heap_enqueue(h, &f);
  heap_enqueue(h, &g);
  heap_enqueue(h, &m);
  heap_enqueue(h, &i);
  heap_enqueue(h, &l);
  printf("en1\n");

  heap_dump(h);
    printf("en1\n");



  void * fb = heap_get_max(h);
  printf("max = %d\n", *(int *) fb);

  //printf("find %d: %s\n", b, (fb != NULL)?"true":"false");

  /* delete a leaf */
  //map_delete(m,f); 
  /* delete a node with a single child */
  // ???

  /* delete a node with two children */
  //map_delete(m,d); 
  /*
  map_delete(m,a); 
  map_dump(m);
  map_delete(m,f);
  map_dump(m);
  map_delete(m,d);
  map_dump(m);
  map_delete(m,b);
  map_dump(m);
  map_delete(m,l);

  /* delete the root node */
  //map_delete(m,a); 

  heap_dump(h);
  heap_destroy(h);
  
  return 0;
  
}
