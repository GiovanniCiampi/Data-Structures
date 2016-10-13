#include<stdio.h>


typedef struct trouArray{
	void **tab;
	int debTrou;
	int sizeTrou;
	int size;
};

void insert(trouArray trou, int pos, void *object);
void delete(trouArray trou, int pos);

int main(int argc, char** argv){


	trouArray trou = malloc(sizeof(*trou));
	trou->tab = calloc(5, sizeof(void *));

	trou->size = 5;
	trou->debTrou = 0;
	trou->sizeTrou = 5;


}

void insert(trouArray trou, int pos, void *object){

	if(pos < 0 || pos > trou->size - trou->sizeTrou)
		return;

	if(pos < trou->debTrou){

		int i; 
		int diff = trou->debTrou - pos;
		int end = trou->debTrou + trou->sizeTrou - 1;

		for(i = 0; i < diff; i++)
			trou->tab[end - diff + i] = trou->tab[pos + i];
		trou->tab[pos] = object;
		trou->debTrou = pos + 1;

	} else if (pos > trou->debTrou + trou->sizeTrou) {

	}
}
