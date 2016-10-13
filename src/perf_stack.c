/* perf_stack.c */

#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

int main (int argc, char* argv[]) 
{
  struct timeval start, end; 
  double time_exp, time_amorti;
  int i, n, max = 1000000;
  int val = 1;

  printf("# n time_exp(µs) time_amorti(µs)\n");        
  
  for(n = 10 ; n < max ; n *= 2) {    
    // create stack
    stack p = stack_create();
    
    gettimeofday(&start,NULL);
    
    // push n times in the stack
    for(i = 1 ; i < n ; i++) { 
      stack_push(p, &val);
    }
    
    gettimeofday(&end,NULL);    
    time_exp = ((end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec)); // µs
    time_amorti = time_exp / n;
    printf("%d %.2f %.2f\n",n,time_exp,time_amorti);
    
    stack_destroy(p);    
  }

  return 0;
}
