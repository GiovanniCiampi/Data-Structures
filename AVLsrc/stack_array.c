#include<stdlib.h>
#include<assert.h>
#include"stack.h"

#define SIZE 5

struct stack_t{
	void **tab;
	int size;
	int nb_elem;
};


void stack_resize(stack s, int newSize){
	assert(s->nb_elem < newSize);

	void **newTab = calloc(newSize, sizeof(void *));

	int i;
	for(i = 0; i < s->nb_elem; i++){
		newTab[i] = s->tab[i];
	}

	free(s->tab);
	s->tab = newTab;
	s->size = newSize;
}

stack stack_create(){

	stack s = malloc(sizeof(*s));

	s->tab = calloc(SIZE, sizeof(void *));

	s->size = SIZE;
	s->nb_elem = 0;

	return s;

}

int stack_empty(stack s){
	return s->nb_elem == 0;
}

void *stack_pop(stack s){
	if(stack_empty(s))
		return NULL;
	void *pop = s->tab[s->nb_elem - 1];
	s->nb_elem--;

	if(s->nb_elem > 5 && s->nb_elem < s->size / 2)
		stack_resize(s, s->size / 2);

	return pop;
}

void stack_push(stack s, void *object){
	if(s->nb_elem >= s->size)
		stack_resize(s, s->size * 2);

	s->tab[s->nb_elem] = object;
	s->nb_elem++;
}

void stack_destroy(stack s){
	free(s->tab);
	free(s);
	return;
}