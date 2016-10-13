#include <stdlib.h>
#include <assert.h>
#include "stack.h"



typedef struct node{

	void *object;
	struct node *next;
}node_t;



struct stack_t {

	node_t *list;
};




stack stack_create(void){
	
	stack s;
	s=malloc(sizeof(*s));

	s->list = NULL;
	s->list = malloc(sizeof(node_t));

	return s;
}


 
void stack_push(stack s, void *object){

	node_t * new = NULL;
	new = malloc(sizeof(node_t));
	new->object = object; 
	new->next = s->list;
	s->list = new;

	return;
}

int stack_empty(stack s){

	return s->list == NULL;
}



void *stack_top(stack s){

	if(!stack_empty(s))
		return s->list->object;
	else return NULL;
}

void stack_pop(stack s){
	
	if(!stack_empty(s))
		s->list = s->list->next;
        return;
}

void stack_destroy(stack s){


	while (s->list != NULL){
		
		node_t *prev = s->list;
		s->list = s->list->next;
		//free(prev);
	}
}


