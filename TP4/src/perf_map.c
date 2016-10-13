/* perf_map.c */

#include "map.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>

int f(void * object) { return *((int*)object); }

void swap(int * tab, int i, int j) 
{
  int tmp = tab[i];
  tab[i] = tab[j];
  tab[j] = tmp;
}

int * random_permutation(int n) 
{
  int i;
  int * tab = malloc(n*sizeof(int));
  for(i = 0 ; i < n ; i++) tab[i] = i;
  for(i = 0 ; i < n ; i++) {
    int j = rand() % (n-i) + i;
    swap(tab,i,j);
  }
  return tab;
}


int main (int argc, char* argv[]) 
{
  struct timeval start, end; 
  int n, N = 1000;
  int EXP = 100;
  int i,j;
  double result, mean, amorti;
  double height;
  
  srand((unsigned int)time(NULL));
  
  printf("# n height mean(µs) amorti(µs)\n");        
  
  // for different size of tree
  for(n = 2 ; n < N ; n*=2) { 
    
    result = mean = amorti = 0.0;
    height = 0.0;

    // repeat EXP times 
    for(j = 0 ; j < EXP ; j++) {
      
      // create map
      map m = map_create(f);
      int * objs = random_permutation(n);
      
      /* printf("objs ["); */
      /* for(i = 0 ; i < n ; i++) printf("%d ", objs[i]); */
      /* printf("]\n"); */
      
      // insert n times in the map
      gettimeofday(&start,NULL);
      for(i = 0 ; i < n ; i++) {     
	map_insert(m, &objs[i]);
      }    
      gettimeofday(&end,NULL);    
      result = ((end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec)); // µs
      mean += result;

      height += map_height(m);

      // free memory      
      map_destroy(m);
      free(objs);
    }
    mean = mean / EXP; // mean time    
    amorti = mean / n; 
    height = height / EXP; // mean height
    printf("%d %.2f %.4f %.4f\n",n, height, mean, amorti);    
  }  
  
  return EXIT_SUCCESS;
}
