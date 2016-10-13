/* test_queue.c */

#include "queue.h"
#include "stdio.h"

int main (int argc, char* argv[]) 
{

    int choice;
    printf("1 = push, 2 = pop, -1 = exit\n");
    queue q = queue_create();
    while(1){
    
        int push;
        scanf("%d", &choice);
        switch(choice){
        
            case 1: 
                printf("Inserisci numero _");
                scanf("%d", &push);
                queue_push(q, &push);
                break;
            case 2:
                printf("eliminato = %d \n",*((int *)queue_front(q)));
                queue_pop(q);
                break;
            case -1:
                return 0;
        }
    }
}
