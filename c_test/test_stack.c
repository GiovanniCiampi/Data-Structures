#include<stdio.h>
#include"stack.h"

int main(void){

    stack st = stack_create();
    

    int push = 0, cmd;
    
    while(1){
    
        printf("push = 1\n pop = 2\n top = 3\n");
        scanf("%d", &cmd);
        
        switch(cmd){
        
            case 1:
                printf("inserisci numero_");
                scanf("%d", &push);
                stack_push(st, &push);
                break;
                
            case 2: 
                stack_pop(st);
                break;
                
            case 3: 
                printf("top = %d", *( (int *) stack_top(st)) );
                break;
                
            default:
                printf("default");
                break;
        }
    }
    

    return 0;
}