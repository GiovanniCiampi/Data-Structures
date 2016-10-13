#include<stdio.h>
#include<assert.h>
#include"stack.h"

int main(void){

	stack s = stack_create();

	char a;
	int i;
	char arr[20];

	for(i = 0; i < 20; i++){
		printf("Insert character_");
		scanf("%s", &arr[i]);
		stack_push(s, &arr[i]);
	}

	for(i = 0; i < 20; i++){
		printf("pop%d: %c\n", i, *(char *) stack_pop(s));
	}

	stack_destroy(s);

	return 0;
}