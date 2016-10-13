#include <stdlib.h>
#include <assert.h>
#include "stack.h"

#define INITIAL_SIZE  2

void stack_resize(stack , int );

struct stack_t {

	void ** array;
	int size;
	int num_elements;
};


stack stack_create(void){

	stack s;
	s=malloc(sizeof(*s));
	s->array=calloc(INITIAL_SIZE, sizeof(void *));
	s->size = INITIAL_SIZE;
	s->num_elements = 0;
	return s;
}


 
void stack_push(stack s, void *object){

	if(s->num_elements == s->size - 1)
		stack_resize(s, 2* s->size );

	s->array[s->num_elements] = object;
	s->num_elements++;
	return;
}

int stack_empty(stack s){

	return s->num_elements == 0;
}



void *stack_top(stack s){

	assert(!stack_empty(s));

	return s->array[s->num_elements - 1];
}

void stack_pop(stack s){

	assert(!stack_empty(s));

	s->num_elements--;

	if(s->num_elements <= (s->size)/2)
		stack_resize(s, (s->size)/2);

        return;
}



void stack_resize(stack s, int new_size){

	assert(s->num_elements < new_size);

	void **array = calloc(new_size, sizeof(void *));
	void **old_array = s->array;

	int i;
	for(i = 0; i < s->num_elements; i++)
		array[i] = old_array[i];

	s->array = array;
	free(old_array);
	return;
}


void stack_destroy(stack s){

	free(s->array);
	return;
}
