#include<stdio.h>
#include"sequence.h"
#include<assert.h>
#include<stdlib.h>


#define SIZE 5
#define INSERT 1
#define DELETE 2

struct sequence_t{
    void **tab;
    int size;
    int deb_trou;
    int taille_trou;
};

sequence sequence_create(){

    sequence s = malloc(sizeof(*s));
    s->tab = calloc(SIZE, sizeof(void *));
    s->size = SIZE;
    s->deb_trou = 0;
    s->taille_trou = SIZE;
    return s;
}


void deplace_trou(int pos, int mode, sequence s){

  assert(pos >= 0 && pos <= s->size - s->taille_trou && !(mode == DELETE && pos == s->size - s->taille_trou));

  if(pos == s->deb_trou){
      return;
  }

  if(pos < s->deb_trou){
      s->tab[pos + s->taille_trou] = s->tab[pos];
      s->deb_trou--;
  }
  else{
      s->tab[pos] = s->tab[pos + s->taille_trou];
      s->deb_trou++;    
  }

  deplace_trou(pos, mode, s);
}

void sequence_resize(sequence s, int newSize){
    assert(newSize > s->size - s->taille_trou);

    void **newTab = calloc(newSize, sizeof(void *));

    int i;

    deplace_trou(0, INSERT, s);

    for(i = 0; i < s->deb_trou; i++)
        newTab[i] = s->tab[i];

    s->taille_trou = newSize - (s->size - s->taille_trou);
    s->size = newSize;
    free(s->tab);
    s->tab = newTab;

}

/*
void deplace_trou(int pos, int mode, sequence s){

    assert(pos >= 0 && pos <= s->size - s->taille_trou && !(mode == DELETE && pos == s->size - s->taille_trou));

    int i;

    if(pos == s->deb_trou)
        return;

    else if(pos < s->deb_trou){

        for(i = pos; i < s->deb_trou; i++)
            s->tab[i + s->taille_trou] = s->tab[i];

    } else if(pos > s->deb_trou){

        for(i = pos + s->taille_trou; i >= s->deb_trou + s->taille_trou; i--)
            s->tab[i - s->taille_trou] = s->tab[i];

    }

    s->deb_trou = pos;
}
*/




void sequence_destroy(sequence s){
    if(s == NULL)
        return;
    if(s->tab != NULL)
        free(s->tab);

    free(s);
}

void *sequence_find(sequence s, int pos){
    if(pos > s->size - s->taille_trou || pos < 0)
        return NULL;
    if(pos < s->deb_trou)
        return s->tab[pos];
    else 
        return s->tab[pos + s->taille_trou];
}

void sequence_insert(sequence s, void * object, int pos){

    if(pos < 0 || pos > (s->size - s->taille_trou))
      return;

    if(s->taille_trou <= 2)
      sequence_resize(s, 2*s->size);
    

    deplace_trou(pos, INSERT, s);
    s->tab[pos] = object;
    s->deb_trou++;
    s->taille_trou--;
}

void sequence_delete(sequence s, int pos){
  if(pos < 0 || pos >= (s->size - s->taille_trou))
      return;

  if(s->size > 5 && s->taille_trou > s->size / 2)
      sequence_resize(s, s->size / 2);

  deplace_trou(pos, DELETE, s);
  s->taille_trou++;
}

void sequence_dump(sequence s){
    int i;
    printf("-");
    for(i = 0; i< s->deb_trou; i++)
        printf("%c-", *(char *) s->tab[i]);
    for(i = s->deb_trou; i< s->deb_trou + s->taille_trou; i++)
        printf("0-");
    for(i = s->deb_trou + s->taille_trou; i < s->size; i++)
        printf("%c-", *(char *) s->tab[i]);

    printf("\t\t|");

}

int sequence_length(sequence s){
    return s->size - s->taille_trou;
}

