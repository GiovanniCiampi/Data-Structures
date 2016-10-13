#include<stdlib.h>
#include<assert.h>
#include"stack.h"

struct node_t{
	void *object;
	struct node_t *next;
};

typedef struct node_t *node;

struct stack_t{
	node list;
};

stack stack_create(){
	stack s = malloc(sizeof(*s));
	s->list = NULL;
	return s;
}

int stack_empty(stack s){
	return s->list == NULL;
}

void *stack_pop(stack s){
	if(s->list == NULL)
		return NULL;
	void *pop = s->list->object;
	s->list = s->list->next;
	return pop;
}

void stack_push(stack s, void *object){
	node new = malloc(sizeof(*new));
	new->object = object;
	new->next = s->list;
	s->list = new;
}

void stack_destroy(stack s){
}