/* test_map.c */

#include "map.h"
#include "stdio.h"

int f(void * object) { return *((int*)object); }

int main (int argc, char* argv[]) 
{
  map m = map_create(f);

  int a=10, b=6, c=13, d=19, e=14, f=20, g=11, h = 25, i = 23, l = 27, n = 26;
  map_insert(m, &a);
    printf("Contiene solo 10\n");

    map_dump(m);


  map_insert(m, &b);
      printf("Ho inserito 6\n");

    map_dump(m);


  map_insert(m, &c);
    printf("Ho inserito 13\n");
    map_dump(m);

  map_insert(m, &d);

    printf("Ho inserito 19\n");
    map_dump(m);
  map_insert(m, &e);
   printf("Ho inserito 14\n");
    map_dump(m);
  map_insert(m, &f);
  printf("Ho inserito 20\n");
    map_dump(m);
  map_insert(m, &g);
  printf("Ho inserito 11\n");
    map_dump(m);
    map_insert(m, &h);
printf("Ho inserito 25\n");
    map_dump(m);
  map_insert(m, &i);

  map_insert(m, &l);

  map_insert(m, &n);

  printf("test6");
  map_dump(m);

  void * fb = map_find(m, b);
  printf("find %d: %s\n", b, (fb != NULL)?"true":"false");

  /* delete a leaf */
  // map_delete(m,f); 
  /* delete a node with a single child */
  // ???

  /* delete a node with two children */
  map_delete(m,c); 
    map_dump(m);

  map_delete(m,g); 
    map_dump(m);

    map_delete(m,b); 



  /* delete the root node */
  // map_delete(m,a); 

  map_dump(m);
  
  return 0;
  
}
