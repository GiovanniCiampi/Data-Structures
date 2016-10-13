/* test_sequence.c */

#include "sequence.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char* argv[]) 
{
  int pos = 0;
  int length = 0;
  sequence s = sequence_create();
  srand(time(NULL));
   
  while(length < 20) {
    char * c = malloc(sizeof(char));
    *c = getc(stdin);
    if(*c == '\n') continue;
    printf("insert position_");
    scanf("%d", &pos);
    printf("\n");
    printf("try to insert '%c' at pos %d...\n",*c,pos);
    sequence_insert(s,c,pos);
    length++;
    sequence_dump(s);
  }

  sequence_destroy(s);
  return 0;
}
