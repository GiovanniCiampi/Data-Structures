#include <stdio.h>
#include "queue.h"
#include "stdlib.h"
#include "assert.h"

int main(void){

	int a[15];

	queue q = create_queue();


	for(int i = 0; i < 15; i++){
		a[i] = rand() % 50;
		printf("- %d -", a[i]);
	}

	printf("----------------\n");

	for(int i = 0; i < 15; i++)
		enqueue(q, &a[i]);

	printf("\n--------ENQUEUED--------\n");

	printf("FRONT : %d \n", *(int *) front(q));

	printf("----------------\n");

	for(int i = 0; i < 15; i++)
		printf("- %d -", *(int *)dequeue(q));

	printf("\n--------DEQUEUED--------\n");

	destroy_queue(q);

	printf("--------DESTROYED--------\n");





	
}
