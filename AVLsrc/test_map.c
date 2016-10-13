/* test_map.c */

#include "map.h"
#include "stdio.h"

int f(void * object) { return *((int*)object); }

int main (int argc, char* argv[]) 
{
  map m = map_create(f);
  int a=10, b=6, c=13, d=19, e=14, f=20, g=11, h = 2, i = 8, l = 7;
  map_insert(m, &a);
  map_insert(m, &b);
  map_insert(m, &c);
  map_insert(m, &d);
  map_insert(m, &e);
  map_insert(m, &f);
  map_insert(m, &g);
  map_insert(m, &h);
  map_insert(m, &i);
  map_insert(m, &l);

  map_dump(m);


  void * fb = map_find(m, b);
  printf("find %d: %s\n", b, (fb != NULL)?"true":"false");

  /* delete a leaf */
  //map_delete(m,f); 
  /* delete a node with a single child */
  // ???

  /* delete a node with two children */
  //map_delete(m,d); 
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

  map_dump(m);
  map_destroy(m);
  
  return 0;
  
}
