#include "rope.h"
#include "rope_handling.h"
#include "stdio.h"

int main(int argc, char* argv[])
{
  char* sep = "\n---------------------------------------------------------\n";

  //question 1.1

  rope str1 = of_string("abcdefg");
  rope str2 = of_string("hijklmn");
  rope str3 = of_string("opqrstu");
  rope str4 = of_string("vwxyz !");
  printf("%s", sep);
  printf("test nb_parents\n");
  rope alpha = concat(concat(str1,sub_rope(concat(str2,str3), 5, 6)),str4);
  char ee = char_at(alpha,4);
  char mm = char_at(alpha,7);
  char pp = char_at(alpha,10);
  char ww = char_at(alpha,14);
  printf("a: %d || b: %d || c: %d || d: %d \n", get_nbparents(str1),
   get_nbparents(sub_rope(str2, 2, 3)), get_nbparents(concat(str1, str2)), get_nbparents(alpha));
  printf("Test de charat:\n\n");
  printf("should print e,m,p,w and print %c,%c,%c,%c\n\n",ee,mm,pp,ww);
  printf("Fin du test de char_at.");
  printf("%s",sep);

  //question 1.2
  
  rope hello_world = delete(of_string("hell##o world!"),4,2);
  printf("Test de delete:\n\n");
  printf("Should print\n\t\"hello world!\"\nand prints:\n\t\"");
  int i;
  for(i=0;i<12;i++){printf("%c", char_at(hello_world,i));}
  printf("\"\n\nFin du test de delete");
  printf("%s",sep);
  
  //question 1.3

  rope everybody = of_string(" everybody in the");
  rope hello_everybody = insert(hello_world,everybody,5);
  printf("Test de insert:\n\n");
  printf("Should print\n\t\"hello everybody in the world!\"\nand prints:\n\t\"");
  for(i=0;i<29;i++){printf("%c",char_at(hello_everybody,i));}
  printf("\"\n\nFin du test de insert");
  printf("%s",sep);

  //question 1.4

  rope world = sub_rope(hello_everybody,22,6);
  rope_draw(world,"test_to_string.dot",2);

    printf("%s",sep);
    printf("Test 2\n");
    printf("%s",sep);

  return 0;
}
