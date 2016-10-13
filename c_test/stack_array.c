#include<stdlib.h>
#include"stack.h"

#define BASIC_SIZE 5


struct stack_t{

    void **tab;
    int nb_elem;
    int size;
};

stack stack_create(void){

    stack s = malloc(sizeof(*s));
    s->tab = calloc(BASIC_SIZE, sizeof(void*));
    s->nb_elem = 0;
    s->size = 5;
    
    return s;
}

void stack_resize(stack s, int newSize){

    void **old = s->tab;
    void **tab = calloc(newSize, sizeof(void*));
    int i;
    for(i = 0; i < s->nb_elem; i++)
        tab[i] = s->tab[i];
    
    s->tab = tab;
    s->size = newSize;
    free(old);
}


void stack_push(stack s, void *object){

   if(s->nb_elem == s->size)
        stack_resize(s, (2* s->size));
    
    s->tab[s->nb_elem] = object;
    s->nb_elem++;
    return;
}

int stack_empty(stack s){

    return s->nb_elem == 0;
}

void *stack_top(stack s){

    if(!stack_empty(s))
        return s->tab[s->nb_elem -1];
    return NULL;
}

void stack_pop(stack s){

    if(!stack_empty(s))
        s->nb_elem--;
    
    if(s->nb_elem <= s->size)
        stack_resize(s, (s->size / 2));
    return;
}

