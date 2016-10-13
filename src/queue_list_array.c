#include<stdio.h>
#include<stdlib.h>
#include "queue.h"

#define SIZE 5

struct queue_t{
    struct queue_t *next;
    void **tab;
    int first;
    int nb_elem;
};

/* create an empty queue */
queue queue_create(void){
    queue s = malloc(sizeof(struct queue_t));
    s->tab = calloc(SIZE, sizeof(void *));
    s->next = NULL;
    s->first = 0;
    s->nb_elem = 0;
    return s;
}

/* create an empty queue */
void queue_destroy(queue s){
    if(queue_empty(s))
        return;
    queue copySucc = s;
    queue copyPrev;
    do{
        copyPrev = copySucc;
        copySucc = copySucc->next;
        free(copyPrev);
    } while(copySucc != NULL);
}

/* return true if and only if the queue is empty */
int queue_empty(queue s){
    return s->nb_elem == 0;
}

/* push an object on the back of the queue */
void queue_push(queue s, void *object){
    queue copy = s;
    while(copy->next != NULL)
        copy = copy->next;
    
    if(copy->first + copy->nb_elem >= SIZE){
    
        queue newQueue;
        newQueue = malloc(sizeof(struct queue_t));
        newQueue->tab = calloc(SIZE, sizeof(void *));
        newQueue->tab[0] = object;
        newQueue->next = NULL;
        newQueue->first = 0;
        newQueue->nb_elem = 1;
        
        copy->next = newQueue;
        return;
    }
    
    copy->tab[copy->first + copy->nb_elem] = object;
    copy->nb_elem++;
    return;
}

void *queue_front(queue s){

    if(queue_empty(s))
        return NULL;
    
    return s->tab[s->first];
}


/* pop the front element off of the queue.
The queue must not be empty (as reported by queue_empty()) */
void queue_pop(queue s){
    if(queue_empty(s))
        return;
    
    queue kk = s;
    int i = 1, j;
   

    if(s->next == NULL){
        if(s->nb_elem == 1)
            s->first = 0;
        else s->first++;
        s->nb_elem--;
    }
    else if(s->nb_elem <= SIZE / 2 && s->next->nb_elem <= SIZE / 2){
    
        void **newTab = calloc(SIZE, sizeof(void *));
        int i, k;
        int el1 = s->nb_elem;
        int el2 = s->next->nb_elem;
        
        for(i = 0, k = s->first + 1; k < s->first + el1; i++, k++)
            newTab[i] = s->tab[k];
        for(k = s->next->first; k < s->next->first + el2; i++, k++)
            newTab[i] = s->next->tab[k];
        queue copy = s->next;
        free(s->tab);
        s->next = s->next->next;
        s->tab = newTab;
        s->first = 0;
        s->nb_elem = el1 + el2 - 1;
        free(copy->tab);
        free(copy);
        
     
    } else {
    
        void **newTab = calloc(SIZE, sizeof(void *));
        int i;
        for(i = 1; i < s->nb_elem; i++)
            newTab[i - 1] = s->tab[i + s->first];
        free(s->tab);
        s->tab = newTab;
        s->first = 0;
        s->nb_elem--;
    }
}
